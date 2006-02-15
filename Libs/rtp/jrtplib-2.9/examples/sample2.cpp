/*
   This demonstrates the round-trip time function of the library. Also,
   it gives an example of how to use the select function in combination
   with the library.

   To test the round-trip time measurements, you should start two instances
   of this program and have them send data to each other.

   IMPORTANT:
   	This sample was written for unix-like environments. For a Windows
   	platform, you'll need to perform Winsock initialisation through
   	WSAStartup.
*/

#include <stdlib.h>
#include <stdio.h>
#include "rtpsession.h"
#include "rtppacket.h"

/*
   This function checks if there was a RTP error. If so, it displays an error
   message and exists.
*/

void checkerror(int rtperr)
{
	if (rtperr < 0)
	{
		char *errstr;
		
		// This function gets the error string for a certain error code
		errstr = RTPGetErrorString(rtperr);
		
		printf("Error:\n");
		printf("%s\n",errstr);
		exit(-1);
	}
}

/*
   The main routine
*/

int main(void)
{
	RTPSession sess;
	int portbase;
	unsigned long destip;
	int destport;
	char ipstr[256];
	int status;
	char dummybuffer[1024];
	struct timeval rttprev = {0,0},rtt,tv;
	int sock1,sock2;
	bool done;
	fd_set fdset;
	
        /*
           First, we'll ask for the necessary information
        */
		
	printf("Enter the local portbase\n");
	scanf("%d",&portbase);
	printf("\n");
	
	printf("Enter the destination IP address\n");
	scanf("%s",ipstr);
	destip = inet_addr(ipstr);
	if (destip == INADDR_NONE)
	{
		printf("Bad IP address specified\n");
		return -1;
	}
	
	// The inet_addr function returns a value in network byte order, but
	// we need the IP address in host byte order, so we use a call to
	// ntohl
	destip = ntohl(destip);
	
	printf("Enter the destination port\n");
	scanf("%d",&destport);
	
	/*
	   Now, we'll create a RTP session, set the destination, send some
	   packets and poll for incoming data.
	*/
	
	status = sess.Create(portbase);	
	checkerror(status);

	/* Get the sockets, so we can use them in a 'select' call */
	
	sess.GetRTPSocket(&sock1);
	sess.GetRTCPSocket(&sock2);
	
	status = sess.AddDestination(destip,destport);
	checkerror(status);

	printf("Press return to quit...\n");
	
	done = false;
	while (!done)
	{
		/* Just send something */
		
		status = sess.SendPacket((void *)"1234567890",10,(unsigned char)0,false,10UL);
		checkerror(status);
		
		/* Wait for incoming data, or wait just one second */
		
		tv.tv_sec = 1;
		tv.tv_usec = 0;
		FD_ZERO(&fdset);
		FD_SET(sock1,&fdset);
		FD_SET(sock2,&fdset);
		FD_SET(0,&fdset); // check for keypress
			
		select(FD_SETSIZE,&fdset,NULL,NULL,&tv);
		if (FD_ISSET(0,&fdset))
			done = true;
		
		/* poll for incoming data */
		
		status = sess.PollData();
		
		/* check incoming packets */
		
		if (sess.GotoFirstSourceWithData())
		{
			do
			{
				RTPSourceData *srcdat;
				
				srcdat = sess.GetCurrentSourceInfo();
				srcdat->FlushPackets(); // we don't need the actual data
				
				rtt = srcdat->INF_GetRoundTripTime();
				if (rtt.tv_sec != 0 || rtt.tv_usec != 0)
				{
					if ((rtt.tv_sec != rttprev.tv_sec) || (rtt.tv_usec != rttprev.tv_usec))
					{
						double t;
					
						t = (double)rtt.tv_sec;
						t += ((double)rtt.tv_usec)/1000000.0;
						t *= 1000.0; // we want milliseconds;
						printf("rtt: %f ms\n",(float)t);
						rttprev = rtt;
					}
				}
			} while (sess.GotoNextSourceWithData());
		}
	}
	
	return 0;
}
