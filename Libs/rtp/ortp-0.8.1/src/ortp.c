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
#include "scheduler.h"
#include <stdlib.h>

rtp_stats_t ortp_global_stats;

#ifdef ENABLE_MEMCHECK
gint ortp_allocations=0;
#endif


RtpScheduler *__ortp_scheduler;


void dummy_log(const gchar *log_domain,
                                             GLogLevelFlags log_level,
                                             const gchar *message,
                                             gpointer user_data)
{
	return;
}

extern void av_profile_init(RtpProfile *profile);

static void init_random_number_generator(){
	struct timeval t;
	gettimeofday(&t,NULL);
	srandom(t.tv_usec+t.tv_sec);
}

/**
 *ortp_init:
 *
 *	Initialize the oRTP library. You should call this function first before using
 *	oRTP API.
**/
 
void ortp_init()
{
	static gboolean initialized=FALSE;
	if (initialized) return;
	initialized=TRUE;

#ifdef _WIN32
	WORD wVersionRequested;
	WSADATA wsaData;
 
	wVersionRequested = MAKEWORD( 1, 0 );

	if (WSAStartup(wVersionRequested,&wsaData)!=0) 
	{
		g_error("Fail to initialise socket api");
	}
#endif

#ifdef HAVE_GLIB
	if (!g_thread_supported()) g_thread_init (NULL);
#endif
	av_profile_init(&av_profile);
	ortp_global_stats_reset();
	init_random_number_generator();
	g_message("oRTP-" ORTP_VERSION "initialized.");
}


/**
 *ortp_scheduler_init:
 *
 *	Initialize the oRTP scheduler. You only have to do that if you intend to use the
 *	scheduled mode of the #RtpSession in your application.
 *	
**/
void ortp_scheduler_init()
{
	static gboolean initialized=FALSE;
	if (initialized) return;
	initialized=TRUE;
#ifdef __hpux
	/* on hpux, we must block sigalrm on the main process, because signal delivery
	is ?random?, well, sometimes the SIGALRM goes to both the main thread and the 
	scheduler thread */
	sigset_t set;
	sigemptyset(&set);
	sigaddset(&set,SIGALRM);
	sigprocmask(SIG_BLOCK,&set,NULL);
#endif /* __hpux */
	if (!g_thread_supported()) g_thread_init(NULL);
	__ortp_scheduler=rtp_scheduler_new();
	rtp_scheduler_start(__ortp_scheduler);
	//sleep(1);
}


/**
 *ortp_exit:
 *
 * Gracefully uninitialize the library, including shutdowning the scheduler if it was started.
 *	
**/
void ortp_exit()
{
	if (__ortp_scheduler!=NULL)
	{
		rtp_scheduler_destroy(__ortp_scheduler);
		__ortp_scheduler=NULL;
	}
}

/**
 *ortp_get_scheduler:
 *
 *	Returns a pointer to the scheduler, NULL if it was not running.
 *	The application developer should have to call this function.
 *
 *Returns: a pointer to the scheduler.
**/
RtpScheduler * ortp_get_scheduler()
{
	if (__ortp_scheduler==NULL) g_error("Cannot use the scheduled mode: the scheduler is not "
									"started. Call ortp_scheduler_init() at the begginning of the application.");
	return __ortp_scheduler;
}


void ortp_log(const gchar *log_domain,GLogLevelFlags log_level,
                                           const gchar *message,
                                           gpointer user_data)
{
	gchar *lev;
	switch(log_level){
		case G_LOG_LEVEL_MESSAGE:
			lev="message";
			break;
		case G_LOG_LEVEL_WARNING:
			lev="warning";
			break;
		case G_LOG_LEVEL_ERROR:
			lev="error";
		default:
			lev="(unknown log type)";
	}
	if (user_data==NULL){
		user_data=stdout;
	}
	fprintf((FILE*)user_data,"%s-%s:%s\n",log_domain,lev,message);
}


/**
 *ortp_set_debug_file:
 *@domain:	one of "oRTP" or "oRTP-stats" logging domain.
 *@file: a FILE pointer where to output the messages from the domain.
 *
 * Warning: domain is ignored when not compiling with glib support.
**/
void ortp_set_debug_file(gchar *domain,FILE *file)
{
	if (file!=NULL)
		g_log_set_handler (domain, G_LOG_LEVEL_MASK, ortp_log, (gpointer)file);
	else g_log_set_handler (domain, G_LOG_LEVEL_MASK, dummy_log, NULL);
}
/**
 *ortp_set_log_handler:
 *@domain: one of the "oRTP" or "oRTP-stats" logging domain.
 *@func: your logging function, compatible with the GLogFunc prototype.
 *
 * Warning: domain is ignored when not compiling with glib support.
**/
void ortp_set_log_handler(const gchar *domain, GLogFunc func, gpointer userdata){
	g_log_set_handler(domain,G_LOG_LEVEL_MASK,func,userdata);
}



void ortp_global_stats_display()
{
	rtp_stats_display(&ortp_global_stats,"Global statistics");
#ifdef ENABLE_MEMCHECK	
	printf("Unfreed allocations: %i\n",ortp_allocations);
#endif
}


void rtp_stats_display(rtp_stats_t *stats, char *header)
{

	g_log("oRTP-stats",G_LOG_LEVEL_MESSAGE,
			"\n   %s :\n"
	      " number of rtp packet sent=%lld\n"
	      " number of rtp bytes sent=%lld bytes\n"
	      " number of rtp packet received=%lld\n"
	      " number of rtp bytes received=%lld bytes\n"
	      " number of incoming rtp bytes successfully delivered to the application=%lld \n"
	      " number of times the application queried a packet that didn't exist=%lld \n"
	      " number of rtp packets received too late=%lld\n"
		  " number of rtp packets skipped=%lld\n"
	      " number of bad formatted rtp packets=%lld\n"
	      " number of packet discarded because of queue overflow=%lld\n",
	      header,
	      (long long)stats->packet_sent,
	      (long long)stats->sent,
	      (long long)stats->packet_recv,
	      (long long)stats->hw_recv,
	      (long long)stats->recv,
	      (long long)stats->unavaillable,
	      (long long)stats->outoftime,
		  (long long)stats->skipped,
	      (long long)stats->bad,
	      (long long)stats->discarded);
}

void ortp_global_stats_reset(){
	memset(&ortp_global_stats,0,sizeof(rtp_stats_t));
}

rtp_stats_t *ortp_get_global_stats(){
	return &ortp_global_stats;
}

void rtp_stats_reset(rtp_stats_t *stats){
	memset((void*)stats,0,sizeof(rtp_stats_t));
}


/**
 *ortp_min_version_required:
 *@major: 
 *@minor: 
 *@micro:
 *
 * This function give the opportunity to programs to check if the libortp they link to
 * has the minimum version number they need.
 *
 * Returns: true if ortp has a version number greater or equal than the required one.
**/
gboolean ortp_min_version_required(int major, int minor, int micro){
	return ((major*1000000) + (minor*1000) + micro) <= 
		   ((ORTP_MAJOR_VERSION*1000000) + (ORTP_MINOR_VERSION*1000) + ORTP_MICRO_VERSION);
}
