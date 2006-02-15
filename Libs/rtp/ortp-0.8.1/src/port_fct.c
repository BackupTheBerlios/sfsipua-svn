
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

/* port_fct.h.  define methods to help for portability between unix and win32 */

#include <unistd.h>

#include <ortp/rtpport.h>
#include "port_fct.h"



/*
 * this method is an utility method that calls fnctl() on UNIX or
 * ioctlsocket on Win32.
 * int retrun the result of the system method
 */
int set_non_blocking_socket (gint sock)
{
	

#ifndef _WIN32
	return fcntl (sock, F_SETFL, O_NONBLOCK);
#else
	unsigned long nonBlock = 1;
	return ioctlsocket(sock, FIONBIO , &nonBlock);
#endif
}


/*
 * this method is an utility method that calls close() on UNIX or
 * closesocket on Win32.
 * int retrun the result of the system method
 */
#ifndef _WIN32
	int close_socket(gint sock)
	{
		return close (sock);
	}
#else
	int close_socket(SOCKET sock)
	{
		return closesocket(sock);
	}
#endif



/*
 * getSocketError() return a string describing the error
 */
#ifdef _WIN32
char *getSocketError()
{
	int error = WSAGetLastError ();
	static char buf[80];

	switch (error)
	{
		case WSANOTINITIALISED: return "Windows sockets not initialized : call WSAStartup";
		case WSAEADDRINUSE:		return "Local Address already in use";
		case WSAEADDRNOTAVAIL:	return "The specified address is not a valid address for this machine";
//		case WSAEFAULT:			return "";
//		case WSAEINPROGRESS:	return "";
		case WSAEINVAL:			return "The socket is already bound to an address.";
		case WSAENOBUFS:		return "Not enough buffers available, too many connections.";
		case WSAENOTSOCK:		return "The descriptor is not a socket.";
		case WSAECONNRESET:		return "Connection reset by peer";
/*

		case : return "";
		case : return "";
		case : return "";
		case : return "";
		case : return "";
		case : return "";
*/
		default :
			sprintf (buf,"Error code : %d", error);
			return buf;
		break;
	}

	return buf;

}
#endif

#ifndef _WIN32
	/* Use UNIX inet_aton method */
#else
	int inet_aton (const char * cp, struct in_addr * addr)
	{
		unsigned long retval;
		
		retval = inet_addr (cp);

		if (retval == INADDR_NONE) 
		{
			return -1;
		}
		else
		{
			addr->S_un.S_addr = retval;
			return 1;
		}
	}
#endif

#ifndef HAVE_GLIB		

char * g_strdup_vprintf(const char *fmt, va_list ap)
{
	/* Guess we need no more than 100 bytes. */
	int n, size = 100;
	char *p;
	if ((p = g_malloc (size)) == NULL)
		return NULL;
	while (1)
	{
		/* Try to print in the allocated space. */
		n = vsnprintf (p, size, fmt, ap);
		/* If that worked, return the string. */
		if (n > -1 && n < size)
			return p;
		//printf("Reallocing space.\n");
		/* Else try again with more space. */
		if (n > -1)	/* glibc 2.1 */
			size = n + 1;	/* precisely what is needed */
		else		/* glibc 2.0 */
			size *= 2;	/* twice the old size */
		if ((p = g_realloc (p, size)) == NULL)
			return NULL;
	}
}	



extern void ortp_log(const gchar *log_domain,GLogLevelFlags log_level,
                                           const gchar *message,
                                           gpointer user_data);

static GLogFunc __log_func=ortp_log;
static gpointer __log_user_data=(gpointer)NULL;

void g_log(const gchar *log_domain,GLogLevelFlags log_level,const gchar *format,...){
	va_list args;
	va_start(args,format);
	g_logv(log_domain,log_level,format,args);
	va_end(args);
}

void g_logv(const gchar *log_domain,GLogLevelFlags log_level,const gchar *format,va_list args){
	gchar *msg;
	msg=g_strdup_vprintf(format,args);
	__log_func(log_domain,log_level,msg,__log_user_data);
	g_free(msg);
}

void g_log_set_handler(const gchar *log_domain,GLogLevelFlags log_levels, GLogFunc log_func, gpointer user_data){
	__log_func=log_func;
	__log_user_data=user_data;
}
	
#endif
