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
 *            rtcp.c
 *
 *  Wed Dec  1 11:45:30 2004
 *  Copyright  2004  Simon Morlat
 *  Email simon dot morlat at linphone dot org
 ****************************************************************************/

#include <ortp/rtpsession.h>
#include <ortp/rtcp.h>

extern gint ortp_rtcp_send (RtpSession * session, mblk_t * m);


void rtcp_common_header_init(rtcp_common_header_t *ch, RtpSession *s,int type, int rc, int bytes_len){
	rtcp_common_header_set_version(ch,2);
	rtcp_common_header_set_padbit(ch,0);
	rtcp_common_header_set_packet_type(ch,type);
	rtcp_common_header_set_rc(ch,rc);	/* as we don't yet support multi source receiving */
	rtcp_common_header_set_length(ch,(bytes_len/4)-1);
}

mblk_t *sdes_chunk_new(guint32 ssrc){
	mblk_t *m=allocb(RTCP_SDES_CHUNK_DEFAULT_SIZE,0);
	sdes_chunk_t *sc=(sdes_chunk_t*)m->b_rptr;
	sc->csrc=htonl(ssrc);
	m->b_wptr+=sizeof(sc->csrc);
	return m;
}


mblk_t * sdes_chunk_append_item(mblk_t *m, rtcp_sdes_type_t sdes_type, const gchar *content)
{	
	if ( content )
	{
		sdes_item_t si;
		si.item_type=sdes_type;
		si.len=MIN(strlen(content),RTCP_SDES_MAX_STRING_SIZE);
		m=appendb(m,(char*)&si,RTCP_SDES_ITEM_HEADER_SIZE,FALSE);
		m=appendb(m,content,si.len,FALSE);
	}
	return m;
}

void sdes_chunk_set_ssrc(mblk_t *m, guint32 ssrc){
	sdes_chunk_t *sc=(sdes_chunk_t*)m->b_rptr;
	sc->csrc=htonl(ssrc);
}

#define sdes_chunk_get_ssrc(m) ntohl(((sdes_chunk_t*)((m)->b_rptr))->csrc)

mblk_t * sdes_chunk_pad(mblk_t *m){
	return appendb(m,NULL,0,TRUE);
}

void rtp_session_set_source_description(RtpSession *session, 
    const gchar *cname, const gchar *name, const gchar *email, const gchar *phone, 
    const gchar *loc, const gchar *tool, const gchar *note){
	mblk_t *chunk = sdes_chunk_new(session->send_ssrc);
	mblk_t *m=chunk;
	const gchar *_cname=cname;
	if (_cname==NULL)
	{
		_cname="Unknown";
	}
	chunk=sdes_chunk_append_item(chunk, RTCP_SDES_CNAME, _cname);
	chunk=sdes_chunk_append_item(chunk, RTCP_SDES_NAME, name);
	chunk=sdes_chunk_append_item(chunk, RTCP_SDES_EMAIL, email);
	chunk=sdes_chunk_append_item(chunk, RTCP_SDES_PHONE, phone);
	chunk=sdes_chunk_append_item(chunk, RTCP_SDES_LOC, loc);
	chunk=sdes_chunk_append_item(chunk, RTCP_SDES_TOOL, tool);
	chunk=sdes_chunk_append_item(chunk, RTCP_SDES_NOTE, note);
	chunk=sdes_chunk_pad(chunk);
	rtp_session_lock(session);
	if (session->sd!=NULL) freemsg(session->sd);
	session->sd=m;
	rtp_session_unlock(session);
}

void
rtp_session_add_contributing_source(RtpSession *session, guint32 csrc, 
    const gchar *cname, const gchar *name, const gchar *email, const gchar *phone, 
    const gchar *loc, const gchar *tool, const gchar *note)
{
	mblk_t *chunk = sdes_chunk_new(csrc);
	mblk_t *m=chunk;
	gchar *_cname=(gchar*)cname;
	if (_cname==NULL)
	{
		_cname="toto";
	}
	chunk=sdes_chunk_append_item(chunk, RTCP_SDES_CNAME, cname);
	chunk=sdes_chunk_append_item(chunk, RTCP_SDES_NAME, name);
	chunk=sdes_chunk_append_item(chunk, RTCP_SDES_EMAIL, email);
	chunk=sdes_chunk_append_item(chunk, RTCP_SDES_PHONE, phone);
	chunk=sdes_chunk_append_item(chunk, RTCP_SDES_LOC, loc);
	chunk=sdes_chunk_append_item(chunk, RTCP_SDES_TOOL, tool);
	chunk=sdes_chunk_append_item(chunk, RTCP_SDES_NOTE, note);
	chunk=sdes_chunk_pad(chunk);
	rtp_session_lock(session);
	putq(&session->contributing_sources,m);
	rtp_session_unlock(session);
}



mblk_t* rtp_session_create_rtcp_sdes_packet(RtpSession *session)
{
    mblk_t *mp=allocb(sizeof(rtcp_common_header_t),0);
	rtcp_common_header_t *rtcp;
    mblk_t *tmp,*m=mp;
	queue_t *q;
	int rc=0;
    rtcp = (rtcp_common_header_t*)mp->b_wptr;
	mp->b_wptr+=sizeof(rtcp_common_header_t);
	
	/* concatenate all sdes chunks */
	sdes_chunk_set_ssrc(session->sd,session->send_ssrc);
	m=concatb(m,dupmsg(session->sd));
	rc++;
	
	q=&session->contributing_sources;
    for (tmp=qbegin(q); !qend(q,tmp); tmp=qnext(q,mp)){
		m=concatb(m,dupmsg(tmp));
		rc++;
	}
	rtcp_common_header_init(rtcp,session,RTCP_SDES,rc,msgdsize(mp));
    return mp;
}
 

mblk_t *rtcp_create_simple_bye_packet(guint32 ssrc, const gchar *reason)
{	
	gint strsize=0;
    gint packet_size;
	mblk_t *mp;
	rtcp_bye_t *rtcp;
	packet_size	= RTCP_BYE_HEADER_SIZE + 1 + strsize;
	if (reason!=NULL)
		strsize=MIN(strlen(reason),RTCP_BYE_REASON_MAX_STRING_SIZE);
	mp	= allocb(packet_size, 0);
	
    rtcp = (rtcp_bye_t*)mp->b_rptr;

	rtcp_common_header_init(&rtcp->ch,NULL,RTCP_BYE,1,packet_size);
	rtcp->ssrc[0] = htonl(ssrc);
    mp->b_wptr += packet_size;
	/* append the reason if any*/
	if (reason!=NULL)
		appendb(mp,reason,strsize,FALSE);
	return mp;
}

void rtp_session_remove_contributing_sources(RtpSession *session, guint32 ssrc)
{
	queue_t *q=&session->contributing_sources;
	mblk_t *tmp;
	for (tmp=qbegin(q); !qend(q,tmp); tmp=qnext(q,tmp)){
		guint32 csrc=sdes_chunk_get_ssrc(tmp);
		if (csrc==ssrc) {
			remq(q,tmp);
			break;
		}
	}
	tmp=rtcp_create_simple_bye_packet(ssrc, NULL);
	ortp_rtcp_send(session,tmp);
}

void sender_info_init(sender_info_t *info, RtpSession *session){
	struct timeval tv;
	guint32 tmp;
	gettimeofday(&tv,NULL);
	info->ntp_timestamp_msw=htonl(tv.tv_sec + 0x83AA7E80); /* 0x83AA7E80 is the number of seconds from 1900 to 1970 */
	tmp=(guint32)((double)tv.tv_usec*(double)(1LL<<32)*1.0e-6);
	info->ntp_timestamp_lsw=htonl(tmp);
	info->rtp_timestamp=htonl(session->rtp.snd_last_ts);
	info->senders_packet_count=htonl(session->rtp.stats.packet_sent);
	info->senders_octet_count=htonl(session->rtp.stats.sent);
}



void report_block_init(report_block_t *b, RtpSession *session){
	guint packet_loss=0;
	guint8 loss_fraction=0;
	RtpStream *stream=&session->rtp;
	guint32 delay_snc_last_sr=0;
	
	/* compute the statistics */
	/*printf("hwrcv_extseq.one=%u, hwrcv_seq_at_last_SR=%u hwrcv_since_last_SR=%u\n",
		stream->hwrcv_extseq.one,
		stream->hwrcv_seq_at_last_SR,
		stream->hwrcv_since_last_SR
		);*/
	if (stream->hwrcv_seq_at_last_SR!=0){
		packet_loss=(stream->hwrcv_extseq.one - stream->hwrcv_seq_at_last_SR) - stream->hwrcv_since_last_SR;
		stream->stats.cum_packet_loss+=packet_loss;
		loss_fraction=(int)(256.0*(float)packet_loss/(float)stream->hwrcv_since_last_SR);
	}
	/* reset them */
	stream->hwrcv_since_last_SR=0;
	stream->hwrcv_seq_at_last_SR=stream->hwrcv_extseq.one;
	
	if (stream->last_rcv_SR_time.tv_sec!=0){
		struct timeval now;
		gfloat delay;
		gettimeofday(&now,NULL);
		delay=((now.tv_sec-stream->last_rcv_SR_time.tv_sec)*1e6 ) + (now.tv_usec-stream->last_rcv_SR_time.tv_usec);
		delay=delay*65536*1e-6;
		delay_snc_last_sr=(guint32) delay;
	}
	
	b->ssrc=htonl(session->recv_ssrc);
	b->fraction_lost=loss_fraction;
	b->cum_num_packet_lost=hton24(stream->stats.cum_packet_loss);
	b->interarrival_jitter=htonl((guint32) stream->jittctl.inter_jitter);
	b->ext_high_seq_num_rec=htonl(stream->hwrcv_extseq.one);
	b->lsr=htonl(stream->last_rcv_SR_ts);
	b->delay_snc_last_sr=htonl(delay_snc_last_sr);
}



int rtcp_sr_init(RtpSession *session, char *buf, int size){
	rtcp_sr_t *sr=(rtcp_sr_t*)buf;
	if (size<sizeof(rtcp_sr_t)) return -1;
	rtcp_common_header_init(&sr->ch,session,RTCP_SR,1,sizeof(rtcp_sr_t));
	sr->ssrc=htonl(session->send_ssrc);
	sender_info_init(&sr->si,session);
	report_block_init(&sr->rb[0],session);
	return sizeof(rtcp_sr_t);
}

int rtcp_rr_init(RtpSession *session, char *buf, int size){
	rtcp_rr_t *rr=(rtcp_rr_t*)buf;
	if (size<sizeof(rtcp_rr_t)) return -1;
	rtcp_common_header_init(&rr->ch,session,RTCP_RR,1,sizeof(rtcp_sr_t));
	rr->ssrc=htonl(session->send_ssrc);
	report_block_init(&rr->rb[0],session);
	return sizeof(rtcp_rr_t);
}


void __rtp_session_rtcp_process(RtpSession *session){
	mblk_t *cm=NULL;
	mblk_t *sdes=NULL;
	if (session->mode==RTP_SESSION_SENDONLY || session->mode==RTP_SESSION_SENDRECV){
		/* first make a SR packet */
		cm=allocb(sizeof(rtcp_sr_t),0);
		cm->b_wptr+=rtcp_sr_init(session,cm->b_wptr,sizeof(rtcp_sr_t));
		/* make a SDES packet */
		sdes=rtp_session_create_rtcp_sdes_packet(session);
		/* link them */
		cm->b_cont=sdes;
	}else{
		/* make a RR packet */
		cm=allocb(sizeof(rtcp_rr_t),0);
		cm->b_wptr+=rtcp_rr_init(session,cm->b_wptr,sizeof(rtcp_rr_t));
		/* if we are recv-only do we need to add SDES packet ? I don't think so
		as we are not a source	*/
	}
	/* send the compound packet */
	ortp_rtcp_send(session,cm);
	ortp_debug("Rtcp compound message sent.");
}

void rtp_session_rtcp_process(RtpSession *session){
	RtpStream *st=&session->rtp;
	if (st->rcv_last_app_ts - st->last_rtcp_report_snt_r > st->rtcp_report_snt_interval 
		|| st->snd_last_ts - st->last_rtcp_report_snt_s > st->rtcp_report_snt_interval){
		st->last_rtcp_report_snt_r=st->rcv_last_app_ts;
		st->last_rtcp_report_snt_s=st->snd_last_ts;
		__rtp_session_rtcp_process(session);
	}
}
