// Copyright (C) 1999-2003 Open Source Telecom Corporation.
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

/** 
 * @file rtp.h 
 *
 * @short Generic and audio/video profile specific RTP interface of
 * ccRTP.
 *
 * The classes and types in this header provide general RTP
 * functionality (following RFC 1889/draft-ietf-avt-rtp-new) as well
 * as audio/video RTP profile specific functionality (following RFC
 * 1890/draft-ietf-avt-profile-new).
 **/

#ifndef	CCXX_RTP_RTP_H_
#define CCXX_RTP_RTP_H_

#include <ccrtp/cqueue.h>
#include <ccrtp/channel.h>

#ifdef	CCXX_NAMESPACES
namespace ost {
#endif

/**
 * @defgroup sessions RTP sessions.
 * @{
 **/

/**
 * @class RTPSessionBase
 *
 * Generic RTP protocol stack for exchange of realtime data.  This
 * stack uses the concept of packet send and receive queues to schedule
 * and buffer outgoing packets and to arrange or reorder incoming packets
 * as they arrive.
 *
 * This is a template class that allows customization of two aspects:
 * the underlying network and the control protocol. The RTPDataChannel
 * and RTCPChannel template parameters specify the socket types to
 * use. The ServiceQueue template parameter specify which packet queue
 * is used.
 *
 * RTPSessionBase objects do not have any threading policy, thus
 * allowing to customize this aspect in derived classes (see
 * SingleThreadRTPSession or RTPSessionPoolBase).
 *
 * @author David Sugar <dyfet@ostel.com>
 * @short RTP protocol stack based on Common C++.
 **/
template <class RTPDataChannel = DualRTPUDPIPv4Channel, 
	  class RTCPChannel = DualRTPUDPIPv4Channel, 
	  class ServiceQueue = AVPQueue>
class CCXX_CLASS_EXPORT TRTPSessionBase : public ServiceQueue
{
public:
	/**
	 * Builds a session waiting for packets in a host address.
	 *
	 * @param ia Network address this socket is to be bound.
	 * @param dataPort Transport port the data socket is to be bound.
	 * @param controlPort Transport port the control socket is to be bound.
	 * @param membersSize Initial size of the membership table.
	 * @param app Application this session is associated to.
	 * */
	TRTPSessionBase(const InetHostAddress& ia, tpport_t dataPort,
			 tpport_t controlPort, uint32 membersSize,
			 RTPApplication& app) :
		ServiceQueue(membersSize,app)
	{ build(ia,dataPort,controlPort); }

	/**
	 * Builds a session with the specified ssrc identifier for the
	 * local source.
	 *
	 * @param ssrc SSRC identifier for the local source.
	 * @param ia Network address this socket is to be bound.
	 * @param dataPort Transport port the data socket is to be bound.
	 * @param controlPort Transport port the control socket is to be bound.
	 * @param membersSize Initial size of the membership table.
	 * @param app Application this session is associated to.
	 **/
	TRTPSessionBase(uint32 ssrc,
			 const InetHostAddress& ia, 
			 tpport_t dataPort, tpport_t controlPort,
			 uint32 membersSize, RTPApplication& app):
			 ServiceQueue(ssrc,membersSize,app)
	{ build(ia,dataPort,controlPort); }
			 
	/**
	 * Builds a session waiting for packets in a multicast address.
	 * TODO: ssrc constructor for multicast!
	 *
	 * @param ia Multicast address this socket is to be bound.
	 * @param dataPort Transport port the data socket is to be bound.
	 * @param controlPort Transport port the control socket is to be bound.
	 * @param membersSize Initial size of the membership table.
	 * @param app Application this session is associated to.
	 **/
	TRTPSessionBase(const InetMcastAddress& ia, tpport_t dataPort,
			tpport_t controlPort, uint32 membersSize,
			 RTPApplication& app) :
		ServiceQueue(membersSize,app)
	{ build(ia,dataPort,controlPort); }

	/**
	 * Builds a session waiting for packets in a multicast
	 * address, with the specified ssrc identifier for the local
	 * source.
	 *
	 * @param ssrc SSRC identifier for the local source.
	 * @param ia Multicast address this socket is to be bound.
	 * @param dataPort Transport port the data socket is to be bound.
	 * @param controlPort Transport port the control socket is to be bound.
	 * @param membersSize Initial size of the membership table.
	 * @param app Application this session is associated to.
	 **/
	TRTPSessionBase(uint32 ssrc,
			const InetMcastAddress& ia, tpport_t dataPort,
			tpport_t controlPort, uint32 membersSize,
			 RTPApplication& app) :
		ServiceQueue(ssrc,membersSize,app)
	{ build(ia,dataPort,controlPort); }


	inline virtual
	~TRTPSessionBase()
	{ 
	 dispatchBYE("RTP session being destroyed, GNU ccRTP stack finishing.");
	 endSocket(); 
	}

protected:
	/**
	 * @param timeout maximum timeout to wait, in microseconds
	 */
	inline bool
	isPendingData(microtimeout_t timeout)
	{ return dso->isPendingRecv(timeout); }

	InetHostAddress
	getDataSender(tpport_t *port = NULL) const
        { return dso->getSender(port); }

	inline size_t
	getNextDataPacketSize() const
	{ return dso->getNextPacketSize(); }

	/**
	 * Receive data from the data channel/socket.
	 *
	 * @param buffer Memory region to read to.
	 * @param len Maximum number of octets to get.
	 * @param na Source network address.
	 * @param tp Source transport port.
	 * @return Number of octets actually read.
	 */
	inline size_t
	recvData(unsigned char* buffer, size_t len, 
		 InetHostAddress& na, tpport_t& tp)
	{ na = dso->getSender(tp); return dso->recv(buffer, len); }

        inline void
        setDataPeer(const InetAddress &host, tpport_t port)
	{ dso->setPeer(host,port); }

	/**
	 * @param buffer memory region to write from
	 * @param len number of octets to write
	 */
	inline size_t
	sendData(const unsigned char* const buffer, size_t len)
	{ return dso->send(buffer, len); }

	inline SOCKET getDataRecvSocket() const
	{ return dso->getRecvSocket(); }

	/**
	 * @param timeout maximum timeout to wait, in microseconds
	 * @return whether there are packets waiting to be picked
	 */
        inline bool
	isPendingControl(microtimeout_t timeout)
	{ return cso->isPendingRecv(timeout); }

	InetHostAddress
	getControlSender(tpport_t *port = NULL) const
        { return cso->getSender(port); }

	/**
	 * Receive data from the control channel/socket.
	 *
	 * @param buffer Buffer where to get data.
	 * @param len Maximum number of octets to get.
	 * @param na Source network address.
	 * @param tp Source transport port.
	 * @return Number of octets actually read.
	 **/
        inline size_t
	recvControl(unsigned char *buffer, size_t len,
		    InetHostAddress& na, tpport_t& tp)
	{ na = cso->getSender(tp); return cso->recv(buffer,len); }

        inline void
        setControlPeer(const InetAddress &host, tpport_t port)
	{ cso->setPeer(host,port); }

	/**
	 * @return number of octets actually written
	 * @param buffer
	 * @param len
	 */
        inline size_t
	sendControl(const unsigned char* const buffer, size_t len)
	{ return cso->send(buffer,len); }

	inline SOCKET getControlRecvSocket() const
	{ return cso->getRecvSocket(); }
	
	inline void
	endSocket()
	{ 
		dso->endSocket();
		cso->endSocket();
		if (dso) delete dso;
		dso = NULL;
		if (cso) delete cso;
		cso = NULL;
	}

private:
	void 
	build(const InetHostAddress& ia, tpport_t dataPort, 
	      tpport_t controlPort)
	{
		if ( 0 == controlPort ) {
			dataBasePort = even_port(dataPort); 
			controlBasePort = dataBasePort + 1;
		} else {
			dataBasePort = dataPort;
			controlBasePort = controlPort;
		}
		dso = new RTPDataChannel(ia,dataBasePort);
		cso = new RTCPChannel(ia,controlBasePort);
	}

	void 
	build(const InetMcastAddress& ia, tpport_t dataPort, 
	      tpport_t controlPort)
	{
		if ( 0 == controlPort ) {
			dataBasePort = even_port(dataPort); 
			controlBasePort = dataBasePort + 1;
		} else {
			dataBasePort = dataPort;
			controlBasePort = controlPort;
		}
		dso = new RTPDataChannel(ia,dataBasePort);
		cso = new RTCPChannel(ia,controlBasePort);
		joinGroup(ia);
	}

	/**
	 * Join a multicast group. 
	 *
	 * @param ia address of the multicast group
	 * @return error code from the socket operation
	 */
	inline Socket::Error
	joinGroup(const InetMcastAddress& ia)
	{ 
		Socket::Error error  = dso->setMulticast(true);
		if ( error ) return error;
		error = dso->join(ia); 
		if ( error ) return error;
		error = cso->setMulticast(true);
		if ( error ) {
			dso->drop(ia);
			return error;
		}
		error = cso->join(ia);
		if ( error ) {
			dso->drop(ia);
			return error;
		}
		return Socket::errSuccess;
	}

	/**
	 * Leave a multicast group. 
	 * 
	 * @param ia address of the multicast group
	 * @return error code from the socket operation
	 */
	inline Socket::Error
	leaveGroup(const InetMcastAddress& ia)
	{
		Socket::Error error = dso->setMulticast(false);
		if ( error ) return error;
		error = dso->leaveGroup(ia);
		if ( error ) return error;
		error = cso->setMulticast(false);
		if ( error ) return errror;
		return cso->leaveGroup(ia);
	}

	/**
	 * Set the value of the TTL field in the sent packets.
	 *
	 * @param ttl Time To Live
	 * @return error code from the socket operation
	 */
	inline Socket::Error
	setMcastTTL(uint8 ttl)
	{
		Socket::Error error = dso->setMulticast(true);
		if ( error ) return error;
		error = dso->setTimeToLive(ttl);
		if ( error ) return error;
		error = cso->setMulticast(true);
		if ( error ) return error;
		return cso->setTimeToLive(ttl);
	}

	/**
	 * Ensure a port number is odd. If it is an even number, return
	 * the next lower (odd) port number.
	 *
	 * @param port number to filter
	 * @return filtered (odd) port number
	 */
	inline tpport_t
	odd_port(tpport_t port)
	{ return (port & 0x01)? (port) : (port - 1); }

	/**
	 * Ensure a port number is even. If it is an odd number, return
	 * the next lower (even) port number.
	 *
	 * @param port number to filter
	 * @return filtered (even) port number
	 */
	inline tpport_t
	even_port(tpport_t port)
	{ return (port & 0x01)? (port - 1) : (port); }

	tpport_t dataBasePort;
	tpport_t controlBasePort;
	RTPDataChannel* dso;
	RTCPChannel* cso;
	friend class RTPSessionBaseHandler;
};

/**
 * @class OneThreadRTPSession
 *
 * This template class adds the threading aspect to the RTPSessionBase
 * template in one of the many possible ways. It inherits from a
 * single execution thread that schedules sending of outgoing packets
 * and receipt of incoming packets.
 *
 * @author Federico Montesino Pouzols <fedemp@altern.org>
 **/
template
<class RTPDataChannel = DualRTPUDPIPv4Channel, 
 class RTCPChannel = DualRTPUDPIPv4Channel, 
 class ServiceQueue = AVPQueue>
class CCXX_CLASS_EXPORT SingleThreadRTPSession : 
	protected Thread,
	public TRTPSessionBase<RTPDataChannel,RTCPChannel,ServiceQueue>
{
public:
	SingleThreadRTPSession(const InetHostAddress& ia, 
			       tpport_t dataPort = DefaultRTPDataPort, 
			       tpport_t controlPort = 0,
			       int pri = 0,
			       uint32 memberssize = 
			       MembershipBookkeeping::defaultMembersHashSize,
			       RTPApplication& app = defaultApplication()): 
		Thread(pri),
		TRTPSessionBase<RTPDataChannel,RTCPChannel,ServiceQueue>
	(ia,dataPort,controlPort,memberssize,app)
	{ }

	SingleThreadRTPSession(const InetMcastAddress& ia, 
			       tpport_t dataPort = DefaultRTPDataPort, 
			       tpport_t controlPort = 0, 
			       int pri = 0,
			       uint32 memberssize = 
			       MembershipBookkeeping::defaultMembersHashSize,
			       RTPApplication& app = defaultApplication()): 
		Thread(pri),
		TRTPSessionBase<RTPDataChannel,RTCPChannel,ServiceQueue>
	(ia,dataPort,controlPort,memberssize,app)
	{ }

	~SingleThreadRTPSession()
	{ terminate(); }

	/**
	 * Activate stack and start service thread.
	 **/
	void
	startRunning()
	{ startStack(); Thread::start(); }

protected:
	/**
	 * Single runnable method for this RTP stacks, schedules
	 * outgoing and incoming RTP data and RTCP packets.
	 **/
	void 
	run()
	{
		microtimeout_t timeout = 0;
		while ( ServiceQueue::isActive() ) {
			if ( !timeout ){
				timeout = getSchedulingTimeout();
			}
			setCancel(cancelDeferred);
			controlReceptionService();
			controlTransmissionService();
			setCancel(cancelImmediate);
			microtimeout_t maxWait = 
				timeval2microtimeout(getRTCPCheckInterval());
			// make sure the scheduling timeout is
			// <= the check interval for RTCP
			// packets
			timeout = (timeout > maxWait)? maxWait : timeout;
			if ( !timeout ) {
				setCancel(cancelDeferred);
				size_t r = dispatchDataPacket();
				setCancel(cancelImmediate);
				if ( r < 0 )
					timeout = timeout;
				timerTick();
			} else {
				if ( isPendingData(timeout/1000) ) {
					setCancel(cancelDeferred);
					size_t r = takeInDataPacket();
					setCancel(cancelImmediate);
					if ( r < 0 )
						return;
				}
				timeout = 0;
			}
		}
		dispatchBYE("GNU ccRTP stack finishing.");
		sleep(~0);
	}
};

/**
 * @typedef RTPSession
 *
 * Uses two pairs of sockets for RTP data and RTCP
 * transmission/reception.
 *
 * @short UDP/IPv4 RTP Session scheduled by one thread of execution.
 **/
typedef SingleThreadRTPSession<> RTPSession;

/**
 * @typedef RTPSocket
 *
 * Alias for RTPSession.
 **/
typedef RTPSession RTPSocket;

/** @}*/ // sessions

#ifdef  CCXX_NAMESPACES
};
#endif

#endif  //CCXX_RTP_RTP_H_

/** EMACS **
 * Local variables:
 * mode: c++
 * c-basic-offset: 8
 * End:
 */
