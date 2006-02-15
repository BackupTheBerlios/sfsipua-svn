/*
  The oRTP library is an RTP (Realtime Transport Protocol - rfc1889) stack.
  Copyright (C) 2001  Simon MORLAT simon.morlat@linphone.org

  This source code file was written by Nicola Baldo as an extension of 
  the oRTP library. Copyright (C) 2005 Nicola Baldo nicola@baldo.biz

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



void report_block_parse(RtpSession *session, report_block_t *rb, struct timeval rcv_time_tv)
{   		
  rb->ssrc = ntohl(rb->ssrc);

  if ( rb->ssrc != session->send_ssrc )

    {
      ortp_debug("Received rtcp report block related to unknown ssrc (not from us)... discarded");
      return;
    }	    

  else

    {
      guint32 rcv_time_msw;	   
      guint32 rcv_time_lsw;
      guint32 rcv_time;
      double rtt;

      rcv_time_msw = rcv_time_tv.tv_sec;
      rcv_time_lsw = (guint32) ((double)rcv_time_tv.tv_usec*(double)(1LL<<32)*1.0e-6);
      rcv_time = (rcv_time_msw<<16) | (rcv_time_lsw >> 16);

      rb->cum_num_packet_lost = ntoh24(rb->cum_num_packet_lost);
      rb->ext_high_seq_num_rec = ntohl(rb->ext_high_seq_num_rec);
      rb->interarrival_jitter = ntohl(rb->interarrival_jitter);
      rb->lsr = ntohl(rb->lsr);
      rb->delay_snc_last_sr = ntohl(rb->delay_snc_last_sr);

		  
      /* calculating Round Trip Time*/ 
      if (rb->lsr != 0)
	{
	  rtt = (double) (rcv_time - rb->delay_snc_last_sr - rb->lsr);
	  rtt = rtt/65536;	  
	  //printf("RTT = %f s\n",rtt);
	}

    }

}


void rtcp_parse(RtpSession *session, mblk_t *mp)
{
  rtcp_common_header_t *rtcp;
  int msgsize;
  int rtcp_pk_size;
  RtpStream *rtpstream=&session->rtp;
  struct timeval rcv_time_tv;

  
  gettimeofday(&rcv_time_tv,NULL);
	
  g_return_if_fail(mp!=NULL);
	
  msgsize=mp->b_wptr-mp->b_rptr;

 

  if (msgsize < RTCP_COMMON_HEADER_SIZE)
    {
      ortp_debug("Receiving too short rtcp packet... discarded");
      return;
    }

  rtcp=(rtcp_common_header_t *)mp->b_rptr;


  /* compound rtcp packet can be composed by more than one rtcp message */
  while (msgsize >= RTCP_COMMON_HEADER_SIZE)

    {      

      if (rtcp->version!=2)
	{
	  ortp_debug("Receiving rtcp packet with version number !=2...discarded");
	  return;
	}
	
      /* convert header data from network order to host order */
      rtcp->length = ntohs(rtcp->length);


      switch (rtcp->packet_type)   

	{

	case RTCP_SR:

	  {
	    rtcp_sr_t *sr = (rtcp_sr_t *) rtcp;
	    report_block_t *rb;
	    int i;

	    if ( ntohl(sr->ssrc) != session->recv_ssrc )
	      {
		ortp_debug("Receiving rtcp sr packet from unknown ssrc.. discarded");		
		return;
	      }	    

	    if (msgsize < RTCP_COMMON_HEADER_SIZE + RTCP_SSRC_FIELD_SIZE + RTCP_SENDER_INFO_SIZE + (RTCP_REPORT_BLOCK_SIZE*sr->ch.rc))
	      {
		ortp_debug("Receiving too short rtcp sr packet... discarded");
		return;
	      }	    

	    /* parsing RTCP Sender Info */ 
	    sr->si.ntp_timestamp_msw = ntohl(sr->si.ntp_timestamp_msw);
	    sr->si.ntp_timestamp_lsw = ntohl(sr->si.ntp_timestamp_lsw);
	    sr->si.rtp_timestamp = ntohl(sr->si.rtp_timestamp);
	    sr->si.senders_packet_count = ntohl(sr->si.senders_packet_count);
	    sr->si.senders_octet_count = ntohl(sr->si.senders_octet_count);	    

	    /* saving data to fill LSR and DLSR field in next RTCP report to be transmitted  */
	    rtpstream->last_rcv_SR_ts = (sr->si.ntp_timestamp_msw << 16) | (sr->si.ntp_timestamp_lsw >> 16);  
	    rtpstream->last_rcv_SR_time.tv_usec = rcv_time_tv.tv_usec;
	    rtpstream->last_rcv_SR_time.tv_sec = rcv_time_tv.tv_sec;	    	    


	    /* parsing all RTCP report blocks */    	  
	    for (i=0; i<sr->ch.rc; i++)
	      { 
		rb = &(sr->rb[i]);		
		report_block_parse(session, rb, rcv_time_tv);		
	      }

	  }
	  break;



	case RTCP_RR:

	  {
	    rtcp_rr_t *rr = (rtcp_rr_t *) rtcp;
	    report_block_t *rb;
	    int i;

	    if ( ntohl(rr->ssrc) != session->recv_ssrc )
	      {
		ortp_debug("Receiving rtcp rr packet from unknown ssrc.. discarded");
		return;
	      }

	    if (msgsize < RTCP_COMMON_HEADER_SIZE + RTCP_SSRC_FIELD_SIZE + (RTCP_REPORT_BLOCK_SIZE*rr->ch.rc))
	      {
		ortp_debug("Receiving too short rtcp sr packet... discarded");
		return;
	      }	    

	    /* parsing all RTCP report blocks */    	  
	    for (i=0; i<rr->ch.rc; i++)
	      { 
		rb = &(rr->rb[i]);		
		report_block_parse(session, rb, rcv_time_tv);		
	      }
  
	  }
	  break;
	  
	  
	case RTCP_SDES: 
	  /* to be implemented */
	  break;
	  	  
	  
	case RTCP_BYE:
	  /* to be implemented */
	  break;
	  
	  
	case RTCP_APP:
	  /* to be implemented */
	  break;

	  
	default:

	  ortp_debug("Receiving unknown rtcp packet type... discarded");
	  return;

	}

      
      rtcp_pk_size = ((rtcp->length)+1)*4;  /* current RTCP packet size, in octets */
      msgsize -= rtcp_pk_size;              /* size of unparsed portion of UDP packet, in octets */
      rtcp = (rtcp_common_header_t *) (rtcp_pk_size + (char *) rtcp);  /* pointer to next RTCP packet in current UDP packet */

    }
}
