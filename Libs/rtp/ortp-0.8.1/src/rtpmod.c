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




#include <ortp/rtp.h>
#include "rtpmod.h"

#define RTP_SEQ_IS_GREATER(seq1,seq2)\
	((guint16)((guint16)(seq1) - (guint16)(seq2))< (guint16)(1<<15))

/* put an rtp packet in queue. It is called by rtp_parse()*/
void rtp_putq(queue_t *q, mblk_t *mp)
{
	mblk_t *tmp;
	rtp_header_t *rtp=(rtp_header_t*)mp->b_rptr,*tmprtp;
	/* insert message block by increasing time stamp order : the last (at the bottom)
		message of the queue is the newest*/
	ortp_debug("rtp_putq(): Enqueuing packet with ts=%i and seq=%i",rtp->timestamp,rtp->seq_number);
	
	if (qempty(q)) {
		putq(q,mp);
		return;
	}
	tmp=qlast(q);
	/* we look at the queue from bottom to top, because enqueued packets have a better chance
	to be enqueued at the bottom, since there are surely newer */
	while (!qend(q,tmp))
	{
		tmprtp=(rtp_header_t*)tmp->b_rptr;
		ortp_debug("rtp_putq(): Seeing packet with seq=%i",tmprtp->seq_number);
		
 		if (rtp->seq_number == tmprtp->seq_number)
 		{
 			/* this is a duplicated packet. Don't queue it */
 			ortp_debug("rtp_putq: duplicated message.");
 			freemsg(mp);
 			return;
		}else if (RTP_SEQ_IS_GREATER(rtp->seq_number,tmprtp->seq_number)){
			
			insq(q,tmp->b_next,mp);
			return;
 		}
		tmp=tmp->b_prev;
	}
	/* this packet is the oldest, it has to be 
	placed on top of the queue */
	insq(q,qfirst(q),mp);
	
}



mblk_t *rtp_getq(queue_t *q,guint32 timestamp, int *rejected)
{
	mblk_t *tmp,*ret=NULL,*old;
	rtp_header_t *tmprtp;
	guint32 oldest;
	guint32 ts_found=0;
	
	*rejected=0;
	ortp_debug("rtp_getq(): Timestamp %i wanted.",timestamp);

	if (qempty(q))
	{
		/*ortp_debug("rtp_getq: q is empty.");*/
		return NULL;
	}
	/* prevent somebody to ask for a timestamp that is older than the oldest of the queue */
	oldest=((rtp_header_t*) qfirst(q)->b_rptr)->timestamp;
	if (RTP_TIMESTAMP_IS_STRICTLY_NEWER_THAN(oldest,timestamp))
	{
		ortp_debug("rtp_getq(): asking for too old packet ! oldest=%i",oldest);
		return NULL;
	}
	ret=NULL;
	old=NULL;
	/* return the packet with ts just equal or older than the asked timestamp */
	while ((tmp=qfirst(q))!=NULL)
	{
		tmprtp=(rtp_header_t*)tmp->b_rptr;
		ortp_debug("rtp_getq: Seeing packet with ts=%i",tmprtp->timestamp);
		if ( RTP_TIMESTAMP_IS_NEWER_THAN(timestamp,tmprtp->timestamp) )
		{
			if (ret!=NULL && tmprtp->timestamp==ts_found) {
				/* we've found two packets with same timestamp. return the first one */
				break;
			}
			if (old!=NULL) {
				ortp_debug("rtp_getq: discarding too old packet with ts=%i",ts_found);
				(*rejected)++;
				freemsg(old);
			}
			ret=getq(q); /* dequeue the packet, since it has an interesting timestamp*/
			ts_found=tmprtp->timestamp;
			ortp_debug("rtp_getq: Found packet with ts=%i",tmprtp->timestamp);
			old=ret;
		}
		else
		{
			break;
		}
	}
	return ret;
}
