/*
  The oRTP library is an RTP (Realtime Transport Protocol - rfc1889) stack.
  Copyright (C) 2001  Simon MORLAT simon.morlat@linphone.org

  This library is free software; you can redistribute it and/or
  modify it under the terms of the GNU Lesser General Public
  License as published by the Free Software Foundation; either
  version 2.1 of the License, or (at your option) any later version.

  This library is distributed in the hope that it will be useful,
  but WITHOUT ANY WARRANTY; without even the implied warranty of
  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
  Lesser General Public License for more details.

  You should have received a copy of the GNU Lesser General Public
  License along with this library; if not, write to the Free Software
  Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA
*/


#include <ortp/ortp.h>
#include <ortp/telephonyevents.h>
#include "rtpmod.h"
#include "jitterctl.h"
#include "scheduler.h"
#include "port_fct.h"
#include "utils.h"

#include <fcntl.h>
#include <errno.h>
#include <stdlib.h>
#include <stdio.h>

#ifndef _WIN32
# include <sys/types.h>
# include <sys/socket.h>
# include <netinet/in.h>
# include <arpa/inet.h>
# ifdef INET6
#  include <netdb.h>
# endif
#else
# include <winsock2.h>
# include "errno-win32.h"
#endif


#if defined(HAVE_POLL_H)
#include <poll.h>
#elif defined(HAVE_SYS_POLL_H)
#include <sys/poll.h>
#endif
#ifdef HAVE_SYS_UIO_H
#include <sys/uio.h>
#define USE_SENDMSG 1
#endif



void wait_point_init(WaitPoint *wp){
	wp->lock=g_mutex_new();
	wp->cond=g_cond_new();
	wp->time=0;
	wp->wakeup=FALSE;
}
void wait_point_uninit(WaitPoint *wp){
	g_cond_free(wp->cond);
	g_mutex_free(wp->lock);
}

#define wait_point_lock(wp) g_mutex_lock((wp)->lock)
#define wait_point_unlock(wp) g_mutex_unlock((wp)->lock)

void wait_point_wakeup_at(WaitPoint *wp, guint32 t, gboolean dosleep){
	wp->time=t;
	wp->wakeup=TRUE;
	if (dosleep) g_cond_wait(wp->cond,wp->lock);
}


gboolean wait_point_check(WaitPoint *wp, guint32 t){
	gboolean ok=FALSE;
	
	if (wp->wakeup){
		if (TIME_IS_NEWER_THAN(t,wp->time)){
			wp->wakeup=FALSE;
			ok=TRUE;
			
		}
	}
	return ok;
}
#define wait_point_wakeup(wp) g_cond_signal((wp)->cond);

extern void rtp_parse(RtpSession *session, mblk_t *mp, guint32 local_str_ts);


static guint32 guint32_random(){
	return random();
}

void
rtp_session_init (RtpSession * session, gint mode)
{
	memset (session, 0, sizeof (RtpSession));
	session->lock = g_mutex_new ();
	session->rtp.max_rq_size = 100;/* maximum number of packet allowed to be queued */
	session->mode = mode;
	if ((mode == RTP_SESSION_RECVONLY) || (mode == RTP_SESSION_SENDRECV))
	{
		rtp_session_set_flag (session, RTP_SESSION_RECV_SYNC);
		rtp_session_set_flag (session, RTP_SESSION_RECV_NOT_STARTED);
		
	}
	if ((mode == RTP_SESSION_SENDONLY) || (mode == RTP_SESSION_SENDRECV))
	{
		rtp_session_set_flag (session, RTP_SESSION_SEND_NOT_STARTED);
		rtp_session_set_flag (session, RTP_SESSION_SEND_SYNC);
		session->send_ssrc=guint32_random();
		/* set default source description */
		rtp_session_set_source_description(session,"unknown@unknown",NULL,NULL,
				NULL,NULL,"oRTP-" ORTP_VERSION,"This is free sofware (LGPL) !");
	}
	session->telephone_events_pt=-1;	/* not defined a priori */
	rtp_session_set_profile (session, &av_profile); /*the default profile to work with */
	session->recv_pt=0;/* default to something */
	session->send_pt=0;/* default to something */
	session->hw_recv_pt=0;
	qinit(&session->rtp.rq);
	qinit(&session->rtp.tev_rq);
	qinit(&session->contributing_sources);
	/* init signal tables */
	rtp_signal_table_init (&session->on_ssrc_changed, session,"ssrc_changed");
	rtp_signal_table_init (&session->on_payload_type_changed, session,"payload_type_changed");
	rtp_signal_table_init (&session->on_telephone_event, session,"telephone-event");
	rtp_signal_table_init (&session->on_telephone_event_packet, session,"telephone-event_packet");
	rtp_signal_table_init (&session->on_timestamp_jump,session,"timestamp_jump");
	rtp_signal_table_init (&session->on_network_error,session,"network_error");
	wait_point_init(&session->send_wp);
	wait_point_init(&session->recv_wp);
	rtp_session_set_jitter_compensation(session,RTP_DEFAULT_JITTER_TIME);
	rtp_session_enable_adaptive_jitter_compensation(session,FALSE);
	rtp_session_set_time_jump_limit(session,5000);
	session->recv_buf_size = UDP_MAX_SIZE;
}

/**
 *rtp_session_new:
 *@mode: One of the #RtpSessionMode flags.
 *
 *	Creates a new rtp session.
 *  If the session is able to send data (RTP_SESSION_SENDONLY or RTP_SESSION_SENDRECV), then a
 *	random SSRC number is choosed for the outgoing stream.
 *
 *Returns: the newly created rtp session.
**/

RtpSession *
rtp_session_new (gint mode)
{
	RtpSession *session;
	session = g_malloc (sizeof (RtpSession));
	rtp_session_init (session, mode);
	return session;
}

/**
 *rtp_session_set_scheduling_mode:
 *@session: a rtp session.
 *@yesno:	a boolean to indicate the scheduling mode.
 *
 *	Sets the scheduling mode of the rtp session. If @yesno is TRUE, the rtp session is in
 *	the scheduled mode, that means that you can use session_set_select() to block until it's time
 *	to receive or send on this session according to the timestamp passed to the respective functions.
 *  You can also use blocking mode (see rtp_session_set_blocking_mode() ), to simply block within
 *	the receive and send functions.
 *	If @yesno is FALSE, the ortp scheduler will not manage those sessions, meaning that blocking mode 
 *  and the use of session_set_select() for this session are disabled.
 *
**/

void
rtp_session_set_scheduling_mode (RtpSession * session, gint yesno)
{
	if (yesno)
	{
		RtpScheduler *sched;
		sched = ortp_get_scheduler ();
		if (sched != NULL)
		{
			rtp_session_set_flag (session, RTP_SESSION_SCHEDULED);
			session->sched = sched;
			rtp_scheduler_add_session (sched, session);
		}
		else
			g_warning
				("rtp_session_set_scheduling_mode: Cannot use scheduled mode because the "
				 "scheduler is not started. Use ortp_scheduler_init() before.");
	}
	else
		rtp_session_unset_flag (session, RTP_SESSION_SCHEDULED);
}


/**
 *rtp_session_set_blocking_mode:
 *@session: a rtp session
 *@yesno: a boolean
 *
 *	Using this function implies that you previously enabled scheduled mode on the session
 *  (see rtp_session_set_scheduling_mode() ).
 *	rtp_session_set_blocking_mode() defines the behaviour of the rtp_session_recv_with_ts() and 
 *	rtp_session_send_with_ts() functions. If @yesno is TRUE, rtp_session_recv_with_ts()
 *	will block until it is time for the packet to be received, according to the timestamp
 *	passed to the function. After this time, the function returns.
 *	For rtp_session_send_with_ts(), it will block until it is time for the packet to be sent.
 *	If @yesno is FALSE, then the two functions will return immediately.
 *
**/
void
rtp_session_set_blocking_mode (RtpSession * session, gint yesno)
{
	if (yesno)
		rtp_session_set_flag (session, RTP_SESSION_BLOCKING_MODE);
	else
		rtp_session_unset_flag (session, RTP_SESSION_BLOCKING_MODE);
}

/**
 *rtp_session_set_profile:
 *@session: a rtp session
 *@profile: a rtp profile
 *
 *	Set the RTP profile to be used for the session. By default, all session are created by
 *	rtp_session_new() are initialized with the AV profile, as defined in RFC 1890. The application
 *	can set any other profile instead using that function.
 *
 *
**/

void
rtp_session_set_profile (RtpSession * session, RtpProfile * profile)
{
	session->profile = profile;
	rtp_session_telephone_events_supported(session);
}

/**
 *rtp_session_get_profile:
 *@session: a rtp session
 *
 *	Returns current profile.
 *
**/
RtpProfile *rtp_session_get_profile(RtpSession *session){
	return session->profile;
}

/**
 *rtp_session_set_recv_buf_size:
 *@session: a rtp session
 *@bufsize: buffer size in bytes for receiving packets
 *
 *	The default value is 65535 bytes, a big value which is working for everyone.
 *	However if your application can make assumption on the MTU, it can be interesting
 *	to set it to a lower value in order to save memory.
 *
**/
void rtp_session_set_recv_buf_size(RtpSession *session, int bufsize){
	session->recv_buf_size=bufsize;
}

/**
 *rtp_session_signal_connect:
 *@session: 	a rtp session
 *@signal:		the name of a signal
 *@cb:			a #RtpCallback
 *@user_data:	a pointer to any data to be passed when invoking the callback.
 *
 *	This function provides the way for an application to be informed of various events that
 *	may occur during a rtp session. @signal is a string identifying the event, and @cb is 
 *	a user supplied function in charge of processing it. The application can register
 *	several callbacks for the same signal, in the limit of #RTP_CALLBACK_TABLE_MAX_ENTRIES.
 *	Here are name and meaning of supported signals types:
 *
 *	"ssrc_changed" : the SSRC of the incoming stream has changed.
 *
 *	"payload_type_changed" : the payload type of the incoming stream has changed.
 *
 *	"telephone-event_packet" : a telephone-event rtp packet (RFC2833) is received.
 *
 *	"telephone-event" : a telephone event has occured. This is a high-level shortcut for "telephone-event_packet".
 *
 *	"network_error" : a network error happened on a socket. Arguments of the callback functions are
 *						a const char * explaining the error, an int errno error code and the user_data as usual.
 *
 *	"timestamp_jump" : we have received a packet with timestamp in far future compared to last timestamp received.
 *						The farness of far future is set by rtp_sesssion_set_time_jump_limit()
 *
 *	Returns: 0 on success, -EOPNOTSUPP if the signal does not exists, -1 if no more callbacks
 *	can be assigned to the signal type.
**/
int
rtp_session_signal_connect (RtpSession * session, const char *signal,
			    RtpCallback cb, gpointer user_data)
{
	OList *elem;
	for (elem=session->signal_tables;elem!=NULL;elem=o_list_next(elem)){
		RtpSignalTable *s=(RtpSignalTable*) elem->data;
		if (strcmp(signal,s->signal_name)==0){
			return rtp_signal_table_add(s,cb,user_data);
		}
	}
	g_warning ("rtp_session_signal_connect: inexistant signal %s",signal);
	return -1;
}


/**
 *rtp_session_signal_disconnect_by_callback:
 *@session: a rtp session
 *@signal:	a signal name
 *@cb:		a callback function.
 *
 *	Removes callback function @cb to the list of callbacks for signal @signal.
 *
 *Returns: 0 on success, -ENOENT if the callbacks was not found.
**/

int
rtp_session_signal_disconnect_by_callback (RtpSession * session, const gchar *signal,
					   RtpCallback cb)
{
	OList *elem;
	for (elem=session->signal_tables;elem!=NULL;elem=o_list_next(elem)){
		RtpSignalTable *s=(RtpSignalTable*) elem->data;
		if (strcmp(signal,s->signal_name)==0){
			return rtp_signal_table_remove_by_callback(s,cb);
		}
	}
	g_warning ("rtp_session_signal_connect: inexistant signal %s",signal);
	return -1;
}


static int create_and_bind(const char *addr, int port, int *sock_family){
	gint err;
	gint optval = 1;
	int sock=-1;
#ifdef INET6
	char num[8];
	struct addrinfo hints, *res0, *res;
#else
	struct sockaddr_in saddr;
#endif
	
#ifdef INET6
	
	memset(&hints, 0, sizeof(hints));
	hints.ai_family = PF_UNSPEC;
	hints.ai_socktype = SOCK_DGRAM;
	snprintf(num, sizeof(num), "%d",port);
	err = getaddrinfo(addr,num, &hints, &res0);
	if (err!=0) {
		g_warning ("Error: %s", gai_strerror(err));
		return -1;
	}
	
	for (res = res0; res; res = res->ai_next) {
		sock = socket(res->ai_family, res->ai_socktype, 0);
		if (sock < 0)
		  continue;
                
		err = setsockopt (sock, SOL_SOCKET, SO_REUSEADDR,
				  (void*)&optval, sizeof (optval));
		if (err < 0)
		{
			g_warning ("Fail to set rtp address reusable: %s.", getSocketError());
		}

		*sock_family=res->ai_family;
		err = bind (sock, res->ai_addr, res->ai_addrlen);
		if (err != 0)
		  {
		    g_warning ("Fail to bind rtp socket to %s:%i : %s.", addr,port, getSocketError());
		    close_socket (sock);
			sock=-1;
		    continue;
		  }
#ifndef __hpux
		switch (res->ai_family)
		  {
		    case AF_INET:
		      if (IN_MULTICAST(ntohl(((struct sockaddr_in *) res->ai_addr)->sin_addr.s_addr)))
			{
		          struct ip_mreq mreq;
			  mreq.imr_multiaddr.s_addr = ((struct sockaddr_in *) res->ai_addr)->sin_addr.s_addr;
			  mreq.imr_interface.s_addr = INADDR_ANY;
			  err = setsockopt(sock, IPPROTO_IP, IP_ADD_MEMBERSHIP, &mreq, sizeof(mreq));
			  if (err < 0)
			    {
			      g_warning ("Fail to join address group: %s.", getSocketError());
			      close_socket (sock);
					sock=-1;
			      continue;
			    }
			}
		      break;
		    case AF_INET6:
		      if (IN6_IS_ADDR_MULTICAST(&(((struct sockaddr_in6 *) res->ai_addr)->sin6_addr)))
			{
			  struct ipv6_mreq mreq;
			  mreq.ipv6mr_multiaddr = ((struct sockaddr_in6 *) res->ai_addr)->sin6_addr;
			  mreq.ipv6mr_interface = 0;
			  err = setsockopt(sock, IPPROTO_IPV6, IPV6_JOIN_GROUP, &mreq, sizeof(mreq));
			  if (err < 0)
			    {
			      g_warning ("Fail to join address group: %s.", getSocketError());
			      close_socket (sock);
					sock=-1;
			      continue;
			    }
			}
		      break;
		  }
#endif /*hpux*/
		break;
	}
	freeaddrinfo(res0);
#else
	saddr.sin_family = AF_INET;
	*sock_family=AF_INET;
	err = inet_aton (addr, &saddr.sin_addr);
	if (err < 0)
	{
		g_warning ("Error in socket address:%s.", getSocketError());
		return err;
	}
	saddr.sin_port = htons (port);

	sock = socket (PF_INET, SOCK_DGRAM, 0);
	
	if (sock<0) return -1;
	
	err = setsockopt (sock, SOL_SOCKET, SO_REUSEADDR,
			  (void*)&optval, sizeof (optval));
	if (err < 0)
	{
		g_warning ("Fail to set rtp address reusable: %s.",getSocketError());
	}

	err = bind (sock,
		    (struct sockaddr *) &saddr,
		    sizeof (saddr));

	if (err != 0)
	{
		g_warning ("Fail to bind rtp socket to port %i: %s.", port, getSocketError());
		close_socket (sock);
		return -1;
	}
#endif
	if (sock>0) set_non_blocking_socket (sock);
	return sock;
}

static int create_and_bind_random(const char *localip, int *sock_family, int *port){
	int retry;
	int sock;
	for (retry=0;retry<100;retry++)
	{
		int localport;
		do
		{
			localport = (rand () + 5000) & 0xfffe;
		}
		while ((localport < 5000) || (localport > 0xffff));
		sock = create_and_bind(localip, localport, sock_family);
		if (sock>0) {
			*port=localport;
			return sock;
		}
	}
	g_warning("create_and_bind_random: Could not find a random port for %s !",localip);
	return -1;
}

/**
 *rtp_session_set_local_addr:
 *@session:		a rtp session freshly created.
 *@addr:		a local IP address in the xxx.xxx.xxx.xxx form.
 *@port:		a local port or -1 to let oRTP choose the port randomly
 *
 *	Specify the local addr to be use to listen for rtp packets or to send rtp packet from.
 *	In case where the rtp session is send-only, then it is not required to call this function:
 *	when calling rtp_session_set_remote_addr(), if no local address has been set, then the 
 *	default INADRR_ANY (0.0.0.0) IP address with a random port will be used. Calling 
 *	rtp_sesession_set_local_addr() is mandatory when the session is recv-only or duplex.
 *
 *	Returns: 0 on success.
**/

gint
rtp_session_set_local_addr (RtpSession * session, const gchar * addr, gint port)
{
	int sock;
	int sockfamily;
	if (session->rtp.socket>0){
		/* don't rebind, but close before*/
		close_socket(session->rtp.socket);
		if (session->rtcp.socket>0) close_socket(session->rtcp.socket);
		session->rtp.socket=-1;
		session->rtcp.socket=-1;
		session->rtp.loc_port=-1;
	}
	/* try to bind the rtp port */
	if (port>0)
		sock=create_and_bind(addr,port,&sockfamily);
	else
		sock=create_and_bind_random(addr,&sockfamily,&port);
	if (sock>0){
		session->rtp.sockfamily=sockfamily;
		session->rtp.socket=sock;
		session->rtp.loc_port=port;
		/*try to bind rtcp port */
		sock=create_and_bind(addr,port+1,&sockfamily);
		if (sock>0){
			session->rtcp.sockfamily=sockfamily;
			session->rtcp.socket=sock;
		}else{
			g_warning("Could not create and bind rtcp socket.");
		}
		return 0;
	}
	return -1;
}

/**
 *rtp_session_get_local_port:
 *@session:	a rtp session for which rtp_session_set_local_addr() or rtp_session_set_remote_addr() has been called
 *
 *	This function can be useful to retrieve the local port that was randomly choosen by 
 *	rtp_session_set_remote_addr() when rtp_session_set_local_addr() was not called.
 *
 *	Returns: the local port used to listen for rtp packets, -1 if not set.
**/

int rtp_session_get_local_port(const RtpSession *session){
	return (session->rtp.loc_port>0) ? session->rtp.loc_port : -1;
}


/**
 *rtp_session_set_remote_addr:
 *@session:		a rtp session freshly created.
 *@addr:		a local IP address in the xxx.xxx.xxx.xxx form.
 *@port:		a local port.
 *
 *	Sets the remote address of the rtp session, ie the destination address where rtp packet
 *	are sent. If the session is recv-only or duplex, it also sets the origin of incoming RTP 
 *	packets. Rtp packets that don't come from addr:port are discarded.
 *
 *	Returns: 0 on success.
**/

gint
rtp_session_set_remote_addr (RtpSession * session, const gchar * addr, gint port)
{
	gint err;
#ifdef INET6
	struct addrinfo hints, *res0, *res;
	char num[8];
	memset(&hints, 0, sizeof(hints));
	hints.ai_family = PF_UNSPEC;
	hints.ai_socktype = SOCK_DGRAM;
	snprintf(num, sizeof(num), "%d", port);
	err = getaddrinfo(addr, num, &hints, &res0);
	if (err) {
		g_warning ("Error in socket address: %s", gai_strerror(err));
		return -1;
	}
#endif

	if (session->rtp.socket == 0){
		/* the session has not its socket bound, do it */
		g_message ("Setting random local addresses.");
#ifdef INET6
		/* bind to an address type that matches the destination address */
		if (res0->ai_addr->sa_family==AF_INET6)
			err = rtp_session_set_local_addr (session, "::", -1);
		else err=rtp_session_set_local_addr (session, "0.0.0.0", -1);
#else
		err = rtp_session_set_local_addr (session, "0.0.0.0", -1);
#endif
		if (err<0) return -1;
	}

#ifdef INET6
	err=1;
	for (res = res0; res; res = res->ai_next) {
		/* set a destination address that has the same type as the local address */
		if (res->ai_family==session->rtp.sockfamily ) {
			memcpy( &session->rtp.rem_addr, res->ai_addr, res->ai_addrlen);
			session->rtp.rem_addrlen=res->ai_addrlen;
		  	err=0;
		  	break;
		}
	}
	freeaddrinfo(res0);
	if (err) {
		g_warning("Could not set destination for RTP socket to %s:%i.",addr,port);
		return -1;
	}
	
	memset(&hints, 0, sizeof(hints));
	hints.ai_family = PF_UNSPEC;
	hints.ai_socktype = SOCK_DGRAM;
	snprintf(num, sizeof(num), "%d", (port + 1));
	err = getaddrinfo(addr, num, &hints, &res0);
	if (err) {
		g_warning ("Error: %s", gai_strerror(err));
		return err;
	}
	err=1;
	for (res = res0; res; res = res->ai_next) {
		/* set a destination address that has the same type as the local address */
		if (res->ai_family==session->rtp.sockfamily ) {
		  	err=0;
		  	memcpy( &session->rtcp.rem_addr, res->ai_addr, res->ai_addrlen);
			session->rtcp.rem_addrlen=res->ai_addrlen;
		  	break;
		}
	}
	freeaddrinfo(res0);
	if (err) {
		g_warning("Could not set destination for RCTP socket to %s:%i.",addr,port+1);
		return -1;
	}
#else
	session->rtp.rem_addrlen=sizeof(session->rtp.rem_addr);
	session->rtp.rem_addr.sin_family = AF_INET;

	err = inet_aton (addr, &session->rtp.rem_addr.sin_addr);
	if (err < 0)
	{
		g_warning ("Error in socket address:%s.", getSocketError());
		return err;
	}
	session->rtp.rem_addr.sin_port = htons (port);

	memcpy (&session->rtcp.rem_addr, &session->rtp.rem_addr,
		sizeof (struct sockaddr_in));
	session->rtcp.rem_addr.sin_port = htons (port + 1);
	session->rtcp.rem_addrlen=sizeof(session->rtp.rem_addr);
#endif
#ifndef NOCONNECT
	if (session->mode == RTP_SESSION_SENDONLY)
	{
		err = connect (session->rtp.socket,
			       (struct sockaddr *) &session->rtp.rem_addr,
#ifdef INET6
			       session->rtp.rem_addrlen);
#else
			       sizeof (struct sockaddr_in));
#endif
		if (err != 0)
		{
			g_message ("Can't connect rtp socket: %s.",getSocketError());
			return err;
		}
		err = connect (session->rtcp.socket,
			       (struct sockaddr *) &session->rtcp.rem_addr,
#ifdef INET6
			       session->rtcp.rem_addrlen);
#else
			       sizeof (struct sockaddr_in));
#endif
		if (err != 0)
		{
			g_message ("Can't connect rtp socket: %s.",getSocketError());
			return err;
		}
	}
#endif
	return 0;
}

void rtp_session_set_sockets(RtpSession *session, gint rtpfd, gint rtcpfd)
{
	if (rtpfd>0) set_non_blocking_socket(rtpfd);
	if (rtcpfd>0) set_non_blocking_socket(rtcpfd);
	session->rtp.socket=rtpfd;
	session->rtcp.socket=rtcpfd;
	session->flags|=RTP_SESSION_USING_EXT_SOCKETS;
}

/**
 *rtp_session_flush_sockets:
 *@session: a rtp session
 *
 * Flushes the sockets for all pending incoming packets.
 * This can be usefull if you did not listen to the stream for a while
 * and wishes to start to receive again. During the time no receive is made
 * packets get bufferised into the internal kernel socket structure.
 *
**/
void rtp_session_flush_sockets(RtpSession *session){
	char trash[4096];
#ifdef INET6
	struct sockaddr_storage from;
#else
	struct sockaddr from;
#endif
	socklen_t fromlen=sizeof(from);
	if (session->rtp.socket>0){
		while (recvfrom(session->rtp.socket,(void*)trash,sizeof(trash),0,(struct sockaddr *)&from,&fromlen)>0){};
	}
	if (session->rtcp.socket>0){
		while (recvfrom(session->rtcp.socket,(void*)trash,sizeof(trash),0,(struct sockaddr*)&from,&fromlen)>0){};
	}
}

/**
 *rtp_session_set_seq_number:
 *@session:		a rtp session freshly created.
 *@addr:			a 16 bit unsigned number.
 *
 * sets the initial sequence number of a sending session.
 *
**/
void rtp_session_set_seq_number(RtpSession *session, guint16 seq){
	session->rtp.snd_seq=seq;
}


guint16 rtp_session_get_seq_number(RtpSession *session){
	return session->rtp.snd_seq;
}


#ifdef USE_SENDMSG 
#define MAX_IOV 10
static gint rtp_sendmsg(int sock,mblk_t *m, struct sockaddr *rem_addr, int addr_len){
	int error;
	struct msghdr msg;
	struct iovec iov[MAX_IOV];
	int iovlen;
	for(iovlen=0; iovlen<MAX_IOV && m!=NULL; m=m->b_cont,iovlen++){
		iov[iovlen].iov_base=m->b_rptr;
		iov[iovlen].iov_len=m->b_wptr-m->b_rptr;
	}
	msg.msg_name=(void*)rem_addr;
	msg.msg_namelen=addr_len;
	msg.msg_iov=&iov[0];
	msg.msg_iovlen=iovlen;
	msg.msg_control=NULL;
	msg.msg_controllen=0;
	msg.msg_flags=0;
	
	error=sendmsg(sock,&msg,0);
	return error;
}
#endif	

static gint
ortp_rtp_send (RtpSession * session, mblk_t * m)
{
	gint error;
	int i;
	rtp_header_t *hdr;

	hdr = (rtp_header_t *) m->b_rptr;
	/* perform host to network conversions */
	hdr->ssrc = htonl (hdr->ssrc);
	hdr->timestamp = htonl (hdr->timestamp);
	hdr->seq_number = htons (hdr->seq_number);
	for (i = 0; i < hdr->cc; i++)
		hdr->csrc[i] = htonl (hdr->csrc[i]);
	
#ifdef USE_SENDMSG
	if (session->flags & RTP_SESSION_USING_EXT_SOCKETS){
		error=rtp_sendmsg(session->rtp.socket,m,(struct sockaddr *)NULL,0);
	}else {
		error=rtp_sendmsg(session->rtp.socket,m,(struct sockaddr *) &session->rtp.rem_addr,
		session->rtp.rem_addrlen);
	}
#else
	if (m->b_cont!=NULL){
		mblk_t *newm=msgpullup(m,-1);
		freemsg(m);
		m=newm;
	}
	if (session->flags & RTP_SESSION_USING_EXT_SOCKETS){
		error=send(session->rtp.socket, m->b_rptr, (m->b_wptr - m->b_rptr),0);
	}else error = sendto (session->rtp.socket, m->b_rptr,
		(m->b_wptr - m->b_rptr), 0,
		(struct sockaddr *) &session->rtp.rem_addr,
		session->rtp.rem_addrlen);
#endif
	if (error < 0){
		if (session->on_network_error.count>0){
			rtp_signal_table_emit3(&session->on_network_error,(gpointer)"Error sending RTP packet",INT_TO_POINTER(getSocketErrorCode()));
		}else g_warning ("Error sending rtp packet: %s ; socket=%i", getSocketError(), session->rtp.socket);
	}
	freemsg (m);
	return error;
}

gint
ortp_rtcp_send (RtpSession * session, mblk_t * m)
{
	gint error=0;
	gboolean using_ext_socket=(session->flags & RTP_SESSION_USING_EXT_SOCKETS)!=0;
	if ( (using_ext_socket && session->rtcp.socket>0 ) || session->rtcp.rem_addrlen>0){
		
#ifndef USE_SENDMSG
		if (m->b_cont!=NULL){
			mblk_t *newm=msgpullup(m,-1);
			freemsg(m);
			m=newm;
		}
#endif
		if (using_ext_socket &&  session->rtcp.socket>0 ){
#ifdef USE_SENDMSG
			error=rtp_sendmsg(session->rtcp.socket,m,(struct sockaddr *)NULL,0);
#else
			error=send(session->rtcp.socket, m->b_rptr, (m->b_wptr - m->b_rptr),0);
#endif
		}else {
#ifdef USE_SENDMSG
			error=rtp_sendmsg(session->rtcp.socket,m,(struct sockaddr *) &session->rtcp.rem_addr,
			session->rtcp.rem_addrlen);
#else
			error = sendto (session->rtcp.socket, m->b_rptr,
			(m->b_wptr - m->b_rptr), 0,
			(struct sockaddr *) &session->rtcp.rem_addr,
			session->rtcp.rem_addrlen);
#endif
		}
	
		if (error < 0){
			if (session->on_network_error.count>0){
				rtp_signal_table_emit3(&session->on_network_error,(gpointer)"Error sending RTCP packet",INT_TO_POINTER(getSocketErrorCode()));
			}else g_warning ("Error sending rtcp packet: %s ; socket=%i", getSocketError(), session->rtcp.socket);
		}
	}else g_warning("Cannot send rtcp report because I don't know the remote address.");
	freemsg (m);
	return error;
}


/**
 *rtp_session_set_ssrc:
 *@session: a rtp session.
 *@ssrc: an unsigned 32bit integer representing the synchronisation source identifier (SSRC).
 *
 *	Sets the SSRC for the outgoing stream.
 *  If not done, a random ssrc is used.
 *
**/
void
rtp_session_set_ssrc (RtpSession * session, guint32 ssrc)
{
	session->send_ssrc = ssrc;
}

/* this function initialize all session parameter's that depend on the payload type */
static void payload_type_changed(RtpSession *session, PayloadType *pt){
	jitter_control_set_payload(&session->rtp.jittctl,pt);
	session->rtp.rtcp_report_snt_interval=RTCP_DEFAULT_REPORT_INTERVAL*pt->clock_rate;
	rtp_session_set_time_jump_limit(session,session->rtp.time_jump);
}

void rtp_session_update_payload_type(RtpSession *session, int paytype){
	/* check if we support this payload type */
	PayloadType *pt=rtp_profile_get_payload(session->profile,paytype);
	session->hw_recv_pt=paytype;
	if (pt!=0){
		g_message ("payload type changed to %i(%s) !",
				 paytype,pt->mime_type);
		payload_type_changed(session,pt);
	}else{
		g_warning("Receiving packet with unknown payload type %i.",paytype);
	}
}
/**
 *rtp_session_set_send_payload_type:
 *@session: a rtp session
 *@paytype: the payload type
 *
 *	Sets the payload type of the rtp session. It decides of the payload types written in the
 *	of the rtp header for the outgoing stream, if the session is SENDRECV or SENDONLY.
 *	For payload type in incoming packets, the application can be informed by registering
 *	for the "payload_type_changed" signal, so that it can make the necessary changes
 *	on the downstream decoder that deals with the payload of the packets.
 *
 *Returns: 0 on success, -1 if the payload is not defined.
**/

int
rtp_session_set_send_payload_type (RtpSession * session, int paytype)
{
	session->send_pt=paytype;
	return 0;
}

/**
 *rtp_session_get_send_payload_type:
 *@session: a rtp session
 *
 *	Returns: the payload type currently used in outgoing rtp packets
**/
int rtp_session_get_send_payload_type(const RtpSession *session){
	return session->send_pt;
}

/**
 *rtp_session_set_recv_payload_type:
 *@session: a rtp session
 *@paytype: the payload type
 *
 *	Sets the expected payload type for incoming packets.
 *	If the actual payload type in incoming packets is different that this expected payload type, thus
 *	the "payload_type_changed" signal is emitted.
 *
 *Returns: 0 on success, -1 if the payload is not defined.
**/

int
rtp_session_set_recv_payload_type (RtpSession * session, int paytype)
{
	PayloadType *pt;
	session->recv_pt=paytype;
	session->hw_recv_pt=paytype;
	pt=rtp_profile_get_payload(session->profile,paytype);
	if (pt!=NULL){
		payload_type_changed(session,pt);
	}
	return 0;
}

/**
 *rtp_session_get_recv_payload_type:
 *@session: a rtp session
 *
 *	Returns: the payload type currently used in incoming rtp packets
**/
int rtp_session_get_recv_payload_type(const RtpSession *session){
	return session->recv_pt;
}

/**
 *rtp_session_set_payload_type:
 *@session: a rtp session
 *@paytype: the payload type
 *
 *	Sets the expected payload type for incoming packets and payload type to be used for outgoing packets.
 *	If the actual payload type in incoming packets is different that this expected payload type, thus
 *	the "payload_type_changed" signal is emitted.
 *
 *Returns: 0 on success, -1 if the payload is not defined.
**/
int rtp_session_set_payload_type(RtpSession *session, int pt){
	if (rtp_session_set_send_payload_type(session,pt)<0) return -1;
	if (rtp_session_set_recv_payload_type(session,pt)<0) return -1;
	return 0;
}


/**
 *rtp_session_create_packet:
 *@session:		a rtp session.
 *@header_size:	the rtp header size. For standart size (without extensions), it is #RTP_FIXED_HEADER_SIZE
 *@payload		:data to be copied into the rtp packet.
 *@payload_size	: size of data carried by the rtp packet.
 *
 *	Allocates a new rtp packet. In the header, ssrc and payload_type according to the session's
 *	context. Timestamp and seq number are not set, there will be set when the packet is going to be
 *	sent with rtp_session_sendm_with_ts().
 *	If payload_size is zero, thus an empty packet (just a RTP header) is returned.
 *
 *Returns: a rtp packet in a mblk_t (message block) structure.
**/
mblk_t * rtp_session_create_packet(RtpSession *session,gint header_size, const char *payload, gint payload_size)
{
	mblk_t *mp;
	gint msglen=header_size+payload_size;
	rtp_header_t *rtp;
	
	mp=allocb(msglen,BPRI_MED);
	rtp=(rtp_header_t*)mp->b_rptr;
	rtp->version = 2;
	rtp->padbit = 0;
	rtp->extbit = 0;
	rtp->markbit= 0;
	rtp->cc = 0;
	rtp->paytype = session->send_pt;
	rtp->ssrc = session->send_ssrc;
	rtp->timestamp = 0;	/* set later, when packet is sended */
	rtp->seq_number = 0; /*set later, when packet is sended */
	/*copy the payload, if any */
	mp->b_wptr+=header_size;
	if (payload_size){
		memcpy(mp->b_wptr,payload,payload_size);
		mp->b_wptr+=payload_size;
	}
	return mp;
}

/**
 *rtp_session_create_packet_with_data:
 *@session:		a rtp session.
 *@payload		: the data to be sent with this packet
 *@payload_size	: size of data
 *@freefn		: a function that will be called when the payload buffer is no more needed.
 *
 *	Creates a new rtp packet using the given payload buffer (no copy). The header will be allocated separetely.
 *  In the header, ssrc and payload_type according to the session's
 *	context. Timestamp and seq number are not set, there will be set when the packet is going to be
 *	sent with rtp_session_sendm_with_ts().
 *	oRTP will send this packet using libc's sendmsg() (if this function is availlable!) so that there will be no
 *	packet concatenation involving copies to be done in user-space.
 *  @freefn can be NULL, in that case payload will be kept untouched.
 *
 *Returns: a rtp packet in a mblk_t (message block) structure.
**/

mblk_t * rtp_session_create_packet_with_data(RtpSession *session, char *payload, gint payload_size, void (*freefn)(void*))
{
	mblk_t *mp,*mpayload;
	gint header_size=RTP_FIXED_HEADER_SIZE; /* revisit when support for csrc is done */
	rtp_header_t *rtp;
	
	mp=allocb(header_size,BPRI_MED);
	rtp=(rtp_header_t*)mp->b_rptr;
	rtp->version = 2;
	rtp->padbit = 0;
	rtp->extbit = 0;
	rtp->markbit= 0;
	rtp->cc = 0;
	rtp->paytype = session->send_pt;
	rtp->ssrc = session->send_ssrc;
	rtp->timestamp = 0;	/* set later, when packet is sended */
	rtp->seq_number = 0; /*set later, when packet is sended */
	mp->b_wptr+=header_size;
	/* create a mblk_t around the user supplied payload buffer */
	mpayload=allocb_with_buf(payload,payload_size,BPRI_MED,freefn);
	mpayload->b_wptr+=payload_size;
	/* link it with the header */
	mp->b_cont=mpayload;
	return mp;
}


/**
 *rtp_session_create_packet_in_place:
 *@session:		a rtp session.
 *@buffer:	a buffer that contains first just enough place to write a RTP header, then the data to send.
 *@size		: the size of the buffer
 *@freefn : a function that will be called once the buffer is no more needed (the data has been sent).
 *
 *	Creates a new rtp packet using the buffer given in arguments (no copy). 
 *  In the header, ssrc and payload_type according to the session's
 *	context. Timestamp and seq number are not set, there will be set when the packet is going to be
 *	sent with rtp_session_sendm_with_ts().
 *  @freefn can be NULL, in that case payload will be kept untouched.
 *
 *Returns: a rtp packet in a mblk_t (message block) structure.
**/
mblk_t * rtp_session_create_packet_in_place(RtpSession *session,char *buffer, gint size, void (*freefn)(void*) )
{
	mblk_t *mp;
	rtp_header_t *rtp;
	
	mp=allocb_with_buf(buffer,size,BPRI_MED,freefn);

	rtp=(rtp_header_t*)mp->b_rptr;
	rtp->version = 2;
	rtp->padbit = 0;
	rtp->extbit = 0;
	rtp->markbit= 0;
	rtp->cc = 0;
	rtp->paytype = session->send_pt;
	rtp->ssrc = session->send_ssrc;
	rtp->timestamp = 0;	/* set later, when packet is sended */
	rtp->seq_number = 0; /*set later, when packet is sended */
	return mp;
}


/**
 *rtp_session_sendm_with_ts:
 *@session	: a rtp session.
 *@mp		:	a rtp packet presented as a mblk_t.
 *@timestamp:	the timestamp of the data to be sent. Refer to the rfc to know what it is.
 *
 *	Send the rtp datagram @mp to the destination set by rtp_session_set_remote_addr() 
 *	with timestamp @timestamp. For audio data, the timestamp is the number
 *	of the first sample resulting of the data transmitted. See rfc1889 for details.
 *  The packet (@mp) is freed once it is sended.
 *
 *Returns: the number of bytes sent over the network.
**/
gint
rtp_session_sendm_with_ts (RtpSession * session, mblk_t *mp, guint32 timestamp)
{
	rtp_header_t *rtp;
	guint32 packet_time;
	gint error = 0;
	gint packsize;
	RtpScheduler *sched=session->sched;
	RtpStream *stream=&session->rtp;

	if (session->flags & RTP_SESSION_SEND_NOT_STARTED)
	{
		session->rtp.snd_ts_offset = timestamp;
		if (session->flags & RTP_SESSION_SCHEDULED)
		{
			session->rtp.snd_time_offset = sched->time_;
		}
		rtp_session_unset_flag (session,RTP_SESSION_SEND_NOT_STARTED);
	}
	/* if we are in blocking mode, then suspend the process until the scheduler it's time to send  the
	 * next packet */
	/* if the timestamp of the packet queued is older than current time, then you we must
	 * not block */
	if (session->flags & RTP_SESSION_SCHEDULED)
	{
		packet_time =
			rtp_session_ts_to_time (session,
				     timestamp -
				     session->rtp.snd_ts_offset) +
					session->rtp.snd_time_offset;
		/*g_message("rtp_session_send_with_ts: packet_time=%i time=%i",packet_time,sched->time_);*/
		wait_point_lock(&session->send_wp);
		if (TIME_IS_STRICTLY_NEWER_THAN (packet_time, sched->time_))
		{
			wait_point_wakeup_at(&session->send_wp,packet_time,(session->flags & RTP_SESSION_BLOCKING_MODE)!=0);	
			session_set_clr(&sched->w_sessions,session);	/* the session has written */
		}
		else session_set_set(&sched->w_sessions,session);	/*to indicate select to return immediately */
		wait_point_unlock(&session->send_wp);
	}
	

	rtp=(rtp_header_t*)mp->b_rptr;
	
	packsize = msgdsize(mp) ;
	rtp_session_lock (session);
	
	/* set a seq number */
	rtp->seq_number=session->rtp.snd_seq;
	rtp->timestamp=timestamp;
	session->rtp.snd_seq++;
	session->rtp.snd_last_ts = timestamp;


	ortp_global_stats.sent += packsize;
	stream->stats.sent += packsize;
	ortp_global_stats.packet_sent++;
	stream->stats.packet_sent++;

	error = ortp_rtp_send (session, mp);
	rtp_session_rtcp_process(session);
	rtp_session_unlock (session);
	
	return error;
}


/**
 *rtp_session_send_with_ts:
 *@session: a rtp session.
 *@buffer:	a buffer containing the data to be sent in a rtp packet.
 *@len:		the length of the data buffer, in bytes.
 *@userts:	the timestamp of the data to be sent. Refer to the rfc to know what it is.
 *
 *	Send a rtp datagram to the destination set by rtp_session_set_remote_addr() containing
 *	the data from @buffer with timestamp @userts. This is a high level function that uses
 *	rtp_session_create_packet() and rtp_session_sendm_with_ts() to send the data.
 *
 *
 *Returns: the number of bytes sent over the network.
**/
gint
rtp_session_send_with_ts (RtpSession * session, const gchar * buffer, gint len,
			  guint32 userts)
{
	mblk_t *m;
	int err;
#ifdef USE_SENDMSG
	m=rtp_session_create_packet_with_data(session,(gchar*)buffer,len,NULL);
#else
	m = rtp_session_create_packet(session,RTP_FIXED_HEADER_SIZE,(gchar*)buffer,len);
#endif
	err=rtp_session_sendm_with_ts(session,m,userts);
	return err;
}


static gint
rtp_recv (RtpSession * session, guint32 user_ts)
{
	gint error;
	struct sockaddr remaddr;
	socklen_t addrlen = sizeof (remaddr);
	char *p;
	mblk_t *mp;
	RtpStream *stream=&session->rtp;

	if (session->rtp.socket<1) return -1;  /*session has no sockets for the moment*/
	

	while (1)
	{
		int bufsz;
		if (session->rtp.cached_mp==NULL)
			 session->rtp.cached_mp = allocb (session->recv_buf_size, 0);
		mp=session->rtp.cached_mp;
		bufsz=mp->b_datap->db_lim - mp->b_datap->db_base;
		if (session->flags & RTP_SESSION_USING_EXT_SOCKETS){
			error=recv(session->rtp.socket,mp->b_wptr,bufsz,0);
		}else error = recvfrom (session->rtp.socket, mp->b_wptr,
				  bufsz, 0,
				  (struct sockaddr *) &remaddr,
				  &addrlen);
		if (error > 0)
		{
			if (error<RTP_FIXED_HEADER_SIZE){
				g_warning("Packet too small to be a rtp packet (%i)!",error);
				stream->stats.bad++;
				ortp_global_stats.bad++;
				/* don't free, it will be reused next time */
			}else{
				/* resize the memory allocated to fit the udp message */

				p = g_realloc (mp->b_wptr, error);
				if (p != mp->b_wptr)
					ortp_debug("The recv area has moved during reallocation.");
				mp->b_datap->db_base = mp->b_rptr =
					mp->b_wptr = p;
				mp->b_wptr += error;
				mp->b_datap->db_lim = mp->b_wptr;
				/* then parse the message and put on queue */
				rtp_parse (session, mp, user_ts + session->rtp.hwrcv_diff_ts);
				session->rtp.cached_mp=NULL;
			}
		}
		else
		{
			if (error == 0)
			{
				g_warning
					("rtp_recv: strange... recv() returned zero.");
			}
			else if (errno!=EWOULDBLOCK && errno!=EAGAIN)
			{
				if (session->on_network_error.count>0){
					rtp_signal_table_emit3(&session->on_network_error,(gpointer)"Error receiving RTP packet",INT_TO_POINTER(getSocketErrorCode()));
				}else g_warning("Error receiving RTP packet: %s.",getSocketError());
			}
			/* don't free the cached_mp, it will be reused next time */
			return -1;	/* avoids an infinite loop ! */
		}
	}
	return error;
}

extern void rtcp_parse(RtpSession *session, mblk_t *mp);

static gint
rtcp_recv (RtpSession * session)
{
	gint error;
	struct sockaddr remaddr;
	socklen_t addrlen=0;
	char *p;
	mblk_t *mp;
	

	if (session->rtcp.socket<1) return -1;  /*session has no rtcp sockets for the moment*/
	

	while (1)
	{
		if (session->rtcp.cached_mp==NULL)
			 session->rtcp.cached_mp = allocb (RTCP_MAX_RECV_BUFSIZE, 0);
		
		mp=session->rtcp.cached_mp;
		if (session->flags & RTP_SESSION_USING_EXT_SOCKETS){
			error=recv(session->rtcp.socket,mp->b_wptr,RTCP_MAX_RECV_BUFSIZE,0);
		}else {
			addrlen=sizeof (remaddr);
			error=recvfrom (session->rtcp.socket, mp->b_wptr,
				  RTCP_MAX_RECV_BUFSIZE, 0,
				  (struct sockaddr *) &remaddr,
				  &addrlen);
		}
		if (error > 0)
		{
			/* resize the memory allocated to fit the udp message */
	
			p = g_realloc (mp->b_wptr, error);
			if (p != mp->b_wptr)
				ortp_debug("The recv area has moved during reallocation.");
			mp->b_datap->db_base = mp->b_rptr =
				mp->b_wptr = p;
			mp->b_wptr += error;
			mp->b_datap->db_lim = mp->b_wptr;
			/* then parse the message */
			rtcp_parse (session, mp);
			freemsg(mp);
			session->rtcp.cached_mp=NULL;
			if (addrlen>0){
				/* store the sender rtcp address to send him receiver reports */
				memcpy(&session->rtcp.rem_addr,&remaddr,addrlen);
			}
		}
		else
		{
			if (error == 0)
			{
				g_warning
					("rtcp_recv: strange... recv() returned zero.");
			}
			else if (errno!=EWOULDBLOCK && errno!=EAGAIN)
			{
				if (session->on_network_error.count>0){
					rtp_signal_table_emit3(&session->on_network_error,(gpointer)"Error receiving RTCP packet",INT_TO_POINTER(getSocketErrorCode()));
				}else g_warning("Error receiving RTCP packet: %s.",getSocketError());
			}
			/* don't free the cached_mp, it will be reused next time */
			return -1;	/* avoids an infinite loop ! */
		}
	}
	return error;
}


static void payload_type_changed_notify(RtpSession *session, int paytype){
	rtp_signal_table_emit (&session->on_payload_type_changed);	
	session->recv_pt = paytype;
}


/**
 *rtp_session_recvm_with_ts:
 *@session: a rtp session.
 *@user_ts:	a timestamp.
 *
 *	Try to get a rtp packet presented as a mblk_t structure from the rtp session.
 *	The @user_ts parameter is relative to the first timestamp of the incoming stream. In other
 *	words, the application does not have to know the first timestamp of the stream, it can
 *	simply call for the first time this function with @user_ts=0, and then incrementing it
 *	as it want. The RtpSession takes care of synchronisation between the stream timestamp
 *	and the user timestamp given here.
 *
 *Returns: a rtp packet presented as a mblk_t.
**/

mblk_t *
rtp_session_recvm_with_ts (RtpSession * session, guint32 user_ts)
{
	mblk_t *mp = NULL;
	rtp_header_t *rtp;
	guint32 ts;
	guint32 packet_time;
	RtpScheduler *sched=session->sched;
	RtpStream *stream=&session->rtp;
	gint rejected=0;

	/* if we are scheduled, remember the scheduler time at which the application has
	 * asked for its first timestamp */

	if (session->flags & RTP_SESSION_RECV_NOT_STARTED)
	{
		
		session->rtp.rcv_query_ts_offset = user_ts;
		if (session->flags & RTP_SESSION_SCHEDULED)
		{
			session->rtp.rcv_time_offset = sched->time_;
			//g_message("setting snd_time_offset=%i",session->rtp.snd_time_offset);
		}
		rtp_session_unset_flag (session,RTP_SESSION_RECV_NOT_STARTED);
	}
	session->rtp.rcv_last_app_ts = user_ts;
	rtp_recv (session, user_ts);
	rtcp_recv(session);
	/* check for telephone event first */
	/* first lock the session */
	rtp_session_lock (session);
	mp=getq(&session->rtp.tev_rq);
	if (mp!=NULL){
		rtp_signal_table_emit2(&session->on_telephone_event_packet,(gpointer)mp);
		if (session->on_telephone_event.count>0){
			rtp_session_check_telephone_events(session,mp);
		}
		freemsg(mp);
		mp=NULL;
	}
	
	/* then now try to return a media packet, if possible */
	/* first condition: if the session is starting, don't return anything
	 * until the queue size reaches jitt_comp */
	
	if (session->flags & RTP_SESSION_RECV_SYNC)
	{
		rtp_header_t *oldest, *newest;
		queue_t *q = &session->rtp.rq;
		if (qempty(q))
		{
			ortp_debug ("Queue is empty.");
			goto end;
		}
		oldest = (rtp_header_t *) qfirst(q)->b_rptr;
		newest = (rtp_header_t *) qlast(q)->b_rptr;
		if ((guint32) (newest->timestamp - oldest->timestamp) <
		    session->rtp.jittctl.jitt_comp_ts)
		{
			ortp_debug("Not enough packet bufferised.");
			goto end;
		}
		/* enough packet bufferised */
		mp = getq (&session->rtp.rq);
		rtp = (rtp_header_t *) mp->b_rptr;
		session->rtp.rcv_ts_offset = rtp->timestamp;
		/* remember the timestamp offset between the stream timestamp (random)
		 * and the user timestamp, that very often starts at zero */
		session->rtp.rcv_diff_ts = rtp->timestamp - user_ts;
		/* remember the difference between the last received on the socket timestamp and the user timestamp */
		session->rtp.hwrcv_diff_ts=session->rtp.rcv_diff_ts + session->rtp.jittctl.jitt_comp_ts;
		session->rtp.rcv_last_ret_ts = user_ts;	/* just to have an init value */
		session->rtp.rcv_last_ts = rtp->timestamp;
		session->recv_ssrc = rtp->ssrc;
		/* delete the recv synchronisation flag */
		rtp_session_unset_flag (session, RTP_SESSION_RECV_SYNC);
		ortp_debug("Returning FIRST packet with ts=%i, hwrcv_diff_ts=%i, rcv_diff_ts=%i", rtp->timestamp,
					session->rtp.hwrcv_diff_ts,session->rtp.rcv_diff_ts);

		goto end;
	}
	/* else this the normal case */
	/*calculate the stream timestamp from the user timestamp */
	ts = user_ts + session->rtp.rcv_diff_ts;
	session->rtp.rcv_last_ts = ts;
	mp = rtp_getq (&session->rtp.rq, ts,&rejected);
	
	stream->stats.skipped+=rejected;
	ortp_global_stats.skipped+=rejected;

	/* perhaps we can now make some checks to see if a resynchronization is needed */
	/* TODO */
	goto end;

      end:
	if (mp != NULL)
	{
		int msgsize = msgdsize (mp);	/* evaluate how much bytes (including header) is received by app */
		guint32 packet_ts;
		ortp_global_stats.recv += msgsize;
		stream->stats.recv += msgsize;
		rtp = (rtp_header_t *) mp->b_rptr;
		packet_ts=rtp->timestamp;
		ortp_debug("Returning mp with ts=%i", packet_ts);
		/* check for payload type changes */
		if (session->recv_pt != rtp->paytype)
		{
			payload_type_changed_notify(session, rtp->paytype);
		}
		/* patch the packet so that it has a timestamp compensated by the 
		adaptive jitter buffer mechanism */
		if (session->rtp.jittctl.adaptive){
			rtp->timestamp-=session->rtp.jittctl.corrective_slide;
			/*printf("Returned packet has timestamp %u, with clock slide compensated it is %u\n",packet_ts,rtp->timestamp);*/
		}
	}
	else
	{
		ortp_debug ("No mp for timestamp queried");
		stream->stats.unavaillable++;
		ortp_global_stats.unavaillable++;
	}
	rtp_session_rtcp_process(session);
	rtp_session_unlock (session);
	
	if (session->flags & RTP_SESSION_SCHEDULED)
	{
		/* if we are in blocking mode, then suspend the calling process until timestamp
		 * wanted expires */
		/* but we must not block the process if the timestamp wanted by the application is older
		 * than current time */
		packet_time =
			rtp_session_ts_to_time (session,
				     user_ts -
				     session->rtp.rcv_query_ts_offset) +
			session->rtp.rcv_time_offset;
		ortp_debug ("rtp_session_recvm_with_ts: packet_time=%i, time=%i",packet_time, sched->time_);
		wait_point_lock(&session->recv_wp);
		if (TIME_IS_STRICTLY_NEWER_THAN (packet_time, sched->time_))
		{
			wait_point_wakeup_at(&session->recv_wp,packet_time, (session->flags & RTP_SESSION_BLOCKING_MODE)!=0);
			session_set_clr(&sched->r_sessions,session);
		}
		else session_set_set(&sched->r_sessions,session);	/*to unblock _select() immediately */
		wait_point_unlock(&session->recv_wp);
	}
	return mp;
}


gint msg_to_buf (mblk_t * mp, char *buffer, gint len)
{
	gint rlen = len;
	mblk_t *m, *mprev;
	gint mlen;
	m = mp->b_cont;
	mprev = mp;
	while (m != NULL)
	{
		mlen = m->b_wptr - m->b_rptr;
		if (mlen <= rlen)
		{
			mblk_t *consumed = m;
			memcpy (buffer, m->b_rptr, mlen);
			/* go to next mblk_t */
			mprev->b_cont = m->b_cont;
			m = m->b_cont;
			consumed->b_cont = NULL;
			freeb (consumed);
			buffer += mlen;
			rlen -= mlen;
		}
		else
		{		/*if mlen>rlen */
			memcpy (buffer, m->b_rptr, rlen);
			m->b_rptr += rlen;
			return len;
		}
	}
	return len - rlen;
}

/**
 *rtp_session_recv_with_ts:
 *@session: a rtp session.
 *@buffer:	a user supplied buffer to write the data.
 *@len:		the length in bytes of the user supplied buffer.
 *@time:	the timestamp wanted.
 *@have_more: the address of an integer to indicate if more data is availlable for the given timestamp.
 *
 *	Tries to read the bytes of the incoming rtp stream related to timestamp @time. In case 
 *	where the user supplied buffer @buffer is not large enough to get all the data 
 *	related to timestamp @time, then *( @have_more) is set to 1 to indicate that the application
 *	should recall the function with the same timestamp to get more data.
 *	
 *  When the rtp session is scheduled (see rtp_session_set_scheduling_mode() ), and the 
 *	blocking mode is on (see rtp_session_set_blocking_mode() ), then the calling thread
 *	is suspended until the timestamp given as argument expires, whatever a received packet 
 *	fits the query or not.
 *
 *	Important note: it is clear that the application cannot know the timestamp of the first
 *	packet of the incoming stream, because it can be random. The @time timestamp given to the
 *	function is used relatively to first timestamp of the stream. In simple words, 0 is a good
 *	value to start calling this function.
 *
 *	This function internally calls rtp_session_recvm_with_ts() to get a rtp packet. The content
 *	of this packet is then copied into the user supplied buffer in an intelligent manner:
 *	the function takes care of the size of the supplied buffer and the timestamp given in  
 *	argument. Using this function it is possible to read continous audio data (e.g. pcma,pcmu...)
 *	with for example a standart buffer of size of 160 with timestamp incrementing by 160 while the incoming
 *	stream has a different packet size.
 *
 *Returns: if a packet was availlable with the corresponding timestamp supplied in argument 
 *	then the number of bytes written in the user supplied buffer is returned. If no packets
 *	are availlable, either because the sender has not started to send the stream, or either
 *	because silence packet are not transmitted, or either because the packet was lost during
 *	network transport, then the function returns zero.
**/
gint rtp_session_recv_with_ts (RtpSession * session, gchar * buffer,
			       gint len, guint32 time, gint * have_more)
{
	mblk_t *mp;
	gint rlen = len;
	gint wlen, mlen;
	guint32 ts_int = 0;	/*the length of the data returned in the user supplied buffer, in TIMESTAMP UNIT */
	PayloadType *payload;
	RtpStream *stream=&session->rtp;

	*have_more = 0;

	mp = rtp_session_recvm_with_ts (session, time);
	payload =rtp_profile_get_payload (session->profile,
					 session->recv_pt);
	if (payload==NULL){
		g_warning("rtp_session_recv_with_ts: unable to recv an unsupported payload.");
		if (mp!=NULL) freemsg(mp);
		return -1;
	}
	if (!(session->flags & RTP_SESSION_RECV_SYNC))
	{
		//ortp_debug("time=%i   rcv_last_ret_ts=%i",time,session->rtp.rcv_last_ret_ts);
		if (RTP_TIMESTAMP_IS_STRICTLY_NEWER_THAN
		    (time, session->rtp.rcv_last_ret_ts))
		{
			/* the user has missed some data previously, so we are going to give him now. */
			/* we must tell him to call the function once again with the same timestamp
			 * by setting *have_more=1 */
			*have_more = 1;
		}
		if (payload->type == PAYLOAD_AUDIO_CONTINUOUS)
		{
			ts_int = (len * payload->bits_per_sample) >> 3;
			session->rtp.rcv_last_ret_ts += ts_int;
			//ortp_debug("ts_int=%i",ts_int);
		}
		else
			ts_int = 0;
	}
	else return 0;

	/* try to fill the user buffer */
	while (1)
	{

		if (mp != NULL)
		{
			mlen = msgdsize (mp->b_cont);
			wlen = msg_to_buf (mp, buffer, rlen);
			buffer += wlen;
			rlen -= wlen;
			ortp_debug("mlen=%i wlen=%i rlen=%i", mlen, wlen,
				   rlen);
			/* do we fill all the buffer ? */
			if (rlen > 0)
			{
				/* we did not fill all the buffer */
				freemsg (mp);
				/* if we have continuous audio, try to get other packets to fill the buffer,
				 * ie continue the loop */
				//ortp_debug("User buffer not filled entirely");
				if (ts_int > 0)
				{
					time = session->rtp.rcv_last_ret_ts;
					ortp_debug("Need more: will ask for %i.",
						 time);
				}
				else
					return len - rlen;
			}
			else if (mlen > wlen)
			{
				int unread =
					mlen - wlen + (mp->b_wptr -
						       mp->b_rptr);
				/* not enough space in the user supplied buffer */
				/* we re-enqueue the msg with its updated read pointers for next time */
				ortp_debug ("Re-enqueuing packet.");
				rtp_session_lock (session);
				rtp_putq (&session->rtp.rq, mp);
				rtp_session_unlock (session);
				/* quite ugly: I change the stats ... */
				ortp_global_stats.recv -= unread;
				stream->stats.recv -= unread;
				return len;
			}
			else
			{
				/* the entire packet was written to the user buffer */
				freemsg (mp);
				return len;
			}
		}
		else
		{
			/* fill with a zero pattern (silence) */
			if (payload->pattern_length != 0)
			{
				int i = 0, j = 0;
				while (i < rlen)
				{
					buffer[i] = payload->zero_pattern[j];
					i++;
					j++;
					if (j <= payload->pattern_length)
						j = 0;
				}
				return len;
			}
			*have_more = 0;
			return 0;
		}
		mp = rtp_session_recvm_with_ts (session, time);
		payload = rtp_profile_get_payload (session->profile,
						 session->recv_pt);
		if (payload==NULL){
			g_warning("rtp_session_recv_with_ts: unable to recv an unsupported payload.");
			if (mp!=NULL) freemsg(mp);
			return -1;
		}
	}
	return -1;
}
/**
 *rtp_session_get_current_send_ts:
 *@session: a rtp session.
 *
 *	When the rtp session is scheduled and has started to send packets, this function
 *	computes the timestamp that matches to the present time. Using this function can be 
 *	usefull when sending discontinuous streams. Some time can be elapsed between the end
 *	of a stream burst and the begin of a new stream burst, and the application may be not
 *	not aware of this elapsed time. In order to get a valid (current) timestamp to pass to 
 *	#rtp_session_send_with_ts() or #rtp_session_sendm_with_ts(), the application may
 *	use rtp_session_get_current_send_ts().
 *
 *Returns: the current send timestamp for the rtp session.
**/
guint32 rtp_session_get_current_send_ts(RtpSession *session)
{
	guint32 userts;
	guint32 session_time;
	RtpScheduler *sched=session->sched;
	PayloadType *payload;
	payload=rtp_profile_get_payload(session->profile,session->send_pt);
	g_return_val_if_fail(payload!=NULL, 0);
	if ( (session->flags & RTP_SESSION_SCHEDULED)==0 ){
		g_warning("can't guess current timestamp because session is not scheduled.");
		return 0;
	}
	session_time=sched->time_-session->rtp.snd_time_offset;
	userts=  (guint32)( ( (gdouble)(session_time) * (gdouble) payload->clock_rate )/ 1000.0)
				+ session->rtp.snd_ts_offset;
	return userts;
}

/**
 *rtp_session_get_current_recv_ts:
 *@session: a rtp session.
 *
 * Same thing as rtp_session_get_current_send_ts() except that it's for an incoming stream.
 * Works only on scheduled mode.
 *
 * Returns: the theoritical that would have to be receive now.
 *
**/
guint32 rtp_session_get_current_recv_ts(RtpSession *session){
	guint32 userts;
	guint32 session_time;
	RtpScheduler *sched=ortp_get_scheduler();
	PayloadType *payload;
	payload=rtp_profile_get_payload(session->profile,session->recv_pt);
	g_return_val_if_fail(payload!=NULL, 0);
	if ( (session->flags & RTP_SESSION_SCHEDULED)==0 ){
		g_warning("can't guess current timestamp because session is not scheduled.");
		return 0;
	}
	session_time=sched->time_-session->rtp.rcv_time_offset;
	userts=  (guint32)( ( (gdouble)(session_time) * (gdouble) payload->clock_rate )/ 1000.0)
				+ session->rtp.rcv_ts_offset;
	return userts;
}

/**
 *rtp_session_set_time_jump_limit:
 *@session: the rtp session
 *@ts_step: a time interval in miliseconds
 *
 * oRTP has the possibility to inform the application through a callback registered 
 * with rtp_session_signal_connect about crazy incoming RTP stream that jumps from 
 * a timestamp N to N+<some crazy value>. This lets the opportunity for the application
 * to reset the session in order to resynchronize, or any other action like stopping the call
 * and reporting an error.
**/
void rtp_session_set_time_jump_limit(RtpSession *session, gint milisecs){
	guint32 ts;
	session->rtp.time_jump=milisecs;
	ts=rtp_session_time_to_ts(session,milisecs);
	if (ts==0) session->rtp.ts_jump=1<<31;	/* do not detect ts jump */
	else session->rtp.ts_jump=ts;
}

void rtp_session_release_sockets(RtpSession *session){
	if (session->rtp.socket>0) close_socket (session->rtp.socket);
	if (session->rtcp.socket>0) close_socket (session->rtcp.socket);
	session->rtp.socket=-1;
	session->rtcp.socket=-1;
}

void rtp_session_uninit (RtpSession * session)
{
	/* first of all remove the session from the scheduler */
	if (session->flags & RTP_SESSION_SCHEDULED)
	{
		rtp_scheduler_remove_session (session->sched,session);
	}
	/*flush all queues */
	flushq (&session->rtp.rq, FLUSHALL);

	/* close sockets */
	if (session->rtp.socket>0) close_socket (session->rtp.socket);
	if (session->rtcp.socket>0) close_socket (session->rtcp.socket);

	wait_point_uninit(&session->send_wp);
	wait_point_uninit(&session->recv_wp);
	g_mutex_free (session->lock);
	session->lock=NULL;
	if (session->current_tev!=NULL) freemsg(session->current_tev);
	if (session->rtp.cached_mp!=NULL) freemsg(session->rtp.cached_mp);
	if (session->rtcp.cached_mp!=NULL) freemsg(session->rtcp.cached_mp);
	if (session->sd!=NULL) freemsg(session->sd);
}

/**
 *rtp_session_reset:
 *@session: a rtp session.
 *
 *	Reset the session: local and remote addresses are kept unchanged but the internal
 *	queue for ordering and buffering packets is flushed, the session is ready to be
 *	re-synchronised to another incoming stream.
 *
**/
void rtp_session_reset (RtpSession * session)
{

	if (session->flags & RTP_SESSION_SCHEDULED) rtp_session_lock (session);
	
	flushq (&session->rtp.rq, FLUSHALL);
	rtp_session_set_flag (session, RTP_SESSION_RECV_SYNC);
	rtp_session_set_flag (session, RTP_SESSION_SEND_SYNC);
	rtp_session_set_flag (session, RTP_SESSION_RECV_NOT_STARTED);
	rtp_session_set_flag (session, RTP_SESSION_SEND_NOT_STARTED);
	//session->ssrc=0;
	session->rtp.snd_time_offset = 0;
	session->rtp.snd_ts_offset = 0;
	session->rtp.snd_rand_offset = 0;
	session->rtp.snd_last_ts = 0;
	session->rtp.rcv_time_offset = 0;
	session->rtp.rcv_ts_offset = 0;
	session->rtp.rcv_query_ts_offset = 0;
	session->rtp.rcv_diff_ts = 0;
	session->rtp.rcv_ts = 0;
	session->rtp.rcv_last_ts = 0;
	session->rtp.rcv_last_app_ts = 0;
	session->rtp.hwrcv_extseq.one = 0;
	session->rtp.hwrcv_since_last_SR=0;
	session->rtp.snd_seq = 0;
	rtp_stats_reset(&session->rtp.stats);
	jitter_control_init(&session->rtp.jittctl,-1,NULL);
	
	if (session->flags & RTP_SESSION_SCHEDULED) rtp_session_unlock (session);

}

/**
 *rtp_session_set_data:
 *	@session : a rtp session
 *	@data : an opaque pointer to be stored in the session
 *
 *	Stores some application specific data into the session, so that it is easy to retrieve it
 *	from the signal callbacks using rtp_session_get_data().
**/

void rtp_session_set_data(RtpSession *session, void *data){
	session->user_data=data;
}

/**
 *rtp_session_get_data:
 *	@session : a rtp session
 *
 *	Returns: the void pointer previously set using rtp_session_set_data()
**/
void *rtp_session_get_data(const RtpSession *session){
	return session->user_data;
}

/**
 *rtp_session_destroy:
 *@session: a rtp session.
 *
 *	Destroys a rtp session.
 *
**/
void rtp_session_destroy (RtpSession * session)
{
	rtp_session_uninit (session);
	g_free (session);
}

guint32 rtp_session_time_to_ts(RtpSession *session, gint time){
	PayloadType *payload;
	payload =
		rtp_profile_get_payload (session->profile,
					 session->send_pt);
	if (payload == NULL)
	{
		g_warning
			("rtp_session_ts_to_t: use of unsupported payload type.");
		return 0;
	}
	/* the return value is in milisecond */
	return (double)payload->clock_rate*(double)time/1000.0;
}

/* function used by the scheduler only:*/
guint32 rtp_session_ts_to_time (RtpSession * session, guint32 timestamp)
{
	PayloadType *payload;
	payload =
		rtp_profile_get_payload (session->profile,
					 session->send_pt);
	if (payload == NULL)
	{
		g_warning
			("rtp_session_ts_to_t: use of unsupported payload type.");
		return 0;
	}
	/* the return value is in milisecond */
	return (guint32) (1000.0 *
			  ((double) timestamp /
			   (double) payload->clock_rate));
}


/* time is the number of miliseconds elapsed since the start of the scheduler */
void rtp_session_process (RtpSession * session, guint32 time, RtpScheduler *sched)
{
	wait_point_lock(&session->send_wp);
	if (wait_point_check(&session->send_wp,time)){
		session_set_set(&sched->w_sessions,session);
		wait_point_wakeup(&session->send_wp);
	}
	wait_point_unlock(&session->send_wp);
	
	wait_point_lock(&session->recv_wp);
	if (wait_point_check(&session->recv_wp,time)){
		session_set_set(&sched->r_sessions,session);
		wait_point_wakeup(&session->recv_wp);
	}
	wait_point_unlock(&session->recv_wp);
}


void rtp_session_make_time_distorsion(RtpSession *session, gint milisec)
{
	session->rtp.snd_time_offset+=milisec;
}


/* packet api */

void rtp_add_csrc(mblk_t *mp, guint32 csrc)
{
	rtp_header_t *hdr=(rtp_header_t*)mp->b_rptr;
	hdr->csrc[hdr->cc]=csrc;
    hdr->cc++;
}
