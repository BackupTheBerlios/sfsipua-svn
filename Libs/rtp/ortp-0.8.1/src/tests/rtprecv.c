 /*
  The lprtplib LinPhone RTP library intends to provide basics for a RTP stack.
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
#include <signal.h>
#include <stdlib.h>
#ifndef _WIN32
#include <unistd.h>
#include <stdio.h>
#include <sys/types.h>
#endif

gint cond=1;

void stop_handler(int signum)
{
	cond=0;
}

void ssrc_cb(RtpSession *session)
{
	printf("hey, the ssrc has changed !\n");
}

static char *help="usage: rtprecv  filename loc_port [--format format] [--soundcard]\n";

#define MULAW 0
#define ALAW 1

#if defined(__hpux) && HAVE_SYS_AUDIO_H

#include <sys/audio.h>

gint sound_init(gint format)
{
	int fd;
	fd=open("/dev/audio",O_WRONLY);
	if (fd<0){
		perror("Can't open /dev/audio");
		return -1;
	}
	ioctl(fd,AUDIO_RESET,0);
	ioctl(fd,AUDIO_SET_SAMPLE_RATE,8000);
	ioctl(fd,AUDIO_SET_CHANNELS,1);
	if (format==MULAW)
		ioctl(fd,AUDIO_SET_DATA_FORMAT,AUDIO_FORMAT_ULAW);
	else ioctl(fd,AUDIO_SET_DATA_FORMAT,AUDIO_FORMAT_ALAW);
	return fd;	
}
#else
gint sound_init(gint format)
{
	return -1;
}
#endif

int main(int argc, char*argv[])
{
	RtpSession *session;
	char buffer[160];
	int err;
	guint32 ts=0;
	gint stream_received=0;
	FILE *outfile;
	gint local_port;
	gint have_more;
	gint i;
	gint format=0;
	gint soundcard=0;
	gint sound_fd=0;
	gboolean adapt=TRUE;
	
	/* init the lib */
	if (argc<3){
		printf(help);
		return -1;
	}
	local_port=atoi(argv[2]);
	if (local_port<=0) {
		printf(help);
		return -1;
	}
	for (i=3;i<argc;i++)
	{
		if (strcmp(argv[i],"--noadapt")==0) adapt=FALSE;
		if (strcmp(argv[i],"--format")==0){
			i++;
			if (i<argc){
				if (strcmp(argv[i],"mulaw")==0){
					format=MULAW;
				}else
				if (strcmp(argv[i],"alaw")==0){
					format=ALAW;
				}else{
					printf("Unsupported format %s\n",argv[i]);
					return -1;
				}
			}
		}
		else if (strcmp(argv[i],"--soundcard")==0){
			soundcard=1;
		}
	}
	
	outfile=fopen(argv[1],"wb");
	if (outfile==NULL) {
		perror("Cannot open file for writing");
		return -1;
	}
	
	
	if (soundcard){
		sound_fd=sound_init(format);
	}
	
	ortp_init();
	ortp_scheduler_init();
	
	signal(SIGINT,stop_handler);
	ortp_set_debug_file("oRTP",stdout);
	session=rtp_session_new(RTP_SESSION_RECVONLY);	
	rtp_session_set_scheduling_mode(session,1);
	rtp_session_set_blocking_mode(session,1);
	rtp_session_set_local_addr(session,"0.0.0.0",atoi(argv[2]));
	rtp_session_enable_adaptive_jitter_compensation(session,adapt);
	rtp_session_set_jitter_compensation(session,40);
	rtp_session_set_payload_type(session,0);
	rtp_session_signal_connect(session,"ssrc_changed",(RtpCallback)ssrc_cb,NULL);
	rtp_session_signal_connect(session,"ssrc_changed",(RtpCallback)rtp_session_reset,NULL);
	
	while(cond)
	{
		have_more=1;
		while (have_more){
			err=rtp_session_recv_with_ts(session,buffer,160,ts,&have_more);
			if (err>0) stream_received=1;
			/* this is to avoid to write to disk some silence before the first RTP packet is returned*/	
			if ((stream_received) && (err>0)) {
				fwrite(buffer,1,err,outfile);
				if (sound_fd>0) write(sound_fd,buffer,err);
			}
		}
		ts+=160;
		//g_message("Receiving packet.");
	}
	
	rtp_session_destroy(session);
	ortp_exit();
	
	ortp_global_stats_display();
	
	return 0;
}
