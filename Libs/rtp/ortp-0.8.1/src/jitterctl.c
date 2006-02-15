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
/***************************************************************************
 *            jitterctl.c
 *
 *  Mon Nov  8 11:53:21 2004
 *  Copyright  2004  Simon MORLAT
 *  Email simon.morlat@linphone.org
 ****************************************************************************/

#include <ortp/rtpsession.h>
#include <ortp/payloadtype.h>
#include <math.h>
#include <stdlib.h>

#define JC_BETA 0.03	/*allows a clock slide around 3% */
#define JC_GAMMA (JC_BETA)

#include "jitterctl.h"

void jitter_control_init(JitterControl *ctl, int base_jiitt_time, PayloadType *payload){
	ctl->count=0;
	ctl->slide=0;
	ctl->jitter=0;
	ctl->inter_jitter=0;
	ctl->slide=0;
	if (base_jiitt_time!=-1) ctl->jitt_comp = base_jiitt_time;
	/* convert in timestamp unit: */
	if (payload!=NULL){
		jitter_control_set_payload(ctl,payload);
	}
	ctl->adapt_jitt_comp_ts=ctl->jitt_comp_ts;
	ctl->corrective_slide=0;
}

void jitter_control_enable_adaptive(JitterControl *ctl, gboolean val){
	ctl->adaptive=val;
}

void jitter_control_set_payload(JitterControl *ctl, PayloadType *pt){
	ctl->jitt_comp_ts =
			(gint) (((double) ctl->jitt_comp / 1000.0) * (pt->clock_rate));
	ctl->corrective_step=(160 * 8000 )/pt->clock_rate; /* This formula got to me after some beers */
	ctl->adapt_jitt_comp_ts=ctl->jitt_comp_ts;
}


void jitter_control_dump_stats(JitterControl *ctl){
	g_log("oRTP-stats",G_LOG_LEVEL_MESSAGE,"JitterControl:\n\tslide=%g,jitter=%g,count=%i",
			ctl->slide,ctl->jitter, ctl->count);
}


/*
 The algorithm computes two values:
	slide: an average of difference between the expected and the socket-received timestamp
	jitter: an average of the absolute value of the difference between socket-received timestamp and slide.
	slide is used to make clock-slide detection and correction.
	jitter is added to the initial jitt_comp_time value. It compensates bursty packets arrival (packets
	not arriving at regular interval ).
*/
void jitter_control_new_packet(JitterControl *ctl, guint32 packet_ts, guint32 cur_str_ts, gint32 * slide, gint32 *safe_delay){
	int diff=packet_ts - cur_str_ts;
	float gap;
	int d;
	//printf("diff=%g\n",diff);
	
	ctl->count++;
	ctl->slide= (ctl->slide*(1-JC_BETA)) + ((float)diff*JC_BETA);
	gap=fabs((float)diff - ctl->slide);
	ctl->jitter=(ctl->jitter*(1-JC_GAMMA)) + (gap*JC_GAMMA);
	d=diff-ctl->olddiff;
	ctl->inter_jitter=ctl->inter_jitter+ (( (float)abs(d) - ctl->inter_jitter)*(1/16.0));
	ctl->olddiff=diff;
	if (ctl->adaptive){
		int tmp;
		if (ctl->count%50==0) {
			/*jitter_control_dump_stats(ctl);*/
		}
		tmp=(int)(ctl->slide)-ctl->corrective_slide;
		if (tmp>ctl->corrective_step) ctl->corrective_slide+=ctl->corrective_step;
		else if (tmp<-ctl->corrective_step) ctl->corrective_slide-=ctl->corrective_step;
		/* the following is nearly equivalent, but maybe it consumes more CPU: ?*/
		/*ctl->corrective_slide=(((gint)ctl->slide)/ctl->corrective_step)*ctl->corrective_step;*/
		
		ctl->adapt_jitt_comp_ts=MAX(ctl->jitt_comp_ts,ctl->jitter);
		
		*slide=(gint32)ctl->slide;
		*safe_delay=(gint32)ctl->adapt_jitt_comp_ts;
	}else {
		*slide=0;
		*safe_delay=(gint32)ctl->jitt_comp_ts;
	}
	return ;
}


/**
 *rtp_session_set_jitter_compensation:
 *@session: a RtpSession
 *@milisec: the time interval in milisec to be jitter compensed.
 *
 * Sets the time interval for which packet are buffered instead of being delivered to the 
 * application.
 **/
void
rtp_session_set_jitter_compensation (RtpSession * session, gint milisec)
{
	PayloadType *payload = rtp_profile_get_payload (session->profile,
							session->recv_pt);
	if (payload==NULL){
		g_warning("rtp_session_set_jitter_compensation: cannot set because the payload type (%i) is unknown",session->recv_pt);
		return;
	}
	jitter_control_init(&session->rtp.jittctl,milisec,payload);
}

void rtp_session_enable_adaptive_jitter_compensation(RtpSession *session, gboolean val){
	jitter_control_enable_adaptive(&session->rtp.jittctl,val);
}

gboolean rtp_session_adaptive_jitter_compensation_enabled(RtpSession *session){
	return session->rtp.jittctl.adaptive;
}
