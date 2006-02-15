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


#ifndef RTP_H
#define RTP_H

#include <ortp/rtpport.h>

#define IPMAXLEN 20
#define UDP_MAX_SIZE 65536
#define RTP_FIXED_HEADER_SIZE 12
#define RTP_DEFAULT_JITTER_TIME 80	/*miliseconds*/



typedef struct rtp_header
{
#ifdef WORDS_BIGENDIAN
	guint16 version:2;
	guint16 padbit:1;
	guint16 extbit:1;
	guint16 cc:4;
	guint16 markbit:1;
	guint16 paytype:7;
#else
	guint16 cc:4;
	guint16 extbit:1;
	guint16 padbit:1;
	guint16 version:2;
	guint16 paytype:7;
	guint16 markbit:1;
#endif
	guint16 seq_number;
	guint32 timestamp;
	guint32 ssrc;
	guint32 csrc[16];
} rtp_header_t;




typedef struct rtp_stats
{
	guint64 packet_sent;
	guint64 sent;		/* bytes sent */
	guint64 recv; 		/* bytes of payload received and delivered in time to the application */
	guint64 hw_recv;		/* bytes of payload received */
	guint64 packet_recv;	/* number of packets received */
	guint64 unavaillable;	/* packets not availlable when they were queried */
	guint64 outoftime;		/* number of packets that were received too late */
	guint64 skipped;		/* number of packets skipped (that the application never queried 
											or that need to be skipped in order to compensate a clock slide (see adaptive jitter control)) */
	guint64 cum_packet_loss; /* cumulative number of packet lost */
	guint64 bad;			/* packets that did not appear to be RTP */
	guint64 discarded;		/* incoming packets discarded because the queue exceeds its max size */
} rtp_stats_t;

#define RTP_TIMESTAMP_IS_NEWER_THAN(ts1,ts2) \
	((guint32)((guint32)(ts1) - (guint32)(ts2))< (guint32)(1<<31))

#define RTP_TIMESTAMP_IS_STRICTLY_NEWER_THAN(ts1,ts2) \
	( ((guint32)((guint32)(ts1) - (guint32)(ts2))< (guint32)(1<<31)) && (ts1)!=(ts2) )

#define TIME_IS_NEWER_THAN(t1,t2) RTP_TIMESTAMP_IS_NEWER_THAN(t1,t2)

#define TIME_IS_STRICTLY_NEWER_THAN(t1,t2) RTP_TIMESTAMP_IS_STRICTLY_NEWER_THAN(t1,t2)

#endif
