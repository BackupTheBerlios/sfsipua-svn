dnl Process this file with autoconf to produce a configure script.
AC_INIT(src/rtpmod.c)
AC_CANONICAL_SYSTEM

ORTP_MAJOR_VERSION=0
ORTP_MINOR_VERSION=8
ORTP_MICRO_VERSION=1
ORTP_EXTRA_VERSION=

LIBORTP_SO_CURRENT=2 dnl increment this number when you add/change/remove an interface
LIBORTP_SO_REVISION=0 dnl increment this number when you change source code, without changing interfaces; set to 0 when incrementing CURRENT
LIBORTP_SO_AGE=0 dnl increment this number when you add an interface, set to 0 if you remove an interface

LIBORTP_SO_VERSION=$LIBORTP_SO_CURRENT:$LIBORTP_SO_REVISION:$LIBORTP_SO_AGE
ORTP_VERSION=${ORTP_MAJOR_VERSION}.${ORTP_MINOR_VERSION}.${ORTP_MICRO_VERSION}${ORTP_EXTRA_VERSION}
dnl seems pkg-config doesn't like extra version
ORTP_PKGCONFIG_VERSION=${ORTP_MAJOR_VERSION}.${ORTP_MINOR_VERSION}.${ORTP_MICRO_VERSION}

AC_SUBST(LIBORTP_SO_VERSION)
AC_SUBST(ORTP_VERSION)
AC_SUBST(ORTP_PKGCONFIG_VERSION)


PACKAGE=ortp

AM_INIT_AUTOMAKE($PACKAGE,$ORTP_VERSION,no-define)
AM_CONFIG_HEADER(ortp-config.h)
AC_DEFINE_UNQUOTED(ORTP_MAJOR_VERSION,$ORTP_MAJOR_VERSION, [major version])
AC_DEFINE_UNQUOTED(ORTP_MINOR_VERSION,$ORTP_MINOR_VERSION, [minor version])
AC_DEFINE_UNQUOTED(ORTP_MICRO_VERSION,$ORTP_MICRO_VERSION, [micro version])
AC_DEFINE_UNQUOTED(ORTP_VERSION,"$ORTP_VERSION",[ortp version number])

AC_MSG_CHECKING([warning make an error on compilation])
AC_ARG_ENABLE(ewarning,
[  --enable-ewarning       Enable error on compilation warning [default=yes]],
[wall_werror=$enableval],
[wall_werror=yes]
)


dnl enable ipv6 support
AC_ARG_ENABLE(ipv6,
      [  --enable-ipv6    Turn on ipv6 support],
      [case "${enableval}" in
        yes)  ipv6=true;;
        no)   ipv6=false;;
        *) AC_MSG_ERROR(bad value ${enableval} for --enable-ipv6) ;;
      esac],[ipv6=true])
if test x$ipv6 = xtrue ; then
	AC_DEFINE([INET6],[1],[Defined when ortp is compiled with ipv6 support])
fi

AC_ARG_ENABLE(mode64bit,
			[  --enable-mode64bit=[yes/no]   produce a 64-bit library. [default=no]],
			[case "${enableval}" in
				yes) mode64bit_enabled=yes;;
				no) mode64bit_enabled=no;;
				*) AC_MSG_ERROR("Bad value for --enable-mode64bit");;
			esac],
			[mode64bit_enabled=no])

AC_ARG_ENABLE(debug,
			[  --enable-debug=[yes/no]   enables the display of traces showing the execution of the library. [default=yes]],
			[case "${enableval}" in
				yes) debug_enabled=yes;;
				no) debug_enabled=no;;
				*) AC_MSG_ERROR("Bad value for --enable-debug");;
			esac],
			[debug_enabled=no])



AC_ARG_ENABLE(bigfdset,
			[  --enable-bigfdset=[yes/no]   enables big fd_set (hpux only). [default=no]],
			[case "${enableval}" in
				yes) AC_DEFINE(_USE_BIG_FDS,1,"Define when fd_set should be bigger (hpux only)") ;;
				no) ;;
				*) AC_MSG_ERROR("Bad value for --enable-bigfdset");;
			esac],
			)



hpux_host=no
posixtimer_interval=10000
PTHREAD_LDFLAGS=

case "$host_os" in
	*hpux*) 
		hpux_host=yes
		AC_DEFINE(NOCONNECT,1,[Defined if we should not use connect() on udp sockets])
		CFLAGS="$CFLAGS -D_HPUX_SOURCE -D_XOPEN_SOURCE_EXTENDED -D_XOPEN_SOURCE=500 -D_POSIX_C_SOURCE=199506L"
		LIBS="$LIBS -lxnet"
		;;
	*freebsd*)
		AC_DEFINE(NOCONNECT,1,[Defined if we should not use connect() on udp sockets])
		PTHREAD_LDFLAGS="-pthread"
		;;
esac

dnl Checks for programs.
AC_PROG_CC
AC_PROG_LIBTOOL
AC_ENABLE_SHARED(yes)
AC_ENABLE_STATIC(no)


dnl Checks for libraries.

AC_ARG_ENABLE(glib,
[  --disable-glib         do not compile with glib.],
use_glib=$enableval,use_glib="yes")

if test "x$use_glib" = "xyes"; then
	AM_PATH_GLIB_2_0(2.0.0, [AC_DEFINE(HAVE_GLIB,1,[Defined if we compile against the glib])],[use_glib=no] ,[gthread])
fi

ORTPDEPS_LIBS="$GLIB_LIBS"
ORTPDEPS_CFLAGS="$GLIB_CFLAGS"
ORTPDEPS_LDFLAGS="$GLIB_LDFLAGS"


AM_CONDITIONAL(GLIB_SUPPORT,test "x$use_glib" = "xyes")

if test "$GCC" != "yes" ; then
	if test "$hpux_host" = "yes" ; then
		dnl we are probably using HPUX cc compiler, so add a +O2 to CFLAGS
			CFLAGS="$CFLAGS +O2 -g "
		if test x$mode64bit_enabled = xyes ; then
			CFLAGS="$CFLAGS +DA2.0W +DS2.0"
		fi
	fi
else
	CFLAGS="$CFLAGS -Wall"	
fi

build_scheduler=yes

dnl Check if we have seteuid system call
AC_CHECK_FUNCS(seteuid)

if test "x$use_glib" = "xno" ; then
	dnl check if we can use the pthread_library
	AC_CHECK_LIB(pthread, pthread_mutex_init, [pthread_enabled=yes], [pthread_enabled=no])
	if test $pthread_enabled = "no" ; then
		build_scheduler=no
	else
		PTHREAD_LIBS="-lpthread"
		PTHREAD_CFLAGS="-D_REENTRANT"
		AC_SUBST(PTHREAD_CFLAGS)
		AC_SUBST(PTHREAD_LIBS)
		AC_SUBST(PTHREAD_LDFLAGS)
	fi
fi

ORTPDEPS_LIBS="$ORTPDEPS_LIBS $PTHREAD_LIBS"
ORTPDEPS_CFLAGS="$ORTPDEPS_CFLAGS $PTHREAD_CFLAGS"
ORTPDEPS_LDFLAGS="$ORTPDEPS_LDFLAGS $PTHREAD_LDFLAGS"

if test $debug_enabled = "yes"; then
	AC_DEFINE(RTP_DEBUG,1,[Defined if debug mode (lots of traces)])
fi

AC_ARG_ENABLE(memcheck,
				[  --enable-memcheck=[yes/no]   enables memory leak detection (HPUX only).],
				[case "${enableval}" in
				yes) memcheck_enabled=yes;;
				no) memcheck_enabled=no;;
				*) AC_MSG_ERROR("Bad value for --enable-memcheck");;
			esac],
				[memcheck_enabled=no])
				
if test "$memcheck_enabled" = "yes" ; then
	if test "$hpux_host" = "yes" ; then
		AC_DEFINE(ENABLE_MEMCHECK,1,[Defined when memory leak checking if enabled])
	else
		echo "WARNING ************ : the memory check option is only available for HPUX."
	fi
fi


dnl Checks for header files.
AC_HEADER_STDC
AC_CHECK_HEADERS(poll.h sys/poll.h sys/uio.h fcntl.h sys/time.h unistd.h sys/audio.h linux/soundcard.h)

dnl Checks for typedefs, structures, and compiler characteristics.
AC_C_CONST
AC_C_INLINE
AC_HEADER_TIME
AC_WORDS_BIGENDIAN

dnl Checks for library functions.
AC_CHECK_FUNCS(select socket strerror)

if test $hpux_host = "yes" ; then
dnl it seems 10 ms is too fast on hpux and it causes trouble 
		posixtimer_interval=20000
fi

AC_DEFINE_UNQUOTED(POSIXTIMER_INTERVAL,$posixtimer_interval,[Defines the periodicity of the rtp scheduler in microseconds])

if test $GCC = yes && test $wall_werror = yes;  then
	CFLAGS="$CFLAGS -Werror "
fi


dnl ##################################################
dnl # Check for gtk-doc.
dnl ##################################################

AC_ARG_WITH(html-dir, [  --with-html-dir=PATH path to installed docs ])

if test "x$with_html_dir" = "x" ; then
  HTML_DIR='${datadir}/gtk-doc/html'
else
  HTML_DIR=$with_html_dir
fi

AC_SUBST(HTML_DIR)


dnl Let people disable the gtk-doc stuff.
AC_ARG_ENABLE(gtk-doc, [  --enable-gtk-doc  Build documentation with gtk-doc if available [default=yes]], enable_gtk_doc="$enableval", enable_gtk_doc=yes)

PKG_CHECK_MODULES(GTK_DOC,gtk-doc >= 0.6, 
[gtk_doc_found=yes] ,
gtk_doc_found=no)

AM_CONDITIONAL(ENABLE_GTK_DOC, test x$enable_gtk_doc$gtk_doc_found = xyesyes )


dnl ##################################################
dnl # Check for ESP Packager
dnl ##################################################

AC_PATH_PROG(EPM,epm,false)
AC_PATH_PROG(MKEPMLIST,mkepmlist,false)
AC_PATH_PROG(EPMINSTALL,epminstall,false)
AM_CONDITIONAL(WITH_EPM,test $EPM != false && test $MKEPMLIST != false && test $EPMINSTALL != false)


# Preferred packaging system, as per EPM terminology
case $target in
*-*-linux*)
     	EPM_PKG_EXT=rpm;;
*-hp-hpux*)
     	EPM_PKG_EXT=depot.gz;;
*-dec-osf*)
	EPM_PKG_EXT=setld;;
esac
AC_SUBST(EPM_PKG_EXT)

# System software User & Group names
case $target in
*-*-linux*)
	SYS_USER=root
	SYS_GROUP=root
	;;
*-*-hpux*|*-dec-osf*)
	SYS_USER=bin
	SYS_GROUP=bin
	;;
esac
AC_SUBST(SYS_USER)
AC_SUBST(SYS_GROUP)

# CPU Architecture
case $target_cpu in
i?86)		ARCH=i386;;
*)		ARCH=$target_cpu;;
esac
AC_SUBST(ARCH)

# Various other packaging variables, that can be over-ridden ad `make
# package' time
SUMMARY="An LGPL implementation of RTP - RFC3550"
AC_SUBST(SUMMARY)
PACKAGER=anonymous
AC_SUBST(PACKAGER)
LICENSE=LGPL
AC_SUBST(LICENSE)
VENDOR=Linphone
AC_SUBST(VENDOR)
RELEASE=1
AC_SUBST(RELEASE)

AC_SUBST(ORTPDEPS_CFLAGS)
AC_SUBST(ORTPDEPS_LIBS)
AC_SUBST(ORTPDEPS_LDFLAGS)

AC_OUTPUT(
Makefile
include/Makefile
include/ortp/Makefile
src/Makefile
src/tests/Makefile
docs/Makefile
build/Makefile
build/win32/Makefile
ortp.pc
ortp.spec
)
