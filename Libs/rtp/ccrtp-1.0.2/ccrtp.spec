Summary: ccrtp - a Common C++ class framework for RTP/RTCP
Name: ccrtp1
Version: 1.0.2
Release: 1
Group: Development/Libraries
URL: http://www.gnu.org/software/ccrtp
Source: ftp://ftp.gnu.org/gnu/ccrtp/ccrtp-%{PACKAGE_VERSION}.tar.gz
Prefix: %{_prefix}
Copyright: GPL
BuildRoot: %{_tmppath}/rtp-root
Packager: David Sugar <dyfet@ostel.com>
Requires: commoncpp2 >= 0.99.0

%package devel
Requires: ccrtp1, commoncpp2-devel
Group: Development/Libraries
Summary: headers and link libraries

%description
ccRTP is a generic, extensible and efficient C++ framework for
developing applications based on the Real-Time Transport Protocol
(RTP) from the IETF. It is based on Common C++ and provides a full
RTP/RTCP stack for sending and receiving of realtime data by the use
of send and receive packet queues. ccRTP supports unicast,
multi-unicast and multicast, manages multiple sources, handles RTCP
automatically, supports different threading models and is generic as
for underlying network and transport protocols.

%description devel
This package holds documentation, header files, and static link libraries
for building applications that use GNU ccRTP.

%prep
rm -rf $RPM_BUILD_ROOT

%setup -n ccrtp-%{PACKAGE_VERSION}
./configure --prefix=%{_prefix} --mandir=%{_mandir} --infodir=%{_infodir}

%build
uname -a|grep SMP && make -j 2 || make

%install
mkdir -p $RPM_BUILD_ROOT/%{_mandir}/man3
make prefix=$RPM_BUILD_ROOT/%{_prefix} \
	mandir=$RPM_BUILD_ROOT/%{_mandir} \
	infodir=$RPM_BUILD_ROOT/%{_infodir} install
make prefix=$RPM_BUILD_ROOT/%{_prefix} \
	mandir=$RPM_BUILD_ROOT/%{_mandir} man

%files
%defattr(-,root,root,0755)
%{_prefix}/lib/libcc*so*
%{_prefix}/bin/phone

%files devel
%defattr(-,root,root,0755)
%doc AUTHORS COPYING NEWS README TODO ChangeLog
%{_prefix}/lib/libcc*a
%{_prefix}/include/ccrtp
%{_mandir}/man3/*.3cc*
%{_infodir}/ccrtp*info*

%clean
rm -rf $RPM_BUILD_ROOT

%post
/sbin/ldconfig -n ${exec_prefix}/lib

%postun
/sbin/ldconfig -n ${exec_prefix}/lib

