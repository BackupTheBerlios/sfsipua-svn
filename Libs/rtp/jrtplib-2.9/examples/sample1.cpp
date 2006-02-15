/*
   Here's a small example: it asks for a portbase and a destination and starts
   sending packets to that destination.

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
	int status,i;
	char dummybuffer[1024];

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
	
	status = sess.AddDestination(destip,destport);
	checkerror(status);
	
	for (i = 1 ; i <= 10 ; i++)
	{
		printf("\nSending packet %d/10\n",i);
		
		// send the packet
		status = sess.SendPacket((void *)"1234567890",10,(unsigned char)0,false,10UL);
		checkerror(status);
		
		// poll for incoming data
		status = sess.PollData();
		
		// check incoming packets
		if (sess.GotoFirstSourceWithData())
		{
			do
			{
				RTPPacket *pack;
				
				while ((pack = sess.GetNextPacket()) != NULL)
				{
					// You can examine the data here
					printf("Got packet !\n");
					
					// we don't longer need the packet, so
					// we'll delete it
					delete pack;
				}
			} while (sess.GotoNextSourceWithData());
		}
		
		printf("Press enter to send the next packet\n");
		gets(dummybuffer);
	}
	
	return 0;
}
