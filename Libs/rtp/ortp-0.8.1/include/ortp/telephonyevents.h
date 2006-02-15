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

#ifndef TELEPHONYEVENTS_H
#define TELEPHONYEVENTS_H


#include <ortp/rtpsession.h>


struct _telephone_event
{
#ifdef WORDS_BIGENDIAN
	guint32 event:8;
	guint32 E:1;
	guint32 R:1;
	guint32 volume:6;
	guint32 duration:16;
#else
	guint32 event:8;
	guint32 volume:6;
	guint32 R:1;
	guint32 E:1;
	guint32 duration:16;
#endif
};

typedef struct _telephone_event telephone_event_t;

#ifdef __cplusplus
extern "C" {
#endif

extern PayloadType	payload_type_telephone_event;

/* tell if the session supports telephony events. For this the telephony events payload_type 
	must be present in the rtp profile used by the session */
	
/* low level functions */	
gint rtp_session_telephone_events_supported(RtpSession *session);

mblk_t	*rtp_session_create_telephone_event_packet(RtpSession *session, int start);

gint rtp_session_add_telephone_event(RtpSession *session,
			mblk_t *packet, guchar event, gint end, guchar volume, guint16 duration);
			
gint rtp_session_read_telephone_event(RtpSession *session,
		mblk_t *packet,telephone_event_t **tab);

/* high level functions*/
gint rtp_session_send_dtmf(RtpSession *session, gchar dtmf, guint32 userts);
/* for high level telephony event callback */
void rtp_session_check_telephone_events(RtpSession *session, mblk_t *m0);

#ifdef __cplusplus
}
#endif
	
/* the size allocated for telephony events packets */
#define TELEPHONY_EVENTS_ALLOCATED_SIZE		(4*sizeof(telephone_event_t))

/* list of named events */
#define TEV_DTMF_0			(0)
#define TEV_DTMF_1			(1)
#define TEV_DTMF_2			(2)
#define TEV_DTMF_3			(3)
#define TEV_DTMF_4			(4)
#define TEV_DTMF_5			(5)
#define TEV_DTMF_6			(6)
#define TEV_DTMF_7			(7)
#define TEV_DTMF_8			(8)
#define TEV_DTMF_9			(9)
#define TEV_DTMF_STAR		(10)
#define TEV_DTMF_POUND		(11)
#define TEV_DTMF_A			(12)
#define TEV_DTMF_B			(13)
#define TEV_DTMF_C			(14)
#define TEV_DTMF_D			(15)
#define TEV_FLASH			(16)


#endif
