// Copyright (C) 2001,2002,2003 Federico Montesino Pouzols <fedemp@altern.org>
// 
// This program is free software; you can redistribute it and/or modify
// it under the terms of the GNU General Public License as published by
// the Free Software Foundation; either version 2 of the License, or
// (at your option) any later version.
// 
// This program is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU General Public License for more details.
// 
// You should have received a copy of the GNU General Public License
// along with this program; if not, write to the Free Software 
// Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA 02111-1307, USA.
// 
// As a special exception to the GNU General Public License, permission is 
// granted for additional uses of the text contained in its release 
// of ccRTP.
// 
// The exception is that, if you link the ccRTP library with other
// files to produce an executable, this does not by itself cause the
// resulting executable to be covered by the GNU General Public License.
// Your use of that executable is in no way restricted on account of
// linking the ccRTP library code into it.
// 
// This exception does not however invalidate any other reasons why
// the executable file might be covered by the GNU General Public License.
// 
// This exception applies only to the code released under the 
// name ccRTP.  If you copy code from other releases into a copy of
// ccRTP, as the General Public License permits, the exception does
// not apply to the code that you add in this way.  To avoid misleading
// anyone as to the status of such modified files, you must delete
// this exception notice from them.
// 
// If you write modifications of your own for ccRTP, it is your choice
// whether to permit this exception to apply to your modifications.
// If you do not wish that, delete this exception notice.  

#ifndef	CCRTP_CHANNEL_H_
#define CCRTP_CHANNEL_H_

#include <ccrtp/base.h>

#ifndef WIN32
#include <sys/ioctl.h>
inline size_t ccioctl(int so, int request, size_t& len) 
{ return ::ioctl(so,request,&len); }
#else
inline size_t ccioctl(int so, int request, size_t& len )
{ 
	unsigned long l; 
	size_t result;
	::ioctlsocket(so,request,&l); 
	len = l; 
	return result;
}
#endif

#ifdef	CCXX_NAMESPACES
namespace ost {
#endif

/**
 * @file channel.h
 *
 * Definition of socket classes for different underlying transport
 * and/or network protocols that can be used to instantiate the
 * TRTPSessionBase template.
 **/

/**
 * @defgroup sockets Underlying transport protocol socket classes.
 * @{
 **/

/**
 * @class RTPBaseUDPIPv4Socket
 * @short A UDP/IPv4 socket class targetted at RTP stacks.
 *
 * This class provides a flat interface that all the services required
 * by an RTP stack.
 *
 * It can be used in two ways:
 *
 * To instantiate the DualSocket template, which will be used to
 * instantiate an RTP stack template (such as TRTPSessionBase).
 *
 * To directly instantiate an RTP stack template (such as
 * TRTPSessionBase).
 *
 * This class offers an example of the interface that other classes
 * should provide in order to specialize the ccRTP stack for different
 * underlying protocols.
 *
 * @author Federico Montesino Pouzols <fedemp@altern.org>
 **/
class RTPBaseUDPIPv4Socket : private UDPSocket
{
public:
	/**
	 * Constructor for receiver.
	 **/
	RTPBaseUDPIPv4Socket(const InetAddress& ia, tpport_t port) :
		UDPSocket(ia,port)
	{ }
	
	inline ~RTPBaseUDPIPv4Socket()
	{ endSocket(); }
	
	inline bool
	isPendingRecv(microtimeout_t timeout)
	{ return UDPSocket::isPending(UDPSocket::pendingInput, timeout); }

	InetHostAddress
	getSender(tpport_t& port) const
	{ return UDPSocket::getSender(&port); }

	inline size_t
	recv(unsigned char* buffer, size_t len)
	{ return UDPSocket::receive(buffer, len); }

	/**
	 * Get size of next datagram waiting to be read.
	 **/
	inline size_t
	getNextPacketSize() const
	{ size_t len; ccioctl(UDPSocket::so,FIONREAD,len); return len; }

	Socket::Error
	setMulticast(bool enable)
	{ return UDPSocket::setMulticast(enable); }

	inline Socket::Error
	join(const InetMcastAddress& ia)
	{ return Socket::join(ia); }

	inline Socket::Error
	drop(const InetMcastAddress& ia)
	{ return UDPSocket::drop(ia); }

        inline Socket::Error 
	setTimeToLive(unsigned char ttl)
	{ return UDPSocket::setTimeToLive(ttl); }
 
	/**
	 * Constructor for transmitter.
	 **/
	RTPBaseUDPIPv4Socket() :
		UDPSocket()
	{ }

	inline void 
	setPeer(const InetAddress &ia, tpport_t port)
	{
		memset(&peer, 0, sizeof(peer));
		UDPSocket::peer.sin_family = AF_INET;
		UDPSocket::peer.sin_addr = getaddress(ia);
		UDPSocket::peer.sin_port = htons(port);		
	}

	inline size_t
	send(const unsigned char* const buffer, size_t len)
	{ return UDPSocket::send(buffer, len); }

	inline SOCKET getRecvSocket() const
	{ return UDPSocket::so; }

	// common
	inline void
	endSocket()
	{ UDPSocket::endSocket(); }
};

/**
 * @class DualUDPIPv4Socket
 * @short A socket class based on two UDP/IPv4 sockets.
 *
 * Defines a communication channel for RTP data and/or RTCP streams.
 * Sockets used to instantiate this template must define a framing
 * mechanism (UDP does not need any addition, TCP does).
 *
 * This class implements a socket as a pair of UDP/IPv4 sockets,
 * alllowing both transmission and reception of packets in unicast as
 * well as multicast mode. The implementation of this class relies on
 * the Common C++ UDPSocket class but provides the interface needed by
 * a ccRTP stack.
 *
 * Normally, RTP stacks will use two objects of this class, one for
 * RTP data packets transmission/reception and other for RTCP
 * (control) transmission/reception.
 *
 * @author Federico Montesino Pouzols <fedemp@altern.org>
 **/
template<class BaseSocket>
class DualRTPChannel
{
public:
	DualRTPChannel(const InetAddress& ia, tpport_t port)
	{ 
		recvSocket = new BaseSocket(ia,port);
		sendSocket = new BaseSocket;
	}

	inline ~DualRTPChannel()
	{ delete sendSocket; delete recvSocket; }
	
	inline bool
	isPendingRecv(microtimeout_t timeout) const
	{ return recvSocket->isPendingRecv(timeout); }

	InetHostAddress
	getSender(tpport_t& port) const
	{ return recvSocket->getSender(port); }

	inline size_t
	recv(unsigned char* buffer, size_t len)
	{ return recvSocket->recv(buffer, len); }

	inline size_t
	getNextPacketSize() const
	{ return recvSocket->getNextPacketSize(); }

	Socket::Error
	setMulticast(bool enable)
	{ return recvSocket->setMulticast(enable); }

	inline Socket::Error
	join(const InetMcastAddress& ia)
	{ return recvSocket->join(ia); }

	inline Socket::Error
	drop(const InetMcastAddress& ia)
	{ return recvSocket->drop(ia); }

        inline Socket::Error 
	setTimeToLive(unsigned char ttl)
	{ return recvSocket->setTimeToLive(ttl); }
 
	inline void 
	setPeer(const InetAddress& host, tpport_t port)
	{ sendSocket->setPeer(host,port); }

	inline size_t
	send(const unsigned char* const buffer, size_t len)		  
	{ return sendSocket->send(buffer, len); }

	inline SOCKET getRecvSocket() const
	{ return recvSocket->getRecvSocket(); }

	// common.
	inline void
	endSocket()
	{ sendSocket->endSocket(); recvSocket->endSocket(); }

private:
	BaseSocket* sendSocket;
	BaseSocket* recvSocket;
};

typedef DualRTPChannel<RTPBaseUDPIPv4Socket> DualRTPUDPIPv4Channel;

/**
 * May be used in applications where using the same socket for both
 * sending and receiving is not a limitation.
 **/
typedef RTPBaseUDPIPv4Socket SingleRTPChannel;

/** @}*/ // sockets

#ifdef  CCXX_NAMESPACES
};
#endif

#endif  //CCRTP_CHANNEL_H_

/** EMACS **
 * Local variables:
 * mode: c++
 * c-basic-offset: 8
 * End:
 */
