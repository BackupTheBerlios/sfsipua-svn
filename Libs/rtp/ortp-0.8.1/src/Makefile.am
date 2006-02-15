


EXTRA_DIST=export.c export.h

AM_CFLAGS=  -D_ORTP_SOURCE $(PTHREAD_CFLAGS) -DG_LOG_DOMAIN=\"oRTP\" -I$(top_srcdir) $(GLIB_CFLAGS) $(TRUESPEECH_CFLAGS)
AM_LDFLAGS= $(PTHREAD_LDFLAGS)

INCLUDES=-I$(top_srcdir)/include/

lib_LTLIBRARIES = libortp.la

libortp_la_SOURCES=str_utils.c 	\
			port_fct.c port_fct.h \
			rtpmod.c rtpmod.h	\
			rtpparse.c  \
			rtpsession.c \
			jitterctl.c jitterctl.h \
			rtpsignaltable.c  \
			rtptimer.c	rtptimer.h \
			posixtimer.c \
			ortp.c \
			scheduler.c scheduler.h \
			avprofile.c  \
			sessionset.c  \
			telephonyevents.c  \
			ortp-config-win32.h errno-win32.h \
			payloadtype.c \
			rtcp.c  \
			utils.c utils.h \
			rtcpparse.c 


libortp_la_LIBADD=$(GLIB_LIBS) $(PTHREAD_LIBS) -lm

libortp_la_LDFLAGS= -version-info $(LIBORTP_SO_VERSION)


SUBDIRS= . tests
