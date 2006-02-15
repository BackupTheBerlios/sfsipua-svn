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
#include "rtpmod.h"
#include "jitterctl.h"

extern void rtp_session_update_payload_type(RtpSession * session, int pt);


void split_and_queue(queue_t *q, int maxrqsz, mblk_t *mp, rtp_header_t *rtp, int *discarded)
{
	mblk_t *mdata,*tmp;
	int header_size;
	*discarded=0;
	header_size=RTP_FIXED_HEADER_SIZE+ (4*rtp->cc);
	if ((mp->b_wptr - mp->b_rptr)==header_size){
		ortp_debug("Rtp packet contains no data.");
		(*discarded)++;
		freemsg(mp);
		return;
	}
	/* creates a new mblk_t to be linked with the rtp header*/
	mdata=dupb(mp);
	
	mp->b_wptr=mp->b_rptr+header_size;
	mdata->b_rptr+=header_size;
	/* link proto with data */
	mp->b_cont=mdata;
	/* and then add the packet to the queue */
	
	rtp_putq(q,mp);
	/* make some checks: q size must not exceed RtpStream::max_rq_size */
	while (q->q_mcount > maxrqsz)
	{
		/* remove the oldest mblk_t */
		tmp=getq(q);
		if (mp!=NULL)
		{
			ortp_debug("rtp_putq: Queue is full. Discarding message with ts=%i",((rtp_header_t*)mp->b_rptr)->timestamp);
			freemsg(tmp);
			(*discarded)++;
		}
	}
}


void rtp_parse(RtpSession *session, mblk_t *mp, guint32 local_str_ts)
{
	gint i;
	rtp_header_t *rtp;
	int msgsize;
	RtpStream *rtpstream=&session->rtp;
	rtp_stats_t *stats=&rtpstream->stats;
	
	g_return_if_fail(mp!=NULL);
	
	ortp_global_stats.packet_recv++;
	stats->packet_recv++;
	msgsize=msgdsize(mp);
	ortp_global_stats.hw_recv+=msgsize;
	stats->hw_recv+=msgsize;
	
	session->rtp.hwrcv_since_last_SR++;
	
	rtp=(rtp_header_t*)mp->b_rptr;
	if (rtp->version!=2)
	{
		ortp_debug("Receiving rtp packet with version number !=2...discarded");
		stats->bad++;
		ortp_global_stats.bad++;
		freemsg(mp);
		return;
	}
	
	/* convert all header data from network order to host order */
	rtp->seq_number=ntohs(rtp->seq_number);
	rtp->timestamp=ntohl(rtp->timestamp);
	rtp->ssrc=ntohl(rtp->ssrc);
	/* convert csrc if necessary */
	if (rtp->cc*sizeof(guint32) > (msgsize-RTP_FIXED_HEADER_SIZE)){
		ortp_debug("Receiving too short rtp packet.");
		stats->bad++;
		ortp_global_stats.bad++;
		freemsg(mp);
		return;
	}
	for (i=0;i<rtp->cc;i++)
		rtp->csrc[i]=ntohl(rtp->csrc[i]);
	if (session->recv_ssrc!=0)
	{
		/*the ssrc is set, so we must check it */
		if (session->recv_ssrc!=rtp->ssrc){
			/*ortp_debug("rtp_parse: bad ssrc - %i",rtp->ssrc);*/
			session->recv_ssrc=rtp->ssrc;
			rtp_signal_table_emit(&session->on_ssrc_changed);
		}
	}else session->recv_ssrc=rtp->ssrc;
	
	/* update some statistics */
	if (rtp->seq_number>rtpstream->hwrcv_extseq.split.lo){
		rtpstream->hwrcv_extseq.split.lo=rtp->seq_number;
	}else if (rtp->seq_number<200 && rtpstream->hwrcv_extseq.split.lo>((1<<16) - 200)){
		/* this is a check for sequence number looping */
		rtpstream->hwrcv_extseq.split.lo=rtp->seq_number;
		rtpstream->hwrcv_extseq.split.hi++;
	}
	
	/* check for possible telephone events */
	if (rtp->paytype==session->telephone_events_pt){
		split_and_queue(&session->rtp.tev_rq,session->rtp.max_rq_size,mp,rtp,&i);
		stats->discarded+=i;
		ortp_global_stats.discarded+=i;
		return;
	}
	
	/* check for possible payload type change, in order to update accordingly our clock-rate dependant
	parameters */
	if (session->hw_recv_pt!=rtp->paytype){
		rtp_session_update_payload_type(session,rtp->paytype);
	}
	
	if (!(session->flags & RTP_SESSION_RECV_SYNC)){
		gint32 slide=0;
		gint32 safe_delay=0;
		jitter_control_new_packet(&session->rtp.jittctl,rtp->timestamp,local_str_ts,&slide,&safe_delay);
		
		session->rtp.rcv_diff_ts=session->rtp.hwrcv_diff_ts + slide - safe_delay;
		ortp_debug("  rcv_diff_ts=%i", session->rtp.rcv_diff_ts);
		
		/* detect timestamp important jumps in the future, to workaround stupid rtp senders */
		if (RTP_TIMESTAMP_IS_NEWER_THAN(rtp->timestamp,session->rtp.rcv_last_ts+session->rtp.ts_jump)){
			ortp_debug("rtp_parse: timestamp jump ?");
			rtp_signal_table_emit2(&session->on_timestamp_jump,&rtp->timestamp);
		}
		else if (RTP_TIMESTAMP_IS_NEWER_THAN(session->rtp.rcv_last_ts,rtp->timestamp)){
			/* avoid very old packet to enqueued, because the user is no more supposed to get them */
			ortp_debug("rtp_parse: silently discarding very old packet (ts=%i)",rtp->timestamp);
			freemsg(mp);
			stats->outoftime++;
			ortp_global_stats.outoftime++;
			return;
		}
		
	}
	
	split_and_queue(&session->rtp.rq,session->rtp.max_rq_size,mp,rtp,&i);
	stats->discarded+=i;
	ortp_global_stats.discarded+=i;
}
