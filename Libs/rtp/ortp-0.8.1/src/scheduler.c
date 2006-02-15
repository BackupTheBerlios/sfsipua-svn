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

#ifndef _WIN32	/* do not include ortp-config.h when we are on win32 */
	#include <ortp/rtpport.h>
	#include <sched.h>
	#include <unistd.h>
	#include <errno.h>
#else
	#include "ortp-config-win32.h"
#endif



#include "scheduler.h"

// To avoid warning during compile
extern void rtp_session_process (RtpSession * session, guint32 time, RtpScheduler *sched);


void rtp_scheduler_init(RtpScheduler *sched)
{
	sched->list=0;
	sched->time_=0;
	/* default to the posix timer */
	rtp_scheduler_set_timer(sched,&posix_timer);
	sched->lock=g_mutex_new();
	//sched->unblock_select_mutex=g_mutex_new();
	sched->unblock_select_cond=g_cond_new();
	sched->max_sessions=sizeof(SessionSet)*8;
	session_set_init(&sched->all_sessions);
	sched->all_max=0;
	session_set_init(&sched->r_sessions);
	sched->r_max=0;
	session_set_init(&sched->w_sessions);
	sched->w_max=0;
	session_set_init(&sched->e_sessions);
	sched->e_max=0;
}

RtpScheduler * rtp_scheduler_new()
{
	RtpScheduler *sched=g_malloc(sizeof(RtpScheduler));
	memset(sched,0,sizeof(RtpScheduler));
	rtp_scheduler_init(sched);
	return sched;
}

void rtp_scheduler_set_timer(RtpScheduler *sched,RtpTimer *timer)
{
	if (sched->thread_running){
		g_warning("Cannot change timer while the scheduler is running !!");
		return;
	}
	sched->timer=timer;
	/* report the timer increment */
	sched->timer_inc=(timer->interval.tv_usec/1000) + (timer->interval.tv_sec*1000);
}

void rtp_scheduler_start(RtpScheduler *sched)
{
	if (sched->thread_running==0){
		sched->thread_running=1;
		g_mutex_lock(sched->lock);
		sched->thread=g_thread_create((GThreadFunc)rtp_scheduler_schedule,(gpointer)sched,TRUE,NULL);
		g_cond_wait(sched->unblock_select_cond,sched->lock);
		g_mutex_unlock(sched->lock);
	}
	else g_warning("Scheduler thread already running.");

}
void rtp_scheduler_stop(RtpScheduler *sched)
{
	if (sched->thread_running==1)
	{
		sched->thread_running=0;
		g_thread_join(sched->thread);
	}
	else g_warning("Scheduler thread is not running.");
}

void rtp_scheduler_destroy(RtpScheduler *sched)
{
	if (sched->thread_running) rtp_scheduler_stop(sched);
	g_mutex_free(sched->lock);
	//g_mutex_free(sched->unblock_select_mutex);
	g_cond_free(sched->unblock_select_cond);
	g_free(sched);
}

gpointer rtp_scheduler_schedule(gpointer psched)
{
	RtpScheduler *sched=(RtpScheduler*) psched;
	RtpTimer *timer=sched->timer;
	RtpSession *current;
	int err;

	/* try to get the real time priority by getting root*/
#ifndef _WIN32
#ifdef HAVE_SETEUID
	err=seteuid(0);
#else
	err=setuid(0);
#endif
	if (err<0) g_message("Could not get root euid: %s",strerror(errno));
#endif
	g_message("scheduler: trying to reach real time kernel scheduling...");

	/* take this lock to prevent the thread to start until g_thread_create() returns
		because we need sched->thread to be initialized */
	g_mutex_lock(sched->lock);
	g_cond_signal(sched->unblock_select_cond);	/* unblock the starting thread */
	g_mutex_unlock(sched->lock);
	g_thread_set_priority(sched->thread,G_THREAD_PRIORITY_HIGH);
	timer->timer_init();
	while(sched->thread_running)
	{
		/* do the processing here: */
		
		g_mutex_lock(sched->lock);
		
		current=sched->list;
		/* processing all scheduled rtp sessions */
		while (current!=NULL)
		{
			ortp_debug("scheduler: processing session=%p.\n",current);
			rtp_session_process(current,sched->time_,sched);
			current=current->next;
		}
		/* wake up all the threads that are sleeping in _select()  */
		g_cond_broadcast(sched->unblock_select_cond);
		g_mutex_unlock(sched->lock);
		
		/* now while the scheduler is going to sleep, the other threads can compute their
		result mask and see if they have to leave, or to wait for next tick*/
		//g_message("scheduler: sleeping.");
		timer->timer_do();
		sched->time_+=sched->timer_inc;
	}
	/* when leaving the thread, stop the timer */
	timer->timer_uninit();
	return NULL;
}

void rtp_scheduler_add_session(RtpScheduler *sched, RtpSession *session)
{
	RtpSession *oldfirst;
	int i;
	if (session->flags & RTP_SESSION_IN_SCHEDULER){
		/* the rtp session is already scheduled, so return silently */
		return;
	}
	rtp_scheduler_lock(sched);
	/* enqueue the session to the list of scheduled sessions */
	oldfirst=sched->list;
	sched->list=session;
	session->next=oldfirst;
	if (sched->max_sessions==0){
		g_error("rtp_scheduler_add_session: max_session=0 !");
	}
	/* find a free pos in the session mask*/
	for (i=0;i<sched->max_sessions;i++){
		if (!ORTP_FD_ISSET(i,&sched->all_sessions.rtpset)){
			session->mask_pos=i;
			session_set_set(&sched->all_sessions,session);
			/* make a new session scheduled not blockable if it has not started*/
			if (session->flags & RTP_SESSION_RECV_NOT_STARTED) 
				session_set_set(&sched->r_sessions,session);
			if (session->flags & RTP_SESSION_SEND_NOT_STARTED) 
				session_set_set(&sched->w_sessions,session);
			if (i>sched->all_max){
				sched->all_max=i;
			}
			break;
		}
	}
	
	rtp_session_set_flag(session,RTP_SESSION_IN_SCHEDULER);
	rtp_scheduler_unlock(sched);
}

void rtp_scheduler_remove_session(RtpScheduler *sched, RtpSession *session)
{
	RtpSession *tmp;
	int cond=1;
	g_return_if_fail(session!=NULL); 
	if (!(session->flags & RTP_SESSION_IN_SCHEDULER)){
		/* the rtp session is not scheduled, so return silently */
		return;
	}

	rtp_scheduler_lock(sched);
	tmp=sched->list;
	if (tmp==session){
		sched->list=tmp->next;
		rtp_session_unset_flag(session,RTP_SESSION_IN_SCHEDULER);
		session_set_clr(&sched->all_sessions,session);
		rtp_scheduler_unlock(sched);
		return;
	}
	/* go the position of session in the list */
	while(cond){
		if (tmp!=NULL){
			if (tmp->next==session){
				tmp->next=tmp->next->next;
				cond=0;
			}
			else tmp=tmp->next;
		}else {
			/* the session was not found ! */
			g_warning("rtp_scheduler_remove_session: the session was not found in the scheduler list!");
			cond=0;
		}
	}
	rtp_session_unset_flag(session,RTP_SESSION_IN_SCHEDULER);
	/* delete the bit in the mask */
	session_set_clr(&sched->all_sessions,session);
	rtp_scheduler_unlock(sched);
}
