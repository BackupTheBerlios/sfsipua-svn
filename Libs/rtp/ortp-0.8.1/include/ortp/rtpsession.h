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

#ifndef RTPSESSION_H
#define RTPSESSION_H


#include <ortp/rtpport.h>
#include <ortp/rtp.h>
#include <ortp/payloadtype.h>
#include <ortp/sessionset.h>
#include <ortp/rtcp.h>
#include <ortp/str_utils.h>
#include <ortp/rtpsignaltable.h>

#include <stdio.h>


#ifndef _WIN32
# include <sys/types.h>
# include <sys/socket.h>
# include <errno.h>
# include <netinet/in.h>
# ifdef _XOPEN_SOURCE_EXTENDED
#  include <arpa/inet.h>
# endif
# include <unistd.h>
# include <sys/time.h>
#else
# include <winsock2.h>
#endif   /* _WIN32 */



typedef enum {
	RTP_SESSION_RECVONLY,
	RTP_SESSION_SENDONLY,
	RTP_SESSION_SENDRECV
} RtpSessionMode;



typedef enum {
	RTP_SESSION_RECV_SYNC=1,	/* the rtp session is synchronising in the incoming stream */
	RTP_SESSION_SEND_SYNC=1<<1, /* the rtp session is synchronising in the outgoing stream */
	RTP_SESSION_SCHEDULED=1<<2, /* the rtp session has to be scheduled */
	RTP_SESSION_BLOCKING_MODE=1<<3, /* in blocking mode */
	RTP_SESSION_RECV_NOT_STARTED=1<<4,	/* the application has not started to try to recv */
	RTP_SESSION_SEND_NOT_STARTED=1<<5,  /* the application has not started to send something */
	RTP_SESSION_IN_SCHEDULER=1<<6,	/* the rtp session is in the scheduler list */
	RTP_SESSION_USING_EXT_SOCKETS=1<<7 /* the session is using externaly supplied sockets */
}RtpSessionFlags;


typedef struct _JitterControl
{
	gint jitt_comp;   /* the user jitt_comp in miliseconds*/
	gint jitt_comp_ts; /* the jitt_comp converted in rtp time (same unit as timestamp) */
	gint adapt_jitt_comp_ts;
	float slide;
	float jitter;
	gint count;
	gint olddiff;
	float inter_jitter;	/* interarrival jitter as defined in the RFC */
	gint corrective_step;
	gint corrective_slide;
	gboolean adaptive;
} JitterControl;

typedef struct _WaitPoint
{
	GMutex *lock;
	GCond *cond;
	guint32 time;
	gboolean wakeup;
} WaitPoint;
	
typedef struct _RtpStream
{
	gint socket;
	gint sockfamily;
	gint max_rq_size;
	gint time_jump;
	guint32 ts_jump;
	queue_t rq;
	queue_t tev_rq;
	mblk_t *cached_mp;
	int loc_port;
#ifdef INET6
	struct sockaddr_storage rem_addr;
#else
	struct sockaddr_in rem_addr;
#endif
	int rem_addrlen;
	JitterControl jittctl;
	guint32 snd_time_offset;/*the scheduler time when the application send its first timestamp*/	
	guint32 snd_ts_offset;	/* the first application timestamp sent by the application */
	guint32 snd_rand_offset;	/* a random number added to the user offset to make the stream timestamp*/
	guint32 snd_last_ts;	/* the last stream timestamp sended */
	guint32 rcv_time_offset; /*the scheduler time when the application ask for its first timestamp*/
	guint32 rcv_ts_offset;  /* the first stream timestamp */
	guint32 rcv_query_ts_offset;	/* the first user timestamp asked by the application */
	guint32 rcv_diff_ts;	/* difference between the first user timestamp and first stream timestamp */
	guint32 hwrcv_diff_ts;
	guint32 rcv_ts;			/* to be unused */
	guint32 rcv_last_ts;	/* the last stream timestamp got by the application */
	guint32 rcv_last_app_ts; /* the last application timestamp asked by the application */	
	guint32 rcv_last_ret_ts; /* the timestamp of the last sample returned (only for continuous audio)*/
	poly32_t hwrcv_extseq; /* last received on socket extended sequence number */
	guint32 hwrcv_seq_at_last_SR;
	guint hwrcv_since_last_SR;
	guint32 last_rcv_SR_ts;     /* NTP timestamp (middle 32 bits) of last received SR */
	struct timeval last_rcv_SR_time;   /* time at which last SR was received  */
	guint16 snd_seq; /* send sequence number */
	guint32 last_rtcp_report_snt_r;	/* the time of the last rtcp report sent, in recv timestamp unit */
	guint32 last_rtcp_report_snt_s;	/* the time of the last rtcp report sent, in send timestamp unit */
	guint32 rtcp_report_snt_interval; /* the interval in timestamp unit between rtcp report sent */
	rtp_stats_t stats;
}RtpStream;

typedef struct _RtcpStream
{
	gint socket;
	gint sockfamily;
	mblk_t *cached_mp;
#ifdef INET6
	struct sockaddr_storage rem_addr;
#else
	struct sockaddr_in rem_addr;
#endif
	int rem_addrlen;
} RtcpStream;

typedef struct _RtpSession RtpSession;



struct _RtpSession
{
	RtpSession *next;	/* next RtpSession, when the session are enqueued by the scheduler */
	RtpProfile *profile;
	WaitPoint recv_wp;
	WaitPoint send_wp;
	GMutex *lock;
	guint32 send_ssrc;
	guint32 recv_ssrc;
	gint send_pt;/* sent payload type */
	gint recv_pt;/* recv payload type */
	gint hw_recv_pt; /* recv payload type before jitter buffer */
	gint recv_buf_size;
	RtpSignalTable on_ssrc_changed;
	RtpSignalTable on_payload_type_changed;
	RtpSignalTable on_telephone_event_packet;
	RtpSignalTable on_telephone_event;
	RtpSignalTable on_timestamp_jump;
	RtpSignalTable on_network_error;
	struct _OList *signal_tables;
	RtpStream rtp;
	RtcpStream rtcp;
	RtpSessionMode mode;
	struct _RtpScheduler *sched;
	guint32 flags;
	gint mask_pos;	/* the position in the scheduler mask of RtpSession */
	gpointer user_data;
	
	/* telephony events extension */
	gint telephone_events_pt;	/* the payload type used for telephony events */
	mblk_t *current_tev;		/* the pending telephony events */
	mblk_t *sd;
	queue_t contributing_sources;
};
	



#ifdef __cplusplus
extern "C"
{
#endif

/*private */
void rtp_session_init(RtpSession *session, gint mode);
#define rtp_session_lock(session) 	g_mutex_lock(session->lock)
#define rtp_session_unlock(session) g_mutex_unlock(session->lock)
#define rtp_session_set_flag(session,flag) (session)->flags|=(flag)
#define rtp_session_unset_flag(session,flag) (session)->flags&=~(flag)
void rtp_session_uninit(RtpSession *session);

/* public API */
RtpSession *rtp_session_new(gint mode);
void rtp_session_set_scheduling_mode(RtpSession *session, gint yesno);
void rtp_session_set_blocking_mode(RtpSession *session, gint yesno);
void rtp_session_set_profile(RtpSession *session,RtpProfile *profile);
RtpProfile *rtp_session_get_profile(RtpSession *session);
int rtp_session_signal_connect(RtpSession *session,const gchar *signal, RtpCallback cb, gpointer user_data);
int rtp_session_signal_disconnect_by_callback(RtpSession *session,const gchar *signal, RtpCallback cb);
void rtp_session_set_ssrc(RtpSession *session, guint32 ssrc);
void rtp_session_set_seq_number(RtpSession *session, guint16 seq);
guint16 rtp_session_get_seq_number(RtpSession *session);
void rtp_session_set_jitter_compensation(RtpSession *session, int milisec);
void rtp_session_enable_adaptive_jitter_compensation(RtpSession *session, gboolean val);
gboolean rtp_session_adaptive_jitter_compensation_enabled(RtpSession *session);
void rtp_session_set_time_jump_limit(RtpSession *session, gint miliseconds);
int rtp_session_set_local_addr(RtpSession *session,const gchar *addr, gint port);
int rtp_session_get_local_port(const RtpSession *session);
gint rtp_session_set_remote_addr(RtpSession *session,const gchar *addr, gint port);
/* alternatively to the set_remote_addr() and set_local_addr(), an application can give
a valid socket (potentially connect()ed )to be used by the RtpSession */
void rtp_session_set_sockets(RtpSession *session, gint rtpfd, gint rtcpfd);

int rtp_session_set_send_payload_type(RtpSession *session, int paytype);
int rtp_session_get_send_payload_type(const RtpSession *session);

int rtp_session_get_recv_payload_type(const RtpSession *session);
int rtp_session_set_recv_payload_type(RtpSession *session, int pt);

int rtp_session_set_payload_type(RtpSession *session, int pt);

/* deprecated API:
int rtp_session_set_payload_type(RtpSession *session, int paytype);
int rtp_session_get_payload_type(RtpSession *session);
int rtp_session_set_payload_type_with_string (RtpSession * session, const char * mime);
*/

/*low level recv and send functions */
mblk_t * rtp_session_recvm_with_ts (RtpSession * session, guint32 user_ts);
mblk_t * rtp_session_create_packet(RtpSession *session,gint header_size, const char *payload, gint payload_size);
mblk_t * rtp_session_create_packet_with_data(RtpSession *session, char *payload, gint payload_size, void (*freefn)(void*));
mblk_t * rtp_session_create_packet_in_place(RtpSession *session,char *buffer, gint size, void (*freefn)(void*) );
gint rtp_session_sendm_with_ts (RtpSession * session, mblk_t *mp, guint32 userts);
/* high level recv and send functions */
gint rtp_session_recv_with_ts(RtpSession *session, gchar *buffer, gint len, guint32 time, gint *have_more);
gint rtp_session_send_with_ts(RtpSession *session, const gchar *buffer, gint len, guint32 userts);


guint32 rtp_session_get_current_send_ts(RtpSession *session);
guint32 rtp_session_get_current_recv_ts(RtpSession *session);
void rtp_session_flush_sockets(RtpSession *session);
void rtp_session_release_sockets(RtpSession *session);
void rtp_session_reset(RtpSession *session);
void rtp_session_destroy(RtpSession *session);

#define rtp_session_get_stats(session) (&(session)->stats)
#define rtp_session_reset_stats(session)	memset(&(session)->stats,0,sizeof(rtp_stats_t))
void rtp_session_set_data(RtpSession *session, void *data);
void *rtp_session_get_data(const RtpSession *session);

void rtp_session_set_recv_buf_size(RtpSession *session, int bufsize);

/* in use with the scheduler to convert a timestamp in scheduler time unit (ms) */
guint32 rtp_session_ts_to_time(RtpSession *session,guint32 timestamp);
guint32 rtp_session_time_to_ts(RtpSession *session, gint time);
/* this function aims at simulating senders with "imprecise" clocks, resulting in 
rtp packets sent with timestamp uncorrelated with the system clock .
This is only availlable to sessions working with the oRTP scheduler */
void rtp_session_make_time_distorsion(RtpSession *session, gint milisec);

/*RTCP functions */
void rtp_session_set_source_description(RtpSession *session, const gchar *cname,
	const gchar *name, const gchar *email, const gchar *phone, 
    const gchar *loc, const gchar *tool, const gchar *note);
void rtp_session_add_contributing_source(RtpSession *session, guint32 csrc, 
    const gchar *cname, const gchar *name, const gchar *email, const gchar *phone, 
    const gchar *loc, const gchar *tool, const gchar *note);
void rtp_session_remove_contributing_sources(RtpSession *session, guint32 csrc);
mblk_t* rtp_session_create_rtcp_sdes_packet(RtpSession *session);


/* packet api */
/* the first argument is a mblk_t. The header is supposed to be not splitted  */
#define rtp_set_markbit(mp,value)		((rtp_header_t*)((mp)->b_rptr))->markbit=(value)
#define rtp_set_seqnumber(mp,seq)	((rtp_header_t*)((mp)->b_rptr))->seq_number=(seq)
#define rtp_set_timestamp(mp,ts)	((rtp_header_t*)((mp)->b_rptr))->timestamp=(ts)
#define rtp_set_ssrc(mp,_ssrc)		((rtp_header_t*)((mp)->b_rptr))->ssrc=(_ssrc)
void rtp_add_csrc(mblk_t *mp,guint32 csrc);
#define rtp_set_payload_type(mp,pt)	((rtp_header_t*)((mp)->b_rptr))->paytype=(pt)



#ifdef __cplusplus
}
#endif

#endif
