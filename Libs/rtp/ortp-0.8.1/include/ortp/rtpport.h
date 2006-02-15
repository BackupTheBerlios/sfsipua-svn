/*
  The oRTP LinPhone RTP library intends to provide basics for a RTP stack.
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


/* this file is responsible of the portability of the stack */

#ifndef RTPPORT_H
#define RTPPORT_H

#ifdef UGLIB_H
#define HAVE_GLIB
#endif

#ifndef _WIN32	/* do not include ortp-config.h when we are on win32 */
#	ifdef _ORTP_SOURCE
#		include <ortp-config.h>
#	else
#		include <ortp/ortp-config.h>
#	endif
#else
	#include "ortp-config-win32.h"
#endif

#define INT_TO_POINTER(truc)	((gpointer)(long)(truc))
#define POINTER_TO_INT(truc)	((int)(long)(truc))

/* defines things that should be defined when we have not glib */
#ifndef HAVE_GLIB  

#include <errno.h>
#include <sys/types.h>
#ifdef HAVE_STDINT_H
#include <stdint.h>
#endif

/* integer types */
typedef  uint64_t guint64;
typedef  uint16_t guint16;
typedef  uint32_t guint32;
typedef  signed short gint16;
typedef  int32_t gint32;
typedef  unsigned int guint;
typedef  int gint;
typedef  char gchar;
typedef  unsigned char guchar;
typedef  unsigned char guint8;
typedef  void* gpointer;
typedef int gboolean;
typedef double gdouble;
typedef float gfloat;

#define TRUE 1
#define FALSE 0


/*misc*/
#define g_return_if_fail(expr) if (!(expr)) {printf("%s:%i- assertion" #expr "failed\n",__FILE__,__LINE__); return;}
#define g_return_val_if_fail(expr,ret) if (!(expr)) {printf("%s:%i- assertion" #expr "failed\n",__FILE__,__LINE__); return (ret);}

#include <unistd.h>
#include <stdio.h>
#include <stdarg.h>

typedef enum {
	/* GLib log levels */
  G_LOG_LEVEL_ERROR             = 1 << 2,       /* always fatal */
  G_LOG_LEVEL_CRITICAL          = 1 << 3,
  G_LOG_LEVEL_WARNING           = 1 << 4,
  G_LOG_LEVEL_MESSAGE           = 1 << 5,
  G_LOG_LEVEL_MASK              = ~0

} GLogLevelFlags;

#ifndef G_LOG_DOMAIN
#define G_LOG_DOMAIN ((const gchar*)"")
#endif
#ifdef __cplusplus
extern "C" {
#endif

void g_log(const gchar *log_domain,GLogLevelFlags log_level,const gchar *format,...);
void g_logv(const gchar *log_domain,GLogLevelFlags log_level,const gchar *format,va_list args);
typedef void (*GLogFunc)  (const gchar *log_domain,
                                          GLogLevelFlags log_level,
                                           const gchar *message,
                                           gpointer user_data);
static inline void g_warning(const gchar *fmt,...)
{
  va_list args;
  va_start (args, fmt);
  g_logv (G_LOG_DOMAIN, G_LOG_LEVEL_WARNING, fmt, args);
  va_end (args);
}
static inline void g_error(const gchar *fmt,...)
{
  va_list args;
  va_start (args, fmt);
  g_logv (G_LOG_DOMAIN, G_LOG_LEVEL_ERROR, fmt, args);
  va_end (args);
}
static inline void g_message(const gchar *fmt,...)
{
  va_list args;
  va_start (args, fmt);
  g_logv (G_LOG_DOMAIN, G_LOG_LEVEL_MESSAGE, fmt, args);
  va_end (args);
}
/* in order to simplify, domain is ignored when using the folowing function, ie all logs will go through your handler
whatever the domain is */
void g_log_set_handler(const gchar *domain, GLogLevelFlags levels, GLogFunc func, gpointer ud);

#ifdef __cplusplus
}
#endif

#endif  /* HAVE_GLIB */


#if defined(TIME_WITH_SYS_TIME)
#include <time.h>
#include <sys/time.h>
#elif defined(HAVE_SYS_TIME_H)
#include <sys/time.h>
#endif


#ifdef HAVE_GLIB

#ifndef UGLIB_H
#include <glib.h>
#endif
#include <string.h>


#else /* not HAVE_GLIB */
/* things that in glib, but should only be defined when we are not in the HPUX kernel. */
#include <stdlib.h>
#include <pthread.h>
#include <sched.h>
#include <string.h>

#ifdef ENABLE_MEMCHECK
extern gint ortp_allocations;
#endif

/* memory allocation functions */
static inline void * g_malloc(int sz) 
{
	void *p=malloc(sz);
	if (p==NULL) {
		printf("g_malloc: Failed to allocate %i bytes: %s.\n",sz,strerror(errno));
		abort();
	}
#ifdef ENABLE_MEMCHECK
	ortp_allocations++;
#endif
	return p;
}

static inline void * g_malloc0(int sz) 
{
	void *p=malloc(sz);
	if (p==NULL) {
		printf("g_malloc: Failed to allocate %i bytes: %s.\n",sz,strerror(errno));
		abort();
	}
	memset(p,0,sz);
#ifdef ENABLE_MEMCHECK
	ortp_allocations++;
#endif
	return p;
}

#define g_new(type,count)   (type *)g_malloc(sizeof(type)*(count))
#define g_new0(type, count)	(type *)g_malloc0(sizeof(type)*(count))
#define g_realloc(p,sz) realloc((p),(sz))
static inline void g_free(void *p)
{
#ifdef ENABLE_MEMCHECK
	ortp_allocations--;
#endif
	free(p);
}

#define g_strdup(machin)	strdup(machin)

typedef pthread_mutex_t GMutex;
static inline GMutex * g_mutex_new()
{
	pthread_mutex_t *mutex=g_new(pthread_mutex_t,1);
	pthread_mutex_init(mutex,NULL);
	return mutex;
}
typedef enum
{
  G_THREAD_PRIORITY_LOW,
  G_THREAD_PRIORITY_NORMAL,
  G_THREAD_PRIORITY_HIGH,
  G_THREAD_PRIORITY_URGENT
} GThreadPriority;
typedef pthread_t GThread;
typedef gpointer (*GThreadFunc)(gpointer data);
static inline GThread *g_thread_create(GThreadFunc func, gpointer data, gboolean joinable, void **error){
	GThread *thread=g_new(GThread,1);
	pthread_create(thread,NULL,func,data);
	return thread;
}

static inline void g_thread_join(GThread *thread){
	pthread_join(*thread,NULL);
	g_free(thread);
}

static inline void g_thread_set_priority(GThread *thread,GThreadPriority prio){
	if (prio>G_THREAD_PRIORITY_NORMAL){
		/* this is unsupported on HPUX */
		/*
		struct sched_param param;
		param.sched_priority=1;
		sched_setscheduler(*thread,SCHED_RR,&param);
		*/
	}
}

#define g_mutex_lock(mutex)	  pthread_mutex_lock((mutex))
#define g_mutex_unlock(mutex)  pthread_mutex_unlock((mutex))
#define g_mutex_free(mutex)		pthread_mutex_destroy((mutex));g_free((mutex))

typedef pthread_cond_t GCond;
static inline GCond * g_cond_new()
{
	pthread_cond_t *cond=g_new(pthread_cond_t,1);
	pthread_cond_init(cond,NULL);
	return cond;
}
#define g_cond_wait(cond,mutex)	pthread_cond_wait((cond),(mutex))
#define g_cond_signal(cond)		pthread_cond_signal((cond))
#define g_cond_broadcast(cond)	pthread_cond_broadcast((cond))
#define g_cond_free(cond)		pthread_cond_destroy((cond)); g_free((cond))

#define g_thread_init(vtable)
#define g_thread_supported()	(1)

#endif /* HAVE_GLIB */


#ifndef RTP_DEBUG
#define ortp_debug(...)	
#else
#define ortp_debug	g_message
#endif

#ifdef _WIN32
extern char *getSocketError();
#define getSocketErrorCode()	WSAGetLastError ()
#else
#define getSocketError() strerror(errno)
#define getSocketErrorCode() (errno)
#endif

#ifdef UGLIB_H
#undef HAVE_GLIB
#endif

#undef MIN
#define MIN(a,b) (((a)>(b)) ? (b) : (a))
#undef MAX
#define MAX(a,b) (((a)>(b)) ? (a) : (b))

typedef struct _dwsplit_t{
#ifdef WORDS_BIGENDIAN
	guint16 hi;
	guint16 lo;
#else
	guint16 lo;
	guint16 hi;
#endif
} dwsplit_t;

typedef union{
	dwsplit_t split;
	guint32 one;
} poly32_t;

#ifdef WORDS_BIGENDIAN
#define hton24(x) (x)
#else
#define hton24(x) ((( (x) & 0x00ff0000) >>16) | (( (x) & 0x000000ff) <<16) | ( (x) & 0x0000ff00) )
#endif
#define ntoh24(x) hton24(x)

#endif /*RTPPORT_H*/
