 /*
  The oRTP LinPhone RTP library intends to provide basics for a RTP stack.
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

/* this program shows how to receive streams in paralel using the SessionSet api 
	and two threads only. */

#include <ortp/ortp.h>
#include <stdlib.h>
#include <stdio.h>

#ifndef _WIN32
#include <signal.h>
#include <sys/types.h>
#include <sys/time.h>
#include <unistd.h>
#include <sys/stat.h>
#include <fcntl.h>

#else
//#include <time.h>
#endif

#include <ortp/telephonyevents.h>

int runcond=1;

void stophandler(int signum)
{
	runcond=0;
}

static int dtmf_tab[16]={'0','1','2','3','4','5','6','7','8','9','*','#','A','B','C','D'};

static int *p_channel_id;

int dtmf_count=0;

static char *help="usage: tevmrtprecv	file_prefix local_port number_of_streams \n"
		"Receives multiples rtp streams with telephone events on local_port+2*k, k={0..number_of_streams}\n";

#define STREAMS_COUNT 1000


void recv_tev_cb(RtpSession *session,gint type,gpointer user_data)
{
        //printf("Receiving telephony event:%i\n",type);
        if (type<16) printf("This is dtmf %c on channel %d\n",dtmf_tab[type],*(int *)user_data);
        dtmf_count++;
}

int rtp2disk(RtpSession *session,guint32 ts, int fd)
{
	char buffer[160];
	int err,havemore=1;
	while (havemore){
		err=rtp_session_recv_with_ts(session,buffer,160,ts,&havemore);
		if (err>0){
			rtp_session_set_data(session,(gpointer)1);
			/* to indicate that (for the application) the stream has started, so we can start
			recording on disk */
		}
		if (session->user_data != NULL)
			write(fd,buffer,err);
	}
	return 0;
}


int main(int argc, char *argv[])
{
	RtpSession *session[STREAMS_COUNT];
	gint i;
	gint filefd[STREAMS_COUNT];
	gint port;
	guint32 user_ts=0;
	gint channels;
	SessionSet *set;
	gchar *filename;

	if (argc<4){
		printf(help);
		return -1;
	}
	
	channels=atoi(argv[3]);
	if (channels==0){
		printf(help);
		return -1;
	}
	
	ortp_init();
	ortp_scheduler_init();
	ortp_set_debug_file("oRTP",NULL);
	
        /* set the telephony event payload type to 96 in the av profile.*/
        rtp_profile_set_payload(&av_profile,96,&payload_type_telephone_event);

	port=atoi(argv[2]);
	p_channel_id = (int *)g_malloc(channels*sizeof(int));
	for (i=0;i<channels;i++){
		session[i]=rtp_session_new(RTP_SESSION_RECVONLY);	
		rtp_session_set_scheduling_mode(session[i],1);
		rtp_session_set_blocking_mode(session[i],0);

		rtp_session_set_local_addr(session[i],"0.0.0.0",port);
		rtp_session_set_recv_payload_type(session[i],0);
		rtp_session_set_recv_buf_size(session[i],256);

		p_channel_id[i] = i;
		/* register for telephony events */
		rtp_session_signal_connect(session[i],"telephone-event",(RtpCallback)recv_tev_cb,&p_channel_id[i]);

		port+=2;
	}
		
	filename=g_malloc(strlen(argv[1])+8);
	for (i=0;i<channels;i++){
		sprintf(filename,"%s%4.4d.dat",argv[1],i);
		#ifndef _WIN32
		filefd[i]=open(filename,O_WRONLY | O_CREAT | O_TRUNC, S_IRUSR|S_IWUSR|S_IRGRP|S_IWGRP);
		#else
		filefd[i]=open(filename,_O_BINARY | O_WRONLY | O_CREAT | O_TRUNC);
		#endif
		if (filefd[i]<0) g_error("Could not open %s for writing: %s",filename,strerror(errno));
	}
	signal(SIGINT,stophandler);
	/* create a set */
	set=session_set_new();
	while(runcond)
	{
		int k;
		
		for (k=0;k<channels;k++){
			/* add the session to the set */
			session_set_set(set,session[k]);
			
		}
		/* and then suspend the process by selecting() */
		session_set_select(set,NULL,NULL);
		for (k=0;k<channels;k++){
			if (session_set_is_set(set,session[k])){
				rtp2disk(session[k],user_ts,filefd[k]);
			}
		}
		user_ts+=160;
	}
	for (i=0;i<channels;i++){
		close(filefd[i]);
		rtp_session_destroy(session[i]);
	}
	session_set_destroy(set);
	g_free(p_channel_id);
	g_free(filename);
	ortp_exit();
	ortp_global_stats_display();
	return 0;
}
