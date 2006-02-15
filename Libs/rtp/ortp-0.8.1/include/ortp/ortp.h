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


#ifndef ORTP_H
#define ORTP_H

#include <ortp/rtpsession.h>
#include <ortp/sessionset.h>

#ifdef __cplusplus
extern "C"
{
#endif
gboolean ortp_min_version_required(int major, int minor, int micro);
void ortp_init();
void ortp_scheduler_init();
void ortp_exit();


void ortp_set_debug_file(gchar *domain, FILE *file);
/* domain is ignored when not compiling with glib support */
void ortp_set_log_handler(const gchar *domain, GLogFunc func, gpointer ud);

extern rtp_stats_t ortp_global_stats;

void ortp_global_stats_reset();
rtp_stats_t *ortp_get_global_stats();

void ortp_global_stats_display();
void rtp_stats_display(rtp_stats_t *stats, char *header);
void rtp_stats_reset(rtp_stats_t *stats);

#ifdef __cplusplus
}
#endif

#endif
