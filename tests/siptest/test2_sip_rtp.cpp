#include "assert.h"
#include <conio.h>


#include <string>

#include "eXosip/eXosip.h"
#include "eXosip/eXosip_cfg.h"


#include "M:/sips/jrtp/jrtplib-2.9/rtpsession.h"
#include "M:/sips/jrtp/jrtplib-2.9/rtppacket.h"
#include <fstream.h>
#include <process.h>

#include "mmreg.h"
#include "msacm.h"
#include <iostream>
#include "osip2/osip_mt.h"
char server[200]="@192.168.3.190:6060";
char identity[200]="sip:";//king@sip.broadz.net";
char registrar[200]="sip:192.168.3.190:6060";
char username[100];//="king";
char password[100];//="";
int j;
int reg_id;
char contact[200]="sip:";//king@sip.broadz.net";
int expires;
bool run = true;


int portbase=10000;
char *destip="sip:987636039@192.168.3.190:6060";
int destport=80;
char ipstr[256];
int status,i;
char dummybuffer[1024];

int g_g723Drivers = 0;
int g_gsmDrivers = 0;
int portt;
void* startsound(void *_ca)
{
	FILE *source=fopen("c://12.wav","rb");
	if ( source == NULL )
	{
		cout<<"can't access the file"<<endl;
	}
//#ifdef win32
 	
//#endif	
	size_t bufRead  = 0;
	bool Mark=true;
	#define bufsize 1024
	BYTE buffer[bufsize];
	int t;
	RTPSession sess;
	
	t=sess.Create(5800);
	if(t!=0)cout<<"can't create"<<endl;
	bool sen;
	if(t==0){sen=true;}
	int nPT ;
	int nTSTAMP;
	sess.SetMulticastTTL(1);	//設定multicast封包TTL
	sess.AddDestination(ntohl(inet_addr("192.168.3.190")),portt);	//指定傳送目的端
	//sess.AddDestination(ntohl(inet_addr("192.168.25.79")),6900);
	if(t!=0) cout<<"can't add destination"<<endl;
	(void) fseek( source, 0, SEEK_SET );
		while(!feof(source))
		{
			bufRead = fread(buffer, sizeof(BYTE), bufsize, source ); 
			nPT=rand()%64+1;		
			nTSTAMP=rand()%1000+1;	
		    t=sess.SendPacket(buffer,bufsize,nPT,Mark,nTSTAMP);	
		    if(t!=0)cout<<"can't sending"<<endl;
			Sleep(5);
			Mark=false;			
		}
		(void) fflush( source ); 
		(void) fclose( source ); 
		cout<<("send success")<<endl;
	WSACleanup();
	return NULL;
}

class jcall;
int    os_sound_start(jcall *ca, int port);

int os_sound_start(jcall *ca, int port)
{
		portt=port;
	   osip_thread_create(20000,startsound, ca);  
	   return 0;
}

class jcall {
public:
	int cid;
	int did;

	char reason_phrase[50];
	int  status_code;

	char textinfo[256];
	char req_uri[256];
	char local_uri[256];
	char remote_uri[256];
	char subject[256];

	char remote_sdp_audio_ip[50];
	int  remote_sdp_audio_port;
	int  payload;
	char payload_name[50];

	int state;

	jcall() {}

	int build(eXosip_event_t *je)
	{
		jcall *ca = this;

		ca->cid = je->cid;
		ca->did = je->did;

		if (ca->did<1 && ca->cid<1)
		{
			assert(0);
			return -1; /* not enough information for this event?? */
		}

		osip_strncpy(ca->textinfo,   je->textinfo, 255);
		osip_strncpy(ca->req_uri,    je->req_uri, 255);
		osip_strncpy(ca->local_uri,  je->local_uri, 255);
		osip_strncpy(ca->remote_uri, je->remote_uri, 255);
		osip_strncpy(ca->subject,    je->subject, 255);

		if (ca->remote_sdp_audio_ip[0]=='\0')
		{
			osip_strncpy(ca->remote_sdp_audio_ip, je->remote_sdp_audio_ip, 49);
			ca->remote_sdp_audio_port = je->remote_sdp_audio_port;
			ca->payload = je->payload;
			osip_strncpy(ca->payload_name, je->payload_name, 49);
		}

		if (je->reason_phrase[0]!='\0')
		{
			osip_strncpy(ca->reason_phrase, je->reason_phrase, 49);
			ca->status_code = je->status_code;
		}
		os_sound_start(ca, (je->remote_sdp_audio_port));
		ca->state = je->type;
		return 0;
	}

};


jcall call;

void __exit( int r )
{
	char line[256];
	gets( line );
	exit( r );
}

void josua_printf(char* buf)
{
	
	printf( "\n" );
}


int josua_event_get()
{
	int counter =0;
	/* use events to print some info */
	eXosip_event_t *je;
	for (;;)
	{
		char buf[100];
		je = eXosip_event_wait(0,50);
		if (je==NULL)
			break;
		counter++;
		if (je->type==EXOSIP_CALL_NEW)
		{
			printf( "<- (%i %i) INVITE from: %s",
				je->cid, je->did,
				je->remote_uri);
			josua_printf(buf);

			call.build(je);
		}
		else if (je->type==EXOSIP_CALL_ANSWERED)
		{
			printf( "<- (%i %i) [%i %s ANSWERED] %s",
				je->cid, je->did, 
				je->status_code,
				je->reason_phrase,
				je->remote_uri);
			josua_printf(buf);
			call.build(je);
		}
		else if (je->type==EXOSIP_CALL_PROCEEDING)
		{
			printf( "<- (%i %i) [%i %s] %s",
				je->cid, je->did, 
				je->status_code,
				je->reason_phrase,
				je->remote_uri);
			josua_printf(buf);
			josua_printf("EXOSIP_CALL_PROCEEDING");
		}
		else if (je->type==EXOSIP_CALL_RINGING)
		{
			printf( "<- (%i %i) [%i %s] %s",
				je->cid, je->did, 
				je->status_code,
				je->reason_phrase,
				je->remote_uri);
			josua_printf(buf);
			std::cout<<"EXOSIP_CALL_RINGING"<<endl;
		}
		else if (je->type==EXOSIP_CALL_CANCELLED)
		{std::cout<<"cancer";
		}
		else if (je->type==EXOSIP_CALL_REDIRECTED)
		{
			printf( "<- (%i %i) [%i %s] %s",
				je->cid, je->did,
				je->status_code,
				je->reason_phrase,
				je->remote_uri);
			josua_printf(buf);
			std::cout<<"EXOSIP_CALL_REDIRECTED"<<endl;
		}
		else if (je->type==EXOSIP_CALL_REQUESTFAILURE)
		{
			printf( "<- (%i %i) [%i %s] %s",
				je->cid, je->did,
				je->status_code,
				je->reason_phrase,
				je->remote_uri);
			josua_printf(buf);
			std::cout<<"EXOSIP_CALL_REQUESTFAILURE"<<endl;
		}
		else if (je->type==EXOSIP_CALL_SERVERFAILURE)
		{
			printf( "<- (%i %i) [%i %s] %s",
				je->cid, je->did, 
				je->status_code,
				je->reason_phrase,
				je->remote_uri);
			josua_printf(buf);
		}
		else if (je->type==EXOSIP_CALL_GLOBALFAILURE)
		{
			printf( "<- (%i %i) [%i %s] %s",
				je->cid, je->did,
				je->status_code,
				je->reason_phrase,
				je->remote_uri);
			josua_printf(buf);
		}
		else if (je->type==EXOSIP_CALL_CLOSED)
		{
			printf( "<- (%i %i) BYE from: %s",
				je->cid, je->did, je->remote_uri);
			josua_printf(buf);
		}
		else if (je->type==EXOSIP_CALL_HOLD)
		{
			printf( "<- (%i %i) INVITE (On Hold) from: %s",
				je->cid, je->did, je->remote_uri);
			josua_printf(buf);
		}
		else if (je->type==EXOSIP_CALL_OFFHOLD)
		{
			printf( "<- (%i %i) INVITE (Off Hold) from: %s",
				je->cid, je->did, je->remote_uri);
			josua_printf(buf);
		}
		else if (je->type==EXOSIP_REGISTRATION_SUCCESS)
		{
			printf( "<- (%i) [%i %s] %s for REGISTER_SUCCESS %s",
				je->rid,
				je->status_code,
				je->reason_phrase,
				je->remote_uri,
				je->req_uri);
			josua_printf(buf);
			std::cout<<endl;
		}
		else if (je->type==EXOSIP_REGISTRATION_REFRESHED)
		{

		}
		else if (je->type== EXOSIP_REGISTRATION_TERMINATED)
		{

		}
		else if (je->type==EXOSIP_REGISTRATION_FAILURE)
		{
			reg_id = eXosip_register_init(identity, registrar, contact);
			if(eXosip_add_authentication_info(username, username, password, NULL, NULL)) 
			{
				exit(1);
			}
			eXosip_lock();
			j = eXosip_register(reg_id, expires);
			eXosip_unlock();
			std::cout<<"REGISTER_FAILURE";
			printf( "<- (%i) [%i %s] %s for REGISTER_FAILURE %s",
				je->rid,
				je->status_code,
				je->reason_phrase,
				je->remote_uri,
				je->req_uri);
			josua_printf(buf);
		}
		else if (je->type==EXOSIP_OPTIONS_NEW)
		{
			printf( "<- (%i %i) OPTIONS from: %s",
				je->cid, je->did,
				je->remote_uri);
			josua_printf(buf);

		}
		else if (je->type==EXOSIP_OPTIONS_ANSWERED)
		{
			printf( "<- (%i %i) [%i %s] %s",
				je->cid, je->did, 
				je->status_code,
				je->reason_phrase,
				je->remote_uri);
			josua_printf(buf);
		}
		else if (je->type==EXOSIP_OPTIONS_PROCEEDING)
		{
			printf( "<- (%i %i) [%i %s] %s",
				je->cid, je->did, 
				je->status_code,
				je->reason_phrase,
				je->remote_uri);
			josua_printf(buf);

		}
		else if (je->type==EXOSIP_OPTIONS_REDIRECTED)
		{
			printf( "<- (%i %i) [%i %s] %s",
				je->cid, je->did,
				je->status_code,
				je->reason_phrase,
				je->remote_uri);
			josua_printf(buf);
		}
		else if (je->type==EXOSIP_OPTIONS_REQUESTFAILURE)
		{
			printf( "<- (%i %i) [%i %s] %s",
				je->cid, je->did,
				je->status_code,
				je->reason_phrase,
				je->remote_uri);
			josua_printf(buf);
		}
		else if (je->type==EXOSIP_OPTIONS_SERVERFAILURE)
		{
			printf( "<- (%i %i) [%i %s] %s",
				je->cid, je->did, 
				je->status_code,
				je->reason_phrase,
				je->remote_uri);
			josua_printf(buf);
		}
		else if (je->type==EXOSIP_OPTIONS_GLOBALFAILURE)
		{
			printf( "<- (%i %i) [%i %s] %s",
				je->cid, je->did,
				je->status_code,
				je->reason_phrase,
				je->remote_uri);
			josua_printf(buf);
		}
		else if (je->type==EXOSIP_INFO_NEW)
		{
			printf( "<- (%i %i) INFO from: %s",
				je->cid, je->did,
				je->remote_uri);
			josua_printf(buf);
		}
		else if (je->type==EXOSIP_INFO_ANSWERED)
		{
			printf( "<- (%i %i) [%i %s] %s",
				je->cid, je->did, 
				je->status_code,
				je->reason_phrase,
				je->remote_uri);
			josua_printf(buf);
		}
		else if (je->type==EXOSIP_INFO_PROCEEDING)
		{
			printf( "<- (%i %i) [%i %s] %s",
				je->cid, je->did, 
				je->status_code,
				je->reason_phrase,
				je->remote_uri);
			josua_printf(buf);
		}
		else if (je->type==EXOSIP_INFO_REDIRECTED)
		{
			printf( "<- (%i %i) [%i %s] %s",
				je->cid, je->did,
				je->status_code,
				je->reason_phrase,
				je->remote_uri);
			josua_printf(buf);
		}
		else if (je->type==EXOSIP_INFO_REQUESTFAILURE)
		{
			printf( "<- (%i %i) [%i %s] %s",
				je->cid, je->did,
				je->status_code,
				je->reason_phrase,
				je->remote_uri);
			josua_printf(buf);
		}
		else if (je->type==EXOSIP_INFO_SERVERFAILURE)
		{
			printf( "<- (%i %i) [%i %s] %s",
				je->cid, je->did, 
				je->status_code,
				je->reason_phrase,
				je->remote_uri);
			josua_printf(buf);
		}
		else if (je->type==EXOSIP_INFO_GLOBALFAILURE)
		{
			printf( "<- (%i %i) [%i %s] %s",
				je->cid, je->did,
				je->status_code,
				je->reason_phrase,
				je->remote_uri);
			josua_printf(buf);
		}

		else if (je->type==EXOSIP_SUBSCRIPTION_ANSWERED)
		{
			printf( "<- (%i %i) [%i %s] %s for SUBSCRIBE",
				je->sid, je->did, 
				je->status_code,
				je->reason_phrase,
				je->remote_uri);
			josua_printf(buf);

			printf( "<- (%i %i) online=%i [status: %i reason:%i]",
				je->sid, je->did, 
				je->online_status,
				je->ss_status,
				je->ss_reason);
			josua_printf(buf);

		}
		else if (je->type==EXOSIP_SUBSCRIPTION_PROCEEDING)
		{
			printf( "<- (%i %i) [%i %s] %s for SUBSCRIBE",
				je->sid, je->did, 
				je->status_code,
				je->reason_phrase,
				je->remote_uri);
			josua_printf(buf);

		}
		else if (je->type==EXOSIP_SUBSCRIPTION_REDIRECTED)
		{
			printf( "<- (%i %i) [%i %s] %s for SUBSCRIBE",
				je->sid, je->did,
				je->status_code,
				je->reason_phrase,
				je->remote_uri);
			josua_printf(buf);
		}
		else if (je->type==EXOSIP_SUBSCRIPTION_REQUESTFAILURE)
		{
			printf( "<- (%i %i) [%i %s] %s for SUBSCRIBE",
				je->sid, je->did,
				je->status_code,
				je->reason_phrase,
				je->remote_uri);
			josua_printf(buf);
		}
		else if (je->type==EXOSIP_SUBSCRIPTION_SERVERFAILURE)
		{
			printf( "<- (%i %i) [%i %s] %s for SUBSCRIBE",
				je->sid, je->did, 
				je->status_code,
				je->reason_phrase,
				je->remote_uri);
			josua_printf(buf);
		}
		else if (je->type==EXOSIP_SUBSCRIPTION_GLOBALFAILURE)
		{
			printf( "<- (%i %i) [%i %s] %s for SUBSCRIBE",
				je->sid, je->did,
				je->status_code,
				je->reason_phrase,
				je->remote_uri);
			josua_printf(buf);
		}
		else if (je->type==EXOSIP_SUBSCRIPTION_NOTIFY)
		{
			printf( "<- (%i %i) NOTIFY from: %s",
				je->sid, je->did,
				je->remote_uri);
			josua_printf(buf);

			printf( "<- (%i %i) online=%i [status: %i reason:%i]",
				je->sid, je->did, 
				je->online_status,
				je->ss_status,
				je->ss_reason);
			josua_printf(buf);

		}
		else if (je->type==EXOSIP_IN_SUBSCRIPTION_NEW)
		{
			printf( "<- (%i %i) SUBSCRIBE from: %s",
				je->nid, je->did,
				je->remote_uri);
			josua_printf(buf);

			/* search for the user to see if he has been
			previously accepted or not! */

			eXosip_notify(je->did, EXOSIP_SUBCRSTATE_PENDING, EXOSIP_NOTIFY_AWAY);
		}
		else if (je->textinfo[0]!='\0')
		{
			printf( "(%i %i %i %i) %s", je->cid, je->sid, je->nid, je->did, je->textinfo);
			josua_printf(buf);
		}


		eXosip_event_free(je);
	}
	if (counter>0)
		return 0;
	return -1;
}
int main(int argc, char* argv[])
{
	int i;
	expires = 3600;
	memset( &call, 0, sizeof(call) );
	std::cout<<"Please Enter Your Username:";
	cin>>username;
	std::cout<<"Please Enter Your Password:";
	cin>>password;
	strcat(identity,username);
	strcat(identity,server);
	strcpy(contact,identity);

	std::cout << "Usage:"<< endl;
	std::cout << "a - answering call"<< endl;
	std::cout << "h - hangup"<< endl;
	std::cout << "z - zhuxiao"<< endl;
	std::cout << "c - call"<< endl;
	std::cout << "q - quit"<< endl;

	FILE* logfile = fopen( "logfile.txt", "w");

	i = eXosip_init(NULL, NULL, 6060);
	if (i!=0)
	{
		fprintf (stderr, "test: could not initialize eXosip\n");
		__exit(0);  
	}
	eXosip_sdp_negotiation_remove_audio_payloads();
	reg_id = eXosip_register_init(identity, registrar, contact);
	j = eXosip_register(reg_id, 3600);
	std::cout<<"init"<<endl;

	eXosip_sdp_negotiation_add_codec(osip_strdup("0"),
		NULL,
		osip_strdup("RTP/AVP"),
		NULL, NULL, NULL,
		NULL,NULL,
		osip_strdup("0 PCMU/8000"));

	eXosip_sdp_negotiation_add_codec(osip_strdup("8"),
		NULL,
		osip_strdup("RTP/AVP"),
		NULL, NULL, NULL,
		NULL,NULL,
		osip_strdup("8 PCMA/8000"));


	eXosip_set_mode(EVENT_MODE);

	osip_message_t *invite;

	std::cout << "oSIP>"<<endl;
	while( run )
	{
		josua_event_get();

		if ( _kbhit() )
		{
			switch ( _getch() )
			{
			case 'a':
				std::cout << "answer"<< endl;
				eXosip_lock();
				eXosip_answer_call(call.did, 200, 0);
				eXosip_unlock();
				break;

			case 'h':
				std::cout << "hangup"<< endl;
				eXosip_lock();
				eXosip_terminate_call( call.cid, call.did );
				eXosip_unlock();
				break;

			case 'z':
				std::cout << "zhuxiao"<< endl;
				expires = 0;
				reg_id = eXosip_register_init(identity, registrar, contact);
				j = eXosip_register(reg_id, 0);
				break;

			case 'c':
				std::cout << "call"<< endl;
				i = eXosip_build_initial_invite(&invite,
					destip,       //掩請
					identity,     //翋請
					NULL,
					"oSIP phone");
				if (i!=0)
				{
					fprintf (stderr, "eXosip_build_initial_invite failed\n");
					__exit(0);
				}
				eXosip_lock();
				eXosip_initiate_call(invite, NULL, NULL, "10500");
				eXosip_unlock();
				break;

			case 'q':
				eXosip_quit();
				std::cout << "quit"<< endl;
				run = false;
				break;
			}
		}
	}
	return 0;
}

