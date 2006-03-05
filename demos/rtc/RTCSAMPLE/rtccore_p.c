

/* this ALWAYS GENERATED file contains the proxy stub code */


 /* File created by MIDL compiler version 6.00.0366 */
/* at Fri Feb 24 21:15:12 2006
 */
/* Compiler settings for rtccore.idl:
    Oicf, W1, Zp8, env=Win32 (32b run)
    protocol : dce , ms_ext, c_ext, robust
    error checks: allocation ref bounds_check enum stub_data 
    VC __declspec() decoration level: 
         __declspec(uuid()), __declspec(selectany), __declspec(novtable)
         DECLSPEC_UUID(), MIDL_INTERFACE()
*/
//@@MIDL_FILE_HEADING(  )

#if !defined(_M_IA64) && !defined(_M_AMD64)


#pragma warning( disable: 4049 )  /* more than 64k source lines */
#if _MSC_VER >= 1200
#pragma warning(push)
#endif
#pragma warning( disable: 4100 ) /* unreferenced arguments in x86 call */
#pragma warning( disable: 4211 )  /* redefine extent to static */
#pragma warning( disable: 4232 )  /* dllimport identity*/
#pragma optimize("", off ) 

#define USE_STUBLESS_PROXY


/* verify that the <rpcproxy.h> version is high enough to compile this file*/
#ifndef __REDQ_RPCPROXY_H_VERSION__
#define __REQUIRED_RPCPROXY_H_VERSION__ 475
#endif


#include "rpcproxy.h"
#ifndef __RPCPROXY_H_VERSION__
#error this stub requires an updated version of <rpcproxy.h>
#endif // __RPCPROXY_H_VERSION__


#include "rtccore.h"

#define TYPE_FORMAT_STRING_SIZE   2435                              
#define PROC_FORMAT_STRING_SIZE   9835                              
#define TRANSMIT_AS_TABLE_SIZE    0            
#define WIRE_MARSHAL_TABLE_SIZE   2            

typedef struct _MIDL_TYPE_FORMAT_STRING
    {
    short          Pad;
    unsigned char  Format[ TYPE_FORMAT_STRING_SIZE ];
    } MIDL_TYPE_FORMAT_STRING;

typedef struct _MIDL_PROC_FORMAT_STRING
    {
    short          Pad;
    unsigned char  Format[ PROC_FORMAT_STRING_SIZE ];
    } MIDL_PROC_FORMAT_STRING;


static RPC_SYNTAX_IDENTIFIER  _RpcTransferSyntax = 
{{0x8A885D04,0x1CEB,0x11C9,{0x9F,0xE8,0x08,0x00,0x2B,0x10,0x48,0x60}},{2,0}};


extern const MIDL_TYPE_FORMAT_STRING __MIDL_TypeFormatString;
extern const MIDL_PROC_FORMAT_STRING __MIDL_ProcFormatString;


extern const MIDL_STUB_DESC Object_StubDesc;


extern const MIDL_SERVER_INFO IRTCClient_ServerInfo;
extern const MIDL_STUBLESS_PROXY_INFO IRTCClient_ProxyInfo;


extern const MIDL_STUB_DESC Object_StubDesc;


extern const MIDL_SERVER_INFO IRTCClient2_ServerInfo;
extern const MIDL_STUBLESS_PROXY_INFO IRTCClient2_ProxyInfo;


extern const MIDL_STUB_DESC Object_StubDesc;


extern const MIDL_SERVER_INFO IRTCClientPresence_ServerInfo;
extern const MIDL_STUBLESS_PROXY_INFO IRTCClientPresence_ProxyInfo;


extern const MIDL_STUB_DESC Object_StubDesc;


extern const MIDL_SERVER_INFO IRTCClientPresence2_ServerInfo;
extern const MIDL_STUBLESS_PROXY_INFO IRTCClientPresence2_ProxyInfo;


extern const MIDL_STUB_DESC Object_StubDesc;


extern const MIDL_SERVER_INFO IRTCClientProvisioning_ServerInfo;
extern const MIDL_STUBLESS_PROXY_INFO IRTCClientProvisioning_ProxyInfo;


extern const MIDL_STUB_DESC Object_StubDesc;


extern const MIDL_SERVER_INFO IRTCClientProvisioning2_ServerInfo;
extern const MIDL_STUBLESS_PROXY_INFO IRTCClientProvisioning2_ProxyInfo;


extern const MIDL_STUB_DESC Object_StubDesc;


extern const MIDL_SERVER_INFO IRTCProfile_ServerInfo;
extern const MIDL_STUBLESS_PROXY_INFO IRTCProfile_ProxyInfo;


extern const MIDL_STUB_DESC Object_StubDesc;


extern const MIDL_SERVER_INFO IRTCProfile2_ServerInfo;
extern const MIDL_STUBLESS_PROXY_INFO IRTCProfile2_ProxyInfo;


extern const MIDL_STUB_DESC Object_StubDesc;


extern const MIDL_SERVER_INFO IRTCProfile3_ServerInfo;
extern const MIDL_STUBLESS_PROXY_INFO IRTCProfile3_ProxyInfo;


extern const MIDL_STUB_DESC Object_StubDesc;


extern const MIDL_SERVER_INFO IRTCSession_ServerInfo;
extern const MIDL_STUBLESS_PROXY_INFO IRTCSession_ProxyInfo;


extern const MIDL_STUB_DESC Object_StubDesc;


extern const MIDL_SERVER_INFO IRTCSession2_ServerInfo;
extern const MIDL_STUBLESS_PROXY_INFO IRTCSession2_ProxyInfo;


extern const MIDL_STUB_DESC Object_StubDesc;


extern const MIDL_SERVER_INFO IRTCSession3_ServerInfo;
extern const MIDL_STUBLESS_PROXY_INFO IRTCSession3_ProxyInfo;


extern const MIDL_STUB_DESC Object_StubDesc;


extern const MIDL_SERVER_INFO IRTCSessionCallControl_ServerInfo;
extern const MIDL_STUBLESS_PROXY_INFO IRTCSessionCallControl_ProxyInfo;


extern const MIDL_STUB_DESC Object_StubDesc;


extern const MIDL_SERVER_INFO IRTCParticipant_ServerInfo;
extern const MIDL_STUBLESS_PROXY_INFO IRTCParticipant_ProxyInfo;


extern const MIDL_STUB_DESC Object_StubDesc;


extern const MIDL_SERVER_INFO IRTCParticipant2_ServerInfo;
extern const MIDL_STUBLESS_PROXY_INFO IRTCParticipant2_ProxyInfo;


extern const MIDL_STUB_DESC Object_StubDesc;


extern const MIDL_SERVER_INFO IRTCRoamingEvent_ServerInfo;
extern const MIDL_STUBLESS_PROXY_INFO IRTCRoamingEvent_ProxyInfo;


extern const MIDL_STUB_DESC Object_StubDesc;


extern const MIDL_SERVER_INFO IRTCProfileEvent_ServerInfo;
extern const MIDL_STUBLESS_PROXY_INFO IRTCProfileEvent_ProxyInfo;


extern const MIDL_STUB_DESC Object_StubDesc;


extern const MIDL_SERVER_INFO IRTCProfileEvent2_ServerInfo;
extern const MIDL_STUBLESS_PROXY_INFO IRTCProfileEvent2_ProxyInfo;


extern const MIDL_STUB_DESC Object_StubDesc;


extern const MIDL_SERVER_INFO IRTCClientEvent_ServerInfo;
extern const MIDL_STUBLESS_PROXY_INFO IRTCClientEvent_ProxyInfo;


extern const MIDL_STUB_DESC Object_StubDesc;


extern const MIDL_SERVER_INFO IRTCRegistrationStateChangeEvent_ServerInfo;
extern const MIDL_STUBLESS_PROXY_INFO IRTCRegistrationStateChangeEvent_ProxyInfo;


extern const MIDL_STUB_DESC Object_StubDesc;


extern const MIDL_SERVER_INFO IRTCSessionStateChangeEvent_ServerInfo;
extern const MIDL_STUBLESS_PROXY_INFO IRTCSessionStateChangeEvent_ProxyInfo;


extern const MIDL_STUB_DESC Object_StubDesc;


extern const MIDL_SERVER_INFO IRTCSessionStateChangeEvent2_ServerInfo;
extern const MIDL_STUBLESS_PROXY_INFO IRTCSessionStateChangeEvent2_ProxyInfo;


extern const MIDL_STUB_DESC Object_StubDesc;


extern const MIDL_SERVER_INFO IRTCSessionOperationCompleteEvent_ServerInfo;
extern const MIDL_STUBLESS_PROXY_INFO IRTCSessionOperationCompleteEvent_ProxyInfo;


extern const MIDL_STUB_DESC Object_StubDesc;


extern const MIDL_SERVER_INFO IRTCSessionOperationCompleteEvent2_ServerInfo;
extern const MIDL_STUBLESS_PROXY_INFO IRTCSessionOperationCompleteEvent2_ProxyInfo;


extern const MIDL_STUB_DESC Object_StubDesc;


extern const MIDL_SERVER_INFO IRTCParticipantStateChangeEvent_ServerInfo;
extern const MIDL_STUBLESS_PROXY_INFO IRTCParticipantStateChangeEvent_ProxyInfo;


extern const MIDL_STUB_DESC Object_StubDesc;


extern const MIDL_SERVER_INFO IRTCMediaEvent_ServerInfo;
extern const MIDL_STUBLESS_PROXY_INFO IRTCMediaEvent_ProxyInfo;


extern const MIDL_STUB_DESC Object_StubDesc;


extern const MIDL_SERVER_INFO IRTCIntensityEvent_ServerInfo;
extern const MIDL_STUBLESS_PROXY_INFO IRTCIntensityEvent_ProxyInfo;


extern const MIDL_STUB_DESC Object_StubDesc;


extern const MIDL_SERVER_INFO IRTCMessagingEvent_ServerInfo;
extern const MIDL_STUBLESS_PROXY_INFO IRTCMessagingEvent_ProxyInfo;


extern const MIDL_STUB_DESC Object_StubDesc;


extern const MIDL_SERVER_INFO IRTCBuddyEvent_ServerInfo;
extern const MIDL_STUBLESS_PROXY_INFO IRTCBuddyEvent_ProxyInfo;


extern const MIDL_STUB_DESC Object_StubDesc;


extern const MIDL_SERVER_INFO IRTCBuddyEvent2_ServerInfo;
extern const MIDL_STUBLESS_PROXY_INFO IRTCBuddyEvent2_ProxyInfo;


extern const MIDL_STUB_DESC Object_StubDesc;


extern const MIDL_SERVER_INFO IRTCWatcherEvent_ServerInfo;
extern const MIDL_STUBLESS_PROXY_INFO IRTCWatcherEvent_ProxyInfo;


extern const MIDL_STUB_DESC Object_StubDesc;


extern const MIDL_SERVER_INFO IRTCWatcherEvent2_ServerInfo;
extern const MIDL_STUBLESS_PROXY_INFO IRTCWatcherEvent2_ProxyInfo;


extern const MIDL_STUB_DESC Object_StubDesc;


extern const MIDL_SERVER_INFO IRTCBuddyGroupEvent_ServerInfo;
extern const MIDL_STUBLESS_PROXY_INFO IRTCBuddyGroupEvent_ProxyInfo;


extern const MIDL_STUB_DESC Object_StubDesc;


extern const MIDL_SERVER_INFO IRTCInfoEvent_ServerInfo;
extern const MIDL_STUBLESS_PROXY_INFO IRTCInfoEvent_ProxyInfo;


extern const MIDL_STUB_DESC Object_StubDesc;


extern const MIDL_SERVER_INFO IRTCMediaRequestEvent_ServerInfo;
extern const MIDL_STUBLESS_PROXY_INFO IRTCMediaRequestEvent_ProxyInfo;


extern const MIDL_STUB_DESC Object_StubDesc;


extern const MIDL_SERVER_INFO IRTCReInviteEvent_ServerInfo;
extern const MIDL_STUBLESS_PROXY_INFO IRTCReInviteEvent_ProxyInfo;


extern const MIDL_STUB_DESC Object_StubDesc;


extern const MIDL_SERVER_INFO IRTCPresencePropertyEvent_ServerInfo;
extern const MIDL_STUBLESS_PROXY_INFO IRTCPresencePropertyEvent_ProxyInfo;


extern const MIDL_STUB_DESC Object_StubDesc;


extern const MIDL_SERVER_INFO IRTCPresenceDataEvent_ServerInfo;
extern const MIDL_STUBLESS_PROXY_INFO IRTCPresenceDataEvent_ProxyInfo;


extern const MIDL_STUB_DESC Object_StubDesc;


extern const MIDL_SERVER_INFO IRTCPresenceStatusEvent_ServerInfo;
extern const MIDL_STUBLESS_PROXY_INFO IRTCPresenceStatusEvent_ProxyInfo;


extern const MIDL_STUB_DESC Object_StubDesc;


extern const MIDL_SERVER_INFO IRTCCollection_ServerInfo;
extern const MIDL_STUBLESS_PROXY_INFO IRTCCollection_ProxyInfo;


extern const MIDL_STUB_DESC Object_StubDesc;


extern const MIDL_SERVER_INFO IRTCEnumParticipants_ServerInfo;
extern const MIDL_STUBLESS_PROXY_INFO IRTCEnumParticipants_ProxyInfo;


extern const MIDL_STUB_DESC Object_StubDesc;


extern const MIDL_SERVER_INFO IRTCEnumProfiles_ServerInfo;
extern const MIDL_STUBLESS_PROXY_INFO IRTCEnumProfiles_ProxyInfo;


extern const MIDL_STUB_DESC Object_StubDesc;


extern const MIDL_SERVER_INFO IRTCEnumBuddies_ServerInfo;
extern const MIDL_STUBLESS_PROXY_INFO IRTCEnumBuddies_ProxyInfo;


extern const MIDL_STUB_DESC Object_StubDesc;


extern const MIDL_SERVER_INFO IRTCEnumWatchers_ServerInfo;
extern const MIDL_STUBLESS_PROXY_INFO IRTCEnumWatchers_ProxyInfo;


extern const MIDL_STUB_DESC Object_StubDesc;


extern const MIDL_SERVER_INFO IRTCEnumGroups_ServerInfo;
extern const MIDL_STUBLESS_PROXY_INFO IRTCEnumGroups_ProxyInfo;


extern const MIDL_STUB_DESC Object_StubDesc;


extern const MIDL_SERVER_INFO IRTCPresenceContact_ServerInfo;
extern const MIDL_STUBLESS_PROXY_INFO IRTCPresenceContact_ProxyInfo;


extern const MIDL_STUB_DESC Object_StubDesc;


extern const MIDL_SERVER_INFO IRTCBuddy_ServerInfo;
extern const MIDL_STUBLESS_PROXY_INFO IRTCBuddy_ProxyInfo;


extern const MIDL_STUB_DESC Object_StubDesc;


extern const MIDL_SERVER_INFO IRTCBuddy2_ServerInfo;
extern const MIDL_STUBLESS_PROXY_INFO IRTCBuddy2_ProxyInfo;


extern const MIDL_STUB_DESC Object_StubDesc;


extern const MIDL_SERVER_INFO IRTCWatcher_ServerInfo;
extern const MIDL_STUBLESS_PROXY_INFO IRTCWatcher_ProxyInfo;


extern const MIDL_STUB_DESC Object_StubDesc;


extern const MIDL_SERVER_INFO IRTCWatcher2_ServerInfo;
extern const MIDL_STUBLESS_PROXY_INFO IRTCWatcher2_ProxyInfo;


extern const MIDL_STUB_DESC Object_StubDesc;


extern const MIDL_SERVER_INFO IRTCBuddyGroup_ServerInfo;
extern const MIDL_STUBLESS_PROXY_INFO IRTCBuddyGroup_ProxyInfo;


extern const MIDL_STUB_DESC Object_StubDesc;


extern const MIDL_SERVER_INFO IRTCEventNotification_ServerInfo;
extern const MIDL_STUBLESS_PROXY_INFO IRTCEventNotification_ProxyInfo;


extern const MIDL_STUB_DESC Object_StubDesc;


extern const MIDL_SERVER_INFO IRTCPortManager_ServerInfo;
extern const MIDL_STUBLESS_PROXY_INFO IRTCPortManager_ProxyInfo;


extern const MIDL_STUB_DESC Object_StubDesc;


extern const MIDL_SERVER_INFO IRTCPortManager2_ServerInfo;
extern const MIDL_STUBLESS_PROXY_INFO IRTCPortManager2_ProxyInfo;


extern const MIDL_STUB_DESC Object_StubDesc;


extern const MIDL_SERVER_INFO IRTCSessionPortManagement_ServerInfo;
extern const MIDL_STUBLESS_PROXY_INFO IRTCSessionPortManagement_ProxyInfo;


extern const MIDL_STUB_DESC Object_StubDesc;


extern const MIDL_SERVER_INFO IRTCClientPortManagement_ServerInfo;
extern const MIDL_STUBLESS_PROXY_INFO IRTCClientPortManagement_ProxyInfo;


extern const MIDL_STUB_DESC Object_StubDesc;


extern const MIDL_SERVER_INFO IRTCUserSearch_ServerInfo;
extern const MIDL_STUBLESS_PROXY_INFO IRTCUserSearch_ProxyInfo;


extern const MIDL_STUB_DESC Object_StubDesc;


extern const MIDL_SERVER_INFO IRTCUserSearchQuery_ServerInfo;
extern const MIDL_STUBLESS_PROXY_INFO IRTCUserSearchQuery_ProxyInfo;


extern const MIDL_STUB_DESC Object_StubDesc;


extern const MIDL_SERVER_INFO IRTCUserSearchResult_ServerInfo;
extern const MIDL_STUBLESS_PROXY_INFO IRTCUserSearchResult_ProxyInfo;


extern const MIDL_STUB_DESC Object_StubDesc;


extern const MIDL_SERVER_INFO IRTCEnumUserSearchResults_ServerInfo;
extern const MIDL_STUBLESS_PROXY_INFO IRTCEnumUserSearchResults_ProxyInfo;


extern const MIDL_STUB_DESC Object_StubDesc;


extern const MIDL_SERVER_INFO IRTCUserSearchResultsEvent_ServerInfo;
extern const MIDL_STUBLESS_PROXY_INFO IRTCUserSearchResultsEvent_ProxyInfo;


extern const MIDL_STUB_DESC Object_StubDesc;


extern const MIDL_SERVER_INFO IRTCSessionReferStatusEvent_ServerInfo;
extern const MIDL_STUBLESS_PROXY_INFO IRTCSessionReferStatusEvent_ProxyInfo;


extern const MIDL_STUB_DESC Object_StubDesc;


extern const MIDL_SERVER_INFO IRTCSessionReferredEvent_ServerInfo;
extern const MIDL_STUBLESS_PROXY_INFO IRTCSessionReferredEvent_ProxyInfo;


extern const MIDL_STUB_DESC Object_StubDesc;


extern const MIDL_SERVER_INFO IRTCSessionDescriptionManager_ServerInfo;
extern const MIDL_STUBLESS_PROXY_INFO IRTCSessionDescriptionManager_ProxyInfo;


extern const MIDL_STUB_DESC Object_StubDesc;


extern const MIDL_SERVER_INFO IRTCEnumPresenceDevices_ServerInfo;
extern const MIDL_STUBLESS_PROXY_INFO IRTCEnumPresenceDevices_ProxyInfo;


extern const MIDL_STUB_DESC Object_StubDesc;


extern const MIDL_SERVER_INFO IRTCPresenceDevice_ServerInfo;
extern const MIDL_STUBLESS_PROXY_INFO IRTCPresenceDevice_ProxyInfo;


extern const MIDL_STUB_DESC Object_StubDesc;


extern const MIDL_SERVER_INFO IRTCPresenceDevice2_ServerInfo;
extern const MIDL_STUBLESS_PROXY_INFO IRTCPresenceDevice2_ProxyInfo;


extern const USER_MARSHAL_ROUTINE_QUADRUPLE UserMarshalRoutines[ WIRE_MARSHAL_TABLE_SIZE ];

#if !defined(__RPC_WIN32__)
#error  Invalid build platform for this stub.
#endif

#if !(TARGET_IS_NT50_OR_LATER)
#error You need a Windows 2000 or later to run this stub because it uses these features:
#error   /robust command line switch.
#error However, your C/C++ compilation flags indicate you intend to run this app on earlier systems.
#error This app will die there with the RPC_X_WRONG_STUB_VERSION error.
#endif


static const MIDL_PROC_FORMAT_STRING __MIDL_ProcFormatString =
    {
        0,
        {

	/* Procedure Initialize */

			0x33,		/* FC_AUTO_HANDLE */
			0x6c,		/* Old Flags:  object, Oi2 */
/*  2 */	NdrFcLong( 0x0 ),	/* 0 */
/*  6 */	NdrFcShort( 0x3 ),	/* 3 */
/*  8 */	NdrFcShort( 0x8 ),	/* x86 Stack size/offset = 8 */
/* 10 */	NdrFcShort( 0x0 ),	/* 0 */
/* 12 */	NdrFcShort( 0x8 ),	/* 8 */
/* 14 */	0x44,		/* Oi2 Flags:  has return, has ext, */
			0x1,		/* 1 */
/* 16 */	0x8,		/* 8 */
			0x1,		/* Ext Flags:  new corr desc, */
/* 18 */	NdrFcShort( 0x0 ),	/* 0 */
/* 20 */	NdrFcShort( 0x0 ),	/* 0 */
/* 22 */	NdrFcShort( 0x0 ),	/* 0 */

	/* Return value */

/* 24 */	NdrFcShort( 0x70 ),	/* Flags:  out, return, base type, */
/* 26 */	NdrFcShort( 0x4 ),	/* x86 Stack size/offset = 4 */
/* 28 */	0x8,		/* FC_LONG */
			0x0,		/* 0 */

	/* Procedure Reset */


	/* Procedure Reset */


	/* Procedure Reset */


	/* Procedure Reset */


	/* Procedure Reset */


	/* Procedure Reset */


	/* Procedure Reset */


	/* Procedure Shutdown */

/* 30 */	0x33,		/* FC_AUTO_HANDLE */
			0x6c,		/* Old Flags:  object, Oi2 */
/* 32 */	NdrFcLong( 0x0 ),	/* 0 */
/* 36 */	NdrFcShort( 0x4 ),	/* 4 */
/* 38 */	NdrFcShort( 0x8 ),	/* x86 Stack size/offset = 8 */
/* 40 */	NdrFcShort( 0x0 ),	/* 0 */
/* 42 */	NdrFcShort( 0x8 ),	/* 8 */
/* 44 */	0x44,		/* Oi2 Flags:  has return, has ext, */
			0x1,		/* 1 */
/* 46 */	0x8,		/* 8 */
			0x1,		/* Ext Flags:  new corr desc, */
/* 48 */	NdrFcShort( 0x0 ),	/* 0 */
/* 50 */	NdrFcShort( 0x0 ),	/* 0 */
/* 52 */	NdrFcShort( 0x0 ),	/* 0 */

	/* Return value */


	/* Return value */


	/* Return value */


	/* Return value */


	/* Return value */


	/* Return value */


	/* Return value */


	/* Return value */

/* 54 */	NdrFcShort( 0x70 ),	/* Flags:  out, return, base type, */
/* 56 */	NdrFcShort( 0x4 ),	/* x86 Stack size/offset = 4 */
/* 58 */	0x8,		/* FC_LONG */
			0x0,		/* 0 */

	/* Procedure PrepareForShutdown */

/* 60 */	0x33,		/* FC_AUTO_HANDLE */
			0x6c,		/* Old Flags:  object, Oi2 */
/* 62 */	NdrFcLong( 0x0 ),	/* 0 */
/* 66 */	NdrFcShort( 0x5 ),	/* 5 */
/* 68 */	NdrFcShort( 0x8 ),	/* x86 Stack size/offset = 8 */
/* 70 */	NdrFcShort( 0x0 ),	/* 0 */
/* 72 */	NdrFcShort( 0x8 ),	/* 8 */
/* 74 */	0x44,		/* Oi2 Flags:  has return, has ext, */
			0x1,		/* 1 */
/* 76 */	0x8,		/* 8 */
			0x1,		/* Ext Flags:  new corr desc, */
/* 78 */	NdrFcShort( 0x0 ),	/* 0 */
/* 80 */	NdrFcShort( 0x0 ),	/* 0 */
/* 82 */	NdrFcShort( 0x0 ),	/* 0 */

	/* Return value */

/* 84 */	NdrFcShort( 0x70 ),	/* Flags:  out, return, base type, */
/* 86 */	NdrFcShort( 0x4 ),	/* x86 Stack size/offset = 4 */
/* 88 */	0x8,		/* FC_LONG */
			0x0,		/* 0 */

	/* Procedure put_EventFilter */

/* 90 */	0x33,		/* FC_AUTO_HANDLE */
			0x6c,		/* Old Flags:  object, Oi2 */
/* 92 */	NdrFcLong( 0x0 ),	/* 0 */
/* 96 */	NdrFcShort( 0x6 ),	/* 6 */
/* 98 */	NdrFcShort( 0xc ),	/* x86 Stack size/offset = 12 */
/* 100 */	NdrFcShort( 0x8 ),	/* 8 */
/* 102 */	NdrFcShort( 0x8 ),	/* 8 */
/* 104 */	0x44,		/* Oi2 Flags:  has return, has ext, */
			0x2,		/* 2 */
/* 106 */	0x8,		/* 8 */
			0x1,		/* Ext Flags:  new corr desc, */
/* 108 */	NdrFcShort( 0x0 ),	/* 0 */
/* 110 */	NdrFcShort( 0x0 ),	/* 0 */
/* 112 */	NdrFcShort( 0x0 ),	/* 0 */

	/* Parameter lFilter */

/* 114 */	NdrFcShort( 0x48 ),	/* Flags:  in, base type, */
/* 116 */	NdrFcShort( 0x4 ),	/* x86 Stack size/offset = 4 */
/* 118 */	0x8,		/* FC_LONG */
			0x0,		/* 0 */

	/* Return value */

/* 120 */	NdrFcShort( 0x70 ),	/* Flags:  out, return, base type, */
/* 122 */	NdrFcShort( 0x8 ),	/* x86 Stack size/offset = 8 */
/* 124 */	0x8,		/* FC_LONG */
			0x0,		/* 0 */

	/* Procedure get_Count */


	/* Procedure get_StatusCode */


	/* Procedure get_StatusCode */


	/* Procedure get_StatusCode */


	/* Procedure get_Level */


	/* Procedure get_MediaType */


	/* Procedure get_EventFilter */

/* 126 */	0x33,		/* FC_AUTO_HANDLE */
			0x6c,		/* Old Flags:  object, Oi2 */
/* 128 */	NdrFcLong( 0x0 ),	/* 0 */
/* 132 */	NdrFcShort( 0x7 ),	/* 7 */
/* 134 */	NdrFcShort( 0xc ),	/* x86 Stack size/offset = 12 */
/* 136 */	NdrFcShort( 0x0 ),	/* 0 */
/* 138 */	NdrFcShort( 0x24 ),	/* 36 */
/* 140 */	0x44,		/* Oi2 Flags:  has return, has ext, */
			0x2,		/* 2 */
/* 142 */	0x8,		/* 8 */
			0x1,		/* Ext Flags:  new corr desc, */
/* 144 */	NdrFcShort( 0x0 ),	/* 0 */
/* 146 */	NdrFcShort( 0x0 ),	/* 0 */
/* 148 */	NdrFcShort( 0x0 ),	/* 0 */

	/* Parameter lCount */


	/* Parameter plStatusCode */


	/* Parameter plStatusCode */


	/* Parameter plStatusCode */


	/* Parameter plLevel */


	/* Parameter pMediaType */


	/* Parameter plFilter */

/* 150 */	NdrFcShort( 0x2150 ),	/* Flags:  out, base type, simple ref, srv alloc size=8 */
/* 152 */	NdrFcShort( 0x4 ),	/* x86 Stack size/offset = 4 */
/* 154 */	0x8,		/* FC_LONG */
			0x0,		/* 0 */

	/* Return value */


	/* Return value */


	/* Return value */


	/* Return value */


	/* Return value */


	/* Return value */


	/* Return value */

/* 156 */	NdrFcShort( 0x70 ),	/* Flags:  out, return, base type, */
/* 158 */	NdrFcShort( 0x8 ),	/* x86 Stack size/offset = 8 */
/* 160 */	0x8,		/* FC_LONG */
			0x0,		/* 0 */

	/* Procedure SetPreferredMediaTypes */

/* 162 */	0x33,		/* FC_AUTO_HANDLE */
			0x6c,		/* Old Flags:  object, Oi2 */
/* 164 */	NdrFcLong( 0x0 ),	/* 0 */
/* 168 */	NdrFcShort( 0x8 ),	/* 8 */
/* 170 */	NdrFcShort( 0x10 ),	/* x86 Stack size/offset = 16 */
/* 172 */	NdrFcShort( 0xe ),	/* 14 */
/* 174 */	NdrFcShort( 0x8 ),	/* 8 */
/* 176 */	0x44,		/* Oi2 Flags:  has return, has ext, */
			0x3,		/* 3 */
/* 178 */	0x8,		/* 8 */
			0x1,		/* Ext Flags:  new corr desc, */
/* 180 */	NdrFcShort( 0x0 ),	/* 0 */
/* 182 */	NdrFcShort( 0x0 ),	/* 0 */
/* 184 */	NdrFcShort( 0x0 ),	/* 0 */

	/* Parameter lMediaTypes */

/* 186 */	NdrFcShort( 0x48 ),	/* Flags:  in, base type, */
/* 188 */	NdrFcShort( 0x4 ),	/* x86 Stack size/offset = 4 */
/* 190 */	0x8,		/* FC_LONG */
			0x0,		/* 0 */

	/* Parameter fPersistent */

/* 192 */	NdrFcShort( 0x48 ),	/* Flags:  in, base type, */
/* 194 */	NdrFcShort( 0x8 ),	/* x86 Stack size/offset = 8 */
/* 196 */	0x6,		/* FC_SHORT */
			0x0,		/* 0 */

	/* Return value */

/* 198 */	NdrFcShort( 0x70 ),	/* Flags:  out, return, base type, */
/* 200 */	NdrFcShort( 0xc ),	/* x86 Stack size/offset = 12 */
/* 202 */	0x8,		/* FC_LONG */
			0x0,		/* 0 */

	/* Procedure get_StatusCode */


	/* Procedure get_CurrentMedia */


	/* Procedure get_StatusCode */


	/* Procedure get_StatusCode */


	/* Procedure get_Max */


	/* Procedure get_StatusCode */


	/* Procedure get_StatusCode */


	/* Procedure get_StatusCode */


	/* Procedure get_StatusCode */


	/* Procedure get_StatusCode */


	/* Procedure get_StatusCode */


	/* Procedure get_FederationFlag */


	/* Procedure get_SessionCapabilities */


	/* Procedure get_PreferredMediaTypes */

/* 204 */	0x33,		/* FC_AUTO_HANDLE */
			0x6c,		/* Old Flags:  object, Oi2 */
/* 206 */	NdrFcLong( 0x0 ),	/* 0 */
/* 210 */	NdrFcShort( 0x9 ),	/* 9 */
/* 212 */	NdrFcShort( 0xc ),	/* x86 Stack size/offset = 12 */
/* 214 */	NdrFcShort( 0x0 ),	/* 0 */
/* 216 */	NdrFcShort( 0x24 ),	/* 36 */
/* 218 */	0x44,		/* Oi2 Flags:  has return, has ext, */
			0x2,		/* 2 */
/* 220 */	0x8,		/* 8 */
			0x1,		/* Ext Flags:  new corr desc, */
/* 222 */	NdrFcShort( 0x0 ),	/* 0 */
/* 224 */	NdrFcShort( 0x0 ),	/* 0 */
/* 226 */	NdrFcShort( 0x0 ),	/* 0 */

	/* Parameter plStatusCode */


	/* Parameter plMediaTypes */


	/* Parameter plStatusCode */


	/* Parameter plStatusCode */


	/* Parameter plMax */


	/* Parameter plStatusCode */


	/* Parameter plStatusCode */


	/* Parameter plStatusCode */


	/* Parameter plStatusCode */


	/* Parameter plStatusCode */


	/* Parameter plStatusCode */


	/* Parameter plFederationFlag */


	/* Parameter plSupportedSessions */


	/* Parameter plMediaTypes */

/* 228 */	NdrFcShort( 0x2150 ),	/* Flags:  out, base type, simple ref, srv alloc size=8 */
/* 230 */	NdrFcShort( 0x4 ),	/* x86 Stack size/offset = 4 */
/* 232 */	0x8,		/* FC_LONG */
			0x0,		/* 0 */

	/* Return value */


	/* Return value */


	/* Return value */


	/* Return value */


	/* Return value */


	/* Return value */


	/* Return value */


	/* Return value */


	/* Return value */


	/* Return value */


	/* Return value */


	/* Return value */


	/* Return value */


	/* Return value */

/* 234 */	NdrFcShort( 0x70 ),	/* Flags:  out, return, base type, */
/* 236 */	NdrFcShort( 0x8 ),	/* x86 Stack size/offset = 8 */
/* 238 */	0x8,		/* FC_LONG */
			0x0,		/* 0 */

	/* Procedure get_StatusCode */


	/* Procedure get_MediaCapabilities */

/* 240 */	0x33,		/* FC_AUTO_HANDLE */
			0x6c,		/* Old Flags:  object, Oi2 */
/* 242 */	NdrFcLong( 0x0 ),	/* 0 */
/* 246 */	NdrFcShort( 0xa ),	/* 10 */
/* 248 */	NdrFcShort( 0xc ),	/* x86 Stack size/offset = 12 */
/* 250 */	NdrFcShort( 0x0 ),	/* 0 */
/* 252 */	NdrFcShort( 0x24 ),	/* 36 */
/* 254 */	0x44,		/* Oi2 Flags:  has return, has ext, */
			0x2,		/* 2 */
/* 256 */	0x8,		/* 8 */
			0x1,		/* Ext Flags:  new corr desc, */
/* 258 */	NdrFcShort( 0x0 ),	/* 0 */
/* 260 */	NdrFcShort( 0x0 ),	/* 0 */
/* 262 */	NdrFcShort( 0x0 ),	/* 0 */

	/* Parameter plStatusCode */


	/* Parameter plMediaTypes */

/* 264 */	NdrFcShort( 0x2150 ),	/* Flags:  out, base type, simple ref, srv alloc size=8 */
/* 266 */	NdrFcShort( 0x4 ),	/* x86 Stack size/offset = 4 */
/* 268 */	0x8,		/* FC_LONG */
			0x0,		/* 0 */

	/* Return value */


	/* Return value */

/* 270 */	NdrFcShort( 0x70 ),	/* Flags:  out, return, base type, */
/* 272 */	NdrFcShort( 0x8 ),	/* x86 Stack size/offset = 8 */
/* 274 */	0x8,		/* FC_LONG */
			0x0,		/* 0 */

	/* Procedure CreateSession */

/* 276 */	0x33,		/* FC_AUTO_HANDLE */
			0x6c,		/* Old Flags:  object, Oi2 */
/* 278 */	NdrFcLong( 0x0 ),	/* 0 */
/* 282 */	NdrFcShort( 0xb ),	/* 11 */
/* 284 */	NdrFcShort( 0x1c ),	/* x86 Stack size/offset = 28 */
/* 286 */	NdrFcShort( 0xe ),	/* 14 */
/* 288 */	NdrFcShort( 0x8 ),	/* 8 */
/* 290 */	0x47,		/* Oi2 Flags:  srv must size, clt must size, has return, has ext, */
			0x6,		/* 6 */
/* 292 */	0x8,		/* 8 */
			0x5,		/* Ext Flags:  new corr desc, srv corr check, */
/* 294 */	NdrFcShort( 0x0 ),	/* 0 */
/* 296 */	NdrFcShort( 0x1 ),	/* 1 */
/* 298 */	NdrFcShort( 0x0 ),	/* 0 */

	/* Parameter enType */

/* 300 */	NdrFcShort( 0x48 ),	/* Flags:  in, base type, */
/* 302 */	NdrFcShort( 0x4 ),	/* x86 Stack size/offset = 4 */
/* 304 */	0xd,		/* FC_ENUM16 */
			0x0,		/* 0 */

	/* Parameter bstrLocalPhoneURI */

/* 306 */	NdrFcShort( 0x8b ),	/* Flags:  must size, must free, in, by val, */
/* 308 */	NdrFcShort( 0x8 ),	/* x86 Stack size/offset = 8 */
/* 310 */	NdrFcShort( 0x20 ),	/* Type Offset=32 */

	/* Parameter pProfile */

/* 312 */	NdrFcShort( 0xb ),	/* Flags:  must size, must free, in, */
/* 314 */	NdrFcShort( 0xc ),	/* x86 Stack size/offset = 12 */
/* 316 */	NdrFcShort( 0x2a ),	/* Type Offset=42 */

	/* Parameter lFlags */

/* 318 */	NdrFcShort( 0x48 ),	/* Flags:  in, base type, */
/* 320 */	NdrFcShort( 0x10 ),	/* x86 Stack size/offset = 16 */
/* 322 */	0x8,		/* FC_LONG */
			0x0,		/* 0 */

	/* Parameter ppSession */

/* 324 */	NdrFcShort( 0x13 ),	/* Flags:  must size, must free, out, */
/* 326 */	NdrFcShort( 0x14 ),	/* x86 Stack size/offset = 20 */
/* 328 */	NdrFcShort( 0x3c ),	/* Type Offset=60 */

	/* Return value */

/* 330 */	NdrFcShort( 0x70 ),	/* Flags:  out, return, base type, */
/* 332 */	NdrFcShort( 0x18 ),	/* x86 Stack size/offset = 24 */
/* 334 */	0x8,		/* FC_LONG */
			0x0,		/* 0 */

	/* Procedure put_State */


	/* Procedure put_ListenForIncomingSessions */

/* 336 */	0x33,		/* FC_AUTO_HANDLE */
			0x6c,		/* Old Flags:  object, Oi2 */
/* 338 */	NdrFcLong( 0x0 ),	/* 0 */
/* 342 */	NdrFcShort( 0xc ),	/* 12 */
/* 344 */	NdrFcShort( 0xc ),	/* x86 Stack size/offset = 12 */
/* 346 */	NdrFcShort( 0x6 ),	/* 6 */
/* 348 */	NdrFcShort( 0x8 ),	/* 8 */
/* 350 */	0x44,		/* Oi2 Flags:  has return, has ext, */
			0x2,		/* 2 */
/* 352 */	0x8,		/* 8 */
			0x1,		/* Ext Flags:  new corr desc, */
/* 354 */	NdrFcShort( 0x0 ),	/* 0 */
/* 356 */	NdrFcShort( 0x0 ),	/* 0 */
/* 358 */	NdrFcShort( 0x0 ),	/* 0 */

	/* Parameter enState */


	/* Parameter enListen */

/* 360 */	NdrFcShort( 0x48 ),	/* Flags:  in, base type, */
/* 362 */	NdrFcShort( 0x4 ),	/* x86 Stack size/offset = 4 */
/* 364 */	0xd,		/* FC_ENUM16 */
			0x0,		/* 0 */

	/* Return value */


	/* Return value */

/* 366 */	NdrFcShort( 0x70 ),	/* Flags:  out, return, base type, */
/* 368 */	NdrFcShort( 0x8 ),	/* x86 Stack size/offset = 8 */
/* 370 */	0x8,		/* FC_LONG */
			0x0,		/* 0 */

	/* Procedure get_State */


	/* Procedure get_ListenForIncomingSessions */

/* 372 */	0x33,		/* FC_AUTO_HANDLE */
			0x6c,		/* Old Flags:  object, Oi2 */
/* 374 */	NdrFcLong( 0x0 ),	/* 0 */
/* 378 */	NdrFcShort( 0xd ),	/* 13 */
/* 380 */	NdrFcShort( 0xc ),	/* x86 Stack size/offset = 12 */
/* 382 */	NdrFcShort( 0x0 ),	/* 0 */
/* 384 */	NdrFcShort( 0x22 ),	/* 34 */
/* 386 */	0x44,		/* Oi2 Flags:  has return, has ext, */
			0x2,		/* 2 */
/* 388 */	0x8,		/* 8 */
			0x1,		/* Ext Flags:  new corr desc, */
/* 390 */	NdrFcShort( 0x0 ),	/* 0 */
/* 392 */	NdrFcShort( 0x0 ),	/* 0 */
/* 394 */	NdrFcShort( 0x0 ),	/* 0 */

	/* Parameter pState */


	/* Parameter penListen */

/* 396 */	NdrFcShort( 0x2010 ),	/* Flags:  out, srv alloc size=8 */
/* 398 */	NdrFcShort( 0x4 ),	/* x86 Stack size/offset = 4 */
/* 400 */	NdrFcShort( 0x52 ),	/* Type Offset=82 */

	/* Return value */


	/* Return value */

/* 402 */	NdrFcShort( 0x70 ),	/* Flags:  out, return, base type, */
/* 404 */	NdrFcShort( 0x8 ),	/* x86 Stack size/offset = 8 */
/* 406 */	0x8,		/* FC_LONG */
			0x0,		/* 0 */

	/* Procedure get_NetworkAddresses */

/* 408 */	0x33,		/* FC_AUTO_HANDLE */
			0x6c,		/* Old Flags:  object, Oi2 */
/* 410 */	NdrFcLong( 0x0 ),	/* 0 */
/* 414 */	NdrFcShort( 0xe ),	/* 14 */
/* 416 */	NdrFcShort( 0x14 ),	/* x86 Stack size/offset = 20 */
/* 418 */	NdrFcShort( 0xc ),	/* 12 */
/* 420 */	NdrFcShort( 0x8 ),	/* 8 */
/* 422 */	0x45,		/* Oi2 Flags:  srv must size, has return, has ext, */
			0x4,		/* 4 */
/* 424 */	0x8,		/* 8 */
			0x3,		/* Ext Flags:  new corr desc, clt corr check, */
/* 426 */	NdrFcShort( 0x20 ),	/* 32 */
/* 428 */	NdrFcShort( 0x0 ),	/* 0 */
/* 430 */	NdrFcShort( 0x0 ),	/* 0 */

	/* Parameter fTCP */

/* 432 */	NdrFcShort( 0x48 ),	/* Flags:  in, base type, */
/* 434 */	NdrFcShort( 0x4 ),	/* x86 Stack size/offset = 4 */
/* 436 */	0x6,		/* FC_SHORT */
			0x0,		/* 0 */

	/* Parameter fExternal */

/* 438 */	NdrFcShort( 0x48 ),	/* Flags:  in, base type, */
/* 440 */	NdrFcShort( 0x8 ),	/* x86 Stack size/offset = 8 */
/* 442 */	0x6,		/* FC_SHORT */
			0x0,		/* 0 */

	/* Parameter pvAddresses */

/* 444 */	NdrFcShort( 0x4113 ),	/* Flags:  must size, must free, out, simple ref, srv alloc size=16 */
/* 446 */	NdrFcShort( 0xc ),	/* x86 Stack size/offset = 12 */
/* 448 */	NdrFcShort( 0x442 ),	/* Type Offset=1090 */

	/* Return value */

/* 450 */	NdrFcShort( 0x70 ),	/* Flags:  out, return, base type, */
/* 452 */	NdrFcShort( 0x10 ),	/* x86 Stack size/offset = 16 */
/* 454 */	0x8,		/* FC_LONG */
			0x0,		/* 0 */

	/* Procedure put_Volume */

/* 456 */	0x33,		/* FC_AUTO_HANDLE */
			0x6c,		/* Old Flags:  object, Oi2 */
/* 458 */	NdrFcLong( 0x0 ),	/* 0 */
/* 462 */	NdrFcShort( 0xf ),	/* 15 */
/* 464 */	NdrFcShort( 0x10 ),	/* x86 Stack size/offset = 16 */
/* 466 */	NdrFcShort( 0xe ),	/* 14 */
/* 468 */	NdrFcShort( 0x8 ),	/* 8 */
/* 470 */	0x44,		/* Oi2 Flags:  has return, has ext, */
			0x3,		/* 3 */
/* 472 */	0x8,		/* 8 */
			0x1,		/* Ext Flags:  new corr desc, */
/* 474 */	NdrFcShort( 0x0 ),	/* 0 */
/* 476 */	NdrFcShort( 0x0 ),	/* 0 */
/* 478 */	NdrFcShort( 0x0 ),	/* 0 */

	/* Parameter enDevice */

/* 480 */	NdrFcShort( 0x48 ),	/* Flags:  in, base type, */
/* 482 */	NdrFcShort( 0x4 ),	/* x86 Stack size/offset = 4 */
/* 484 */	0xd,		/* FC_ENUM16 */
			0x0,		/* 0 */

	/* Parameter lVolume */

/* 486 */	NdrFcShort( 0x48 ),	/* Flags:  in, base type, */
/* 488 */	NdrFcShort( 0x8 ),	/* x86 Stack size/offset = 8 */
/* 490 */	0x8,		/* FC_LONG */
			0x0,		/* 0 */

	/* Return value */

/* 492 */	NdrFcShort( 0x70 ),	/* Flags:  out, return, base type, */
/* 494 */	NdrFcShort( 0xc ),	/* x86 Stack size/offset = 12 */
/* 496 */	0x8,		/* FC_LONG */
			0x0,		/* 0 */

	/* Procedure get_Volume */

/* 498 */	0x33,		/* FC_AUTO_HANDLE */
			0x6c,		/* Old Flags:  object, Oi2 */
/* 500 */	NdrFcLong( 0x0 ),	/* 0 */
/* 504 */	NdrFcShort( 0x10 ),	/* 16 */
/* 506 */	NdrFcShort( 0x10 ),	/* x86 Stack size/offset = 16 */
/* 508 */	NdrFcShort( 0x6 ),	/* 6 */
/* 510 */	NdrFcShort( 0x24 ),	/* 36 */
/* 512 */	0x44,		/* Oi2 Flags:  has return, has ext, */
			0x3,		/* 3 */
/* 514 */	0x8,		/* 8 */
			0x1,		/* Ext Flags:  new corr desc, */
/* 516 */	NdrFcShort( 0x0 ),	/* 0 */
/* 518 */	NdrFcShort( 0x0 ),	/* 0 */
/* 520 */	NdrFcShort( 0x0 ),	/* 0 */

	/* Parameter enDevice */

/* 522 */	NdrFcShort( 0x48 ),	/* Flags:  in, base type, */
/* 524 */	NdrFcShort( 0x4 ),	/* x86 Stack size/offset = 4 */
/* 526 */	0xd,		/* FC_ENUM16 */
			0x0,		/* 0 */

	/* Parameter plVolume */

/* 528 */	NdrFcShort( 0x2150 ),	/* Flags:  out, base type, simple ref, srv alloc size=8 */
/* 530 */	NdrFcShort( 0x8 ),	/* x86 Stack size/offset = 8 */
/* 532 */	0x8,		/* FC_LONG */
			0x0,		/* 0 */

	/* Return value */

/* 534 */	NdrFcShort( 0x70 ),	/* Flags:  out, return, base type, */
/* 536 */	NdrFcShort( 0xc ),	/* x86 Stack size/offset = 12 */
/* 538 */	0x8,		/* FC_LONG */
			0x0,		/* 0 */

	/* Procedure put_AudioMuted */

/* 540 */	0x33,		/* FC_AUTO_HANDLE */
			0x6c,		/* Old Flags:  object, Oi2 */
/* 542 */	NdrFcLong( 0x0 ),	/* 0 */
/* 546 */	NdrFcShort( 0x11 ),	/* 17 */
/* 548 */	NdrFcShort( 0x10 ),	/* x86 Stack size/offset = 16 */
/* 550 */	NdrFcShort( 0xc ),	/* 12 */
/* 552 */	NdrFcShort( 0x8 ),	/* 8 */
/* 554 */	0x44,		/* Oi2 Flags:  has return, has ext, */
			0x3,		/* 3 */
/* 556 */	0x8,		/* 8 */
			0x1,		/* Ext Flags:  new corr desc, */
/* 558 */	NdrFcShort( 0x0 ),	/* 0 */
/* 560 */	NdrFcShort( 0x0 ),	/* 0 */
/* 562 */	NdrFcShort( 0x0 ),	/* 0 */

	/* Parameter enDevice */

/* 564 */	NdrFcShort( 0x48 ),	/* Flags:  in, base type, */
/* 566 */	NdrFcShort( 0x4 ),	/* x86 Stack size/offset = 4 */
/* 568 */	0xd,		/* FC_ENUM16 */
			0x0,		/* 0 */

	/* Parameter fMuted */

/* 570 */	NdrFcShort( 0x48 ),	/* Flags:  in, base type, */
/* 572 */	NdrFcShort( 0x8 ),	/* x86 Stack size/offset = 8 */
/* 574 */	0x6,		/* FC_SHORT */
			0x0,		/* 0 */

	/* Return value */

/* 576 */	NdrFcShort( 0x70 ),	/* Flags:  out, return, base type, */
/* 578 */	NdrFcShort( 0xc ),	/* x86 Stack size/offset = 12 */
/* 580 */	0x8,		/* FC_LONG */
			0x0,		/* 0 */

	/* Procedure get_AudioMuted */

/* 582 */	0x33,		/* FC_AUTO_HANDLE */
			0x6c,		/* Old Flags:  object, Oi2 */
/* 584 */	NdrFcLong( 0x0 ),	/* 0 */
/* 588 */	NdrFcShort( 0x12 ),	/* 18 */
/* 590 */	NdrFcShort( 0x10 ),	/* x86 Stack size/offset = 16 */
/* 592 */	NdrFcShort( 0x6 ),	/* 6 */
/* 594 */	NdrFcShort( 0x22 ),	/* 34 */
/* 596 */	0x44,		/* Oi2 Flags:  has return, has ext, */
			0x3,		/* 3 */
/* 598 */	0x8,		/* 8 */
			0x1,		/* Ext Flags:  new corr desc, */
/* 600 */	NdrFcShort( 0x0 ),	/* 0 */
/* 602 */	NdrFcShort( 0x0 ),	/* 0 */
/* 604 */	NdrFcShort( 0x0 ),	/* 0 */

	/* Parameter enDevice */

/* 606 */	NdrFcShort( 0x48 ),	/* Flags:  in, base type, */
/* 608 */	NdrFcShort( 0x4 ),	/* x86 Stack size/offset = 4 */
/* 610 */	0xd,		/* FC_ENUM16 */
			0x0,		/* 0 */

	/* Parameter pfMuted */

/* 612 */	NdrFcShort( 0x2150 ),	/* Flags:  out, base type, simple ref, srv alloc size=8 */
/* 614 */	NdrFcShort( 0x8 ),	/* x86 Stack size/offset = 8 */
/* 616 */	0x6,		/* FC_SHORT */
			0x0,		/* 0 */

	/* Return value */

/* 618 */	NdrFcShort( 0x70 ),	/* Flags:  out, return, base type, */
/* 620 */	NdrFcShort( 0xc ),	/* x86 Stack size/offset = 12 */
/* 622 */	0x8,		/* FC_LONG */
			0x0,		/* 0 */

	/* Procedure get_IVideoWindow */

/* 624 */	0x33,		/* FC_AUTO_HANDLE */
			0x6c,		/* Old Flags:  object, Oi2 */
/* 626 */	NdrFcLong( 0x0 ),	/* 0 */
/* 630 */	NdrFcShort( 0x13 ),	/* 19 */
/* 632 */	NdrFcShort( 0x10 ),	/* x86 Stack size/offset = 16 */
/* 634 */	NdrFcShort( 0x6 ),	/* 6 */
/* 636 */	NdrFcShort( 0x8 ),	/* 8 */
/* 638 */	0x45,		/* Oi2 Flags:  srv must size, has return, has ext, */
			0x3,		/* 3 */
/* 640 */	0x8,		/* 8 */
			0x1,		/* Ext Flags:  new corr desc, */
/* 642 */	NdrFcShort( 0x0 ),	/* 0 */
/* 644 */	NdrFcShort( 0x0 ),	/* 0 */
/* 646 */	NdrFcShort( 0x0 ),	/* 0 */

	/* Parameter enDevice */

/* 648 */	NdrFcShort( 0x48 ),	/* Flags:  in, base type, */
/* 650 */	NdrFcShort( 0x4 ),	/* x86 Stack size/offset = 4 */
/* 652 */	0xd,		/* FC_ENUM16 */
			0x0,		/* 0 */

	/* Parameter ppIVideoWindow */

/* 654 */	NdrFcShort( 0x13 ),	/* Flags:  must size, must free, out, */
/* 656 */	NdrFcShort( 0x8 ),	/* x86 Stack size/offset = 8 */
/* 658 */	NdrFcShort( 0x450 ),	/* Type Offset=1104 */

	/* Return value */

/* 660 */	NdrFcShort( 0x70 ),	/* Flags:  out, return, base type, */
/* 662 */	NdrFcShort( 0xc ),	/* x86 Stack size/offset = 12 */
/* 664 */	0x8,		/* FC_LONG */
			0x0,		/* 0 */

	/* Procedure put_PreferredAudioDevice */

/* 666 */	0x33,		/* FC_AUTO_HANDLE */
			0x6c,		/* Old Flags:  object, Oi2 */
/* 668 */	NdrFcLong( 0x0 ),	/* 0 */
/* 672 */	NdrFcShort( 0x14 ),	/* 20 */
/* 674 */	NdrFcShort( 0x10 ),	/* x86 Stack size/offset = 16 */
/* 676 */	NdrFcShort( 0x6 ),	/* 6 */
/* 678 */	NdrFcShort( 0x8 ),	/* 8 */
/* 680 */	0x46,		/* Oi2 Flags:  clt must size, has return, has ext, */
			0x3,		/* 3 */
/* 682 */	0x8,		/* 8 */
			0x5,		/* Ext Flags:  new corr desc, srv corr check, */
/* 684 */	NdrFcShort( 0x0 ),	/* 0 */
/* 686 */	NdrFcShort( 0x1 ),	/* 1 */
/* 688 */	NdrFcShort( 0x0 ),	/* 0 */

	/* Parameter enDevice */

/* 690 */	NdrFcShort( 0x48 ),	/* Flags:  in, base type, */
/* 692 */	NdrFcShort( 0x4 ),	/* x86 Stack size/offset = 4 */
/* 694 */	0xd,		/* FC_ENUM16 */
			0x0,		/* 0 */

	/* Parameter bstrDeviceName */

/* 696 */	NdrFcShort( 0x8b ),	/* Flags:  must size, must free, in, by val, */
/* 698 */	NdrFcShort( 0x8 ),	/* x86 Stack size/offset = 8 */
/* 700 */	NdrFcShort( 0x20 ),	/* Type Offset=32 */

	/* Return value */

/* 702 */	NdrFcShort( 0x70 ),	/* Flags:  out, return, base type, */
/* 704 */	NdrFcShort( 0xc ),	/* x86 Stack size/offset = 12 */
/* 706 */	0x8,		/* FC_LONG */
			0x0,		/* 0 */

	/* Procedure get_PreferredAudioDevice */

/* 708 */	0x33,		/* FC_AUTO_HANDLE */
			0x6c,		/* Old Flags:  object, Oi2 */
/* 710 */	NdrFcLong( 0x0 ),	/* 0 */
/* 714 */	NdrFcShort( 0x15 ),	/* 21 */
/* 716 */	NdrFcShort( 0x10 ),	/* x86 Stack size/offset = 16 */
/* 718 */	NdrFcShort( 0x6 ),	/* 6 */
/* 720 */	NdrFcShort( 0x8 ),	/* 8 */
/* 722 */	0x45,		/* Oi2 Flags:  srv must size, has return, has ext, */
			0x3,		/* 3 */
/* 724 */	0x8,		/* 8 */
			0x3,		/* Ext Flags:  new corr desc, clt corr check, */
/* 726 */	NdrFcShort( 0x1 ),	/* 1 */
/* 728 */	NdrFcShort( 0x0 ),	/* 0 */
/* 730 */	NdrFcShort( 0x0 ),	/* 0 */

	/* Parameter enDevice */

/* 732 */	NdrFcShort( 0x48 ),	/* Flags:  in, base type, */
/* 734 */	NdrFcShort( 0x4 ),	/* x86 Stack size/offset = 4 */
/* 736 */	0xd,		/* FC_ENUM16 */
			0x0,		/* 0 */

	/* Parameter pbstrDeviceName */

/* 738 */	NdrFcShort( 0x2113 ),	/* Flags:  must size, must free, out, simple ref, srv alloc size=8 */
/* 740 */	NdrFcShort( 0x8 ),	/* x86 Stack size/offset = 8 */
/* 742 */	NdrFcShort( 0x46a ),	/* Type Offset=1130 */

	/* Return value */

/* 744 */	NdrFcShort( 0x70 ),	/* Flags:  out, return, base type, */
/* 746 */	NdrFcShort( 0xc ),	/* x86 Stack size/offset = 12 */
/* 748 */	0x8,		/* FC_LONG */
			0x0,		/* 0 */

	/* Procedure put_PreferredVolume */

/* 750 */	0x33,		/* FC_AUTO_HANDLE */
			0x6c,		/* Old Flags:  object, Oi2 */
/* 752 */	NdrFcLong( 0x0 ),	/* 0 */
/* 756 */	NdrFcShort( 0x16 ),	/* 22 */
/* 758 */	NdrFcShort( 0x10 ),	/* x86 Stack size/offset = 16 */
/* 760 */	NdrFcShort( 0xe ),	/* 14 */
/* 762 */	NdrFcShort( 0x8 ),	/* 8 */
/* 764 */	0x44,		/* Oi2 Flags:  has return, has ext, */
			0x3,		/* 3 */
/* 766 */	0x8,		/* 8 */
			0x1,		/* Ext Flags:  new corr desc, */
/* 768 */	NdrFcShort( 0x0 ),	/* 0 */
/* 770 */	NdrFcShort( 0x0 ),	/* 0 */
/* 772 */	NdrFcShort( 0x0 ),	/* 0 */

	/* Parameter enDevice */

/* 774 */	NdrFcShort( 0x48 ),	/* Flags:  in, base type, */
/* 776 */	NdrFcShort( 0x4 ),	/* x86 Stack size/offset = 4 */
/* 778 */	0xd,		/* FC_ENUM16 */
			0x0,		/* 0 */

	/* Parameter lVolume */

/* 780 */	NdrFcShort( 0x48 ),	/* Flags:  in, base type, */
/* 782 */	NdrFcShort( 0x8 ),	/* x86 Stack size/offset = 8 */
/* 784 */	0x8,		/* FC_LONG */
			0x0,		/* 0 */

	/* Return value */

/* 786 */	NdrFcShort( 0x70 ),	/* Flags:  out, return, base type, */
/* 788 */	NdrFcShort( 0xc ),	/* x86 Stack size/offset = 12 */
/* 790 */	0x8,		/* FC_LONG */
			0x0,		/* 0 */

	/* Procedure get_PreferredVolume */

/* 792 */	0x33,		/* FC_AUTO_HANDLE */
			0x6c,		/* Old Flags:  object, Oi2 */
/* 794 */	NdrFcLong( 0x0 ),	/* 0 */
/* 798 */	NdrFcShort( 0x17 ),	/* 23 */
/* 800 */	NdrFcShort( 0x10 ),	/* x86 Stack size/offset = 16 */
/* 802 */	NdrFcShort( 0x6 ),	/* 6 */
/* 804 */	NdrFcShort( 0x24 ),	/* 36 */
/* 806 */	0x44,		/* Oi2 Flags:  has return, has ext, */
			0x3,		/* 3 */
/* 808 */	0x8,		/* 8 */
			0x1,		/* Ext Flags:  new corr desc, */
/* 810 */	NdrFcShort( 0x0 ),	/* 0 */
/* 812 */	NdrFcShort( 0x0 ),	/* 0 */
/* 814 */	NdrFcShort( 0x0 ),	/* 0 */

	/* Parameter enDevice */

/* 816 */	NdrFcShort( 0x48 ),	/* Flags:  in, base type, */
/* 818 */	NdrFcShort( 0x4 ),	/* x86 Stack size/offset = 4 */
/* 820 */	0xd,		/* FC_ENUM16 */
			0x0,		/* 0 */

	/* Parameter plVolume */

/* 822 */	NdrFcShort( 0x2150 ),	/* Flags:  out, base type, simple ref, srv alloc size=8 */
/* 824 */	NdrFcShort( 0x8 ),	/* x86 Stack size/offset = 8 */
/* 826 */	0x8,		/* FC_LONG */
			0x0,		/* 0 */

	/* Return value */

/* 828 */	NdrFcShort( 0x70 ),	/* Flags:  out, return, base type, */
/* 830 */	NdrFcShort( 0xc ),	/* x86 Stack size/offset = 12 */
/* 832 */	0x8,		/* FC_LONG */
			0x0,		/* 0 */

	/* Procedure put_PreferredAEC */

/* 834 */	0x33,		/* FC_AUTO_HANDLE */
			0x6c,		/* Old Flags:  object, Oi2 */
/* 836 */	NdrFcLong( 0x0 ),	/* 0 */
/* 840 */	NdrFcShort( 0x18 ),	/* 24 */
/* 842 */	NdrFcShort( 0xc ),	/* x86 Stack size/offset = 12 */
/* 844 */	NdrFcShort( 0x6 ),	/* 6 */
/* 846 */	NdrFcShort( 0x8 ),	/* 8 */
/* 848 */	0x44,		/* Oi2 Flags:  has return, has ext, */
			0x2,		/* 2 */
/* 850 */	0x8,		/* 8 */
			0x1,		/* Ext Flags:  new corr desc, */
/* 852 */	NdrFcShort( 0x0 ),	/* 0 */
/* 854 */	NdrFcShort( 0x0 ),	/* 0 */
/* 856 */	NdrFcShort( 0x0 ),	/* 0 */

	/* Parameter bEnable */

/* 858 */	NdrFcShort( 0x48 ),	/* Flags:  in, base type, */
/* 860 */	NdrFcShort( 0x4 ),	/* x86 Stack size/offset = 4 */
/* 862 */	0x6,		/* FC_SHORT */
			0x0,		/* 0 */

	/* Return value */

/* 864 */	NdrFcShort( 0x70 ),	/* Flags:  out, return, base type, */
/* 866 */	NdrFcShort( 0x8 ),	/* x86 Stack size/offset = 8 */
/* 868 */	0x8,		/* FC_LONG */
			0x0,		/* 0 */

	/* Procedure get_PreferredAEC */

/* 870 */	0x33,		/* FC_AUTO_HANDLE */
			0x6c,		/* Old Flags:  object, Oi2 */
/* 872 */	NdrFcLong( 0x0 ),	/* 0 */
/* 876 */	NdrFcShort( 0x19 ),	/* 25 */
/* 878 */	NdrFcShort( 0xc ),	/* x86 Stack size/offset = 12 */
/* 880 */	NdrFcShort( 0x0 ),	/* 0 */
/* 882 */	NdrFcShort( 0x22 ),	/* 34 */
/* 884 */	0x44,		/* Oi2 Flags:  has return, has ext, */
			0x2,		/* 2 */
/* 886 */	0x8,		/* 8 */
			0x1,		/* Ext Flags:  new corr desc, */
/* 888 */	NdrFcShort( 0x0 ),	/* 0 */
/* 890 */	NdrFcShort( 0x0 ),	/* 0 */
/* 892 */	NdrFcShort( 0x0 ),	/* 0 */

	/* Parameter pbEnabled */

/* 894 */	NdrFcShort( 0x2150 ),	/* Flags:  out, base type, simple ref, srv alloc size=8 */
/* 896 */	NdrFcShort( 0x4 ),	/* x86 Stack size/offset = 4 */
/* 898 */	0x6,		/* FC_SHORT */
			0x0,		/* 0 */

	/* Return value */

/* 900 */	NdrFcShort( 0x70 ),	/* Flags:  out, return, base type, */
/* 902 */	NdrFcShort( 0x8 ),	/* x86 Stack size/offset = 8 */
/* 904 */	0x8,		/* FC_LONG */
			0x0,		/* 0 */

	/* Procedure put_PreferredVideoDevice */

/* 906 */	0x33,		/* FC_AUTO_HANDLE */
			0x6c,		/* Old Flags:  object, Oi2 */
/* 908 */	NdrFcLong( 0x0 ),	/* 0 */
/* 912 */	NdrFcShort( 0x1a ),	/* 26 */
/* 914 */	NdrFcShort( 0xc ),	/* x86 Stack size/offset = 12 */
/* 916 */	NdrFcShort( 0x0 ),	/* 0 */
/* 918 */	NdrFcShort( 0x8 ),	/* 8 */
/* 920 */	0x46,		/* Oi2 Flags:  clt must size, has return, has ext, */
			0x2,		/* 2 */
/* 922 */	0x8,		/* 8 */
			0x5,		/* Ext Flags:  new corr desc, srv corr check, */
/* 924 */	NdrFcShort( 0x0 ),	/* 0 */
/* 926 */	NdrFcShort( 0x1 ),	/* 1 */
/* 928 */	NdrFcShort( 0x0 ),	/* 0 */

	/* Parameter bstrDeviceName */

/* 930 */	NdrFcShort( 0x8b ),	/* Flags:  must size, must free, in, by val, */
/* 932 */	NdrFcShort( 0x4 ),	/* x86 Stack size/offset = 4 */
/* 934 */	NdrFcShort( 0x20 ),	/* Type Offset=32 */

	/* Return value */

/* 936 */	NdrFcShort( 0x70 ),	/* Flags:  out, return, base type, */
/* 938 */	NdrFcShort( 0x8 ),	/* x86 Stack size/offset = 8 */
/* 940 */	0x8,		/* FC_LONG */
			0x0,		/* 0 */

	/* Procedure get_PreferredVideoDevice */

/* 942 */	0x33,		/* FC_AUTO_HANDLE */
			0x6c,		/* Old Flags:  object, Oi2 */
/* 944 */	NdrFcLong( 0x0 ),	/* 0 */
/* 948 */	NdrFcShort( 0x1b ),	/* 27 */
/* 950 */	NdrFcShort( 0xc ),	/* x86 Stack size/offset = 12 */
/* 952 */	NdrFcShort( 0x0 ),	/* 0 */
/* 954 */	NdrFcShort( 0x8 ),	/* 8 */
/* 956 */	0x45,		/* Oi2 Flags:  srv must size, has return, has ext, */
			0x2,		/* 2 */
/* 958 */	0x8,		/* 8 */
			0x3,		/* Ext Flags:  new corr desc, clt corr check, */
/* 960 */	NdrFcShort( 0x1 ),	/* 1 */
/* 962 */	NdrFcShort( 0x0 ),	/* 0 */
/* 964 */	NdrFcShort( 0x0 ),	/* 0 */

	/* Parameter pbstrDeviceName */

/* 966 */	NdrFcShort( 0x2113 ),	/* Flags:  must size, must free, out, simple ref, srv alloc size=8 */
/* 968 */	NdrFcShort( 0x4 ),	/* x86 Stack size/offset = 4 */
/* 970 */	NdrFcShort( 0x46a ),	/* Type Offset=1130 */

	/* Return value */

/* 972 */	NdrFcShort( 0x70 ),	/* Flags:  out, return, base type, */
/* 974 */	NdrFcShort( 0x8 ),	/* x86 Stack size/offset = 8 */
/* 976 */	0x8,		/* FC_LONG */
			0x0,		/* 0 */

	/* Procedure get_ActiveMedia */

/* 978 */	0x33,		/* FC_AUTO_HANDLE */
			0x6c,		/* Old Flags:  object, Oi2 */
/* 980 */	NdrFcLong( 0x0 ),	/* 0 */
/* 984 */	NdrFcShort( 0x1c ),	/* 28 */
/* 986 */	NdrFcShort( 0xc ),	/* x86 Stack size/offset = 12 */
/* 988 */	NdrFcShort( 0x0 ),	/* 0 */
/* 990 */	NdrFcShort( 0x24 ),	/* 36 */
/* 992 */	0x44,		/* Oi2 Flags:  has return, has ext, */
			0x2,		/* 2 */
/* 994 */	0x8,		/* 8 */
			0x1,		/* Ext Flags:  new corr desc, */
/* 996 */	NdrFcShort( 0x0 ),	/* 0 */
/* 998 */	NdrFcShort( 0x0 ),	/* 0 */
/* 1000 */	NdrFcShort( 0x0 ),	/* 0 */

	/* Parameter plMediaType */

/* 1002 */	NdrFcShort( 0x2150 ),	/* Flags:  out, base type, simple ref, srv alloc size=8 */
/* 1004 */	NdrFcShort( 0x4 ),	/* x86 Stack size/offset = 4 */
/* 1006 */	0x8,		/* FC_LONG */
			0x0,		/* 0 */

	/* Return value */

/* 1008 */	NdrFcShort( 0x70 ),	/* Flags:  out, return, base type, */
/* 1010 */	NdrFcShort( 0x8 ),	/* x86 Stack size/offset = 8 */
/* 1012 */	0x8,		/* FC_LONG */
			0x0,		/* 0 */

	/* Procedure put_MaxBitrate */

/* 1014 */	0x33,		/* FC_AUTO_HANDLE */
			0x6c,		/* Old Flags:  object, Oi2 */
/* 1016 */	NdrFcLong( 0x0 ),	/* 0 */
/* 1020 */	NdrFcShort( 0x1d ),	/* 29 */
/* 1022 */	NdrFcShort( 0xc ),	/* x86 Stack size/offset = 12 */
/* 1024 */	NdrFcShort( 0x8 ),	/* 8 */
/* 1026 */	NdrFcShort( 0x8 ),	/* 8 */
/* 1028 */	0x44,		/* Oi2 Flags:  has return, has ext, */
			0x2,		/* 2 */
/* 1030 */	0x8,		/* 8 */
			0x1,		/* Ext Flags:  new corr desc, */
/* 1032 */	NdrFcShort( 0x0 ),	/* 0 */
/* 1034 */	NdrFcShort( 0x0 ),	/* 0 */
/* 1036 */	NdrFcShort( 0x0 ),	/* 0 */

	/* Parameter lMaxBitrate */

/* 1038 */	NdrFcShort( 0x48 ),	/* Flags:  in, base type, */
/* 1040 */	NdrFcShort( 0x4 ),	/* x86 Stack size/offset = 4 */
/* 1042 */	0x8,		/* FC_LONG */
			0x0,		/* 0 */

	/* Return value */

/* 1044 */	NdrFcShort( 0x70 ),	/* Flags:  out, return, base type, */
/* 1046 */	NdrFcShort( 0x8 ),	/* x86 Stack size/offset = 8 */
/* 1048 */	0x8,		/* FC_LONG */
			0x0,		/* 0 */

	/* Procedure get_MaxBitrate */

/* 1050 */	0x33,		/* FC_AUTO_HANDLE */
			0x6c,		/* Old Flags:  object, Oi2 */
/* 1052 */	NdrFcLong( 0x0 ),	/* 0 */
/* 1056 */	NdrFcShort( 0x1e ),	/* 30 */
/* 1058 */	NdrFcShort( 0xc ),	/* x86 Stack size/offset = 12 */
/* 1060 */	NdrFcShort( 0x0 ),	/* 0 */
/* 1062 */	NdrFcShort( 0x24 ),	/* 36 */
/* 1064 */	0x44,		/* Oi2 Flags:  has return, has ext, */
			0x2,		/* 2 */
/* 1066 */	0x8,		/* 8 */
			0x1,		/* Ext Flags:  new corr desc, */
/* 1068 */	NdrFcShort( 0x0 ),	/* 0 */
/* 1070 */	NdrFcShort( 0x0 ),	/* 0 */
/* 1072 */	NdrFcShort( 0x0 ),	/* 0 */

	/* Parameter plMaxBitrate */

/* 1074 */	NdrFcShort( 0x2150 ),	/* Flags:  out, base type, simple ref, srv alloc size=8 */
/* 1076 */	NdrFcShort( 0x4 ),	/* x86 Stack size/offset = 4 */
/* 1078 */	0x8,		/* FC_LONG */
			0x0,		/* 0 */

	/* Return value */

/* 1080 */	NdrFcShort( 0x70 ),	/* Flags:  out, return, base type, */
/* 1082 */	NdrFcShort( 0x8 ),	/* x86 Stack size/offset = 8 */
/* 1084 */	0x8,		/* FC_LONG */
			0x0,		/* 0 */

	/* Procedure put_TemporalSpatialTradeOff */

/* 1086 */	0x33,		/* FC_AUTO_HANDLE */
			0x6c,		/* Old Flags:  object, Oi2 */
/* 1088 */	NdrFcLong( 0x0 ),	/* 0 */
/* 1092 */	NdrFcShort( 0x1f ),	/* 31 */
/* 1094 */	NdrFcShort( 0xc ),	/* x86 Stack size/offset = 12 */
/* 1096 */	NdrFcShort( 0x8 ),	/* 8 */
/* 1098 */	NdrFcShort( 0x8 ),	/* 8 */
/* 1100 */	0x44,		/* Oi2 Flags:  has return, has ext, */
			0x2,		/* 2 */
/* 1102 */	0x8,		/* 8 */
			0x1,		/* Ext Flags:  new corr desc, */
/* 1104 */	NdrFcShort( 0x0 ),	/* 0 */
/* 1106 */	NdrFcShort( 0x0 ),	/* 0 */
/* 1108 */	NdrFcShort( 0x0 ),	/* 0 */

	/* Parameter lValue */

/* 1110 */	NdrFcShort( 0x48 ),	/* Flags:  in, base type, */
/* 1112 */	NdrFcShort( 0x4 ),	/* x86 Stack size/offset = 4 */
/* 1114 */	0x8,		/* FC_LONG */
			0x0,		/* 0 */

	/* Return value */

/* 1116 */	NdrFcShort( 0x70 ),	/* Flags:  out, return, base type, */
/* 1118 */	NdrFcShort( 0x8 ),	/* x86 Stack size/offset = 8 */
/* 1120 */	0x8,		/* FC_LONG */
			0x0,		/* 0 */

	/* Procedure get_TemporalSpatialTradeOff */

/* 1122 */	0x33,		/* FC_AUTO_HANDLE */
			0x6c,		/* Old Flags:  object, Oi2 */
/* 1124 */	NdrFcLong( 0x0 ),	/* 0 */
/* 1128 */	NdrFcShort( 0x20 ),	/* 32 */
/* 1130 */	NdrFcShort( 0xc ),	/* x86 Stack size/offset = 12 */
/* 1132 */	NdrFcShort( 0x0 ),	/* 0 */
/* 1134 */	NdrFcShort( 0x24 ),	/* 36 */
/* 1136 */	0x44,		/* Oi2 Flags:  has return, has ext, */
			0x2,		/* 2 */
/* 1138 */	0x8,		/* 8 */
			0x1,		/* Ext Flags:  new corr desc, */
/* 1140 */	NdrFcShort( 0x0 ),	/* 0 */
/* 1142 */	NdrFcShort( 0x0 ),	/* 0 */
/* 1144 */	NdrFcShort( 0x0 ),	/* 0 */

	/* Parameter plValue */

/* 1146 */	NdrFcShort( 0x2150 ),	/* Flags:  out, base type, simple ref, srv alloc size=8 */
/* 1148 */	NdrFcShort( 0x4 ),	/* x86 Stack size/offset = 4 */
/* 1150 */	0x8,		/* FC_LONG */
			0x0,		/* 0 */

	/* Return value */

/* 1152 */	NdrFcShort( 0x70 ),	/* Flags:  out, return, base type, */
/* 1154 */	NdrFcShort( 0x8 ),	/* x86 Stack size/offset = 8 */
/* 1156 */	0x8,		/* FC_LONG */
			0x0,		/* 0 */

	/* Procedure get_NetworkQuality */

/* 1158 */	0x33,		/* FC_AUTO_HANDLE */
			0x6c,		/* Old Flags:  object, Oi2 */
/* 1160 */	NdrFcLong( 0x0 ),	/* 0 */
/* 1164 */	NdrFcShort( 0x21 ),	/* 33 */
/* 1166 */	NdrFcShort( 0xc ),	/* x86 Stack size/offset = 12 */
/* 1168 */	NdrFcShort( 0x0 ),	/* 0 */
/* 1170 */	NdrFcShort( 0x24 ),	/* 36 */
/* 1172 */	0x44,		/* Oi2 Flags:  has return, has ext, */
			0x2,		/* 2 */
/* 1174 */	0x8,		/* 8 */
			0x1,		/* Ext Flags:  new corr desc, */
/* 1176 */	NdrFcShort( 0x0 ),	/* 0 */
/* 1178 */	NdrFcShort( 0x0 ),	/* 0 */
/* 1180 */	NdrFcShort( 0x0 ),	/* 0 */

	/* Parameter plNetworkQuality */

/* 1182 */	NdrFcShort( 0x2150 ),	/* Flags:  out, base type, simple ref, srv alloc size=8 */
/* 1184 */	NdrFcShort( 0x4 ),	/* x86 Stack size/offset = 4 */
/* 1186 */	0x8,		/* FC_LONG */
			0x0,		/* 0 */

	/* Return value */

/* 1188 */	NdrFcShort( 0x70 ),	/* Flags:  out, return, base type, */
/* 1190 */	NdrFcShort( 0x8 ),	/* x86 Stack size/offset = 8 */
/* 1192 */	0x8,		/* FC_LONG */
			0x0,		/* 0 */

	/* Procedure StartT120Applet */

/* 1194 */	0x33,		/* FC_AUTO_HANDLE */
			0x6c,		/* Old Flags:  object, Oi2 */
/* 1196 */	NdrFcLong( 0x0 ),	/* 0 */
/* 1200 */	NdrFcShort( 0x22 ),	/* 34 */
/* 1202 */	NdrFcShort( 0xc ),	/* x86 Stack size/offset = 12 */
/* 1204 */	NdrFcShort( 0x6 ),	/* 6 */
/* 1206 */	NdrFcShort( 0x8 ),	/* 8 */
/* 1208 */	0x44,		/* Oi2 Flags:  has return, has ext, */
			0x2,		/* 2 */
/* 1210 */	0x8,		/* 8 */
			0x1,		/* Ext Flags:  new corr desc, */
/* 1212 */	NdrFcShort( 0x0 ),	/* 0 */
/* 1214 */	NdrFcShort( 0x0 ),	/* 0 */
/* 1216 */	NdrFcShort( 0x0 ),	/* 0 */

	/* Parameter enApplet */

/* 1218 */	NdrFcShort( 0x48 ),	/* Flags:  in, base type, */
/* 1220 */	NdrFcShort( 0x4 ),	/* x86 Stack size/offset = 4 */
/* 1222 */	0xd,		/* FC_ENUM16 */
			0x0,		/* 0 */

	/* Return value */

/* 1224 */	NdrFcShort( 0x70 ),	/* Flags:  out, return, base type, */
/* 1226 */	NdrFcShort( 0x8 ),	/* x86 Stack size/offset = 8 */
/* 1228 */	0x8,		/* FC_LONG */
			0x0,		/* 0 */

	/* Procedure StopT120Applets */

/* 1230 */	0x33,		/* FC_AUTO_HANDLE */
			0x6c,		/* Old Flags:  object, Oi2 */
/* 1232 */	NdrFcLong( 0x0 ),	/* 0 */
/* 1236 */	NdrFcShort( 0x23 ),	/* 35 */
/* 1238 */	NdrFcShort( 0x8 ),	/* x86 Stack size/offset = 8 */
/* 1240 */	NdrFcShort( 0x0 ),	/* 0 */
/* 1242 */	NdrFcShort( 0x8 ),	/* 8 */
/* 1244 */	0x44,		/* Oi2 Flags:  has return, has ext, */
			0x1,		/* 1 */
/* 1246 */	0x8,		/* 8 */
			0x1,		/* Ext Flags:  new corr desc, */
/* 1248 */	NdrFcShort( 0x0 ),	/* 0 */
/* 1250 */	NdrFcShort( 0x0 ),	/* 0 */
/* 1252 */	NdrFcShort( 0x0 ),	/* 0 */

	/* Return value */

/* 1254 */	NdrFcShort( 0x70 ),	/* Flags:  out, return, base type, */
/* 1256 */	NdrFcShort( 0x4 ),	/* x86 Stack size/offset = 4 */
/* 1258 */	0x8,		/* FC_LONG */
			0x0,		/* 0 */

	/* Procedure get_IsT120AppletRunning */

/* 1260 */	0x33,		/* FC_AUTO_HANDLE */
			0x6c,		/* Old Flags:  object, Oi2 */
/* 1262 */	NdrFcLong( 0x0 ),	/* 0 */
/* 1266 */	NdrFcShort( 0x24 ),	/* 36 */
/* 1268 */	NdrFcShort( 0x10 ),	/* x86 Stack size/offset = 16 */
/* 1270 */	NdrFcShort( 0x6 ),	/* 6 */
/* 1272 */	NdrFcShort( 0x22 ),	/* 34 */
/* 1274 */	0x44,		/* Oi2 Flags:  has return, has ext, */
			0x3,		/* 3 */
/* 1276 */	0x8,		/* 8 */
			0x1,		/* Ext Flags:  new corr desc, */
/* 1278 */	NdrFcShort( 0x0 ),	/* 0 */
/* 1280 */	NdrFcShort( 0x0 ),	/* 0 */
/* 1282 */	NdrFcShort( 0x0 ),	/* 0 */

	/* Parameter enApplet */

/* 1284 */	NdrFcShort( 0x48 ),	/* Flags:  in, base type, */
/* 1286 */	NdrFcShort( 0x4 ),	/* x86 Stack size/offset = 4 */
/* 1288 */	0xd,		/* FC_ENUM16 */
			0x0,		/* 0 */

	/* Parameter pfRunning */

/* 1290 */	NdrFcShort( 0x2150 ),	/* Flags:  out, base type, simple ref, srv alloc size=8 */
/* 1292 */	NdrFcShort( 0x8 ),	/* x86 Stack size/offset = 8 */
/* 1294 */	0x6,		/* FC_SHORT */
			0x0,		/* 0 */

	/* Return value */

/* 1296 */	NdrFcShort( 0x70 ),	/* Flags:  out, return, base type, */
/* 1298 */	NdrFcShort( 0xc ),	/* x86 Stack size/offset = 12 */
/* 1300 */	0x8,		/* FC_LONG */
			0x0,		/* 0 */

	/* Procedure get_LocalUserURI */

/* 1302 */	0x33,		/* FC_AUTO_HANDLE */
			0x6c,		/* Old Flags:  object, Oi2 */
/* 1304 */	NdrFcLong( 0x0 ),	/* 0 */
/* 1308 */	NdrFcShort( 0x25 ),	/* 37 */
/* 1310 */	NdrFcShort( 0xc ),	/* x86 Stack size/offset = 12 */
/* 1312 */	NdrFcShort( 0x0 ),	/* 0 */
/* 1314 */	NdrFcShort( 0x8 ),	/* 8 */
/* 1316 */	0x45,		/* Oi2 Flags:  srv must size, has return, has ext, */
			0x2,		/* 2 */
/* 1318 */	0x8,		/* 8 */
			0x3,		/* Ext Flags:  new corr desc, clt corr check, */
/* 1320 */	NdrFcShort( 0x1 ),	/* 1 */
/* 1322 */	NdrFcShort( 0x0 ),	/* 0 */
/* 1324 */	NdrFcShort( 0x0 ),	/* 0 */

	/* Parameter pbstrUserURI */

/* 1326 */	NdrFcShort( 0x2113 ),	/* Flags:  must size, must free, out, simple ref, srv alloc size=8 */
/* 1328 */	NdrFcShort( 0x4 ),	/* x86 Stack size/offset = 4 */
/* 1330 */	NdrFcShort( 0x46a ),	/* Type Offset=1130 */

	/* Return value */

/* 1332 */	NdrFcShort( 0x70 ),	/* Flags:  out, return, base type, */
/* 1334 */	NdrFcShort( 0x8 ),	/* x86 Stack size/offset = 8 */
/* 1336 */	0x8,		/* FC_LONG */
			0x0,		/* 0 */

	/* Procedure put_LocalUserURI */

/* 1338 */	0x33,		/* FC_AUTO_HANDLE */
			0x6c,		/* Old Flags:  object, Oi2 */
/* 1340 */	NdrFcLong( 0x0 ),	/* 0 */
/* 1344 */	NdrFcShort( 0x26 ),	/* 38 */
/* 1346 */	NdrFcShort( 0xc ),	/* x86 Stack size/offset = 12 */
/* 1348 */	NdrFcShort( 0x0 ),	/* 0 */
/* 1350 */	NdrFcShort( 0x8 ),	/* 8 */
/* 1352 */	0x46,		/* Oi2 Flags:  clt must size, has return, has ext, */
			0x2,		/* 2 */
/* 1354 */	0x8,		/* 8 */
			0x5,		/* Ext Flags:  new corr desc, srv corr check, */
/* 1356 */	NdrFcShort( 0x0 ),	/* 0 */
/* 1358 */	NdrFcShort( 0x1 ),	/* 1 */
/* 1360 */	NdrFcShort( 0x0 ),	/* 0 */

	/* Parameter bstrUserURI */

/* 1362 */	NdrFcShort( 0x8b ),	/* Flags:  must size, must free, in, by val, */
/* 1364 */	NdrFcShort( 0x4 ),	/* x86 Stack size/offset = 4 */
/* 1366 */	NdrFcShort( 0x20 ),	/* Type Offset=32 */

	/* Return value */

/* 1368 */	NdrFcShort( 0x70 ),	/* Flags:  out, return, base type, */
/* 1370 */	NdrFcShort( 0x8 ),	/* x86 Stack size/offset = 8 */
/* 1372 */	0x8,		/* FC_LONG */
			0x0,		/* 0 */

	/* Procedure get_LocalUserName */

/* 1374 */	0x33,		/* FC_AUTO_HANDLE */
			0x6c,		/* Old Flags:  object, Oi2 */
/* 1376 */	NdrFcLong( 0x0 ),	/* 0 */
/* 1380 */	NdrFcShort( 0x27 ),	/* 39 */
/* 1382 */	NdrFcShort( 0xc ),	/* x86 Stack size/offset = 12 */
/* 1384 */	NdrFcShort( 0x0 ),	/* 0 */
/* 1386 */	NdrFcShort( 0x8 ),	/* 8 */
/* 1388 */	0x45,		/* Oi2 Flags:  srv must size, has return, has ext, */
			0x2,		/* 2 */
/* 1390 */	0x8,		/* 8 */
			0x3,		/* Ext Flags:  new corr desc, clt corr check, */
/* 1392 */	NdrFcShort( 0x1 ),	/* 1 */
/* 1394 */	NdrFcShort( 0x0 ),	/* 0 */
/* 1396 */	NdrFcShort( 0x0 ),	/* 0 */

	/* Parameter pbstrUserName */

/* 1398 */	NdrFcShort( 0x2113 ),	/* Flags:  must size, must free, out, simple ref, srv alloc size=8 */
/* 1400 */	NdrFcShort( 0x4 ),	/* x86 Stack size/offset = 4 */
/* 1402 */	NdrFcShort( 0x46a ),	/* Type Offset=1130 */

	/* Return value */

/* 1404 */	NdrFcShort( 0x70 ),	/* Flags:  out, return, base type, */
/* 1406 */	NdrFcShort( 0x8 ),	/* x86 Stack size/offset = 8 */
/* 1408 */	0x8,		/* FC_LONG */
			0x0,		/* 0 */

	/* Procedure put_LocalUserName */

/* 1410 */	0x33,		/* FC_AUTO_HANDLE */
			0x6c,		/* Old Flags:  object, Oi2 */
/* 1412 */	NdrFcLong( 0x0 ),	/* 0 */
/* 1416 */	NdrFcShort( 0x28 ),	/* 40 */
/* 1418 */	NdrFcShort( 0xc ),	/* x86 Stack size/offset = 12 */
/* 1420 */	NdrFcShort( 0x0 ),	/* 0 */
/* 1422 */	NdrFcShort( 0x8 ),	/* 8 */
/* 1424 */	0x46,		/* Oi2 Flags:  clt must size, has return, has ext, */
			0x2,		/* 2 */
/* 1426 */	0x8,		/* 8 */
			0x5,		/* Ext Flags:  new corr desc, srv corr check, */
/* 1428 */	NdrFcShort( 0x0 ),	/* 0 */
/* 1430 */	NdrFcShort( 0x1 ),	/* 1 */
/* 1432 */	NdrFcShort( 0x0 ),	/* 0 */

	/* Parameter bstrUserName */

/* 1434 */	NdrFcShort( 0x8b ),	/* Flags:  must size, must free, in, by val, */
/* 1436 */	NdrFcShort( 0x4 ),	/* x86 Stack size/offset = 4 */
/* 1438 */	NdrFcShort( 0x20 ),	/* Type Offset=32 */

	/* Return value */

/* 1440 */	NdrFcShort( 0x70 ),	/* Flags:  out, return, base type, */
/* 1442 */	NdrFcShort( 0x8 ),	/* x86 Stack size/offset = 8 */
/* 1444 */	0x8,		/* FC_LONG */
			0x0,		/* 0 */

	/* Procedure PlayRing */

/* 1446 */	0x33,		/* FC_AUTO_HANDLE */
			0x6c,		/* Old Flags:  object, Oi2 */
/* 1448 */	NdrFcLong( 0x0 ),	/* 0 */
/* 1452 */	NdrFcShort( 0x29 ),	/* 41 */
/* 1454 */	NdrFcShort( 0x10 ),	/* x86 Stack size/offset = 16 */
/* 1456 */	NdrFcShort( 0xc ),	/* 12 */
/* 1458 */	NdrFcShort( 0x8 ),	/* 8 */
/* 1460 */	0x44,		/* Oi2 Flags:  has return, has ext, */
			0x3,		/* 3 */
/* 1462 */	0x8,		/* 8 */
			0x1,		/* Ext Flags:  new corr desc, */
/* 1464 */	NdrFcShort( 0x0 ),	/* 0 */
/* 1466 */	NdrFcShort( 0x0 ),	/* 0 */
/* 1468 */	NdrFcShort( 0x0 ),	/* 0 */

	/* Parameter enType */

/* 1470 */	NdrFcShort( 0x48 ),	/* Flags:  in, base type, */
/* 1472 */	NdrFcShort( 0x4 ),	/* x86 Stack size/offset = 4 */
/* 1474 */	0xd,		/* FC_ENUM16 */
			0x0,		/* 0 */

	/* Parameter bPlay */

/* 1476 */	NdrFcShort( 0x48 ),	/* Flags:  in, base type, */
/* 1478 */	NdrFcShort( 0x8 ),	/* x86 Stack size/offset = 8 */
/* 1480 */	0x6,		/* FC_SHORT */
			0x0,		/* 0 */

	/* Return value */

/* 1482 */	NdrFcShort( 0x70 ),	/* Flags:  out, return, base type, */
/* 1484 */	NdrFcShort( 0xc ),	/* x86 Stack size/offset = 12 */
/* 1486 */	0x8,		/* FC_LONG */
			0x0,		/* 0 */

	/* Procedure SendDTMF */

/* 1488 */	0x33,		/* FC_AUTO_HANDLE */
			0x6c,		/* Old Flags:  object, Oi2 */
/* 1490 */	NdrFcLong( 0x0 ),	/* 0 */
/* 1494 */	NdrFcShort( 0x2a ),	/* 42 */
/* 1496 */	NdrFcShort( 0xc ),	/* x86 Stack size/offset = 12 */
/* 1498 */	NdrFcShort( 0x6 ),	/* 6 */
/* 1500 */	NdrFcShort( 0x8 ),	/* 8 */
/* 1502 */	0x44,		/* Oi2 Flags:  has return, has ext, */
			0x2,		/* 2 */
/* 1504 */	0x8,		/* 8 */
			0x1,		/* Ext Flags:  new corr desc, */
/* 1506 */	NdrFcShort( 0x0 ),	/* 0 */
/* 1508 */	NdrFcShort( 0x0 ),	/* 0 */
/* 1510 */	NdrFcShort( 0x0 ),	/* 0 */

	/* Parameter enDTMF */

/* 1512 */	NdrFcShort( 0x48 ),	/* Flags:  in, base type, */
/* 1514 */	NdrFcShort( 0x4 ),	/* x86 Stack size/offset = 4 */
/* 1516 */	0xd,		/* FC_ENUM16 */
			0x0,		/* 0 */

	/* Return value */

/* 1518 */	NdrFcShort( 0x70 ),	/* Flags:  out, return, base type, */
/* 1520 */	NdrFcShort( 0x8 ),	/* x86 Stack size/offset = 8 */
/* 1522 */	0x8,		/* FC_LONG */
			0x0,		/* 0 */

	/* Procedure InvokeTuningWizard */

/* 1524 */	0x33,		/* FC_AUTO_HANDLE */
			0x6c,		/* Old Flags:  object, Oi2 */
/* 1526 */	NdrFcLong( 0x0 ),	/* 0 */
/* 1530 */	NdrFcShort( 0x2b ),	/* 43 */
/* 1532 */	NdrFcShort( 0xc ),	/* x86 Stack size/offset = 12 */
/* 1534 */	NdrFcShort( 0x8 ),	/* 8 */
/* 1536 */	NdrFcShort( 0x8 ),	/* 8 */
/* 1538 */	0x44,		/* Oi2 Flags:  has return, has ext, */
			0x2,		/* 2 */
/* 1540 */	0x8,		/* 8 */
			0x1,		/* Ext Flags:  new corr desc, */
/* 1542 */	NdrFcShort( 0x0 ),	/* 0 */
/* 1544 */	NdrFcShort( 0x0 ),	/* 0 */
/* 1546 */	NdrFcShort( 0x0 ),	/* 0 */

	/* Parameter hwndParent */

/* 1548 */	NdrFcShort( 0x48 ),	/* Flags:  in, base type, */
/* 1550 */	NdrFcShort( 0x4 ),	/* x86 Stack size/offset = 4 */
/* 1552 */	0x8,		/* FC_LONG */
			0x0,		/* 0 */

	/* Return value */

/* 1554 */	NdrFcShort( 0x70 ),	/* Flags:  out, return, base type, */
/* 1556 */	NdrFcShort( 0x8 ),	/* x86 Stack size/offset = 8 */
/* 1558 */	0x8,		/* FC_LONG */
			0x0,		/* 0 */

	/* Procedure get_IsTuned */

/* 1560 */	0x33,		/* FC_AUTO_HANDLE */
			0x6c,		/* Old Flags:  object, Oi2 */
/* 1562 */	NdrFcLong( 0x0 ),	/* 0 */
/* 1566 */	NdrFcShort( 0x2c ),	/* 44 */
/* 1568 */	NdrFcShort( 0xc ),	/* x86 Stack size/offset = 12 */
/* 1570 */	NdrFcShort( 0x0 ),	/* 0 */
/* 1572 */	NdrFcShort( 0x22 ),	/* 34 */
/* 1574 */	0x44,		/* Oi2 Flags:  has return, has ext, */
			0x2,		/* 2 */
/* 1576 */	0x8,		/* 8 */
			0x1,		/* Ext Flags:  new corr desc, */
/* 1578 */	NdrFcShort( 0x0 ),	/* 0 */
/* 1580 */	NdrFcShort( 0x0 ),	/* 0 */
/* 1582 */	NdrFcShort( 0x0 ),	/* 0 */

	/* Parameter pfTuned */

/* 1584 */	NdrFcShort( 0x2150 ),	/* Flags:  out, base type, simple ref, srv alloc size=8 */
/* 1586 */	NdrFcShort( 0x4 ),	/* x86 Stack size/offset = 4 */
/* 1588 */	0x6,		/* FC_SHORT */
			0x0,		/* 0 */

	/* Return value */

/* 1590 */	NdrFcShort( 0x70 ),	/* Flags:  out, return, base type, */
/* 1592 */	NdrFcShort( 0x8 ),	/* x86 Stack size/offset = 8 */
/* 1594 */	0x8,		/* FC_LONG */
			0x0,		/* 0 */

	/* Procedure put_AnswerMode */

/* 1596 */	0x33,		/* FC_AUTO_HANDLE */
			0x6c,		/* Old Flags:  object, Oi2 */
/* 1598 */	NdrFcLong( 0x0 ),	/* 0 */
/* 1602 */	NdrFcShort( 0x2d ),	/* 45 */
/* 1604 */	NdrFcShort( 0x10 ),	/* x86 Stack size/offset = 16 */
/* 1606 */	NdrFcShort( 0xc ),	/* 12 */
/* 1608 */	NdrFcShort( 0x8 ),	/* 8 */
/* 1610 */	0x44,		/* Oi2 Flags:  has return, has ext, */
			0x3,		/* 3 */
/* 1612 */	0x8,		/* 8 */
			0x1,		/* Ext Flags:  new corr desc, */
/* 1614 */	NdrFcShort( 0x0 ),	/* 0 */
/* 1616 */	NdrFcShort( 0x0 ),	/* 0 */
/* 1618 */	NdrFcShort( 0x0 ),	/* 0 */

	/* Parameter enType */

/* 1620 */	NdrFcShort( 0x48 ),	/* Flags:  in, base type, */
/* 1622 */	NdrFcShort( 0x4 ),	/* x86 Stack size/offset = 4 */
/* 1624 */	0xd,		/* FC_ENUM16 */
			0x0,		/* 0 */

	/* Parameter enMode */

/* 1626 */	NdrFcShort( 0x48 ),	/* Flags:  in, base type, */
/* 1628 */	NdrFcShort( 0x8 ),	/* x86 Stack size/offset = 8 */
/* 1630 */	0xd,		/* FC_ENUM16 */
			0x0,		/* 0 */

	/* Return value */

/* 1632 */	NdrFcShort( 0x70 ),	/* Flags:  out, return, base type, */
/* 1634 */	NdrFcShort( 0xc ),	/* x86 Stack size/offset = 12 */
/* 1636 */	0x8,		/* FC_LONG */
			0x0,		/* 0 */

	/* Procedure get_AnswerMode */

/* 1638 */	0x33,		/* FC_AUTO_HANDLE */
			0x6c,		/* Old Flags:  object, Oi2 */
/* 1640 */	NdrFcLong( 0x0 ),	/* 0 */
/* 1644 */	NdrFcShort( 0x2e ),	/* 46 */
/* 1646 */	NdrFcShort( 0x10 ),	/* x86 Stack size/offset = 16 */
/* 1648 */	NdrFcShort( 0x6 ),	/* 6 */
/* 1650 */	NdrFcShort( 0x22 ),	/* 34 */
/* 1652 */	0x44,		/* Oi2 Flags:  has return, has ext, */
			0x3,		/* 3 */
/* 1654 */	0x8,		/* 8 */
			0x1,		/* Ext Flags:  new corr desc, */
/* 1656 */	NdrFcShort( 0x0 ),	/* 0 */
/* 1658 */	NdrFcShort( 0x0 ),	/* 0 */
/* 1660 */	NdrFcShort( 0x0 ),	/* 0 */

	/* Parameter enType */

/* 1662 */	NdrFcShort( 0x48 ),	/* Flags:  in, base type, */
/* 1664 */	NdrFcShort( 0x4 ),	/* x86 Stack size/offset = 4 */
/* 1666 */	0xd,		/* FC_ENUM16 */
			0x0,		/* 0 */

	/* Parameter penMode */

/* 1668 */	NdrFcShort( 0x2010 ),	/* Flags:  out, srv alloc size=8 */
/* 1670 */	NdrFcShort( 0x8 ),	/* x86 Stack size/offset = 8 */
/* 1672 */	NdrFcShort( 0x52 ),	/* Type Offset=82 */

	/* Return value */

/* 1674 */	NdrFcShort( 0x70 ),	/* Flags:  out, return, base type, */
/* 1676 */	NdrFcShort( 0xc ),	/* x86 Stack size/offset = 12 */
/* 1678 */	0x8,		/* FC_LONG */
			0x0,		/* 0 */

	/* Procedure InvokeTuningWizardEx */

/* 1680 */	0x33,		/* FC_AUTO_HANDLE */
			0x6c,		/* Old Flags:  object, Oi2 */
/* 1682 */	NdrFcLong( 0x0 ),	/* 0 */
/* 1686 */	NdrFcShort( 0x2f ),	/* 47 */
/* 1688 */	NdrFcShort( 0x14 ),	/* x86 Stack size/offset = 20 */
/* 1690 */	NdrFcShort( 0x14 ),	/* 20 */
/* 1692 */	NdrFcShort( 0x8 ),	/* 8 */
/* 1694 */	0x44,		/* Oi2 Flags:  has return, has ext, */
			0x4,		/* 4 */
/* 1696 */	0x8,		/* 8 */
			0x1,		/* Ext Flags:  new corr desc, */
/* 1698 */	NdrFcShort( 0x0 ),	/* 0 */
/* 1700 */	NdrFcShort( 0x0 ),	/* 0 */
/* 1702 */	NdrFcShort( 0x0 ),	/* 0 */

	/* Parameter hwndParent */

/* 1704 */	NdrFcShort( 0x48 ),	/* Flags:  in, base type, */
/* 1706 */	NdrFcShort( 0x4 ),	/* x86 Stack size/offset = 4 */
/* 1708 */	0x8,		/* FC_LONG */
			0x0,		/* 0 */

	/* Parameter fAllowAudio */

/* 1710 */	NdrFcShort( 0x48 ),	/* Flags:  in, base type, */
/* 1712 */	NdrFcShort( 0x8 ),	/* x86 Stack size/offset = 8 */
/* 1714 */	0x6,		/* FC_SHORT */
			0x0,		/* 0 */

	/* Parameter fAllowVideo */

/* 1716 */	NdrFcShort( 0x48 ),	/* Flags:  in, base type, */
/* 1718 */	NdrFcShort( 0xc ),	/* x86 Stack size/offset = 12 */
/* 1720 */	0x6,		/* FC_SHORT */
			0x0,		/* 0 */

	/* Return value */

/* 1722 */	NdrFcShort( 0x70 ),	/* Flags:  out, return, base type, */
/* 1724 */	NdrFcShort( 0x10 ),	/* x86 Stack size/offset = 16 */
/* 1726 */	0x8,		/* FC_LONG */
			0x0,		/* 0 */

	/* Procedure get_Version */

/* 1728 */	0x33,		/* FC_AUTO_HANDLE */
			0x6c,		/* Old Flags:  object, Oi2 */
/* 1730 */	NdrFcLong( 0x0 ),	/* 0 */
/* 1734 */	NdrFcShort( 0x30 ),	/* 48 */
/* 1736 */	NdrFcShort( 0xc ),	/* x86 Stack size/offset = 12 */
/* 1738 */	NdrFcShort( 0x0 ),	/* 0 */
/* 1740 */	NdrFcShort( 0x24 ),	/* 36 */
/* 1742 */	0x44,		/* Oi2 Flags:  has return, has ext, */
			0x2,		/* 2 */
/* 1744 */	0x8,		/* 8 */
			0x1,		/* Ext Flags:  new corr desc, */
/* 1746 */	NdrFcShort( 0x0 ),	/* 0 */
/* 1748 */	NdrFcShort( 0x0 ),	/* 0 */
/* 1750 */	NdrFcShort( 0x0 ),	/* 0 */

	/* Parameter plVersion */

/* 1752 */	NdrFcShort( 0x2150 ),	/* Flags:  out, base type, simple ref, srv alloc size=8 */
/* 1754 */	NdrFcShort( 0x4 ),	/* x86 Stack size/offset = 4 */
/* 1756 */	0x8,		/* FC_LONG */
			0x0,		/* 0 */

	/* Return value */

/* 1758 */	NdrFcShort( 0x70 ),	/* Flags:  out, return, base type, */
/* 1760 */	NdrFcShort( 0x8 ),	/* x86 Stack size/offset = 8 */
/* 1762 */	0x8,		/* FC_LONG */
			0x0,		/* 0 */

	/* Procedure put_ClientName */

/* 1764 */	0x33,		/* FC_AUTO_HANDLE */
			0x6c,		/* Old Flags:  object, Oi2 */
/* 1766 */	NdrFcLong( 0x0 ),	/* 0 */
/* 1770 */	NdrFcShort( 0x31 ),	/* 49 */
/* 1772 */	NdrFcShort( 0xc ),	/* x86 Stack size/offset = 12 */
/* 1774 */	NdrFcShort( 0x0 ),	/* 0 */
/* 1776 */	NdrFcShort( 0x8 ),	/* 8 */
/* 1778 */	0x46,		/* Oi2 Flags:  clt must size, has return, has ext, */
			0x2,		/* 2 */
/* 1780 */	0x8,		/* 8 */
			0x5,		/* Ext Flags:  new corr desc, srv corr check, */
/* 1782 */	NdrFcShort( 0x0 ),	/* 0 */
/* 1784 */	NdrFcShort( 0x1 ),	/* 1 */
/* 1786 */	NdrFcShort( 0x0 ),	/* 0 */

	/* Parameter bstrClientName */

/* 1788 */	NdrFcShort( 0x8b ),	/* Flags:  must size, must free, in, by val, */
/* 1790 */	NdrFcShort( 0x4 ),	/* x86 Stack size/offset = 4 */
/* 1792 */	NdrFcShort( 0x20 ),	/* Type Offset=32 */

	/* Return value */

/* 1794 */	NdrFcShort( 0x70 ),	/* Flags:  out, return, base type, */
/* 1796 */	NdrFcShort( 0x8 ),	/* x86 Stack size/offset = 8 */
/* 1798 */	0x8,		/* FC_LONG */
			0x0,		/* 0 */

	/* Procedure put_ClientCurVer */

/* 1800 */	0x33,		/* FC_AUTO_HANDLE */
			0x6c,		/* Old Flags:  object, Oi2 */
/* 1802 */	NdrFcLong( 0x0 ),	/* 0 */
/* 1806 */	NdrFcShort( 0x32 ),	/* 50 */
/* 1808 */	NdrFcShort( 0xc ),	/* x86 Stack size/offset = 12 */
/* 1810 */	NdrFcShort( 0x0 ),	/* 0 */
/* 1812 */	NdrFcShort( 0x8 ),	/* 8 */
/* 1814 */	0x46,		/* Oi2 Flags:  clt must size, has return, has ext, */
			0x2,		/* 2 */
/* 1816 */	0x8,		/* 8 */
			0x5,		/* Ext Flags:  new corr desc, srv corr check, */
/* 1818 */	NdrFcShort( 0x0 ),	/* 0 */
/* 1820 */	NdrFcShort( 0x1 ),	/* 1 */
/* 1822 */	NdrFcShort( 0x0 ),	/* 0 */

	/* Parameter bstrClientCurVer */

/* 1824 */	NdrFcShort( 0x8b ),	/* Flags:  must size, must free, in, by val, */
/* 1826 */	NdrFcShort( 0x4 ),	/* x86 Stack size/offset = 4 */
/* 1828 */	NdrFcShort( 0x20 ),	/* Type Offset=32 */

	/* Return value */

/* 1830 */	NdrFcShort( 0x70 ),	/* Flags:  out, return, base type, */
/* 1832 */	NdrFcShort( 0x8 ),	/* x86 Stack size/offset = 8 */
/* 1834 */	0x8,		/* FC_LONG */
			0x0,		/* 0 */

	/* Procedure InitializeEx */

/* 1836 */	0x33,		/* FC_AUTO_HANDLE */
			0x6c,		/* Old Flags:  object, Oi2 */
/* 1838 */	NdrFcLong( 0x0 ),	/* 0 */
/* 1842 */	NdrFcShort( 0x33 ),	/* 51 */
/* 1844 */	NdrFcShort( 0xc ),	/* x86 Stack size/offset = 12 */
/* 1846 */	NdrFcShort( 0x8 ),	/* 8 */
/* 1848 */	NdrFcShort( 0x8 ),	/* 8 */
/* 1850 */	0x44,		/* Oi2 Flags:  has return, has ext, */
			0x2,		/* 2 */
/* 1852 */	0x8,		/* 8 */
			0x1,		/* Ext Flags:  new corr desc, */
/* 1854 */	NdrFcShort( 0x0 ),	/* 0 */
/* 1856 */	NdrFcShort( 0x0 ),	/* 0 */
/* 1858 */	NdrFcShort( 0x0 ),	/* 0 */

	/* Parameter lFlags */

/* 1860 */	NdrFcShort( 0x48 ),	/* Flags:  in, base type, */
/* 1862 */	NdrFcShort( 0x4 ),	/* x86 Stack size/offset = 4 */
/* 1864 */	0x8,		/* FC_LONG */
			0x0,		/* 0 */

	/* Return value */

/* 1866 */	NdrFcShort( 0x70 ),	/* Flags:  out, return, base type, */
/* 1868 */	NdrFcShort( 0x8 ),	/* x86 Stack size/offset = 8 */
/* 1870 */	0x8,		/* FC_LONG */
			0x0,		/* 0 */

	/* Procedure CreateSessionWithDescription */

/* 1872 */	0x33,		/* FC_AUTO_HANDLE */
			0x6c,		/* Old Flags:  object, Oi2 */
/* 1874 */	NdrFcLong( 0x0 ),	/* 0 */
/* 1878 */	NdrFcShort( 0x34 ),	/* 52 */
/* 1880 */	NdrFcShort( 0x1c ),	/* x86 Stack size/offset = 28 */
/* 1882 */	NdrFcShort( 0x8 ),	/* 8 */
/* 1884 */	NdrFcShort( 0x8 ),	/* 8 */
/* 1886 */	0x47,		/* Oi2 Flags:  srv must size, clt must size, has return, has ext, */
			0x6,		/* 6 */
/* 1888 */	0x8,		/* 8 */
			0x5,		/* Ext Flags:  new corr desc, srv corr check, */
/* 1890 */	NdrFcShort( 0x0 ),	/* 0 */
/* 1892 */	NdrFcShort( 0x2 ),	/* 2 */
/* 1894 */	NdrFcShort( 0x0 ),	/* 0 */

	/* Parameter bstrContentType */

/* 1896 */	NdrFcShort( 0x8b ),	/* Flags:  must size, must free, in, by val, */
/* 1898 */	NdrFcShort( 0x4 ),	/* x86 Stack size/offset = 4 */
/* 1900 */	NdrFcShort( 0x20 ),	/* Type Offset=32 */

	/* Parameter bstrSessionDescription */

/* 1902 */	NdrFcShort( 0x8b ),	/* Flags:  must size, must free, in, by val, */
/* 1904 */	NdrFcShort( 0x8 ),	/* x86 Stack size/offset = 8 */
/* 1906 */	NdrFcShort( 0x20 ),	/* Type Offset=32 */

	/* Parameter pProfile */

/* 1908 */	NdrFcShort( 0xb ),	/* Flags:  must size, must free, in, */
/* 1910 */	NdrFcShort( 0xc ),	/* x86 Stack size/offset = 12 */
/* 1912 */	NdrFcShort( 0x2a ),	/* Type Offset=42 */

	/* Parameter lFlags */

/* 1914 */	NdrFcShort( 0x48 ),	/* Flags:  in, base type, */
/* 1916 */	NdrFcShort( 0x10 ),	/* x86 Stack size/offset = 16 */
/* 1918 */	0x8,		/* FC_LONG */
			0x0,		/* 0 */

	/* Parameter ppSession2 */

/* 1920 */	NdrFcShort( 0x13 ),	/* Flags:  must size, must free, out, */
/* 1922 */	NdrFcShort( 0x14 ),	/* x86 Stack size/offset = 20 */
/* 1924 */	NdrFcShort( 0x474 ),	/* Type Offset=1140 */

	/* Return value */

/* 1926 */	NdrFcShort( 0x70 ),	/* Flags:  out, return, base type, */
/* 1928 */	NdrFcShort( 0x18 ),	/* x86 Stack size/offset = 24 */
/* 1930 */	0x8,		/* FC_LONG */
			0x0,		/* 0 */

	/* Procedure SetSessionDescriptionManager */

/* 1932 */	0x33,		/* FC_AUTO_HANDLE */
			0x6c,		/* Old Flags:  object, Oi2 */
/* 1934 */	NdrFcLong( 0x0 ),	/* 0 */
/* 1938 */	NdrFcShort( 0x35 ),	/* 53 */
/* 1940 */	NdrFcShort( 0xc ),	/* x86 Stack size/offset = 12 */
/* 1942 */	NdrFcShort( 0x0 ),	/* 0 */
/* 1944 */	NdrFcShort( 0x8 ),	/* 8 */
/* 1946 */	0x46,		/* Oi2 Flags:  clt must size, has return, has ext, */
			0x2,		/* 2 */
/* 1948 */	0x8,		/* 8 */
			0x1,		/* Ext Flags:  new corr desc, */
/* 1950 */	NdrFcShort( 0x0 ),	/* 0 */
/* 1952 */	NdrFcShort( 0x0 ),	/* 0 */
/* 1954 */	NdrFcShort( 0x0 ),	/* 0 */

	/* Parameter pSessionDescriptionManager */

/* 1956 */	NdrFcShort( 0xb ),	/* Flags:  must size, must free, in, */
/* 1958 */	NdrFcShort( 0x4 ),	/* x86 Stack size/offset = 4 */
/* 1960 */	NdrFcShort( 0x48a ),	/* Type Offset=1162 */

	/* Return value */

/* 1962 */	NdrFcShort( 0x70 ),	/* Flags:  out, return, base type, */
/* 1964 */	NdrFcShort( 0x8 ),	/* x86 Stack size/offset = 8 */
/* 1966 */	0x8,		/* FC_LONG */
			0x0,		/* 0 */

	/* Procedure put_PreferredSecurityLevel */

/* 1968 */	0x33,		/* FC_AUTO_HANDLE */
			0x6c,		/* Old Flags:  object, Oi2 */
/* 1970 */	NdrFcLong( 0x0 ),	/* 0 */
/* 1974 */	NdrFcShort( 0x36 ),	/* 54 */
/* 1976 */	NdrFcShort( 0x10 ),	/* x86 Stack size/offset = 16 */
/* 1978 */	NdrFcShort( 0xc ),	/* 12 */
/* 1980 */	NdrFcShort( 0x8 ),	/* 8 */
/* 1982 */	0x44,		/* Oi2 Flags:  has return, has ext, */
			0x3,		/* 3 */
/* 1984 */	0x8,		/* 8 */
			0x1,		/* Ext Flags:  new corr desc, */
/* 1986 */	NdrFcShort( 0x0 ),	/* 0 */
/* 1988 */	NdrFcShort( 0x0 ),	/* 0 */
/* 1990 */	NdrFcShort( 0x0 ),	/* 0 */

	/* Parameter enSecurityType */

/* 1992 */	NdrFcShort( 0x48 ),	/* Flags:  in, base type, */
/* 1994 */	NdrFcShort( 0x4 ),	/* x86 Stack size/offset = 4 */
/* 1996 */	0xd,		/* FC_ENUM16 */
			0x0,		/* 0 */

	/* Parameter enSecurityLevel */

/* 1998 */	NdrFcShort( 0x48 ),	/* Flags:  in, base type, */
/* 2000 */	NdrFcShort( 0x8 ),	/* x86 Stack size/offset = 8 */
/* 2002 */	0xd,		/* FC_ENUM16 */
			0x0,		/* 0 */

	/* Return value */

/* 2004 */	NdrFcShort( 0x70 ),	/* Flags:  out, return, base type, */
/* 2006 */	NdrFcShort( 0xc ),	/* x86 Stack size/offset = 12 */
/* 2008 */	0x8,		/* FC_LONG */
			0x0,		/* 0 */

	/* Procedure get_PreferredSecurityLevel */

/* 2010 */	0x33,		/* FC_AUTO_HANDLE */
			0x6c,		/* Old Flags:  object, Oi2 */
/* 2012 */	NdrFcLong( 0x0 ),	/* 0 */
/* 2016 */	NdrFcShort( 0x37 ),	/* 55 */
/* 2018 */	NdrFcShort( 0x10 ),	/* x86 Stack size/offset = 16 */
/* 2020 */	NdrFcShort( 0x6 ),	/* 6 */
/* 2022 */	NdrFcShort( 0x22 ),	/* 34 */
/* 2024 */	0x44,		/* Oi2 Flags:  has return, has ext, */
			0x3,		/* 3 */
/* 2026 */	0x8,		/* 8 */
			0x1,		/* Ext Flags:  new corr desc, */
/* 2028 */	NdrFcShort( 0x0 ),	/* 0 */
/* 2030 */	NdrFcShort( 0x0 ),	/* 0 */
/* 2032 */	NdrFcShort( 0x0 ),	/* 0 */

	/* Parameter enSecurityType */

/* 2034 */	NdrFcShort( 0x48 ),	/* Flags:  in, base type, */
/* 2036 */	NdrFcShort( 0x4 ),	/* x86 Stack size/offset = 4 */
/* 2038 */	0xd,		/* FC_ENUM16 */
			0x0,		/* 0 */

	/* Parameter penSecurityLevel */

/* 2040 */	NdrFcShort( 0x2010 ),	/* Flags:  out, srv alloc size=8 */
/* 2042 */	NdrFcShort( 0x8 ),	/* x86 Stack size/offset = 8 */
/* 2044 */	NdrFcShort( 0x52 ),	/* Type Offset=82 */

	/* Return value */

/* 2046 */	NdrFcShort( 0x70 ),	/* Flags:  out, return, base type, */
/* 2048 */	NdrFcShort( 0xc ),	/* x86 Stack size/offset = 12 */
/* 2050 */	0x8,		/* FC_LONG */
			0x0,		/* 0 */

	/* Procedure put_AllowedPorts */

/* 2052 */	0x33,		/* FC_AUTO_HANDLE */
			0x6c,		/* Old Flags:  object, Oi2 */
/* 2054 */	NdrFcLong( 0x0 ),	/* 0 */
/* 2058 */	NdrFcShort( 0x38 ),	/* 56 */
/* 2060 */	NdrFcShort( 0x10 ),	/* x86 Stack size/offset = 16 */
/* 2062 */	NdrFcShort( 0xe ),	/* 14 */
/* 2064 */	NdrFcShort( 0x8 ),	/* 8 */
/* 2066 */	0x44,		/* Oi2 Flags:  has return, has ext, */
			0x3,		/* 3 */
/* 2068 */	0x8,		/* 8 */
			0x1,		/* Ext Flags:  new corr desc, */
/* 2070 */	NdrFcShort( 0x0 ),	/* 0 */
/* 2072 */	NdrFcShort( 0x0 ),	/* 0 */
/* 2074 */	NdrFcShort( 0x0 ),	/* 0 */

	/* Parameter lTransport */

/* 2076 */	NdrFcShort( 0x48 ),	/* Flags:  in, base type, */
/* 2078 */	NdrFcShort( 0x4 ),	/* x86 Stack size/offset = 4 */
/* 2080 */	0x8,		/* FC_LONG */
			0x0,		/* 0 */

	/* Parameter enListenMode */

/* 2082 */	NdrFcShort( 0x48 ),	/* Flags:  in, base type, */
/* 2084 */	NdrFcShort( 0x8 ),	/* x86 Stack size/offset = 8 */
/* 2086 */	0xd,		/* FC_ENUM16 */
			0x0,		/* 0 */

	/* Return value */

/* 2088 */	NdrFcShort( 0x70 ),	/* Flags:  out, return, base type, */
/* 2090 */	NdrFcShort( 0xc ),	/* x86 Stack size/offset = 12 */
/* 2092 */	0x8,		/* FC_LONG */
			0x0,		/* 0 */

	/* Procedure get_AllowedPorts */

/* 2094 */	0x33,		/* FC_AUTO_HANDLE */
			0x6c,		/* Old Flags:  object, Oi2 */
/* 2096 */	NdrFcLong( 0x0 ),	/* 0 */
/* 2100 */	NdrFcShort( 0x39 ),	/* 57 */
/* 2102 */	NdrFcShort( 0x10 ),	/* x86 Stack size/offset = 16 */
/* 2104 */	NdrFcShort( 0x8 ),	/* 8 */
/* 2106 */	NdrFcShort( 0x22 ),	/* 34 */
/* 2108 */	0x44,		/* Oi2 Flags:  has return, has ext, */
			0x3,		/* 3 */
/* 2110 */	0x8,		/* 8 */
			0x1,		/* Ext Flags:  new corr desc, */
/* 2112 */	NdrFcShort( 0x0 ),	/* 0 */
/* 2114 */	NdrFcShort( 0x0 ),	/* 0 */
/* 2116 */	NdrFcShort( 0x0 ),	/* 0 */

	/* Parameter lTransport */

/* 2118 */	NdrFcShort( 0x48 ),	/* Flags:  in, base type, */
/* 2120 */	NdrFcShort( 0x4 ),	/* x86 Stack size/offset = 4 */
/* 2122 */	0x8,		/* FC_LONG */
			0x0,		/* 0 */

	/* Parameter penListenMode */

/* 2124 */	NdrFcShort( 0x2010 ),	/* Flags:  out, srv alloc size=8 */
/* 2126 */	NdrFcShort( 0x8 ),	/* x86 Stack size/offset = 8 */
/* 2128 */	NdrFcShort( 0x52 ),	/* Type Offset=82 */

	/* Return value */

/* 2130 */	NdrFcShort( 0x70 ),	/* Flags:  out, return, base type, */
/* 2132 */	NdrFcShort( 0xc ),	/* x86 Stack size/offset = 12 */
/* 2134 */	0x8,		/* FC_LONG */
			0x0,		/* 0 */

	/* Procedure EnablePresence */

/* 2136 */	0x33,		/* FC_AUTO_HANDLE */
			0x6c,		/* Old Flags:  object, Oi2 */
/* 2138 */	NdrFcLong( 0x0 ),	/* 0 */
/* 2142 */	NdrFcShort( 0x3 ),	/* 3 */
/* 2144 */	NdrFcShort( 0x1c ),	/* x86 Stack size/offset = 28 */
/* 2146 */	NdrFcShort( 0x6 ),	/* 6 */
/* 2148 */	NdrFcShort( 0x8 ),	/* 8 */
/* 2150 */	0x46,		/* Oi2 Flags:  clt must size, has return, has ext, */
			0x3,		/* 3 */
/* 2152 */	0x8,		/* 8 */
			0x5,		/* Ext Flags:  new corr desc, srv corr check, */
/* 2154 */	NdrFcShort( 0x0 ),	/* 0 */
/* 2156 */	NdrFcShort( 0x20 ),	/* 32 */
/* 2158 */	NdrFcShort( 0x0 ),	/* 0 */

	/* Parameter fUseStorage */

/* 2160 */	NdrFcShort( 0x48 ),	/* Flags:  in, base type, */
/* 2162 */	NdrFcShort( 0x4 ),	/* x86 Stack size/offset = 4 */
/* 2164 */	0x6,		/* FC_SHORT */
			0x0,		/* 0 */

	/* Parameter varStorage */

/* 2166 */	NdrFcShort( 0x8b ),	/* Flags:  must size, must free, in, by val, */
/* 2168 */	NdrFcShort( 0x8 ),	/* x86 Stack size/offset = 8 */
/* 2170 */	NdrFcShort( 0x4a0 ),	/* Type Offset=1184 */

	/* Return value */

/* 2172 */	NdrFcShort( 0x70 ),	/* Flags:  out, return, base type, */
/* 2174 */	NdrFcShort( 0x18 ),	/* x86 Stack size/offset = 24 */
/* 2176 */	0x8,		/* FC_LONG */
			0x0,		/* 0 */

	/* Procedure Export */

/* 2178 */	0x33,		/* FC_AUTO_HANDLE */
			0x6c,		/* Old Flags:  object, Oi2 */
/* 2180 */	NdrFcLong( 0x0 ),	/* 0 */
/* 2184 */	NdrFcShort( 0x4 ),	/* 4 */
/* 2186 */	NdrFcShort( 0x18 ),	/* x86 Stack size/offset = 24 */
/* 2188 */	NdrFcShort( 0x0 ),	/* 0 */
/* 2190 */	NdrFcShort( 0x8 ),	/* 8 */
/* 2192 */	0x46,		/* Oi2 Flags:  clt must size, has return, has ext, */
			0x2,		/* 2 */
/* 2194 */	0x8,		/* 8 */
			0x5,		/* Ext Flags:  new corr desc, srv corr check, */
/* 2196 */	NdrFcShort( 0x0 ),	/* 0 */
/* 2198 */	NdrFcShort( 0x20 ),	/* 32 */
/* 2200 */	NdrFcShort( 0x0 ),	/* 0 */

	/* Parameter varStorage */

/* 2202 */	NdrFcShort( 0x8b ),	/* Flags:  must size, must free, in, by val, */
/* 2204 */	NdrFcShort( 0x4 ),	/* x86 Stack size/offset = 4 */
/* 2206 */	NdrFcShort( 0x4a0 ),	/* Type Offset=1184 */

	/* Return value */

/* 2208 */	NdrFcShort( 0x70 ),	/* Flags:  out, return, base type, */
/* 2210 */	NdrFcShort( 0x14 ),	/* x86 Stack size/offset = 20 */
/* 2212 */	0x8,		/* FC_LONG */
			0x0,		/* 0 */

	/* Procedure Import */

/* 2214 */	0x33,		/* FC_AUTO_HANDLE */
			0x6c,		/* Old Flags:  object, Oi2 */
/* 2216 */	NdrFcLong( 0x0 ),	/* 0 */
/* 2220 */	NdrFcShort( 0x5 ),	/* 5 */
/* 2222 */	NdrFcShort( 0x1c ),	/* x86 Stack size/offset = 28 */
/* 2224 */	NdrFcShort( 0x6 ),	/* 6 */
/* 2226 */	NdrFcShort( 0x8 ),	/* 8 */
/* 2228 */	0x46,		/* Oi2 Flags:  clt must size, has return, has ext, */
			0x3,		/* 3 */
/* 2230 */	0x8,		/* 8 */
			0x5,		/* Ext Flags:  new corr desc, srv corr check, */
/* 2232 */	NdrFcShort( 0x0 ),	/* 0 */
/* 2234 */	NdrFcShort( 0x20 ),	/* 32 */
/* 2236 */	NdrFcShort( 0x0 ),	/* 0 */

	/* Parameter varStorage */

/* 2238 */	NdrFcShort( 0x8b ),	/* Flags:  must size, must free, in, by val, */
/* 2240 */	NdrFcShort( 0x4 ),	/* x86 Stack size/offset = 4 */
/* 2242 */	NdrFcShort( 0x4a0 ),	/* Type Offset=1184 */

	/* Parameter fReplaceAll */

/* 2244 */	NdrFcShort( 0x48 ),	/* Flags:  in, base type, */
/* 2246 */	NdrFcShort( 0x14 ),	/* x86 Stack size/offset = 20 */
/* 2248 */	0x6,		/* FC_SHORT */
			0x0,		/* 0 */

	/* Return value */

/* 2250 */	NdrFcShort( 0x70 ),	/* Flags:  out, return, base type, */
/* 2252 */	NdrFcShort( 0x18 ),	/* x86 Stack size/offset = 24 */
/* 2254 */	0x8,		/* FC_LONG */
			0x0,		/* 0 */

	/* Procedure EnumerateBuddies */

/* 2256 */	0x33,		/* FC_AUTO_HANDLE */
			0x6c,		/* Old Flags:  object, Oi2 */
/* 2258 */	NdrFcLong( 0x0 ),	/* 0 */
/* 2262 */	NdrFcShort( 0x6 ),	/* 6 */
/* 2264 */	NdrFcShort( 0xc ),	/* x86 Stack size/offset = 12 */
/* 2266 */	NdrFcShort( 0x0 ),	/* 0 */
/* 2268 */	NdrFcShort( 0x8 ),	/* 8 */
/* 2270 */	0x45,		/* Oi2 Flags:  srv must size, has return, has ext, */
			0x2,		/* 2 */
/* 2272 */	0x8,		/* 8 */
			0x1,		/* Ext Flags:  new corr desc, */
/* 2274 */	NdrFcShort( 0x0 ),	/* 0 */
/* 2276 */	NdrFcShort( 0x0 ),	/* 0 */
/* 2278 */	NdrFcShort( 0x0 ),	/* 0 */

	/* Parameter ppEnum */

/* 2280 */	NdrFcShort( 0x13 ),	/* Flags:  must size, must free, out, */
/* 2282 */	NdrFcShort( 0x4 ),	/* x86 Stack size/offset = 4 */
/* 2284 */	NdrFcShort( 0x4aa ),	/* Type Offset=1194 */

	/* Return value */

/* 2286 */	NdrFcShort( 0x70 ),	/* Flags:  out, return, base type, */
/* 2288 */	NdrFcShort( 0x8 ),	/* x86 Stack size/offset = 8 */
/* 2290 */	0x8,		/* FC_LONG */
			0x0,		/* 0 */

	/* Procedure get_Participants */


	/* Procedure get_Profiles */


	/* Procedure get_Buddies */

/* 2292 */	0x33,		/* FC_AUTO_HANDLE */
			0x6c,		/* Old Flags:  object, Oi2 */
/* 2294 */	NdrFcLong( 0x0 ),	/* 0 */
/* 2298 */	NdrFcShort( 0x7 ),	/* 7 */
/* 2300 */	NdrFcShort( 0xc ),	/* x86 Stack size/offset = 12 */
/* 2302 */	NdrFcShort( 0x0 ),	/* 0 */
/* 2304 */	NdrFcShort( 0x8 ),	/* 8 */
/* 2306 */	0x45,		/* Oi2 Flags:  srv must size, has return, has ext, */
			0x2,		/* 2 */
/* 2308 */	0x8,		/* 8 */
			0x1,		/* Ext Flags:  new corr desc, */
/* 2310 */	NdrFcShort( 0x0 ),	/* 0 */
/* 2312 */	NdrFcShort( 0x0 ),	/* 0 */
/* 2314 */	NdrFcShort( 0x0 ),	/* 0 */

	/* Parameter ppCollection */


	/* Parameter ppCollection */


	/* Parameter ppCollection */

/* 2316 */	NdrFcShort( 0x13 ),	/* Flags:  must size, must free, out, */
/* 2318 */	NdrFcShort( 0x4 ),	/* x86 Stack size/offset = 4 */
/* 2320 */	NdrFcShort( 0x4c0 ),	/* Type Offset=1216 */

	/* Return value */


	/* Return value */


	/* Return value */

/* 2322 */	NdrFcShort( 0x70 ),	/* Flags:  out, return, base type, */
/* 2324 */	NdrFcShort( 0x8 ),	/* x86 Stack size/offset = 8 */
/* 2326 */	0x8,		/* FC_LONG */
			0x0,		/* 0 */

	/* Procedure get_Buddy */

/* 2328 */	0x33,		/* FC_AUTO_HANDLE */
			0x6c,		/* Old Flags:  object, Oi2 */
/* 2330 */	NdrFcLong( 0x0 ),	/* 0 */
/* 2334 */	NdrFcShort( 0x8 ),	/* 8 */
/* 2336 */	NdrFcShort( 0x10 ),	/* x86 Stack size/offset = 16 */
/* 2338 */	NdrFcShort( 0x0 ),	/* 0 */
/* 2340 */	NdrFcShort( 0x8 ),	/* 8 */
/* 2342 */	0x47,		/* Oi2 Flags:  srv must size, clt must size, has return, has ext, */
			0x3,		/* 3 */
/* 2344 */	0x8,		/* 8 */
			0x5,		/* Ext Flags:  new corr desc, srv corr check, */
/* 2346 */	NdrFcShort( 0x0 ),	/* 0 */
/* 2348 */	NdrFcShort( 0x1 ),	/* 1 */
/* 2350 */	NdrFcShort( 0x0 ),	/* 0 */

	/* Parameter bstrPresentityURI */

/* 2352 */	NdrFcShort( 0x8b ),	/* Flags:  must size, must free, in, by val, */
/* 2354 */	NdrFcShort( 0x4 ),	/* x86 Stack size/offset = 4 */
/* 2356 */	NdrFcShort( 0x20 ),	/* Type Offset=32 */

	/* Parameter ppBuddy */

/* 2358 */	NdrFcShort( 0x13 ),	/* Flags:  must size, must free, out, */
/* 2360 */	NdrFcShort( 0x8 ),	/* x86 Stack size/offset = 8 */
/* 2362 */	NdrFcShort( 0x4d6 ),	/* Type Offset=1238 */

	/* Return value */

/* 2364 */	NdrFcShort( 0x70 ),	/* Flags:  out, return, base type, */
/* 2366 */	NdrFcShort( 0xc ),	/* x86 Stack size/offset = 12 */
/* 2368 */	0x8,		/* FC_LONG */
			0x0,		/* 0 */

	/* Procedure AddBuddy */

/* 2370 */	0x33,		/* FC_AUTO_HANDLE */
			0x6c,		/* Old Flags:  object, Oi2 */
/* 2372 */	NdrFcLong( 0x0 ),	/* 0 */
/* 2376 */	NdrFcShort( 0x9 ),	/* 9 */
/* 2378 */	NdrFcShort( 0x24 ),	/* x86 Stack size/offset = 36 */
/* 2380 */	NdrFcShort( 0xe ),	/* 14 */
/* 2382 */	NdrFcShort( 0x8 ),	/* 8 */
/* 2384 */	0x47,		/* Oi2 Flags:  srv must size, clt must size, has return, has ext, */
			0x8,		/* 8 */
/* 2386 */	0x8,		/* 8 */
			0x5,		/* Ext Flags:  new corr desc, srv corr check, */
/* 2388 */	NdrFcShort( 0x0 ),	/* 0 */
/* 2390 */	NdrFcShort( 0x3 ),	/* 3 */
/* 2392 */	NdrFcShort( 0x0 ),	/* 0 */

	/* Parameter bstrPresentityURI */

/* 2394 */	NdrFcShort( 0x8b ),	/* Flags:  must size, must free, in, by val, */
/* 2396 */	NdrFcShort( 0x4 ),	/* x86 Stack size/offset = 4 */
/* 2398 */	NdrFcShort( 0x20 ),	/* Type Offset=32 */

	/* Parameter bstrUserName */

/* 2400 */	NdrFcShort( 0x8b ),	/* Flags:  must size, must free, in, by val, */
/* 2402 */	NdrFcShort( 0x8 ),	/* x86 Stack size/offset = 8 */
/* 2404 */	NdrFcShort( 0x20 ),	/* Type Offset=32 */

	/* Parameter bstrData */

/* 2406 */	NdrFcShort( 0x8b ),	/* Flags:  must size, must free, in, by val, */
/* 2408 */	NdrFcShort( 0xc ),	/* x86 Stack size/offset = 12 */
/* 2410 */	NdrFcShort( 0x20 ),	/* Type Offset=32 */

	/* Parameter fPersistent */

/* 2412 */	NdrFcShort( 0x48 ),	/* Flags:  in, base type, */
/* 2414 */	NdrFcShort( 0x10 ),	/* x86 Stack size/offset = 16 */
/* 2416 */	0x6,		/* FC_SHORT */
			0x0,		/* 0 */

	/* Parameter pProfile */

/* 2418 */	NdrFcShort( 0xb ),	/* Flags:  must size, must free, in, */
/* 2420 */	NdrFcShort( 0x14 ),	/* x86 Stack size/offset = 20 */
/* 2422 */	NdrFcShort( 0x2a ),	/* Type Offset=42 */

	/* Parameter lFlags */

/* 2424 */	NdrFcShort( 0x48 ),	/* Flags:  in, base type, */
/* 2426 */	NdrFcShort( 0x18 ),	/* x86 Stack size/offset = 24 */
/* 2428 */	0x8,		/* FC_LONG */
			0x0,		/* 0 */

	/* Parameter ppBuddy */

/* 2430 */	NdrFcShort( 0x13 ),	/* Flags:  must size, must free, out, */
/* 2432 */	NdrFcShort( 0x1c ),	/* x86 Stack size/offset = 28 */
/* 2434 */	NdrFcShort( 0x4d6 ),	/* Type Offset=1238 */

	/* Return value */

/* 2436 */	NdrFcShort( 0x70 ),	/* Flags:  out, return, base type, */
/* 2438 */	NdrFcShort( 0x20 ),	/* x86 Stack size/offset = 32 */
/* 2440 */	0x8,		/* FC_LONG */
			0x0,		/* 0 */

	/* Procedure RemoveBuddy */

/* 2442 */	0x33,		/* FC_AUTO_HANDLE */
			0x6c,		/* Old Flags:  object, Oi2 */
/* 2444 */	NdrFcLong( 0x0 ),	/* 0 */
/* 2448 */	NdrFcShort( 0xa ),	/* 10 */
/* 2450 */	NdrFcShort( 0xc ),	/* x86 Stack size/offset = 12 */
/* 2452 */	NdrFcShort( 0x0 ),	/* 0 */
/* 2454 */	NdrFcShort( 0x8 ),	/* 8 */
/* 2456 */	0x46,		/* Oi2 Flags:  clt must size, has return, has ext, */
			0x2,		/* 2 */
/* 2458 */	0x8,		/* 8 */
			0x1,		/* Ext Flags:  new corr desc, */
/* 2460 */	NdrFcShort( 0x0 ),	/* 0 */
/* 2462 */	NdrFcShort( 0x0 ),	/* 0 */
/* 2464 */	NdrFcShort( 0x0 ),	/* 0 */

	/* Parameter pBuddy */

/* 2466 */	NdrFcShort( 0xb ),	/* Flags:  must size, must free, in, */
/* 2468 */	NdrFcShort( 0x4 ),	/* x86 Stack size/offset = 4 */
/* 2470 */	NdrFcShort( 0x4da ),	/* Type Offset=1242 */

	/* Return value */

/* 2472 */	NdrFcShort( 0x70 ),	/* Flags:  out, return, base type, */
/* 2474 */	NdrFcShort( 0x8 ),	/* x86 Stack size/offset = 8 */
/* 2476 */	0x8,		/* FC_LONG */
			0x0,		/* 0 */

	/* Procedure EnumerateWatchers */

/* 2478 */	0x33,		/* FC_AUTO_HANDLE */
			0x6c,		/* Old Flags:  object, Oi2 */
/* 2480 */	NdrFcLong( 0x0 ),	/* 0 */
/* 2484 */	NdrFcShort( 0xb ),	/* 11 */
/* 2486 */	NdrFcShort( 0xc ),	/* x86 Stack size/offset = 12 */
/* 2488 */	NdrFcShort( 0x0 ),	/* 0 */
/* 2490 */	NdrFcShort( 0x8 ),	/* 8 */
/* 2492 */	0x45,		/* Oi2 Flags:  srv must size, has return, has ext, */
			0x2,		/* 2 */
/* 2494 */	0x8,		/* 8 */
			0x1,		/* Ext Flags:  new corr desc, */
/* 2496 */	NdrFcShort( 0x0 ),	/* 0 */
/* 2498 */	NdrFcShort( 0x0 ),	/* 0 */
/* 2500 */	NdrFcShort( 0x0 ),	/* 0 */

	/* Parameter ppEnum */

/* 2502 */	NdrFcShort( 0x13 ),	/* Flags:  must size, must free, out, */
/* 2504 */	NdrFcShort( 0x4 ),	/* x86 Stack size/offset = 4 */
/* 2506 */	NdrFcShort( 0x4ec ),	/* Type Offset=1260 */

	/* Return value */

/* 2508 */	NdrFcShort( 0x70 ),	/* Flags:  out, return, base type, */
/* 2510 */	NdrFcShort( 0x8 ),	/* x86 Stack size/offset = 8 */
/* 2512 */	0x8,		/* FC_LONG */
			0x0,		/* 0 */

	/* Procedure get_Watchers */

/* 2514 */	0x33,		/* FC_AUTO_HANDLE */
			0x6c,		/* Old Flags:  object, Oi2 */
/* 2516 */	NdrFcLong( 0x0 ),	/* 0 */
/* 2520 */	NdrFcShort( 0xc ),	/* 12 */
/* 2522 */	NdrFcShort( 0xc ),	/* x86 Stack size/offset = 12 */
/* 2524 */	NdrFcShort( 0x0 ),	/* 0 */
/* 2526 */	NdrFcShort( 0x8 ),	/* 8 */
/* 2528 */	0x45,		/* Oi2 Flags:  srv must size, has return, has ext, */
			0x2,		/* 2 */
/* 2530 */	0x8,		/* 8 */
			0x1,		/* Ext Flags:  new corr desc, */
/* 2532 */	NdrFcShort( 0x0 ),	/* 0 */
/* 2534 */	NdrFcShort( 0x0 ),	/* 0 */
/* 2536 */	NdrFcShort( 0x0 ),	/* 0 */

	/* Parameter ppCollection */

/* 2538 */	NdrFcShort( 0x13 ),	/* Flags:  must size, must free, out, */
/* 2540 */	NdrFcShort( 0x4 ),	/* x86 Stack size/offset = 4 */
/* 2542 */	NdrFcShort( 0x4c0 ),	/* Type Offset=1216 */

	/* Return value */

/* 2544 */	NdrFcShort( 0x70 ),	/* Flags:  out, return, base type, */
/* 2546 */	NdrFcShort( 0x8 ),	/* x86 Stack size/offset = 8 */
/* 2548 */	0x8,		/* FC_LONG */
			0x0,		/* 0 */

	/* Procedure get_Watcher */

/* 2550 */	0x33,		/* FC_AUTO_HANDLE */
			0x6c,		/* Old Flags:  object, Oi2 */
/* 2552 */	NdrFcLong( 0x0 ),	/* 0 */
/* 2556 */	NdrFcShort( 0xd ),	/* 13 */
/* 2558 */	NdrFcShort( 0x10 ),	/* x86 Stack size/offset = 16 */
/* 2560 */	NdrFcShort( 0x0 ),	/* 0 */
/* 2562 */	NdrFcShort( 0x8 ),	/* 8 */
/* 2564 */	0x47,		/* Oi2 Flags:  srv must size, clt must size, has return, has ext, */
			0x3,		/* 3 */
/* 2566 */	0x8,		/* 8 */
			0x5,		/* Ext Flags:  new corr desc, srv corr check, */
/* 2568 */	NdrFcShort( 0x0 ),	/* 0 */
/* 2570 */	NdrFcShort( 0x1 ),	/* 1 */
/* 2572 */	NdrFcShort( 0x0 ),	/* 0 */

	/* Parameter bstrPresentityURI */

/* 2574 */	NdrFcShort( 0x8b ),	/* Flags:  must size, must free, in, by val, */
/* 2576 */	NdrFcShort( 0x4 ),	/* x86 Stack size/offset = 4 */
/* 2578 */	NdrFcShort( 0x20 ),	/* Type Offset=32 */

	/* Parameter ppWatcher */

/* 2580 */	NdrFcShort( 0x13 ),	/* Flags:  must size, must free, out, */
/* 2582 */	NdrFcShort( 0x8 ),	/* x86 Stack size/offset = 8 */
/* 2584 */	NdrFcShort( 0x502 ),	/* Type Offset=1282 */

	/* Return value */

/* 2586 */	NdrFcShort( 0x70 ),	/* Flags:  out, return, base type, */
/* 2588 */	NdrFcShort( 0xc ),	/* x86 Stack size/offset = 12 */
/* 2590 */	0x8,		/* FC_LONG */
			0x0,		/* 0 */

	/* Procedure AddWatcher */

/* 2592 */	0x33,		/* FC_AUTO_HANDLE */
			0x6c,		/* Old Flags:  object, Oi2 */
/* 2594 */	NdrFcLong( 0x0 ),	/* 0 */
/* 2598 */	NdrFcShort( 0xe ),	/* 14 */
/* 2600 */	NdrFcShort( 0x20 ),	/* x86 Stack size/offset = 32 */
/* 2602 */	NdrFcShort( 0xc ),	/* 12 */
/* 2604 */	NdrFcShort( 0x8 ),	/* 8 */
/* 2606 */	0x47,		/* Oi2 Flags:  srv must size, clt must size, has return, has ext, */
			0x7,		/* 7 */
/* 2608 */	0x8,		/* 8 */
			0x5,		/* Ext Flags:  new corr desc, srv corr check, */
/* 2610 */	NdrFcShort( 0x0 ),	/* 0 */
/* 2612 */	NdrFcShort( 0x3 ),	/* 3 */
/* 2614 */	NdrFcShort( 0x0 ),	/* 0 */

	/* Parameter bstrPresentityURI */

/* 2616 */	NdrFcShort( 0x8b ),	/* Flags:  must size, must free, in, by val, */
/* 2618 */	NdrFcShort( 0x4 ),	/* x86 Stack size/offset = 4 */
/* 2620 */	NdrFcShort( 0x20 ),	/* Type Offset=32 */

	/* Parameter bstrUserName */

/* 2622 */	NdrFcShort( 0x8b ),	/* Flags:  must size, must free, in, by val, */
/* 2624 */	NdrFcShort( 0x8 ),	/* x86 Stack size/offset = 8 */
/* 2626 */	NdrFcShort( 0x20 ),	/* Type Offset=32 */

	/* Parameter bstrData */

/* 2628 */	NdrFcShort( 0x8b ),	/* Flags:  must size, must free, in, by val, */
/* 2630 */	NdrFcShort( 0xc ),	/* x86 Stack size/offset = 12 */
/* 2632 */	NdrFcShort( 0x20 ),	/* Type Offset=32 */

	/* Parameter fBlocked */

/* 2634 */	NdrFcShort( 0x48 ),	/* Flags:  in, base type, */
/* 2636 */	NdrFcShort( 0x10 ),	/* x86 Stack size/offset = 16 */
/* 2638 */	0x6,		/* FC_SHORT */
			0x0,		/* 0 */

	/* Parameter fPersistent */

/* 2640 */	NdrFcShort( 0x48 ),	/* Flags:  in, base type, */
/* 2642 */	NdrFcShort( 0x14 ),	/* x86 Stack size/offset = 20 */
/* 2644 */	0x6,		/* FC_SHORT */
			0x0,		/* 0 */

	/* Parameter ppWatcher */

/* 2646 */	NdrFcShort( 0x13 ),	/* Flags:  must size, must free, out, */
/* 2648 */	NdrFcShort( 0x18 ),	/* x86 Stack size/offset = 24 */
/* 2650 */	NdrFcShort( 0x502 ),	/* Type Offset=1282 */

	/* Return value */

/* 2652 */	NdrFcShort( 0x70 ),	/* Flags:  out, return, base type, */
/* 2654 */	NdrFcShort( 0x1c ),	/* x86 Stack size/offset = 28 */
/* 2656 */	0x8,		/* FC_LONG */
			0x0,		/* 0 */

	/* Procedure RemoveWatcher */

/* 2658 */	0x33,		/* FC_AUTO_HANDLE */
			0x6c,		/* Old Flags:  object, Oi2 */
/* 2660 */	NdrFcLong( 0x0 ),	/* 0 */
/* 2664 */	NdrFcShort( 0xf ),	/* 15 */
/* 2666 */	NdrFcShort( 0xc ),	/* x86 Stack size/offset = 12 */
/* 2668 */	NdrFcShort( 0x0 ),	/* 0 */
/* 2670 */	NdrFcShort( 0x8 ),	/* 8 */
/* 2672 */	0x46,		/* Oi2 Flags:  clt must size, has return, has ext, */
			0x2,		/* 2 */
/* 2674 */	0x8,		/* 8 */
			0x1,		/* Ext Flags:  new corr desc, */
/* 2676 */	NdrFcShort( 0x0 ),	/* 0 */
/* 2678 */	NdrFcShort( 0x0 ),	/* 0 */
/* 2680 */	NdrFcShort( 0x0 ),	/* 0 */

	/* Parameter pWatcher */

/* 2682 */	NdrFcShort( 0xb ),	/* Flags:  must size, must free, in, */
/* 2684 */	NdrFcShort( 0x4 ),	/* x86 Stack size/offset = 4 */
/* 2686 */	NdrFcShort( 0x506 ),	/* Type Offset=1286 */

	/* Return value */

/* 2688 */	NdrFcShort( 0x70 ),	/* Flags:  out, return, base type, */
/* 2690 */	NdrFcShort( 0x8 ),	/* x86 Stack size/offset = 8 */
/* 2692 */	0x8,		/* FC_LONG */
			0x0,		/* 0 */

	/* Procedure SetLocalPresenceInfo */

/* 2694 */	0x33,		/* FC_AUTO_HANDLE */
			0x6c,		/* Old Flags:  object, Oi2 */
/* 2696 */	NdrFcLong( 0x0 ),	/* 0 */
/* 2700 */	NdrFcShort( 0x10 ),	/* 16 */
/* 2702 */	NdrFcShort( 0x10 ),	/* x86 Stack size/offset = 16 */
/* 2704 */	NdrFcShort( 0x6 ),	/* 6 */
/* 2706 */	NdrFcShort( 0x8 ),	/* 8 */
/* 2708 */	0x46,		/* Oi2 Flags:  clt must size, has return, has ext, */
			0x3,		/* 3 */
/* 2710 */	0x8,		/* 8 */
			0x5,		/* Ext Flags:  new corr desc, srv corr check, */
/* 2712 */	NdrFcShort( 0x0 ),	/* 0 */
/* 2714 */	NdrFcShort( 0x1 ),	/* 1 */
/* 2716 */	NdrFcShort( 0x0 ),	/* 0 */

	/* Parameter enStatus */

/* 2718 */	NdrFcShort( 0x48 ),	/* Flags:  in, base type, */
/* 2720 */	NdrFcShort( 0x4 ),	/* x86 Stack size/offset = 4 */
/* 2722 */	0xd,		/* FC_ENUM16 */
			0x0,		/* 0 */

	/* Parameter bstrNotes */

/* 2724 */	NdrFcShort( 0x8b ),	/* Flags:  must size, must free, in, by val, */
/* 2726 */	NdrFcShort( 0x8 ),	/* x86 Stack size/offset = 8 */
/* 2728 */	NdrFcShort( 0x20 ),	/* Type Offset=32 */

	/* Return value */

/* 2730 */	NdrFcShort( 0x70 ),	/* Flags:  out, return, base type, */
/* 2732 */	NdrFcShort( 0xc ),	/* x86 Stack size/offset = 12 */
/* 2734 */	0x8,		/* FC_LONG */
			0x0,		/* 0 */

	/* Procedure get_OfferWatcherMode */

/* 2736 */	0x33,		/* FC_AUTO_HANDLE */
			0x6c,		/* Old Flags:  object, Oi2 */
/* 2738 */	NdrFcLong( 0x0 ),	/* 0 */
/* 2742 */	NdrFcShort( 0x11 ),	/* 17 */
/* 2744 */	NdrFcShort( 0xc ),	/* x86 Stack size/offset = 12 */
/* 2746 */	NdrFcShort( 0x0 ),	/* 0 */
/* 2748 */	NdrFcShort( 0x22 ),	/* 34 */
/* 2750 */	0x44,		/* Oi2 Flags:  has return, has ext, */
			0x2,		/* 2 */
/* 2752 */	0x8,		/* 8 */
			0x1,		/* Ext Flags:  new corr desc, */
/* 2754 */	NdrFcShort( 0x0 ),	/* 0 */
/* 2756 */	NdrFcShort( 0x0 ),	/* 0 */
/* 2758 */	NdrFcShort( 0x0 ),	/* 0 */

	/* Parameter penMode */

/* 2760 */	NdrFcShort( 0x2010 ),	/* Flags:  out, srv alloc size=8 */
/* 2762 */	NdrFcShort( 0x4 ),	/* x86 Stack size/offset = 4 */
/* 2764 */	NdrFcShort( 0x52 ),	/* Type Offset=82 */

	/* Return value */

/* 2766 */	NdrFcShort( 0x70 ),	/* Flags:  out, return, base type, */
/* 2768 */	NdrFcShort( 0x8 ),	/* x86 Stack size/offset = 8 */
/* 2770 */	0x8,		/* FC_LONG */
			0x0,		/* 0 */

	/* Procedure put_OfferWatcherMode */

/* 2772 */	0x33,		/* FC_AUTO_HANDLE */
			0x6c,		/* Old Flags:  object, Oi2 */
/* 2774 */	NdrFcLong( 0x0 ),	/* 0 */
/* 2778 */	NdrFcShort( 0x12 ),	/* 18 */
/* 2780 */	NdrFcShort( 0xc ),	/* x86 Stack size/offset = 12 */
/* 2782 */	NdrFcShort( 0x6 ),	/* 6 */
/* 2784 */	NdrFcShort( 0x8 ),	/* 8 */
/* 2786 */	0x44,		/* Oi2 Flags:  has return, has ext, */
			0x2,		/* 2 */
/* 2788 */	0x8,		/* 8 */
			0x1,		/* Ext Flags:  new corr desc, */
/* 2790 */	NdrFcShort( 0x0 ),	/* 0 */
/* 2792 */	NdrFcShort( 0x0 ),	/* 0 */
/* 2794 */	NdrFcShort( 0x0 ),	/* 0 */

	/* Parameter enMode */

/* 2796 */	NdrFcShort( 0x48 ),	/* Flags:  in, base type, */
/* 2798 */	NdrFcShort( 0x4 ),	/* x86 Stack size/offset = 4 */
/* 2800 */	0xd,		/* FC_ENUM16 */
			0x0,		/* 0 */

	/* Return value */

/* 2802 */	NdrFcShort( 0x70 ),	/* Flags:  out, return, base type, */
/* 2804 */	NdrFcShort( 0x8 ),	/* x86 Stack size/offset = 8 */
/* 2806 */	0x8,		/* FC_LONG */
			0x0,		/* 0 */

	/* Procedure get_PrivacyMode */

/* 2808 */	0x33,		/* FC_AUTO_HANDLE */
			0x6c,		/* Old Flags:  object, Oi2 */
/* 2810 */	NdrFcLong( 0x0 ),	/* 0 */
/* 2814 */	NdrFcShort( 0x13 ),	/* 19 */
/* 2816 */	NdrFcShort( 0xc ),	/* x86 Stack size/offset = 12 */
/* 2818 */	NdrFcShort( 0x0 ),	/* 0 */
/* 2820 */	NdrFcShort( 0x22 ),	/* 34 */
/* 2822 */	0x44,		/* Oi2 Flags:  has return, has ext, */
			0x2,		/* 2 */
/* 2824 */	0x8,		/* 8 */
			0x1,		/* Ext Flags:  new corr desc, */
/* 2826 */	NdrFcShort( 0x0 ),	/* 0 */
/* 2828 */	NdrFcShort( 0x0 ),	/* 0 */
/* 2830 */	NdrFcShort( 0x0 ),	/* 0 */

	/* Parameter penMode */

/* 2832 */	NdrFcShort( 0x2010 ),	/* Flags:  out, srv alloc size=8 */
/* 2834 */	NdrFcShort( 0x4 ),	/* x86 Stack size/offset = 4 */
/* 2836 */	NdrFcShort( 0x52 ),	/* Type Offset=82 */

	/* Return value */

/* 2838 */	NdrFcShort( 0x70 ),	/* Flags:  out, return, base type, */
/* 2840 */	NdrFcShort( 0x8 ),	/* x86 Stack size/offset = 8 */
/* 2842 */	0x8,		/* FC_LONG */
			0x0,		/* 0 */

	/* Procedure put_PrivacyMode */

/* 2844 */	0x33,		/* FC_AUTO_HANDLE */
			0x6c,		/* Old Flags:  object, Oi2 */
/* 2846 */	NdrFcLong( 0x0 ),	/* 0 */
/* 2850 */	NdrFcShort( 0x14 ),	/* 20 */
/* 2852 */	NdrFcShort( 0xc ),	/* x86 Stack size/offset = 12 */
/* 2854 */	NdrFcShort( 0x6 ),	/* 6 */
/* 2856 */	NdrFcShort( 0x8 ),	/* 8 */
/* 2858 */	0x44,		/* Oi2 Flags:  has return, has ext, */
			0x2,		/* 2 */
/* 2860 */	0x8,		/* 8 */
			0x1,		/* Ext Flags:  new corr desc, */
/* 2862 */	NdrFcShort( 0x0 ),	/* 0 */
/* 2864 */	NdrFcShort( 0x0 ),	/* 0 */
/* 2866 */	NdrFcShort( 0x0 ),	/* 0 */

	/* Parameter enMode */

/* 2868 */	NdrFcShort( 0x48 ),	/* Flags:  in, base type, */
/* 2870 */	NdrFcShort( 0x4 ),	/* x86 Stack size/offset = 4 */
/* 2872 */	0xd,		/* FC_ENUM16 */
			0x0,		/* 0 */

	/* Return value */

/* 2874 */	NdrFcShort( 0x70 ),	/* Flags:  out, return, base type, */
/* 2876 */	NdrFcShort( 0x8 ),	/* x86 Stack size/offset = 8 */
/* 2878 */	0x8,		/* FC_LONG */
			0x0,		/* 0 */

	/* Procedure EnablePresenceEx */

/* 2880 */	0x33,		/* FC_AUTO_HANDLE */
			0x6c,		/* Old Flags:  object, Oi2 */
/* 2882 */	NdrFcLong( 0x0 ),	/* 0 */
/* 2886 */	NdrFcShort( 0x15 ),	/* 21 */
/* 2888 */	NdrFcShort( 0x20 ),	/* x86 Stack size/offset = 32 */
/* 2890 */	NdrFcShort( 0x8 ),	/* 8 */
/* 2892 */	NdrFcShort( 0x8 ),	/* 8 */
/* 2894 */	0x46,		/* Oi2 Flags:  clt must size, has return, has ext, */
			0x4,		/* 4 */
/* 2896 */	0x8,		/* 8 */
			0x5,		/* Ext Flags:  new corr desc, srv corr check, */
/* 2898 */	NdrFcShort( 0x0 ),	/* 0 */
/* 2900 */	NdrFcShort( 0x20 ),	/* 32 */
/* 2902 */	NdrFcShort( 0x0 ),	/* 0 */

	/* Parameter pProfile */

/* 2904 */	NdrFcShort( 0xb ),	/* Flags:  must size, must free, in, */
/* 2906 */	NdrFcShort( 0x4 ),	/* x86 Stack size/offset = 4 */
/* 2908 */	NdrFcShort( 0x2a ),	/* Type Offset=42 */

	/* Parameter varStorage */

/* 2910 */	NdrFcShort( 0x8b ),	/* Flags:  must size, must free, in, by val, */
/* 2912 */	NdrFcShort( 0x8 ),	/* x86 Stack size/offset = 8 */
/* 2914 */	NdrFcShort( 0x4a0 ),	/* Type Offset=1184 */

	/* Parameter lFlags */

/* 2916 */	NdrFcShort( 0x48 ),	/* Flags:  in, base type, */
/* 2918 */	NdrFcShort( 0x18 ),	/* x86 Stack size/offset = 24 */
/* 2920 */	0x8,		/* FC_LONG */
			0x0,		/* 0 */

	/* Return value */

/* 2922 */	NdrFcShort( 0x70 ),	/* Flags:  out, return, base type, */
/* 2924 */	NdrFcShort( 0x1c ),	/* x86 Stack size/offset = 28 */
/* 2926 */	0x8,		/* FC_LONG */
			0x0,		/* 0 */

	/* Procedure DisablePresence */

/* 2928 */	0x33,		/* FC_AUTO_HANDLE */
			0x6c,		/* Old Flags:  object, Oi2 */
/* 2930 */	NdrFcLong( 0x0 ),	/* 0 */
/* 2934 */	NdrFcShort( 0x16 ),	/* 22 */
/* 2936 */	NdrFcShort( 0x8 ),	/* x86 Stack size/offset = 8 */
/* 2938 */	NdrFcShort( 0x0 ),	/* 0 */
/* 2940 */	NdrFcShort( 0x8 ),	/* 8 */
/* 2942 */	0x44,		/* Oi2 Flags:  has return, has ext, */
			0x1,		/* 1 */
/* 2944 */	0x8,		/* 8 */
			0x1,		/* Ext Flags:  new corr desc, */
/* 2946 */	NdrFcShort( 0x0 ),	/* 0 */
/* 2948 */	NdrFcShort( 0x0 ),	/* 0 */
/* 2950 */	NdrFcShort( 0x0 ),	/* 0 */

	/* Return value */

/* 2952 */	NdrFcShort( 0x70 ),	/* Flags:  out, return, base type, */
/* 2954 */	NdrFcShort( 0x4 ),	/* x86 Stack size/offset = 4 */
/* 2956 */	0x8,		/* FC_LONG */
			0x0,		/* 0 */

	/* Procedure AddGroup */

/* 2958 */	0x33,		/* FC_AUTO_HANDLE */
			0x6c,		/* Old Flags:  object, Oi2 */
/* 2960 */	NdrFcLong( 0x0 ),	/* 0 */
/* 2964 */	NdrFcShort( 0x17 ),	/* 23 */
/* 2966 */	NdrFcShort( 0x1c ),	/* x86 Stack size/offset = 28 */
/* 2968 */	NdrFcShort( 0x8 ),	/* 8 */
/* 2970 */	NdrFcShort( 0x8 ),	/* 8 */
/* 2972 */	0x47,		/* Oi2 Flags:  srv must size, clt must size, has return, has ext, */
			0x6,		/* 6 */
/* 2974 */	0x8,		/* 8 */
			0x5,		/* Ext Flags:  new corr desc, srv corr check, */
/* 2976 */	NdrFcShort( 0x0 ),	/* 0 */
/* 2978 */	NdrFcShort( 0x2 ),	/* 2 */
/* 2980 */	NdrFcShort( 0x0 ),	/* 0 */

	/* Parameter bstrGroupName */

/* 2982 */	NdrFcShort( 0x8b ),	/* Flags:  must size, must free, in, by val, */
/* 2984 */	NdrFcShort( 0x4 ),	/* x86 Stack size/offset = 4 */
/* 2986 */	NdrFcShort( 0x20 ),	/* Type Offset=32 */

	/* Parameter bstrData */

/* 2988 */	NdrFcShort( 0x8b ),	/* Flags:  must size, must free, in, by val, */
/* 2990 */	NdrFcShort( 0x8 ),	/* x86 Stack size/offset = 8 */
/* 2992 */	NdrFcShort( 0x20 ),	/* Type Offset=32 */

	/* Parameter pProfile */

/* 2994 */	NdrFcShort( 0xb ),	/* Flags:  must size, must free, in, */
/* 2996 */	NdrFcShort( 0xc ),	/* x86 Stack size/offset = 12 */
/* 2998 */	NdrFcShort( 0x2a ),	/* Type Offset=42 */

	/* Parameter lFlags */

/* 3000 */	NdrFcShort( 0x48 ),	/* Flags:  in, base type, */
/* 3002 */	NdrFcShort( 0x10 ),	/* x86 Stack size/offset = 16 */
/* 3004 */	0x8,		/* FC_LONG */
			0x0,		/* 0 */

	/* Parameter ppGroup */

/* 3006 */	NdrFcShort( 0x13 ),	/* Flags:  must size, must free, out, */
/* 3008 */	NdrFcShort( 0x14 ),	/* x86 Stack size/offset = 20 */
/* 3010 */	NdrFcShort( 0x518 ),	/* Type Offset=1304 */

	/* Return value */

/* 3012 */	NdrFcShort( 0x70 ),	/* Flags:  out, return, base type, */
/* 3014 */	NdrFcShort( 0x18 ),	/* x86 Stack size/offset = 24 */
/* 3016 */	0x8,		/* FC_LONG */
			0x0,		/* 0 */

	/* Procedure RemoveGroup */

/* 3018 */	0x33,		/* FC_AUTO_HANDLE */
			0x6c,		/* Old Flags:  object, Oi2 */
/* 3020 */	NdrFcLong( 0x0 ),	/* 0 */
/* 3024 */	NdrFcShort( 0x18 ),	/* 24 */
/* 3026 */	NdrFcShort( 0xc ),	/* x86 Stack size/offset = 12 */
/* 3028 */	NdrFcShort( 0x0 ),	/* 0 */
/* 3030 */	NdrFcShort( 0x8 ),	/* 8 */
/* 3032 */	0x46,		/* Oi2 Flags:  clt must size, has return, has ext, */
			0x2,		/* 2 */
/* 3034 */	0x8,		/* 8 */
			0x1,		/* Ext Flags:  new corr desc, */
/* 3036 */	NdrFcShort( 0x0 ),	/* 0 */
/* 3038 */	NdrFcShort( 0x0 ),	/* 0 */
/* 3040 */	NdrFcShort( 0x0 ),	/* 0 */

	/* Parameter pGroup */

/* 3042 */	NdrFcShort( 0xb ),	/* Flags:  must size, must free, in, */
/* 3044 */	NdrFcShort( 0x4 ),	/* x86 Stack size/offset = 4 */
/* 3046 */	NdrFcShort( 0x51c ),	/* Type Offset=1308 */

	/* Return value */

/* 3048 */	NdrFcShort( 0x70 ),	/* Flags:  out, return, base type, */
/* 3050 */	NdrFcShort( 0x8 ),	/* x86 Stack size/offset = 8 */
/* 3052 */	0x8,		/* FC_LONG */
			0x0,		/* 0 */

	/* Procedure EnumerateGroups */

/* 3054 */	0x33,		/* FC_AUTO_HANDLE */
			0x6c,		/* Old Flags:  object, Oi2 */
/* 3056 */	NdrFcLong( 0x0 ),	/* 0 */
/* 3060 */	NdrFcShort( 0x19 ),	/* 25 */
/* 3062 */	NdrFcShort( 0xc ),	/* x86 Stack size/offset = 12 */
/* 3064 */	NdrFcShort( 0x0 ),	/* 0 */
/* 3066 */	NdrFcShort( 0x8 ),	/* 8 */
/* 3068 */	0x45,		/* Oi2 Flags:  srv must size, has return, has ext, */
			0x2,		/* 2 */
/* 3070 */	0x8,		/* 8 */
			0x1,		/* Ext Flags:  new corr desc, */
/* 3072 */	NdrFcShort( 0x0 ),	/* 0 */
/* 3074 */	NdrFcShort( 0x0 ),	/* 0 */
/* 3076 */	NdrFcShort( 0x0 ),	/* 0 */

	/* Parameter ppEnum */

/* 3078 */	NdrFcShort( 0x13 ),	/* Flags:  must size, must free, out, */
/* 3080 */	NdrFcShort( 0x4 ),	/* x86 Stack size/offset = 4 */
/* 3082 */	NdrFcShort( 0x52e ),	/* Type Offset=1326 */

	/* Return value */

/* 3084 */	NdrFcShort( 0x70 ),	/* Flags:  out, return, base type, */
/* 3086 */	NdrFcShort( 0x8 ),	/* x86 Stack size/offset = 8 */
/* 3088 */	0x8,		/* FC_LONG */
			0x0,		/* 0 */

	/* Procedure get_Groups */

/* 3090 */	0x33,		/* FC_AUTO_HANDLE */
			0x6c,		/* Old Flags:  object, Oi2 */
/* 3092 */	NdrFcLong( 0x0 ),	/* 0 */
/* 3096 */	NdrFcShort( 0x1a ),	/* 26 */
/* 3098 */	NdrFcShort( 0xc ),	/* x86 Stack size/offset = 12 */
/* 3100 */	NdrFcShort( 0x0 ),	/* 0 */
/* 3102 */	NdrFcShort( 0x8 ),	/* 8 */
/* 3104 */	0x45,		/* Oi2 Flags:  srv must size, has return, has ext, */
			0x2,		/* 2 */
/* 3106 */	0x8,		/* 8 */
			0x1,		/* Ext Flags:  new corr desc, */
/* 3108 */	NdrFcShort( 0x0 ),	/* 0 */
/* 3110 */	NdrFcShort( 0x0 ),	/* 0 */
/* 3112 */	NdrFcShort( 0x0 ),	/* 0 */

	/* Parameter ppCollection */

/* 3114 */	NdrFcShort( 0x13 ),	/* Flags:  must size, must free, out, */
/* 3116 */	NdrFcShort( 0x4 ),	/* x86 Stack size/offset = 4 */
/* 3118 */	NdrFcShort( 0x544 ),	/* Type Offset=1348 */

	/* Return value */

/* 3120 */	NdrFcShort( 0x70 ),	/* Flags:  out, return, base type, */
/* 3122 */	NdrFcShort( 0x8 ),	/* x86 Stack size/offset = 8 */
/* 3124 */	0x8,		/* FC_LONG */
			0x0,		/* 0 */

	/* Procedure get_Group */

/* 3126 */	0x33,		/* FC_AUTO_HANDLE */
			0x6c,		/* Old Flags:  object, Oi2 */
/* 3128 */	NdrFcLong( 0x0 ),	/* 0 */
/* 3132 */	NdrFcShort( 0x1b ),	/* 27 */
/* 3134 */	NdrFcShort( 0x10 ),	/* x86 Stack size/offset = 16 */
/* 3136 */	NdrFcShort( 0x0 ),	/* 0 */
/* 3138 */	NdrFcShort( 0x8 ),	/* 8 */
/* 3140 */	0x47,		/* Oi2 Flags:  srv must size, clt must size, has return, has ext, */
			0x3,		/* 3 */
/* 3142 */	0x8,		/* 8 */
			0x5,		/* Ext Flags:  new corr desc, srv corr check, */
/* 3144 */	NdrFcShort( 0x0 ),	/* 0 */
/* 3146 */	NdrFcShort( 0x1 ),	/* 1 */
/* 3148 */	NdrFcShort( 0x0 ),	/* 0 */

	/* Parameter bstrGroupName */

/* 3150 */	NdrFcShort( 0x8b ),	/* Flags:  must size, must free, in, by val, */
/* 3152 */	NdrFcShort( 0x4 ),	/* x86 Stack size/offset = 4 */
/* 3154 */	NdrFcShort( 0x20 ),	/* Type Offset=32 */

	/* Parameter ppGroup */

/* 3156 */	NdrFcShort( 0x13 ),	/* Flags:  must size, must free, out, */
/* 3158 */	NdrFcShort( 0x8 ),	/* x86 Stack size/offset = 8 */
/* 3160 */	NdrFcShort( 0x518 ),	/* Type Offset=1304 */

	/* Return value */

/* 3162 */	NdrFcShort( 0x70 ),	/* Flags:  out, return, base type, */
/* 3164 */	NdrFcShort( 0xc ),	/* x86 Stack size/offset = 12 */
/* 3166 */	0x8,		/* FC_LONG */
			0x0,		/* 0 */

	/* Procedure AddWatcherEx */

/* 3168 */	0x33,		/* FC_AUTO_HANDLE */
			0x6c,		/* Old Flags:  object, Oi2 */
/* 3170 */	NdrFcLong( 0x0 ),	/* 0 */
/* 3174 */	NdrFcShort( 0x1c ),	/* 28 */
/* 3176 */	NdrFcShort( 0x2c ),	/* x86 Stack size/offset = 44 */
/* 3178 */	NdrFcShort( 0x1a ),	/* 26 */
/* 3180 */	NdrFcShort( 0x8 ),	/* 8 */
/* 3182 */	0x47,		/* Oi2 Flags:  srv must size, clt must size, has return, has ext, */
			0xa,		/* 10 */
/* 3184 */	0x8,		/* 8 */
			0x5,		/* Ext Flags:  new corr desc, srv corr check, */
/* 3186 */	NdrFcShort( 0x0 ),	/* 0 */
/* 3188 */	NdrFcShort( 0x3 ),	/* 3 */
/* 3190 */	NdrFcShort( 0x0 ),	/* 0 */

	/* Parameter bstrPresentityURI */

/* 3192 */	NdrFcShort( 0x8b ),	/* Flags:  must size, must free, in, by val, */
/* 3194 */	NdrFcShort( 0x4 ),	/* x86 Stack size/offset = 4 */
/* 3196 */	NdrFcShort( 0x20 ),	/* Type Offset=32 */

	/* Parameter bstrUserName */

/* 3198 */	NdrFcShort( 0x8b ),	/* Flags:  must size, must free, in, by val, */
/* 3200 */	NdrFcShort( 0x8 ),	/* x86 Stack size/offset = 8 */
/* 3202 */	NdrFcShort( 0x20 ),	/* Type Offset=32 */

	/* Parameter bstrData */

/* 3204 */	NdrFcShort( 0x8b ),	/* Flags:  must size, must free, in, by val, */
/* 3206 */	NdrFcShort( 0xc ),	/* x86 Stack size/offset = 12 */
/* 3208 */	NdrFcShort( 0x20 ),	/* Type Offset=32 */

	/* Parameter enState */

/* 3210 */	NdrFcShort( 0x48 ),	/* Flags:  in, base type, */
/* 3212 */	NdrFcShort( 0x10 ),	/* x86 Stack size/offset = 16 */
/* 3214 */	0xd,		/* FC_ENUM16 */
			0x0,		/* 0 */

	/* Parameter fPersistent */

/* 3216 */	NdrFcShort( 0x48 ),	/* Flags:  in, base type, */
/* 3218 */	NdrFcShort( 0x14 ),	/* x86 Stack size/offset = 20 */
/* 3220 */	0x6,		/* FC_SHORT */
			0x0,		/* 0 */

	/* Parameter enScope */

/* 3222 */	NdrFcShort( 0x48 ),	/* Flags:  in, base type, */
/* 3224 */	NdrFcShort( 0x18 ),	/* x86 Stack size/offset = 24 */
/* 3226 */	0xd,		/* FC_ENUM16 */
			0x0,		/* 0 */

	/* Parameter pProfile */

/* 3228 */	NdrFcShort( 0xb ),	/* Flags:  must size, must free, in, */
/* 3230 */	NdrFcShort( 0x1c ),	/* x86 Stack size/offset = 28 */
/* 3232 */	NdrFcShort( 0x2a ),	/* Type Offset=42 */

	/* Parameter lFlags */

/* 3234 */	NdrFcShort( 0x48 ),	/* Flags:  in, base type, */
/* 3236 */	NdrFcShort( 0x20 ),	/* x86 Stack size/offset = 32 */
/* 3238 */	0x8,		/* FC_LONG */
			0x0,		/* 0 */

	/* Parameter ppWatcher */

/* 3240 */	NdrFcShort( 0x13 ),	/* Flags:  must size, must free, out, */
/* 3242 */	NdrFcShort( 0x24 ),	/* x86 Stack size/offset = 36 */
/* 3244 */	NdrFcShort( 0x55a ),	/* Type Offset=1370 */

	/* Return value */

/* 3246 */	NdrFcShort( 0x70 ),	/* Flags:  out, return, base type, */
/* 3248 */	NdrFcShort( 0x28 ),	/* x86 Stack size/offset = 40 */
/* 3250 */	0x8,		/* FC_LONG */
			0x0,		/* 0 */

	/* Procedure get_WatcherEx */

/* 3252 */	0x33,		/* FC_AUTO_HANDLE */
			0x6c,		/* Old Flags:  object, Oi2 */
/* 3254 */	NdrFcLong( 0x0 ),	/* 0 */
/* 3258 */	NdrFcShort( 0x1d ),	/* 29 */
/* 3260 */	NdrFcShort( 0x14 ),	/* x86 Stack size/offset = 20 */
/* 3262 */	NdrFcShort( 0x6 ),	/* 6 */
/* 3264 */	NdrFcShort( 0x8 ),	/* 8 */
/* 3266 */	0x47,		/* Oi2 Flags:  srv must size, clt must size, has return, has ext, */
			0x4,		/* 4 */
/* 3268 */	0x8,		/* 8 */
			0x5,		/* Ext Flags:  new corr desc, srv corr check, */
/* 3270 */	NdrFcShort( 0x0 ),	/* 0 */
/* 3272 */	NdrFcShort( 0x1 ),	/* 1 */
/* 3274 */	NdrFcShort( 0x0 ),	/* 0 */

	/* Parameter enMode */

/* 3276 */	NdrFcShort( 0x48 ),	/* Flags:  in, base type, */
/* 3278 */	NdrFcShort( 0x4 ),	/* x86 Stack size/offset = 4 */
/* 3280 */	0xd,		/* FC_ENUM16 */
			0x0,		/* 0 */

	/* Parameter bstrPresentityURI */

/* 3282 */	NdrFcShort( 0x8b ),	/* Flags:  must size, must free, in, by val, */
/* 3284 */	NdrFcShort( 0x8 ),	/* x86 Stack size/offset = 8 */
/* 3286 */	NdrFcShort( 0x20 ),	/* Type Offset=32 */

	/* Parameter ppWatcher */

/* 3288 */	NdrFcShort( 0x13 ),	/* Flags:  must size, must free, out, */
/* 3290 */	NdrFcShort( 0xc ),	/* x86 Stack size/offset = 12 */
/* 3292 */	NdrFcShort( 0x55a ),	/* Type Offset=1370 */

	/* Return value */

/* 3294 */	NdrFcShort( 0x70 ),	/* Flags:  out, return, base type, */
/* 3296 */	NdrFcShort( 0x10 ),	/* x86 Stack size/offset = 16 */
/* 3298 */	0x8,		/* FC_LONG */
			0x0,		/* 0 */

	/* Procedure put_PresenceProperty */

/* 3300 */	0x33,		/* FC_AUTO_HANDLE */
			0x6c,		/* Old Flags:  object, Oi2 */
/* 3302 */	NdrFcLong( 0x0 ),	/* 0 */
/* 3306 */	NdrFcShort( 0x1e ),	/* 30 */
/* 3308 */	NdrFcShort( 0x10 ),	/* x86 Stack size/offset = 16 */
/* 3310 */	NdrFcShort( 0x6 ),	/* 6 */
/* 3312 */	NdrFcShort( 0x8 ),	/* 8 */
/* 3314 */	0x46,		/* Oi2 Flags:  clt must size, has return, has ext, */
			0x3,		/* 3 */
/* 3316 */	0x8,		/* 8 */
			0x5,		/* Ext Flags:  new corr desc, srv corr check, */
/* 3318 */	NdrFcShort( 0x0 ),	/* 0 */
/* 3320 */	NdrFcShort( 0x1 ),	/* 1 */
/* 3322 */	NdrFcShort( 0x0 ),	/* 0 */

	/* Parameter enProperty */

/* 3324 */	NdrFcShort( 0x48 ),	/* Flags:  in, base type, */
/* 3326 */	NdrFcShort( 0x4 ),	/* x86 Stack size/offset = 4 */
/* 3328 */	0xd,		/* FC_ENUM16 */
			0x0,		/* 0 */

	/* Parameter bstrProperty */

/* 3330 */	NdrFcShort( 0x8b ),	/* Flags:  must size, must free, in, by val, */
/* 3332 */	NdrFcShort( 0x8 ),	/* x86 Stack size/offset = 8 */
/* 3334 */	NdrFcShort( 0x20 ),	/* Type Offset=32 */

	/* Return value */

/* 3336 */	NdrFcShort( 0x70 ),	/* Flags:  out, return, base type, */
/* 3338 */	NdrFcShort( 0xc ),	/* x86 Stack size/offset = 12 */
/* 3340 */	0x8,		/* FC_LONG */
			0x0,		/* 0 */

	/* Procedure get_PresenceProperty */

/* 3342 */	0x33,		/* FC_AUTO_HANDLE */
			0x6c,		/* Old Flags:  object, Oi2 */
/* 3344 */	NdrFcLong( 0x0 ),	/* 0 */
/* 3348 */	NdrFcShort( 0x1f ),	/* 31 */
/* 3350 */	NdrFcShort( 0x10 ),	/* x86 Stack size/offset = 16 */
/* 3352 */	NdrFcShort( 0x6 ),	/* 6 */
/* 3354 */	NdrFcShort( 0x8 ),	/* 8 */
/* 3356 */	0x45,		/* Oi2 Flags:  srv must size, has return, has ext, */
			0x3,		/* 3 */
/* 3358 */	0x8,		/* 8 */
			0x3,		/* Ext Flags:  new corr desc, clt corr check, */
/* 3360 */	NdrFcShort( 0x1 ),	/* 1 */
/* 3362 */	NdrFcShort( 0x0 ),	/* 0 */
/* 3364 */	NdrFcShort( 0x0 ),	/* 0 */

	/* Parameter enProperty */

/* 3366 */	NdrFcShort( 0x48 ),	/* Flags:  in, base type, */
/* 3368 */	NdrFcShort( 0x4 ),	/* x86 Stack size/offset = 4 */
/* 3370 */	0xd,		/* FC_ENUM16 */
			0x0,		/* 0 */

	/* Parameter pbstrProperty */

/* 3372 */	NdrFcShort( 0x2113 ),	/* Flags:  must size, must free, out, simple ref, srv alloc size=8 */
/* 3374 */	NdrFcShort( 0x8 ),	/* x86 Stack size/offset = 8 */
/* 3376 */	NdrFcShort( 0x46a ),	/* Type Offset=1130 */

	/* Return value */

/* 3378 */	NdrFcShort( 0x70 ),	/* Flags:  out, return, base type, */
/* 3380 */	NdrFcShort( 0xc ),	/* x86 Stack size/offset = 12 */
/* 3382 */	0x8,		/* FC_LONG */
			0x0,		/* 0 */

	/* Procedure SetPresenceData */

/* 3384 */	0x33,		/* FC_AUTO_HANDLE */
			0x6c,		/* Old Flags:  object, Oi2 */
/* 3386 */	NdrFcLong( 0x0 ),	/* 0 */
/* 3390 */	NdrFcShort( 0x20 ),	/* 32 */
/* 3392 */	NdrFcShort( 0x10 ),	/* x86 Stack size/offset = 16 */
/* 3394 */	NdrFcShort( 0x0 ),	/* 0 */
/* 3396 */	NdrFcShort( 0x8 ),	/* 8 */
/* 3398 */	0x46,		/* Oi2 Flags:  clt must size, has return, has ext, */
			0x3,		/* 3 */
/* 3400 */	0x8,		/* 8 */
			0x5,		/* Ext Flags:  new corr desc, srv corr check, */
/* 3402 */	NdrFcShort( 0x0 ),	/* 0 */
/* 3404 */	NdrFcShort( 0x2 ),	/* 2 */
/* 3406 */	NdrFcShort( 0x0 ),	/* 0 */

	/* Parameter bstrNamespace */

/* 3408 */	NdrFcShort( 0x8b ),	/* Flags:  must size, must free, in, by val, */
/* 3410 */	NdrFcShort( 0x4 ),	/* x86 Stack size/offset = 4 */
/* 3412 */	NdrFcShort( 0x20 ),	/* Type Offset=32 */

	/* Parameter bstrData */

/* 3414 */	NdrFcShort( 0x8b ),	/* Flags:  must size, must free, in, by val, */
/* 3416 */	NdrFcShort( 0x8 ),	/* x86 Stack size/offset = 8 */
/* 3418 */	NdrFcShort( 0x20 ),	/* Type Offset=32 */

	/* Return value */

/* 3420 */	NdrFcShort( 0x70 ),	/* Flags:  out, return, base type, */
/* 3422 */	NdrFcShort( 0xc ),	/* x86 Stack size/offset = 12 */
/* 3424 */	0x8,		/* FC_LONG */
			0x0,		/* 0 */

	/* Procedure GetPresenceData */

/* 3426 */	0x33,		/* FC_AUTO_HANDLE */
			0x6c,		/* Old Flags:  object, Oi2 */
/* 3428 */	NdrFcLong( 0x0 ),	/* 0 */
/* 3432 */	NdrFcShort( 0x21 ),	/* 33 */
/* 3434 */	NdrFcShort( 0x10 ),	/* x86 Stack size/offset = 16 */
/* 3436 */	NdrFcShort( 0x0 ),	/* 0 */
/* 3438 */	NdrFcShort( 0x8 ),	/* 8 */
/* 3440 */	0x45,		/* Oi2 Flags:  srv must size, has return, has ext, */
			0x3,		/* 3 */
/* 3442 */	0x8,		/* 8 */
			0x3,		/* Ext Flags:  new corr desc, clt corr check, */
/* 3444 */	NdrFcShort( 0x2 ),	/* 2 */
/* 3446 */	NdrFcShort( 0x0 ),	/* 0 */
/* 3448 */	NdrFcShort( 0x0 ),	/* 0 */

	/* Parameter pbstrNamespace */

/* 3450 */	NdrFcShort( 0x2113 ),	/* Flags:  must size, must free, out, simple ref, srv alloc size=8 */
/* 3452 */	NdrFcShort( 0x4 ),	/* x86 Stack size/offset = 4 */
/* 3454 */	NdrFcShort( 0x46a ),	/* Type Offset=1130 */

	/* Parameter pbstrData */

/* 3456 */	NdrFcShort( 0x2113 ),	/* Flags:  must size, must free, out, simple ref, srv alloc size=8 */
/* 3458 */	NdrFcShort( 0x8 ),	/* x86 Stack size/offset = 8 */
/* 3460 */	NdrFcShort( 0x46a ),	/* Type Offset=1130 */

	/* Return value */

/* 3462 */	NdrFcShort( 0x70 ),	/* Flags:  out, return, base type, */
/* 3464 */	NdrFcShort( 0xc ),	/* x86 Stack size/offset = 12 */
/* 3466 */	0x8,		/* FC_LONG */
			0x0,		/* 0 */

	/* Procedure GetLocalPresenceInfo */

/* 3468 */	0x33,		/* FC_AUTO_HANDLE */
			0x6c,		/* Old Flags:  object, Oi2 */
/* 3470 */	NdrFcLong( 0x0 ),	/* 0 */
/* 3474 */	NdrFcShort( 0x22 ),	/* 34 */
/* 3476 */	NdrFcShort( 0x10 ),	/* x86 Stack size/offset = 16 */
/* 3478 */	NdrFcShort( 0x0 ),	/* 0 */
/* 3480 */	NdrFcShort( 0x22 ),	/* 34 */
/* 3482 */	0x45,		/* Oi2 Flags:  srv must size, has return, has ext, */
			0x3,		/* 3 */
/* 3484 */	0x8,		/* 8 */
			0x3,		/* Ext Flags:  new corr desc, clt corr check, */
/* 3486 */	NdrFcShort( 0x1 ),	/* 1 */
/* 3488 */	NdrFcShort( 0x0 ),	/* 0 */
/* 3490 */	NdrFcShort( 0x0 ),	/* 0 */

	/* Parameter penStatus */

/* 3492 */	NdrFcShort( 0x2010 ),	/* Flags:  out, srv alloc size=8 */
/* 3494 */	NdrFcShort( 0x4 ),	/* x86 Stack size/offset = 4 */
/* 3496 */	NdrFcShort( 0x52 ),	/* Type Offset=82 */

	/* Parameter pbstrNotes */

/* 3498 */	NdrFcShort( 0x2113 ),	/* Flags:  must size, must free, out, simple ref, srv alloc size=8 */
/* 3500 */	NdrFcShort( 0x8 ),	/* x86 Stack size/offset = 8 */
/* 3502 */	NdrFcShort( 0x46a ),	/* Type Offset=1130 */

	/* Return value */

/* 3504 */	NdrFcShort( 0x70 ),	/* Flags:  out, return, base type, */
/* 3506 */	NdrFcShort( 0xc ),	/* x86 Stack size/offset = 12 */
/* 3508 */	0x8,		/* FC_LONG */
			0x0,		/* 0 */

	/* Procedure AddBuddyEx */

/* 3510 */	0x33,		/* FC_AUTO_HANDLE */
			0x6c,		/* Old Flags:  object, Oi2 */
/* 3512 */	NdrFcLong( 0x0 ),	/* 0 */
/* 3516 */	NdrFcShort( 0x23 ),	/* 35 */
/* 3518 */	NdrFcShort( 0x28 ),	/* x86 Stack size/offset = 40 */
/* 3520 */	NdrFcShort( 0x14 ),	/* 20 */
/* 3522 */	NdrFcShort( 0x8 ),	/* 8 */
/* 3524 */	0x47,		/* Oi2 Flags:  srv must size, clt must size, has return, has ext, */
			0x9,		/* 9 */
/* 3526 */	0x8,		/* 8 */
			0x5,		/* Ext Flags:  new corr desc, srv corr check, */
/* 3528 */	NdrFcShort( 0x0 ),	/* 0 */
/* 3530 */	NdrFcShort( 0x3 ),	/* 3 */
/* 3532 */	NdrFcShort( 0x0 ),	/* 0 */

	/* Parameter bstrPresentityURI */

/* 3534 */	NdrFcShort( 0x8b ),	/* Flags:  must size, must free, in, by val, */
/* 3536 */	NdrFcShort( 0x4 ),	/* x86 Stack size/offset = 4 */
/* 3538 */	NdrFcShort( 0x20 ),	/* Type Offset=32 */

	/* Parameter bstrUserName */

/* 3540 */	NdrFcShort( 0x8b ),	/* Flags:  must size, must free, in, by val, */
/* 3542 */	NdrFcShort( 0x8 ),	/* x86 Stack size/offset = 8 */
/* 3544 */	NdrFcShort( 0x20 ),	/* Type Offset=32 */

	/* Parameter bstrData */

/* 3546 */	NdrFcShort( 0x8b ),	/* Flags:  must size, must free, in, by val, */
/* 3548 */	NdrFcShort( 0xc ),	/* x86 Stack size/offset = 12 */
/* 3550 */	NdrFcShort( 0x20 ),	/* Type Offset=32 */

	/* Parameter fPersistent */

/* 3552 */	NdrFcShort( 0x48 ),	/* Flags:  in, base type, */
/* 3554 */	NdrFcShort( 0x10 ),	/* x86 Stack size/offset = 16 */
/* 3556 */	0x6,		/* FC_SHORT */
			0x0,		/* 0 */

	/* Parameter enSubscriptionType */

/* 3558 */	NdrFcShort( 0x48 ),	/* Flags:  in, base type, */
/* 3560 */	NdrFcShort( 0x14 ),	/* x86 Stack size/offset = 20 */
/* 3562 */	0xd,		/* FC_ENUM16 */
			0x0,		/* 0 */

	/* Parameter pProfile */

/* 3564 */	NdrFcShort( 0xb ),	/* Flags:  must size, must free, in, */
/* 3566 */	NdrFcShort( 0x18 ),	/* x86 Stack size/offset = 24 */
/* 3568 */	NdrFcShort( 0x2a ),	/* Type Offset=42 */

	/* Parameter lFlags */

/* 3570 */	NdrFcShort( 0x48 ),	/* Flags:  in, base type, */
/* 3572 */	NdrFcShort( 0x1c ),	/* x86 Stack size/offset = 28 */
/* 3574 */	0x8,		/* FC_LONG */
			0x0,		/* 0 */

	/* Parameter ppBuddy */

/* 3576 */	NdrFcShort( 0x13 ),	/* Flags:  must size, must free, out, */
/* 3578 */	NdrFcShort( 0x20 ),	/* x86 Stack size/offset = 32 */
/* 3580 */	NdrFcShort( 0x570 ),	/* Type Offset=1392 */

	/* Return value */

/* 3582 */	NdrFcShort( 0x70 ),	/* Flags:  out, return, base type, */
/* 3584 */	NdrFcShort( 0x24 ),	/* x86 Stack size/offset = 36 */
/* 3586 */	0x8,		/* FC_LONG */
			0x0,		/* 0 */

	/* Procedure CreateProfile */

/* 3588 */	0x33,		/* FC_AUTO_HANDLE */
			0x6c,		/* Old Flags:  object, Oi2 */
/* 3590 */	NdrFcLong( 0x0 ),	/* 0 */
/* 3594 */	NdrFcShort( 0x3 ),	/* 3 */
/* 3596 */	NdrFcShort( 0x10 ),	/* x86 Stack size/offset = 16 */
/* 3598 */	NdrFcShort( 0x0 ),	/* 0 */
/* 3600 */	NdrFcShort( 0x8 ),	/* 8 */
/* 3602 */	0x47,		/* Oi2 Flags:  srv must size, clt must size, has return, has ext, */
			0x3,		/* 3 */
/* 3604 */	0x8,		/* 8 */
			0x5,		/* Ext Flags:  new corr desc, srv corr check, */
/* 3606 */	NdrFcShort( 0x0 ),	/* 0 */
/* 3608 */	NdrFcShort( 0x1 ),	/* 1 */
/* 3610 */	NdrFcShort( 0x0 ),	/* 0 */

	/* Parameter bstrProfileXML */

/* 3612 */	NdrFcShort( 0x8b ),	/* Flags:  must size, must free, in, by val, */
/* 3614 */	NdrFcShort( 0x4 ),	/* x86 Stack size/offset = 4 */
/* 3616 */	NdrFcShort( 0x20 ),	/* Type Offset=32 */

	/* Parameter ppProfile */

/* 3618 */	NdrFcShort( 0x13 ),	/* Flags:  must size, must free, out, */
/* 3620 */	NdrFcShort( 0x8 ),	/* x86 Stack size/offset = 8 */
/* 3622 */	NdrFcShort( 0x586 ),	/* Type Offset=1414 */

	/* Return value */

/* 3624 */	NdrFcShort( 0x70 ),	/* Flags:  out, return, base type, */
/* 3626 */	NdrFcShort( 0xc ),	/* x86 Stack size/offset = 12 */
/* 3628 */	0x8,		/* FC_LONG */
			0x0,		/* 0 */

	/* Procedure EnableProfile */

/* 3630 */	0x33,		/* FC_AUTO_HANDLE */
			0x6c,		/* Old Flags:  object, Oi2 */
/* 3632 */	NdrFcLong( 0x0 ),	/* 0 */
/* 3636 */	NdrFcShort( 0x4 ),	/* 4 */
/* 3638 */	NdrFcShort( 0x10 ),	/* x86 Stack size/offset = 16 */
/* 3640 */	NdrFcShort( 0x8 ),	/* 8 */
/* 3642 */	NdrFcShort( 0x8 ),	/* 8 */
/* 3644 */	0x46,		/* Oi2 Flags:  clt must size, has return, has ext, */
			0x3,		/* 3 */
/* 3646 */	0x8,		/* 8 */
			0x1,		/* Ext Flags:  new corr desc, */
/* 3648 */	NdrFcShort( 0x0 ),	/* 0 */
/* 3650 */	NdrFcShort( 0x0 ),	/* 0 */
/* 3652 */	NdrFcShort( 0x0 ),	/* 0 */

	/* Parameter pProfile */

/* 3654 */	NdrFcShort( 0xb ),	/* Flags:  must size, must free, in, */
/* 3656 */	NdrFcShort( 0x4 ),	/* x86 Stack size/offset = 4 */
/* 3658 */	NdrFcShort( 0x2a ),	/* Type Offset=42 */

	/* Parameter lRegisterFlags */

/* 3660 */	NdrFcShort( 0x48 ),	/* Flags:  in, base type, */
/* 3662 */	NdrFcShort( 0x8 ),	/* x86 Stack size/offset = 8 */
/* 3664 */	0x8,		/* FC_LONG */
			0x0,		/* 0 */

	/* Return value */

/* 3666 */	NdrFcShort( 0x70 ),	/* Flags:  out, return, base type, */
/* 3668 */	NdrFcShort( 0xc ),	/* x86 Stack size/offset = 12 */
/* 3670 */	0x8,		/* FC_LONG */
			0x0,		/* 0 */

	/* Procedure DisableProfile */

/* 3672 */	0x33,		/* FC_AUTO_HANDLE */
			0x6c,		/* Old Flags:  object, Oi2 */
/* 3674 */	NdrFcLong( 0x0 ),	/* 0 */
/* 3678 */	NdrFcShort( 0x5 ),	/* 5 */
/* 3680 */	NdrFcShort( 0xc ),	/* x86 Stack size/offset = 12 */
/* 3682 */	NdrFcShort( 0x0 ),	/* 0 */
/* 3684 */	NdrFcShort( 0x8 ),	/* 8 */
/* 3686 */	0x46,		/* Oi2 Flags:  clt must size, has return, has ext, */
			0x2,		/* 2 */
/* 3688 */	0x8,		/* 8 */
			0x1,		/* Ext Flags:  new corr desc, */
/* 3690 */	NdrFcShort( 0x0 ),	/* 0 */
/* 3692 */	NdrFcShort( 0x0 ),	/* 0 */
/* 3694 */	NdrFcShort( 0x0 ),	/* 0 */

	/* Parameter pProfile */

/* 3696 */	NdrFcShort( 0xb ),	/* Flags:  must size, must free, in, */
/* 3698 */	NdrFcShort( 0x4 ),	/* x86 Stack size/offset = 4 */
/* 3700 */	NdrFcShort( 0x2a ),	/* Type Offset=42 */

	/* Return value */

/* 3702 */	NdrFcShort( 0x70 ),	/* Flags:  out, return, base type, */
/* 3704 */	NdrFcShort( 0x8 ),	/* x86 Stack size/offset = 8 */
/* 3706 */	0x8,		/* FC_LONG */
			0x0,		/* 0 */

	/* Procedure Clone */


	/* Procedure EnumerateProfiles */

/* 3708 */	0x33,		/* FC_AUTO_HANDLE */
			0x6c,		/* Old Flags:  object, Oi2 */
/* 3710 */	NdrFcLong( 0x0 ),	/* 0 */
/* 3714 */	NdrFcShort( 0x6 ),	/* 6 */
/* 3716 */	NdrFcShort( 0xc ),	/* x86 Stack size/offset = 12 */
/* 3718 */	NdrFcShort( 0x0 ),	/* 0 */
/* 3720 */	NdrFcShort( 0x8 ),	/* 8 */
/* 3722 */	0x45,		/* Oi2 Flags:  srv must size, has return, has ext, */
			0x2,		/* 2 */
/* 3724 */	0x8,		/* 8 */
			0x1,		/* Ext Flags:  new corr desc, */
/* 3726 */	NdrFcShort( 0x0 ),	/* 0 */
/* 3728 */	NdrFcShort( 0x0 ),	/* 0 */
/* 3730 */	NdrFcShort( 0x0 ),	/* 0 */

	/* Parameter ppEnum */


	/* Parameter ppEnum */

/* 3732 */	NdrFcShort( 0x13 ),	/* Flags:  must size, must free, out, */
/* 3734 */	NdrFcShort( 0x4 ),	/* x86 Stack size/offset = 4 */
/* 3736 */	NdrFcShort( 0x58a ),	/* Type Offset=1418 */

	/* Return value */


	/* Return value */

/* 3738 */	NdrFcShort( 0x70 ),	/* Flags:  out, return, base type, */
/* 3740 */	NdrFcShort( 0x8 ),	/* x86 Stack size/offset = 8 */
/* 3742 */	0x8,		/* FC_LONG */
			0x0,		/* 0 */

	/* Procedure GetProfile */

/* 3744 */	0x33,		/* FC_AUTO_HANDLE */
			0x6c,		/* Old Flags:  object, Oi2 */
/* 3746 */	NdrFcLong( 0x0 ),	/* 0 */
/* 3750 */	NdrFcShort( 0x8 ),	/* 8 */
/* 3752 */	NdrFcShort( 0x20 ),	/* x86 Stack size/offset = 32 */
/* 3754 */	NdrFcShort( 0x10 ),	/* 16 */
/* 3756 */	NdrFcShort( 0x8 ),	/* 8 */
/* 3758 */	0x46,		/* Oi2 Flags:  clt must size, has return, has ext, */
			0x7,		/* 7 */
/* 3760 */	0x8,		/* 8 */
			0x5,		/* Ext Flags:  new corr desc, srv corr check, */
/* 3762 */	NdrFcShort( 0x0 ),	/* 0 */
/* 3764 */	NdrFcShort( 0x4 ),	/* 4 */
/* 3766 */	NdrFcShort( 0x0 ),	/* 0 */

	/* Parameter bstrUserAccount */

/* 3768 */	NdrFcShort( 0x8b ),	/* Flags:  must size, must free, in, by val, */
/* 3770 */	NdrFcShort( 0x4 ),	/* x86 Stack size/offset = 4 */
/* 3772 */	NdrFcShort( 0x20 ),	/* Type Offset=32 */

	/* Parameter bstrUserPassword */

/* 3774 */	NdrFcShort( 0x8b ),	/* Flags:  must size, must free, in, by val, */
/* 3776 */	NdrFcShort( 0x8 ),	/* x86 Stack size/offset = 8 */
/* 3778 */	NdrFcShort( 0x20 ),	/* Type Offset=32 */

	/* Parameter bstrUserURI */

/* 3780 */	NdrFcShort( 0x8b ),	/* Flags:  must size, must free, in, by val, */
/* 3782 */	NdrFcShort( 0xc ),	/* x86 Stack size/offset = 12 */
/* 3784 */	NdrFcShort( 0x20 ),	/* Type Offset=32 */

	/* Parameter bstrServer */

/* 3786 */	NdrFcShort( 0x8b ),	/* Flags:  must size, must free, in, by val, */
/* 3788 */	NdrFcShort( 0x10 ),	/* x86 Stack size/offset = 16 */
/* 3790 */	NdrFcShort( 0x20 ),	/* Type Offset=32 */

	/* Parameter lTransport */

/* 3792 */	NdrFcShort( 0x48 ),	/* Flags:  in, base type, */
/* 3794 */	NdrFcShort( 0x14 ),	/* x86 Stack size/offset = 20 */
/* 3796 */	0x8,		/* FC_LONG */
			0x0,		/* 0 */

	/* Parameter lCookie */

/* 3798 */	NdrFcShort( 0x48 ),	/* Flags:  in, base type, */
/* 3800 */	NdrFcShort( 0x18 ),	/* x86 Stack size/offset = 24 */
/* 3802 */	0x8,		/* FC_LONG */
			0x0,		/* 0 */

	/* Return value */

/* 3804 */	NdrFcShort( 0x70 ),	/* Flags:  out, return, base type, */
/* 3806 */	NdrFcShort( 0x1c ),	/* x86 Stack size/offset = 28 */
/* 3808 */	0x8,		/* FC_LONG */
			0x0,		/* 0 */

	/* Procedure EnableProfileEx */

/* 3810 */	0x33,		/* FC_AUTO_HANDLE */
			0x6c,		/* Old Flags:  object, Oi2 */
/* 3812 */	NdrFcLong( 0x0 ),	/* 0 */
/* 3816 */	NdrFcShort( 0xa ),	/* 10 */
/* 3818 */	NdrFcShort( 0x14 ),	/* x86 Stack size/offset = 20 */
/* 3820 */	NdrFcShort( 0x10 ),	/* 16 */
/* 3822 */	NdrFcShort( 0x8 ),	/* 8 */
/* 3824 */	0x46,		/* Oi2 Flags:  clt must size, has return, has ext, */
			0x4,		/* 4 */
/* 3826 */	0x8,		/* 8 */
			0x1,		/* Ext Flags:  new corr desc, */
/* 3828 */	NdrFcShort( 0x0 ),	/* 0 */
/* 3830 */	NdrFcShort( 0x0 ),	/* 0 */
/* 3832 */	NdrFcShort( 0x0 ),	/* 0 */

	/* Parameter pProfile */

/* 3834 */	NdrFcShort( 0xb ),	/* Flags:  must size, must free, in, */
/* 3836 */	NdrFcShort( 0x4 ),	/* x86 Stack size/offset = 4 */
/* 3838 */	NdrFcShort( 0x2a ),	/* Type Offset=42 */

	/* Parameter lRegisterFlags */

/* 3840 */	NdrFcShort( 0x48 ),	/* Flags:  in, base type, */
/* 3842 */	NdrFcShort( 0x8 ),	/* x86 Stack size/offset = 8 */
/* 3844 */	0x8,		/* FC_LONG */
			0x0,		/* 0 */

	/* Parameter lRoamingFlags */

/* 3846 */	NdrFcShort( 0x48 ),	/* Flags:  in, base type, */
/* 3848 */	NdrFcShort( 0xc ),	/* x86 Stack size/offset = 12 */
/* 3850 */	0x8,		/* FC_LONG */
			0x0,		/* 0 */

	/* Return value */

/* 3852 */	NdrFcShort( 0x70 ),	/* Flags:  out, return, base type, */
/* 3854 */	NdrFcShort( 0x10 ),	/* x86 Stack size/offset = 16 */
/* 3856 */	0x8,		/* FC_LONG */
			0x0,		/* 0 */

	/* Procedure get_Name */


	/* Procedure get_PresentityURI */


	/* Procedure get_UserURI */


	/* Procedure get_Key */

/* 3858 */	0x33,		/* FC_AUTO_HANDLE */
			0x6c,		/* Old Flags:  object, Oi2 */
/* 3860 */	NdrFcLong( 0x0 ),	/* 0 */
/* 3864 */	NdrFcShort( 0x3 ),	/* 3 */
/* 3866 */	NdrFcShort( 0xc ),	/* x86 Stack size/offset = 12 */
/* 3868 */	NdrFcShort( 0x0 ),	/* 0 */
/* 3870 */	NdrFcShort( 0x8 ),	/* 8 */
/* 3872 */	0x45,		/* Oi2 Flags:  srv must size, has return, has ext, */
			0x2,		/* 2 */
/* 3874 */	0x8,		/* 8 */
			0x3,		/* Ext Flags:  new corr desc, clt corr check, */
/* 3876 */	NdrFcShort( 0x1 ),	/* 1 */
/* 3878 */	NdrFcShort( 0x0 ),	/* 0 */
/* 3880 */	NdrFcShort( 0x0 ),	/* 0 */

	/* Parameter pbstrGroupName */


	/* Parameter pbstrPresentityURI */


	/* Parameter pbstrUserURI */


	/* Parameter pbstrKey */

/* 3882 */	NdrFcShort( 0x2113 ),	/* Flags:  must size, must free, out, simple ref, srv alloc size=8 */
/* 3884 */	NdrFcShort( 0x4 ),	/* x86 Stack size/offset = 4 */
/* 3886 */	NdrFcShort( 0x46a ),	/* Type Offset=1130 */

	/* Return value */


	/* Return value */


	/* Return value */


	/* Return value */

/* 3888 */	NdrFcShort( 0x70 ),	/* Flags:  out, return, base type, */
/* 3890 */	NdrFcShort( 0x8 ),	/* x86 Stack size/offset = 8 */
/* 3892 */	0x8,		/* FC_LONG */
			0x0,		/* 0 */

	/* Procedure get_Notes */


	/* Procedure get_Name */


	/* Procedure get_Name */

/* 3894 */	0x33,		/* FC_AUTO_HANDLE */
			0x6c,		/* Old Flags:  object, Oi2 */
/* 3896 */	NdrFcLong( 0x0 ),	/* 0 */
/* 3900 */	NdrFcShort( 0x4 ),	/* 4 */
/* 3902 */	NdrFcShort( 0xc ),	/* x86 Stack size/offset = 12 */
/* 3904 */	NdrFcShort( 0x0 ),	/* 0 */
/* 3906 */	NdrFcShort( 0x8 ),	/* 8 */
/* 3908 */	0x45,		/* Oi2 Flags:  srv must size, has return, has ext, */
			0x2,		/* 2 */
/* 3910 */	0x8,		/* 8 */
			0x3,		/* Ext Flags:  new corr desc, clt corr check, */
/* 3912 */	NdrFcShort( 0x1 ),	/* 1 */
/* 3914 */	NdrFcShort( 0x0 ),	/* 0 */
/* 3916 */	NdrFcShort( 0x0 ),	/* 0 */

	/* Parameter pbstrNotes */


	/* Parameter pbstrName */


	/* Parameter pbstrName */

/* 3918 */	NdrFcShort( 0x2113 ),	/* Flags:  must size, must free, out, simple ref, srv alloc size=8 */
/* 3920 */	NdrFcShort( 0x4 ),	/* x86 Stack size/offset = 4 */
/* 3922 */	NdrFcShort( 0x46a ),	/* Type Offset=1130 */

	/* Return value */


	/* Return value */


	/* Return value */

/* 3924 */	NdrFcShort( 0x70 ),	/* Flags:  out, return, base type, */
/* 3926 */	NdrFcShort( 0x8 ),	/* x86 Stack size/offset = 8 */
/* 3928 */	0x8,		/* FC_LONG */
			0x0,		/* 0 */

	/* Procedure get_SearchTerms */


	/* Procedure get_Name */


	/* Procedure get_XML */

/* 3930 */	0x33,		/* FC_AUTO_HANDLE */
			0x6c,		/* Old Flags:  object, Oi2 */
/* 3932 */	NdrFcLong( 0x0 ),	/* 0 */
/* 3936 */	NdrFcShort( 0x5 ),	/* 5 */
/* 3938 */	NdrFcShort( 0xc ),	/* x86 Stack size/offset = 12 */
/* 3940 */	NdrFcShort( 0x0 ),	/* 0 */
/* 3942 */	NdrFcShort( 0x8 ),	/* 8 */
/* 3944 */	0x45,		/* Oi2 Flags:  srv must size, has return, has ext, */
			0x2,		/* 2 */
/* 3946 */	0x8,		/* 8 */
			0x3,		/* Ext Flags:  new corr desc, clt corr check, */
/* 3948 */	NdrFcShort( 0x1 ),	/* 1 */
/* 3950 */	NdrFcShort( 0x0 ),	/* 0 */
/* 3952 */	NdrFcShort( 0x0 ),	/* 0 */

	/* Parameter pbstrNames */


	/* Parameter pbstrName */


	/* Parameter pbstrXML */

/* 3954 */	NdrFcShort( 0x2113 ),	/* Flags:  must size, must free, out, simple ref, srv alloc size=8 */
/* 3956 */	NdrFcShort( 0x4 ),	/* x86 Stack size/offset = 4 */
/* 3958 */	NdrFcShort( 0x46a ),	/* Type Offset=1130 */

	/* Return value */


	/* Return value */


	/* Return value */

/* 3960 */	NdrFcShort( 0x70 ),	/* Flags:  out, return, base type, */
/* 3962 */	NdrFcShort( 0x8 ),	/* x86 Stack size/offset = 8 */
/* 3964 */	0x8,		/* FC_LONG */
			0x0,		/* 0 */

	/* Procedure get_ProviderName */

/* 3966 */	0x33,		/* FC_AUTO_HANDLE */
			0x6c,		/* Old Flags:  object, Oi2 */
/* 3968 */	NdrFcLong( 0x0 ),	/* 0 */
/* 3972 */	NdrFcShort( 0x6 ),	/* 6 */
/* 3974 */	NdrFcShort( 0xc ),	/* x86 Stack size/offset = 12 */
/* 3976 */	NdrFcShort( 0x0 ),	/* 0 */
/* 3978 */	NdrFcShort( 0x8 ),	/* 8 */
/* 3980 */	0x45,		/* Oi2 Flags:  srv must size, has return, has ext, */
			0x2,		/* 2 */
/* 3982 */	0x8,		/* 8 */
			0x3,		/* Ext Flags:  new corr desc, clt corr check, */
/* 3984 */	NdrFcShort( 0x1 ),	/* 1 */
/* 3986 */	NdrFcShort( 0x0 ),	/* 0 */
/* 3988 */	NdrFcShort( 0x0 ),	/* 0 */

	/* Parameter pbstrName */

/* 3990 */	NdrFcShort( 0x2113 ),	/* Flags:  must size, must free, out, simple ref, srv alloc size=8 */
/* 3992 */	NdrFcShort( 0x4 ),	/* x86 Stack size/offset = 4 */
/* 3994 */	NdrFcShort( 0x46a ),	/* Type Offset=1130 */

	/* Return value */

/* 3996 */	NdrFcShort( 0x70 ),	/* Flags:  out, return, base type, */
/* 3998 */	NdrFcShort( 0x8 ),	/* x86 Stack size/offset = 8 */
/* 4000 */	0x8,		/* FC_LONG */
			0x0,		/* 0 */

	/* Procedure get_ProviderURI */

/* 4002 */	0x33,		/* FC_AUTO_HANDLE */
			0x6c,		/* Old Flags:  object, Oi2 */
/* 4004 */	NdrFcLong( 0x0 ),	/* 0 */
/* 4008 */	NdrFcShort( 0x7 ),	/* 7 */
/* 4010 */	NdrFcShort( 0x10 ),	/* x86 Stack size/offset = 16 */
/* 4012 */	NdrFcShort( 0x6 ),	/* 6 */
/* 4014 */	NdrFcShort( 0x8 ),	/* 8 */
/* 4016 */	0x45,		/* Oi2 Flags:  srv must size, has return, has ext, */
			0x3,		/* 3 */
/* 4018 */	0x8,		/* 8 */
			0x3,		/* Ext Flags:  new corr desc, clt corr check, */
/* 4020 */	NdrFcShort( 0x1 ),	/* 1 */
/* 4022 */	NdrFcShort( 0x0 ),	/* 0 */
/* 4024 */	NdrFcShort( 0x0 ),	/* 0 */

	/* Parameter enURI */

/* 4026 */	NdrFcShort( 0x48 ),	/* Flags:  in, base type, */
/* 4028 */	NdrFcShort( 0x4 ),	/* x86 Stack size/offset = 4 */
/* 4030 */	0xd,		/* FC_ENUM16 */
			0x0,		/* 0 */

	/* Parameter pbstrURI */

/* 4032 */	NdrFcShort( 0x2113 ),	/* Flags:  must size, must free, out, simple ref, srv alloc size=8 */
/* 4034 */	NdrFcShort( 0x8 ),	/* x86 Stack size/offset = 8 */
/* 4036 */	NdrFcShort( 0x46a ),	/* Type Offset=1130 */

	/* Return value */

/* 4038 */	NdrFcShort( 0x70 ),	/* Flags:  out, return, base type, */
/* 4040 */	NdrFcShort( 0xc ),	/* x86 Stack size/offset = 12 */
/* 4042 */	0x8,		/* FC_LONG */
			0x0,		/* 0 */

	/* Procedure get_ReferredByURI */


	/* Procedure get_StatusText */


	/* Procedure get_StatusText */


	/* Procedure get_StatusText */


	/* Procedure get_DeviceID */


	/* Procedure get_ReferredByURI */


	/* Procedure get_ProviderData */

/* 4044 */	0x33,		/* FC_AUTO_HANDLE */
			0x6c,		/* Old Flags:  object, Oi2 */
/* 4046 */	NdrFcLong( 0x0 ),	/* 0 */
/* 4050 */	NdrFcShort( 0x8 ),	/* 8 */
/* 4052 */	NdrFcShort( 0xc ),	/* x86 Stack size/offset = 12 */
/* 4054 */	NdrFcShort( 0x0 ),	/* 0 */
/* 4056 */	NdrFcShort( 0x8 ),	/* 8 */
/* 4058 */	0x45,		/* Oi2 Flags:  srv must size, has return, has ext, */
			0x2,		/* 2 */
/* 4060 */	0x8,		/* 8 */
			0x3,		/* Ext Flags:  new corr desc, clt corr check, */
/* 4062 */	NdrFcShort( 0x1 ),	/* 1 */
/* 4064 */	NdrFcShort( 0x0 ),	/* 0 */
/* 4066 */	NdrFcShort( 0x0 ),	/* 0 */

	/* Parameter pbstrReferredByURI */


	/* Parameter pbstrStatusText */


	/* Parameter pbstrStatusText */


	/* Parameter pbstrStatusText */


	/* Parameter pbstrDeviceID */


	/* Parameter pbstrReferredByURI */


	/* Parameter pbstrData */

/* 4068 */	NdrFcShort( 0x2113 ),	/* Flags:  must size, must free, out, simple ref, srv alloc size=8 */
/* 4070 */	NdrFcShort( 0x4 ),	/* x86 Stack size/offset = 4 */
/* 4072 */	NdrFcShort( 0x46a ),	/* Type Offset=1130 */

	/* Return value */


	/* Return value */


	/* Return value */


	/* Return value */


	/* Return value */


	/* Return value */


	/* Return value */

/* 4074 */	NdrFcShort( 0x70 ),	/* Flags:  out, return, base type, */
/* 4076 */	NdrFcShort( 0x8 ),	/* x86 Stack size/offset = 8 */
/* 4078 */	0x8,		/* FC_LONG */
			0x0,		/* 0 */

	/* Procedure get_ReferToURI */


	/* Procedure get_SearchDomain */


	/* Procedure get_Data */


	/* Procedure get_Info */


	/* Procedure get_ClientName */

/* 4080 */	0x33,		/* FC_AUTO_HANDLE */
			0x6c,		/* Old Flags:  object, Oi2 */
/* 4082 */	NdrFcLong( 0x0 ),	/* 0 */
/* 4086 */	NdrFcShort( 0x9 ),	/* 9 */
/* 4088 */	NdrFcShort( 0xc ),	/* x86 Stack size/offset = 12 */
/* 4090 */	NdrFcShort( 0x0 ),	/* 0 */
/* 4092 */	NdrFcShort( 0x8 ),	/* 8 */
/* 4094 */	0x45,		/* Oi2 Flags:  srv must size, has return, has ext, */
			0x2,		/* 2 */
/* 4096 */	0x8,		/* 8 */
			0x3,		/* Ext Flags:  new corr desc, clt corr check, */
/* 4098 */	NdrFcShort( 0x1 ),	/* 1 */
/* 4100 */	NdrFcShort( 0x0 ),	/* 0 */
/* 4102 */	NdrFcShort( 0x0 ),	/* 0 */

	/* Parameter pbstrReferoURI */


	/* Parameter pbstrDomain */


	/* Parameter pbstrData */


	/* Parameter pbstrInfo */


	/* Parameter pbstrName */

/* 4104 */	NdrFcShort( 0x2113 ),	/* Flags:  must size, must free, out, simple ref, srv alloc size=8 */
/* 4106 */	NdrFcShort( 0x4 ),	/* x86 Stack size/offset = 4 */
/* 4108 */	NdrFcShort( 0x46a ),	/* Type Offset=1130 */

	/* Return value */


	/* Return value */


	/* Return value */


	/* Return value */


	/* Return value */

/* 4110 */	NdrFcShort( 0x70 ),	/* Flags:  out, return, base type, */
/* 4112 */	NdrFcShort( 0x8 ),	/* x86 Stack size/offset = 8 */
/* 4114 */	0x8,		/* FC_LONG */
			0x0,		/* 0 */

	/* Procedure get_ClientBanner */

/* 4116 */	0x33,		/* FC_AUTO_HANDLE */
			0x6c,		/* Old Flags:  object, Oi2 */
/* 4118 */	NdrFcLong( 0x0 ),	/* 0 */
/* 4122 */	NdrFcShort( 0xa ),	/* 10 */
/* 4124 */	NdrFcShort( 0xc ),	/* x86 Stack size/offset = 12 */
/* 4126 */	NdrFcShort( 0x0 ),	/* 0 */
/* 4128 */	NdrFcShort( 0x22 ),	/* 34 */
/* 4130 */	0x44,		/* Oi2 Flags:  has return, has ext, */
			0x2,		/* 2 */
/* 4132 */	0x8,		/* 8 */
			0x1,		/* Ext Flags:  new corr desc, */
/* 4134 */	NdrFcShort( 0x0 ),	/* 0 */
/* 4136 */	NdrFcShort( 0x0 ),	/* 0 */
/* 4138 */	NdrFcShort( 0x0 ),	/* 0 */

	/* Parameter pfBanner */

/* 4140 */	NdrFcShort( 0x2150 ),	/* Flags:  out, base type, simple ref, srv alloc size=8 */
/* 4142 */	NdrFcShort( 0x4 ),	/* x86 Stack size/offset = 4 */
/* 4144 */	0x6,		/* FC_SHORT */
			0x0,		/* 0 */

	/* Return value */

/* 4146 */	NdrFcShort( 0x70 ),	/* Flags:  out, return, base type, */
/* 4148 */	NdrFcShort( 0x8 ),	/* x86 Stack size/offset = 8 */
/* 4150 */	0x8,		/* FC_LONG */
			0x0,		/* 0 */

	/* Procedure get_MessageHeader */


	/* Procedure get_ClientMinVer */

/* 4152 */	0x33,		/* FC_AUTO_HANDLE */
			0x6c,		/* Old Flags:  object, Oi2 */
/* 4154 */	NdrFcLong( 0x0 ),	/* 0 */
/* 4158 */	NdrFcShort( 0xb ),	/* 11 */
/* 4160 */	NdrFcShort( 0xc ),	/* x86 Stack size/offset = 12 */
/* 4162 */	NdrFcShort( 0x0 ),	/* 0 */
/* 4164 */	NdrFcShort( 0x8 ),	/* 8 */
/* 4166 */	0x45,		/* Oi2 Flags:  srv must size, has return, has ext, */
			0x2,		/* 2 */
/* 4168 */	0x8,		/* 8 */
			0x3,		/* Ext Flags:  new corr desc, clt corr check, */
/* 4170 */	NdrFcShort( 0x1 ),	/* 1 */
/* 4172 */	NdrFcShort( 0x0 ),	/* 0 */
/* 4174 */	NdrFcShort( 0x0 ),	/* 0 */

	/* Parameter pbstrMessageHeader */


	/* Parameter pbstrMinVer */

/* 4176 */	NdrFcShort( 0x2113 ),	/* Flags:  must size, must free, out, simple ref, srv alloc size=8 */
/* 4178 */	NdrFcShort( 0x4 ),	/* x86 Stack size/offset = 4 */
/* 4180 */	NdrFcShort( 0x46a ),	/* Type Offset=1130 */

	/* Return value */


	/* Return value */

/* 4182 */	NdrFcShort( 0x70 ),	/* Flags:  out, return, base type, */
/* 4184 */	NdrFcShort( 0x8 ),	/* x86 Stack size/offset = 8 */
/* 4186 */	0x8,		/* FC_LONG */
			0x0,		/* 0 */

	/* Procedure get_Notes */


	/* Procedure get_ClientCurVer */

/* 4188 */	0x33,		/* FC_AUTO_HANDLE */
			0x6c,		/* Old Flags:  object, Oi2 */
/* 4190 */	NdrFcLong( 0x0 ),	/* 0 */
/* 4194 */	NdrFcShort( 0xc ),	/* 12 */
/* 4196 */	NdrFcShort( 0xc ),	/* x86 Stack size/offset = 12 */
/* 4198 */	NdrFcShort( 0x0 ),	/* 0 */
/* 4200 */	NdrFcShort( 0x8 ),	/* 8 */
/* 4202 */	0x45,		/* Oi2 Flags:  srv must size, has return, has ext, */
			0x2,		/* 2 */
/* 4204 */	0x8,		/* 8 */
			0x3,		/* Ext Flags:  new corr desc, clt corr check, */
/* 4206 */	NdrFcShort( 0x1 ),	/* 1 */
/* 4208 */	NdrFcShort( 0x0 ),	/* 0 */
/* 4210 */	NdrFcShort( 0x0 ),	/* 0 */

	/* Parameter pbstrNotes */


	/* Parameter pbstrCurVer */

/* 4212 */	NdrFcShort( 0x2113 ),	/* Flags:  must size, must free, out, simple ref, srv alloc size=8 */
/* 4214 */	NdrFcShort( 0x4 ),	/* x86 Stack size/offset = 4 */
/* 4216 */	NdrFcShort( 0x46a ),	/* Type Offset=1130 */

	/* Return value */


	/* Return value */

/* 4218 */	NdrFcShort( 0x70 ),	/* Flags:  out, return, base type, */
/* 4220 */	NdrFcShort( 0x8 ),	/* x86 Stack size/offset = 8 */
/* 4222 */	0x8,		/* FC_LONG */
			0x0,		/* 0 */

	/* Procedure get_ClientUpdateURI */

/* 4224 */	0x33,		/* FC_AUTO_HANDLE */
			0x6c,		/* Old Flags:  object, Oi2 */
/* 4226 */	NdrFcLong( 0x0 ),	/* 0 */
/* 4230 */	NdrFcShort( 0xd ),	/* 13 */
/* 4232 */	NdrFcShort( 0xc ),	/* x86 Stack size/offset = 12 */
/* 4234 */	NdrFcShort( 0x0 ),	/* 0 */
/* 4236 */	NdrFcShort( 0x8 ),	/* 8 */
/* 4238 */	0x45,		/* Oi2 Flags:  srv must size, has return, has ext, */
			0x2,		/* 2 */
/* 4240 */	0x8,		/* 8 */
			0x3,		/* Ext Flags:  new corr desc, clt corr check, */
/* 4242 */	NdrFcShort( 0x1 ),	/* 1 */
/* 4244 */	NdrFcShort( 0x0 ),	/* 0 */
/* 4246 */	NdrFcShort( 0x0 ),	/* 0 */

	/* Parameter pbstrUpdateURI */

/* 4248 */	NdrFcShort( 0x2113 ),	/* Flags:  must size, must free, out, simple ref, srv alloc size=8 */
/* 4250 */	NdrFcShort( 0x4 ),	/* x86 Stack size/offset = 4 */
/* 4252 */	NdrFcShort( 0x46a ),	/* Type Offset=1130 */

	/* Return value */

/* 4254 */	NdrFcShort( 0x70 ),	/* Flags:  out, return, base type, */
/* 4256 */	NdrFcShort( 0x8 ),	/* x86 Stack size/offset = 8 */
/* 4258 */	0x8,		/* FC_LONG */
			0x0,		/* 0 */

	/* Procedure get_ClientData */

/* 4260 */	0x33,		/* FC_AUTO_HANDLE */
			0x6c,		/* Old Flags:  object, Oi2 */
/* 4262 */	NdrFcLong( 0x0 ),	/* 0 */
/* 4266 */	NdrFcShort( 0xe ),	/* 14 */
/* 4268 */	NdrFcShort( 0xc ),	/* x86 Stack size/offset = 12 */
/* 4270 */	NdrFcShort( 0x0 ),	/* 0 */
/* 4272 */	NdrFcShort( 0x8 ),	/* 8 */
/* 4274 */	0x45,		/* Oi2 Flags:  srv must size, has return, has ext, */
			0x2,		/* 2 */
/* 4276 */	0x8,		/* 8 */
			0x3,		/* Ext Flags:  new corr desc, clt corr check, */
/* 4278 */	NdrFcShort( 0x1 ),	/* 1 */
/* 4280 */	NdrFcShort( 0x0 ),	/* 0 */
/* 4282 */	NdrFcShort( 0x0 ),	/* 0 */

	/* Parameter pbstrData */

/* 4284 */	NdrFcShort( 0x2113 ),	/* Flags:  must size, must free, out, simple ref, srv alloc size=8 */
/* 4286 */	NdrFcShort( 0x4 ),	/* x86 Stack size/offset = 4 */
/* 4288 */	NdrFcShort( 0x46a ),	/* Type Offset=1130 */

	/* Return value */

/* 4290 */	NdrFcShort( 0x70 ),	/* Flags:  out, return, base type, */
/* 4292 */	NdrFcShort( 0x8 ),	/* x86 Stack size/offset = 8 */
/* 4294 */	0x8,		/* FC_LONG */
			0x0,		/* 0 */

	/* Procedure get_RedirectedUserURI */


	/* Procedure get_UserURI */

/* 4296 */	0x33,		/* FC_AUTO_HANDLE */
			0x6c,		/* Old Flags:  object, Oi2 */
/* 4298 */	NdrFcLong( 0x0 ),	/* 0 */
/* 4302 */	NdrFcShort( 0xf ),	/* 15 */
/* 4304 */	NdrFcShort( 0xc ),	/* x86 Stack size/offset = 12 */
/* 4306 */	NdrFcShort( 0x0 ),	/* 0 */
/* 4308 */	NdrFcShort( 0x8 ),	/* 8 */
/* 4310 */	0x45,		/* Oi2 Flags:  srv must size, has return, has ext, */
			0x2,		/* 2 */
/* 4312 */	0x8,		/* 8 */
			0x3,		/* Ext Flags:  new corr desc, clt corr check, */
/* 4314 */	NdrFcShort( 0x1 ),	/* 1 */
/* 4316 */	NdrFcShort( 0x0 ),	/* 0 */
/* 4318 */	NdrFcShort( 0x0 ),	/* 0 */

	/* Parameter pbstrUserURI */


	/* Parameter pbstrUserURI */

/* 4320 */	NdrFcShort( 0x2113 ),	/* Flags:  must size, must free, out, simple ref, srv alloc size=8 */
/* 4322 */	NdrFcShort( 0x4 ),	/* x86 Stack size/offset = 4 */
/* 4324 */	NdrFcShort( 0x46a ),	/* Type Offset=1130 */

	/* Return value */


	/* Return value */

/* 4326 */	NdrFcShort( 0x70 ),	/* Flags:  out, return, base type, */
/* 4328 */	NdrFcShort( 0x8 ),	/* x86 Stack size/offset = 8 */
/* 4330 */	0x8,		/* FC_LONG */
			0x0,		/* 0 */

	/* Procedure get_RedirectedUserName */


	/* Procedure get_UserName */

/* 4332 */	0x33,		/* FC_AUTO_HANDLE */
			0x6c,		/* Old Flags:  object, Oi2 */
/* 4334 */	NdrFcLong( 0x0 ),	/* 0 */
/* 4338 */	NdrFcShort( 0x10 ),	/* 16 */
/* 4340 */	NdrFcShort( 0xc ),	/* x86 Stack size/offset = 12 */
/* 4342 */	NdrFcShort( 0x0 ),	/* 0 */
/* 4344 */	NdrFcShort( 0x8 ),	/* 8 */
/* 4346 */	0x45,		/* Oi2 Flags:  srv must size, has return, has ext, */
			0x2,		/* 2 */
/* 4348 */	0x8,		/* 8 */
			0x3,		/* Ext Flags:  new corr desc, clt corr check, */
/* 4350 */	NdrFcShort( 0x1 ),	/* 1 */
/* 4352 */	NdrFcShort( 0x0 ),	/* 0 */
/* 4354 */	NdrFcShort( 0x0 ),	/* 0 */

	/* Parameter pbstrUserName */


	/* Parameter pbstrUserName */

/* 4356 */	NdrFcShort( 0x2113 ),	/* Flags:  must size, must free, out, simple ref, srv alloc size=8 */
/* 4358 */	NdrFcShort( 0x4 ),	/* x86 Stack size/offset = 4 */
/* 4360 */	NdrFcShort( 0x46a ),	/* Type Offset=1130 */

	/* Return value */


	/* Return value */

/* 4362 */	NdrFcShort( 0x70 ),	/* Flags:  out, return, base type, */
/* 4364 */	NdrFcShort( 0x8 ),	/* x86 Stack size/offset = 8 */
/* 4366 */	0x8,		/* FC_LONG */
			0x0,		/* 0 */

	/* Procedure get_UserAccount */

/* 4368 */	0x33,		/* FC_AUTO_HANDLE */
			0x6c,		/* Old Flags:  object, Oi2 */
/* 4370 */	NdrFcLong( 0x0 ),	/* 0 */
/* 4374 */	NdrFcShort( 0x11 ),	/* 17 */
/* 4376 */	NdrFcShort( 0xc ),	/* x86 Stack size/offset = 12 */
/* 4378 */	NdrFcShort( 0x0 ),	/* 0 */
/* 4380 */	NdrFcShort( 0x8 ),	/* 8 */
/* 4382 */	0x45,		/* Oi2 Flags:  srv must size, has return, has ext, */
			0x2,		/* 2 */
/* 4384 */	0x8,		/* 8 */
			0x3,		/* Ext Flags:  new corr desc, clt corr check, */
/* 4386 */	NdrFcShort( 0x1 ),	/* 1 */
/* 4388 */	NdrFcShort( 0x0 ),	/* 0 */
/* 4390 */	NdrFcShort( 0x0 ),	/* 0 */

	/* Parameter pbstrUserAccount */

/* 4392 */	NdrFcShort( 0x2113 ),	/* Flags:  must size, must free, out, simple ref, srv alloc size=8 */
/* 4394 */	NdrFcShort( 0x4 ),	/* x86 Stack size/offset = 4 */
/* 4396 */	NdrFcShort( 0x46a ),	/* Type Offset=1130 */

	/* Return value */

/* 4398 */	NdrFcShort( 0x70 ),	/* Flags:  out, return, base type, */
/* 4400 */	NdrFcShort( 0x8 ),	/* x86 Stack size/offset = 8 */
/* 4402 */	0x8,		/* FC_LONG */
			0x0,		/* 0 */

	/* Procedure SetCredentials */

/* 4404 */	0x33,		/* FC_AUTO_HANDLE */
			0x6c,		/* Old Flags:  object, Oi2 */
/* 4406 */	NdrFcLong( 0x0 ),	/* 0 */
/* 4410 */	NdrFcShort( 0x12 ),	/* 18 */
/* 4412 */	NdrFcShort( 0x14 ),	/* x86 Stack size/offset = 20 */
/* 4414 */	NdrFcShort( 0x0 ),	/* 0 */
/* 4416 */	NdrFcShort( 0x8 ),	/* 8 */
/* 4418 */	0x46,		/* Oi2 Flags:  clt must size, has return, has ext, */
			0x4,		/* 4 */
/* 4420 */	0x8,		/* 8 */
			0x5,		/* Ext Flags:  new corr desc, srv corr check, */
/* 4422 */	NdrFcShort( 0x0 ),	/* 0 */
/* 4424 */	NdrFcShort( 0x3 ),	/* 3 */
/* 4426 */	NdrFcShort( 0x0 ),	/* 0 */

	/* Parameter bstrUserURI */

/* 4428 */	NdrFcShort( 0x8b ),	/* Flags:  must size, must free, in, by val, */
/* 4430 */	NdrFcShort( 0x4 ),	/* x86 Stack size/offset = 4 */
/* 4432 */	NdrFcShort( 0x20 ),	/* Type Offset=32 */

	/* Parameter bstrUserAccount */

/* 4434 */	NdrFcShort( 0x8b ),	/* Flags:  must size, must free, in, by val, */
/* 4436 */	NdrFcShort( 0x8 ),	/* x86 Stack size/offset = 8 */
/* 4438 */	NdrFcShort( 0x20 ),	/* Type Offset=32 */

	/* Parameter bstrPassword */

/* 4440 */	NdrFcShort( 0x8b ),	/* Flags:  must size, must free, in, by val, */
/* 4442 */	NdrFcShort( 0xc ),	/* x86 Stack size/offset = 12 */
/* 4444 */	NdrFcShort( 0x20 ),	/* Type Offset=32 */

	/* Return value */

/* 4446 */	NdrFcShort( 0x70 ),	/* Flags:  out, return, base type, */
/* 4448 */	NdrFcShort( 0x10 ),	/* x86 Stack size/offset = 16 */
/* 4450 */	0x8,		/* FC_LONG */
			0x0,		/* 0 */

	/* Procedure get_SessionCapabilities */

/* 4452 */	0x33,		/* FC_AUTO_HANDLE */
			0x6c,		/* Old Flags:  object, Oi2 */
/* 4454 */	NdrFcLong( 0x0 ),	/* 0 */
/* 4458 */	NdrFcShort( 0x13 ),	/* 19 */
/* 4460 */	NdrFcShort( 0xc ),	/* x86 Stack size/offset = 12 */
/* 4462 */	NdrFcShort( 0x0 ),	/* 0 */
/* 4464 */	NdrFcShort( 0x24 ),	/* 36 */
/* 4466 */	0x44,		/* Oi2 Flags:  has return, has ext, */
			0x2,		/* 2 */
/* 4468 */	0x8,		/* 8 */
			0x1,		/* Ext Flags:  new corr desc, */
/* 4470 */	NdrFcShort( 0x0 ),	/* 0 */
/* 4472 */	NdrFcShort( 0x0 ),	/* 0 */
/* 4474 */	NdrFcShort( 0x0 ),	/* 0 */

	/* Parameter plSupportedSessions */

/* 4476 */	NdrFcShort( 0x2150 ),	/* Flags:  out, base type, simple ref, srv alloc size=8 */
/* 4478 */	NdrFcShort( 0x4 ),	/* x86 Stack size/offset = 4 */
/* 4480 */	0x8,		/* FC_LONG */
			0x0,		/* 0 */

	/* Return value */

/* 4482 */	NdrFcShort( 0x70 ),	/* Flags:  out, return, base type, */
/* 4484 */	NdrFcShort( 0x8 ),	/* x86 Stack size/offset = 8 */
/* 4486 */	0x8,		/* FC_LONG */
			0x0,		/* 0 */

	/* Procedure get_SubscriptionType */


	/* Procedure get_State */

/* 4488 */	0x33,		/* FC_AUTO_HANDLE */
			0x6c,		/* Old Flags:  object, Oi2 */
/* 4490 */	NdrFcLong( 0x0 ),	/* 0 */
/* 4494 */	NdrFcShort( 0x14 ),	/* 20 */
/* 4496 */	NdrFcShort( 0xc ),	/* x86 Stack size/offset = 12 */
/* 4498 */	NdrFcShort( 0x0 ),	/* 0 */
/* 4500 */	NdrFcShort( 0x22 ),	/* 34 */
/* 4502 */	0x44,		/* Oi2 Flags:  has return, has ext, */
			0x2,		/* 2 */
/* 4504 */	0x8,		/* 8 */
			0x1,		/* Ext Flags:  new corr desc, */
/* 4506 */	NdrFcShort( 0x0 ),	/* 0 */
/* 4508 */	NdrFcShort( 0x0 ),	/* 0 */
/* 4510 */	NdrFcShort( 0x0 ),	/* 0 */

	/* Parameter penSubscriptionType */


	/* Parameter penState */

/* 4512 */	NdrFcShort( 0x2010 ),	/* Flags:  out, srv alloc size=8 */
/* 4514 */	NdrFcShort( 0x4 ),	/* x86 Stack size/offset = 4 */
/* 4516 */	NdrFcShort( 0x52 ),	/* Type Offset=82 */

	/* Return value */


	/* Return value */

/* 4518 */	NdrFcShort( 0x70 ),	/* Flags:  out, return, base type, */
/* 4520 */	NdrFcShort( 0x8 ),	/* x86 Stack size/offset = 8 */
/* 4522 */	0x8,		/* FC_LONG */
			0x0,		/* 0 */

	/* Procedure get_Realm */

/* 4524 */	0x33,		/* FC_AUTO_HANDLE */
			0x6c,		/* Old Flags:  object, Oi2 */
/* 4526 */	NdrFcLong( 0x0 ),	/* 0 */
/* 4530 */	NdrFcShort( 0x15 ),	/* 21 */
/* 4532 */	NdrFcShort( 0xc ),	/* x86 Stack size/offset = 12 */
/* 4534 */	NdrFcShort( 0x0 ),	/* 0 */
/* 4536 */	NdrFcShort( 0x8 ),	/* 8 */
/* 4538 */	0x45,		/* Oi2 Flags:  srv must size, has return, has ext, */
			0x2,		/* 2 */
/* 4540 */	0x8,		/* 8 */
			0x3,		/* Ext Flags:  new corr desc, clt corr check, */
/* 4542 */	NdrFcShort( 0x1 ),	/* 1 */
/* 4544 */	NdrFcShort( 0x0 ),	/* 0 */
/* 4546 */	NdrFcShort( 0x0 ),	/* 0 */

	/* Parameter pbstrRealm */

/* 4548 */	NdrFcShort( 0x2113 ),	/* Flags:  must size, must free, out, simple ref, srv alloc size=8 */
/* 4550 */	NdrFcShort( 0x4 ),	/* x86 Stack size/offset = 4 */
/* 4552 */	NdrFcShort( 0x46a ),	/* Type Offset=1130 */

	/* Return value */

/* 4554 */	NdrFcShort( 0x70 ),	/* Flags:  out, return, base type, */
/* 4556 */	NdrFcShort( 0x8 ),	/* x86 Stack size/offset = 8 */
/* 4558 */	0x8,		/* FC_LONG */
			0x0,		/* 0 */

	/* Procedure put_Realm */

/* 4560 */	0x33,		/* FC_AUTO_HANDLE */
			0x6c,		/* Old Flags:  object, Oi2 */
/* 4562 */	NdrFcLong( 0x0 ),	/* 0 */
/* 4566 */	NdrFcShort( 0x16 ),	/* 22 */
/* 4568 */	NdrFcShort( 0xc ),	/* x86 Stack size/offset = 12 */
/* 4570 */	NdrFcShort( 0x0 ),	/* 0 */
/* 4572 */	NdrFcShort( 0x8 ),	/* 8 */
/* 4574 */	0x46,		/* Oi2 Flags:  clt must size, has return, has ext, */
			0x2,		/* 2 */
/* 4576 */	0x8,		/* 8 */
			0x5,		/* Ext Flags:  new corr desc, srv corr check, */
/* 4578 */	NdrFcShort( 0x0 ),	/* 0 */
/* 4580 */	NdrFcShort( 0x1 ),	/* 1 */
/* 4582 */	NdrFcShort( 0x0 ),	/* 0 */

	/* Parameter bstrRealm */

/* 4584 */	NdrFcShort( 0x8b ),	/* Flags:  must size, must free, in, by val, */
/* 4586 */	NdrFcShort( 0x4 ),	/* x86 Stack size/offset = 4 */
/* 4588 */	NdrFcShort( 0x20 ),	/* Type Offset=32 */

	/* Return value */

/* 4590 */	NdrFcShort( 0x70 ),	/* Flags:  out, return, base type, */
/* 4592 */	NdrFcShort( 0x8 ),	/* x86 Stack size/offset = 8 */
/* 4594 */	0x8,		/* FC_LONG */
			0x0,		/* 0 */

	/* Procedure get_AllowedAuth */

/* 4596 */	0x33,		/* FC_AUTO_HANDLE */
			0x6c,		/* Old Flags:  object, Oi2 */
/* 4598 */	NdrFcLong( 0x0 ),	/* 0 */
/* 4602 */	NdrFcShort( 0x17 ),	/* 23 */
/* 4604 */	NdrFcShort( 0xc ),	/* x86 Stack size/offset = 12 */
/* 4606 */	NdrFcShort( 0x0 ),	/* 0 */
/* 4608 */	NdrFcShort( 0x24 ),	/* 36 */
/* 4610 */	0x44,		/* Oi2 Flags:  has return, has ext, */
			0x2,		/* 2 */
/* 4612 */	0x8,		/* 8 */
			0x1,		/* Ext Flags:  new corr desc, */
/* 4614 */	NdrFcShort( 0x0 ),	/* 0 */
/* 4616 */	NdrFcShort( 0x0 ),	/* 0 */
/* 4618 */	NdrFcShort( 0x0 ),	/* 0 */

	/* Parameter plAllowedAuth */

/* 4620 */	NdrFcShort( 0x2150 ),	/* Flags:  out, base type, simple ref, srv alloc size=8 */
/* 4622 */	NdrFcShort( 0x4 ),	/* x86 Stack size/offset = 4 */
/* 4624 */	0x8,		/* FC_LONG */
			0x0,		/* 0 */

	/* Return value */

/* 4626 */	NdrFcShort( 0x70 ),	/* Flags:  out, return, base type, */
/* 4628 */	NdrFcShort( 0x8 ),	/* x86 Stack size/offset = 8 */
/* 4630 */	0x8,		/* FC_LONG */
			0x0,		/* 0 */

	/* Procedure put_AllowedAuth */

/* 4632 */	0x33,		/* FC_AUTO_HANDLE */
			0x6c,		/* Old Flags:  object, Oi2 */
/* 4634 */	NdrFcLong( 0x0 ),	/* 0 */
/* 4638 */	NdrFcShort( 0x18 ),	/* 24 */
/* 4640 */	NdrFcShort( 0xc ),	/* x86 Stack size/offset = 12 */
/* 4642 */	NdrFcShort( 0x8 ),	/* 8 */
/* 4644 */	NdrFcShort( 0x8 ),	/* 8 */
/* 4646 */	0x44,		/* Oi2 Flags:  has return, has ext, */
			0x2,		/* 2 */
/* 4648 */	0x8,		/* 8 */
			0x1,		/* Ext Flags:  new corr desc, */
/* 4650 */	NdrFcShort( 0x0 ),	/* 0 */
/* 4652 */	NdrFcShort( 0x0 ),	/* 0 */
/* 4654 */	NdrFcShort( 0x0 ),	/* 0 */

	/* Parameter lAllowedAuth */

/* 4656 */	NdrFcShort( 0x48 ),	/* Flags:  in, base type, */
/* 4658 */	NdrFcShort( 0x4 ),	/* x86 Stack size/offset = 4 */
/* 4660 */	0x8,		/* FC_LONG */
			0x0,		/* 0 */

	/* Return value */

/* 4662 */	NdrFcShort( 0x70 ),	/* Flags:  out, return, base type, */
/* 4664 */	NdrFcShort( 0x8 ),	/* x86 Stack size/offset = 8 */
/* 4666 */	0x8,		/* FC_LONG */
			0x0,		/* 0 */

	/* Procedure GetServer */

/* 4668 */	0x33,		/* FC_AUTO_HANDLE */
			0x6c,		/* Old Flags:  object, Oi2 */
/* 4670 */	NdrFcLong( 0x0 ),	/* 0 */
/* 4674 */	NdrFcShort( 0x19 ),	/* 25 */
/* 4676 */	NdrFcShort( 0x10 ),	/* x86 Stack size/offset = 16 */
/* 4678 */	NdrFcShort( 0x0 ),	/* 0 */
/* 4680 */	NdrFcShort( 0x24 ),	/* 36 */
/* 4682 */	0x45,		/* Oi2 Flags:  srv must size, has return, has ext, */
			0x3,		/* 3 */
/* 4684 */	0x8,		/* 8 */
			0x3,		/* Ext Flags:  new corr desc, clt corr check, */
/* 4686 */	NdrFcShort( 0x1 ),	/* 1 */
/* 4688 */	NdrFcShort( 0x0 ),	/* 0 */
/* 4690 */	NdrFcShort( 0x0 ),	/* 0 */

	/* Parameter pbstrServer */

/* 4692 */	NdrFcShort( 0x2113 ),	/* Flags:  must size, must free, out, simple ref, srv alloc size=8 */
/* 4694 */	NdrFcShort( 0x4 ),	/* x86 Stack size/offset = 4 */
/* 4696 */	NdrFcShort( 0x46a ),	/* Type Offset=1130 */

	/* Parameter plTransport */

/* 4698 */	NdrFcShort( 0x2150 ),	/* Flags:  out, base type, simple ref, srv alloc size=8 */
/* 4700 */	NdrFcShort( 0x8 ),	/* x86 Stack size/offset = 8 */
/* 4702 */	0x8,		/* FC_LONG */
			0x0,		/* 0 */

	/* Return value */

/* 4704 */	NdrFcShort( 0x70 ),	/* Flags:  out, return, base type, */
/* 4706 */	NdrFcShort( 0xc ),	/* x86 Stack size/offset = 12 */
/* 4708 */	0x8,		/* FC_LONG */
			0x0,		/* 0 */

	/* Procedure get_Client */

/* 4710 */	0x33,		/* FC_AUTO_HANDLE */
			0x6c,		/* Old Flags:  object, Oi2 */
/* 4712 */	NdrFcLong( 0x0 ),	/* 0 */
/* 4716 */	NdrFcShort( 0x3 ),	/* 3 */
/* 4718 */	NdrFcShort( 0xc ),	/* x86 Stack size/offset = 12 */
/* 4720 */	NdrFcShort( 0x0 ),	/* 0 */
/* 4722 */	NdrFcShort( 0x8 ),	/* 8 */
/* 4724 */	0x45,		/* Oi2 Flags:  srv must size, has return, has ext, */
			0x2,		/* 2 */
/* 4726 */	0x8,		/* 8 */
			0x1,		/* Ext Flags:  new corr desc, */
/* 4728 */	NdrFcShort( 0x0 ),	/* 0 */
/* 4730 */	NdrFcShort( 0x0 ),	/* 0 */
/* 4732 */	NdrFcShort( 0x0 ),	/* 0 */

	/* Parameter ppClient */

/* 4734 */	NdrFcShort( 0x13 ),	/* Flags:  must size, must free, out, */
/* 4736 */	NdrFcShort( 0x4 ),	/* x86 Stack size/offset = 4 */
/* 4738 */	NdrFcShort( 0x5a0 ),	/* Type Offset=1440 */

	/* Return value */

/* 4740 */	NdrFcShort( 0x70 ),	/* Flags:  out, return, base type, */
/* 4742 */	NdrFcShort( 0x8 ),	/* x86 Stack size/offset = 8 */
/* 4744 */	0x8,		/* FC_LONG */
			0x0,		/* 0 */

	/* Procedure get_State */

/* 4746 */	0x33,		/* FC_AUTO_HANDLE */
			0x6c,		/* Old Flags:  object, Oi2 */
/* 4748 */	NdrFcLong( 0x0 ),	/* 0 */
/* 4752 */	NdrFcShort( 0x4 ),	/* 4 */
/* 4754 */	NdrFcShort( 0xc ),	/* x86 Stack size/offset = 12 */
/* 4756 */	NdrFcShort( 0x0 ),	/* 0 */
/* 4758 */	NdrFcShort( 0x22 ),	/* 34 */
/* 4760 */	0x44,		/* Oi2 Flags:  has return, has ext, */
			0x2,		/* 2 */
/* 4762 */	0x8,		/* 8 */
			0x1,		/* Ext Flags:  new corr desc, */
/* 4764 */	NdrFcShort( 0x0 ),	/* 0 */
/* 4766 */	NdrFcShort( 0x0 ),	/* 0 */
/* 4768 */	NdrFcShort( 0x0 ),	/* 0 */

	/* Parameter penState */

/* 4770 */	NdrFcShort( 0x2010 ),	/* Flags:  out, srv alloc size=8 */
/* 4772 */	NdrFcShort( 0x4 ),	/* x86 Stack size/offset = 4 */
/* 4774 */	NdrFcShort( 0x52 ),	/* Type Offset=82 */

	/* Return value */

/* 4776 */	NdrFcShort( 0x70 ),	/* Flags:  out, return, base type, */
/* 4778 */	NdrFcShort( 0x8 ),	/* x86 Stack size/offset = 8 */
/* 4780 */	0x8,		/* FC_LONG */
			0x0,		/* 0 */

	/* Procedure get_Type */

/* 4782 */	0x33,		/* FC_AUTO_HANDLE */
			0x6c,		/* Old Flags:  object, Oi2 */
/* 4784 */	NdrFcLong( 0x0 ),	/* 0 */
/* 4788 */	NdrFcShort( 0x5 ),	/* 5 */
/* 4790 */	NdrFcShort( 0xc ),	/* x86 Stack size/offset = 12 */
/* 4792 */	NdrFcShort( 0x0 ),	/* 0 */
/* 4794 */	NdrFcShort( 0x22 ),	/* 34 */
/* 4796 */	0x44,		/* Oi2 Flags:  has return, has ext, */
			0x2,		/* 2 */
/* 4798 */	0x8,		/* 8 */
			0x1,		/* Ext Flags:  new corr desc, */
/* 4800 */	NdrFcShort( 0x0 ),	/* 0 */
/* 4802 */	NdrFcShort( 0x0 ),	/* 0 */
/* 4804 */	NdrFcShort( 0x0 ),	/* 0 */

	/* Parameter penType */

/* 4806 */	NdrFcShort( 0x2010 ),	/* Flags:  out, srv alloc size=8 */
/* 4808 */	NdrFcShort( 0x4 ),	/* x86 Stack size/offset = 4 */
/* 4810 */	NdrFcShort( 0x52 ),	/* Type Offset=82 */

	/* Return value */

/* 4812 */	NdrFcShort( 0x70 ),	/* Flags:  out, return, base type, */
/* 4814 */	NdrFcShort( 0x8 ),	/* x86 Stack size/offset = 8 */
/* 4816 */	0x8,		/* FC_LONG */
			0x0,		/* 0 */

	/* Procedure get_Profile */

/* 4818 */	0x33,		/* FC_AUTO_HANDLE */
			0x6c,		/* Old Flags:  object, Oi2 */
/* 4820 */	NdrFcLong( 0x0 ),	/* 0 */
/* 4824 */	NdrFcShort( 0x6 ),	/* 6 */
/* 4826 */	NdrFcShort( 0xc ),	/* x86 Stack size/offset = 12 */
/* 4828 */	NdrFcShort( 0x0 ),	/* 0 */
/* 4830 */	NdrFcShort( 0x8 ),	/* 8 */
/* 4832 */	0x45,		/* Oi2 Flags:  srv must size, has return, has ext, */
			0x2,		/* 2 */
/* 4834 */	0x8,		/* 8 */
			0x1,		/* Ext Flags:  new corr desc, */
/* 4836 */	NdrFcShort( 0x0 ),	/* 0 */
/* 4838 */	NdrFcShort( 0x0 ),	/* 0 */
/* 4840 */	NdrFcShort( 0x0 ),	/* 0 */

	/* Parameter ppProfile */

/* 4842 */	NdrFcShort( 0x13 ),	/* Flags:  must size, must free, out, */
/* 4844 */	NdrFcShort( 0x4 ),	/* x86 Stack size/offset = 4 */
/* 4846 */	NdrFcShort( 0x586 ),	/* Type Offset=1414 */

	/* Return value */

/* 4848 */	NdrFcShort( 0x70 ),	/* Flags:  out, return, base type, */
/* 4850 */	NdrFcShort( 0x8 ),	/* x86 Stack size/offset = 8 */
/* 4852 */	0x8,		/* FC_LONG */
			0x0,		/* 0 */

	/* Procedure Answer */

/* 4854 */	0x33,		/* FC_AUTO_HANDLE */
			0x6c,		/* Old Flags:  object, Oi2 */
/* 4856 */	NdrFcLong( 0x0 ),	/* 0 */
/* 4860 */	NdrFcShort( 0x8 ),	/* 8 */
/* 4862 */	NdrFcShort( 0x8 ),	/* x86 Stack size/offset = 8 */
/* 4864 */	NdrFcShort( 0x0 ),	/* 0 */
/* 4866 */	NdrFcShort( 0x8 ),	/* 8 */
/* 4868 */	0x44,		/* Oi2 Flags:  has return, has ext, */
			0x1,		/* 1 */
/* 4870 */	0x8,		/* 8 */
			0x1,		/* Ext Flags:  new corr desc, */
/* 4872 */	NdrFcShort( 0x0 ),	/* 0 */
/* 4874 */	NdrFcShort( 0x0 ),	/* 0 */
/* 4876 */	NdrFcShort( 0x0 ),	/* 0 */

	/* Return value */

/* 4878 */	NdrFcShort( 0x70 ),	/* Flags:  out, return, base type, */
/* 4880 */	NdrFcShort( 0x4 ),	/* x86 Stack size/offset = 4 */
/* 4882 */	0x8,		/* FC_LONG */
			0x0,		/* 0 */

	/* Procedure Terminate */

/* 4884 */	0x33,		/* FC_AUTO_HANDLE */
			0x6c,		/* Old Flags:  object, Oi2 */
/* 4886 */	NdrFcLong( 0x0 ),	/* 0 */
/* 4890 */	NdrFcShort( 0x9 ),	/* 9 */
/* 4892 */	NdrFcShort( 0xc ),	/* x86 Stack size/offset = 12 */
/* 4894 */	NdrFcShort( 0x6 ),	/* 6 */
/* 4896 */	NdrFcShort( 0x8 ),	/* 8 */
/* 4898 */	0x44,		/* Oi2 Flags:  has return, has ext, */
			0x2,		/* 2 */
/* 4900 */	0x8,		/* 8 */
			0x1,		/* Ext Flags:  new corr desc, */
/* 4902 */	NdrFcShort( 0x0 ),	/* 0 */
/* 4904 */	NdrFcShort( 0x0 ),	/* 0 */
/* 4906 */	NdrFcShort( 0x0 ),	/* 0 */

	/* Parameter enReason */

/* 4908 */	NdrFcShort( 0x48 ),	/* Flags:  in, base type, */
/* 4910 */	NdrFcShort( 0x4 ),	/* x86 Stack size/offset = 4 */
/* 4912 */	0xd,		/* FC_ENUM16 */
			0x0,		/* 0 */

	/* Return value */

/* 4914 */	NdrFcShort( 0x70 ),	/* Flags:  out, return, base type, */
/* 4916 */	NdrFcShort( 0x8 ),	/* x86 Stack size/offset = 8 */
/* 4918 */	0x8,		/* FC_LONG */
			0x0,		/* 0 */

	/* Procedure Redirect */

/* 4920 */	0x33,		/* FC_AUTO_HANDLE */
			0x6c,		/* Old Flags:  object, Oi2 */
/* 4922 */	NdrFcLong( 0x0 ),	/* 0 */
/* 4926 */	NdrFcShort( 0xa ),	/* 10 */
/* 4928 */	NdrFcShort( 0x18 ),	/* x86 Stack size/offset = 24 */
/* 4930 */	NdrFcShort( 0xe ),	/* 14 */
/* 4932 */	NdrFcShort( 0x8 ),	/* 8 */
/* 4934 */	0x46,		/* Oi2 Flags:  clt must size, has return, has ext, */
			0x5,		/* 5 */
/* 4936 */	0x8,		/* 8 */
			0x5,		/* Ext Flags:  new corr desc, srv corr check, */
/* 4938 */	NdrFcShort( 0x0 ),	/* 0 */
/* 4940 */	NdrFcShort( 0x1 ),	/* 1 */
/* 4942 */	NdrFcShort( 0x0 ),	/* 0 */

	/* Parameter enType */

/* 4944 */	NdrFcShort( 0x48 ),	/* Flags:  in, base type, */
/* 4946 */	NdrFcShort( 0x4 ),	/* x86 Stack size/offset = 4 */
/* 4948 */	0xd,		/* FC_ENUM16 */
			0x0,		/* 0 */

	/* Parameter bstrLocalPhoneURI */

/* 4950 */	NdrFcShort( 0x8b ),	/* Flags:  must size, must free, in, by val, */
/* 4952 */	NdrFcShort( 0x8 ),	/* x86 Stack size/offset = 8 */
/* 4954 */	NdrFcShort( 0x20 ),	/* Type Offset=32 */

	/* Parameter pProfile */

/* 4956 */	NdrFcShort( 0xb ),	/* Flags:  must size, must free, in, */
/* 4958 */	NdrFcShort( 0xc ),	/* x86 Stack size/offset = 12 */
/* 4960 */	NdrFcShort( 0x2a ),	/* Type Offset=42 */

	/* Parameter lFlags */

/* 4962 */	NdrFcShort( 0x48 ),	/* Flags:  in, base type, */
/* 4964 */	NdrFcShort( 0x10 ),	/* x86 Stack size/offset = 16 */
/* 4966 */	0x8,		/* FC_LONG */
			0x0,		/* 0 */

	/* Return value */

/* 4968 */	NdrFcShort( 0x70 ),	/* Flags:  out, return, base type, */
/* 4970 */	NdrFcShort( 0x14 ),	/* x86 Stack size/offset = 20 */
/* 4972 */	0x8,		/* FC_LONG */
			0x0,		/* 0 */

	/* Procedure AddParticipant */

/* 4974 */	0x33,		/* FC_AUTO_HANDLE */
			0x6c,		/* Old Flags:  object, Oi2 */
/* 4976 */	NdrFcLong( 0x0 ),	/* 0 */
/* 4980 */	NdrFcShort( 0xb ),	/* 11 */
/* 4982 */	NdrFcShort( 0x14 ),	/* x86 Stack size/offset = 20 */
/* 4984 */	NdrFcShort( 0x0 ),	/* 0 */
/* 4986 */	NdrFcShort( 0x8 ),	/* 8 */
/* 4988 */	0x47,		/* Oi2 Flags:  srv must size, clt must size, has return, has ext, */
			0x4,		/* 4 */
/* 4990 */	0x8,		/* 8 */
			0x5,		/* Ext Flags:  new corr desc, srv corr check, */
/* 4992 */	NdrFcShort( 0x0 ),	/* 0 */
/* 4994 */	NdrFcShort( 0x2 ),	/* 2 */
/* 4996 */	NdrFcShort( 0x0 ),	/* 0 */

	/* Parameter bstrAddress */

/* 4998 */	NdrFcShort( 0x8b ),	/* Flags:  must size, must free, in, by val, */
/* 5000 */	NdrFcShort( 0x4 ),	/* x86 Stack size/offset = 4 */
/* 5002 */	NdrFcShort( 0x20 ),	/* Type Offset=32 */

	/* Parameter bstrName */

/* 5004 */	NdrFcShort( 0x8b ),	/* Flags:  must size, must free, in, by val, */
/* 5006 */	NdrFcShort( 0x8 ),	/* x86 Stack size/offset = 8 */
/* 5008 */	NdrFcShort( 0x20 ),	/* Type Offset=32 */

	/* Parameter ppParticipant */

/* 5010 */	NdrFcShort( 0x13 ),	/* Flags:  must size, must free, out, */
/* 5012 */	NdrFcShort( 0xc ),	/* x86 Stack size/offset = 12 */
/* 5014 */	NdrFcShort( 0x5b6 ),	/* Type Offset=1462 */

	/* Return value */

/* 5016 */	NdrFcShort( 0x70 ),	/* Flags:  out, return, base type, */
/* 5018 */	NdrFcShort( 0x10 ),	/* x86 Stack size/offset = 16 */
/* 5020 */	0x8,		/* FC_LONG */
			0x0,		/* 0 */

	/* Procedure RemoveParticipant */

/* 5022 */	0x33,		/* FC_AUTO_HANDLE */
			0x6c,		/* Old Flags:  object, Oi2 */
/* 5024 */	NdrFcLong( 0x0 ),	/* 0 */
/* 5028 */	NdrFcShort( 0xc ),	/* 12 */
/* 5030 */	NdrFcShort( 0xc ),	/* x86 Stack size/offset = 12 */
/* 5032 */	NdrFcShort( 0x0 ),	/* 0 */
/* 5034 */	NdrFcShort( 0x8 ),	/* 8 */
/* 5036 */	0x46,		/* Oi2 Flags:  clt must size, has return, has ext, */
			0x2,		/* 2 */
/* 5038 */	0x8,		/* 8 */
			0x1,		/* Ext Flags:  new corr desc, */
/* 5040 */	NdrFcShort( 0x0 ),	/* 0 */
/* 5042 */	NdrFcShort( 0x0 ),	/* 0 */
/* 5044 */	NdrFcShort( 0x0 ),	/* 0 */

	/* Parameter pParticipant */

/* 5046 */	NdrFcShort( 0xb ),	/* Flags:  must size, must free, in, */
/* 5048 */	NdrFcShort( 0x4 ),	/* x86 Stack size/offset = 4 */
/* 5050 */	NdrFcShort( 0x5ba ),	/* Type Offset=1466 */

	/* Return value */

/* 5052 */	NdrFcShort( 0x70 ),	/* Flags:  out, return, base type, */
/* 5054 */	NdrFcShort( 0x8 ),	/* x86 Stack size/offset = 8 */
/* 5056 */	0x8,		/* FC_LONG */
			0x0,		/* 0 */

	/* Procedure EnumerateParticipants */

/* 5058 */	0x33,		/* FC_AUTO_HANDLE */
			0x6c,		/* Old Flags:  object, Oi2 */
/* 5060 */	NdrFcLong( 0x0 ),	/* 0 */
/* 5064 */	NdrFcShort( 0xd ),	/* 13 */
/* 5066 */	NdrFcShort( 0xc ),	/* x86 Stack size/offset = 12 */
/* 5068 */	NdrFcShort( 0x0 ),	/* 0 */
/* 5070 */	NdrFcShort( 0x8 ),	/* 8 */
/* 5072 */	0x45,		/* Oi2 Flags:  srv must size, has return, has ext, */
			0x2,		/* 2 */
/* 5074 */	0x8,		/* 8 */
			0x1,		/* Ext Flags:  new corr desc, */
/* 5076 */	NdrFcShort( 0x0 ),	/* 0 */
/* 5078 */	NdrFcShort( 0x0 ),	/* 0 */
/* 5080 */	NdrFcShort( 0x0 ),	/* 0 */

	/* Parameter ppEnum */

/* 5082 */	NdrFcShort( 0x13 ),	/* Flags:  must size, must free, out, */
/* 5084 */	NdrFcShort( 0x4 ),	/* x86 Stack size/offset = 4 */
/* 5086 */	NdrFcShort( 0x5cc ),	/* Type Offset=1484 */

	/* Return value */

/* 5088 */	NdrFcShort( 0x70 ),	/* Flags:  out, return, base type, */
/* 5090 */	NdrFcShort( 0x8 ),	/* x86 Stack size/offset = 8 */
/* 5092 */	0x8,		/* FC_LONG */
			0x0,		/* 0 */

	/* Procedure get_CanAddParticipants */

/* 5094 */	0x33,		/* FC_AUTO_HANDLE */
			0x6c,		/* Old Flags:  object, Oi2 */
/* 5096 */	NdrFcLong( 0x0 ),	/* 0 */
/* 5100 */	NdrFcShort( 0xe ),	/* 14 */
/* 5102 */	NdrFcShort( 0xc ),	/* x86 Stack size/offset = 12 */
/* 5104 */	NdrFcShort( 0x0 ),	/* 0 */
/* 5106 */	NdrFcShort( 0x22 ),	/* 34 */
/* 5108 */	0x44,		/* Oi2 Flags:  has return, has ext, */
			0x2,		/* 2 */
/* 5110 */	0x8,		/* 8 */
			0x1,		/* Ext Flags:  new corr desc, */
/* 5112 */	NdrFcShort( 0x0 ),	/* 0 */
/* 5114 */	NdrFcShort( 0x0 ),	/* 0 */
/* 5116 */	NdrFcShort( 0x0 ),	/* 0 */

	/* Parameter pfCanAdd */

/* 5118 */	NdrFcShort( 0x2150 ),	/* Flags:  out, base type, simple ref, srv alloc size=8 */
/* 5120 */	NdrFcShort( 0x4 ),	/* x86 Stack size/offset = 4 */
/* 5122 */	0x6,		/* FC_SHORT */
			0x0,		/* 0 */

	/* Return value */

/* 5124 */	NdrFcShort( 0x70 ),	/* Flags:  out, return, base type, */
/* 5126 */	NdrFcShort( 0x8 ),	/* x86 Stack size/offset = 8 */
/* 5128 */	0x8,		/* FC_LONG */
			0x0,		/* 0 */

	/* Procedure NextRedirectedUser */

/* 5130 */	0x33,		/* FC_AUTO_HANDLE */
			0x6c,		/* Old Flags:  object, Oi2 */
/* 5132 */	NdrFcLong( 0x0 ),	/* 0 */
/* 5136 */	NdrFcShort( 0x11 ),	/* 17 */
/* 5138 */	NdrFcShort( 0x8 ),	/* x86 Stack size/offset = 8 */
/* 5140 */	NdrFcShort( 0x0 ),	/* 0 */
/* 5142 */	NdrFcShort( 0x8 ),	/* 8 */
/* 5144 */	0x44,		/* Oi2 Flags:  has return, has ext, */
			0x1,		/* 1 */
/* 5146 */	0x8,		/* 8 */
			0x1,		/* Ext Flags:  new corr desc, */
/* 5148 */	NdrFcShort( 0x0 ),	/* 0 */
/* 5150 */	NdrFcShort( 0x0 ),	/* 0 */
/* 5152 */	NdrFcShort( 0x0 ),	/* 0 */

	/* Return value */

/* 5154 */	NdrFcShort( 0x70 ),	/* Flags:  out, return, base type, */
/* 5156 */	NdrFcShort( 0x4 ),	/* x86 Stack size/offset = 4 */
/* 5158 */	0x8,		/* FC_LONG */
			0x0,		/* 0 */

	/* Procedure SendMessage */

/* 5160 */	0x33,		/* FC_AUTO_HANDLE */
			0x6c,		/* Old Flags:  object, Oi2 */
/* 5162 */	NdrFcLong( 0x0 ),	/* 0 */
/* 5166 */	NdrFcShort( 0x12 ),	/* 18 */
/* 5168 */	NdrFcShort( 0x14 ),	/* x86 Stack size/offset = 20 */
/* 5170 */	NdrFcShort( 0x8 ),	/* 8 */
/* 5172 */	NdrFcShort( 0x8 ),	/* 8 */
/* 5174 */	0x46,		/* Oi2 Flags:  clt must size, has return, has ext, */
			0x4,		/* 4 */
/* 5176 */	0x8,		/* 8 */
			0x5,		/* Ext Flags:  new corr desc, srv corr check, */
/* 5178 */	NdrFcShort( 0x0 ),	/* 0 */
/* 5180 */	NdrFcShort( 0x2 ),	/* 2 */
/* 5182 */	NdrFcShort( 0x0 ),	/* 0 */

	/* Parameter bstrMessageHeader */

/* 5184 */	NdrFcShort( 0x8b ),	/* Flags:  must size, must free, in, by val, */
/* 5186 */	NdrFcShort( 0x4 ),	/* x86 Stack size/offset = 4 */
/* 5188 */	NdrFcShort( 0x20 ),	/* Type Offset=32 */

	/* Parameter bstrMessage */

/* 5190 */	NdrFcShort( 0x8b ),	/* Flags:  must size, must free, in, by val, */
/* 5192 */	NdrFcShort( 0x8 ),	/* x86 Stack size/offset = 8 */
/* 5194 */	NdrFcShort( 0x20 ),	/* Type Offset=32 */

	/* Parameter lCookie */

/* 5196 */	NdrFcShort( 0x48 ),	/* Flags:  in, base type, */
/* 5198 */	NdrFcShort( 0xc ),	/* x86 Stack size/offset = 12 */
/* 5200 */	0x8,		/* FC_LONG */
			0x0,		/* 0 */

	/* Return value */

/* 5202 */	NdrFcShort( 0x70 ),	/* Flags:  out, return, base type, */
/* 5204 */	NdrFcShort( 0x10 ),	/* x86 Stack size/offset = 16 */
/* 5206 */	0x8,		/* FC_LONG */
			0x0,		/* 0 */

	/* Procedure SendMessageStatus */

/* 5208 */	0x33,		/* FC_AUTO_HANDLE */
			0x6c,		/* Old Flags:  object, Oi2 */
/* 5210 */	NdrFcLong( 0x0 ),	/* 0 */
/* 5214 */	NdrFcShort( 0x13 ),	/* 19 */
/* 5216 */	NdrFcShort( 0x10 ),	/* x86 Stack size/offset = 16 */
/* 5218 */	NdrFcShort( 0xe ),	/* 14 */
/* 5220 */	NdrFcShort( 0x8 ),	/* 8 */
/* 5222 */	0x44,		/* Oi2 Flags:  has return, has ext, */
			0x3,		/* 3 */
/* 5224 */	0x8,		/* 8 */
			0x1,		/* Ext Flags:  new corr desc, */
/* 5226 */	NdrFcShort( 0x0 ),	/* 0 */
/* 5228 */	NdrFcShort( 0x0 ),	/* 0 */
/* 5230 */	NdrFcShort( 0x0 ),	/* 0 */

	/* Parameter enUserStatus */

/* 5232 */	NdrFcShort( 0x48 ),	/* Flags:  in, base type, */
/* 5234 */	NdrFcShort( 0x4 ),	/* x86 Stack size/offset = 4 */
/* 5236 */	0xd,		/* FC_ENUM16 */
			0x0,		/* 0 */

	/* Parameter lCookie */

/* 5238 */	NdrFcShort( 0x48 ),	/* Flags:  in, base type, */
/* 5240 */	NdrFcShort( 0x8 ),	/* x86 Stack size/offset = 8 */
/* 5242 */	0x8,		/* FC_LONG */
			0x0,		/* 0 */

	/* Return value */

/* 5244 */	NdrFcShort( 0x70 ),	/* Flags:  out, return, base type, */
/* 5246 */	NdrFcShort( 0xc ),	/* x86 Stack size/offset = 12 */
/* 5248 */	0x8,		/* FC_LONG */
			0x0,		/* 0 */

	/* Procedure AddStream */

/* 5250 */	0x33,		/* FC_AUTO_HANDLE */
			0x6c,		/* Old Flags:  object, Oi2 */
/* 5252 */	NdrFcLong( 0x0 ),	/* 0 */
/* 5256 */	NdrFcShort( 0x14 ),	/* 20 */
/* 5258 */	NdrFcShort( 0x10 ),	/* x86 Stack size/offset = 16 */
/* 5260 */	NdrFcShort( 0x10 ),	/* 16 */
/* 5262 */	NdrFcShort( 0x8 ),	/* 8 */
/* 5264 */	0x44,		/* Oi2 Flags:  has return, has ext, */
			0x3,		/* 3 */
/* 5266 */	0x8,		/* 8 */
			0x1,		/* Ext Flags:  new corr desc, */
/* 5268 */	NdrFcShort( 0x0 ),	/* 0 */
/* 5270 */	NdrFcShort( 0x0 ),	/* 0 */
/* 5272 */	NdrFcShort( 0x0 ),	/* 0 */

	/* Parameter lMediaType */

/* 5274 */	NdrFcShort( 0x48 ),	/* Flags:  in, base type, */
/* 5276 */	NdrFcShort( 0x4 ),	/* x86 Stack size/offset = 4 */
/* 5278 */	0x8,		/* FC_LONG */
			0x0,		/* 0 */

	/* Parameter lCookie */

/* 5280 */	NdrFcShort( 0x48 ),	/* Flags:  in, base type, */
/* 5282 */	NdrFcShort( 0x8 ),	/* x86 Stack size/offset = 8 */
/* 5284 */	0x8,		/* FC_LONG */
			0x0,		/* 0 */

	/* Return value */

/* 5286 */	NdrFcShort( 0x70 ),	/* Flags:  out, return, base type, */
/* 5288 */	NdrFcShort( 0xc ),	/* x86 Stack size/offset = 12 */
/* 5290 */	0x8,		/* FC_LONG */
			0x0,		/* 0 */

	/* Procedure RemoveStream */

/* 5292 */	0x33,		/* FC_AUTO_HANDLE */
			0x6c,		/* Old Flags:  object, Oi2 */
/* 5294 */	NdrFcLong( 0x0 ),	/* 0 */
/* 5298 */	NdrFcShort( 0x15 ),	/* 21 */
/* 5300 */	NdrFcShort( 0x10 ),	/* x86 Stack size/offset = 16 */
/* 5302 */	NdrFcShort( 0x10 ),	/* 16 */
/* 5304 */	NdrFcShort( 0x8 ),	/* 8 */
/* 5306 */	0x44,		/* Oi2 Flags:  has return, has ext, */
			0x3,		/* 3 */
/* 5308 */	0x8,		/* 8 */
			0x1,		/* Ext Flags:  new corr desc, */
/* 5310 */	NdrFcShort( 0x0 ),	/* 0 */
/* 5312 */	NdrFcShort( 0x0 ),	/* 0 */
/* 5314 */	NdrFcShort( 0x0 ),	/* 0 */

	/* Parameter lMediaType */

/* 5316 */	NdrFcShort( 0x48 ),	/* Flags:  in, base type, */
/* 5318 */	NdrFcShort( 0x4 ),	/* x86 Stack size/offset = 4 */
/* 5320 */	0x8,		/* FC_LONG */
			0x0,		/* 0 */

	/* Parameter lCookie */

/* 5322 */	NdrFcShort( 0x48 ),	/* Flags:  in, base type, */
/* 5324 */	NdrFcShort( 0x8 ),	/* x86 Stack size/offset = 8 */
/* 5326 */	0x8,		/* FC_LONG */
			0x0,		/* 0 */

	/* Return value */

/* 5328 */	NdrFcShort( 0x70 ),	/* Flags:  out, return, base type, */
/* 5330 */	NdrFcShort( 0xc ),	/* x86 Stack size/offset = 12 */
/* 5332 */	0x8,		/* FC_LONG */
			0x0,		/* 0 */

	/* Procedure put_EncryptionKey */

/* 5334 */	0x33,		/* FC_AUTO_HANDLE */
			0x6c,		/* Old Flags:  object, Oi2 */
/* 5336 */	NdrFcLong( 0x0 ),	/* 0 */
/* 5340 */	NdrFcShort( 0x16 ),	/* 22 */
/* 5342 */	NdrFcShort( 0x10 ),	/* x86 Stack size/offset = 16 */
/* 5344 */	NdrFcShort( 0x8 ),	/* 8 */
/* 5346 */	NdrFcShort( 0x8 ),	/* 8 */
/* 5348 */	0x46,		/* Oi2 Flags:  clt must size, has return, has ext, */
			0x3,		/* 3 */
/* 5350 */	0x8,		/* 8 */
			0x5,		/* Ext Flags:  new corr desc, srv corr check, */
/* 5352 */	NdrFcShort( 0x0 ),	/* 0 */
/* 5354 */	NdrFcShort( 0x1 ),	/* 1 */
/* 5356 */	NdrFcShort( 0x0 ),	/* 0 */

	/* Parameter lMediaType */

/* 5358 */	NdrFcShort( 0x48 ),	/* Flags:  in, base type, */
/* 5360 */	NdrFcShort( 0x4 ),	/* x86 Stack size/offset = 4 */
/* 5362 */	0x8,		/* FC_LONG */
			0x0,		/* 0 */

	/* Parameter EncryptionKey */

/* 5364 */	NdrFcShort( 0x8b ),	/* Flags:  must size, must free, in, by val, */
/* 5366 */	NdrFcShort( 0x8 ),	/* x86 Stack size/offset = 8 */
/* 5368 */	NdrFcShort( 0x20 ),	/* Type Offset=32 */

	/* Return value */

/* 5370 */	NdrFcShort( 0x70 ),	/* Flags:  out, return, base type, */
/* 5372 */	NdrFcShort( 0xc ),	/* x86 Stack size/offset = 12 */
/* 5374 */	0x8,		/* FC_LONG */
			0x0,		/* 0 */

	/* Procedure SendInfo */

/* 5376 */	0x33,		/* FC_AUTO_HANDLE */
			0x6c,		/* Old Flags:  object, Oi2 */
/* 5378 */	NdrFcLong( 0x0 ),	/* 0 */
/* 5382 */	NdrFcShort( 0x17 ),	/* 23 */
/* 5384 */	NdrFcShort( 0x14 ),	/* x86 Stack size/offset = 20 */
/* 5386 */	NdrFcShort( 0x8 ),	/* 8 */
/* 5388 */	NdrFcShort( 0x8 ),	/* 8 */
/* 5390 */	0x46,		/* Oi2 Flags:  clt must size, has return, has ext, */
			0x4,		/* 4 */
/* 5392 */	0x8,		/* 8 */
			0x5,		/* Ext Flags:  new corr desc, srv corr check, */
/* 5394 */	NdrFcShort( 0x0 ),	/* 0 */
/* 5396 */	NdrFcShort( 0x2 ),	/* 2 */
/* 5398 */	NdrFcShort( 0x0 ),	/* 0 */

	/* Parameter bstrInfoHeader */

/* 5400 */	NdrFcShort( 0x8b ),	/* Flags:  must size, must free, in, by val, */
/* 5402 */	NdrFcShort( 0x4 ),	/* x86 Stack size/offset = 4 */
/* 5404 */	NdrFcShort( 0x20 ),	/* Type Offset=32 */

	/* Parameter bstrInfo */

/* 5406 */	NdrFcShort( 0x8b ),	/* Flags:  must size, must free, in, by val, */
/* 5408 */	NdrFcShort( 0x8 ),	/* x86 Stack size/offset = 8 */
/* 5410 */	NdrFcShort( 0x20 ),	/* Type Offset=32 */

	/* Parameter lCookie */

/* 5412 */	NdrFcShort( 0x48 ),	/* Flags:  in, base type, */
/* 5414 */	NdrFcShort( 0xc ),	/* x86 Stack size/offset = 12 */
/* 5416 */	0x8,		/* FC_LONG */
			0x0,		/* 0 */

	/* Return value */

/* 5418 */	NdrFcShort( 0x70 ),	/* Flags:  out, return, base type, */
/* 5420 */	NdrFcShort( 0x10 ),	/* x86 Stack size/offset = 16 */
/* 5422 */	0x8,		/* FC_LONG */
			0x0,		/* 0 */

	/* Procedure put_PreferredSecurityLevel */

/* 5424 */	0x33,		/* FC_AUTO_HANDLE */
			0x6c,		/* Old Flags:  object, Oi2 */
/* 5426 */	NdrFcLong( 0x0 ),	/* 0 */
/* 5430 */	NdrFcShort( 0x18 ),	/* 24 */
/* 5432 */	NdrFcShort( 0x10 ),	/* x86 Stack size/offset = 16 */
/* 5434 */	NdrFcShort( 0xc ),	/* 12 */
/* 5436 */	NdrFcShort( 0x8 ),	/* 8 */
/* 5438 */	0x44,		/* Oi2 Flags:  has return, has ext, */
			0x3,		/* 3 */
/* 5440 */	0x8,		/* 8 */
			0x1,		/* Ext Flags:  new corr desc, */
/* 5442 */	NdrFcShort( 0x0 ),	/* 0 */
/* 5444 */	NdrFcShort( 0x0 ),	/* 0 */
/* 5446 */	NdrFcShort( 0x0 ),	/* 0 */

	/* Parameter enSecurityType */

/* 5448 */	NdrFcShort( 0x48 ),	/* Flags:  in, base type, */
/* 5450 */	NdrFcShort( 0x4 ),	/* x86 Stack size/offset = 4 */
/* 5452 */	0xd,		/* FC_ENUM16 */
			0x0,		/* 0 */

	/* Parameter enSecurityLevel */

/* 5454 */	NdrFcShort( 0x48 ),	/* Flags:  in, base type, */
/* 5456 */	NdrFcShort( 0x8 ),	/* x86 Stack size/offset = 8 */
/* 5458 */	0xd,		/* FC_ENUM16 */
			0x0,		/* 0 */

	/* Return value */

/* 5460 */	NdrFcShort( 0x70 ),	/* Flags:  out, return, base type, */
/* 5462 */	NdrFcShort( 0xc ),	/* x86 Stack size/offset = 12 */
/* 5464 */	0x8,		/* FC_LONG */
			0x0,		/* 0 */

	/* Procedure get_PreferredSecurityLevel */

/* 5466 */	0x33,		/* FC_AUTO_HANDLE */
			0x6c,		/* Old Flags:  object, Oi2 */
/* 5468 */	NdrFcLong( 0x0 ),	/* 0 */
/* 5472 */	NdrFcShort( 0x19 ),	/* 25 */
/* 5474 */	NdrFcShort( 0x10 ),	/* x86 Stack size/offset = 16 */
/* 5476 */	NdrFcShort( 0x6 ),	/* 6 */
/* 5478 */	NdrFcShort( 0x22 ),	/* 34 */
/* 5480 */	0x44,		/* Oi2 Flags:  has return, has ext, */
			0x3,		/* 3 */
/* 5482 */	0x8,		/* 8 */
			0x1,		/* Ext Flags:  new corr desc, */
/* 5484 */	NdrFcShort( 0x0 ),	/* 0 */
/* 5486 */	NdrFcShort( 0x0 ),	/* 0 */
/* 5488 */	NdrFcShort( 0x0 ),	/* 0 */

	/* Parameter enSecurityType */

/* 5490 */	NdrFcShort( 0x48 ),	/* Flags:  in, base type, */
/* 5492 */	NdrFcShort( 0x4 ),	/* x86 Stack size/offset = 4 */
/* 5494 */	0xd,		/* FC_ENUM16 */
			0x0,		/* 0 */

	/* Parameter penSecurityLevel */

/* 5496 */	NdrFcShort( 0x2010 ),	/* Flags:  out, srv alloc size=8 */
/* 5498 */	NdrFcShort( 0x8 ),	/* x86 Stack size/offset = 8 */
/* 5500 */	NdrFcShort( 0x52 ),	/* Type Offset=82 */

	/* Return value */

/* 5502 */	NdrFcShort( 0x70 ),	/* Flags:  out, return, base type, */
/* 5504 */	NdrFcShort( 0xc ),	/* x86 Stack size/offset = 12 */
/* 5506 */	0x8,		/* FC_LONG */
			0x0,		/* 0 */

	/* Procedure IsSecurityEnabled */

/* 5508 */	0x33,		/* FC_AUTO_HANDLE */
			0x6c,		/* Old Flags:  object, Oi2 */
/* 5510 */	NdrFcLong( 0x0 ),	/* 0 */
/* 5514 */	NdrFcShort( 0x1a ),	/* 26 */
/* 5516 */	NdrFcShort( 0x10 ),	/* x86 Stack size/offset = 16 */
/* 5518 */	NdrFcShort( 0x6 ),	/* 6 */
/* 5520 */	NdrFcShort( 0x22 ),	/* 34 */
/* 5522 */	0x44,		/* Oi2 Flags:  has return, has ext, */
			0x3,		/* 3 */
/* 5524 */	0x8,		/* 8 */
			0x1,		/* Ext Flags:  new corr desc, */
/* 5526 */	NdrFcShort( 0x0 ),	/* 0 */
/* 5528 */	NdrFcShort( 0x0 ),	/* 0 */
/* 5530 */	NdrFcShort( 0x0 ),	/* 0 */

	/* Parameter enSecurityType */

/* 5532 */	NdrFcShort( 0x48 ),	/* Flags:  in, base type, */
/* 5534 */	NdrFcShort( 0x4 ),	/* x86 Stack size/offset = 4 */
/* 5536 */	0xd,		/* FC_ENUM16 */
			0x0,		/* 0 */

	/* Parameter pfSecurityEnabled */

/* 5538 */	NdrFcShort( 0x2150 ),	/* Flags:  out, base type, simple ref, srv alloc size=8 */
/* 5540 */	NdrFcShort( 0x8 ),	/* x86 Stack size/offset = 8 */
/* 5542 */	0x6,		/* FC_SHORT */
			0x0,		/* 0 */

	/* Return value */

/* 5544 */	NdrFcShort( 0x70 ),	/* Flags:  out, return, base type, */
/* 5546 */	NdrFcShort( 0xc ),	/* x86 Stack size/offset = 12 */
/* 5548 */	0x8,		/* FC_LONG */
			0x0,		/* 0 */

	/* Procedure AnswerWithSessionDescription */

/* 5550 */	0x33,		/* FC_AUTO_HANDLE */
			0x6c,		/* Old Flags:  object, Oi2 */
/* 5552 */	NdrFcLong( 0x0 ),	/* 0 */
/* 5556 */	NdrFcShort( 0x1b ),	/* 27 */
/* 5558 */	NdrFcShort( 0x10 ),	/* x86 Stack size/offset = 16 */
/* 5560 */	NdrFcShort( 0x0 ),	/* 0 */
/* 5562 */	NdrFcShort( 0x8 ),	/* 8 */
/* 5564 */	0x46,		/* Oi2 Flags:  clt must size, has return, has ext, */
			0x3,		/* 3 */
/* 5566 */	0x8,		/* 8 */
			0x5,		/* Ext Flags:  new corr desc, srv corr check, */
/* 5568 */	NdrFcShort( 0x0 ),	/* 0 */
/* 5570 */	NdrFcShort( 0x2 ),	/* 2 */
/* 5572 */	NdrFcShort( 0x0 ),	/* 0 */

	/* Parameter bstrContentType */

/* 5574 */	NdrFcShort( 0x8b ),	/* Flags:  must size, must free, in, by val, */
/* 5576 */	NdrFcShort( 0x4 ),	/* x86 Stack size/offset = 4 */
/* 5578 */	NdrFcShort( 0x20 ),	/* Type Offset=32 */

	/* Parameter bstrSessionDescription */

/* 5580 */	NdrFcShort( 0x8b ),	/* Flags:  must size, must free, in, by val, */
/* 5582 */	NdrFcShort( 0x8 ),	/* x86 Stack size/offset = 8 */
/* 5584 */	NdrFcShort( 0x20 ),	/* Type Offset=32 */

	/* Return value */

/* 5586 */	NdrFcShort( 0x70 ),	/* Flags:  out, return, base type, */
/* 5588 */	NdrFcShort( 0xc ),	/* x86 Stack size/offset = 12 */
/* 5590 */	0x8,		/* FC_LONG */
			0x0,		/* 0 */

	/* Procedure ReInviteWithSessionDescription */

/* 5592 */	0x33,		/* FC_AUTO_HANDLE */
			0x6c,		/* Old Flags:  object, Oi2 */
/* 5594 */	NdrFcLong( 0x0 ),	/* 0 */
/* 5598 */	NdrFcShort( 0x1c ),	/* 28 */
/* 5600 */	NdrFcShort( 0x14 ),	/* x86 Stack size/offset = 20 */
/* 5602 */	NdrFcShort( 0x8 ),	/* 8 */
/* 5604 */	NdrFcShort( 0x8 ),	/* 8 */
/* 5606 */	0x46,		/* Oi2 Flags:  clt must size, has return, has ext, */
			0x4,		/* 4 */
/* 5608 */	0x8,		/* 8 */
			0x5,		/* Ext Flags:  new corr desc, srv corr check, */
/* 5610 */	NdrFcShort( 0x0 ),	/* 0 */
/* 5612 */	NdrFcShort( 0x2 ),	/* 2 */
/* 5614 */	NdrFcShort( 0x0 ),	/* 0 */

	/* Parameter bstrContentType */

/* 5616 */	NdrFcShort( 0x8b ),	/* Flags:  must size, must free, in, by val, */
/* 5618 */	NdrFcShort( 0x4 ),	/* x86 Stack size/offset = 4 */
/* 5620 */	NdrFcShort( 0x20 ),	/* Type Offset=32 */

	/* Parameter bstrSessionDescription */

/* 5622 */	NdrFcShort( 0x8b ),	/* Flags:  must size, must free, in, by val, */
/* 5624 */	NdrFcShort( 0x8 ),	/* x86 Stack size/offset = 8 */
/* 5626 */	NdrFcShort( 0x20 ),	/* Type Offset=32 */

	/* Parameter lCookie */

/* 5628 */	NdrFcShort( 0x48 ),	/* Flags:  in, base type, */
/* 5630 */	NdrFcShort( 0xc ),	/* x86 Stack size/offset = 12 */
/* 5632 */	0x8,		/* FC_LONG */
			0x0,		/* 0 */

	/* Return value */

/* 5634 */	NdrFcShort( 0x70 ),	/* Flags:  out, return, base type, */
/* 5636 */	NdrFcShort( 0x10 ),	/* x86 Stack size/offset = 16 */
/* 5638 */	0x8,		/* FC_LONG */
			0x0,		/* 0 */

	/* Procedure AddParticipantEx */

/* 5640 */	0x33,		/* FC_AUTO_HANDLE */
			0x6c,		/* Old Flags:  object, Oi2 */
/* 5642 */	NdrFcLong( 0x0 ),	/* 0 */
/* 5646 */	NdrFcShort( 0x1d ),	/* 29 */
/* 5648 */	NdrFcShort( 0x18 ),	/* x86 Stack size/offset = 24 */
/* 5650 */	NdrFcShort( 0x0 ),	/* 0 */
/* 5652 */	NdrFcShort( 0x8 ),	/* 8 */
/* 5654 */	0x47,		/* Oi2 Flags:  srv must size, clt must size, has return, has ext, */
			0x5,		/* 5 */
/* 5656 */	0x8,		/* 8 */
			0x5,		/* Ext Flags:  new corr desc, srv corr check, */
/* 5658 */	NdrFcShort( 0x0 ),	/* 0 */
/* 5660 */	NdrFcShort( 0x3 ),	/* 3 */
/* 5662 */	NdrFcShort( 0x0 ),	/* 0 */

	/* Parameter bstrAddress */

/* 5664 */	NdrFcShort( 0x8b ),	/* Flags:  must size, must free, in, by val, */
/* 5666 */	NdrFcShort( 0x4 ),	/* x86 Stack size/offset = 4 */
/* 5668 */	NdrFcShort( 0x20 ),	/* Type Offset=32 */

	/* Parameter bstrName */

/* 5670 */	NdrFcShort( 0x8b ),	/* Flags:  must size, must free, in, by val, */
/* 5672 */	NdrFcShort( 0x8 ),	/* x86 Stack size/offset = 8 */
/* 5674 */	NdrFcShort( 0x20 ),	/* Type Offset=32 */

	/* Parameter bstrDeviceID */

/* 5676 */	NdrFcShort( 0x8b ),	/* Flags:  must size, must free, in, by val, */
/* 5678 */	NdrFcShort( 0xc ),	/* x86 Stack size/offset = 12 */
/* 5680 */	NdrFcShort( 0x20 ),	/* Type Offset=32 */

	/* Parameter ppParticipant */

/* 5682 */	NdrFcShort( 0x13 ),	/* Flags:  must size, must free, out, */
/* 5684 */	NdrFcShort( 0x10 ),	/* x86 Stack size/offset = 16 */
/* 5686 */	NdrFcShort( 0x5e2 ),	/* Type Offset=1506 */

	/* Return value */

/* 5688 */	NdrFcShort( 0x70 ),	/* Flags:  out, return, base type, */
/* 5690 */	NdrFcShort( 0x14 ),	/* x86 Stack size/offset = 20 */
/* 5692 */	0x8,		/* FC_LONG */
			0x0,		/* 0 */

	/* Procedure Hold */

/* 5694 */	0x33,		/* FC_AUTO_HANDLE */
			0x6c,		/* Old Flags:  object, Oi2 */
/* 5696 */	NdrFcLong( 0x0 ),	/* 0 */
/* 5700 */	NdrFcShort( 0x3 ),	/* 3 */
/* 5702 */	NdrFcShort( 0xc ),	/* x86 Stack size/offset = 12 */
/* 5704 */	NdrFcShort( 0x8 ),	/* 8 */
/* 5706 */	NdrFcShort( 0x8 ),	/* 8 */
/* 5708 */	0x44,		/* Oi2 Flags:  has return, has ext, */
			0x2,		/* 2 */
/* 5710 */	0x8,		/* 8 */
			0x1,		/* Ext Flags:  new corr desc, */
/* 5712 */	NdrFcShort( 0x0 ),	/* 0 */
/* 5714 */	NdrFcShort( 0x0 ),	/* 0 */
/* 5716 */	NdrFcShort( 0x0 ),	/* 0 */

	/* Parameter lCookie */

/* 5718 */	NdrFcShort( 0x48 ),	/* Flags:  in, base type, */
/* 5720 */	NdrFcShort( 0x4 ),	/* x86 Stack size/offset = 4 */
/* 5722 */	0x8,		/* FC_LONG */
			0x0,		/* 0 */

	/* Return value */

/* 5724 */	NdrFcShort( 0x70 ),	/* Flags:  out, return, base type, */
/* 5726 */	NdrFcShort( 0x8 ),	/* x86 Stack size/offset = 8 */
/* 5728 */	0x8,		/* FC_LONG */
			0x0,		/* 0 */

	/* Procedure UnHold */

/* 5730 */	0x33,		/* FC_AUTO_HANDLE */
			0x6c,		/* Old Flags:  object, Oi2 */
/* 5732 */	NdrFcLong( 0x0 ),	/* 0 */
/* 5736 */	NdrFcShort( 0x4 ),	/* 4 */
/* 5738 */	NdrFcShort( 0xc ),	/* x86 Stack size/offset = 12 */
/* 5740 */	NdrFcShort( 0x8 ),	/* 8 */
/* 5742 */	NdrFcShort( 0x8 ),	/* 8 */
/* 5744 */	0x44,		/* Oi2 Flags:  has return, has ext, */
			0x2,		/* 2 */
/* 5746 */	0x8,		/* 8 */
			0x1,		/* Ext Flags:  new corr desc, */
/* 5748 */	NdrFcShort( 0x0 ),	/* 0 */
/* 5750 */	NdrFcShort( 0x0 ),	/* 0 */
/* 5752 */	NdrFcShort( 0x0 ),	/* 0 */

	/* Parameter lCookie */

/* 5754 */	NdrFcShort( 0x48 ),	/* Flags:  in, base type, */
/* 5756 */	NdrFcShort( 0x4 ),	/* x86 Stack size/offset = 4 */
/* 5758 */	0x8,		/* FC_LONG */
			0x0,		/* 0 */

	/* Return value */

/* 5760 */	NdrFcShort( 0x70 ),	/* Flags:  out, return, base type, */
/* 5762 */	NdrFcShort( 0x8 ),	/* x86 Stack size/offset = 8 */
/* 5764 */	0x8,		/* FC_LONG */
			0x0,		/* 0 */

	/* Procedure Forward */

/* 5766 */	0x33,		/* FC_AUTO_HANDLE */
			0x6c,		/* Old Flags:  object, Oi2 */
/* 5768 */	NdrFcLong( 0x0 ),	/* 0 */
/* 5772 */	NdrFcShort( 0x5 ),	/* 5 */
/* 5774 */	NdrFcShort( 0xc ),	/* x86 Stack size/offset = 12 */
/* 5776 */	NdrFcShort( 0x0 ),	/* 0 */
/* 5778 */	NdrFcShort( 0x8 ),	/* 8 */
/* 5780 */	0x46,		/* Oi2 Flags:  clt must size, has return, has ext, */
			0x2,		/* 2 */
/* 5782 */	0x8,		/* 8 */
			0x5,		/* Ext Flags:  new corr desc, srv corr check, */
/* 5784 */	NdrFcShort( 0x0 ),	/* 0 */
/* 5786 */	NdrFcShort( 0x1 ),	/* 1 */
/* 5788 */	NdrFcShort( 0x0 ),	/* 0 */

	/* Parameter bstrForwardToURI */

/* 5790 */	NdrFcShort( 0x8b ),	/* Flags:  must size, must free, in, by val, */
/* 5792 */	NdrFcShort( 0x4 ),	/* x86 Stack size/offset = 4 */
/* 5794 */	NdrFcShort( 0x20 ),	/* Type Offset=32 */

	/* Return value */

/* 5796 */	NdrFcShort( 0x70 ),	/* Flags:  out, return, base type, */
/* 5798 */	NdrFcShort( 0x8 ),	/* x86 Stack size/offset = 8 */
/* 5800 */	0x8,		/* FC_LONG */
			0x0,		/* 0 */

	/* Procedure Refer */

/* 5802 */	0x33,		/* FC_AUTO_HANDLE */
			0x6c,		/* Old Flags:  object, Oi2 */
/* 5804 */	NdrFcLong( 0x0 ),	/* 0 */
/* 5808 */	NdrFcShort( 0x6 ),	/* 6 */
/* 5810 */	NdrFcShort( 0x10 ),	/* x86 Stack size/offset = 16 */
/* 5812 */	NdrFcShort( 0x0 ),	/* 0 */
/* 5814 */	NdrFcShort( 0x8 ),	/* 8 */
/* 5816 */	0x46,		/* Oi2 Flags:  clt must size, has return, has ext, */
			0x3,		/* 3 */
/* 5818 */	0x8,		/* 8 */
			0x5,		/* Ext Flags:  new corr desc, srv corr check, */
/* 5820 */	NdrFcShort( 0x0 ),	/* 0 */
/* 5822 */	NdrFcShort( 0x2 ),	/* 2 */
/* 5824 */	NdrFcShort( 0x0 ),	/* 0 */

	/* Parameter bstrReferToURI */

/* 5826 */	NdrFcShort( 0x8b ),	/* Flags:  must size, must free, in, by val, */
/* 5828 */	NdrFcShort( 0x4 ),	/* x86 Stack size/offset = 4 */
/* 5830 */	NdrFcShort( 0x20 ),	/* Type Offset=32 */

	/* Parameter bstrReferCookie */

/* 5832 */	NdrFcShort( 0x8b ),	/* Flags:  must size, must free, in, by val, */
/* 5834 */	NdrFcShort( 0x8 ),	/* x86 Stack size/offset = 8 */
/* 5836 */	NdrFcShort( 0x20 ),	/* Type Offset=32 */

	/* Return value */

/* 5838 */	NdrFcShort( 0x70 ),	/* Flags:  out, return, base type, */
/* 5840 */	NdrFcShort( 0xc ),	/* x86 Stack size/offset = 12 */
/* 5842 */	0x8,		/* FC_LONG */
			0x0,		/* 0 */

	/* Procedure put_ReferredByURI */

/* 5844 */	0x33,		/* FC_AUTO_HANDLE */
			0x6c,		/* Old Flags:  object, Oi2 */
/* 5846 */	NdrFcLong( 0x0 ),	/* 0 */
/* 5850 */	NdrFcShort( 0x7 ),	/* 7 */
/* 5852 */	NdrFcShort( 0xc ),	/* x86 Stack size/offset = 12 */
/* 5854 */	NdrFcShort( 0x0 ),	/* 0 */
/* 5856 */	NdrFcShort( 0x8 ),	/* 8 */
/* 5858 */	0x46,		/* Oi2 Flags:  clt must size, has return, has ext, */
			0x2,		/* 2 */
/* 5860 */	0x8,		/* 8 */
			0x5,		/* Ext Flags:  new corr desc, srv corr check, */
/* 5862 */	NdrFcShort( 0x0 ),	/* 0 */
/* 5864 */	NdrFcShort( 0x1 ),	/* 1 */
/* 5866 */	NdrFcShort( 0x0 ),	/* 0 */

	/* Parameter bstrReferredByURI */

/* 5868 */	NdrFcShort( 0x8b ),	/* Flags:  must size, must free, in, by val, */
/* 5870 */	NdrFcShort( 0x4 ),	/* x86 Stack size/offset = 4 */
/* 5872 */	NdrFcShort( 0x20 ),	/* Type Offset=32 */

	/* Return value */

/* 5874 */	NdrFcShort( 0x70 ),	/* Flags:  out, return, base type, */
/* 5876 */	NdrFcShort( 0x8 ),	/* x86 Stack size/offset = 8 */
/* 5878 */	0x8,		/* FC_LONG */
			0x0,		/* 0 */

	/* Procedure put_ReferCookie */

/* 5880 */	0x33,		/* FC_AUTO_HANDLE */
			0x6c,		/* Old Flags:  object, Oi2 */
/* 5882 */	NdrFcLong( 0x0 ),	/* 0 */
/* 5886 */	NdrFcShort( 0x9 ),	/* 9 */
/* 5888 */	NdrFcShort( 0xc ),	/* x86 Stack size/offset = 12 */
/* 5890 */	NdrFcShort( 0x0 ),	/* 0 */
/* 5892 */	NdrFcShort( 0x8 ),	/* 8 */
/* 5894 */	0x46,		/* Oi2 Flags:  clt must size, has return, has ext, */
			0x2,		/* 2 */
/* 5896 */	0x8,		/* 8 */
			0x5,		/* Ext Flags:  new corr desc, srv corr check, */
/* 5898 */	NdrFcShort( 0x0 ),	/* 0 */
/* 5900 */	NdrFcShort( 0x1 ),	/* 1 */
/* 5902 */	NdrFcShort( 0x0 ),	/* 0 */

	/* Parameter bstrReferCookie */

/* 5904 */	NdrFcShort( 0x8b ),	/* Flags:  must size, must free, in, by val, */
/* 5906 */	NdrFcShort( 0x4 ),	/* x86 Stack size/offset = 4 */
/* 5908 */	NdrFcShort( 0x20 ),	/* Type Offset=32 */

	/* Return value */

/* 5910 */	NdrFcShort( 0x70 ),	/* Flags:  out, return, base type, */
/* 5912 */	NdrFcShort( 0x8 ),	/* x86 Stack size/offset = 8 */
/* 5914 */	0x8,		/* FC_LONG */
			0x0,		/* 0 */

	/* Procedure get_ReferCookie */


	/* Procedure get_StatusText */


	/* Procedure get_Value */


	/* Procedure get_InfoHeader */


	/* Procedure get_StatusText */


	/* Procedure get_Message */


	/* Procedure get_StatusText */


	/* Procedure get_StatusText */


	/* Procedure get_StatusText */


	/* Procedure get_StatusText */


	/* Procedure get_ReferCookie */

/* 5916 */	0x33,		/* FC_AUTO_HANDLE */
			0x6c,		/* Old Flags:  object, Oi2 */
/* 5918 */	NdrFcLong( 0x0 ),	/* 0 */
/* 5922 */	NdrFcShort( 0xa ),	/* 10 */
/* 5924 */	NdrFcShort( 0xc ),	/* x86 Stack size/offset = 12 */
/* 5926 */	NdrFcShort( 0x0 ),	/* 0 */
/* 5928 */	NdrFcShort( 0x8 ),	/* 8 */
/* 5930 */	0x45,		/* Oi2 Flags:  srv must size, has return, has ext, */
			0x2,		/* 2 */
/* 5932 */	0x8,		/* 8 */
			0x3,		/* Ext Flags:  new corr desc, clt corr check, */
/* 5934 */	NdrFcShort( 0x1 ),	/* 1 */
/* 5936 */	NdrFcShort( 0x0 ),	/* 0 */
/* 5938 */	NdrFcShort( 0x0 ),	/* 0 */

	/* Parameter pbstrReferCookie */


	/* Parameter pbstrStatusText */


	/* Parameter pbstrValue */


	/* Parameter pbstrInfoHeader */


	/* Parameter pbstrStatusText */


	/* Parameter pbstrMessage */


	/* Parameter pbstrStatusText */


	/* Parameter pbstrStatusText */


	/* Parameter pbstrStatusText */


	/* Parameter pbstrStatusText */


	/* Parameter pbstrReferCookie */

/* 5940 */	NdrFcShort( 0x2113 ),	/* Flags:  must size, must free, out, simple ref, srv alloc size=8 */
/* 5942 */	NdrFcShort( 0x4 ),	/* x86 Stack size/offset = 4 */
/* 5944 */	NdrFcShort( 0x46a ),	/* Type Offset=1130 */

	/* Return value */


	/* Return value */


	/* Return value */


	/* Return value */


	/* Return value */


	/* Return value */


	/* Return value */


	/* Return value */


	/* Return value */


	/* Return value */


	/* Return value */

/* 5946 */	NdrFcShort( 0x70 ),	/* Flags:  out, return, base type, */
/* 5948 */	NdrFcShort( 0x8 ),	/* x86 Stack size/offset = 8 */
/* 5950 */	0x8,		/* FC_LONG */
			0x0,		/* 0 */

	/* Procedure get_IsReferred */

/* 5952 */	0x33,		/* FC_AUTO_HANDLE */
			0x6c,		/* Old Flags:  object, Oi2 */
/* 5954 */	NdrFcLong( 0x0 ),	/* 0 */
/* 5958 */	NdrFcShort( 0xb ),	/* 11 */
/* 5960 */	NdrFcShort( 0xc ),	/* x86 Stack size/offset = 12 */
/* 5962 */	NdrFcShort( 0x0 ),	/* 0 */
/* 5964 */	NdrFcShort( 0x22 ),	/* 34 */
/* 5966 */	0x44,		/* Oi2 Flags:  has return, has ext, */
			0x2,		/* 2 */
/* 5968 */	0x8,		/* 8 */
			0x1,		/* Ext Flags:  new corr desc, */
/* 5970 */	NdrFcShort( 0x0 ),	/* 0 */
/* 5972 */	NdrFcShort( 0x0 ),	/* 0 */
/* 5974 */	NdrFcShort( 0x0 ),	/* 0 */

	/* Parameter pfIsReferred */

/* 5976 */	NdrFcShort( 0x2150 ),	/* Flags:  out, base type, simple ref, srv alloc size=8 */
/* 5978 */	NdrFcShort( 0x4 ),	/* x86 Stack size/offset = 4 */
/* 5980 */	0x6,		/* FC_SHORT */
			0x0,		/* 0 */

	/* Return value */

/* 5982 */	NdrFcShort( 0x70 ),	/* Flags:  out, return, base type, */
/* 5984 */	NdrFcShort( 0x8 ),	/* x86 Stack size/offset = 8 */
/* 5986 */	0x8,		/* FC_LONG */
			0x0,		/* 0 */

	/* Procedure get_Removable */

/* 5988 */	0x33,		/* FC_AUTO_HANDLE */
			0x6c,		/* Old Flags:  object, Oi2 */
/* 5990 */	NdrFcLong( 0x0 ),	/* 0 */
/* 5994 */	NdrFcShort( 0x5 ),	/* 5 */
/* 5996 */	NdrFcShort( 0xc ),	/* x86 Stack size/offset = 12 */
/* 5998 */	NdrFcShort( 0x0 ),	/* 0 */
/* 6000 */	NdrFcShort( 0x22 ),	/* 34 */
/* 6002 */	0x44,		/* Oi2 Flags:  has return, has ext, */
			0x2,		/* 2 */
/* 6004 */	0x8,		/* 8 */
			0x1,		/* Ext Flags:  new corr desc, */
/* 6006 */	NdrFcShort( 0x0 ),	/* 0 */
/* 6008 */	NdrFcShort( 0x0 ),	/* 0 */
/* 6010 */	NdrFcShort( 0x0 ),	/* 0 */

	/* Parameter pfRemovable */

/* 6012 */	NdrFcShort( 0x2150 ),	/* Flags:  out, base type, simple ref, srv alloc size=8 */
/* 6014 */	NdrFcShort( 0x4 ),	/* x86 Stack size/offset = 4 */
/* 6016 */	0x6,		/* FC_SHORT */
			0x0,		/* 0 */

	/* Return value */

/* 6018 */	NdrFcShort( 0x70 ),	/* Flags:  out, return, base type, */
/* 6020 */	NdrFcShort( 0x8 ),	/* x86 Stack size/offset = 8 */
/* 6022 */	0x8,		/* FC_LONG */
			0x0,		/* 0 */

	/* Procedure get_State */

/* 6024 */	0x33,		/* FC_AUTO_HANDLE */
			0x6c,		/* Old Flags:  object, Oi2 */
/* 6026 */	NdrFcLong( 0x0 ),	/* 0 */
/* 6030 */	NdrFcShort( 0x6 ),	/* 6 */
/* 6032 */	NdrFcShort( 0xc ),	/* x86 Stack size/offset = 12 */
/* 6034 */	NdrFcShort( 0x0 ),	/* 0 */
/* 6036 */	NdrFcShort( 0x22 ),	/* 34 */
/* 6038 */	0x44,		/* Oi2 Flags:  has return, has ext, */
			0x2,		/* 2 */
/* 6040 */	0x8,		/* 8 */
			0x1,		/* Ext Flags:  new corr desc, */
/* 6042 */	NdrFcShort( 0x0 ),	/* 0 */
/* 6044 */	NdrFcShort( 0x0 ),	/* 0 */
/* 6046 */	NdrFcShort( 0x0 ),	/* 0 */

	/* Parameter penState */

/* 6048 */	NdrFcShort( 0x2010 ),	/* Flags:  out, srv alloc size=8 */
/* 6050 */	NdrFcShort( 0x4 ),	/* x86 Stack size/offset = 4 */
/* 6052 */	NdrFcShort( 0x52 ),	/* Type Offset=82 */

	/* Return value */

/* 6054 */	NdrFcShort( 0x70 ),	/* Flags:  out, return, base type, */
/* 6056 */	NdrFcShort( 0x8 ),	/* x86 Stack size/offset = 8 */
/* 6058 */	0x8,		/* FC_LONG */
			0x0,		/* 0 */

	/* Procedure get_Session */


	/* Procedure get_Session */


	/* Procedure get_Session */


	/* Procedure get_Session */

/* 6060 */	0x33,		/* FC_AUTO_HANDLE */
			0x6c,		/* Old Flags:  object, Oi2 */
/* 6062 */	NdrFcLong( 0x0 ),	/* 0 */
/* 6066 */	NdrFcShort( 0x7 ),	/* 7 */
/* 6068 */	NdrFcShort( 0xc ),	/* x86 Stack size/offset = 12 */
/* 6070 */	NdrFcShort( 0x0 ),	/* 0 */
/* 6072 */	NdrFcShort( 0x8 ),	/* 8 */
/* 6074 */	0x45,		/* Oi2 Flags:  srv must size, has return, has ext, */
			0x2,		/* 2 */
/* 6076 */	0x8,		/* 8 */
			0x1,		/* Ext Flags:  new corr desc, */
/* 6078 */	NdrFcShort( 0x0 ),	/* 0 */
/* 6080 */	NdrFcShort( 0x0 ),	/* 0 */
/* 6082 */	NdrFcShort( 0x0 ),	/* 0 */

	/* Parameter ppSession */


	/* Parameter ppSession */


	/* Parameter ppSession */


	/* Parameter ppSession */

/* 6084 */	NdrFcShort( 0x13 ),	/* Flags:  must size, must free, out, */
/* 6086 */	NdrFcShort( 0x4 ),	/* x86 Stack size/offset = 4 */
/* 6088 */	NdrFcShort( 0x5f8 ),	/* Type Offset=1528 */

	/* Return value */


	/* Return value */


	/* Return value */


	/* Return value */

/* 6090 */	NdrFcShort( 0x70 ),	/* Flags:  out, return, base type, */
/* 6092 */	NdrFcShort( 0x8 ),	/* x86 Stack size/offset = 8 */
/* 6094 */	0x8,		/* FC_LONG */
			0x0,		/* 0 */

	/* Procedure get_EventType */


	/* Procedure get_EventType */


	/* Procedure get_EventType */

/* 6096 */	0x33,		/* FC_AUTO_HANDLE */
			0x6c,		/* Old Flags:  object, Oi2 */
/* 6098 */	NdrFcLong( 0x0 ),	/* 0 */
/* 6102 */	NdrFcShort( 0x7 ),	/* 7 */
/* 6104 */	NdrFcShort( 0xc ),	/* x86 Stack size/offset = 12 */
/* 6106 */	NdrFcShort( 0x0 ),	/* 0 */
/* 6108 */	NdrFcShort( 0x22 ),	/* 34 */
/* 6110 */	0x44,		/* Oi2 Flags:  has return, has ext, */
			0x2,		/* 2 */
/* 6112 */	0x8,		/* 8 */
			0x1,		/* Ext Flags:  new corr desc, */
/* 6114 */	NdrFcShort( 0x0 ),	/* 0 */
/* 6116 */	NdrFcShort( 0x0 ),	/* 0 */
/* 6118 */	NdrFcShort( 0x0 ),	/* 0 */

	/* Parameter pEventType */


	/* Parameter penEventType */


	/* Parameter pEventType */

/* 6120 */	NdrFcShort( 0x2010 ),	/* Flags:  out, srv alloc size=8 */
/* 6122 */	NdrFcShort( 0x4 ),	/* x86 Stack size/offset = 4 */
/* 6124 */	NdrFcShort( 0x52 ),	/* Type Offset=82 */

	/* Return value */


	/* Return value */


	/* Return value */

/* 6126 */	NdrFcShort( 0x70 ),	/* Flags:  out, return, base type, */
/* 6128 */	NdrFcShort( 0x8 ),	/* x86 Stack size/offset = 8 */
/* 6130 */	0x8,		/* FC_LONG */
			0x0,		/* 0 */

	/* Procedure get_Profile */

/* 6132 */	0x33,		/* FC_AUTO_HANDLE */
			0x6c,		/* Old Flags:  object, Oi2 */
/* 6134 */	NdrFcLong( 0x0 ),	/* 0 */
/* 6138 */	NdrFcShort( 0x8 ),	/* 8 */
/* 6140 */	NdrFcShort( 0xc ),	/* x86 Stack size/offset = 12 */
/* 6142 */	NdrFcShort( 0x0 ),	/* 0 */
/* 6144 */	NdrFcShort( 0x8 ),	/* 8 */
/* 6146 */	0x45,		/* Oi2 Flags:  srv must size, has return, has ext, */
			0x2,		/* 2 */
/* 6148 */	0x8,		/* 8 */
			0x1,		/* Ext Flags:  new corr desc, */
/* 6150 */	NdrFcShort( 0x0 ),	/* 0 */
/* 6152 */	NdrFcShort( 0x0 ),	/* 0 */
/* 6154 */	NdrFcShort( 0x0 ),	/* 0 */

	/* Parameter ppProfile */

/* 6156 */	NdrFcShort( 0x13 ),	/* Flags:  must size, must free, out, */
/* 6158 */	NdrFcShort( 0x4 ),	/* x86 Stack size/offset = 4 */
/* 6160 */	NdrFcShort( 0x60e ),	/* Type Offset=1550 */

	/* Return value */

/* 6162 */	NdrFcShort( 0x70 ),	/* Flags:  out, return, base type, */
/* 6164 */	NdrFcShort( 0x8 ),	/* x86 Stack size/offset = 8 */
/* 6166 */	0x8,		/* FC_LONG */
			0x0,		/* 0 */

	/* Procedure get_Profile */


	/* Procedure get_Profile */

/* 6168 */	0x33,		/* FC_AUTO_HANDLE */
			0x6c,		/* Old Flags:  object, Oi2 */
/* 6170 */	NdrFcLong( 0x0 ),	/* 0 */
/* 6174 */	NdrFcShort( 0x7 ),	/* 7 */
/* 6176 */	NdrFcShort( 0xc ),	/* x86 Stack size/offset = 12 */
/* 6178 */	NdrFcShort( 0x0 ),	/* 0 */
/* 6180 */	NdrFcShort( 0x8 ),	/* 8 */
/* 6182 */	0x45,		/* Oi2 Flags:  srv must size, has return, has ext, */
			0x2,		/* 2 */
/* 6184 */	0x8,		/* 8 */
			0x1,		/* Ext Flags:  new corr desc, */
/* 6186 */	NdrFcShort( 0x0 ),	/* 0 */
/* 6188 */	NdrFcShort( 0x0 ),	/* 0 */
/* 6190 */	NdrFcShort( 0x0 ),	/* 0 */

	/* Parameter ppProfile */


	/* Parameter ppProfile */

/* 6192 */	NdrFcShort( 0x13 ),	/* Flags:  must size, must free, out, */
/* 6194 */	NdrFcShort( 0x4 ),	/* x86 Stack size/offset = 4 */
/* 6196 */	NdrFcShort( 0x624 ),	/* Type Offset=1572 */

	/* Return value */


	/* Return value */

/* 6198 */	NdrFcShort( 0x70 ),	/* Flags:  out, return, base type, */
/* 6200 */	NdrFcShort( 0x8 ),	/* x86 Stack size/offset = 8 */
/* 6202 */	0x8,		/* FC_LONG */
			0x0,		/* 0 */

	/* Procedure get_ProposedMedia */


	/* Procedure get_Min */


	/* Procedure get_Cookie */


	/* Procedure get_Cookie */

/* 6204 */	0x33,		/* FC_AUTO_HANDLE */
			0x6c,		/* Old Flags:  object, Oi2 */
/* 6206 */	NdrFcLong( 0x0 ),	/* 0 */
/* 6210 */	NdrFcShort( 0x8 ),	/* 8 */
/* 6212 */	NdrFcShort( 0xc ),	/* x86 Stack size/offset = 12 */
/* 6214 */	NdrFcShort( 0x0 ),	/* 0 */
/* 6216 */	NdrFcShort( 0x24 ),	/* 36 */
/* 6218 */	0x44,		/* Oi2 Flags:  has return, has ext, */
			0x2,		/* 2 */
/* 6220 */	0x8,		/* 8 */
			0x1,		/* Ext Flags:  new corr desc, */
/* 6222 */	NdrFcShort( 0x0 ),	/* 0 */
/* 6224 */	NdrFcShort( 0x0 ),	/* 0 */
/* 6226 */	NdrFcShort( 0x0 ),	/* 0 */

	/* Parameter plMediaTypes */


	/* Parameter plMin */


	/* Parameter plCookie */


	/* Parameter plCookie */

/* 6228 */	NdrFcShort( 0x2150 ),	/* Flags:  out, base type, simple ref, srv alloc size=8 */
/* 6230 */	NdrFcShort( 0x4 ),	/* x86 Stack size/offset = 4 */
/* 6232 */	0x8,		/* FC_LONG */
			0x0,		/* 0 */

	/* Return value */


	/* Return value */


	/* Return value */


	/* Return value */

/* 6234 */	NdrFcShort( 0x70 ),	/* Flags:  out, return, base type, */
/* 6236 */	NdrFcShort( 0x8 ),	/* x86 Stack size/offset = 8 */
/* 6238 */	0x8,		/* FC_LONG */
			0x0,		/* 0 */

	/* Procedure get_State */


	/* Procedure get_Direction */


	/* Procedure get_EventType */

/* 6240 */	0x33,		/* FC_AUTO_HANDLE */
			0x6c,		/* Old Flags:  object, Oi2 */
/* 6242 */	NdrFcLong( 0x0 ),	/* 0 */
/* 6246 */	NdrFcShort( 0xa ),	/* 10 */
/* 6248 */	NdrFcShort( 0xc ),	/* x86 Stack size/offset = 12 */
/* 6250 */	NdrFcShort( 0x0 ),	/* 0 */
/* 6252 */	NdrFcShort( 0x22 ),	/* 34 */
/* 6254 */	0x44,		/* Oi2 Flags:  has return, has ext, */
			0x2,		/* 2 */
/* 6256 */	0x8,		/* 8 */
			0x1,		/* Ext Flags:  new corr desc, */
/* 6258 */	NdrFcShort( 0x0 ),	/* 0 */
/* 6260 */	NdrFcShort( 0x0 ),	/* 0 */
/* 6262 */	NdrFcShort( 0x0 ),	/* 0 */

	/* Parameter pState */


	/* Parameter penDirection */


	/* Parameter pEventType */

/* 6264 */	NdrFcShort( 0x2010 ),	/* Flags:  out, srv alloc size=8 */
/* 6266 */	NdrFcShort( 0x4 ),	/* x86 Stack size/offset = 4 */
/* 6268 */	NdrFcShort( 0x52 ),	/* Type Offset=82 */

	/* Return value */


	/* Return value */


	/* Return value */

/* 6270 */	NdrFcShort( 0x70 ),	/* Flags:  out, return, base type, */
/* 6272 */	NdrFcShort( 0x8 ),	/* x86 Stack size/offset = 8 */
/* 6274 */	0x8,		/* FC_LONG */
			0x0,		/* 0 */

	/* Procedure get_Client */

/* 6276 */	0x33,		/* FC_AUTO_HANDLE */
			0x6c,		/* Old Flags:  object, Oi2 */
/* 6278 */	NdrFcLong( 0x0 ),	/* 0 */
/* 6282 */	NdrFcShort( 0x8 ),	/* 8 */
/* 6284 */	NdrFcShort( 0xc ),	/* x86 Stack size/offset = 12 */
/* 6286 */	NdrFcShort( 0x0 ),	/* 0 */
/* 6288 */	NdrFcShort( 0x8 ),	/* 8 */
/* 6290 */	0x45,		/* Oi2 Flags:  srv must size, has return, has ext, */
			0x2,		/* 2 */
/* 6292 */	0x8,		/* 8 */
			0x1,		/* Ext Flags:  new corr desc, */
/* 6294 */	NdrFcShort( 0x0 ),	/* 0 */
/* 6296 */	NdrFcShort( 0x0 ),	/* 0 */
/* 6298 */	NdrFcShort( 0x0 ),	/* 0 */

	/* Parameter ppClient */

/* 6300 */	NdrFcShort( 0x13 ),	/* Flags:  must size, must free, out, */
/* 6302 */	NdrFcShort( 0x4 ),	/* x86 Stack size/offset = 4 */
/* 6304 */	NdrFcShort( 0x63a ),	/* Type Offset=1594 */

	/* Return value */

/* 6306 */	NdrFcShort( 0x70 ),	/* Flags:  out, return, base type, */
/* 6308 */	NdrFcShort( 0x8 ),	/* x86 Stack size/offset = 8 */
/* 6310 */	0x8,		/* FC_LONG */
			0x0,		/* 0 */

	/* Procedure get_ReferStatus */


	/* Procedure get_EventType */


	/* Procedure get_EventType */


	/* Procedure get_EventType */


	/* Procedure get_State */


	/* Procedure get_State */


	/* Procedure get_State */

/* 6312 */	0x33,		/* FC_AUTO_HANDLE */
			0x6c,		/* Old Flags:  object, Oi2 */
/* 6314 */	NdrFcLong( 0x0 ),	/* 0 */
/* 6318 */	NdrFcShort( 0x8 ),	/* 8 */
/* 6320 */	NdrFcShort( 0xc ),	/* x86 Stack size/offset = 12 */
/* 6322 */	NdrFcShort( 0x0 ),	/* 0 */
/* 6324 */	NdrFcShort( 0x22 ),	/* 34 */
/* 6326 */	0x44,		/* Oi2 Flags:  has return, has ext, */
			0x2,		/* 2 */
/* 6328 */	0x8,		/* 8 */
			0x1,		/* Ext Flags:  new corr desc, */
/* 6330 */	NdrFcShort( 0x0 ),	/* 0 */
/* 6332 */	NdrFcShort( 0x0 ),	/* 0 */
/* 6334 */	NdrFcShort( 0x0 ),	/* 0 */

	/* Parameter penReferStatus */


	/* Parameter pEventType */


	/* Parameter pEventType */


	/* Parameter penEventType */


	/* Parameter penState */


	/* Parameter penState */


	/* Parameter penState */

/* 6336 */	NdrFcShort( 0x2010 ),	/* Flags:  out, srv alloc size=8 */
/* 6338 */	NdrFcShort( 0x4 ),	/* x86 Stack size/offset = 4 */
/* 6340 */	NdrFcShort( 0x52 ),	/* Type Offset=82 */

	/* Return value */


	/* Return value */


	/* Return value */


	/* Return value */


	/* Return value */


	/* Return value */


	/* Return value */

/* 6342 */	NdrFcShort( 0x70 ),	/* Flags:  out, return, base type, */
/* 6344 */	NdrFcShort( 0x8 ),	/* x86 Stack size/offset = 8 */
/* 6346 */	0x8,		/* FC_LONG */
			0x0,		/* 0 */

	/* Procedure get_Cookie */


	/* Procedure get_MediaTypes */

/* 6348 */	0x33,		/* FC_AUTO_HANDLE */
			0x6c,		/* Old Flags:  object, Oi2 */
/* 6350 */	NdrFcLong( 0x0 ),	/* 0 */
/* 6354 */	NdrFcShort( 0xb ),	/* 11 */
/* 6356 */	NdrFcShort( 0xc ),	/* x86 Stack size/offset = 12 */
/* 6358 */	NdrFcShort( 0x0 ),	/* 0 */
/* 6360 */	NdrFcShort( 0x24 ),	/* 36 */
/* 6362 */	0x44,		/* Oi2 Flags:  has return, has ext, */
			0x2,		/* 2 */
/* 6364 */	0x8,		/* 8 */
			0x1,		/* Ext Flags:  new corr desc, */
/* 6366 */	NdrFcShort( 0x0 ),	/* 0 */
/* 6368 */	NdrFcShort( 0x0 ),	/* 0 */
/* 6370 */	NdrFcShort( 0x0 ),	/* 0 */

	/* Parameter plCookie */


	/* Parameter pMediaTypes */

/* 6372 */	NdrFcShort( 0x2150 ),	/* Flags:  out, base type, simple ref, srv alloc size=8 */
/* 6374 */	NdrFcShort( 0x4 ),	/* x86 Stack size/offset = 4 */
/* 6376 */	0x8,		/* FC_LONG */
			0x0,		/* 0 */

	/* Return value */


	/* Return value */

/* 6378 */	NdrFcShort( 0x70 ),	/* Flags:  out, return, base type, */
/* 6380 */	NdrFcShort( 0x8 ),	/* x86 Stack size/offset = 8 */
/* 6382 */	0x8,		/* FC_LONG */
			0x0,		/* 0 */

	/* Procedure get_RemotePreferredSecurityLevel */

/* 6384 */	0x33,		/* FC_AUTO_HANDLE */
			0x6c,		/* Old Flags:  object, Oi2 */
/* 6386 */	NdrFcLong( 0x0 ),	/* 0 */
/* 6390 */	NdrFcShort( 0xc ),	/* 12 */
/* 6392 */	NdrFcShort( 0x10 ),	/* x86 Stack size/offset = 16 */
/* 6394 */	NdrFcShort( 0x6 ),	/* 6 */
/* 6396 */	NdrFcShort( 0x22 ),	/* 34 */
/* 6398 */	0x44,		/* Oi2 Flags:  has return, has ext, */
			0x3,		/* 3 */
/* 6400 */	0x8,		/* 8 */
			0x1,		/* Ext Flags:  new corr desc, */
/* 6402 */	NdrFcShort( 0x0 ),	/* 0 */
/* 6404 */	NdrFcShort( 0x0 ),	/* 0 */
/* 6406 */	NdrFcShort( 0x0 ),	/* 0 */

	/* Parameter enSecurityType */

/* 6408 */	NdrFcShort( 0x48 ),	/* Flags:  in, base type, */
/* 6410 */	NdrFcShort( 0x4 ),	/* x86 Stack size/offset = 4 */
/* 6412 */	0xd,		/* FC_ENUM16 */
			0x0,		/* 0 */

	/* Parameter penSecurityLevel */

/* 6414 */	NdrFcShort( 0x2010 ),	/* Flags:  out, srv alloc size=8 */
/* 6416 */	NdrFcShort( 0x8 ),	/* x86 Stack size/offset = 8 */
/* 6418 */	NdrFcShort( 0x52 ),	/* Type Offset=82 */

	/* Return value */

/* 6420 */	NdrFcShort( 0x70 ),	/* Flags:  out, return, base type, */
/* 6422 */	NdrFcShort( 0xc ),	/* x86 Stack size/offset = 12 */
/* 6424 */	0x8,		/* FC_LONG */
			0x0,		/* 0 */

	/* Procedure get_MoreAvailable */


	/* Procedure get_IsForked */

/* 6426 */	0x33,		/* FC_AUTO_HANDLE */
			0x6c,		/* Old Flags:  object, Oi2 */
/* 6428 */	NdrFcLong( 0x0 ),	/* 0 */
/* 6432 */	NdrFcShort( 0xd ),	/* 13 */
/* 6434 */	NdrFcShort( 0xc ),	/* x86 Stack size/offset = 12 */
/* 6436 */	NdrFcShort( 0x0 ),	/* 0 */
/* 6438 */	NdrFcShort( 0x22 ),	/* 34 */
/* 6440 */	0x44,		/* Oi2 Flags:  has return, has ext, */
			0x2,		/* 2 */
/* 6442 */	0x8,		/* 8 */
			0x1,		/* Ext Flags:  new corr desc, */
/* 6444 */	NdrFcShort( 0x0 ),	/* 0 */
/* 6446 */	NdrFcShort( 0x0 ),	/* 0 */
/* 6448 */	NdrFcShort( 0x0 ),	/* 0 */

	/* Parameter pfMoreAvailable */


	/* Parameter pfIsForked */

/* 6450 */	NdrFcShort( 0x2150 ),	/* Flags:  out, base type, simple ref, srv alloc size=8 */
/* 6452 */	NdrFcShort( 0x4 ),	/* x86 Stack size/offset = 4 */
/* 6454 */	0x6,		/* FC_SHORT */
			0x0,		/* 0 */

	/* Return value */


	/* Return value */

/* 6456 */	NdrFcShort( 0x70 ),	/* Flags:  out, return, base type, */
/* 6458 */	NdrFcShort( 0x8 ),	/* x86 Stack size/offset = 8 */
/* 6460 */	0x8,		/* FC_LONG */
			0x0,		/* 0 */

	/* Procedure GetRemoteSessionDescription */

/* 6462 */	0x33,		/* FC_AUTO_HANDLE */
			0x6c,		/* Old Flags:  object, Oi2 */
/* 6464 */	NdrFcLong( 0x0 ),	/* 0 */
/* 6468 */	NdrFcShort( 0xe ),	/* 14 */
/* 6470 */	NdrFcShort( 0x10 ),	/* x86 Stack size/offset = 16 */
/* 6472 */	NdrFcShort( 0x0 ),	/* 0 */
/* 6474 */	NdrFcShort( 0x8 ),	/* 8 */
/* 6476 */	0x45,		/* Oi2 Flags:  srv must size, has return, has ext, */
			0x3,		/* 3 */
/* 6478 */	0x8,		/* 8 */
			0x3,		/* Ext Flags:  new corr desc, clt corr check, */
/* 6480 */	NdrFcShort( 0x2 ),	/* 2 */
/* 6482 */	NdrFcShort( 0x0 ),	/* 0 */
/* 6484 */	NdrFcShort( 0x0 ),	/* 0 */

	/* Parameter pbstrContentType */

/* 6486 */	NdrFcShort( 0x2113 ),	/* Flags:  must size, must free, out, simple ref, srv alloc size=8 */
/* 6488 */	NdrFcShort( 0x4 ),	/* x86 Stack size/offset = 4 */
/* 6490 */	NdrFcShort( 0x46a ),	/* Type Offset=1130 */

	/* Parameter pbstrSessionDescription */

/* 6492 */	NdrFcShort( 0x2113 ),	/* Flags:  must size, must free, out, simple ref, srv alloc size=8 */
/* 6494 */	NdrFcShort( 0x8 ),	/* x86 Stack size/offset = 8 */
/* 6496 */	NdrFcShort( 0x46a ),	/* Type Offset=1130 */

	/* Return value */

/* 6498 */	NdrFcShort( 0x70 ),	/* Flags:  out, return, base type, */
/* 6500 */	NdrFcShort( 0xc ),	/* x86 Stack size/offset = 12 */
/* 6502 */	0x8,		/* FC_LONG */
			0x0,		/* 0 */

	/* Procedure get_Participant */

/* 6504 */	0x33,		/* FC_AUTO_HANDLE */
			0x6c,		/* Old Flags:  object, Oi2 */
/* 6506 */	NdrFcLong( 0x0 ),	/* 0 */
/* 6510 */	NdrFcShort( 0xb ),	/* 11 */
/* 6512 */	NdrFcShort( 0xc ),	/* x86 Stack size/offset = 12 */
/* 6514 */	NdrFcShort( 0x0 ),	/* 0 */
/* 6516 */	NdrFcShort( 0x8 ),	/* 8 */
/* 6518 */	0x45,		/* Oi2 Flags:  srv must size, has return, has ext, */
			0x2,		/* 2 */
/* 6520 */	0x8,		/* 8 */
			0x1,		/* Ext Flags:  new corr desc, */
/* 6522 */	NdrFcShort( 0x0 ),	/* 0 */
/* 6524 */	NdrFcShort( 0x0 ),	/* 0 */
/* 6526 */	NdrFcShort( 0x0 ),	/* 0 */

	/* Parameter ppParticipant */

/* 6528 */	NdrFcShort( 0x13 ),	/* Flags:  must size, must free, out, */
/* 6530 */	NdrFcShort( 0x4 ),	/* x86 Stack size/offset = 4 */
/* 6532 */	NdrFcShort( 0x5b6 ),	/* Type Offset=1462 */

	/* Return value */

/* 6534 */	NdrFcShort( 0x70 ),	/* Flags:  out, return, base type, */
/* 6536 */	NdrFcShort( 0x8 ),	/* x86 Stack size/offset = 8 */
/* 6538 */	0x8,		/* FC_LONG */
			0x0,		/* 0 */

	/* Procedure GetRemoteSessionDescription */

/* 6540 */	0x33,		/* FC_AUTO_HANDLE */
			0x6c,		/* Old Flags:  object, Oi2 */
/* 6542 */	NdrFcLong( 0x0 ),	/* 0 */
/* 6546 */	NdrFcShort( 0xc ),	/* 12 */
/* 6548 */	NdrFcShort( 0x10 ),	/* x86 Stack size/offset = 16 */
/* 6550 */	NdrFcShort( 0x0 ),	/* 0 */
/* 6552 */	NdrFcShort( 0x8 ),	/* 8 */
/* 6554 */	0x45,		/* Oi2 Flags:  srv must size, has return, has ext, */
			0x3,		/* 3 */
/* 6556 */	0x8,		/* 8 */
			0x3,		/* Ext Flags:  new corr desc, clt corr check, */
/* 6558 */	NdrFcShort( 0x2 ),	/* 2 */
/* 6560 */	NdrFcShort( 0x0 ),	/* 0 */
/* 6562 */	NdrFcShort( 0x0 ),	/* 0 */

	/* Parameter pbstrContentType */

/* 6564 */	NdrFcShort( 0x2113 ),	/* Flags:  must size, must free, out, simple ref, srv alloc size=8 */
/* 6566 */	NdrFcShort( 0x4 ),	/* x86 Stack size/offset = 4 */
/* 6568 */	NdrFcShort( 0x46a ),	/* Type Offset=1130 */

	/* Parameter pbstrSessionDescription */

/* 6570 */	NdrFcShort( 0x2113 ),	/* Flags:  must size, must free, out, simple ref, srv alloc size=8 */
/* 6572 */	NdrFcShort( 0x8 ),	/* x86 Stack size/offset = 8 */
/* 6574 */	NdrFcShort( 0x46a ),	/* Type Offset=1130 */

	/* Return value */

/* 6576 */	NdrFcShort( 0x70 ),	/* Flags:  out, return, base type, */
/* 6578 */	NdrFcShort( 0xc ),	/* x86 Stack size/offset = 12 */
/* 6580 */	0x8,		/* FC_LONG */
			0x0,		/* 0 */

	/* Procedure get_Participant */

/* 6582 */	0x33,		/* FC_AUTO_HANDLE */
			0x6c,		/* Old Flags:  object, Oi2 */
/* 6584 */	NdrFcLong( 0x0 ),	/* 0 */
/* 6588 */	NdrFcShort( 0x7 ),	/* 7 */
/* 6590 */	NdrFcShort( 0xc ),	/* x86 Stack size/offset = 12 */
/* 6592 */	NdrFcShort( 0x0 ),	/* 0 */
/* 6594 */	NdrFcShort( 0x8 ),	/* 8 */
/* 6596 */	0x45,		/* Oi2 Flags:  srv must size, has return, has ext, */
			0x2,		/* 2 */
/* 6598 */	0x8,		/* 8 */
			0x1,		/* Ext Flags:  new corr desc, */
/* 6600 */	NdrFcShort( 0x0 ),	/* 0 */
/* 6602 */	NdrFcShort( 0x0 ),	/* 0 */
/* 6604 */	NdrFcShort( 0x0 ),	/* 0 */

	/* Parameter ppParticipant */

/* 6606 */	NdrFcShort( 0x13 ),	/* Flags:  must size, must free, out, */
/* 6608 */	NdrFcShort( 0x4 ),	/* x86 Stack size/offset = 4 */
/* 6610 */	NdrFcShort( 0x5b6 ),	/* Type Offset=1462 */

	/* Return value */

/* 6612 */	NdrFcShort( 0x70 ),	/* Flags:  out, return, base type, */
/* 6614 */	NdrFcShort( 0x8 ),	/* x86 Stack size/offset = 8 */
/* 6616 */	0x8,		/* FC_LONG */
			0x0,		/* 0 */

	/* Procedure get_PresenceProperty */


	/* Procedure get_EventType */


	/* Procedure get_EventReason */

/* 6618 */	0x33,		/* FC_AUTO_HANDLE */
			0x6c,		/* Old Flags:  object, Oi2 */
/* 6620 */	NdrFcLong( 0x0 ),	/* 0 */
/* 6624 */	NdrFcShort( 0x9 ),	/* 9 */
/* 6626 */	NdrFcShort( 0xc ),	/* x86 Stack size/offset = 12 */
/* 6628 */	NdrFcShort( 0x0 ),	/* 0 */
/* 6630 */	NdrFcShort( 0x22 ),	/* 34 */
/* 6632 */	0x44,		/* Oi2 Flags:  has return, has ext, */
			0x2,		/* 2 */
/* 6634 */	0x8,		/* 8 */
			0x1,		/* Ext Flags:  new corr desc, */
/* 6636 */	NdrFcShort( 0x0 ),	/* 0 */
/* 6638 */	NdrFcShort( 0x0 ),	/* 0 */
/* 6640 */	NdrFcShort( 0x0 ),	/* 0 */

	/* Parameter penPresProp */


	/* Parameter penEventType */


	/* Parameter penEventReason */

/* 6642 */	NdrFcShort( 0x2010 ),	/* Flags:  out, srv alloc size=8 */
/* 6644 */	NdrFcShort( 0x4 ),	/* x86 Stack size/offset = 4 */
/* 6646 */	NdrFcShort( 0x52 ),	/* Type Offset=82 */

	/* Return value */


	/* Return value */


	/* Return value */

/* 6648 */	NdrFcShort( 0x70 ),	/* Flags:  out, return, base type, */
/* 6650 */	NdrFcShort( 0x8 ),	/* x86 Stack size/offset = 8 */
/* 6652 */	0x8,		/* FC_LONG */
			0x0,		/* 0 */

	/* Procedure get_Participant */

/* 6654 */	0x33,		/* FC_AUTO_HANDLE */
			0x6c,		/* Old Flags:  object, Oi2 */
/* 6656 */	NdrFcLong( 0x0 ),	/* 0 */
/* 6660 */	NdrFcShort( 0x8 ),	/* 8 */
/* 6662 */	NdrFcShort( 0xc ),	/* x86 Stack size/offset = 12 */
/* 6664 */	NdrFcShort( 0x0 ),	/* 0 */
/* 6666 */	NdrFcShort( 0x8 ),	/* 8 */
/* 6668 */	0x45,		/* Oi2 Flags:  srv must size, has return, has ext, */
			0x2,		/* 2 */
/* 6670 */	0x8,		/* 8 */
			0x1,		/* Ext Flags:  new corr desc, */
/* 6672 */	NdrFcShort( 0x0 ),	/* 0 */
/* 6674 */	NdrFcShort( 0x0 ),	/* 0 */
/* 6676 */	NdrFcShort( 0x0 ),	/* 0 */

	/* Parameter ppParticipant */

/* 6678 */	NdrFcShort( 0x13 ),	/* Flags:  must size, must free, out, */
/* 6680 */	NdrFcShort( 0x4 ),	/* x86 Stack size/offset = 4 */
/* 6682 */	NdrFcShort( 0x5b6 ),	/* Type Offset=1462 */

	/* Return value */

/* 6684 */	NdrFcShort( 0x70 ),	/* Flags:  out, return, base type, */
/* 6686 */	NdrFcShort( 0x8 ),	/* x86 Stack size/offset = 8 */
/* 6688 */	0x8,		/* FC_LONG */
			0x0,		/* 0 */

	/* Procedure get_UserStatus */

/* 6690 */	0x33,		/* FC_AUTO_HANDLE */
			0x6c,		/* Old Flags:  object, Oi2 */
/* 6692 */	NdrFcLong( 0x0 ),	/* 0 */
/* 6696 */	NdrFcShort( 0xc ),	/* 12 */
/* 6698 */	NdrFcShort( 0xc ),	/* x86 Stack size/offset = 12 */
/* 6700 */	NdrFcShort( 0x0 ),	/* 0 */
/* 6702 */	NdrFcShort( 0x22 ),	/* 34 */
/* 6704 */	0x44,		/* Oi2 Flags:  has return, has ext, */
			0x2,		/* 2 */
/* 6706 */	0x8,		/* 8 */
			0x1,		/* Ext Flags:  new corr desc, */
/* 6708 */	NdrFcShort( 0x0 ),	/* 0 */
/* 6710 */	NdrFcShort( 0x0 ),	/* 0 */
/* 6712 */	NdrFcShort( 0x0 ),	/* 0 */

	/* Parameter penUserStatus */

/* 6714 */	NdrFcShort( 0x2010 ),	/* Flags:  out, srv alloc size=8 */
/* 6716 */	NdrFcShort( 0x4 ),	/* x86 Stack size/offset = 4 */
/* 6718 */	NdrFcShort( 0x52 ),	/* Type Offset=82 */

	/* Return value */

/* 6720 */	NdrFcShort( 0x70 ),	/* Flags:  out, return, base type, */
/* 6722 */	NdrFcShort( 0x8 ),	/* x86 Stack size/offset = 8 */
/* 6724 */	0x8,		/* FC_LONG */
			0x0,		/* 0 */

	/* Procedure get_Buddy */

/* 6726 */	0x33,		/* FC_AUTO_HANDLE */
			0x6c,		/* Old Flags:  object, Oi2 */
/* 6728 */	NdrFcLong( 0x0 ),	/* 0 */
/* 6732 */	NdrFcShort( 0x7 ),	/* 7 */
/* 6734 */	NdrFcShort( 0xc ),	/* x86 Stack size/offset = 12 */
/* 6736 */	NdrFcShort( 0x0 ),	/* 0 */
/* 6738 */	NdrFcShort( 0x8 ),	/* 8 */
/* 6740 */	0x45,		/* Oi2 Flags:  srv must size, has return, has ext, */
			0x2,		/* 2 */
/* 6742 */	0x8,		/* 8 */
			0x1,		/* Ext Flags:  new corr desc, */
/* 6744 */	NdrFcShort( 0x0 ),	/* 0 */
/* 6746 */	NdrFcShort( 0x0 ),	/* 0 */
/* 6748 */	NdrFcShort( 0x0 ),	/* 0 */

	/* Parameter ppBuddy */

/* 6750 */	NdrFcShort( 0x13 ),	/* Flags:  must size, must free, out, */
/* 6752 */	NdrFcShort( 0x4 ),	/* x86 Stack size/offset = 4 */
/* 6754 */	NdrFcShort( 0x650 ),	/* Type Offset=1616 */

	/* Return value */

/* 6756 */	NdrFcShort( 0x70 ),	/* Flags:  out, return, base type, */
/* 6758 */	NdrFcShort( 0x8 ),	/* x86 Stack size/offset = 8 */
/* 6760 */	0x8,		/* FC_LONG */
			0x0,		/* 0 */

	/* Procedure get_Watcher */

/* 6762 */	0x33,		/* FC_AUTO_HANDLE */
			0x6c,		/* Old Flags:  object, Oi2 */
/* 6764 */	NdrFcLong( 0x0 ),	/* 0 */
/* 6768 */	NdrFcShort( 0x7 ),	/* 7 */
/* 6770 */	NdrFcShort( 0xc ),	/* x86 Stack size/offset = 12 */
/* 6772 */	NdrFcShort( 0x0 ),	/* 0 */
/* 6774 */	NdrFcShort( 0x8 ),	/* 8 */
/* 6776 */	0x45,		/* Oi2 Flags:  srv must size, has return, has ext, */
			0x2,		/* 2 */
/* 6778 */	0x8,		/* 8 */
			0x1,		/* Ext Flags:  new corr desc, */
/* 6780 */	NdrFcShort( 0x0 ),	/* 0 */
/* 6782 */	NdrFcShort( 0x0 ),	/* 0 */
/* 6784 */	NdrFcShort( 0x0 ),	/* 0 */

	/* Parameter ppWatcher */

/* 6786 */	NdrFcShort( 0x13 ),	/* Flags:  must size, must free, out, */
/* 6788 */	NdrFcShort( 0x4 ),	/* x86 Stack size/offset = 4 */
/* 6790 */	NdrFcShort( 0x666 ),	/* Type Offset=1638 */

	/* Return value */

/* 6792 */	NdrFcShort( 0x70 ),	/* Flags:  out, return, base type, */
/* 6794 */	NdrFcShort( 0x8 ),	/* x86 Stack size/offset = 8 */
/* 6796 */	0x8,		/* FC_LONG */
			0x0,		/* 0 */

	/* Procedure get_Group */

/* 6798 */	0x33,		/* FC_AUTO_HANDLE */
			0x6c,		/* Old Flags:  object, Oi2 */
/* 6800 */	NdrFcLong( 0x0 ),	/* 0 */
/* 6804 */	NdrFcShort( 0x8 ),	/* 8 */
/* 6806 */	NdrFcShort( 0xc ),	/* x86 Stack size/offset = 12 */
/* 6808 */	NdrFcShort( 0x0 ),	/* 0 */
/* 6810 */	NdrFcShort( 0x8 ),	/* 8 */
/* 6812 */	0x45,		/* Oi2 Flags:  srv must size, has return, has ext, */
			0x2,		/* 2 */
/* 6814 */	0x8,		/* 8 */
			0x1,		/* Ext Flags:  new corr desc, */
/* 6816 */	NdrFcShort( 0x0 ),	/* 0 */
/* 6818 */	NdrFcShort( 0x0 ),	/* 0 */
/* 6820 */	NdrFcShort( 0x0 ),	/* 0 */

	/* Parameter ppGroup */

/* 6822 */	NdrFcShort( 0x13 ),	/* Flags:  must size, must free, out, */
/* 6824 */	NdrFcShort( 0x4 ),	/* x86 Stack size/offset = 4 */
/* 6826 */	NdrFcShort( 0x67c ),	/* Type Offset=1660 */

	/* Return value */

/* 6828 */	NdrFcShort( 0x70 ),	/* Flags:  out, return, base type, */
/* 6830 */	NdrFcShort( 0x8 ),	/* x86 Stack size/offset = 8 */
/* 6832 */	0x8,		/* FC_LONG */
			0x0,		/* 0 */

	/* Procedure get_Buddy */

/* 6834 */	0x33,		/* FC_AUTO_HANDLE */
			0x6c,		/* Old Flags:  object, Oi2 */
/* 6836 */	NdrFcLong( 0x0 ),	/* 0 */
/* 6840 */	NdrFcShort( 0x9 ),	/* 9 */
/* 6842 */	NdrFcShort( 0xc ),	/* x86 Stack size/offset = 12 */
/* 6844 */	NdrFcShort( 0x0 ),	/* 0 */
/* 6846 */	NdrFcShort( 0x8 ),	/* 8 */
/* 6848 */	0x45,		/* Oi2 Flags:  srv must size, has return, has ext, */
			0x2,		/* 2 */
/* 6850 */	0x8,		/* 8 */
			0x1,		/* Ext Flags:  new corr desc, */
/* 6852 */	NdrFcShort( 0x0 ),	/* 0 */
/* 6854 */	NdrFcShort( 0x0 ),	/* 0 */
/* 6856 */	NdrFcShort( 0x0 ),	/* 0 */

	/* Parameter ppBuddy */

/* 6858 */	NdrFcShort( 0x13 ),	/* Flags:  must size, must free, out, */
/* 6860 */	NdrFcShort( 0x4 ),	/* x86 Stack size/offset = 4 */
/* 6862 */	NdrFcShort( 0x692 ),	/* Type Offset=1682 */

	/* Return value */

/* 6864 */	NdrFcShort( 0x70 ),	/* Flags:  out, return, base type, */
/* 6866 */	NdrFcShort( 0x8 ),	/* x86 Stack size/offset = 8 */
/* 6868 */	0x8,		/* FC_LONG */
			0x0,		/* 0 */

	/* Procedure get_Session */


	/* Procedure get_Session */


	/* Procedure get_Session */

/* 6870 */	0x33,		/* FC_AUTO_HANDLE */
			0x6c,		/* Old Flags:  object, Oi2 */
/* 6872 */	NdrFcLong( 0x0 ),	/* 0 */
/* 6876 */	NdrFcShort( 0x7 ),	/* 7 */
/* 6878 */	NdrFcShort( 0xc ),	/* x86 Stack size/offset = 12 */
/* 6880 */	NdrFcShort( 0x0 ),	/* 0 */
/* 6882 */	NdrFcShort( 0x8 ),	/* 8 */
/* 6884 */	0x45,		/* Oi2 Flags:  srv must size, has return, has ext, */
			0x2,		/* 2 */
/* 6886 */	0x8,		/* 8 */
			0x1,		/* Ext Flags:  new corr desc, */
/* 6888 */	NdrFcShort( 0x0 ),	/* 0 */
/* 6890 */	NdrFcShort( 0x0 ),	/* 0 */
/* 6892 */	NdrFcShort( 0x0 ),	/* 0 */

	/* Parameter ppSession2 */


	/* Parameter ppSession */


	/* Parameter ppSession */

/* 6894 */	NdrFcShort( 0x13 ),	/* Flags:  must size, must free, out, */
/* 6896 */	NdrFcShort( 0x4 ),	/* x86 Stack size/offset = 4 */
/* 6898 */	NdrFcShort( 0x6a8 ),	/* Type Offset=1704 */

	/* Return value */


	/* Return value */


	/* Return value */

/* 6900 */	NdrFcShort( 0x70 ),	/* Flags:  out, return, base type, */
/* 6902 */	NdrFcShort( 0x8 ),	/* x86 Stack size/offset = 8 */
/* 6904 */	0x8,		/* FC_LONG */
			0x0,		/* 0 */

	/* Procedure get_Participant */

/* 6906 */	0x33,		/* FC_AUTO_HANDLE */
			0x6c,		/* Old Flags:  object, Oi2 */
/* 6908 */	NdrFcLong( 0x0 ),	/* 0 */
/* 6912 */	NdrFcShort( 0x8 ),	/* 8 */
/* 6914 */	NdrFcShort( 0xc ),	/* x86 Stack size/offset = 12 */
/* 6916 */	NdrFcShort( 0x0 ),	/* 0 */
/* 6918 */	NdrFcShort( 0x8 ),	/* 8 */
/* 6920 */	0x45,		/* Oi2 Flags:  srv must size, has return, has ext, */
			0x2,		/* 2 */
/* 6922 */	0x8,		/* 8 */
			0x1,		/* Ext Flags:  new corr desc, */
/* 6924 */	NdrFcShort( 0x0 ),	/* 0 */
/* 6926 */	NdrFcShort( 0x0 ),	/* 0 */
/* 6928 */	NdrFcShort( 0x0 ),	/* 0 */

	/* Parameter ppParticipant */

/* 6930 */	NdrFcShort( 0x13 ),	/* Flags:  must size, must free, out, */
/* 6932 */	NdrFcShort( 0x4 ),	/* x86 Stack size/offset = 4 */
/* 6934 */	NdrFcShort( 0x6be ),	/* Type Offset=1726 */

	/* Return value */

/* 6936 */	NdrFcShort( 0x70 ),	/* Flags:  out, return, base type, */
/* 6938 */	NdrFcShort( 0x8 ),	/* x86 Stack size/offset = 8 */
/* 6940 */	0x8,		/* FC_LONG */
			0x0,		/* 0 */

	/* Procedure Accept */

/* 6942 */	0x33,		/* FC_AUTO_HANDLE */
			0x6c,		/* Old Flags:  object, Oi2 */
/* 6944 */	NdrFcLong( 0x0 ),	/* 0 */
/* 6948 */	NdrFcShort( 0xa ),	/* 10 */
/* 6950 */	NdrFcShort( 0xc ),	/* x86 Stack size/offset = 12 */
/* 6952 */	NdrFcShort( 0x8 ),	/* 8 */
/* 6954 */	NdrFcShort( 0x8 ),	/* 8 */
/* 6956 */	0x44,		/* Oi2 Flags:  has return, has ext, */
			0x2,		/* 2 */
/* 6958 */	0x8,		/* 8 */
			0x1,		/* Ext Flags:  new corr desc, */
/* 6960 */	NdrFcShort( 0x0 ),	/* 0 */
/* 6962 */	NdrFcShort( 0x0 ),	/* 0 */
/* 6964 */	NdrFcShort( 0x0 ),	/* 0 */

	/* Parameter lMediaTypes */

/* 6966 */	NdrFcShort( 0x48 ),	/* Flags:  in, base type, */
/* 6968 */	NdrFcShort( 0x4 ),	/* x86 Stack size/offset = 4 */
/* 6970 */	0x8,		/* FC_LONG */
			0x0,		/* 0 */

	/* Return value */

/* 6972 */	NdrFcShort( 0x70 ),	/* Flags:  out, return, base type, */
/* 6974 */	NdrFcShort( 0x8 ),	/* x86 Stack size/offset = 8 */
/* 6976 */	0x8,		/* FC_LONG */
			0x0,		/* 0 */

	/* Procedure get_RemotePreferredSecurityLevel */

/* 6978 */	0x33,		/* FC_AUTO_HANDLE */
			0x6c,		/* Old Flags:  object, Oi2 */
/* 6980 */	NdrFcLong( 0x0 ),	/* 0 */
/* 6984 */	NdrFcShort( 0xb ),	/* 11 */
/* 6986 */	NdrFcShort( 0x10 ),	/* x86 Stack size/offset = 16 */
/* 6988 */	NdrFcShort( 0x6 ),	/* 6 */
/* 6990 */	NdrFcShort( 0x22 ),	/* 34 */
/* 6992 */	0x44,		/* Oi2 Flags:  has return, has ext, */
			0x3,		/* 3 */
/* 6994 */	0x8,		/* 8 */
			0x1,		/* Ext Flags:  new corr desc, */
/* 6996 */	NdrFcShort( 0x0 ),	/* 0 */
/* 6998 */	NdrFcShort( 0x0 ),	/* 0 */
/* 7000 */	NdrFcShort( 0x0 ),	/* 0 */

	/* Parameter enSecurityType */

/* 7002 */	NdrFcShort( 0x48 ),	/* Flags:  in, base type, */
/* 7004 */	NdrFcShort( 0x4 ),	/* x86 Stack size/offset = 4 */
/* 7006 */	0xd,		/* FC_ENUM16 */
			0x0,		/* 0 */

	/* Parameter penSecurityLevel */

/* 7008 */	NdrFcShort( 0x2010 ),	/* Flags:  out, srv alloc size=8 */
/* 7010 */	NdrFcShort( 0x8 ),	/* x86 Stack size/offset = 8 */
/* 7012 */	NdrFcShort( 0x52 ),	/* Type Offset=82 */

	/* Return value */

/* 7014 */	NdrFcShort( 0x70 ),	/* Flags:  out, return, base type, */
/* 7016 */	NdrFcShort( 0xc ),	/* x86 Stack size/offset = 12 */
/* 7018 */	0x8,		/* FC_LONG */
			0x0,		/* 0 */

	/* Procedure Reject */


	/* Procedure Reject */

/* 7020 */	0x33,		/* FC_AUTO_HANDLE */
			0x6c,		/* Old Flags:  object, Oi2 */
/* 7022 */	NdrFcLong( 0x0 ),	/* 0 */
/* 7026 */	NdrFcShort( 0xc ),	/* 12 */
/* 7028 */	NdrFcShort( 0x8 ),	/* x86 Stack size/offset = 8 */
/* 7030 */	NdrFcShort( 0x0 ),	/* 0 */
/* 7032 */	NdrFcShort( 0x8 ),	/* 8 */
/* 7034 */	0x44,		/* Oi2 Flags:  has return, has ext, */
			0x1,		/* 1 */
/* 7036 */	0x8,		/* 8 */
			0x1,		/* Ext Flags:  new corr desc, */
/* 7038 */	NdrFcShort( 0x0 ),	/* 0 */
/* 7040 */	NdrFcShort( 0x0 ),	/* 0 */
/* 7042 */	NdrFcShort( 0x0 ),	/* 0 */

	/* Return value */


	/* Return value */

/* 7044 */	NdrFcShort( 0x70 ),	/* Flags:  out, return, base type, */
/* 7046 */	NdrFcShort( 0x4 ),	/* x86 Stack size/offset = 4 */
/* 7048 */	0x8,		/* FC_LONG */
			0x0,		/* 0 */

	/* Procedure Accept */

/* 7050 */	0x33,		/* FC_AUTO_HANDLE */
			0x6c,		/* Old Flags:  object, Oi2 */
/* 7052 */	NdrFcLong( 0x0 ),	/* 0 */
/* 7056 */	NdrFcShort( 0x8 ),	/* 8 */
/* 7058 */	NdrFcShort( 0x10 ),	/* x86 Stack size/offset = 16 */
/* 7060 */	NdrFcShort( 0x0 ),	/* 0 */
/* 7062 */	NdrFcShort( 0x8 ),	/* 8 */
/* 7064 */	0x46,		/* Oi2 Flags:  clt must size, has return, has ext, */
			0x3,		/* 3 */
/* 7066 */	0x8,		/* 8 */
			0x5,		/* Ext Flags:  new corr desc, srv corr check, */
/* 7068 */	NdrFcShort( 0x0 ),	/* 0 */
/* 7070 */	NdrFcShort( 0x2 ),	/* 2 */
/* 7072 */	NdrFcShort( 0x0 ),	/* 0 */

	/* Parameter bstrContentType */

/* 7074 */	NdrFcShort( 0x8b ),	/* Flags:  must size, must free, in, by val, */
/* 7076 */	NdrFcShort( 0x4 ),	/* x86 Stack size/offset = 4 */
/* 7078 */	NdrFcShort( 0x20 ),	/* Type Offset=32 */

	/* Parameter bstrSessionDescription */

/* 7080 */	NdrFcShort( 0x8b ),	/* Flags:  must size, must free, in, by val, */
/* 7082 */	NdrFcShort( 0x8 ),	/* x86 Stack size/offset = 8 */
/* 7084 */	NdrFcShort( 0x20 ),	/* Type Offset=32 */

	/* Return value */

/* 7086 */	NdrFcShort( 0x70 ),	/* Flags:  out, return, base type, */
/* 7088 */	NdrFcShort( 0xc ),	/* x86 Stack size/offset = 12 */
/* 7090 */	0x8,		/* FC_LONG */
			0x0,		/* 0 */

	/* Procedure Reject */

/* 7092 */	0x33,		/* FC_AUTO_HANDLE */
			0x6c,		/* Old Flags:  object, Oi2 */
/* 7094 */	NdrFcLong( 0x0 ),	/* 0 */
/* 7098 */	NdrFcShort( 0x9 ),	/* 9 */
/* 7100 */	NdrFcShort( 0x8 ),	/* x86 Stack size/offset = 8 */
/* 7102 */	NdrFcShort( 0x0 ),	/* 0 */
/* 7104 */	NdrFcShort( 0x8 ),	/* 8 */
/* 7106 */	0x44,		/* Oi2 Flags:  has return, has ext, */
			0x1,		/* 1 */
/* 7108 */	0x8,		/* 8 */
			0x1,		/* Ext Flags:  new corr desc, */
/* 7110 */	NdrFcShort( 0x0 ),	/* 0 */
/* 7112 */	NdrFcShort( 0x0 ),	/* 0 */
/* 7114 */	NdrFcShort( 0x0 ),	/* 0 */

	/* Return value */

/* 7116 */	NdrFcShort( 0x70 ),	/* Flags:  out, return, base type, */
/* 7118 */	NdrFcShort( 0x4 ),	/* x86 Stack size/offset = 4 */
/* 7120 */	0x8,		/* FC_LONG */
			0x0,		/* 0 */

	/* Procedure GetRemoteSessionDescription */

/* 7122 */	0x33,		/* FC_AUTO_HANDLE */
			0x6c,		/* Old Flags:  object, Oi2 */
/* 7124 */	NdrFcLong( 0x0 ),	/* 0 */
/* 7128 */	NdrFcShort( 0xb ),	/* 11 */
/* 7130 */	NdrFcShort( 0x10 ),	/* x86 Stack size/offset = 16 */
/* 7132 */	NdrFcShort( 0x0 ),	/* 0 */
/* 7134 */	NdrFcShort( 0x8 ),	/* 8 */
/* 7136 */	0x45,		/* Oi2 Flags:  srv must size, has return, has ext, */
			0x3,		/* 3 */
/* 7138 */	0x8,		/* 8 */
			0x3,		/* Ext Flags:  new corr desc, clt corr check, */
/* 7140 */	NdrFcShort( 0x2 ),	/* 2 */
/* 7142 */	NdrFcShort( 0x0 ),	/* 0 */
/* 7144 */	NdrFcShort( 0x0 ),	/* 0 */

	/* Parameter pbstrContentType */

/* 7146 */	NdrFcShort( 0x2113 ),	/* Flags:  must size, must free, out, simple ref, srv alloc size=8 */
/* 7148 */	NdrFcShort( 0x4 ),	/* x86 Stack size/offset = 4 */
/* 7150 */	NdrFcShort( 0x46a ),	/* Type Offset=1130 */

	/* Parameter pbstrSessionDescription */

/* 7152 */	NdrFcShort( 0x2113 ),	/* Flags:  must size, must free, out, simple ref, srv alloc size=8 */
/* 7154 */	NdrFcShort( 0x8 ),	/* x86 Stack size/offset = 8 */
/* 7156 */	NdrFcShort( 0x46a ),	/* Type Offset=1130 */

	/* Return value */

/* 7158 */	NdrFcShort( 0x70 ),	/* Flags:  out, return, base type, */
/* 7160 */	NdrFcShort( 0xc ),	/* x86 Stack size/offset = 12 */
/* 7162 */	0x8,		/* FC_LONG */
			0x0,		/* 0 */

	/* Procedure GetPresenceData */

/* 7164 */	0x33,		/* FC_AUTO_HANDLE */
			0x6c,		/* Old Flags:  object, Oi2 */
/* 7166 */	NdrFcLong( 0x0 ),	/* 0 */
/* 7170 */	NdrFcShort( 0x9 ),	/* 9 */
/* 7172 */	NdrFcShort( 0x10 ),	/* x86 Stack size/offset = 16 */
/* 7174 */	NdrFcShort( 0x0 ),	/* 0 */
/* 7176 */	NdrFcShort( 0x8 ),	/* 8 */
/* 7178 */	0x45,		/* Oi2 Flags:  srv must size, has return, has ext, */
			0x3,		/* 3 */
/* 7180 */	0x8,		/* 8 */
			0x3,		/* Ext Flags:  new corr desc, clt corr check, */
/* 7182 */	NdrFcShort( 0x2 ),	/* 2 */
/* 7184 */	NdrFcShort( 0x0 ),	/* 0 */
/* 7186 */	NdrFcShort( 0x0 ),	/* 0 */

	/* Parameter pbstrNamespace */

/* 7188 */	NdrFcShort( 0x2113 ),	/* Flags:  must size, must free, out, simple ref, srv alloc size=8 */
/* 7190 */	NdrFcShort( 0x4 ),	/* x86 Stack size/offset = 4 */
/* 7192 */	NdrFcShort( 0x46a ),	/* Type Offset=1130 */

	/* Parameter pbstrData */

/* 7194 */	NdrFcShort( 0x2113 ),	/* Flags:  must size, must free, out, simple ref, srv alloc size=8 */
/* 7196 */	NdrFcShort( 0x8 ),	/* x86 Stack size/offset = 8 */
/* 7198 */	NdrFcShort( 0x46a ),	/* Type Offset=1130 */

	/* Return value */

/* 7200 */	NdrFcShort( 0x70 ),	/* Flags:  out, return, base type, */
/* 7202 */	NdrFcShort( 0xc ),	/* x86 Stack size/offset = 12 */
/* 7204 */	0x8,		/* FC_LONG */
			0x0,		/* 0 */

	/* Procedure GetLocalPresenceInfo */

/* 7206 */	0x33,		/* FC_AUTO_HANDLE */
			0x6c,		/* Old Flags:  object, Oi2 */
/* 7208 */	NdrFcLong( 0x0 ),	/* 0 */
/* 7212 */	NdrFcShort( 0x9 ),	/* 9 */
/* 7214 */	NdrFcShort( 0x10 ),	/* x86 Stack size/offset = 16 */
/* 7216 */	NdrFcShort( 0x0 ),	/* 0 */
/* 7218 */	NdrFcShort( 0x22 ),	/* 34 */
/* 7220 */	0x45,		/* Oi2 Flags:  srv must size, has return, has ext, */
			0x3,		/* 3 */
/* 7222 */	0x8,		/* 8 */
			0x3,		/* Ext Flags:  new corr desc, clt corr check, */
/* 7224 */	NdrFcShort( 0x1 ),	/* 1 */
/* 7226 */	NdrFcShort( 0x0 ),	/* 0 */
/* 7228 */	NdrFcShort( 0x0 ),	/* 0 */

	/* Parameter penStatus */

/* 7230 */	NdrFcShort( 0x2010 ),	/* Flags:  out, srv alloc size=8 */
/* 7232 */	NdrFcShort( 0x4 ),	/* x86 Stack size/offset = 4 */
/* 7234 */	NdrFcShort( 0x52 ),	/* Type Offset=82 */

	/* Parameter pbstrNotes */

/* 7236 */	NdrFcShort( 0x2113 ),	/* Flags:  must size, must free, out, simple ref, srv alloc size=8 */
/* 7238 */	NdrFcShort( 0x8 ),	/* x86 Stack size/offset = 8 */
/* 7240 */	NdrFcShort( 0x46a ),	/* Type Offset=1130 */

	/* Return value */

/* 7242 */	NdrFcShort( 0x70 ),	/* Flags:  out, return, base type, */
/* 7244 */	NdrFcShort( 0xc ),	/* x86 Stack size/offset = 12 */
/* 7246 */	0x8,		/* FC_LONG */
			0x0,		/* 0 */

	/* Procedure get_Item */

/* 7248 */	0x33,		/* FC_AUTO_HANDLE */
			0x6c,		/* Old Flags:  object, Oi2 */
/* 7250 */	NdrFcLong( 0x0 ),	/* 0 */
/* 7254 */	NdrFcShort( 0x8 ),	/* 8 */
/* 7256 */	NdrFcShort( 0x10 ),	/* x86 Stack size/offset = 16 */
/* 7258 */	NdrFcShort( 0x8 ),	/* 8 */
/* 7260 */	NdrFcShort( 0x8 ),	/* 8 */
/* 7262 */	0x45,		/* Oi2 Flags:  srv must size, has return, has ext, */
			0x3,		/* 3 */
/* 7264 */	0x8,		/* 8 */
			0x3,		/* Ext Flags:  new corr desc, clt corr check, */
/* 7266 */	NdrFcShort( 0x20 ),	/* 32 */
/* 7268 */	NdrFcShort( 0x0 ),	/* 0 */
/* 7270 */	NdrFcShort( 0x0 ),	/* 0 */

	/* Parameter Index */

/* 7272 */	NdrFcShort( 0x48 ),	/* Flags:  in, base type, */
/* 7274 */	NdrFcShort( 0x4 ),	/* x86 Stack size/offset = 4 */
/* 7276 */	0x8,		/* FC_LONG */
			0x0,		/* 0 */

	/* Parameter pVariant */

/* 7278 */	NdrFcShort( 0x4113 ),	/* Flags:  must size, must free, out, simple ref, srv alloc size=16 */
/* 7280 */	NdrFcShort( 0x8 ),	/* x86 Stack size/offset = 8 */
/* 7282 */	NdrFcShort( 0x442 ),	/* Type Offset=1090 */

	/* Return value */

/* 7284 */	NdrFcShort( 0x70 ),	/* Flags:  out, return, base type, */
/* 7286 */	NdrFcShort( 0xc ),	/* x86 Stack size/offset = 12 */
/* 7288 */	0x8,		/* FC_LONG */
			0x0,		/* 0 */

	/* Procedure get__NewEnum */

/* 7290 */	0x33,		/* FC_AUTO_HANDLE */
			0x6c,		/* Old Flags:  object, Oi2 */
/* 7292 */	NdrFcLong( 0x0 ),	/* 0 */
/* 7296 */	NdrFcShort( 0x9 ),	/* 9 */
/* 7298 */	NdrFcShort( 0xc ),	/* x86 Stack size/offset = 12 */
/* 7300 */	NdrFcShort( 0x0 ),	/* 0 */
/* 7302 */	NdrFcShort( 0x8 ),	/* 8 */
/* 7304 */	0x45,		/* Oi2 Flags:  srv must size, has return, has ext, */
			0x2,		/* 2 */
/* 7306 */	0x8,		/* 8 */
			0x1,		/* Ext Flags:  new corr desc, */
/* 7308 */	NdrFcShort( 0x0 ),	/* 0 */
/* 7310 */	NdrFcShort( 0x0 ),	/* 0 */
/* 7312 */	NdrFcShort( 0x0 ),	/* 0 */

	/* Parameter ppNewEnum */

/* 7314 */	NdrFcShort( 0x13 ),	/* Flags:  must size, must free, out, */
/* 7316 */	NdrFcShort( 0x4 ),	/* x86 Stack size/offset = 4 */
/* 7318 */	NdrFcShort( 0x6d4 ),	/* Type Offset=1748 */

	/* Return value */

/* 7320 */	NdrFcShort( 0x70 ),	/* Flags:  out, return, base type, */
/* 7322 */	NdrFcShort( 0x8 ),	/* x86 Stack size/offset = 8 */
/* 7324 */	0x8,		/* FC_LONG */
			0x0,		/* 0 */

	/* Procedure Next */

/* 7326 */	0x33,		/* FC_AUTO_HANDLE */
			0x6d,		/* Old Flags:  full ptr, object, Oi2 */
/* 7328 */	NdrFcLong( 0x0 ),	/* 0 */
/* 7332 */	NdrFcShort( 0x3 ),	/* 3 */
/* 7334 */	NdrFcShort( 0x14 ),	/* x86 Stack size/offset = 20 */
/* 7336 */	NdrFcShort( 0x24 ),	/* 36 */
/* 7338 */	NdrFcShort( 0x24 ),	/* 36 */
/* 7340 */	0x45,		/* Oi2 Flags:  srv must size, has return, has ext, */
			0x4,		/* 4 */
/* 7342 */	0x8,		/* 8 */
			0x3,		/* Ext Flags:  new corr desc, clt corr check, */
/* 7344 */	NdrFcShort( 0x1 ),	/* 1 */
/* 7346 */	NdrFcShort( 0x0 ),	/* 0 */
/* 7348 */	NdrFcShort( 0x0 ),	/* 0 */

	/* Parameter celt */

/* 7350 */	NdrFcShort( 0x48 ),	/* Flags:  in, base type, */
/* 7352 */	NdrFcShort( 0x4 ),	/* x86 Stack size/offset = 4 */
/* 7354 */	0x8,		/* FC_LONG */
			0x0,		/* 0 */

	/* Parameter ppElements */

/* 7356 */	NdrFcShort( 0x113 ),	/* Flags:  must size, must free, out, simple ref, */
/* 7358 */	NdrFcShort( 0x8 ),	/* x86 Stack size/offset = 8 */
/* 7360 */	NdrFcShort( 0x6ee ),	/* Type Offset=1774 */

	/* Parameter pceltFetched */

/* 7362 */	NdrFcShort( 0x1a ),	/* Flags:  must free, in, out, */
/* 7364 */	NdrFcShort( 0xc ),	/* x86 Stack size/offset = 12 */
/* 7366 */	NdrFcShort( 0x704 ),	/* Type Offset=1796 */

	/* Return value */

/* 7368 */	NdrFcShort( 0x70 ),	/* Flags:  out, return, base type, */
/* 7370 */	NdrFcShort( 0x10 ),	/* x86 Stack size/offset = 16 */
/* 7372 */	0x8,		/* FC_LONG */
			0x0,		/* 0 */

	/* Procedure Skip */


	/* Procedure Skip */


	/* Procedure Skip */


	/* Procedure Skip */


	/* Procedure Skip */


	/* Procedure Skip */


	/* Procedure Skip */

/* 7374 */	0x33,		/* FC_AUTO_HANDLE */
			0x6c,		/* Old Flags:  object, Oi2 */
/* 7376 */	NdrFcLong( 0x0 ),	/* 0 */
/* 7380 */	NdrFcShort( 0x5 ),	/* 5 */
/* 7382 */	NdrFcShort( 0xc ),	/* x86 Stack size/offset = 12 */
/* 7384 */	NdrFcShort( 0x8 ),	/* 8 */
/* 7386 */	NdrFcShort( 0x8 ),	/* 8 */
/* 7388 */	0x44,		/* Oi2 Flags:  has return, has ext, */
			0x2,		/* 2 */
/* 7390 */	0x8,		/* 8 */
			0x1,		/* Ext Flags:  new corr desc, */
/* 7392 */	NdrFcShort( 0x0 ),	/* 0 */
/* 7394 */	NdrFcShort( 0x0 ),	/* 0 */
/* 7396 */	NdrFcShort( 0x0 ),	/* 0 */

	/* Parameter celt */


	/* Parameter celt */


	/* Parameter celt */


	/* Parameter celt */


	/* Parameter celt */


	/* Parameter celt */


	/* Parameter celt */

/* 7398 */	NdrFcShort( 0x48 ),	/* Flags:  in, base type, */
/* 7400 */	NdrFcShort( 0x4 ),	/* x86 Stack size/offset = 4 */
/* 7402 */	0x8,		/* FC_LONG */
			0x0,		/* 0 */

	/* Return value */


	/* Return value */


	/* Return value */


	/* Return value */


	/* Return value */


	/* Return value */


	/* Return value */

/* 7404 */	NdrFcShort( 0x70 ),	/* Flags:  out, return, base type, */
/* 7406 */	NdrFcShort( 0x8 ),	/* x86 Stack size/offset = 8 */
/* 7408 */	0x8,		/* FC_LONG */
			0x0,		/* 0 */

	/* Procedure Clone */

/* 7410 */	0x33,		/* FC_AUTO_HANDLE */
			0x6c,		/* Old Flags:  object, Oi2 */
/* 7412 */	NdrFcLong( 0x0 ),	/* 0 */
/* 7416 */	NdrFcShort( 0x6 ),	/* 6 */
/* 7418 */	NdrFcShort( 0xc ),	/* x86 Stack size/offset = 12 */
/* 7420 */	NdrFcShort( 0x0 ),	/* 0 */
/* 7422 */	NdrFcShort( 0x8 ),	/* 8 */
/* 7424 */	0x45,		/* Oi2 Flags:  srv must size, has return, has ext, */
			0x2,		/* 2 */
/* 7426 */	0x8,		/* 8 */
			0x1,		/* Ext Flags:  new corr desc, */
/* 7428 */	NdrFcShort( 0x0 ),	/* 0 */
/* 7430 */	NdrFcShort( 0x0 ),	/* 0 */
/* 7432 */	NdrFcShort( 0x0 ),	/* 0 */

	/* Parameter ppEnum */

/* 7434 */	NdrFcShort( 0x13 ),	/* Flags:  must size, must free, out, */
/* 7436 */	NdrFcShort( 0x4 ),	/* x86 Stack size/offset = 4 */
/* 7438 */	NdrFcShort( 0x708 ),	/* Type Offset=1800 */

	/* Return value */

/* 7440 */	NdrFcShort( 0x70 ),	/* Flags:  out, return, base type, */
/* 7442 */	NdrFcShort( 0x8 ),	/* x86 Stack size/offset = 8 */
/* 7444 */	0x8,		/* FC_LONG */
			0x0,		/* 0 */

	/* Procedure Next */

/* 7446 */	0x33,		/* FC_AUTO_HANDLE */
			0x6d,		/* Old Flags:  full ptr, object, Oi2 */
/* 7448 */	NdrFcLong( 0x0 ),	/* 0 */
/* 7452 */	NdrFcShort( 0x3 ),	/* 3 */
/* 7454 */	NdrFcShort( 0x14 ),	/* x86 Stack size/offset = 20 */
/* 7456 */	NdrFcShort( 0x24 ),	/* 36 */
/* 7458 */	NdrFcShort( 0x24 ),	/* 36 */
/* 7460 */	0x45,		/* Oi2 Flags:  srv must size, has return, has ext, */
			0x4,		/* 4 */
/* 7462 */	0x8,		/* 8 */
			0x3,		/* Ext Flags:  new corr desc, clt corr check, */
/* 7464 */	NdrFcShort( 0x1 ),	/* 1 */
/* 7466 */	NdrFcShort( 0x0 ),	/* 0 */
/* 7468 */	NdrFcShort( 0x0 ),	/* 0 */

	/* Parameter celt */

/* 7470 */	NdrFcShort( 0x48 ),	/* Flags:  in, base type, */
/* 7472 */	NdrFcShort( 0x4 ),	/* x86 Stack size/offset = 4 */
/* 7474 */	0x8,		/* FC_LONG */
			0x0,		/* 0 */

	/* Parameter ppElements */

/* 7476 */	NdrFcShort( 0x113 ),	/* Flags:  must size, must free, out, simple ref, */
/* 7478 */	NdrFcShort( 0x8 ),	/* x86 Stack size/offset = 8 */
/* 7480 */	NdrFcShort( 0x734 ),	/* Type Offset=1844 */

	/* Parameter pceltFetched */

/* 7482 */	NdrFcShort( 0x1a ),	/* Flags:  must free, in, out, */
/* 7484 */	NdrFcShort( 0xc ),	/* x86 Stack size/offset = 12 */
/* 7486 */	NdrFcShort( 0x704 ),	/* Type Offset=1796 */

	/* Return value */

/* 7488 */	NdrFcShort( 0x70 ),	/* Flags:  out, return, base type, */
/* 7490 */	NdrFcShort( 0x10 ),	/* x86 Stack size/offset = 16 */
/* 7492 */	0x8,		/* FC_LONG */
			0x0,		/* 0 */

	/* Procedure Next */

/* 7494 */	0x33,		/* FC_AUTO_HANDLE */
			0x6d,		/* Old Flags:  full ptr, object, Oi2 */
/* 7496 */	NdrFcLong( 0x0 ),	/* 0 */
/* 7500 */	NdrFcShort( 0x3 ),	/* 3 */
/* 7502 */	NdrFcShort( 0x14 ),	/* x86 Stack size/offset = 20 */
/* 7504 */	NdrFcShort( 0x24 ),	/* 36 */
/* 7506 */	NdrFcShort( 0x24 ),	/* 36 */
/* 7508 */	0x45,		/* Oi2 Flags:  srv must size, has return, has ext, */
			0x4,		/* 4 */
/* 7510 */	0x8,		/* 8 */
			0x3,		/* Ext Flags:  new corr desc, clt corr check, */
/* 7512 */	NdrFcShort( 0x1 ),	/* 1 */
/* 7514 */	NdrFcShort( 0x0 ),	/* 0 */
/* 7516 */	NdrFcShort( 0x0 ),	/* 0 */

	/* Parameter celt */

/* 7518 */	NdrFcShort( 0x48 ),	/* Flags:  in, base type, */
/* 7520 */	NdrFcShort( 0x4 ),	/* x86 Stack size/offset = 4 */
/* 7522 */	0x8,		/* FC_LONG */
			0x0,		/* 0 */

	/* Parameter ppElements */

/* 7524 */	NdrFcShort( 0x113 ),	/* Flags:  must size, must free, out, simple ref, */
/* 7526 */	NdrFcShort( 0x8 ),	/* x86 Stack size/offset = 8 */
/* 7528 */	NdrFcShort( 0x760 ),	/* Type Offset=1888 */

	/* Parameter pceltFetched */

/* 7530 */	NdrFcShort( 0x1a ),	/* Flags:  must free, in, out, */
/* 7532 */	NdrFcShort( 0xc ),	/* x86 Stack size/offset = 12 */
/* 7534 */	NdrFcShort( 0x704 ),	/* Type Offset=1796 */

	/* Return value */

/* 7536 */	NdrFcShort( 0x70 ),	/* Flags:  out, return, base type, */
/* 7538 */	NdrFcShort( 0x10 ),	/* x86 Stack size/offset = 16 */
/* 7540 */	0x8,		/* FC_LONG */
			0x0,		/* 0 */

	/* Procedure Clone */

/* 7542 */	0x33,		/* FC_AUTO_HANDLE */
			0x6c,		/* Old Flags:  object, Oi2 */
/* 7544 */	NdrFcLong( 0x0 ),	/* 0 */
/* 7548 */	NdrFcShort( 0x6 ),	/* 6 */
/* 7550 */	NdrFcShort( 0xc ),	/* x86 Stack size/offset = 12 */
/* 7552 */	NdrFcShort( 0x0 ),	/* 0 */
/* 7554 */	NdrFcShort( 0x8 ),	/* 8 */
/* 7556 */	0x45,		/* Oi2 Flags:  srv must size, has return, has ext, */
			0x2,		/* 2 */
/* 7558 */	0x8,		/* 8 */
			0x1,		/* Ext Flags:  new corr desc, */
/* 7560 */	NdrFcShort( 0x0 ),	/* 0 */
/* 7562 */	NdrFcShort( 0x0 ),	/* 0 */
/* 7564 */	NdrFcShort( 0x0 ),	/* 0 */

	/* Parameter ppEnum */

/* 7566 */	NdrFcShort( 0x13 ),	/* Flags:  must size, must free, out, */
/* 7568 */	NdrFcShort( 0x4 ),	/* x86 Stack size/offset = 4 */
/* 7570 */	NdrFcShort( 0x776 ),	/* Type Offset=1910 */

	/* Return value */

/* 7572 */	NdrFcShort( 0x70 ),	/* Flags:  out, return, base type, */
/* 7574 */	NdrFcShort( 0x8 ),	/* x86 Stack size/offset = 8 */
/* 7576 */	0x8,		/* FC_LONG */
			0x0,		/* 0 */

	/* Procedure Next */

/* 7578 */	0x33,		/* FC_AUTO_HANDLE */
			0x6d,		/* Old Flags:  full ptr, object, Oi2 */
/* 7580 */	NdrFcLong( 0x0 ),	/* 0 */
/* 7584 */	NdrFcShort( 0x3 ),	/* 3 */
/* 7586 */	NdrFcShort( 0x14 ),	/* x86 Stack size/offset = 20 */
/* 7588 */	NdrFcShort( 0x24 ),	/* 36 */
/* 7590 */	NdrFcShort( 0x24 ),	/* 36 */
/* 7592 */	0x45,		/* Oi2 Flags:  srv must size, has return, has ext, */
			0x4,		/* 4 */
/* 7594 */	0x8,		/* 8 */
			0x3,		/* Ext Flags:  new corr desc, clt corr check, */
/* 7596 */	NdrFcShort( 0x1 ),	/* 1 */
/* 7598 */	NdrFcShort( 0x0 ),	/* 0 */
/* 7600 */	NdrFcShort( 0x0 ),	/* 0 */

	/* Parameter celt */

/* 7602 */	NdrFcShort( 0x48 ),	/* Flags:  in, base type, */
/* 7604 */	NdrFcShort( 0x4 ),	/* x86 Stack size/offset = 4 */
/* 7606 */	0x8,		/* FC_LONG */
			0x0,		/* 0 */

	/* Parameter ppElements */

/* 7608 */	NdrFcShort( 0x113 ),	/* Flags:  must size, must free, out, simple ref, */
/* 7610 */	NdrFcShort( 0x8 ),	/* x86 Stack size/offset = 8 */
/* 7612 */	NdrFcShort( 0x7a2 ),	/* Type Offset=1954 */

	/* Parameter pceltFetched */

/* 7614 */	NdrFcShort( 0x1a ),	/* Flags:  must free, in, out, */
/* 7616 */	NdrFcShort( 0xc ),	/* x86 Stack size/offset = 12 */
/* 7618 */	NdrFcShort( 0x704 ),	/* Type Offset=1796 */

	/* Return value */

/* 7620 */	NdrFcShort( 0x70 ),	/* Flags:  out, return, base type, */
/* 7622 */	NdrFcShort( 0x10 ),	/* x86 Stack size/offset = 16 */
/* 7624 */	0x8,		/* FC_LONG */
			0x0,		/* 0 */

	/* Procedure Clone */

/* 7626 */	0x33,		/* FC_AUTO_HANDLE */
			0x6c,		/* Old Flags:  object, Oi2 */
/* 7628 */	NdrFcLong( 0x0 ),	/* 0 */
/* 7632 */	NdrFcShort( 0x6 ),	/* 6 */
/* 7634 */	NdrFcShort( 0xc ),	/* x86 Stack size/offset = 12 */
/* 7636 */	NdrFcShort( 0x0 ),	/* 0 */
/* 7638 */	NdrFcShort( 0x8 ),	/* 8 */
/* 7640 */	0x45,		/* Oi2 Flags:  srv must size, has return, has ext, */
			0x2,		/* 2 */
/* 7642 */	0x8,		/* 8 */
			0x1,		/* Ext Flags:  new corr desc, */
/* 7644 */	NdrFcShort( 0x0 ),	/* 0 */
/* 7646 */	NdrFcShort( 0x0 ),	/* 0 */
/* 7648 */	NdrFcShort( 0x0 ),	/* 0 */

	/* Parameter ppEnum */

/* 7650 */	NdrFcShort( 0x13 ),	/* Flags:  must size, must free, out, */
/* 7652 */	NdrFcShort( 0x4 ),	/* x86 Stack size/offset = 4 */
/* 7654 */	NdrFcShort( 0x7b8 ),	/* Type Offset=1976 */

	/* Return value */

/* 7656 */	NdrFcShort( 0x70 ),	/* Flags:  out, return, base type, */
/* 7658 */	NdrFcShort( 0x8 ),	/* x86 Stack size/offset = 8 */
/* 7660 */	0x8,		/* FC_LONG */
			0x0,		/* 0 */

	/* Procedure Next */

/* 7662 */	0x33,		/* FC_AUTO_HANDLE */
			0x6d,		/* Old Flags:  full ptr, object, Oi2 */
/* 7664 */	NdrFcLong( 0x0 ),	/* 0 */
/* 7668 */	NdrFcShort( 0x3 ),	/* 3 */
/* 7670 */	NdrFcShort( 0x14 ),	/* x86 Stack size/offset = 20 */
/* 7672 */	NdrFcShort( 0x24 ),	/* 36 */
/* 7674 */	NdrFcShort( 0x24 ),	/* 36 */
/* 7676 */	0x45,		/* Oi2 Flags:  srv must size, has return, has ext, */
			0x4,		/* 4 */
/* 7678 */	0x8,		/* 8 */
			0x3,		/* Ext Flags:  new corr desc, clt corr check, */
/* 7680 */	NdrFcShort( 0x1 ),	/* 1 */
/* 7682 */	NdrFcShort( 0x0 ),	/* 0 */
/* 7684 */	NdrFcShort( 0x0 ),	/* 0 */

	/* Parameter celt */

/* 7686 */	NdrFcShort( 0x48 ),	/* Flags:  in, base type, */
/* 7688 */	NdrFcShort( 0x4 ),	/* x86 Stack size/offset = 4 */
/* 7690 */	0x8,		/* FC_LONG */
			0x0,		/* 0 */

	/* Parameter ppElements */

/* 7692 */	NdrFcShort( 0x113 ),	/* Flags:  must size, must free, out, simple ref, */
/* 7694 */	NdrFcShort( 0x8 ),	/* x86 Stack size/offset = 8 */
/* 7696 */	NdrFcShort( 0x7e4 ),	/* Type Offset=2020 */

	/* Parameter pceltFetched */

/* 7698 */	NdrFcShort( 0x1a ),	/* Flags:  must free, in, out, */
/* 7700 */	NdrFcShort( 0xc ),	/* x86 Stack size/offset = 12 */
/* 7702 */	NdrFcShort( 0x704 ),	/* Type Offset=1796 */

	/* Return value */

/* 7704 */	NdrFcShort( 0x70 ),	/* Flags:  out, return, base type, */
/* 7706 */	NdrFcShort( 0x10 ),	/* x86 Stack size/offset = 16 */
/* 7708 */	0x8,		/* FC_LONG */
			0x0,		/* 0 */

	/* Procedure Clone */

/* 7710 */	0x33,		/* FC_AUTO_HANDLE */
			0x6c,		/* Old Flags:  object, Oi2 */
/* 7712 */	NdrFcLong( 0x0 ),	/* 0 */
/* 7716 */	NdrFcShort( 0x6 ),	/* 6 */
/* 7718 */	NdrFcShort( 0xc ),	/* x86 Stack size/offset = 12 */
/* 7720 */	NdrFcShort( 0x0 ),	/* 0 */
/* 7722 */	NdrFcShort( 0x8 ),	/* 8 */
/* 7724 */	0x45,		/* Oi2 Flags:  srv must size, has return, has ext, */
			0x2,		/* 2 */
/* 7726 */	0x8,		/* 8 */
			0x1,		/* Ext Flags:  new corr desc, */
/* 7728 */	NdrFcShort( 0x0 ),	/* 0 */
/* 7730 */	NdrFcShort( 0x0 ),	/* 0 */
/* 7732 */	NdrFcShort( 0x0 ),	/* 0 */

	/* Parameter ppEnum */

/* 7734 */	NdrFcShort( 0x13 ),	/* Flags:  must size, must free, out, */
/* 7736 */	NdrFcShort( 0x4 ),	/* x86 Stack size/offset = 4 */
/* 7738 */	NdrFcShort( 0x7fa ),	/* Type Offset=2042 */

	/* Return value */

/* 7740 */	NdrFcShort( 0x70 ),	/* Flags:  out, return, base type, */
/* 7742 */	NdrFcShort( 0x8 ),	/* x86 Stack size/offset = 8 */
/* 7744 */	0x8,		/* FC_LONG */
			0x0,		/* 0 */

	/* Procedure put_Name */


	/* Procedure put_PresentityURI */

/* 7746 */	0x33,		/* FC_AUTO_HANDLE */
			0x6c,		/* Old Flags:  object, Oi2 */
/* 7748 */	NdrFcLong( 0x0 ),	/* 0 */
/* 7752 */	NdrFcShort( 0x4 ),	/* 4 */
/* 7754 */	NdrFcShort( 0xc ),	/* x86 Stack size/offset = 12 */
/* 7756 */	NdrFcShort( 0x0 ),	/* 0 */
/* 7758 */	NdrFcShort( 0x8 ),	/* 8 */
/* 7760 */	0x46,		/* Oi2 Flags:  clt must size, has return, has ext, */
			0x2,		/* 2 */
/* 7762 */	0x8,		/* 8 */
			0x5,		/* Ext Flags:  new corr desc, srv corr check, */
/* 7764 */	NdrFcShort( 0x0 ),	/* 0 */
/* 7766 */	NdrFcShort( 0x1 ),	/* 1 */
/* 7768 */	NdrFcShort( 0x0 ),	/* 0 */

	/* Parameter bstrGroupName */


	/* Parameter bstrPresentityURI */

/* 7770 */	NdrFcShort( 0x8b ),	/* Flags:  must size, must free, in, by val, */
/* 7772 */	NdrFcShort( 0x4 ),	/* x86 Stack size/offset = 4 */
/* 7774 */	NdrFcShort( 0x20 ),	/* Type Offset=32 */

	/* Return value */


	/* Return value */

/* 7776 */	NdrFcShort( 0x70 ),	/* Flags:  out, return, base type, */
/* 7778 */	NdrFcShort( 0x8 ),	/* x86 Stack size/offset = 8 */
/* 7780 */	0x8,		/* FC_LONG */
			0x0,		/* 0 */

	/* Procedure put_Name */

/* 7782 */	0x33,		/* FC_AUTO_HANDLE */
			0x6c,		/* Old Flags:  object, Oi2 */
/* 7784 */	NdrFcLong( 0x0 ),	/* 0 */
/* 7788 */	NdrFcShort( 0x6 ),	/* 6 */
/* 7790 */	NdrFcShort( 0xc ),	/* x86 Stack size/offset = 12 */
/* 7792 */	NdrFcShort( 0x0 ),	/* 0 */
/* 7794 */	NdrFcShort( 0x8 ),	/* 8 */
/* 7796 */	0x46,		/* Oi2 Flags:  clt must size, has return, has ext, */
			0x2,		/* 2 */
/* 7798 */	0x8,		/* 8 */
			0x5,		/* Ext Flags:  new corr desc, srv corr check, */
/* 7800 */	NdrFcShort( 0x0 ),	/* 0 */
/* 7802 */	NdrFcShort( 0x1 ),	/* 1 */
/* 7804 */	NdrFcShort( 0x0 ),	/* 0 */

	/* Parameter bstrName */

/* 7806 */	NdrFcShort( 0x8b ),	/* Flags:  must size, must free, in, by val, */
/* 7808 */	NdrFcShort( 0x4 ),	/* x86 Stack size/offset = 4 */
/* 7810 */	NdrFcShort( 0x20 ),	/* Type Offset=32 */

	/* Return value */

/* 7812 */	NdrFcShort( 0x70 ),	/* Flags:  out, return, base type, */
/* 7814 */	NdrFcShort( 0x8 ),	/* x86 Stack size/offset = 8 */
/* 7816 */	0x8,		/* FC_LONG */
			0x0,		/* 0 */

	/* Procedure get_DeviceID */


	/* Procedure get_Data */

/* 7818 */	0x33,		/* FC_AUTO_HANDLE */
			0x6c,		/* Old Flags:  object, Oi2 */
/* 7820 */	NdrFcLong( 0x0 ),	/* 0 */
/* 7824 */	NdrFcShort( 0x7 ),	/* 7 */
/* 7826 */	NdrFcShort( 0xc ),	/* x86 Stack size/offset = 12 */
/* 7828 */	NdrFcShort( 0x0 ),	/* 0 */
/* 7830 */	NdrFcShort( 0x8 ),	/* 8 */
/* 7832 */	0x45,		/* Oi2 Flags:  srv must size, has return, has ext, */
			0x2,		/* 2 */
/* 7834 */	0x8,		/* 8 */
			0x3,		/* Ext Flags:  new corr desc, clt corr check, */
/* 7836 */	NdrFcShort( 0x1 ),	/* 1 */
/* 7838 */	NdrFcShort( 0x0 ),	/* 0 */
/* 7840 */	NdrFcShort( 0x0 ),	/* 0 */

	/* Parameter pbstrDeviceID */


	/* Parameter pbstrData */

/* 7842 */	NdrFcShort( 0x2113 ),	/* Flags:  must size, must free, out, simple ref, srv alloc size=8 */
/* 7844 */	NdrFcShort( 0x4 ),	/* x86 Stack size/offset = 4 */
/* 7846 */	NdrFcShort( 0x46a ),	/* Type Offset=1130 */

	/* Return value */


	/* Return value */

/* 7848 */	NdrFcShort( 0x70 ),	/* Flags:  out, return, base type, */
/* 7850 */	NdrFcShort( 0x8 ),	/* x86 Stack size/offset = 8 */
/* 7852 */	0x8,		/* FC_LONG */
			0x0,		/* 0 */

	/* Procedure put_SearchDomain */


	/* Procedure put_Data */

/* 7854 */	0x33,		/* FC_AUTO_HANDLE */
			0x6c,		/* Old Flags:  object, Oi2 */
/* 7856 */	NdrFcLong( 0x0 ),	/* 0 */
/* 7860 */	NdrFcShort( 0x8 ),	/* 8 */
/* 7862 */	NdrFcShort( 0xc ),	/* x86 Stack size/offset = 12 */
/* 7864 */	NdrFcShort( 0x0 ),	/* 0 */
/* 7866 */	NdrFcShort( 0x8 ),	/* 8 */
/* 7868 */	0x46,		/* Oi2 Flags:  clt must size, has return, has ext, */
			0x2,		/* 2 */
/* 7870 */	0x8,		/* 8 */
			0x5,		/* Ext Flags:  new corr desc, srv corr check, */
/* 7872 */	NdrFcShort( 0x0 ),	/* 0 */
/* 7874 */	NdrFcShort( 0x1 ),	/* 1 */
/* 7876 */	NdrFcShort( 0x0 ),	/* 0 */

	/* Parameter bstrDomain */


	/* Parameter bstrData */

/* 7878 */	NdrFcShort( 0x8b ),	/* Flags:  must size, must free, in, by val, */
/* 7880 */	NdrFcShort( 0x4 ),	/* x86 Stack size/offset = 4 */
/* 7882 */	NdrFcShort( 0x20 ),	/* Type Offset=32 */

	/* Return value */


	/* Return value */

/* 7884 */	NdrFcShort( 0x70 ),	/* Flags:  out, return, base type, */
/* 7886 */	NdrFcShort( 0x8 ),	/* x86 Stack size/offset = 8 */
/* 7888 */	0x8,		/* FC_LONG */
			0x0,		/* 0 */

	/* Procedure get_Persistent */

/* 7890 */	0x33,		/* FC_AUTO_HANDLE */
			0x6c,		/* Old Flags:  object, Oi2 */
/* 7892 */	NdrFcLong( 0x0 ),	/* 0 */
/* 7896 */	NdrFcShort( 0x9 ),	/* 9 */
/* 7898 */	NdrFcShort( 0xc ),	/* x86 Stack size/offset = 12 */
/* 7900 */	NdrFcShort( 0x0 ),	/* 0 */
/* 7902 */	NdrFcShort( 0x22 ),	/* 34 */
/* 7904 */	0x44,		/* Oi2 Flags:  has return, has ext, */
			0x2,		/* 2 */
/* 7906 */	0x8,		/* 8 */
			0x1,		/* Ext Flags:  new corr desc, */
/* 7908 */	NdrFcShort( 0x0 ),	/* 0 */
/* 7910 */	NdrFcShort( 0x0 ),	/* 0 */
/* 7912 */	NdrFcShort( 0x0 ),	/* 0 */

	/* Parameter pfPersistent */

/* 7914 */	NdrFcShort( 0x2150 ),	/* Flags:  out, base type, simple ref, srv alloc size=8 */
/* 7916 */	NdrFcShort( 0x4 ),	/* x86 Stack size/offset = 4 */
/* 7918 */	0x6,		/* FC_SHORT */
			0x0,		/* 0 */

	/* Return value */

/* 7920 */	NdrFcShort( 0x70 ),	/* Flags:  out, return, base type, */
/* 7922 */	NdrFcShort( 0x8 ),	/* x86 Stack size/offset = 8 */
/* 7924 */	0x8,		/* FC_LONG */
			0x0,		/* 0 */

	/* Procedure put_Persistent */

/* 7926 */	0x33,		/* FC_AUTO_HANDLE */
			0x6c,		/* Old Flags:  object, Oi2 */
/* 7928 */	NdrFcLong( 0x0 ),	/* 0 */
/* 7932 */	NdrFcShort( 0xa ),	/* 10 */
/* 7934 */	NdrFcShort( 0xc ),	/* x86 Stack size/offset = 12 */
/* 7936 */	NdrFcShort( 0x6 ),	/* 6 */
/* 7938 */	NdrFcShort( 0x8 ),	/* 8 */
/* 7940 */	0x44,		/* Oi2 Flags:  has return, has ext, */
			0x2,		/* 2 */
/* 7942 */	0x8,		/* 8 */
			0x1,		/* Ext Flags:  new corr desc, */
/* 7944 */	NdrFcShort( 0x0 ),	/* 0 */
/* 7946 */	NdrFcShort( 0x0 ),	/* 0 */
/* 7948 */	NdrFcShort( 0x0 ),	/* 0 */

	/* Parameter fPersistent */

/* 7950 */	NdrFcShort( 0x48 ),	/* Flags:  in, base type, */
/* 7952 */	NdrFcShort( 0x4 ),	/* x86 Stack size/offset = 4 */
/* 7954 */	0x6,		/* FC_SHORT */
			0x0,		/* 0 */

	/* Return value */

/* 7956 */	NdrFcShort( 0x70 ),	/* Flags:  out, return, base type, */
/* 7958 */	NdrFcShort( 0x8 ),	/* x86 Stack size/offset = 8 */
/* 7960 */	0x8,		/* FC_LONG */
			0x0,		/* 0 */

	/* Procedure get_State */


	/* Procedure get_Status */

/* 7962 */	0x33,		/* FC_AUTO_HANDLE */
			0x6c,		/* Old Flags:  object, Oi2 */
/* 7964 */	NdrFcLong( 0x0 ),	/* 0 */
/* 7968 */	NdrFcShort( 0xb ),	/* 11 */
/* 7970 */	NdrFcShort( 0xc ),	/* x86 Stack size/offset = 12 */
/* 7972 */	NdrFcShort( 0x0 ),	/* 0 */
/* 7974 */	NdrFcShort( 0x22 ),	/* 34 */
/* 7976 */	0x44,		/* Oi2 Flags:  has return, has ext, */
			0x2,		/* 2 */
/* 7978 */	0x8,		/* 8 */
			0x1,		/* Ext Flags:  new corr desc, */
/* 7980 */	NdrFcShort( 0x0 ),	/* 0 */
/* 7982 */	NdrFcShort( 0x0 ),	/* 0 */
/* 7984 */	NdrFcShort( 0x0 ),	/* 0 */

	/* Parameter penState */


	/* Parameter penStatus */

/* 7986 */	NdrFcShort( 0x2010 ),	/* Flags:  out, srv alloc size=8 */
/* 7988 */	NdrFcShort( 0x4 ),	/* x86 Stack size/offset = 4 */
/* 7990 */	NdrFcShort( 0x52 ),	/* Type Offset=82 */

	/* Return value */


	/* Return value */

/* 7992 */	NdrFcShort( 0x70 ),	/* Flags:  out, return, base type, */
/* 7994 */	NdrFcShort( 0x8 ),	/* x86 Stack size/offset = 8 */
/* 7996 */	0x8,		/* FC_LONG */
			0x0,		/* 0 */

	/* Procedure get_Profile */


	/* Procedure get_Profile */

/* 7998 */	0x33,		/* FC_AUTO_HANDLE */
			0x6c,		/* Old Flags:  object, Oi2 */
/* 8000 */	NdrFcLong( 0x0 ),	/* 0 */
/* 8004 */	NdrFcShort( 0xd ),	/* 13 */
/* 8006 */	NdrFcShort( 0xc ),	/* x86 Stack size/offset = 12 */
/* 8008 */	NdrFcShort( 0x0 ),	/* 0 */
/* 8010 */	NdrFcShort( 0x8 ),	/* 8 */
/* 8012 */	0x45,		/* Oi2 Flags:  srv must size, has return, has ext, */
			0x2,		/* 2 */
/* 8014 */	0x8,		/* 8 */
			0x1,		/* Ext Flags:  new corr desc, */
/* 8016 */	NdrFcShort( 0x0 ),	/* 0 */
/* 8018 */	NdrFcShort( 0x0 ),	/* 0 */
/* 8020 */	NdrFcShort( 0x0 ),	/* 0 */

	/* Parameter ppProfile */


	/* Parameter ppProfile */

/* 8022 */	NdrFcShort( 0x13 ),	/* Flags:  must size, must free, out, */
/* 8024 */	NdrFcShort( 0x4 ),	/* x86 Stack size/offset = 4 */
/* 8026 */	NdrFcShort( 0x810 ),	/* Type Offset=2064 */

	/* Return value */


	/* Return value */

/* 8028 */	NdrFcShort( 0x70 ),	/* Flags:  out, return, base type, */
/* 8030 */	NdrFcShort( 0x8 ),	/* x86 Stack size/offset = 8 */
/* 8032 */	0x8,		/* FC_LONG */
			0x0,		/* 0 */

	/* Procedure Refresh */

/* 8034 */	0x33,		/* FC_AUTO_HANDLE */
			0x6c,		/* Old Flags:  object, Oi2 */
/* 8036 */	NdrFcLong( 0x0 ),	/* 0 */
/* 8040 */	NdrFcShort( 0xe ),	/* 14 */
/* 8042 */	NdrFcShort( 0x8 ),	/* x86 Stack size/offset = 8 */
/* 8044 */	NdrFcShort( 0x0 ),	/* 0 */
/* 8046 */	NdrFcShort( 0x8 ),	/* 8 */
/* 8048 */	0x44,		/* Oi2 Flags:  has return, has ext, */
			0x1,		/* 1 */
/* 8050 */	0x8,		/* 8 */
			0x1,		/* Ext Flags:  new corr desc, */
/* 8052 */	NdrFcShort( 0x0 ),	/* 0 */
/* 8054 */	NdrFcShort( 0x0 ),	/* 0 */
/* 8056 */	NdrFcShort( 0x0 ),	/* 0 */

	/* Return value */

/* 8058 */	NdrFcShort( 0x70 ),	/* Flags:  out, return, base type, */
/* 8060 */	NdrFcShort( 0x4 ),	/* x86 Stack size/offset = 4 */
/* 8062 */	0x8,		/* FC_LONG */
			0x0,		/* 0 */

	/* Procedure EnumerateGroups */

/* 8064 */	0x33,		/* FC_AUTO_HANDLE */
			0x6c,		/* Old Flags:  object, Oi2 */
/* 8066 */	NdrFcLong( 0x0 ),	/* 0 */
/* 8070 */	NdrFcShort( 0xf ),	/* 15 */
/* 8072 */	NdrFcShort( 0xc ),	/* x86 Stack size/offset = 12 */
/* 8074 */	NdrFcShort( 0x0 ),	/* 0 */
/* 8076 */	NdrFcShort( 0x8 ),	/* 8 */
/* 8078 */	0x45,		/* Oi2 Flags:  srv must size, has return, has ext, */
			0x2,		/* 2 */
/* 8080 */	0x8,		/* 8 */
			0x1,		/* Ext Flags:  new corr desc, */
/* 8082 */	NdrFcShort( 0x0 ),	/* 0 */
/* 8084 */	NdrFcShort( 0x0 ),	/* 0 */
/* 8086 */	NdrFcShort( 0x0 ),	/* 0 */

	/* Parameter ppEnum */

/* 8088 */	NdrFcShort( 0x13 ),	/* Flags:  must size, must free, out, */
/* 8090 */	NdrFcShort( 0x4 ),	/* x86 Stack size/offset = 4 */
/* 8092 */	NdrFcShort( 0x7fa ),	/* Type Offset=2042 */

	/* Return value */

/* 8094 */	NdrFcShort( 0x70 ),	/* Flags:  out, return, base type, */
/* 8096 */	NdrFcShort( 0x8 ),	/* x86 Stack size/offset = 8 */
/* 8098 */	0x8,		/* FC_LONG */
			0x0,		/* 0 */

	/* Procedure get_Groups */

/* 8100 */	0x33,		/* FC_AUTO_HANDLE */
			0x6c,		/* Old Flags:  object, Oi2 */
/* 8102 */	NdrFcLong( 0x0 ),	/* 0 */
/* 8106 */	NdrFcShort( 0x10 ),	/* 16 */
/* 8108 */	NdrFcShort( 0xc ),	/* x86 Stack size/offset = 12 */
/* 8110 */	NdrFcShort( 0x0 ),	/* 0 */
/* 8112 */	NdrFcShort( 0x8 ),	/* 8 */
/* 8114 */	0x45,		/* Oi2 Flags:  srv must size, has return, has ext, */
			0x2,		/* 2 */
/* 8116 */	0x8,		/* 8 */
			0x1,		/* Ext Flags:  new corr desc, */
/* 8118 */	NdrFcShort( 0x0 ),	/* 0 */
/* 8120 */	NdrFcShort( 0x0 ),	/* 0 */
/* 8122 */	NdrFcShort( 0x0 ),	/* 0 */

	/* Parameter ppCollection */

/* 8124 */	NdrFcShort( 0x13 ),	/* Flags:  must size, must free, out, */
/* 8126 */	NdrFcShort( 0x4 ),	/* x86 Stack size/offset = 4 */
/* 8128 */	NdrFcShort( 0x826 ),	/* Type Offset=2086 */

	/* Return value */

/* 8130 */	NdrFcShort( 0x70 ),	/* Flags:  out, return, base type, */
/* 8132 */	NdrFcShort( 0x8 ),	/* x86 Stack size/offset = 8 */
/* 8134 */	0x8,		/* FC_LONG */
			0x0,		/* 0 */

	/* Procedure get_PresenceProperty */

/* 8136 */	0x33,		/* FC_AUTO_HANDLE */
			0x6c,		/* Old Flags:  object, Oi2 */
/* 8138 */	NdrFcLong( 0x0 ),	/* 0 */
/* 8142 */	NdrFcShort( 0x11 ),	/* 17 */
/* 8144 */	NdrFcShort( 0x10 ),	/* x86 Stack size/offset = 16 */
/* 8146 */	NdrFcShort( 0x6 ),	/* 6 */
/* 8148 */	NdrFcShort( 0x8 ),	/* 8 */
/* 8150 */	0x45,		/* Oi2 Flags:  srv must size, has return, has ext, */
			0x3,		/* 3 */
/* 8152 */	0x8,		/* 8 */
			0x3,		/* Ext Flags:  new corr desc, clt corr check, */
/* 8154 */	NdrFcShort( 0x1 ),	/* 1 */
/* 8156 */	NdrFcShort( 0x0 ),	/* 0 */
/* 8158 */	NdrFcShort( 0x0 ),	/* 0 */

	/* Parameter enProperty */

/* 8160 */	NdrFcShort( 0x48 ),	/* Flags:  in, base type, */
/* 8162 */	NdrFcShort( 0x4 ),	/* x86 Stack size/offset = 4 */
/* 8164 */	0xd,		/* FC_ENUM16 */
			0x0,		/* 0 */

	/* Parameter pbstrProperty */

/* 8166 */	NdrFcShort( 0x2113 ),	/* Flags:  must size, must free, out, simple ref, srv alloc size=8 */
/* 8168 */	NdrFcShort( 0x8 ),	/* x86 Stack size/offset = 8 */
/* 8170 */	NdrFcShort( 0x46a ),	/* Type Offset=1130 */

	/* Return value */

/* 8172 */	NdrFcShort( 0x70 ),	/* Flags:  out, return, base type, */
/* 8174 */	NdrFcShort( 0xc ),	/* x86 Stack size/offset = 12 */
/* 8176 */	0x8,		/* FC_LONG */
			0x0,		/* 0 */

	/* Procedure EnumeratePresenceDevices */

/* 8178 */	0x33,		/* FC_AUTO_HANDLE */
			0x6c,		/* Old Flags:  object, Oi2 */
/* 8180 */	NdrFcLong( 0x0 ),	/* 0 */
/* 8184 */	NdrFcShort( 0x12 ),	/* 18 */
/* 8186 */	NdrFcShort( 0xc ),	/* x86 Stack size/offset = 12 */
/* 8188 */	NdrFcShort( 0x0 ),	/* 0 */
/* 8190 */	NdrFcShort( 0x8 ),	/* 8 */
/* 8192 */	0x45,		/* Oi2 Flags:  srv must size, has return, has ext, */
			0x2,		/* 2 */
/* 8194 */	0x8,		/* 8 */
			0x1,		/* Ext Flags:  new corr desc, */
/* 8196 */	NdrFcShort( 0x0 ),	/* 0 */
/* 8198 */	NdrFcShort( 0x0 ),	/* 0 */
/* 8200 */	NdrFcShort( 0x0 ),	/* 0 */

	/* Parameter ppEnumDevices */

/* 8202 */	NdrFcShort( 0x13 ),	/* Flags:  must size, must free, out, */
/* 8204 */	NdrFcShort( 0x4 ),	/* x86 Stack size/offset = 4 */
/* 8206 */	NdrFcShort( 0x83c ),	/* Type Offset=2108 */

	/* Return value */

/* 8208 */	NdrFcShort( 0x70 ),	/* Flags:  out, return, base type, */
/* 8210 */	NdrFcShort( 0x8 ),	/* x86 Stack size/offset = 8 */
/* 8212 */	0x8,		/* FC_LONG */
			0x0,		/* 0 */

	/* Procedure get_PresenceDevices */

/* 8214 */	0x33,		/* FC_AUTO_HANDLE */
			0x6c,		/* Old Flags:  object, Oi2 */
/* 8216 */	NdrFcLong( 0x0 ),	/* 0 */
/* 8220 */	NdrFcShort( 0x13 ),	/* 19 */
/* 8222 */	NdrFcShort( 0xc ),	/* x86 Stack size/offset = 12 */
/* 8224 */	NdrFcShort( 0x0 ),	/* 0 */
/* 8226 */	NdrFcShort( 0x8 ),	/* 8 */
/* 8228 */	0x45,		/* Oi2 Flags:  srv must size, has return, has ext, */
			0x2,		/* 2 */
/* 8230 */	0x8,		/* 8 */
			0x1,		/* Ext Flags:  new corr desc, */
/* 8232 */	NdrFcShort( 0x0 ),	/* 0 */
/* 8234 */	NdrFcShort( 0x0 ),	/* 0 */
/* 8236 */	NdrFcShort( 0x0 ),	/* 0 */

	/* Parameter ppDevicesCollection */

/* 8238 */	NdrFcShort( 0x13 ),	/* Flags:  must size, must free, out, */
/* 8240 */	NdrFcShort( 0x4 ),	/* x86 Stack size/offset = 4 */
/* 8242 */	NdrFcShort( 0x852 ),	/* Type Offset=2130 */

	/* Return value */

/* 8244 */	NdrFcShort( 0x70 ),	/* Flags:  out, return, base type, */
/* 8246 */	NdrFcShort( 0x8 ),	/* x86 Stack size/offset = 8 */
/* 8248 */	0x8,		/* FC_LONG */
			0x0,		/* 0 */

	/* Procedure get_Scope */

/* 8250 */	0x33,		/* FC_AUTO_HANDLE */
			0x6c,		/* Old Flags:  object, Oi2 */
/* 8252 */	NdrFcLong( 0x0 ),	/* 0 */
/* 8256 */	NdrFcShort( 0xe ),	/* 14 */
/* 8258 */	NdrFcShort( 0xc ),	/* x86 Stack size/offset = 12 */
/* 8260 */	NdrFcShort( 0x0 ),	/* 0 */
/* 8262 */	NdrFcShort( 0x22 ),	/* 34 */
/* 8264 */	0x44,		/* Oi2 Flags:  has return, has ext, */
			0x2,		/* 2 */
/* 8266 */	0x8,		/* 8 */
			0x1,		/* Ext Flags:  new corr desc, */
/* 8268 */	NdrFcShort( 0x0 ),	/* 0 */
/* 8270 */	NdrFcShort( 0x0 ),	/* 0 */
/* 8272 */	NdrFcShort( 0x0 ),	/* 0 */

	/* Parameter penScope */

/* 8274 */	NdrFcShort( 0x2010 ),	/* Flags:  out, srv alloc size=8 */
/* 8276 */	NdrFcShort( 0x4 ),	/* x86 Stack size/offset = 4 */
/* 8278 */	NdrFcShort( 0x52 ),	/* Type Offset=82 */

	/* Return value */

/* 8280 */	NdrFcShort( 0x70 ),	/* Flags:  out, return, base type, */
/* 8282 */	NdrFcShort( 0x8 ),	/* x86 Stack size/offset = 8 */
/* 8284 */	0x8,		/* FC_LONG */
			0x0,		/* 0 */

	/* Procedure AddBuddy */

/* 8286 */	0x33,		/* FC_AUTO_HANDLE */
			0x6c,		/* Old Flags:  object, Oi2 */
/* 8288 */	NdrFcLong( 0x0 ),	/* 0 */
/* 8292 */	NdrFcShort( 0x5 ),	/* 5 */
/* 8294 */	NdrFcShort( 0xc ),	/* x86 Stack size/offset = 12 */
/* 8296 */	NdrFcShort( 0x0 ),	/* 0 */
/* 8298 */	NdrFcShort( 0x8 ),	/* 8 */
/* 8300 */	0x46,		/* Oi2 Flags:  clt must size, has return, has ext, */
			0x2,		/* 2 */
/* 8302 */	0x8,		/* 8 */
			0x1,		/* Ext Flags:  new corr desc, */
/* 8304 */	NdrFcShort( 0x0 ),	/* 0 */
/* 8306 */	NdrFcShort( 0x0 ),	/* 0 */
/* 8308 */	NdrFcShort( 0x0 ),	/* 0 */

	/* Parameter pBuddy */

/* 8310 */	NdrFcShort( 0xb ),	/* Flags:  must size, must free, in, */
/* 8312 */	NdrFcShort( 0x4 ),	/* x86 Stack size/offset = 4 */
/* 8314 */	NdrFcShort( 0x868 ),	/* Type Offset=2152 */

	/* Return value */

/* 8316 */	NdrFcShort( 0x70 ),	/* Flags:  out, return, base type, */
/* 8318 */	NdrFcShort( 0x8 ),	/* x86 Stack size/offset = 8 */
/* 8320 */	0x8,		/* FC_LONG */
			0x0,		/* 0 */

	/* Procedure RemoveBuddy */

/* 8322 */	0x33,		/* FC_AUTO_HANDLE */
			0x6c,		/* Old Flags:  object, Oi2 */
/* 8324 */	NdrFcLong( 0x0 ),	/* 0 */
/* 8328 */	NdrFcShort( 0x6 ),	/* 6 */
/* 8330 */	NdrFcShort( 0xc ),	/* x86 Stack size/offset = 12 */
/* 8332 */	NdrFcShort( 0x0 ),	/* 0 */
/* 8334 */	NdrFcShort( 0x8 ),	/* 8 */
/* 8336 */	0x46,		/* Oi2 Flags:  clt must size, has return, has ext, */
			0x2,		/* 2 */
/* 8338 */	0x8,		/* 8 */
			0x1,		/* Ext Flags:  new corr desc, */
/* 8340 */	NdrFcShort( 0x0 ),	/* 0 */
/* 8342 */	NdrFcShort( 0x0 ),	/* 0 */
/* 8344 */	NdrFcShort( 0x0 ),	/* 0 */

	/* Parameter pBuddy */

/* 8346 */	NdrFcShort( 0xb ),	/* Flags:  must size, must free, in, */
/* 8348 */	NdrFcShort( 0x4 ),	/* x86 Stack size/offset = 4 */
/* 8350 */	NdrFcShort( 0x868 ),	/* Type Offset=2152 */

	/* Return value */

/* 8352 */	NdrFcShort( 0x70 ),	/* Flags:  out, return, base type, */
/* 8354 */	NdrFcShort( 0x8 ),	/* x86 Stack size/offset = 8 */
/* 8356 */	0x8,		/* FC_LONG */
			0x0,		/* 0 */

	/* Procedure EnumerateBuddies */

/* 8358 */	0x33,		/* FC_AUTO_HANDLE */
			0x6c,		/* Old Flags:  object, Oi2 */
/* 8360 */	NdrFcLong( 0x0 ),	/* 0 */
/* 8364 */	NdrFcShort( 0x7 ),	/* 7 */
/* 8366 */	NdrFcShort( 0xc ),	/* x86 Stack size/offset = 12 */
/* 8368 */	NdrFcShort( 0x0 ),	/* 0 */
/* 8370 */	NdrFcShort( 0x8 ),	/* 8 */
/* 8372 */	0x45,		/* Oi2 Flags:  srv must size, has return, has ext, */
			0x2,		/* 2 */
/* 8374 */	0x8,		/* 8 */
			0x1,		/* Ext Flags:  new corr desc, */
/* 8376 */	NdrFcShort( 0x0 ),	/* 0 */
/* 8378 */	NdrFcShort( 0x0 ),	/* 0 */
/* 8380 */	NdrFcShort( 0x0 ),	/* 0 */

	/* Parameter ppEnum */

/* 8382 */	NdrFcShort( 0x13 ),	/* Flags:  must size, must free, out, */
/* 8384 */	NdrFcShort( 0x4 ),	/* x86 Stack size/offset = 4 */
/* 8386 */	NdrFcShort( 0x87a ),	/* Type Offset=2170 */

	/* Return value */

/* 8388 */	NdrFcShort( 0x70 ),	/* Flags:  out, return, base type, */
/* 8390 */	NdrFcShort( 0x8 ),	/* x86 Stack size/offset = 8 */
/* 8392 */	0x8,		/* FC_LONG */
			0x0,		/* 0 */

	/* Procedure get_Results */


	/* Procedure get_Buddies */

/* 8394 */	0x33,		/* FC_AUTO_HANDLE */
			0x6c,		/* Old Flags:  object, Oi2 */
/* 8396 */	NdrFcLong( 0x0 ),	/* 0 */
/* 8400 */	NdrFcShort( 0x8 ),	/* 8 */
/* 8402 */	NdrFcShort( 0xc ),	/* x86 Stack size/offset = 12 */
/* 8404 */	NdrFcShort( 0x0 ),	/* 0 */
/* 8406 */	NdrFcShort( 0x8 ),	/* 8 */
/* 8408 */	0x45,		/* Oi2 Flags:  srv must size, has return, has ext, */
			0x2,		/* 2 */
/* 8410 */	0x8,		/* 8 */
			0x1,		/* Ext Flags:  new corr desc, */
/* 8412 */	NdrFcShort( 0x0 ),	/* 0 */
/* 8414 */	NdrFcShort( 0x0 ),	/* 0 */
/* 8416 */	NdrFcShort( 0x0 ),	/* 0 */

	/* Parameter ppCollection */


	/* Parameter ppCollection */

/* 8418 */	NdrFcShort( 0x13 ),	/* Flags:  must size, must free, out, */
/* 8420 */	NdrFcShort( 0x4 ),	/* x86 Stack size/offset = 4 */
/* 8422 */	NdrFcShort( 0x852 ),	/* Type Offset=2130 */

	/* Return value */


	/* Return value */

/* 8424 */	NdrFcShort( 0x70 ),	/* Flags:  out, return, base type, */
/* 8426 */	NdrFcShort( 0x8 ),	/* x86 Stack size/offset = 8 */
/* 8428 */	0x8,		/* FC_LONG */
			0x0,		/* 0 */

	/* Procedure put_Data */

/* 8430 */	0x33,		/* FC_AUTO_HANDLE */
			0x6c,		/* Old Flags:  object, Oi2 */
/* 8432 */	NdrFcLong( 0x0 ),	/* 0 */
/* 8436 */	NdrFcShort( 0xa ),	/* 10 */
/* 8438 */	NdrFcShort( 0xc ),	/* x86 Stack size/offset = 12 */
/* 8440 */	NdrFcShort( 0x0 ),	/* 0 */
/* 8442 */	NdrFcShort( 0x8 ),	/* 8 */
/* 8444 */	0x46,		/* Oi2 Flags:  clt must size, has return, has ext, */
			0x2,		/* 2 */
/* 8446 */	0x8,		/* 8 */
			0x5,		/* Ext Flags:  new corr desc, srv corr check, */
/* 8448 */	NdrFcShort( 0x0 ),	/* 0 */
/* 8450 */	NdrFcShort( 0x1 ),	/* 1 */
/* 8452 */	NdrFcShort( 0x0 ),	/* 0 */

	/* Parameter bstrData */

/* 8454 */	NdrFcShort( 0x8b ),	/* Flags:  must size, must free, in, by val, */
/* 8456 */	NdrFcShort( 0x4 ),	/* x86 Stack size/offset = 4 */
/* 8458 */	NdrFcShort( 0x20 ),	/* Type Offset=32 */

	/* Return value */

/* 8460 */	NdrFcShort( 0x70 ),	/* Flags:  out, return, base type, */
/* 8462 */	NdrFcShort( 0x8 ),	/* x86 Stack size/offset = 8 */
/* 8464 */	0x8,		/* FC_LONG */
			0x0,		/* 0 */

	/* Procedure get_Profile */

/* 8466 */	0x33,		/* FC_AUTO_HANDLE */
			0x6c,		/* Old Flags:  object, Oi2 */
/* 8468 */	NdrFcLong( 0x0 ),	/* 0 */
/* 8472 */	NdrFcShort( 0xb ),	/* 11 */
/* 8474 */	NdrFcShort( 0xc ),	/* x86 Stack size/offset = 12 */
/* 8476 */	NdrFcShort( 0x0 ),	/* 0 */
/* 8478 */	NdrFcShort( 0x8 ),	/* 8 */
/* 8480 */	0x45,		/* Oi2 Flags:  srv must size, has return, has ext, */
			0x2,		/* 2 */
/* 8482 */	0x8,		/* 8 */
			0x1,		/* Ext Flags:  new corr desc, */
/* 8484 */	NdrFcShort( 0x0 ),	/* 0 */
/* 8486 */	NdrFcShort( 0x0 ),	/* 0 */
/* 8488 */	NdrFcShort( 0x0 ),	/* 0 */

	/* Parameter ppProfile */

/* 8490 */	NdrFcShort( 0x13 ),	/* Flags:  must size, must free, out, */
/* 8492 */	NdrFcShort( 0x4 ),	/* x86 Stack size/offset = 4 */
/* 8494 */	NdrFcShort( 0x810 ),	/* Type Offset=2064 */

	/* Return value */

/* 8496 */	NdrFcShort( 0x70 ),	/* Flags:  out, return, base type, */
/* 8498 */	NdrFcShort( 0x8 ),	/* x86 Stack size/offset = 8 */
/* 8500 */	0x8,		/* FC_LONG */
			0x0,		/* 0 */

	/* Procedure Event */

/* 8502 */	0x33,		/* FC_AUTO_HANDLE */
			0x6c,		/* Old Flags:  object, Oi2 */
/* 8504 */	NdrFcLong( 0x0 ),	/* 0 */
/* 8508 */	NdrFcShort( 0x3 ),	/* 3 */
/* 8510 */	NdrFcShort( 0x10 ),	/* x86 Stack size/offset = 16 */
/* 8512 */	NdrFcShort( 0x6 ),	/* 6 */
/* 8514 */	NdrFcShort( 0x8 ),	/* 8 */
/* 8516 */	0x46,		/* Oi2 Flags:  clt must size, has return, has ext, */
			0x3,		/* 3 */
/* 8518 */	0x8,		/* 8 */
			0x1,		/* Ext Flags:  new corr desc, */
/* 8520 */	NdrFcShort( 0x0 ),	/* 0 */
/* 8522 */	NdrFcShort( 0x0 ),	/* 0 */
/* 8524 */	NdrFcShort( 0x0 ),	/* 0 */

	/* Parameter RTCEvent */

/* 8526 */	NdrFcShort( 0x48 ),	/* Flags:  in, base type, */
/* 8528 */	NdrFcShort( 0x4 ),	/* x86 Stack size/offset = 4 */
/* 8530 */	0xd,		/* FC_ENUM16 */
			0x0,		/* 0 */

	/* Parameter pEvent */

/* 8532 */	NdrFcShort( 0xb ),	/* Flags:  must size, must free, in, */
/* 8534 */	NdrFcShort( 0x8 ),	/* x86 Stack size/offset = 8 */
/* 8536 */	NdrFcShort( 0x890 ),	/* Type Offset=2192 */

	/* Return value */

/* 8538 */	NdrFcShort( 0x70 ),	/* Flags:  out, return, base type, */
/* 8540 */	NdrFcShort( 0xc ),	/* x86 Stack size/offset = 12 */
/* 8542 */	0x8,		/* FC_LONG */
			0x0,		/* 0 */

	/* Procedure GetMapping */

/* 8544 */	0x33,		/* FC_AUTO_HANDLE */
			0x6c,		/* Old Flags:  object, Oi2 */
/* 8546 */	NdrFcLong( 0x0 ),	/* 0 */
/* 8550 */	NdrFcShort( 0x3 ),	/* 3 */
/* 8552 */	NdrFcShort( 0x20 ),	/* x86 Stack size/offset = 32 */
/* 8554 */	NdrFcShort( 0x3e ),	/* 62 */
/* 8556 */	NdrFcShort( 0x40 ),	/* 64 */
/* 8558 */	0x47,		/* Oi2 Flags:  srv must size, clt must size, has return, has ext, */
			0x7,		/* 7 */
/* 8560 */	0x8,		/* 8 */
			0x7,		/* Ext Flags:  new corr desc, clt corr check, srv corr check, */
/* 8562 */	NdrFcShort( 0x2 ),	/* 2 */
/* 8564 */	NdrFcShort( 0x3 ),	/* 3 */
/* 8566 */	NdrFcShort( 0x0 ),	/* 0 */

	/* Parameter bstrRemoteAddress */

/* 8568 */	NdrFcShort( 0x8b ),	/* Flags:  must size, must free, in, by val, */
/* 8570 */	NdrFcShort( 0x4 ),	/* x86 Stack size/offset = 4 */
/* 8572 */	NdrFcShort( 0x20 ),	/* Type Offset=32 */

	/* Parameter enPortType */

/* 8574 */	NdrFcShort( 0x48 ),	/* Flags:  in, base type, */
/* 8576 */	NdrFcShort( 0x8 ),	/* x86 Stack size/offset = 8 */
/* 8578 */	0xd,		/* FC_ENUM16 */
			0x0,		/* 0 */

	/* Parameter pbstrInternalLocalAddress */

/* 8580 */	NdrFcShort( 0x11b ),	/* Flags:  must size, must free, in, out, simple ref, */
/* 8582 */	NdrFcShort( 0xc ),	/* x86 Stack size/offset = 12 */
/* 8584 */	NdrFcShort( 0x46a ),	/* Type Offset=1130 */

	/* Parameter plInternalLocalPort */

/* 8586 */	NdrFcShort( 0x158 ),	/* Flags:  in, out, base type, simple ref, */
/* 8588 */	NdrFcShort( 0x10 ),	/* x86 Stack size/offset = 16 */
/* 8590 */	0x8,		/* FC_LONG */
			0x0,		/* 0 */

	/* Parameter pbstrExternalLocalAddress */

/* 8592 */	NdrFcShort( 0x11b ),	/* Flags:  must size, must free, in, out, simple ref, */
/* 8594 */	NdrFcShort( 0x14 ),	/* x86 Stack size/offset = 20 */
/* 8596 */	NdrFcShort( 0x46a ),	/* Type Offset=1130 */

	/* Parameter plExternalLocalPort */

/* 8598 */	NdrFcShort( 0x158 ),	/* Flags:  in, out, base type, simple ref, */
/* 8600 */	NdrFcShort( 0x18 ),	/* x86 Stack size/offset = 24 */
/* 8602 */	0x8,		/* FC_LONG */
			0x0,		/* 0 */

	/* Return value */

/* 8604 */	NdrFcShort( 0x70 ),	/* Flags:  out, return, base type, */
/* 8606 */	NdrFcShort( 0x1c ),	/* x86 Stack size/offset = 28 */
/* 8608 */	0x8,		/* FC_LONG */
			0x0,		/* 0 */

	/* Procedure UpdateRemoteAddress */

/* 8610 */	0x33,		/* FC_AUTO_HANDLE */
			0x6c,		/* Old Flags:  object, Oi2 */
/* 8612 */	NdrFcLong( 0x0 ),	/* 0 */
/* 8616 */	NdrFcShort( 0x4 ),	/* 4 */
/* 8618 */	NdrFcShort( 0x1c ),	/* x86 Stack size/offset = 28 */
/* 8620 */	NdrFcShort( 0x10 ),	/* 16 */
/* 8622 */	NdrFcShort( 0x8 ),	/* 8 */
/* 8624 */	0x46,		/* Oi2 Flags:  clt must size, has return, has ext, */
			0x6,		/* 6 */
/* 8626 */	0x8,		/* 8 */
			0x5,		/* Ext Flags:  new corr desc, srv corr check, */
/* 8628 */	NdrFcShort( 0x0 ),	/* 0 */
/* 8630 */	NdrFcShort( 0x3 ),	/* 3 */
/* 8632 */	NdrFcShort( 0x0 ),	/* 0 */

	/* Parameter bstrRemoteAddress */

/* 8634 */	NdrFcShort( 0x8b ),	/* Flags:  must size, must free, in, by val, */
/* 8636 */	NdrFcShort( 0x4 ),	/* x86 Stack size/offset = 4 */
/* 8638 */	NdrFcShort( 0x20 ),	/* Type Offset=32 */

	/* Parameter bstrInternalLocalAddress */

/* 8640 */	NdrFcShort( 0x8b ),	/* Flags:  must size, must free, in, by val, */
/* 8642 */	NdrFcShort( 0x8 ),	/* x86 Stack size/offset = 8 */
/* 8644 */	NdrFcShort( 0x20 ),	/* Type Offset=32 */

	/* Parameter lInternalLocalPort */

/* 8646 */	NdrFcShort( 0x48 ),	/* Flags:  in, base type, */
/* 8648 */	NdrFcShort( 0xc ),	/* x86 Stack size/offset = 12 */
/* 8650 */	0x8,		/* FC_LONG */
			0x0,		/* 0 */

	/* Parameter bstrExternalLocalAddress */

/* 8652 */	NdrFcShort( 0x8b ),	/* Flags:  must size, must free, in, by val, */
/* 8654 */	NdrFcShort( 0x10 ),	/* x86 Stack size/offset = 16 */
/* 8656 */	NdrFcShort( 0x20 ),	/* Type Offset=32 */

	/* Parameter lExternalLocalPort */

/* 8658 */	NdrFcShort( 0x48 ),	/* Flags:  in, base type, */
/* 8660 */	NdrFcShort( 0x14 ),	/* x86 Stack size/offset = 20 */
/* 8662 */	0x8,		/* FC_LONG */
			0x0,		/* 0 */

	/* Return value */

/* 8664 */	NdrFcShort( 0x70 ),	/* Flags:  out, return, base type, */
/* 8666 */	NdrFcShort( 0x18 ),	/* x86 Stack size/offset = 24 */
/* 8668 */	0x8,		/* FC_LONG */
			0x0,		/* 0 */

	/* Procedure ReleaseMapping */

/* 8670 */	0x33,		/* FC_AUTO_HANDLE */
			0x6c,		/* Old Flags:  object, Oi2 */
/* 8672 */	NdrFcLong( 0x0 ),	/* 0 */
/* 8676 */	NdrFcShort( 0x5 ),	/* 5 */
/* 8678 */	NdrFcShort( 0x18 ),	/* x86 Stack size/offset = 24 */
/* 8680 */	NdrFcShort( 0x10 ),	/* 16 */
/* 8682 */	NdrFcShort( 0x8 ),	/* 8 */
/* 8684 */	0x46,		/* Oi2 Flags:  clt must size, has return, has ext, */
			0x5,		/* 5 */
/* 8686 */	0x8,		/* 8 */
			0x5,		/* Ext Flags:  new corr desc, srv corr check, */
/* 8688 */	NdrFcShort( 0x0 ),	/* 0 */
/* 8690 */	NdrFcShort( 0x2 ),	/* 2 */
/* 8692 */	NdrFcShort( 0x0 ),	/* 0 */

	/* Parameter bstrInternalLocalAddress */

/* 8694 */	NdrFcShort( 0x8b ),	/* Flags:  must size, must free, in, by val, */
/* 8696 */	NdrFcShort( 0x4 ),	/* x86 Stack size/offset = 4 */
/* 8698 */	NdrFcShort( 0x20 ),	/* Type Offset=32 */

	/* Parameter lInternalLocalPort */

/* 8700 */	NdrFcShort( 0x48 ),	/* Flags:  in, base type, */
/* 8702 */	NdrFcShort( 0x8 ),	/* x86 Stack size/offset = 8 */
/* 8704 */	0x8,		/* FC_LONG */
			0x0,		/* 0 */

	/* Parameter bstrExternalLocalAddress */

/* 8706 */	NdrFcShort( 0x8b ),	/* Flags:  must size, must free, in, by val, */
/* 8708 */	NdrFcShort( 0xc ),	/* x86 Stack size/offset = 12 */
/* 8710 */	NdrFcShort( 0x20 ),	/* Type Offset=32 */

	/* Parameter lExternalLocalAddress */

/* 8712 */	NdrFcShort( 0x48 ),	/* Flags:  in, base type, */
/* 8714 */	NdrFcShort( 0x10 ),	/* x86 Stack size/offset = 16 */
/* 8716 */	0x8,		/* FC_LONG */
			0x0,		/* 0 */

	/* Return value */

/* 8718 */	NdrFcShort( 0x70 ),	/* Flags:  out, return, base type, */
/* 8720 */	NdrFcShort( 0x14 ),	/* x86 Stack size/offset = 20 */
/* 8722 */	0x8,		/* FC_LONG */
			0x0,		/* 0 */

	/* Procedure UpdateRemoteAddressEx */

/* 8724 */	0x33,		/* FC_AUTO_HANDLE */
			0x6c,		/* Old Flags:  object, Oi2 */
/* 8726 */	NdrFcLong( 0x0 ),	/* 0 */
/* 8730 */	NdrFcShort( 0x6 ),	/* 6 */
/* 8732 */	NdrFcShort( 0x20 ),	/* x86 Stack size/offset = 32 */
/* 8734 */	NdrFcShort( 0x18 ),	/* 24 */
/* 8736 */	NdrFcShort( 0x8 ),	/* 8 */
/* 8738 */	0x46,		/* Oi2 Flags:  clt must size, has return, has ext, */
			0x7,		/* 7 */
/* 8740 */	0x8,		/* 8 */
			0x5,		/* Ext Flags:  new corr desc, srv corr check, */
/* 8742 */	NdrFcShort( 0x0 ),	/* 0 */
/* 8744 */	NdrFcShort( 0x3 ),	/* 3 */
/* 8746 */	NdrFcShort( 0x0 ),	/* 0 */

	/* Parameter bstrRemoteAddress */

/* 8748 */	NdrFcShort( 0x8b ),	/* Flags:  must size, must free, in, by val, */
/* 8750 */	NdrFcShort( 0x4 ),	/* x86 Stack size/offset = 4 */
/* 8752 */	NdrFcShort( 0x20 ),	/* Type Offset=32 */

	/* Parameter lRemotePort */

/* 8754 */	NdrFcShort( 0x48 ),	/* Flags:  in, base type, */
/* 8756 */	NdrFcShort( 0x8 ),	/* x86 Stack size/offset = 8 */
/* 8758 */	0x8,		/* FC_LONG */
			0x0,		/* 0 */

	/* Parameter bstrInternalLocalAddress */

/* 8760 */	NdrFcShort( 0x8b ),	/* Flags:  must size, must free, in, by val, */
/* 8762 */	NdrFcShort( 0xc ),	/* x86 Stack size/offset = 12 */
/* 8764 */	NdrFcShort( 0x20 ),	/* Type Offset=32 */

	/* Parameter lInternalLocalPort */

/* 8766 */	NdrFcShort( 0x48 ),	/* Flags:  in, base type, */
/* 8768 */	NdrFcShort( 0x10 ),	/* x86 Stack size/offset = 16 */
/* 8770 */	0x8,		/* FC_LONG */
			0x0,		/* 0 */

	/* Parameter bstrExternalLocalAddress */

/* 8772 */	NdrFcShort( 0x8b ),	/* Flags:  must size, must free, in, by val, */
/* 8774 */	NdrFcShort( 0x14 ),	/* x86 Stack size/offset = 20 */
/* 8776 */	NdrFcShort( 0x20 ),	/* Type Offset=32 */

	/* Parameter lExternalLocalPort */

/* 8778 */	NdrFcShort( 0x48 ),	/* Flags:  in, base type, */
/* 8780 */	NdrFcShort( 0x18 ),	/* x86 Stack size/offset = 24 */
/* 8782 */	0x8,		/* FC_LONG */
			0x0,		/* 0 */

	/* Return value */

/* 8784 */	NdrFcShort( 0x70 ),	/* Flags:  out, return, base type, */
/* 8786 */	NdrFcShort( 0x1c ),	/* x86 Stack size/offset = 28 */
/* 8788 */	0x8,		/* FC_LONG */
			0x0,		/* 0 */

	/* Procedure SetPortManager */

/* 8790 */	0x33,		/* FC_AUTO_HANDLE */
			0x6c,		/* Old Flags:  object, Oi2 */
/* 8792 */	NdrFcLong( 0x0 ),	/* 0 */
/* 8796 */	NdrFcShort( 0x3 ),	/* 3 */
/* 8798 */	NdrFcShort( 0xc ),	/* x86 Stack size/offset = 12 */
/* 8800 */	NdrFcShort( 0x0 ),	/* 0 */
/* 8802 */	NdrFcShort( 0x8 ),	/* 8 */
/* 8804 */	0x46,		/* Oi2 Flags:  clt must size, has return, has ext, */
			0x2,		/* 2 */
/* 8806 */	0x8,		/* 8 */
			0x1,		/* Ext Flags:  new corr desc, */
/* 8808 */	NdrFcShort( 0x0 ),	/* 0 */
/* 8810 */	NdrFcShort( 0x0 ),	/* 0 */
/* 8812 */	NdrFcShort( 0x0 ),	/* 0 */

	/* Parameter pPortManager */

/* 8814 */	NdrFcShort( 0xb ),	/* Flags:  must size, must free, in, */
/* 8816 */	NdrFcShort( 0x4 ),	/* x86 Stack size/offset = 4 */
/* 8818 */	NdrFcShort( 0x8aa ),	/* Type Offset=2218 */

	/* Return value */

/* 8820 */	NdrFcShort( 0x70 ),	/* Flags:  out, return, base type, */
/* 8822 */	NdrFcShort( 0x8 ),	/* x86 Stack size/offset = 8 */
/* 8824 */	0x8,		/* FC_LONG */
			0x0,		/* 0 */

	/* Procedure StartListenAddressAndPort */

/* 8826 */	0x33,		/* FC_AUTO_HANDLE */
			0x6c,		/* Old Flags:  object, Oi2 */
/* 8828 */	NdrFcLong( 0x0 ),	/* 0 */
/* 8832 */	NdrFcShort( 0x3 ),	/* 3 */
/* 8834 */	NdrFcShort( 0x10 ),	/* x86 Stack size/offset = 16 */
/* 8836 */	NdrFcShort( 0x8 ),	/* 8 */
/* 8838 */	NdrFcShort( 0x8 ),	/* 8 */
/* 8840 */	0x46,		/* Oi2 Flags:  clt must size, has return, has ext, */
			0x3,		/* 3 */
/* 8842 */	0x8,		/* 8 */
			0x5,		/* Ext Flags:  new corr desc, srv corr check, */
/* 8844 */	NdrFcShort( 0x0 ),	/* 0 */
/* 8846 */	NdrFcShort( 0x1 ),	/* 1 */
/* 8848 */	NdrFcShort( 0x0 ),	/* 0 */

	/* Parameter bstrInternalLocalAddress */

/* 8850 */	NdrFcShort( 0x8b ),	/* Flags:  must size, must free, in, by val, */
/* 8852 */	NdrFcShort( 0x4 ),	/* x86 Stack size/offset = 4 */
/* 8854 */	NdrFcShort( 0x20 ),	/* Type Offset=32 */

	/* Parameter lInternalLocalPort */

/* 8856 */	NdrFcShort( 0x48 ),	/* Flags:  in, base type, */
/* 8858 */	NdrFcShort( 0x8 ),	/* x86 Stack size/offset = 8 */
/* 8860 */	0x8,		/* FC_LONG */
			0x0,		/* 0 */

	/* Return value */

/* 8862 */	NdrFcShort( 0x70 ),	/* Flags:  out, return, base type, */
/* 8864 */	NdrFcShort( 0xc ),	/* x86 Stack size/offset = 12 */
/* 8866 */	0x8,		/* FC_LONG */
			0x0,		/* 0 */

	/* Procedure StopListenAddressAndPort */

/* 8868 */	0x33,		/* FC_AUTO_HANDLE */
			0x6c,		/* Old Flags:  object, Oi2 */
/* 8870 */	NdrFcLong( 0x0 ),	/* 0 */
/* 8874 */	NdrFcShort( 0x4 ),	/* 4 */
/* 8876 */	NdrFcShort( 0x10 ),	/* x86 Stack size/offset = 16 */
/* 8878 */	NdrFcShort( 0x8 ),	/* 8 */
/* 8880 */	NdrFcShort( 0x8 ),	/* 8 */
/* 8882 */	0x46,		/* Oi2 Flags:  clt must size, has return, has ext, */
			0x3,		/* 3 */
/* 8884 */	0x8,		/* 8 */
			0x5,		/* Ext Flags:  new corr desc, srv corr check, */
/* 8886 */	NdrFcShort( 0x0 ),	/* 0 */
/* 8888 */	NdrFcShort( 0x1 ),	/* 1 */
/* 8890 */	NdrFcShort( 0x0 ),	/* 0 */

	/* Parameter bstrInternalLocalAddress */

/* 8892 */	NdrFcShort( 0x8b ),	/* Flags:  must size, must free, in, by val, */
/* 8894 */	NdrFcShort( 0x4 ),	/* x86 Stack size/offset = 4 */
/* 8896 */	NdrFcShort( 0x20 ),	/* Type Offset=32 */

	/* Parameter lInternalLocalPort */

/* 8898 */	NdrFcShort( 0x48 ),	/* Flags:  in, base type, */
/* 8900 */	NdrFcShort( 0x8 ),	/* x86 Stack size/offset = 8 */
/* 8902 */	0x8,		/* FC_LONG */
			0x0,		/* 0 */

	/* Return value */

/* 8904 */	NdrFcShort( 0x70 ),	/* Flags:  out, return, base type, */
/* 8906 */	NdrFcShort( 0xc ),	/* x86 Stack size/offset = 12 */
/* 8908 */	0x8,		/* FC_LONG */
			0x0,		/* 0 */

	/* Procedure GetPortRange */

/* 8910 */	0x33,		/* FC_AUTO_HANDLE */
			0x6c,		/* Old Flags:  object, Oi2 */
/* 8912 */	NdrFcLong( 0x0 ),	/* 0 */
/* 8916 */	NdrFcShort( 0x5 ),	/* 5 */
/* 8918 */	NdrFcShort( 0x14 ),	/* x86 Stack size/offset = 20 */
/* 8920 */	NdrFcShort( 0x6 ),	/* 6 */
/* 8922 */	NdrFcShort( 0x40 ),	/* 64 */
/* 8924 */	0x44,		/* Oi2 Flags:  has return, has ext, */
			0x4,		/* 4 */
/* 8926 */	0x8,		/* 8 */
			0x1,		/* Ext Flags:  new corr desc, */
/* 8928 */	NdrFcShort( 0x0 ),	/* 0 */
/* 8930 */	NdrFcShort( 0x0 ),	/* 0 */
/* 8932 */	NdrFcShort( 0x0 ),	/* 0 */

	/* Parameter enPortType */

/* 8934 */	NdrFcShort( 0x48 ),	/* Flags:  in, base type, */
/* 8936 */	NdrFcShort( 0x4 ),	/* x86 Stack size/offset = 4 */
/* 8938 */	0xd,		/* FC_ENUM16 */
			0x0,		/* 0 */

	/* Parameter plMinValue */

/* 8940 */	NdrFcShort( 0x2150 ),	/* Flags:  out, base type, simple ref, srv alloc size=8 */
/* 8942 */	NdrFcShort( 0x8 ),	/* x86 Stack size/offset = 8 */
/* 8944 */	0x8,		/* FC_LONG */
			0x0,		/* 0 */

	/* Parameter plMaxValue */

/* 8946 */	NdrFcShort( 0x2150 ),	/* Flags:  out, base type, simple ref, srv alloc size=8 */
/* 8948 */	NdrFcShort( 0xc ),	/* x86 Stack size/offset = 12 */
/* 8950 */	0x8,		/* FC_LONG */
			0x0,		/* 0 */

	/* Return value */

/* 8952 */	NdrFcShort( 0x70 ),	/* Flags:  out, return, base type, */
/* 8954 */	NdrFcShort( 0x10 ),	/* x86 Stack size/offset = 16 */
/* 8956 */	0x8,		/* FC_LONG */
			0x0,		/* 0 */

	/* Procedure CreateQuery */

/* 8958 */	0x33,		/* FC_AUTO_HANDLE */
			0x6c,		/* Old Flags:  object, Oi2 */
/* 8960 */	NdrFcLong( 0x0 ),	/* 0 */
/* 8964 */	NdrFcShort( 0x3 ),	/* 3 */
/* 8966 */	NdrFcShort( 0xc ),	/* x86 Stack size/offset = 12 */
/* 8968 */	NdrFcShort( 0x0 ),	/* 0 */
/* 8970 */	NdrFcShort( 0x8 ),	/* 8 */
/* 8972 */	0x45,		/* Oi2 Flags:  srv must size, has return, has ext, */
			0x2,		/* 2 */
/* 8974 */	0x8,		/* 8 */
			0x1,		/* Ext Flags:  new corr desc, */
/* 8976 */	NdrFcShort( 0x0 ),	/* 0 */
/* 8978 */	NdrFcShort( 0x0 ),	/* 0 */
/* 8980 */	NdrFcShort( 0x0 ),	/* 0 */

	/* Parameter ppQuery */

/* 8982 */	NdrFcShort( 0x13 ),	/* Flags:  must size, must free, out, */
/* 8984 */	NdrFcShort( 0x4 ),	/* x86 Stack size/offset = 4 */
/* 8986 */	NdrFcShort( 0x8bc ),	/* Type Offset=2236 */

	/* Return value */

/* 8988 */	NdrFcShort( 0x70 ),	/* Flags:  out, return, base type, */
/* 8990 */	NdrFcShort( 0x8 ),	/* x86 Stack size/offset = 8 */
/* 8992 */	0x8,		/* FC_LONG */
			0x0,		/* 0 */

	/* Procedure ExecuteSearch */

/* 8994 */	0x33,		/* FC_AUTO_HANDLE */
			0x6c,		/* Old Flags:  object, Oi2 */
/* 8996 */	NdrFcLong( 0x0 ),	/* 0 */
/* 9000 */	NdrFcShort( 0x4 ),	/* 4 */
/* 9002 */	NdrFcShort( 0x14 ),	/* x86 Stack size/offset = 20 */
/* 9004 */	NdrFcShort( 0x8 ),	/* 8 */
/* 9006 */	NdrFcShort( 0x8 ),	/* 8 */
/* 9008 */	0x46,		/* Oi2 Flags:  clt must size, has return, has ext, */
			0x4,		/* 4 */
/* 9010 */	0x8,		/* 8 */
			0x1,		/* Ext Flags:  new corr desc, */
/* 9012 */	NdrFcShort( 0x0 ),	/* 0 */
/* 9014 */	NdrFcShort( 0x0 ),	/* 0 */
/* 9016 */	NdrFcShort( 0x0 ),	/* 0 */

	/* Parameter pQuery */

/* 9018 */	NdrFcShort( 0xb ),	/* Flags:  must size, must free, in, */
/* 9020 */	NdrFcShort( 0x4 ),	/* x86 Stack size/offset = 4 */
/* 9022 */	NdrFcShort( 0x8c0 ),	/* Type Offset=2240 */

	/* Parameter pProfile */

/* 9024 */	NdrFcShort( 0xb ),	/* Flags:  must size, must free, in, */
/* 9026 */	NdrFcShort( 0x8 ),	/* x86 Stack size/offset = 8 */
/* 9028 */	NdrFcShort( 0x8d2 ),	/* Type Offset=2258 */

	/* Parameter lCookie */

/* 9030 */	NdrFcShort( 0x48 ),	/* Flags:  in, base type, */
/* 9032 */	NdrFcShort( 0xc ),	/* x86 Stack size/offset = 12 */
/* 9034 */	0x8,		/* FC_LONG */
			0x0,		/* 0 */

	/* Return value */

/* 9036 */	NdrFcShort( 0x70 ),	/* Flags:  out, return, base type, */
/* 9038 */	NdrFcShort( 0x10 ),	/* x86 Stack size/offset = 16 */
/* 9040 */	0x8,		/* FC_LONG */
			0x0,		/* 0 */

	/* Procedure put_SearchTerm */

/* 9042 */	0x33,		/* FC_AUTO_HANDLE */
			0x6c,		/* Old Flags:  object, Oi2 */
/* 9044 */	NdrFcLong( 0x0 ),	/* 0 */
/* 9048 */	NdrFcShort( 0x3 ),	/* 3 */
/* 9050 */	NdrFcShort( 0x10 ),	/* x86 Stack size/offset = 16 */
/* 9052 */	NdrFcShort( 0x0 ),	/* 0 */
/* 9054 */	NdrFcShort( 0x8 ),	/* 8 */
/* 9056 */	0x46,		/* Oi2 Flags:  clt must size, has return, has ext, */
			0x3,		/* 3 */
/* 9058 */	0x8,		/* 8 */
			0x5,		/* Ext Flags:  new corr desc, srv corr check, */
/* 9060 */	NdrFcShort( 0x0 ),	/* 0 */
/* 9062 */	NdrFcShort( 0x2 ),	/* 2 */
/* 9064 */	NdrFcShort( 0x0 ),	/* 0 */

	/* Parameter bstrName */

/* 9066 */	NdrFcShort( 0x8b ),	/* Flags:  must size, must free, in, by val, */
/* 9068 */	NdrFcShort( 0x4 ),	/* x86 Stack size/offset = 4 */
/* 9070 */	NdrFcShort( 0x20 ),	/* Type Offset=32 */

	/* Parameter bstrValue */

/* 9072 */	NdrFcShort( 0x8b ),	/* Flags:  must size, must free, in, by val, */
/* 9074 */	NdrFcShort( 0x8 ),	/* x86 Stack size/offset = 8 */
/* 9076 */	NdrFcShort( 0x20 ),	/* Type Offset=32 */

	/* Return value */

/* 9078 */	NdrFcShort( 0x70 ),	/* Flags:  out, return, base type, */
/* 9080 */	NdrFcShort( 0xc ),	/* x86 Stack size/offset = 12 */
/* 9082 */	0x8,		/* FC_LONG */
			0x0,		/* 0 */

	/* Procedure get_SearchTerm */

/* 9084 */	0x33,		/* FC_AUTO_HANDLE */
			0x6c,		/* Old Flags:  object, Oi2 */
/* 9086 */	NdrFcLong( 0x0 ),	/* 0 */
/* 9090 */	NdrFcShort( 0x4 ),	/* 4 */
/* 9092 */	NdrFcShort( 0x10 ),	/* x86 Stack size/offset = 16 */
/* 9094 */	NdrFcShort( 0x0 ),	/* 0 */
/* 9096 */	NdrFcShort( 0x8 ),	/* 8 */
/* 9098 */	0x47,		/* Oi2 Flags:  srv must size, clt must size, has return, has ext, */
			0x3,		/* 3 */
/* 9100 */	0x8,		/* 8 */
			0x7,		/* Ext Flags:  new corr desc, clt corr check, srv corr check, */
/* 9102 */	NdrFcShort( 0x1 ),	/* 1 */
/* 9104 */	NdrFcShort( 0x1 ),	/* 1 */
/* 9106 */	NdrFcShort( 0x0 ),	/* 0 */

	/* Parameter bstrName */

/* 9108 */	NdrFcShort( 0x8b ),	/* Flags:  must size, must free, in, by val, */
/* 9110 */	NdrFcShort( 0x4 ),	/* x86 Stack size/offset = 4 */
/* 9112 */	NdrFcShort( 0x20 ),	/* Type Offset=32 */

	/* Parameter pbstrValue */

/* 9114 */	NdrFcShort( 0x2113 ),	/* Flags:  must size, must free, out, simple ref, srv alloc size=8 */
/* 9116 */	NdrFcShort( 0x8 ),	/* x86 Stack size/offset = 8 */
/* 9118 */	NdrFcShort( 0x46a ),	/* Type Offset=1130 */

	/* Return value */

/* 9120 */	NdrFcShort( 0x70 ),	/* Flags:  out, return, base type, */
/* 9122 */	NdrFcShort( 0xc ),	/* x86 Stack size/offset = 12 */
/* 9124 */	0x8,		/* FC_LONG */
			0x0,		/* 0 */

	/* Procedure put_SearchPreference */

/* 9126 */	0x33,		/* FC_AUTO_HANDLE */
			0x6c,		/* Old Flags:  object, Oi2 */
/* 9128 */	NdrFcLong( 0x0 ),	/* 0 */
/* 9132 */	NdrFcShort( 0x6 ),	/* 6 */
/* 9134 */	NdrFcShort( 0x10 ),	/* x86 Stack size/offset = 16 */
/* 9136 */	NdrFcShort( 0xe ),	/* 14 */
/* 9138 */	NdrFcShort( 0x8 ),	/* 8 */
/* 9140 */	0x44,		/* Oi2 Flags:  has return, has ext, */
			0x3,		/* 3 */
/* 9142 */	0x8,		/* 8 */
			0x1,		/* Ext Flags:  new corr desc, */
/* 9144 */	NdrFcShort( 0x0 ),	/* 0 */
/* 9146 */	NdrFcShort( 0x0 ),	/* 0 */
/* 9148 */	NdrFcShort( 0x0 ),	/* 0 */

	/* Parameter enPreference */

/* 9150 */	NdrFcShort( 0x48 ),	/* Flags:  in, base type, */
/* 9152 */	NdrFcShort( 0x4 ),	/* x86 Stack size/offset = 4 */
/* 9154 */	0xd,		/* FC_ENUM16 */
			0x0,		/* 0 */

	/* Parameter lValue */

/* 9156 */	NdrFcShort( 0x48 ),	/* Flags:  in, base type, */
/* 9158 */	NdrFcShort( 0x8 ),	/* x86 Stack size/offset = 8 */
/* 9160 */	0x8,		/* FC_LONG */
			0x0,		/* 0 */

	/* Return value */

/* 9162 */	NdrFcShort( 0x70 ),	/* Flags:  out, return, base type, */
/* 9164 */	NdrFcShort( 0xc ),	/* x86 Stack size/offset = 12 */
/* 9166 */	0x8,		/* FC_LONG */
			0x0,		/* 0 */

	/* Procedure get_SearchPreference */

/* 9168 */	0x33,		/* FC_AUTO_HANDLE */
			0x6c,		/* Old Flags:  object, Oi2 */
/* 9170 */	NdrFcLong( 0x0 ),	/* 0 */
/* 9174 */	NdrFcShort( 0x7 ),	/* 7 */
/* 9176 */	NdrFcShort( 0x10 ),	/* x86 Stack size/offset = 16 */
/* 9178 */	NdrFcShort( 0x6 ),	/* 6 */
/* 9180 */	NdrFcShort( 0x24 ),	/* 36 */
/* 9182 */	0x44,		/* Oi2 Flags:  has return, has ext, */
			0x3,		/* 3 */
/* 9184 */	0x8,		/* 8 */
			0x1,		/* Ext Flags:  new corr desc, */
/* 9186 */	NdrFcShort( 0x0 ),	/* 0 */
/* 9188 */	NdrFcShort( 0x0 ),	/* 0 */
/* 9190 */	NdrFcShort( 0x0 ),	/* 0 */

	/* Parameter enPreference */

/* 9192 */	NdrFcShort( 0x48 ),	/* Flags:  in, base type, */
/* 9194 */	NdrFcShort( 0x4 ),	/* x86 Stack size/offset = 4 */
/* 9196 */	0xd,		/* FC_ENUM16 */
			0x0,		/* 0 */

	/* Parameter plValue */

/* 9198 */	NdrFcShort( 0x2150 ),	/* Flags:  out, base type, simple ref, srv alloc size=8 */
/* 9200 */	NdrFcShort( 0x8 ),	/* x86 Stack size/offset = 8 */
/* 9202 */	0x8,		/* FC_LONG */
			0x0,		/* 0 */

	/* Return value */

/* 9204 */	NdrFcShort( 0x70 ),	/* Flags:  out, return, base type, */
/* 9206 */	NdrFcShort( 0xc ),	/* x86 Stack size/offset = 12 */
/* 9208 */	0x8,		/* FC_LONG */
			0x0,		/* 0 */

	/* Procedure get_Value */

/* 9210 */	0x33,		/* FC_AUTO_HANDLE */
			0x6c,		/* Old Flags:  object, Oi2 */
/* 9212 */	NdrFcLong( 0x0 ),	/* 0 */
/* 9216 */	NdrFcShort( 0x3 ),	/* 3 */
/* 9218 */	NdrFcShort( 0x10 ),	/* x86 Stack size/offset = 16 */
/* 9220 */	NdrFcShort( 0x6 ),	/* 6 */
/* 9222 */	NdrFcShort( 0x8 ),	/* 8 */
/* 9224 */	0x45,		/* Oi2 Flags:  srv must size, has return, has ext, */
			0x3,		/* 3 */
/* 9226 */	0x8,		/* 8 */
			0x3,		/* Ext Flags:  new corr desc, clt corr check, */
/* 9228 */	NdrFcShort( 0x1 ),	/* 1 */
/* 9230 */	NdrFcShort( 0x0 ),	/* 0 */
/* 9232 */	NdrFcShort( 0x0 ),	/* 0 */

	/* Parameter enColumn */

/* 9234 */	NdrFcShort( 0x48 ),	/* Flags:  in, base type, */
/* 9236 */	NdrFcShort( 0x4 ),	/* x86 Stack size/offset = 4 */
/* 9238 */	0xd,		/* FC_ENUM16 */
			0x0,		/* 0 */

	/* Parameter pbstrValue */

/* 9240 */	NdrFcShort( 0x2113 ),	/* Flags:  must size, must free, out, simple ref, srv alloc size=8 */
/* 9242 */	NdrFcShort( 0x8 ),	/* x86 Stack size/offset = 8 */
/* 9244 */	NdrFcShort( 0x46a ),	/* Type Offset=1130 */

	/* Return value */

/* 9246 */	NdrFcShort( 0x70 ),	/* Flags:  out, return, base type, */
/* 9248 */	NdrFcShort( 0xc ),	/* x86 Stack size/offset = 12 */
/* 9250 */	0x8,		/* FC_LONG */
			0x0,		/* 0 */

	/* Procedure Next */

/* 9252 */	0x33,		/* FC_AUTO_HANDLE */
			0x6d,		/* Old Flags:  full ptr, object, Oi2 */
/* 9254 */	NdrFcLong( 0x0 ),	/* 0 */
/* 9258 */	NdrFcShort( 0x3 ),	/* 3 */
/* 9260 */	NdrFcShort( 0x14 ),	/* x86 Stack size/offset = 20 */
/* 9262 */	NdrFcShort( 0x24 ),	/* 36 */
/* 9264 */	NdrFcShort( 0x24 ),	/* 36 */
/* 9266 */	0x45,		/* Oi2 Flags:  srv must size, has return, has ext, */
			0x4,		/* 4 */
/* 9268 */	0x8,		/* 8 */
			0x3,		/* Ext Flags:  new corr desc, clt corr check, */
/* 9270 */	NdrFcShort( 0x1 ),	/* 1 */
/* 9272 */	NdrFcShort( 0x0 ),	/* 0 */
/* 9274 */	NdrFcShort( 0x0 ),	/* 0 */

	/* Parameter celt */

/* 9276 */	NdrFcShort( 0x48 ),	/* Flags:  in, base type, */
/* 9278 */	NdrFcShort( 0x4 ),	/* x86 Stack size/offset = 4 */
/* 9280 */	0x8,		/* FC_LONG */
			0x0,		/* 0 */

	/* Parameter ppElements */

/* 9282 */	NdrFcShort( 0x113 ),	/* Flags:  must size, must free, out, simple ref, */
/* 9284 */	NdrFcShort( 0x8 ),	/* x86 Stack size/offset = 8 */
/* 9286 */	NdrFcShort( 0x8fa ),	/* Type Offset=2298 */

	/* Parameter pceltFetched */

/* 9288 */	NdrFcShort( 0x1a ),	/* Flags:  must free, in, out, */
/* 9290 */	NdrFcShort( 0xc ),	/* x86 Stack size/offset = 12 */
/* 9292 */	NdrFcShort( 0x704 ),	/* Type Offset=1796 */

	/* Return value */

/* 9294 */	NdrFcShort( 0x70 ),	/* Flags:  out, return, base type, */
/* 9296 */	NdrFcShort( 0x10 ),	/* x86 Stack size/offset = 16 */
/* 9298 */	0x8,		/* FC_LONG */
			0x0,		/* 0 */

	/* Procedure Clone */

/* 9300 */	0x33,		/* FC_AUTO_HANDLE */
			0x6c,		/* Old Flags:  object, Oi2 */
/* 9302 */	NdrFcLong( 0x0 ),	/* 0 */
/* 9306 */	NdrFcShort( 0x6 ),	/* 6 */
/* 9308 */	NdrFcShort( 0xc ),	/* x86 Stack size/offset = 12 */
/* 9310 */	NdrFcShort( 0x0 ),	/* 0 */
/* 9312 */	NdrFcShort( 0x8 ),	/* 8 */
/* 9314 */	0x45,		/* Oi2 Flags:  srv must size, has return, has ext, */
			0x2,		/* 2 */
/* 9316 */	0x8,		/* 8 */
			0x1,		/* Ext Flags:  new corr desc, */
/* 9318 */	NdrFcShort( 0x0 ),	/* 0 */
/* 9320 */	NdrFcShort( 0x0 ),	/* 0 */
/* 9322 */	NdrFcShort( 0x0 ),	/* 0 */

	/* Parameter ppEnum */

/* 9324 */	NdrFcShort( 0x13 ),	/* Flags:  must size, must free, out, */
/* 9326 */	NdrFcShort( 0x4 ),	/* x86 Stack size/offset = 4 */
/* 9328 */	NdrFcShort( 0x910 ),	/* Type Offset=2320 */

	/* Return value */

/* 9330 */	NdrFcShort( 0x70 ),	/* Flags:  out, return, base type, */
/* 9332 */	NdrFcShort( 0x8 ),	/* x86 Stack size/offset = 8 */
/* 9334 */	0x8,		/* FC_LONG */
			0x0,		/* 0 */

	/* Procedure EnumerateResults */

/* 9336 */	0x33,		/* FC_AUTO_HANDLE */
			0x6c,		/* Old Flags:  object, Oi2 */
/* 9338 */	NdrFcLong( 0x0 ),	/* 0 */
/* 9342 */	NdrFcShort( 0x7 ),	/* 7 */
/* 9344 */	NdrFcShort( 0xc ),	/* x86 Stack size/offset = 12 */
/* 9346 */	NdrFcShort( 0x0 ),	/* 0 */
/* 9348 */	NdrFcShort( 0x8 ),	/* 8 */
/* 9350 */	0x45,		/* Oi2 Flags:  srv must size, has return, has ext, */
			0x2,		/* 2 */
/* 9352 */	0x8,		/* 8 */
			0x1,		/* Ext Flags:  new corr desc, */
/* 9354 */	NdrFcShort( 0x0 ),	/* 0 */
/* 9356 */	NdrFcShort( 0x0 ),	/* 0 */
/* 9358 */	NdrFcShort( 0x0 ),	/* 0 */

	/* Parameter ppEnum */

/* 9360 */	NdrFcShort( 0x13 ),	/* Flags:  must size, must free, out, */
/* 9362 */	NdrFcShort( 0x4 ),	/* x86 Stack size/offset = 4 */
/* 9364 */	NdrFcShort( 0x910 ),	/* Type Offset=2320 */

	/* Return value */

/* 9366 */	NdrFcShort( 0x70 ),	/* Flags:  out, return, base type, */
/* 9368 */	NdrFcShort( 0x8 ),	/* x86 Stack size/offset = 8 */
/* 9370 */	0x8,		/* FC_LONG */
			0x0,		/* 0 */

	/* Procedure get_Profile */

/* 9372 */	0x33,		/* FC_AUTO_HANDLE */
			0x6c,		/* Old Flags:  object, Oi2 */
/* 9374 */	NdrFcLong( 0x0 ),	/* 0 */
/* 9378 */	NdrFcShort( 0x9 ),	/* 9 */
/* 9380 */	NdrFcShort( 0xc ),	/* x86 Stack size/offset = 12 */
/* 9382 */	NdrFcShort( 0x0 ),	/* 0 */
/* 9384 */	NdrFcShort( 0x8 ),	/* 8 */
/* 9386 */	0x45,		/* Oi2 Flags:  srv must size, has return, has ext, */
			0x2,		/* 2 */
/* 9388 */	0x8,		/* 8 */
			0x1,		/* Ext Flags:  new corr desc, */
/* 9390 */	NdrFcShort( 0x0 ),	/* 0 */
/* 9392 */	NdrFcShort( 0x0 ),	/* 0 */
/* 9394 */	NdrFcShort( 0x0 ),	/* 0 */

	/* Parameter ppProfile */

/* 9396 */	NdrFcShort( 0x13 ),	/* Flags:  must size, must free, out, */
/* 9398 */	NdrFcShort( 0x4 ),	/* x86 Stack size/offset = 4 */
/* 9400 */	NdrFcShort( 0x810 ),	/* Type Offset=2064 */

	/* Return value */

/* 9402 */	NdrFcShort( 0x70 ),	/* Flags:  out, return, base type, */
/* 9404 */	NdrFcShort( 0x8 ),	/* x86 Stack size/offset = 8 */
/* 9406 */	0x8,		/* FC_LONG */
			0x0,		/* 0 */

	/* Procedure get_Query */

/* 9408 */	0x33,		/* FC_AUTO_HANDLE */
			0x6c,		/* Old Flags:  object, Oi2 */
/* 9410 */	NdrFcLong( 0x0 ),	/* 0 */
/* 9414 */	NdrFcShort( 0xa ),	/* 10 */
/* 9416 */	NdrFcShort( 0xc ),	/* x86 Stack size/offset = 12 */
/* 9418 */	NdrFcShort( 0x0 ),	/* 0 */
/* 9420 */	NdrFcShort( 0x8 ),	/* 8 */
/* 9422 */	0x45,		/* Oi2 Flags:  srv must size, has return, has ext, */
			0x2,		/* 2 */
/* 9424 */	0x8,		/* 8 */
			0x1,		/* Ext Flags:  new corr desc, */
/* 9426 */	NdrFcShort( 0x0 ),	/* 0 */
/* 9428 */	NdrFcShort( 0x0 ),	/* 0 */
/* 9430 */	NdrFcShort( 0x0 ),	/* 0 */

	/* Parameter ppQuery */

/* 9432 */	NdrFcShort( 0x13 ),	/* Flags:  must size, must free, out, */
/* 9434 */	NdrFcShort( 0x4 ),	/* x86 Stack size/offset = 4 */
/* 9436 */	NdrFcShort( 0x8bc ),	/* Type Offset=2236 */

	/* Return value */

/* 9438 */	NdrFcShort( 0x70 ),	/* Flags:  out, return, base type, */
/* 9440 */	NdrFcShort( 0x8 ),	/* x86 Stack size/offset = 8 */
/* 9442 */	0x8,		/* FC_LONG */
			0x0,		/* 0 */

	/* Procedure get_StatusCode */

/* 9444 */	0x33,		/* FC_AUTO_HANDLE */
			0x6c,		/* Old Flags:  object, Oi2 */
/* 9446 */	NdrFcLong( 0x0 ),	/* 0 */
/* 9450 */	NdrFcShort( 0xc ),	/* 12 */
/* 9452 */	NdrFcShort( 0xc ),	/* x86 Stack size/offset = 12 */
/* 9454 */	NdrFcShort( 0x0 ),	/* 0 */
/* 9456 */	NdrFcShort( 0x24 ),	/* 36 */
/* 9458 */	0x44,		/* Oi2 Flags:  has return, has ext, */
			0x2,		/* 2 */
/* 9460 */	0x8,		/* 8 */
			0x1,		/* Ext Flags:  new corr desc, */
/* 9462 */	NdrFcShort( 0x0 ),	/* 0 */
/* 9464 */	NdrFcShort( 0x0 ),	/* 0 */
/* 9466 */	NdrFcShort( 0x0 ),	/* 0 */

	/* Parameter plStatusCode */

/* 9468 */	NdrFcShort( 0x2150 ),	/* Flags:  out, base type, simple ref, srv alloc size=8 */
/* 9470 */	NdrFcShort( 0x4 ),	/* x86 Stack size/offset = 4 */
/* 9472 */	0x8,		/* FC_LONG */
			0x0,		/* 0 */

	/* Return value */

/* 9474 */	NdrFcShort( 0x70 ),	/* Flags:  out, return, base type, */
/* 9476 */	NdrFcShort( 0x8 ),	/* x86 Stack size/offset = 8 */
/* 9478 */	0x8,		/* FC_LONG */
			0x0,		/* 0 */

	/* Procedure get_Session */


	/* Procedure get_Session */

/* 9480 */	0x33,		/* FC_AUTO_HANDLE */
			0x6c,		/* Old Flags:  object, Oi2 */
/* 9482 */	NdrFcLong( 0x0 ),	/* 0 */
/* 9486 */	NdrFcShort( 0x7 ),	/* 7 */
/* 9488 */	NdrFcShort( 0xc ),	/* x86 Stack size/offset = 12 */
/* 9490 */	NdrFcShort( 0x0 ),	/* 0 */
/* 9492 */	NdrFcShort( 0x8 ),	/* 8 */
/* 9494 */	0x45,		/* Oi2 Flags:  srv must size, has return, has ext, */
			0x2,		/* 2 */
/* 9496 */	0x8,		/* 8 */
			0x1,		/* Ext Flags:  new corr desc, */
/* 9498 */	NdrFcShort( 0x0 ),	/* 0 */
/* 9500 */	NdrFcShort( 0x0 ),	/* 0 */
/* 9502 */	NdrFcShort( 0x0 ),	/* 0 */

	/* Parameter ppSession */


	/* Parameter ppSession */

/* 9504 */	NdrFcShort( 0x13 ),	/* Flags:  must size, must free, out, */
/* 9506 */	NdrFcShort( 0x4 ),	/* x86 Stack size/offset = 4 */
/* 9508 */	NdrFcShort( 0x926 ),	/* Type Offset=2342 */

	/* Return value */


	/* Return value */

/* 9510 */	NdrFcShort( 0x70 ),	/* Flags:  out, return, base type, */
/* 9512 */	NdrFcShort( 0x8 ),	/* x86 Stack size/offset = 8 */
/* 9514 */	0x8,		/* FC_LONG */
			0x0,		/* 0 */

	/* Procedure Accept */

/* 9516 */	0x33,		/* FC_AUTO_HANDLE */
			0x6c,		/* Old Flags:  object, Oi2 */
/* 9518 */	NdrFcLong( 0x0 ),	/* 0 */
/* 9522 */	NdrFcShort( 0xb ),	/* 11 */
/* 9524 */	NdrFcShort( 0x8 ),	/* x86 Stack size/offset = 8 */
/* 9526 */	NdrFcShort( 0x0 ),	/* 0 */
/* 9528 */	NdrFcShort( 0x8 ),	/* 8 */
/* 9530 */	0x44,		/* Oi2 Flags:  has return, has ext, */
			0x1,		/* 1 */
/* 9532 */	0x8,		/* 8 */
			0x1,		/* Ext Flags:  new corr desc, */
/* 9534 */	NdrFcShort( 0x0 ),	/* 0 */
/* 9536 */	NdrFcShort( 0x0 ),	/* 0 */
/* 9538 */	NdrFcShort( 0x0 ),	/* 0 */

	/* Return value */

/* 9540 */	NdrFcShort( 0x70 ),	/* Flags:  out, return, base type, */
/* 9542 */	NdrFcShort( 0x4 ),	/* x86 Stack size/offset = 4 */
/* 9544 */	0x8,		/* FC_LONG */
			0x0,		/* 0 */

	/* Procedure SetReferredSessionState */

/* 9546 */	0x33,		/* FC_AUTO_HANDLE */
			0x6c,		/* Old Flags:  object, Oi2 */
/* 9548 */	NdrFcLong( 0x0 ),	/* 0 */
/* 9552 */	NdrFcShort( 0xd ),	/* 13 */
/* 9554 */	NdrFcShort( 0xc ),	/* x86 Stack size/offset = 12 */
/* 9556 */	NdrFcShort( 0x6 ),	/* 6 */
/* 9558 */	NdrFcShort( 0x8 ),	/* 8 */
/* 9560 */	0x44,		/* Oi2 Flags:  has return, has ext, */
			0x2,		/* 2 */
/* 9562 */	0x8,		/* 8 */
			0x1,		/* Ext Flags:  new corr desc, */
/* 9564 */	NdrFcShort( 0x0 ),	/* 0 */
/* 9566 */	NdrFcShort( 0x0 ),	/* 0 */
/* 9568 */	NdrFcShort( 0x0 ),	/* 0 */

	/* Parameter enState */

/* 9570 */	NdrFcShort( 0x48 ),	/* Flags:  in, base type, */
/* 9572 */	NdrFcShort( 0x4 ),	/* x86 Stack size/offset = 4 */
/* 9574 */	0xd,		/* FC_ENUM16 */
			0x0,		/* 0 */

	/* Return value */

/* 9576 */	NdrFcShort( 0x70 ),	/* Flags:  out, return, base type, */
/* 9578 */	NdrFcShort( 0x8 ),	/* x86 Stack size/offset = 8 */
/* 9580 */	0x8,		/* FC_LONG */
			0x0,		/* 0 */

	/* Procedure EvaluateSessionDescription */

/* 9582 */	0x33,		/* FC_AUTO_HANDLE */
			0x6c,		/* Old Flags:  object, Oi2 */
/* 9584 */	NdrFcLong( 0x0 ),	/* 0 */
/* 9588 */	NdrFcShort( 0x3 ),	/* 3 */
/* 9590 */	NdrFcShort( 0x14 ),	/* x86 Stack size/offset = 20 */
/* 9592 */	NdrFcShort( 0x1a ),	/* 26 */
/* 9594 */	NdrFcShort( 0x22 ),	/* 34 */
/* 9596 */	0x46,		/* Oi2 Flags:  clt must size, has return, has ext, */
			0x4,		/* 4 */
/* 9598 */	0x8,		/* 8 */
			0x5,		/* Ext Flags:  new corr desc, srv corr check, */
/* 9600 */	NdrFcShort( 0x0 ),	/* 0 */
/* 9602 */	NdrFcShort( 0x2 ),	/* 2 */
/* 9604 */	NdrFcShort( 0x0 ),	/* 0 */

	/* Parameter bstrContentType */

/* 9606 */	NdrFcShort( 0x8b ),	/* Flags:  must size, must free, in, by val, */
/* 9608 */	NdrFcShort( 0x4 ),	/* x86 Stack size/offset = 4 */
/* 9610 */	NdrFcShort( 0x20 ),	/* Type Offset=32 */

	/* Parameter bstrSessionDescription */

/* 9612 */	NdrFcShort( 0x8b ),	/* Flags:  must size, must free, in, by val, */
/* 9614 */	NdrFcShort( 0x8 ),	/* x86 Stack size/offset = 8 */
/* 9616 */	NdrFcShort( 0x20 ),	/* Type Offset=32 */

	/* Parameter pfApplicationSession */

/* 9618 */	NdrFcShort( 0x158 ),	/* Flags:  in, out, base type, simple ref, */
/* 9620 */	NdrFcShort( 0xc ),	/* x86 Stack size/offset = 12 */
/* 9622 */	0x6,		/* FC_SHORT */
			0x0,		/* 0 */

	/* Return value */

/* 9624 */	NdrFcShort( 0x70 ),	/* Flags:  out, return, base type, */
/* 9626 */	NdrFcShort( 0x10 ),	/* x86 Stack size/offset = 16 */
/* 9628 */	0x8,		/* FC_LONG */
			0x0,		/* 0 */

	/* Procedure Next */

/* 9630 */	0x33,		/* FC_AUTO_HANDLE */
			0x6d,		/* Old Flags:  full ptr, object, Oi2 */
/* 9632 */	NdrFcLong( 0x0 ),	/* 0 */
/* 9636 */	NdrFcShort( 0x3 ),	/* 3 */
/* 9638 */	NdrFcShort( 0x14 ),	/* x86 Stack size/offset = 20 */
/* 9640 */	NdrFcShort( 0x24 ),	/* 36 */
/* 9642 */	NdrFcShort( 0x24 ),	/* 36 */
/* 9644 */	0x45,		/* Oi2 Flags:  srv must size, has return, has ext, */
			0x4,		/* 4 */
/* 9646 */	0x8,		/* 8 */
			0x3,		/* Ext Flags:  new corr desc, clt corr check, */
/* 9648 */	NdrFcShort( 0x1 ),	/* 1 */
/* 9650 */	NdrFcShort( 0x0 ),	/* 0 */
/* 9652 */	NdrFcShort( 0x0 ),	/* 0 */

	/* Parameter celt */

/* 9654 */	NdrFcShort( 0x48 ),	/* Flags:  in, base type, */
/* 9656 */	NdrFcShort( 0x4 ),	/* x86 Stack size/offset = 4 */
/* 9658 */	0x8,		/* FC_LONG */
			0x0,		/* 0 */

	/* Parameter ppElements */

/* 9660 */	NdrFcShort( 0x113 ),	/* Flags:  must size, must free, out, simple ref, */
/* 9662 */	NdrFcShort( 0x8 ),	/* x86 Stack size/offset = 8 */
/* 9664 */	NdrFcShort( 0x956 ),	/* Type Offset=2390 */

	/* Parameter pceltFetched */

/* 9666 */	NdrFcShort( 0x1a ),	/* Flags:  must free, in, out, */
/* 9668 */	NdrFcShort( 0xc ),	/* x86 Stack size/offset = 12 */
/* 9670 */	NdrFcShort( 0x704 ),	/* Type Offset=1796 */

	/* Return value */

/* 9672 */	NdrFcShort( 0x70 ),	/* Flags:  out, return, base type, */
/* 9674 */	NdrFcShort( 0x10 ),	/* x86 Stack size/offset = 16 */
/* 9676 */	0x8,		/* FC_LONG */
			0x0,		/* 0 */

	/* Procedure Clone */

/* 9678 */	0x33,		/* FC_AUTO_HANDLE */
			0x6c,		/* Old Flags:  object, Oi2 */
/* 9680 */	NdrFcLong( 0x0 ),	/* 0 */
/* 9684 */	NdrFcShort( 0x6 ),	/* 6 */
/* 9686 */	NdrFcShort( 0xc ),	/* x86 Stack size/offset = 12 */
/* 9688 */	NdrFcShort( 0x0 ),	/* 0 */
/* 9690 */	NdrFcShort( 0x8 ),	/* 8 */
/* 9692 */	0x45,		/* Oi2 Flags:  srv must size, has return, has ext, */
			0x2,		/* 2 */
/* 9694 */	0x8,		/* 8 */
			0x1,		/* Ext Flags:  new corr desc, */
/* 9696 */	NdrFcShort( 0x0 ),	/* 0 */
/* 9698 */	NdrFcShort( 0x0 ),	/* 0 */
/* 9700 */	NdrFcShort( 0x0 ),	/* 0 */

	/* Parameter ppEnum */

/* 9702 */	NdrFcShort( 0x13 ),	/* Flags:  must size, must free, out, */
/* 9704 */	NdrFcShort( 0x4 ),	/* x86 Stack size/offset = 4 */
/* 9706 */	NdrFcShort( 0x96c ),	/* Type Offset=2412 */

	/* Return value */

/* 9708 */	NdrFcShort( 0x70 ),	/* Flags:  out, return, base type, */
/* 9710 */	NdrFcShort( 0x8 ),	/* x86 Stack size/offset = 8 */
/* 9712 */	0x8,		/* FC_LONG */
			0x0,		/* 0 */

	/* Procedure get_Status */

/* 9714 */	0x33,		/* FC_AUTO_HANDLE */
			0x6c,		/* Old Flags:  object, Oi2 */
/* 9716 */	NdrFcLong( 0x0 ),	/* 0 */
/* 9720 */	NdrFcShort( 0x3 ),	/* 3 */
/* 9722 */	NdrFcShort( 0xc ),	/* x86 Stack size/offset = 12 */
/* 9724 */	NdrFcShort( 0x0 ),	/* 0 */
/* 9726 */	NdrFcShort( 0x22 ),	/* 34 */
/* 9728 */	0x44,		/* Oi2 Flags:  has return, has ext, */
			0x2,		/* 2 */
/* 9730 */	0x8,		/* 8 */
			0x1,		/* Ext Flags:  new corr desc, */
/* 9732 */	NdrFcShort( 0x0 ),	/* 0 */
/* 9734 */	NdrFcShort( 0x0 ),	/* 0 */
/* 9736 */	NdrFcShort( 0x0 ),	/* 0 */

	/* Parameter penStatus */

/* 9738 */	NdrFcShort( 0x2010 ),	/* Flags:  out, srv alloc size=8 */
/* 9740 */	NdrFcShort( 0x4 ),	/* x86 Stack size/offset = 4 */
/* 9742 */	NdrFcShort( 0x52 ),	/* Type Offset=82 */

	/* Return value */

/* 9744 */	NdrFcShort( 0x70 ),	/* Flags:  out, return, base type, */
/* 9746 */	NdrFcShort( 0x8 ),	/* x86 Stack size/offset = 8 */
/* 9748 */	0x8,		/* FC_LONG */
			0x0,		/* 0 */

	/* Procedure get_PresenceProperty */

/* 9750 */	0x33,		/* FC_AUTO_HANDLE */
			0x6c,		/* Old Flags:  object, Oi2 */
/* 9752 */	NdrFcLong( 0x0 ),	/* 0 */
/* 9756 */	NdrFcShort( 0x5 ),	/* 5 */
/* 9758 */	NdrFcShort( 0x10 ),	/* x86 Stack size/offset = 16 */
/* 9760 */	NdrFcShort( 0x6 ),	/* 6 */
/* 9762 */	NdrFcShort( 0x8 ),	/* 8 */
/* 9764 */	0x45,		/* Oi2 Flags:  srv must size, has return, has ext, */
			0x3,		/* 3 */
/* 9766 */	0x8,		/* 8 */
			0x3,		/* Ext Flags:  new corr desc, clt corr check, */
/* 9768 */	NdrFcShort( 0x1 ),	/* 1 */
/* 9770 */	NdrFcShort( 0x0 ),	/* 0 */
/* 9772 */	NdrFcShort( 0x0 ),	/* 0 */

	/* Parameter enProperty */

/* 9774 */	NdrFcShort( 0x48 ),	/* Flags:  in, base type, */
/* 9776 */	NdrFcShort( 0x4 ),	/* x86 Stack size/offset = 4 */
/* 9778 */	0xd,		/* FC_ENUM16 */
			0x0,		/* 0 */

	/* Parameter pbstrProperty */

/* 9780 */	NdrFcShort( 0x2113 ),	/* Flags:  must size, must free, out, simple ref, srv alloc size=8 */
/* 9782 */	NdrFcShort( 0x8 ),	/* x86 Stack size/offset = 8 */
/* 9784 */	NdrFcShort( 0x46a ),	/* Type Offset=1130 */

	/* Return value */

/* 9786 */	NdrFcShort( 0x70 ),	/* Flags:  out, return, base type, */
/* 9788 */	NdrFcShort( 0xc ),	/* x86 Stack size/offset = 12 */
/* 9790 */	0x8,		/* FC_LONG */
			0x0,		/* 0 */

	/* Procedure GetPresenceData */

/* 9792 */	0x33,		/* FC_AUTO_HANDLE */
			0x6c,		/* Old Flags:  object, Oi2 */
/* 9794 */	NdrFcLong( 0x0 ),	/* 0 */
/* 9798 */	NdrFcShort( 0x6 ),	/* 6 */
/* 9800 */	NdrFcShort( 0x10 ),	/* x86 Stack size/offset = 16 */
/* 9802 */	NdrFcShort( 0x0 ),	/* 0 */
/* 9804 */	NdrFcShort( 0x8 ),	/* 8 */
/* 9806 */	0x45,		/* Oi2 Flags:  srv must size, has return, has ext, */
			0x3,		/* 3 */
/* 9808 */	0x8,		/* 8 */
			0x3,		/* Ext Flags:  new corr desc, clt corr check, */
/* 9810 */	NdrFcShort( 0x2 ),	/* 2 */
/* 9812 */	NdrFcShort( 0x0 ),	/* 0 */
/* 9814 */	NdrFcShort( 0x0 ),	/* 0 */

	/* Parameter pbstrNamespace */

/* 9816 */	NdrFcShort( 0x2113 ),	/* Flags:  must size, must free, out, simple ref, srv alloc size=8 */
/* 9818 */	NdrFcShort( 0x4 ),	/* x86 Stack size/offset = 4 */
/* 9820 */	NdrFcShort( 0x46a ),	/* Type Offset=1130 */

	/* Parameter pbstrData */

/* 9822 */	NdrFcShort( 0x2113 ),	/* Flags:  must size, must free, out, simple ref, srv alloc size=8 */
/* 9824 */	NdrFcShort( 0x8 ),	/* x86 Stack size/offset = 8 */
/* 9826 */	NdrFcShort( 0x46a ),	/* Type Offset=1130 */

	/* Return value */

/* 9828 */	NdrFcShort( 0x70 ),	/* Flags:  out, return, base type, */
/* 9830 */	NdrFcShort( 0xc ),	/* x86 Stack size/offset = 12 */
/* 9832 */	0x8,		/* FC_LONG */
			0x0,		/* 0 */

			0x0
        }
    };

static const MIDL_TYPE_FORMAT_STRING __MIDL_TypeFormatString =
    {
        0,
        {
			NdrFcShort( 0x0 ),	/* 0 */
/*  2 */	
			0x11, 0xc,	/* FC_RP [alloced_on_stack] [simple_pointer] */
/*  4 */	0x8,		/* FC_LONG */
			0x5c,		/* FC_PAD */
/*  6 */	
			0x12, 0x0,	/* FC_UP */
/*  8 */	NdrFcShort( 0xe ),	/* Offset= 14 (22) */
/* 10 */	
			0x1b,		/* FC_CARRAY */
			0x1,		/* 1 */
/* 12 */	NdrFcShort( 0x2 ),	/* 2 */
/* 14 */	0x9,		/* Corr desc: FC_ULONG */
			0x0,		/*  */
/* 16 */	NdrFcShort( 0xfffc ),	/* -4 */
/* 18 */	NdrFcShort( 0x1 ),	/* Corr flags:  early, */
/* 20 */	0x6,		/* FC_SHORT */
			0x5b,		/* FC_END */
/* 22 */	
			0x17,		/* FC_CSTRUCT */
			0x3,		/* 3 */
/* 24 */	NdrFcShort( 0x8 ),	/* 8 */
/* 26 */	NdrFcShort( 0xfff0 ),	/* Offset= -16 (10) */
/* 28 */	0x8,		/* FC_LONG */
			0x8,		/* FC_LONG */
/* 30 */	0x5c,		/* FC_PAD */
			0x5b,		/* FC_END */
/* 32 */	0xb4,		/* FC_USER_MARSHAL */
			0x83,		/* 131 */
/* 34 */	NdrFcShort( 0x0 ),	/* 0 */
/* 36 */	NdrFcShort( 0x4 ),	/* 4 */
/* 38 */	NdrFcShort( 0x0 ),	/* 0 */
/* 40 */	NdrFcShort( 0xffde ),	/* Offset= -34 (6) */
/* 42 */	
			0x2f,		/* FC_IP */
			0x5a,		/* FC_CONSTANT_IID */
/* 44 */	NdrFcLong( 0xd07eca9e ),	/* -796996962 */
/* 48 */	NdrFcShort( 0x4062 ),	/* 16482 */
/* 50 */	NdrFcShort( 0x4dd4 ),	/* 19924 */
/* 52 */	0x9e,		/* 158 */
			0x7d,		/* 125 */
/* 54 */	0x72,		/* 114 */
			0x2a,		/* 42 */
/* 56 */	0x49,		/* 73 */
			0xba,		/* 186 */
/* 58 */	0x73,		/* 115 */
			0x3,		/* 3 */
/* 60 */	
			0x11, 0x10,	/* FC_RP [pointer_deref] */
/* 62 */	NdrFcShort( 0x2 ),	/* Offset= 2 (64) */
/* 64 */	
			0x2f,		/* FC_IP */
			0x5a,		/* FC_CONSTANT_IID */
/* 66 */	NdrFcLong( 0x387c8086 ),	/* 947683462 */
/* 70 */	NdrFcShort( 0x99be ),	/* -26178 */
/* 72 */	NdrFcShort( 0x42fb ),	/* 17147 */
/* 74 */	0x99,		/* 153 */
			0x73,		/* 115 */
/* 76 */	0x7c,		/* 124 */
			0xf,		/* 15 */
/* 78 */	0xc0,		/* 192 */
			0xca,		/* 202 */
/* 80 */	0x9f,		/* 159 */
			0xa8,		/* 168 */
/* 82 */	
			0x11, 0xc,	/* FC_RP [alloced_on_stack] [simple_pointer] */
/* 84 */	0xd,		/* FC_ENUM16 */
			0x5c,		/* FC_PAD */
/* 86 */	
			0x11, 0x4,	/* FC_RP [alloced_on_stack] */
/* 88 */	NdrFcShort( 0x3ea ),	/* Offset= 1002 (1090) */
/* 90 */	
			0x13, 0x0,	/* FC_OP */
/* 92 */	NdrFcShort( 0x3d2 ),	/* Offset= 978 (1070) */
/* 94 */	
			0x2b,		/* FC_NON_ENCAPSULATED_UNION */
			0x9,		/* FC_ULONG */
/* 96 */	0x7,		/* Corr desc: FC_USHORT */
			0x0,		/*  */
/* 98 */	NdrFcShort( 0xfff8 ),	/* -8 */
/* 100 */	NdrFcShort( 0x1 ),	/* Corr flags:  early, */
/* 102 */	NdrFcShort( 0x2 ),	/* Offset= 2 (104) */
/* 104 */	NdrFcShort( 0x10 ),	/* 16 */
/* 106 */	NdrFcShort( 0x2f ),	/* 47 */
/* 108 */	NdrFcLong( 0x14 ),	/* 20 */
/* 112 */	NdrFcShort( 0x800b ),	/* Simple arm type: FC_HYPER */
/* 114 */	NdrFcLong( 0x3 ),	/* 3 */
/* 118 */	NdrFcShort( 0x8008 ),	/* Simple arm type: FC_LONG */
/* 120 */	NdrFcLong( 0x11 ),	/* 17 */
/* 124 */	NdrFcShort( 0x8001 ),	/* Simple arm type: FC_BYTE */
/* 126 */	NdrFcLong( 0x2 ),	/* 2 */
/* 130 */	NdrFcShort( 0x8006 ),	/* Simple arm type: FC_SHORT */
/* 132 */	NdrFcLong( 0x4 ),	/* 4 */
/* 136 */	NdrFcShort( 0x800a ),	/* Simple arm type: FC_FLOAT */
/* 138 */	NdrFcLong( 0x5 ),	/* 5 */
/* 142 */	NdrFcShort( 0x800c ),	/* Simple arm type: FC_DOUBLE */
/* 144 */	NdrFcLong( 0xb ),	/* 11 */
/* 148 */	NdrFcShort( 0x8006 ),	/* Simple arm type: FC_SHORT */
/* 150 */	NdrFcLong( 0xa ),	/* 10 */
/* 154 */	NdrFcShort( 0x8008 ),	/* Simple arm type: FC_LONG */
/* 156 */	NdrFcLong( 0x6 ),	/* 6 */
/* 160 */	NdrFcShort( 0xe8 ),	/* Offset= 232 (392) */
/* 162 */	NdrFcLong( 0x7 ),	/* 7 */
/* 166 */	NdrFcShort( 0x800c ),	/* Simple arm type: FC_DOUBLE */
/* 168 */	NdrFcLong( 0x8 ),	/* 8 */
/* 172 */	NdrFcShort( 0xe2 ),	/* Offset= 226 (398) */
/* 174 */	NdrFcLong( 0xd ),	/* 13 */
/* 178 */	NdrFcShort( 0xe0 ),	/* Offset= 224 (402) */
/* 180 */	NdrFcLong( 0x9 ),	/* 9 */
/* 184 */	NdrFcShort( 0xec ),	/* Offset= 236 (420) */
/* 186 */	NdrFcLong( 0x2000 ),	/* 8192 */
/* 190 */	NdrFcShort( 0xf8 ),	/* Offset= 248 (438) */
/* 192 */	NdrFcLong( 0x24 ),	/* 36 */
/* 196 */	NdrFcShort( 0x320 ),	/* Offset= 800 (996) */
/* 198 */	NdrFcLong( 0x4024 ),	/* 16420 */
/* 202 */	NdrFcShort( 0x31a ),	/* Offset= 794 (996) */
/* 204 */	NdrFcLong( 0x4011 ),	/* 16401 */
/* 208 */	NdrFcShort( 0x318 ),	/* Offset= 792 (1000) */
/* 210 */	NdrFcLong( 0x4002 ),	/* 16386 */
/* 214 */	NdrFcShort( 0x316 ),	/* Offset= 790 (1004) */
/* 216 */	NdrFcLong( 0x4003 ),	/* 16387 */
/* 220 */	NdrFcShort( 0x314 ),	/* Offset= 788 (1008) */
/* 222 */	NdrFcLong( 0x4014 ),	/* 16404 */
/* 226 */	NdrFcShort( 0x312 ),	/* Offset= 786 (1012) */
/* 228 */	NdrFcLong( 0x4004 ),	/* 16388 */
/* 232 */	NdrFcShort( 0x310 ),	/* Offset= 784 (1016) */
/* 234 */	NdrFcLong( 0x4005 ),	/* 16389 */
/* 238 */	NdrFcShort( 0x30e ),	/* Offset= 782 (1020) */
/* 240 */	NdrFcLong( 0x400b ),	/* 16395 */
/* 244 */	NdrFcShort( 0x2f8 ),	/* Offset= 760 (1004) */
/* 246 */	NdrFcLong( 0x400a ),	/* 16394 */
/* 250 */	NdrFcShort( 0x2f6 ),	/* Offset= 758 (1008) */
/* 252 */	NdrFcLong( 0x4006 ),	/* 16390 */
/* 256 */	NdrFcShort( 0x300 ),	/* Offset= 768 (1024) */
/* 258 */	NdrFcLong( 0x4007 ),	/* 16391 */
/* 262 */	NdrFcShort( 0x2f6 ),	/* Offset= 758 (1020) */
/* 264 */	NdrFcLong( 0x4008 ),	/* 16392 */
/* 268 */	NdrFcShort( 0x2f8 ),	/* Offset= 760 (1028) */
/* 270 */	NdrFcLong( 0x400d ),	/* 16397 */
/* 274 */	NdrFcShort( 0x2f6 ),	/* Offset= 758 (1032) */
/* 276 */	NdrFcLong( 0x4009 ),	/* 16393 */
/* 280 */	NdrFcShort( 0x2f4 ),	/* Offset= 756 (1036) */
/* 282 */	NdrFcLong( 0x6000 ),	/* 24576 */
/* 286 */	NdrFcShort( 0x2f2 ),	/* Offset= 754 (1040) */
/* 288 */	NdrFcLong( 0x400c ),	/* 16396 */
/* 292 */	NdrFcShort( 0x2f0 ),	/* Offset= 752 (1044) */
/* 294 */	NdrFcLong( 0x10 ),	/* 16 */
/* 298 */	NdrFcShort( 0x8002 ),	/* Simple arm type: FC_CHAR */
/* 300 */	NdrFcLong( 0x12 ),	/* 18 */
/* 304 */	NdrFcShort( 0x8006 ),	/* Simple arm type: FC_SHORT */
/* 306 */	NdrFcLong( 0x13 ),	/* 19 */
/* 310 */	NdrFcShort( 0x8008 ),	/* Simple arm type: FC_LONG */
/* 312 */	NdrFcLong( 0x15 ),	/* 21 */
/* 316 */	NdrFcShort( 0x800b ),	/* Simple arm type: FC_HYPER */
/* 318 */	NdrFcLong( 0x16 ),	/* 22 */
/* 322 */	NdrFcShort( 0x8008 ),	/* Simple arm type: FC_LONG */
/* 324 */	NdrFcLong( 0x17 ),	/* 23 */
/* 328 */	NdrFcShort( 0x8008 ),	/* Simple arm type: FC_LONG */
/* 330 */	NdrFcLong( 0xe ),	/* 14 */
/* 334 */	NdrFcShort( 0x2ce ),	/* Offset= 718 (1052) */
/* 336 */	NdrFcLong( 0x400e ),	/* 16398 */
/* 340 */	NdrFcShort( 0x2d2 ),	/* Offset= 722 (1062) */
/* 342 */	NdrFcLong( 0x4010 ),	/* 16400 */
/* 346 */	NdrFcShort( 0x2d0 ),	/* Offset= 720 (1066) */
/* 348 */	NdrFcLong( 0x4012 ),	/* 16402 */
/* 352 */	NdrFcShort( 0x28c ),	/* Offset= 652 (1004) */
/* 354 */	NdrFcLong( 0x4013 ),	/* 16403 */
/* 358 */	NdrFcShort( 0x28a ),	/* Offset= 650 (1008) */
/* 360 */	NdrFcLong( 0x4015 ),	/* 16405 */
/* 364 */	NdrFcShort( 0x288 ),	/* Offset= 648 (1012) */
/* 366 */	NdrFcLong( 0x4016 ),	/* 16406 */
/* 370 */	NdrFcShort( 0x27e ),	/* Offset= 638 (1008) */
/* 372 */	NdrFcLong( 0x4017 ),	/* 16407 */
/* 376 */	NdrFcShort( 0x278 ),	/* Offset= 632 (1008) */
/* 378 */	NdrFcLong( 0x0 ),	/* 0 */
/* 382 */	NdrFcShort( 0x0 ),	/* Offset= 0 (382) */
/* 384 */	NdrFcLong( 0x1 ),	/* 1 */
/* 388 */	NdrFcShort( 0x0 ),	/* Offset= 0 (388) */
/* 390 */	NdrFcShort( 0xffff ),	/* Offset= -1 (389) */
/* 392 */	
			0x15,		/* FC_STRUCT */
			0x7,		/* 7 */
/* 394 */	NdrFcShort( 0x8 ),	/* 8 */
/* 396 */	0xb,		/* FC_HYPER */
			0x5b,		/* FC_END */
/* 398 */	
			0x13, 0x0,	/* FC_OP */
/* 400 */	NdrFcShort( 0xfe86 ),	/* Offset= -378 (22) */
/* 402 */	
			0x2f,		/* FC_IP */
			0x5a,		/* FC_CONSTANT_IID */
/* 404 */	NdrFcLong( 0x0 ),	/* 0 */
/* 408 */	NdrFcShort( 0x0 ),	/* 0 */
/* 410 */	NdrFcShort( 0x0 ),	/* 0 */
/* 412 */	0xc0,		/* 192 */
			0x0,		/* 0 */
/* 414 */	0x0,		/* 0 */
			0x0,		/* 0 */
/* 416 */	0x0,		/* 0 */
			0x0,		/* 0 */
/* 418 */	0x0,		/* 0 */
			0x46,		/* 70 */
/* 420 */	
			0x2f,		/* FC_IP */
			0x5a,		/* FC_CONSTANT_IID */
/* 422 */	NdrFcLong( 0x20400 ),	/* 132096 */
/* 426 */	NdrFcShort( 0x0 ),	/* 0 */
/* 428 */	NdrFcShort( 0x0 ),	/* 0 */
/* 430 */	0xc0,		/* 192 */
			0x0,		/* 0 */
/* 432 */	0x0,		/* 0 */
			0x0,		/* 0 */
/* 434 */	0x0,		/* 0 */
			0x0,		/* 0 */
/* 436 */	0x0,		/* 0 */
			0x46,		/* 70 */
/* 438 */	
			0x13, 0x10,	/* FC_OP [pointer_deref] */
/* 440 */	NdrFcShort( 0x2 ),	/* Offset= 2 (442) */
/* 442 */	
			0x13, 0x0,	/* FC_OP */
/* 444 */	NdrFcShort( 0x216 ),	/* Offset= 534 (978) */
/* 446 */	
			0x2a,		/* FC_ENCAPSULATED_UNION */
			0x49,		/* 73 */
/* 448 */	NdrFcShort( 0x18 ),	/* 24 */
/* 450 */	NdrFcShort( 0xa ),	/* 10 */
/* 452 */	NdrFcLong( 0x8 ),	/* 8 */
/* 456 */	NdrFcShort( 0x5a ),	/* Offset= 90 (546) */
/* 458 */	NdrFcLong( 0xd ),	/* 13 */
/* 462 */	NdrFcShort( 0x7e ),	/* Offset= 126 (588) */
/* 464 */	NdrFcLong( 0x9 ),	/* 9 */
/* 468 */	NdrFcShort( 0x9e ),	/* Offset= 158 (626) */
/* 470 */	NdrFcLong( 0xc ),	/* 12 */
/* 474 */	NdrFcShort( 0xc8 ),	/* Offset= 200 (674) */
/* 476 */	NdrFcLong( 0x24 ),	/* 36 */
/* 480 */	NdrFcShort( 0x124 ),	/* Offset= 292 (772) */
/* 482 */	NdrFcLong( 0x800d ),	/* 32781 */
/* 486 */	NdrFcShort( 0x140 ),	/* Offset= 320 (806) */
/* 488 */	NdrFcLong( 0x10 ),	/* 16 */
/* 492 */	NdrFcShort( 0x15a ),	/* Offset= 346 (838) */
/* 494 */	NdrFcLong( 0x2 ),	/* 2 */
/* 498 */	NdrFcShort( 0x174 ),	/* Offset= 372 (870) */
/* 500 */	NdrFcLong( 0x3 ),	/* 3 */
/* 504 */	NdrFcShort( 0x18e ),	/* Offset= 398 (902) */
/* 506 */	NdrFcLong( 0x14 ),	/* 20 */
/* 510 */	NdrFcShort( 0x1a8 ),	/* Offset= 424 (934) */
/* 512 */	NdrFcShort( 0xffff ),	/* Offset= -1 (511) */
/* 514 */	
			0x1b,		/* FC_CARRAY */
			0x3,		/* 3 */
/* 516 */	NdrFcShort( 0x4 ),	/* 4 */
/* 518 */	0x19,		/* Corr desc:  field pointer, FC_ULONG */
			0x0,		/*  */
/* 520 */	NdrFcShort( 0x0 ),	/* 0 */
/* 522 */	NdrFcShort( 0x1 ),	/* Corr flags:  early, */
/* 524 */	
			0x4b,		/* FC_PP */
			0x5c,		/* FC_PAD */
/* 526 */	
			0x48,		/* FC_VARIABLE_REPEAT */
			0x49,		/* FC_FIXED_OFFSET */
/* 528 */	NdrFcShort( 0x4 ),	/* 4 */
/* 530 */	NdrFcShort( 0x0 ),	/* 0 */
/* 532 */	NdrFcShort( 0x1 ),	/* 1 */
/* 534 */	NdrFcShort( 0x0 ),	/* 0 */
/* 536 */	NdrFcShort( 0x0 ),	/* 0 */
/* 538 */	0x13, 0x0,	/* FC_OP */
/* 540 */	NdrFcShort( 0xfdfa ),	/* Offset= -518 (22) */
/* 542 */	
			0x5b,		/* FC_END */

			0x8,		/* FC_LONG */
/* 544 */	0x5c,		/* FC_PAD */
			0x5b,		/* FC_END */
/* 546 */	
			0x16,		/* FC_PSTRUCT */
			0x3,		/* 3 */
/* 548 */	NdrFcShort( 0x8 ),	/* 8 */
/* 550 */	
			0x4b,		/* FC_PP */
			0x5c,		/* FC_PAD */
/* 552 */	
			0x46,		/* FC_NO_REPEAT */
			0x5c,		/* FC_PAD */
/* 554 */	NdrFcShort( 0x4 ),	/* 4 */
/* 556 */	NdrFcShort( 0x4 ),	/* 4 */
/* 558 */	0x11, 0x0,	/* FC_RP */
/* 560 */	NdrFcShort( 0xffd2 ),	/* Offset= -46 (514) */
/* 562 */	
			0x5b,		/* FC_END */

			0x8,		/* FC_LONG */
/* 564 */	0x8,		/* FC_LONG */
			0x5b,		/* FC_END */
/* 566 */	
			0x21,		/* FC_BOGUS_ARRAY */
			0x3,		/* 3 */
/* 568 */	NdrFcShort( 0x0 ),	/* 0 */
/* 570 */	0x19,		/* Corr desc:  field pointer, FC_ULONG */
			0x0,		/*  */
/* 572 */	NdrFcShort( 0x0 ),	/* 0 */
/* 574 */	NdrFcShort( 0x1 ),	/* Corr flags:  early, */
/* 576 */	NdrFcLong( 0xffffffff ),	/* -1 */
/* 580 */	NdrFcShort( 0x0 ),	/* Corr flags:  */
/* 582 */	0x4c,		/* FC_EMBEDDED_COMPLEX */
			0x0,		/* 0 */
/* 584 */	NdrFcShort( 0xff4a ),	/* Offset= -182 (402) */
/* 586 */	0x5c,		/* FC_PAD */
			0x5b,		/* FC_END */
/* 588 */	
			0x1a,		/* FC_BOGUS_STRUCT */
			0x3,		/* 3 */
/* 590 */	NdrFcShort( 0x8 ),	/* 8 */
/* 592 */	NdrFcShort( 0x0 ),	/* 0 */
/* 594 */	NdrFcShort( 0x6 ),	/* Offset= 6 (600) */
/* 596 */	0x8,		/* FC_LONG */
			0x36,		/* FC_POINTER */
/* 598 */	0x5c,		/* FC_PAD */
			0x5b,		/* FC_END */
/* 600 */	
			0x11, 0x0,	/* FC_RP */
/* 602 */	NdrFcShort( 0xffdc ),	/* Offset= -36 (566) */
/* 604 */	
			0x21,		/* FC_BOGUS_ARRAY */
			0x3,		/* 3 */
/* 606 */	NdrFcShort( 0x0 ),	/* 0 */
/* 608 */	0x19,		/* Corr desc:  field pointer, FC_ULONG */
			0x0,		/*  */
/* 610 */	NdrFcShort( 0x0 ),	/* 0 */
/* 612 */	NdrFcShort( 0x1 ),	/* Corr flags:  early, */
/* 614 */	NdrFcLong( 0xffffffff ),	/* -1 */
/* 618 */	NdrFcShort( 0x0 ),	/* Corr flags:  */
/* 620 */	0x4c,		/* FC_EMBEDDED_COMPLEX */
			0x0,		/* 0 */
/* 622 */	NdrFcShort( 0xff36 ),	/* Offset= -202 (420) */
/* 624 */	0x5c,		/* FC_PAD */
			0x5b,		/* FC_END */
/* 626 */	
			0x1a,		/* FC_BOGUS_STRUCT */
			0x3,		/* 3 */
/* 628 */	NdrFcShort( 0x8 ),	/* 8 */
/* 630 */	NdrFcShort( 0x0 ),	/* 0 */
/* 632 */	NdrFcShort( 0x6 ),	/* Offset= 6 (638) */
/* 634 */	0x8,		/* FC_LONG */
			0x36,		/* FC_POINTER */
/* 636 */	0x5c,		/* FC_PAD */
			0x5b,		/* FC_END */
/* 638 */	
			0x11, 0x0,	/* FC_RP */
/* 640 */	NdrFcShort( 0xffdc ),	/* Offset= -36 (604) */
/* 642 */	
			0x1b,		/* FC_CARRAY */
			0x3,		/* 3 */
/* 644 */	NdrFcShort( 0x4 ),	/* 4 */
/* 646 */	0x19,		/* Corr desc:  field pointer, FC_ULONG */
			0x0,		/*  */
/* 648 */	NdrFcShort( 0x0 ),	/* 0 */
/* 650 */	NdrFcShort( 0x1 ),	/* Corr flags:  early, */
/* 652 */	
			0x4b,		/* FC_PP */
			0x5c,		/* FC_PAD */
/* 654 */	
			0x48,		/* FC_VARIABLE_REPEAT */
			0x49,		/* FC_FIXED_OFFSET */
/* 656 */	NdrFcShort( 0x4 ),	/* 4 */
/* 658 */	NdrFcShort( 0x0 ),	/* 0 */
/* 660 */	NdrFcShort( 0x1 ),	/* 1 */
/* 662 */	NdrFcShort( 0x0 ),	/* 0 */
/* 664 */	NdrFcShort( 0x0 ),	/* 0 */
/* 666 */	0x13, 0x0,	/* FC_OP */
/* 668 */	NdrFcShort( 0x192 ),	/* Offset= 402 (1070) */
/* 670 */	
			0x5b,		/* FC_END */

			0x8,		/* FC_LONG */
/* 672 */	0x5c,		/* FC_PAD */
			0x5b,		/* FC_END */
/* 674 */	
			0x1a,		/* FC_BOGUS_STRUCT */
			0x3,		/* 3 */
/* 676 */	NdrFcShort( 0x8 ),	/* 8 */
/* 678 */	NdrFcShort( 0x0 ),	/* 0 */
/* 680 */	NdrFcShort( 0x6 ),	/* Offset= 6 (686) */
/* 682 */	0x8,		/* FC_LONG */
			0x36,		/* FC_POINTER */
/* 684 */	0x5c,		/* FC_PAD */
			0x5b,		/* FC_END */
/* 686 */	
			0x11, 0x0,	/* FC_RP */
/* 688 */	NdrFcShort( 0xffd2 ),	/* Offset= -46 (642) */
/* 690 */	
			0x2f,		/* FC_IP */
			0x5a,		/* FC_CONSTANT_IID */
/* 692 */	NdrFcLong( 0x2f ),	/* 47 */
/* 696 */	NdrFcShort( 0x0 ),	/* 0 */
/* 698 */	NdrFcShort( 0x0 ),	/* 0 */
/* 700 */	0xc0,		/* 192 */
			0x0,		/* 0 */
/* 702 */	0x0,		/* 0 */
			0x0,		/* 0 */
/* 704 */	0x0,		/* 0 */
			0x0,		/* 0 */
/* 706 */	0x0,		/* 0 */
			0x46,		/* 70 */
/* 708 */	
			0x1b,		/* FC_CARRAY */
			0x0,		/* 0 */
/* 710 */	NdrFcShort( 0x1 ),	/* 1 */
/* 712 */	0x19,		/* Corr desc:  field pointer, FC_ULONG */
			0x0,		/*  */
/* 714 */	NdrFcShort( 0x4 ),	/* 4 */
/* 716 */	NdrFcShort( 0x1 ),	/* Corr flags:  early, */
/* 718 */	0x1,		/* FC_BYTE */
			0x5b,		/* FC_END */
/* 720 */	
			0x1a,		/* FC_BOGUS_STRUCT */
			0x3,		/* 3 */
/* 722 */	NdrFcShort( 0x10 ),	/* 16 */
/* 724 */	NdrFcShort( 0x0 ),	/* 0 */
/* 726 */	NdrFcShort( 0xa ),	/* Offset= 10 (736) */
/* 728 */	0x8,		/* FC_LONG */
			0x8,		/* FC_LONG */
/* 730 */	0x4c,		/* FC_EMBEDDED_COMPLEX */
			0x0,		/* 0 */
/* 732 */	NdrFcShort( 0xffd6 ),	/* Offset= -42 (690) */
/* 734 */	0x36,		/* FC_POINTER */
			0x5b,		/* FC_END */
/* 736 */	
			0x13, 0x0,	/* FC_OP */
/* 738 */	NdrFcShort( 0xffe2 ),	/* Offset= -30 (708) */
/* 740 */	
			0x1b,		/* FC_CARRAY */
			0x3,		/* 3 */
/* 742 */	NdrFcShort( 0x4 ),	/* 4 */
/* 744 */	0x19,		/* Corr desc:  field pointer, FC_ULONG */
			0x0,		/*  */
/* 746 */	NdrFcShort( 0x0 ),	/* 0 */
/* 748 */	NdrFcShort( 0x1 ),	/* Corr flags:  early, */
/* 750 */	
			0x4b,		/* FC_PP */
			0x5c,		/* FC_PAD */
/* 752 */	
			0x48,		/* FC_VARIABLE_REPEAT */
			0x49,		/* FC_FIXED_OFFSET */
/* 754 */	NdrFcShort( 0x4 ),	/* 4 */
/* 756 */	NdrFcShort( 0x0 ),	/* 0 */
/* 758 */	NdrFcShort( 0x1 ),	/* 1 */
/* 760 */	NdrFcShort( 0x0 ),	/* 0 */
/* 762 */	NdrFcShort( 0x0 ),	/* 0 */
/* 764 */	0x13, 0x0,	/* FC_OP */
/* 766 */	NdrFcShort( 0xffd2 ),	/* Offset= -46 (720) */
/* 768 */	
			0x5b,		/* FC_END */

			0x8,		/* FC_LONG */
/* 770 */	0x5c,		/* FC_PAD */
			0x5b,		/* FC_END */
/* 772 */	
			0x1a,		/* FC_BOGUS_STRUCT */
			0x3,		/* 3 */
/* 774 */	NdrFcShort( 0x8 ),	/* 8 */
/* 776 */	NdrFcShort( 0x0 ),	/* 0 */
/* 778 */	NdrFcShort( 0x6 ),	/* Offset= 6 (784) */
/* 780 */	0x8,		/* FC_LONG */
			0x36,		/* FC_POINTER */
/* 782 */	0x5c,		/* FC_PAD */
			0x5b,		/* FC_END */
/* 784 */	
			0x11, 0x0,	/* FC_RP */
/* 786 */	NdrFcShort( 0xffd2 ),	/* Offset= -46 (740) */
/* 788 */	
			0x1d,		/* FC_SMFARRAY */
			0x0,		/* 0 */
/* 790 */	NdrFcShort( 0x8 ),	/* 8 */
/* 792 */	0x1,		/* FC_BYTE */
			0x5b,		/* FC_END */
/* 794 */	
			0x15,		/* FC_STRUCT */
			0x3,		/* 3 */
/* 796 */	NdrFcShort( 0x10 ),	/* 16 */
/* 798 */	0x8,		/* FC_LONG */
			0x6,		/* FC_SHORT */
/* 800 */	0x6,		/* FC_SHORT */
			0x4c,		/* FC_EMBEDDED_COMPLEX */
/* 802 */	0x0,		/* 0 */
			NdrFcShort( 0xfff1 ),	/* Offset= -15 (788) */
			0x5b,		/* FC_END */
/* 806 */	
			0x1a,		/* FC_BOGUS_STRUCT */
			0x3,		/* 3 */
/* 808 */	NdrFcShort( 0x18 ),	/* 24 */
/* 810 */	NdrFcShort( 0x0 ),	/* 0 */
/* 812 */	NdrFcShort( 0xa ),	/* Offset= 10 (822) */
/* 814 */	0x8,		/* FC_LONG */
			0x36,		/* FC_POINTER */
/* 816 */	0x4c,		/* FC_EMBEDDED_COMPLEX */
			0x0,		/* 0 */
/* 818 */	NdrFcShort( 0xffe8 ),	/* Offset= -24 (794) */
/* 820 */	0x5c,		/* FC_PAD */
			0x5b,		/* FC_END */
/* 822 */	
			0x11, 0x0,	/* FC_RP */
/* 824 */	NdrFcShort( 0xfefe ),	/* Offset= -258 (566) */
/* 826 */	
			0x1b,		/* FC_CARRAY */
			0x0,		/* 0 */
/* 828 */	NdrFcShort( 0x1 ),	/* 1 */
/* 830 */	0x19,		/* Corr desc:  field pointer, FC_ULONG */
			0x0,		/*  */
/* 832 */	NdrFcShort( 0x0 ),	/* 0 */
/* 834 */	NdrFcShort( 0x1 ),	/* Corr flags:  early, */
/* 836 */	0x1,		/* FC_BYTE */
			0x5b,		/* FC_END */
/* 838 */	
			0x16,		/* FC_PSTRUCT */
			0x3,		/* 3 */
/* 840 */	NdrFcShort( 0x8 ),	/* 8 */
/* 842 */	
			0x4b,		/* FC_PP */
			0x5c,		/* FC_PAD */
/* 844 */	
			0x46,		/* FC_NO_REPEAT */
			0x5c,		/* FC_PAD */
/* 846 */	NdrFcShort( 0x4 ),	/* 4 */
/* 848 */	NdrFcShort( 0x4 ),	/* 4 */
/* 850 */	0x13, 0x0,	/* FC_OP */
/* 852 */	NdrFcShort( 0xffe6 ),	/* Offset= -26 (826) */
/* 854 */	
			0x5b,		/* FC_END */

			0x8,		/* FC_LONG */
/* 856 */	0x8,		/* FC_LONG */
			0x5b,		/* FC_END */
/* 858 */	
			0x1b,		/* FC_CARRAY */
			0x1,		/* 1 */
/* 860 */	NdrFcShort( 0x2 ),	/* 2 */
/* 862 */	0x19,		/* Corr desc:  field pointer, FC_ULONG */
			0x0,		/*  */
/* 864 */	NdrFcShort( 0x0 ),	/* 0 */
/* 866 */	NdrFcShort( 0x1 ),	/* Corr flags:  early, */
/* 868 */	0x6,		/* FC_SHORT */
			0x5b,		/* FC_END */
/* 870 */	
			0x16,		/* FC_PSTRUCT */
			0x3,		/* 3 */
/* 872 */	NdrFcShort( 0x8 ),	/* 8 */
/* 874 */	
			0x4b,		/* FC_PP */
			0x5c,		/* FC_PAD */
/* 876 */	
			0x46,		/* FC_NO_REPEAT */
			0x5c,		/* FC_PAD */
/* 878 */	NdrFcShort( 0x4 ),	/* 4 */
/* 880 */	NdrFcShort( 0x4 ),	/* 4 */
/* 882 */	0x13, 0x0,	/* FC_OP */
/* 884 */	NdrFcShort( 0xffe6 ),	/* Offset= -26 (858) */
/* 886 */	
			0x5b,		/* FC_END */

			0x8,		/* FC_LONG */
/* 888 */	0x8,		/* FC_LONG */
			0x5b,		/* FC_END */
/* 890 */	
			0x1b,		/* FC_CARRAY */
			0x3,		/* 3 */
/* 892 */	NdrFcShort( 0x4 ),	/* 4 */
/* 894 */	0x19,		/* Corr desc:  field pointer, FC_ULONG */
			0x0,		/*  */
/* 896 */	NdrFcShort( 0x0 ),	/* 0 */
/* 898 */	NdrFcShort( 0x1 ),	/* Corr flags:  early, */
/* 900 */	0x8,		/* FC_LONG */
			0x5b,		/* FC_END */
/* 902 */	
			0x16,		/* FC_PSTRUCT */
			0x3,		/* 3 */
/* 904 */	NdrFcShort( 0x8 ),	/* 8 */
/* 906 */	
			0x4b,		/* FC_PP */
			0x5c,		/* FC_PAD */
/* 908 */	
			0x46,		/* FC_NO_REPEAT */
			0x5c,		/* FC_PAD */
/* 910 */	NdrFcShort( 0x4 ),	/* 4 */
/* 912 */	NdrFcShort( 0x4 ),	/* 4 */
/* 914 */	0x13, 0x0,	/* FC_OP */
/* 916 */	NdrFcShort( 0xffe6 ),	/* Offset= -26 (890) */
/* 918 */	
			0x5b,		/* FC_END */

			0x8,		/* FC_LONG */
/* 920 */	0x8,		/* FC_LONG */
			0x5b,		/* FC_END */
/* 922 */	
			0x1b,		/* FC_CARRAY */
			0x7,		/* 7 */
/* 924 */	NdrFcShort( 0x8 ),	/* 8 */
/* 926 */	0x19,		/* Corr desc:  field pointer, FC_ULONG */
			0x0,		/*  */
/* 928 */	NdrFcShort( 0x0 ),	/* 0 */
/* 930 */	NdrFcShort( 0x1 ),	/* Corr flags:  early, */
/* 932 */	0xb,		/* FC_HYPER */
			0x5b,		/* FC_END */
/* 934 */	
			0x16,		/* FC_PSTRUCT */
			0x3,		/* 3 */
/* 936 */	NdrFcShort( 0x8 ),	/* 8 */
/* 938 */	
			0x4b,		/* FC_PP */
			0x5c,		/* FC_PAD */
/* 940 */	
			0x46,		/* FC_NO_REPEAT */
			0x5c,		/* FC_PAD */
/* 942 */	NdrFcShort( 0x4 ),	/* 4 */
/* 944 */	NdrFcShort( 0x4 ),	/* 4 */
/* 946 */	0x13, 0x0,	/* FC_OP */
/* 948 */	NdrFcShort( 0xffe6 ),	/* Offset= -26 (922) */
/* 950 */	
			0x5b,		/* FC_END */

			0x8,		/* FC_LONG */
/* 952 */	0x8,		/* FC_LONG */
			0x5b,		/* FC_END */
/* 954 */	
			0x15,		/* FC_STRUCT */
			0x3,		/* 3 */
/* 956 */	NdrFcShort( 0x8 ),	/* 8 */
/* 958 */	0x8,		/* FC_LONG */
			0x8,		/* FC_LONG */
/* 960 */	0x5c,		/* FC_PAD */
			0x5b,		/* FC_END */
/* 962 */	
			0x1b,		/* FC_CARRAY */
			0x3,		/* 3 */
/* 964 */	NdrFcShort( 0x8 ),	/* 8 */
/* 966 */	0x7,		/* Corr desc: FC_USHORT */
			0x0,		/*  */
/* 968 */	NdrFcShort( 0xffd8 ),	/* -40 */
/* 970 */	NdrFcShort( 0x1 ),	/* Corr flags:  early, */
/* 972 */	0x4c,		/* FC_EMBEDDED_COMPLEX */
			0x0,		/* 0 */
/* 974 */	NdrFcShort( 0xffec ),	/* Offset= -20 (954) */
/* 976 */	0x5c,		/* FC_PAD */
			0x5b,		/* FC_END */
/* 978 */	
			0x1a,		/* FC_BOGUS_STRUCT */
			0x3,		/* 3 */
/* 980 */	NdrFcShort( 0x28 ),	/* 40 */
/* 982 */	NdrFcShort( 0xffec ),	/* Offset= -20 (962) */
/* 984 */	NdrFcShort( 0x0 ),	/* Offset= 0 (984) */
/* 986 */	0x6,		/* FC_SHORT */
			0x6,		/* FC_SHORT */
/* 988 */	0x8,		/* FC_LONG */
			0x8,		/* FC_LONG */
/* 990 */	0x4c,		/* FC_EMBEDDED_COMPLEX */
			0x0,		/* 0 */
/* 992 */	NdrFcShort( 0xfdde ),	/* Offset= -546 (446) */
/* 994 */	0x5c,		/* FC_PAD */
			0x5b,		/* FC_END */
/* 996 */	
			0x13, 0x0,	/* FC_OP */
/* 998 */	NdrFcShort( 0xfeea ),	/* Offset= -278 (720) */
/* 1000 */	
			0x13, 0x8,	/* FC_OP [simple_pointer] */
/* 1002 */	0x1,		/* FC_BYTE */
			0x5c,		/* FC_PAD */
/* 1004 */	
			0x13, 0x8,	/* FC_OP [simple_pointer] */
/* 1006 */	0x6,		/* FC_SHORT */
			0x5c,		/* FC_PAD */
/* 1008 */	
			0x13, 0x8,	/* FC_OP [simple_pointer] */
/* 1010 */	0x8,		/* FC_LONG */
			0x5c,		/* FC_PAD */
/* 1012 */	
			0x13, 0x8,	/* FC_OP [simple_pointer] */
/* 1014 */	0xb,		/* FC_HYPER */
			0x5c,		/* FC_PAD */
/* 1016 */	
			0x13, 0x8,	/* FC_OP [simple_pointer] */
/* 1018 */	0xa,		/* FC_FLOAT */
			0x5c,		/* FC_PAD */
/* 1020 */	
			0x13, 0x8,	/* FC_OP [simple_pointer] */
/* 1022 */	0xc,		/* FC_DOUBLE */
			0x5c,		/* FC_PAD */
/* 1024 */	
			0x13, 0x0,	/* FC_OP */
/* 1026 */	NdrFcShort( 0xfd86 ),	/* Offset= -634 (392) */
/* 1028 */	
			0x13, 0x10,	/* FC_OP [pointer_deref] */
/* 1030 */	NdrFcShort( 0xfd88 ),	/* Offset= -632 (398) */
/* 1032 */	
			0x13, 0x10,	/* FC_OP [pointer_deref] */
/* 1034 */	NdrFcShort( 0xfd88 ),	/* Offset= -632 (402) */
/* 1036 */	
			0x13, 0x10,	/* FC_OP [pointer_deref] */
/* 1038 */	NdrFcShort( 0xfd96 ),	/* Offset= -618 (420) */
/* 1040 */	
			0x13, 0x10,	/* FC_OP [pointer_deref] */
/* 1042 */	NdrFcShort( 0xfda4 ),	/* Offset= -604 (438) */
/* 1044 */	
			0x13, 0x10,	/* FC_OP [pointer_deref] */
/* 1046 */	NdrFcShort( 0x2 ),	/* Offset= 2 (1048) */
/* 1048 */	
			0x13, 0x0,	/* FC_OP */
/* 1050 */	NdrFcShort( 0x14 ),	/* Offset= 20 (1070) */
/* 1052 */	
			0x15,		/* FC_STRUCT */
			0x7,		/* 7 */
/* 1054 */	NdrFcShort( 0x10 ),	/* 16 */
/* 1056 */	0x6,		/* FC_SHORT */
			0x1,		/* FC_BYTE */
/* 1058 */	0x1,		/* FC_BYTE */
			0x8,		/* FC_LONG */
/* 1060 */	0xb,		/* FC_HYPER */
			0x5b,		/* FC_END */
/* 1062 */	
			0x13, 0x0,	/* FC_OP */
/* 1064 */	NdrFcShort( 0xfff4 ),	/* Offset= -12 (1052) */
/* 1066 */	
			0x13, 0x8,	/* FC_OP [simple_pointer] */
/* 1068 */	0x2,		/* FC_CHAR */
			0x5c,		/* FC_PAD */
/* 1070 */	
			0x1a,		/* FC_BOGUS_STRUCT */
			0x7,		/* 7 */
/* 1072 */	NdrFcShort( 0x20 ),	/* 32 */
/* 1074 */	NdrFcShort( 0x0 ),	/* 0 */
/* 1076 */	NdrFcShort( 0x0 ),	/* Offset= 0 (1076) */
/* 1078 */	0x8,		/* FC_LONG */
			0x8,		/* FC_LONG */
/* 1080 */	0x6,		/* FC_SHORT */
			0x6,		/* FC_SHORT */
/* 1082 */	0x6,		/* FC_SHORT */
			0x6,		/* FC_SHORT */
/* 1084 */	0x4c,		/* FC_EMBEDDED_COMPLEX */
			0x0,		/* 0 */
/* 1086 */	NdrFcShort( 0xfc20 ),	/* Offset= -992 (94) */
/* 1088 */	0x5c,		/* FC_PAD */
			0x5b,		/* FC_END */
/* 1090 */	0xb4,		/* FC_USER_MARSHAL */
			0x83,		/* 131 */
/* 1092 */	NdrFcShort( 0x1 ),	/* 1 */
/* 1094 */	NdrFcShort( 0x10 ),	/* 16 */
/* 1096 */	NdrFcShort( 0x0 ),	/* 0 */
/* 1098 */	NdrFcShort( 0xfc10 ),	/* Offset= -1008 (90) */
/* 1100 */	
			0x11, 0xc,	/* FC_RP [alloced_on_stack] [simple_pointer] */
/* 1102 */	0x6,		/* FC_SHORT */
			0x5c,		/* FC_PAD */
/* 1104 */	
			0x11, 0x10,	/* FC_RP [pointer_deref] */
/* 1106 */	NdrFcShort( 0x2 ),	/* Offset= 2 (1108) */
/* 1108 */	
			0x2f,		/* FC_IP */
			0x5a,		/* FC_CONSTANT_IID */
/* 1110 */	NdrFcLong( 0x56a868b4 ),	/* 1453877428 */
/* 1114 */	NdrFcShort( 0xad4 ),	/* 2772 */
/* 1116 */	NdrFcShort( 0x11ce ),	/* 4558 */
/* 1118 */	0xb0,		/* 176 */
			0x3a,		/* 58 */
/* 1120 */	0x0,		/* 0 */
			0x20,		/* 32 */
/* 1122 */	0xaf,		/* 175 */
			0xb,		/* 11 */
/* 1124 */	0xa7,		/* 167 */
			0x70,		/* 112 */
/* 1126 */	
			0x11, 0x4,	/* FC_RP [alloced_on_stack] */
/* 1128 */	NdrFcShort( 0x2 ),	/* Offset= 2 (1130) */
/* 1130 */	0xb4,		/* FC_USER_MARSHAL */
			0x83,		/* 131 */
/* 1132 */	NdrFcShort( 0x0 ),	/* 0 */
/* 1134 */	NdrFcShort( 0x4 ),	/* 4 */
/* 1136 */	NdrFcShort( 0x0 ),	/* 0 */
/* 1138 */	NdrFcShort( 0xfd1c ),	/* Offset= -740 (398) */
/* 1140 */	
			0x11, 0x10,	/* FC_RP [pointer_deref] */
/* 1142 */	NdrFcShort( 0x2 ),	/* Offset= 2 (1144) */
/* 1144 */	
			0x2f,		/* FC_IP */
			0x5a,		/* FC_CONSTANT_IID */
/* 1146 */	NdrFcLong( 0x17d7cdfc ),	/* 400018940 */
/* 1150 */	NdrFcShort( 0xb007 ),	/* -20473 */
/* 1152 */	NdrFcShort( 0x484c ),	/* 18508 */
/* 1154 */	0x99,		/* 153 */
			0xd2,		/* 210 */
/* 1156 */	0x86,		/* 134 */
			0xa8,		/* 168 */
/* 1158 */	0xa8,		/* 168 */
			0x20,		/* 32 */
/* 1160 */	0x99,		/* 153 */
			0x1d,		/* 29 */
/* 1162 */	
			0x2f,		/* FC_IP */
			0x5a,		/* FC_CONSTANT_IID */
/* 1164 */	NdrFcLong( 0xba7f518e ),	/* -1166061170 */
/* 1168 */	NdrFcShort( 0xd336 ),	/* -11466 */
/* 1170 */	NdrFcShort( 0x4070 ),	/* 16496 */
/* 1172 */	0x93,		/* 147 */
			0xa6,		/* 166 */
/* 1174 */	0x86,		/* 134 */
			0x53,		/* 83 */
/* 1176 */	0x95,		/* 149 */
			0xc8,		/* 200 */
/* 1178 */	0x43,		/* 67 */
			0xf9,		/* 249 */
/* 1180 */	
			0x12, 0x0,	/* FC_UP */
/* 1182 */	NdrFcShort( 0xff90 ),	/* Offset= -112 (1070) */
/* 1184 */	0xb4,		/* FC_USER_MARSHAL */
			0x83,		/* 131 */
/* 1186 */	NdrFcShort( 0x1 ),	/* 1 */
/* 1188 */	NdrFcShort( 0x10 ),	/* 16 */
/* 1190 */	NdrFcShort( 0x0 ),	/* 0 */
/* 1192 */	NdrFcShort( 0xfff4 ),	/* Offset= -12 (1180) */
/* 1194 */	
			0x11, 0x10,	/* FC_RP [pointer_deref] */
/* 1196 */	NdrFcShort( 0x2 ),	/* Offset= 2 (1198) */
/* 1198 */	
			0x2f,		/* FC_IP */
			0x5a,		/* FC_CONSTANT_IID */
/* 1200 */	NdrFcLong( 0xf7296917 ),	/* -148281065 */
/* 1204 */	NdrFcShort( 0x5569 ),	/* 21865 */
/* 1206 */	NdrFcShort( 0x4b3b ),	/* 19259 */
/* 1208 */	0xb3,		/* 179 */
			0xaf,		/* 175 */
/* 1210 */	0x98,		/* 152 */
			0xd1,		/* 209 */
/* 1212 */	0x14,		/* 20 */
			0x4b,		/* 75 */
/* 1214 */	0x2b,		/* 43 */
			0x87,		/* 135 */
/* 1216 */	
			0x11, 0x10,	/* FC_RP [pointer_deref] */
/* 1218 */	NdrFcShort( 0x2 ),	/* Offset= 2 (1220) */
/* 1220 */	
			0x2f,		/* FC_IP */
			0x5a,		/* FC_CONSTANT_IID */
/* 1222 */	NdrFcLong( 0xec7c8096 ),	/* -327384938 */
/* 1226 */	NdrFcShort( 0xb918 ),	/* -18152 */
/* 1228 */	NdrFcShort( 0x4044 ),	/* 16452 */
/* 1230 */	0x94,		/* 148 */
			0xf1,		/* 241 */
/* 1232 */	0xe4,		/* 228 */
			0xfb,		/* 251 */
/* 1234 */	0xa0,		/* 160 */
			0x36,		/* 54 */
/* 1236 */	0x1d,		/* 29 */
			0x5c,		/* 92 */
/* 1238 */	
			0x11, 0x10,	/* FC_RP [pointer_deref] */
/* 1240 */	NdrFcShort( 0x2 ),	/* Offset= 2 (1242) */
/* 1242 */	
			0x2f,		/* FC_IP */
			0x5a,		/* FC_CONSTANT_IID */
/* 1244 */	NdrFcLong( 0xfcb136c8 ),	/* -55494968 */
/* 1248 */	NdrFcShort( 0x7b90 ),	/* 31632 */
/* 1250 */	NdrFcShort( 0x4e0c ),	/* 19980 */
/* 1252 */	0xbe,		/* 190 */
			0xfe,		/* 254 */
/* 1254 */	0x56,		/* 86 */
			0xed,		/* 237 */
/* 1256 */	0xf0,		/* 240 */
			0xba,		/* 186 */
/* 1258 */	0x6f,		/* 111 */
			0x1c,		/* 28 */
/* 1260 */	
			0x11, 0x10,	/* FC_RP [pointer_deref] */
/* 1262 */	NdrFcShort( 0x2 ),	/* Offset= 2 (1264) */
/* 1264 */	
			0x2f,		/* FC_IP */
			0x5a,		/* FC_CONSTANT_IID */
/* 1266 */	NdrFcLong( 0xa87d55d7 ),	/* -1468181033 */
/* 1270 */	NdrFcShort( 0xdb74 ),	/* -9356 */
/* 1272 */	NdrFcShort( 0x4ed1 ),	/* 20177 */
/* 1274 */	0x9c,		/* 156 */
			0xa4,		/* 164 */
/* 1276 */	0x77,		/* 119 */
			0xa0,		/* 160 */
/* 1278 */	0xe4,		/* 228 */
			0x1b,		/* 27 */
/* 1280 */	0x41,		/* 65 */
			0x3e,		/* 62 */
/* 1282 */	
			0x11, 0x10,	/* FC_RP [pointer_deref] */
/* 1284 */	NdrFcShort( 0x2 ),	/* Offset= 2 (1286) */
/* 1286 */	
			0x2f,		/* FC_IP */
			0x5a,		/* FC_CONSTANT_IID */
/* 1288 */	NdrFcLong( 0xc7cedad8 ),	/* -942744872 */
/* 1292 */	NdrFcShort( 0x346b ),	/* 13419 */
/* 1294 */	NdrFcShort( 0x4d1b ),	/* 19739 */
/* 1296 */	0xac,		/* 172 */
			0x2,		/* 2 */
/* 1298 */	0xa2,		/* 162 */
			0x8,		/* 8 */
/* 1300 */	0x8d,		/* 141 */
			0xf9,		/* 249 */
/* 1302 */	0xbe,		/* 190 */
			0x4f,		/* 79 */
/* 1304 */	
			0x11, 0x10,	/* FC_RP [pointer_deref] */
/* 1306 */	NdrFcShort( 0x2 ),	/* Offset= 2 (1308) */
/* 1308 */	
			0x2f,		/* FC_IP */
			0x5a,		/* FC_CONSTANT_IID */
/* 1310 */	NdrFcLong( 0x60361e68 ),	/* 1614159464 */
/* 1314 */	NdrFcShort( 0x9164 ),	/* -28316 */
/* 1316 */	NdrFcShort( 0x4389 ),	/* 17289 */
/* 1318 */	0xa4,		/* 164 */
			0xc6,		/* 198 */
/* 1320 */	0xd0,		/* 208 */
			0xb3,		/* 179 */
/* 1322 */	0x92,		/* 146 */
			0x5b,		/* 91 */
/* 1324 */	0xda,		/* 218 */
			0x5e,		/* 94 */
/* 1326 */	0x11, 0x10,	/* FC_RP [pointer_deref] */
/* 1328 */	NdrFcShort( 0x2 ),	/* Offset= 2 (1330) */
/* 1330 */	
			0x2f,		/* FC_IP */
			0x5a,		/* FC_CONSTANT_IID */
/* 1332 */	NdrFcLong( 0x742378d6 ),	/* 1948481750 */
/* 1336 */	NdrFcShort( 0xa141 ),	/* -24255 */
/* 1338 */	NdrFcShort( 0x4415 ),	/* 17429 */
/* 1340 */	0x8f,		/* 143 */
			0x27,		/* 39 */
/* 1342 */	0x35,		/* 53 */
			0xd9,		/* 217 */
/* 1344 */	0x90,		/* 144 */
			0x76,		/* 118 */
/* 1346 */	0xcf,		/* 207 */
			0x5d,		/* 93 */
/* 1348 */	
			0x11, 0x10,	/* FC_RP [pointer_deref] */
/* 1350 */	NdrFcShort( 0x2 ),	/* Offset= 2 (1352) */
/* 1352 */	
			0x2f,		/* FC_IP */
			0x5a,		/* FC_CONSTANT_IID */
/* 1354 */	NdrFcLong( 0xec7c8096 ),	/* -327384938 */
/* 1358 */	NdrFcShort( 0xb918 ),	/* -18152 */
/* 1360 */	NdrFcShort( 0x4044 ),	/* 16452 */
/* 1362 */	0x94,		/* 148 */
			0xf1,		/* 241 */
/* 1364 */	0xe4,		/* 228 */
			0xfb,		/* 251 */
/* 1366 */	0xa0,		/* 160 */
			0x36,		/* 54 */
/* 1368 */	0x1d,		/* 29 */
			0x5c,		/* 92 */
/* 1370 */	
			0x11, 0x10,	/* FC_RP [pointer_deref] */
/* 1372 */	NdrFcShort( 0x2 ),	/* Offset= 2 (1374) */
/* 1374 */	
			0x2f,		/* FC_IP */
			0x5a,		/* FC_CONSTANT_IID */
/* 1376 */	NdrFcLong( 0xd4d9967f ),	/* -723937665 */
/* 1380 */	NdrFcShort( 0xd011 ),	/* -12271 */
/* 1382 */	NdrFcShort( 0x4b1d ),	/* 19229 */
/* 1384 */	0x91,		/* 145 */
			0xe3,		/* 227 */
/* 1386 */	0xab,		/* 171 */
			0xa7,		/* 167 */
/* 1388 */	0x8f,		/* 143 */
			0x96,		/* 150 */
/* 1390 */	0x39,		/* 57 */
			0x3d,		/* 61 */
/* 1392 */	
			0x11, 0x10,	/* FC_RP [pointer_deref] */
/* 1394 */	NdrFcShort( 0x2 ),	/* Offset= 2 (1396) */
/* 1396 */	
			0x2f,		/* FC_IP */
			0x5a,		/* FC_CONSTANT_IID */
/* 1398 */	NdrFcLong( 0x102f9588 ),	/* 271553928 */
/* 1402 */	NdrFcShort( 0x23e7 ),	/* 9191 */
/* 1404 */	NdrFcShort( 0x40e3 ),	/* 16611 */
/* 1406 */	0x95,		/* 149 */
			0x4d,		/* 77 */
/* 1408 */	0xcd,		/* 205 */
			0x7a,		/* 122 */
/* 1410 */	0x1d,		/* 29 */
			0x5c,		/* 92 */
/* 1412 */	0x3,		/* 3 */
			0x61,		/* 97 */
/* 1414 */	
			0x11, 0x10,	/* FC_RP [pointer_deref] */
/* 1416 */	NdrFcShort( 0xfaa2 ),	/* Offset= -1374 (42) */
/* 1418 */	
			0x11, 0x10,	/* FC_RP [pointer_deref] */
/* 1420 */	NdrFcShort( 0x2 ),	/* Offset= 2 (1422) */
/* 1422 */	
			0x2f,		/* FC_IP */
			0x5a,		/* FC_CONSTANT_IID */
/* 1424 */	NdrFcLong( 0x29b7c41c ),	/* 699909148 */
/* 1428 */	NdrFcShort( 0xed82 ),	/* -4734 */
/* 1430 */	NdrFcShort( 0x4bca ),	/* 19402 */
/* 1432 */	0x84,		/* 132 */
			0xad,		/* 173 */
/* 1434 */	0x39,		/* 57 */
			0xd5,		/* 213 */
/* 1436 */	0x10,		/* 16 */
			0x1b,		/* 27 */
/* 1438 */	0x58,		/* 88 */
			0xe3,		/* 227 */
/* 1440 */	
			0x11, 0x10,	/* FC_RP [pointer_deref] */
/* 1442 */	NdrFcShort( 0x2 ),	/* Offset= 2 (1444) */
/* 1444 */	
			0x2f,		/* FC_IP */
			0x5a,		/* FC_CONSTANT_IID */
/* 1446 */	NdrFcLong( 0x7829e45 ),	/* 126000709 */
/* 1450 */	NdrFcShort( 0x9a34 ),	/* -26060 */
/* 1452 */	NdrFcShort( 0x408e ),	/* 16526 */
/* 1454 */	0xa0,		/* 160 */
			0x11,		/* 17 */
/* 1456 */	0xbd,		/* 189 */
			0xdf,		/* 223 */
/* 1458 */	0x13,		/* 19 */
			0x48,		/* 72 */
/* 1460 */	0x7c,		/* 124 */
			0xd1,		/* 209 */
/* 1462 */	
			0x11, 0x10,	/* FC_RP [pointer_deref] */
/* 1464 */	NdrFcShort( 0x2 ),	/* Offset= 2 (1466) */
/* 1466 */	
			0x2f,		/* FC_IP */
			0x5a,		/* FC_CONSTANT_IID */
/* 1468 */	NdrFcLong( 0xae86add5 ),	/* -1366905387 */
/* 1472 */	NdrFcShort( 0x26b1 ),	/* 9905 */
/* 1474 */	NdrFcShort( 0x4414 ),	/* 17428 */
/* 1476 */	0xaf,		/* 175 */
			0x1d,		/* 29 */
/* 1478 */	0xb9,		/* 185 */
			0x4c,		/* 76 */
/* 1480 */	0xd9,		/* 217 */
			0x38,		/* 56 */
/* 1482 */	0xd7,		/* 215 */
			0x39,		/* 57 */
/* 1484 */	
			0x11, 0x10,	/* FC_RP [pointer_deref] */
/* 1486 */	NdrFcShort( 0x2 ),	/* Offset= 2 (1488) */
/* 1488 */	
			0x2f,		/* FC_IP */
			0x5a,		/* FC_CONSTANT_IID */
/* 1490 */	NdrFcLong( 0xfcd56f29 ),	/* -53121239 */
/* 1494 */	NdrFcShort( 0x4a4f ),	/* 19023 */
/* 1496 */	NdrFcShort( 0x41b2 ),	/* 16818 */
/* 1498 */	0xba,		/* 186 */
			0x5c,		/* 92 */
/* 1500 */	0xf5,		/* 245 */
			0xbc,		/* 188 */
/* 1502 */	0xcc,		/* 204 */
			0x6,		/* 6 */
/* 1504 */	0xb,		/* 11 */
			0xf6,		/* 246 */
/* 1506 */	
			0x11, 0x10,	/* FC_RP [pointer_deref] */
/* 1508 */	NdrFcShort( 0x2 ),	/* Offset= 2 (1510) */
/* 1510 */	
			0x2f,		/* FC_IP */
			0x5a,		/* FC_CONSTANT_IID */
/* 1512 */	NdrFcLong( 0xb492d4b4 ),	/* -1265445708 */
/* 1516 */	NdrFcShort( 0x42df ),	/* 17119 */
/* 1518 */	NdrFcShort( 0x430a ),	/* 17162 */
/* 1520 */	0x84,		/* 132 */
			0x8f,		/* 143 */
/* 1522 */	0x36,		/* 54 */
			0xfb,		/* 251 */
/* 1524 */	0x39,		/* 57 */
			0xfd,		/* 253 */
/* 1526 */	0x0,		/* 0 */
			0x5f,		/* 95 */
/* 1528 */	
			0x11, 0x10,	/* FC_RP [pointer_deref] */
/* 1530 */	NdrFcShort( 0x2 ),	/* Offset= 2 (1532) */
/* 1532 */	
			0x2f,		/* FC_IP */
			0x5a,		/* FC_CONSTANT_IID */
/* 1534 */	NdrFcLong( 0x387c8086 ),	/* 947683462 */
/* 1538 */	NdrFcShort( 0x99be ),	/* -26178 */
/* 1540 */	NdrFcShort( 0x42fb ),	/* 17147 */
/* 1542 */	0x99,		/* 153 */
			0x73,		/* 115 */
/* 1544 */	0x7c,		/* 124 */
			0xf,		/* 15 */
/* 1546 */	0xc0,		/* 192 */
			0xca,		/* 202 */
/* 1548 */	0x9f,		/* 159 */
			0xa8,		/* 168 */
/* 1550 */	
			0x11, 0x10,	/* FC_RP [pointer_deref] */
/* 1552 */	NdrFcShort( 0x2 ),	/* Offset= 2 (1554) */
/* 1554 */	
			0x2f,		/* FC_IP */
			0x5a,		/* FC_CONSTANT_IID */
/* 1556 */	NdrFcLong( 0x4b81f84e ),	/* 1266808910 */
/* 1560 */	NdrFcShort( 0xbdc7 ),	/* -16953 */
/* 1562 */	NdrFcShort( 0x4184 ),	/* 16772 */
/* 1564 */	0x91,		/* 145 */
			0x54,		/* 84 */
/* 1566 */	0x3c,		/* 60 */
			0xb2,		/* 178 */
/* 1568 */	0xdd,		/* 221 */
			0x79,		/* 121 */
/* 1570 */	0x17,		/* 23 */
			0xfb,		/* 251 */
/* 1572 */	
			0x11, 0x10,	/* FC_RP [pointer_deref] */
/* 1574 */	NdrFcShort( 0x2 ),	/* Offset= 2 (1576) */
/* 1576 */	
			0x2f,		/* FC_IP */
			0x5a,		/* FC_CONSTANT_IID */
/* 1578 */	NdrFcLong( 0xd07eca9e ),	/* -796996962 */
/* 1582 */	NdrFcShort( 0x4062 ),	/* 16482 */
/* 1584 */	NdrFcShort( 0x4dd4 ),	/* 19924 */
/* 1586 */	0x9e,		/* 158 */
			0x7d,		/* 125 */
/* 1588 */	0x72,		/* 114 */
			0x2a,		/* 42 */
/* 1590 */	0x49,		/* 73 */
			0xba,		/* 186 */
/* 1592 */	0x73,		/* 115 */
			0x3,		/* 3 */
/* 1594 */	
			0x11, 0x10,	/* FC_RP [pointer_deref] */
/* 1596 */	NdrFcShort( 0x2 ),	/* Offset= 2 (1598) */
/* 1598 */	
			0x2f,		/* FC_IP */
			0x5a,		/* FC_CONSTANT_IID */
/* 1600 */	NdrFcLong( 0x7829e45 ),	/* 126000709 */
/* 1604 */	NdrFcShort( 0x9a34 ),	/* -26060 */
/* 1606 */	NdrFcShort( 0x408e ),	/* 16526 */
/* 1608 */	0xa0,		/* 160 */
			0x11,		/* 17 */
/* 1610 */	0xbd,		/* 189 */
			0xdf,		/* 223 */
/* 1612 */	0x13,		/* 19 */
			0x48,		/* 72 */
/* 1614 */	0x7c,		/* 124 */
			0xd1,		/* 209 */
/* 1616 */	
			0x11, 0x10,	/* FC_RP [pointer_deref] */
/* 1618 */	NdrFcShort( 0x2 ),	/* Offset= 2 (1620) */
/* 1620 */	
			0x2f,		/* FC_IP */
			0x5a,		/* FC_CONSTANT_IID */
/* 1622 */	NdrFcLong( 0xfcb136c8 ),	/* -55494968 */
/* 1626 */	NdrFcShort( 0x7b90 ),	/* 31632 */
/* 1628 */	NdrFcShort( 0x4e0c ),	/* 19980 */
/* 1630 */	0xbe,		/* 190 */
			0xfe,		/* 254 */
/* 1632 */	0x56,		/* 86 */
			0xed,		/* 237 */
/* 1634 */	0xf0,		/* 240 */
			0xba,		/* 186 */
/* 1636 */	0x6f,		/* 111 */
			0x1c,		/* 28 */
/* 1638 */	
			0x11, 0x10,	/* FC_RP [pointer_deref] */
/* 1640 */	NdrFcShort( 0x2 ),	/* Offset= 2 (1642) */
/* 1642 */	
			0x2f,		/* FC_IP */
			0x5a,		/* FC_CONSTANT_IID */
/* 1644 */	NdrFcLong( 0xc7cedad8 ),	/* -942744872 */
/* 1648 */	NdrFcShort( 0x346b ),	/* 13419 */
/* 1650 */	NdrFcShort( 0x4d1b ),	/* 19739 */
/* 1652 */	0xac,		/* 172 */
			0x2,		/* 2 */
/* 1654 */	0xa2,		/* 162 */
			0x8,		/* 8 */
/* 1656 */	0x8d,		/* 141 */
			0xf9,		/* 249 */
/* 1658 */	0xbe,		/* 190 */
			0x4f,		/* 79 */
/* 1660 */	
			0x11, 0x10,	/* FC_RP [pointer_deref] */
/* 1662 */	NdrFcShort( 0x2 ),	/* Offset= 2 (1664) */
/* 1664 */	
			0x2f,		/* FC_IP */
			0x5a,		/* FC_CONSTANT_IID */
/* 1666 */	NdrFcLong( 0x60361e68 ),	/* 1614159464 */
/* 1670 */	NdrFcShort( 0x9164 ),	/* -28316 */
/* 1672 */	NdrFcShort( 0x4389 ),	/* 17289 */
/* 1674 */	0xa4,		/* 164 */
			0xc6,		/* 198 */
/* 1676 */	0xd0,		/* 208 */
			0xb3,		/* 179 */
/* 1678 */	0x92,		/* 146 */
			0x5b,		/* 91 */
/* 1680 */	0xda,		/* 218 */
			0x5e,		/* 94 */
/* 1682 */	0x11, 0x10,	/* FC_RP [pointer_deref] */
/* 1684 */	NdrFcShort( 0x2 ),	/* Offset= 2 (1686) */
/* 1686 */	
			0x2f,		/* FC_IP */
			0x5a,		/* FC_CONSTANT_IID */
/* 1688 */	NdrFcLong( 0x102f9588 ),	/* 271553928 */
/* 1692 */	NdrFcShort( 0x23e7 ),	/* 9191 */
/* 1694 */	NdrFcShort( 0x40e3 ),	/* 16611 */
/* 1696 */	0x95,		/* 149 */
			0x4d,		/* 77 */
/* 1698 */	0xcd,		/* 205 */
			0x7a,		/* 122 */
/* 1700 */	0x1d,		/* 29 */
			0x5c,		/* 92 */
/* 1702 */	0x3,		/* 3 */
			0x61,		/* 97 */
/* 1704 */	
			0x11, 0x10,	/* FC_RP [pointer_deref] */
/* 1706 */	NdrFcShort( 0x2 ),	/* Offset= 2 (1708) */
/* 1708 */	
			0x2f,		/* FC_IP */
			0x5a,		/* FC_CONSTANT_IID */
/* 1710 */	NdrFcLong( 0x17d7cdfc ),	/* 400018940 */
/* 1714 */	NdrFcShort( 0xb007 ),	/* -20473 */
/* 1716 */	NdrFcShort( 0x484c ),	/* 18508 */
/* 1718 */	0x99,		/* 153 */
			0xd2,		/* 210 */
/* 1720 */	0x86,		/* 134 */
			0xa8,		/* 168 */
/* 1722 */	0xa8,		/* 168 */
			0x20,		/* 32 */
/* 1724 */	0x99,		/* 153 */
			0x1d,		/* 29 */
/* 1726 */	
			0x11, 0x10,	/* FC_RP [pointer_deref] */
/* 1728 */	NdrFcShort( 0x2 ),	/* Offset= 2 (1730) */
/* 1730 */	
			0x2f,		/* FC_IP */
			0x5a,		/* FC_CONSTANT_IID */
/* 1732 */	NdrFcLong( 0xae86add5 ),	/* -1366905387 */
/* 1736 */	NdrFcShort( 0x26b1 ),	/* 9905 */
/* 1738 */	NdrFcShort( 0x4414 ),	/* 17428 */
/* 1740 */	0xaf,		/* 175 */
			0x1d,		/* 29 */
/* 1742 */	0xb9,		/* 185 */
			0x4c,		/* 76 */
/* 1744 */	0xd9,		/* 217 */
			0x38,		/* 56 */
/* 1746 */	0xd7,		/* 215 */
			0x39,		/* 57 */
/* 1748 */	
			0x11, 0x10,	/* FC_RP [pointer_deref] */
/* 1750 */	NdrFcShort( 0x2 ),	/* Offset= 2 (1752) */
/* 1752 */	
			0x2f,		/* FC_IP */
			0x5a,		/* FC_CONSTANT_IID */
/* 1754 */	NdrFcLong( 0x0 ),	/* 0 */
/* 1758 */	NdrFcShort( 0x0 ),	/* 0 */
/* 1760 */	NdrFcShort( 0x0 ),	/* 0 */
/* 1762 */	0xc0,		/* 192 */
			0x0,		/* 0 */
/* 1764 */	0x0,		/* 0 */
			0x0,		/* 0 */
/* 1766 */	0x0,		/* 0 */
			0x0,		/* 0 */
/* 1768 */	0x0,		/* 0 */
			0x46,		/* 70 */
/* 1770 */	
			0x11, 0x0,	/* FC_RP */
/* 1772 */	NdrFcShort( 0x2 ),	/* Offset= 2 (1774) */
/* 1774 */	
			0x21,		/* FC_BOGUS_ARRAY */
			0x3,		/* 3 */
/* 1776 */	NdrFcShort( 0x0 ),	/* 0 */
/* 1778 */	0x29,		/* Corr desc:  parameter, FC_ULONG */
			0x0,		/*  */
/* 1780 */	NdrFcShort( 0x4 ),	/* x86 Stack size/offset = 4 */
/* 1782 */	NdrFcShort( 0x1 ),	/* Corr flags:  early, */
/* 1784 */	NdrFcLong( 0xffffffff ),	/* -1 */
/* 1788 */	NdrFcShort( 0x0 ),	/* Corr flags:  */
/* 1790 */	0x4c,		/* FC_EMBEDDED_COMPLEX */
			0x0,		/* 0 */
/* 1792 */	NdrFcShort( 0xffc2 ),	/* Offset= -62 (1730) */
/* 1794 */	0x5c,		/* FC_PAD */
			0x5b,		/* FC_END */
/* 1796 */	
			0x14, 0x8,	/* FC_FP [simple_pointer] */
/* 1798 */	0x8,		/* FC_LONG */
			0x5c,		/* FC_PAD */
/* 1800 */	
			0x11, 0x10,	/* FC_RP [pointer_deref] */
/* 1802 */	NdrFcShort( 0x2 ),	/* Offset= 2 (1804) */
/* 1804 */	
			0x2f,		/* FC_IP */
			0x5a,		/* FC_CONSTANT_IID */
/* 1806 */	NdrFcLong( 0xfcd56f29 ),	/* -53121239 */
/* 1810 */	NdrFcShort( 0x4a4f ),	/* 19023 */
/* 1812 */	NdrFcShort( 0x41b2 ),	/* 16818 */
/* 1814 */	0xba,		/* 186 */
			0x5c,		/* 92 */
/* 1816 */	0xf5,		/* 245 */
			0xbc,		/* 188 */
/* 1818 */	0xcc,		/* 204 */
			0x6,		/* 6 */
/* 1820 */	0xb,		/* 11 */
			0xf6,		/* 246 */
/* 1822 */	
			0x11, 0x0,	/* FC_RP */
/* 1824 */	NdrFcShort( 0x14 ),	/* Offset= 20 (1844) */
/* 1826 */	
			0x2f,		/* FC_IP */
			0x5a,		/* FC_CONSTANT_IID */
/* 1828 */	NdrFcLong( 0xd07eca9e ),	/* -796996962 */
/* 1832 */	NdrFcShort( 0x4062 ),	/* 16482 */
/* 1834 */	NdrFcShort( 0x4dd4 ),	/* 19924 */
/* 1836 */	0x9e,		/* 158 */
			0x7d,		/* 125 */
/* 1838 */	0x72,		/* 114 */
			0x2a,		/* 42 */
/* 1840 */	0x49,		/* 73 */
			0xba,		/* 186 */
/* 1842 */	0x73,		/* 115 */
			0x3,		/* 3 */
/* 1844 */	
			0x21,		/* FC_BOGUS_ARRAY */
			0x3,		/* 3 */
/* 1846 */	NdrFcShort( 0x0 ),	/* 0 */
/* 1848 */	0x29,		/* Corr desc:  parameter, FC_ULONG */
			0x0,		/*  */
/* 1850 */	NdrFcShort( 0x4 ),	/* x86 Stack size/offset = 4 */
/* 1852 */	NdrFcShort( 0x1 ),	/* Corr flags:  early, */
/* 1854 */	NdrFcLong( 0xffffffff ),	/* -1 */
/* 1858 */	NdrFcShort( 0x0 ),	/* Corr flags:  */
/* 1860 */	0x4c,		/* FC_EMBEDDED_COMPLEX */
			0x0,		/* 0 */
/* 1862 */	NdrFcShort( 0xffdc ),	/* Offset= -36 (1826) */
/* 1864 */	0x5c,		/* FC_PAD */
			0x5b,		/* FC_END */
/* 1866 */	
			0x11, 0x0,	/* FC_RP */
/* 1868 */	NdrFcShort( 0x14 ),	/* Offset= 20 (1888) */
/* 1870 */	
			0x2f,		/* FC_IP */
			0x5a,		/* FC_CONSTANT_IID */
/* 1872 */	NdrFcLong( 0xfcb136c8 ),	/* -55494968 */
/* 1876 */	NdrFcShort( 0x7b90 ),	/* 31632 */
/* 1878 */	NdrFcShort( 0x4e0c ),	/* 19980 */
/* 1880 */	0xbe,		/* 190 */
			0xfe,		/* 254 */
/* 1882 */	0x56,		/* 86 */
			0xed,		/* 237 */
/* 1884 */	0xf0,		/* 240 */
			0xba,		/* 186 */
/* 1886 */	0x6f,		/* 111 */
			0x1c,		/* 28 */
/* 1888 */	
			0x21,		/* FC_BOGUS_ARRAY */
			0x3,		/* 3 */
/* 1890 */	NdrFcShort( 0x0 ),	/* 0 */
/* 1892 */	0x29,		/* Corr desc:  parameter, FC_ULONG */
			0x0,		/*  */
/* 1894 */	NdrFcShort( 0x4 ),	/* x86 Stack size/offset = 4 */
/* 1896 */	NdrFcShort( 0x1 ),	/* Corr flags:  early, */
/* 1898 */	NdrFcLong( 0xffffffff ),	/* -1 */
/* 1902 */	NdrFcShort( 0x0 ),	/* Corr flags:  */
/* 1904 */	0x4c,		/* FC_EMBEDDED_COMPLEX */
			0x0,		/* 0 */
/* 1906 */	NdrFcShort( 0xffdc ),	/* Offset= -36 (1870) */
/* 1908 */	0x5c,		/* FC_PAD */
			0x5b,		/* FC_END */
/* 1910 */	
			0x11, 0x10,	/* FC_RP [pointer_deref] */
/* 1912 */	NdrFcShort( 0x2 ),	/* Offset= 2 (1914) */
/* 1914 */	
			0x2f,		/* FC_IP */
			0x5a,		/* FC_CONSTANT_IID */
/* 1916 */	NdrFcLong( 0xf7296917 ),	/* -148281065 */
/* 1920 */	NdrFcShort( 0x5569 ),	/* 21865 */
/* 1922 */	NdrFcShort( 0x4b3b ),	/* 19259 */
/* 1924 */	0xb3,		/* 179 */
			0xaf,		/* 175 */
/* 1926 */	0x98,		/* 152 */
			0xd1,		/* 209 */
/* 1928 */	0x14,		/* 20 */
			0x4b,		/* 75 */
/* 1930 */	0x2b,		/* 43 */
			0x87,		/* 135 */
/* 1932 */	
			0x11, 0x0,	/* FC_RP */
/* 1934 */	NdrFcShort( 0x14 ),	/* Offset= 20 (1954) */
/* 1936 */	
			0x2f,		/* FC_IP */
			0x5a,		/* FC_CONSTANT_IID */
/* 1938 */	NdrFcLong( 0xc7cedad8 ),	/* -942744872 */
/* 1942 */	NdrFcShort( 0x346b ),	/* 13419 */
/* 1944 */	NdrFcShort( 0x4d1b ),	/* 19739 */
/* 1946 */	0xac,		/* 172 */
			0x2,		/* 2 */
/* 1948 */	0xa2,		/* 162 */
			0x8,		/* 8 */
/* 1950 */	0x8d,		/* 141 */
			0xf9,		/* 249 */
/* 1952 */	0xbe,		/* 190 */
			0x4f,		/* 79 */
/* 1954 */	
			0x21,		/* FC_BOGUS_ARRAY */
			0x3,		/* 3 */
/* 1956 */	NdrFcShort( 0x0 ),	/* 0 */
/* 1958 */	0x29,		/* Corr desc:  parameter, FC_ULONG */
			0x0,		/*  */
/* 1960 */	NdrFcShort( 0x4 ),	/* x86 Stack size/offset = 4 */
/* 1962 */	NdrFcShort( 0x1 ),	/* Corr flags:  early, */
/* 1964 */	NdrFcLong( 0xffffffff ),	/* -1 */
/* 1968 */	NdrFcShort( 0x0 ),	/* Corr flags:  */
/* 1970 */	0x4c,		/* FC_EMBEDDED_COMPLEX */
			0x0,		/* 0 */
/* 1972 */	NdrFcShort( 0xffdc ),	/* Offset= -36 (1936) */
/* 1974 */	0x5c,		/* FC_PAD */
			0x5b,		/* FC_END */
/* 1976 */	
			0x11, 0x10,	/* FC_RP [pointer_deref] */
/* 1978 */	NdrFcShort( 0x2 ),	/* Offset= 2 (1980) */
/* 1980 */	
			0x2f,		/* FC_IP */
			0x5a,		/* FC_CONSTANT_IID */
/* 1982 */	NdrFcLong( 0xa87d55d7 ),	/* -1468181033 */
/* 1986 */	NdrFcShort( 0xdb74 ),	/* -9356 */
/* 1988 */	NdrFcShort( 0x4ed1 ),	/* 20177 */
/* 1990 */	0x9c,		/* 156 */
			0xa4,		/* 164 */
/* 1992 */	0x77,		/* 119 */
			0xa0,		/* 160 */
/* 1994 */	0xe4,		/* 228 */
			0x1b,		/* 27 */
/* 1996 */	0x41,		/* 65 */
			0x3e,		/* 62 */
/* 1998 */	
			0x11, 0x0,	/* FC_RP */
/* 2000 */	NdrFcShort( 0x14 ),	/* Offset= 20 (2020) */
/* 2002 */	
			0x2f,		/* FC_IP */
			0x5a,		/* FC_CONSTANT_IID */
/* 2004 */	NdrFcLong( 0x60361e68 ),	/* 1614159464 */
/* 2008 */	NdrFcShort( 0x9164 ),	/* -28316 */
/* 2010 */	NdrFcShort( 0x4389 ),	/* 17289 */
/* 2012 */	0xa4,		/* 164 */
			0xc6,		/* 198 */
/* 2014 */	0xd0,		/* 208 */
			0xb3,		/* 179 */
/* 2016 */	0x92,		/* 146 */
			0x5b,		/* 91 */
/* 2018 */	0xda,		/* 218 */
			0x5e,		/* 94 */
/* 2020 */	
			0x21,		/* FC_BOGUS_ARRAY */
			0x3,		/* 3 */
/* 2022 */	NdrFcShort( 0x0 ),	/* 0 */
/* 2024 */	0x29,		/* Corr desc:  parameter, FC_ULONG */
			0x0,		/*  */
/* 2026 */	NdrFcShort( 0x4 ),	/* x86 Stack size/offset = 4 */
/* 2028 */	NdrFcShort( 0x1 ),	/* Corr flags:  early, */
/* 2030 */	NdrFcLong( 0xffffffff ),	/* -1 */
/* 2034 */	NdrFcShort( 0x0 ),	/* Corr flags:  */
/* 2036 */	0x4c,		/* FC_EMBEDDED_COMPLEX */
			0x0,		/* 0 */
/* 2038 */	NdrFcShort( 0xffdc ),	/* Offset= -36 (2002) */
/* 2040 */	0x5c,		/* FC_PAD */
			0x5b,		/* FC_END */
/* 2042 */	
			0x11, 0x10,	/* FC_RP [pointer_deref] */
/* 2044 */	NdrFcShort( 0x2 ),	/* Offset= 2 (2046) */
/* 2046 */	
			0x2f,		/* FC_IP */
			0x5a,		/* FC_CONSTANT_IID */
/* 2048 */	NdrFcLong( 0x742378d6 ),	/* 1948481750 */
/* 2052 */	NdrFcShort( 0xa141 ),	/* -24255 */
/* 2054 */	NdrFcShort( 0x4415 ),	/* 17429 */
/* 2056 */	0x8f,		/* 143 */
			0x27,		/* 39 */
/* 2058 */	0x35,		/* 53 */
			0xd9,		/* 217 */
/* 2060 */	0x90,		/* 144 */
			0x76,		/* 118 */
/* 2062 */	0xcf,		/* 207 */
			0x5d,		/* 93 */
/* 2064 */	
			0x11, 0x10,	/* FC_RP [pointer_deref] */
/* 2066 */	NdrFcShort( 0x2 ),	/* Offset= 2 (2068) */
/* 2068 */	
			0x2f,		/* FC_IP */
			0x5a,		/* FC_CONSTANT_IID */
/* 2070 */	NdrFcLong( 0x4b81f84e ),	/* 1266808910 */
/* 2074 */	NdrFcShort( 0xbdc7 ),	/* -16953 */
/* 2076 */	NdrFcShort( 0x4184 ),	/* 16772 */
/* 2078 */	0x91,		/* 145 */
			0x54,		/* 84 */
/* 2080 */	0x3c,		/* 60 */
			0xb2,		/* 178 */
/* 2082 */	0xdd,		/* 221 */
			0x79,		/* 121 */
/* 2084 */	0x17,		/* 23 */
			0xfb,		/* 251 */
/* 2086 */	
			0x11, 0x10,	/* FC_RP [pointer_deref] */
/* 2088 */	NdrFcShort( 0x2 ),	/* Offset= 2 (2090) */
/* 2090 */	
			0x2f,		/* FC_IP */
			0x5a,		/* FC_CONSTANT_IID */
/* 2092 */	NdrFcLong( 0xec7c8096 ),	/* -327384938 */
/* 2096 */	NdrFcShort( 0xb918 ),	/* -18152 */
/* 2098 */	NdrFcShort( 0x4044 ),	/* 16452 */
/* 2100 */	0x94,		/* 148 */
			0xf1,		/* 241 */
/* 2102 */	0xe4,		/* 228 */
			0xfb,		/* 251 */
/* 2104 */	0xa0,		/* 160 */
			0x36,		/* 54 */
/* 2106 */	0x1d,		/* 29 */
			0x5c,		/* 92 */
/* 2108 */	
			0x11, 0x10,	/* FC_RP [pointer_deref] */
/* 2110 */	NdrFcShort( 0x2 ),	/* Offset= 2 (2112) */
/* 2112 */	
			0x2f,		/* FC_IP */
			0x5a,		/* FC_CONSTANT_IID */
/* 2114 */	NdrFcLong( 0x708c2ab7 ),	/* 1888234167 */
/* 2118 */	NdrFcShort( 0x8bf8 ),	/* -29704 */
/* 2120 */	NdrFcShort( 0x42f8 ),	/* 17144 */
/* 2122 */	0x8c,		/* 140 */
			0x7d,		/* 125 */
/* 2124 */	0x63,		/* 99 */
			0x51,		/* 81 */
/* 2126 */	0x97,		/* 151 */
			0xad,		/* 173 */
/* 2128 */	0x55,		/* 85 */
			0x39,		/* 57 */
/* 2130 */	
			0x11, 0x10,	/* FC_RP [pointer_deref] */
/* 2132 */	NdrFcShort( 0x2 ),	/* Offset= 2 (2134) */
/* 2134 */	
			0x2f,		/* FC_IP */
			0x5a,		/* FC_CONSTANT_IID */
/* 2136 */	NdrFcLong( 0xec7c8096 ),	/* -327384938 */
/* 2140 */	NdrFcShort( 0xb918 ),	/* -18152 */
/* 2142 */	NdrFcShort( 0x4044 ),	/* 16452 */
/* 2144 */	0x94,		/* 148 */
			0xf1,		/* 241 */
/* 2146 */	0xe4,		/* 228 */
			0xfb,		/* 251 */
/* 2148 */	0xa0,		/* 160 */
			0x36,		/* 54 */
/* 2150 */	0x1d,		/* 29 */
			0x5c,		/* 92 */
/* 2152 */	
			0x2f,		/* FC_IP */
			0x5a,		/* FC_CONSTANT_IID */
/* 2154 */	NdrFcLong( 0xfcb136c8 ),	/* -55494968 */
/* 2158 */	NdrFcShort( 0x7b90 ),	/* 31632 */
/* 2160 */	NdrFcShort( 0x4e0c ),	/* 19980 */
/* 2162 */	0xbe,		/* 190 */
			0xfe,		/* 254 */
/* 2164 */	0x56,		/* 86 */
			0xed,		/* 237 */
/* 2166 */	0xf0,		/* 240 */
			0xba,		/* 186 */
/* 2168 */	0x6f,		/* 111 */
			0x1c,		/* 28 */
/* 2170 */	
			0x11, 0x10,	/* FC_RP [pointer_deref] */
/* 2172 */	NdrFcShort( 0x2 ),	/* Offset= 2 (2174) */
/* 2174 */	
			0x2f,		/* FC_IP */
			0x5a,		/* FC_CONSTANT_IID */
/* 2176 */	NdrFcLong( 0xf7296917 ),	/* -148281065 */
/* 2180 */	NdrFcShort( 0x5569 ),	/* 21865 */
/* 2182 */	NdrFcShort( 0x4b3b ),	/* 19259 */
/* 2184 */	0xb3,		/* 179 */
			0xaf,		/* 175 */
/* 2186 */	0x98,		/* 152 */
			0xd1,		/* 209 */
/* 2188 */	0x14,		/* 20 */
			0x4b,		/* 75 */
/* 2190 */	0x2b,		/* 43 */
			0x87,		/* 135 */
/* 2192 */	
			0x2f,		/* FC_IP */
			0x5a,		/* FC_CONSTANT_IID */
/* 2194 */	NdrFcLong( 0x20400 ),	/* 132096 */
/* 2198 */	NdrFcShort( 0x0 ),	/* 0 */
/* 2200 */	NdrFcShort( 0x0 ),	/* 0 */
/* 2202 */	0xc0,		/* 192 */
			0x0,		/* 0 */
/* 2204 */	0x0,		/* 0 */
			0x0,		/* 0 */
/* 2206 */	0x0,		/* 0 */
			0x0,		/* 0 */
/* 2208 */	0x0,		/* 0 */
			0x46,		/* 70 */
/* 2210 */	
			0x11, 0x0,	/* FC_RP */
/* 2212 */	NdrFcShort( 0xfbc6 ),	/* Offset= -1082 (1130) */
/* 2214 */	
			0x11, 0x8,	/* FC_RP [simple_pointer] */
/* 2216 */	0x8,		/* FC_LONG */
			0x5c,		/* FC_PAD */
/* 2218 */	
			0x2f,		/* FC_IP */
			0x5a,		/* FC_CONSTANT_IID */
/* 2220 */	NdrFcLong( 0xda77c14b ),	/* -629685941 */
/* 2224 */	NdrFcShort( 0x6208 ),	/* 25096 */
/* 2226 */	NdrFcShort( 0x43ca ),	/* 17354 */
/* 2228 */	0x8d,		/* 141 */
			0xdf,		/* 223 */
/* 2230 */	0x5b,		/* 91 */
			0x60,		/* 96 */
/* 2232 */	0xa0,		/* 160 */
			0xa6,		/* 166 */
/* 2234 */	0x9f,		/* 159 */
			0xac,		/* 172 */
/* 2236 */	
			0x11, 0x10,	/* FC_RP [pointer_deref] */
/* 2238 */	NdrFcShort( 0x2 ),	/* Offset= 2 (2240) */
/* 2240 */	
			0x2f,		/* FC_IP */
			0x5a,		/* FC_CONSTANT_IID */
/* 2242 */	NdrFcLong( 0x288300f5 ),	/* 679674101 */
/* 2246 */	NdrFcShort( 0xd23a ),	/* -11718 */
/* 2248 */	NdrFcShort( 0x4365 ),	/* 17253 */
/* 2250 */	0x9a,		/* 154 */
			0x73,		/* 115 */
/* 2252 */	0x99,		/* 153 */
			0x85,		/* 133 */
/* 2254 */	0xc9,		/* 201 */
			0x8c,		/* 140 */
/* 2256 */	0x28,		/* 40 */
			0x81,		/* 129 */
/* 2258 */	
			0x2f,		/* FC_IP */
			0x5a,		/* FC_CONSTANT_IID */
/* 2260 */	NdrFcLong( 0xd07eca9e ),	/* -796996962 */
/* 2264 */	NdrFcShort( 0x4062 ),	/* 16482 */
/* 2266 */	NdrFcShort( 0x4dd4 ),	/* 19924 */
/* 2268 */	0x9e,		/* 158 */
			0x7d,		/* 125 */
/* 2270 */	0x72,		/* 114 */
			0x2a,		/* 42 */
/* 2272 */	0x49,		/* 73 */
			0xba,		/* 186 */
/* 2274 */	0x73,		/* 115 */
			0x3,		/* 3 */
/* 2276 */	
			0x11, 0x0,	/* FC_RP */
/* 2278 */	NdrFcShort( 0x14 ),	/* Offset= 20 (2298) */
/* 2280 */	
			0x2f,		/* FC_IP */
			0x5a,		/* FC_CONSTANT_IID */
/* 2282 */	NdrFcLong( 0x851278b2 ),	/* -2062387022 */
/* 2286 */	NdrFcShort( 0x9592 ),	/* -27246 */
/* 2288 */	NdrFcShort( 0x480f ),	/* 18447 */
/* 2290 */	0x8d,		/* 141 */
			0xb5,		/* 181 */
/* 2292 */	0x2d,		/* 45 */
			0xe8,		/* 232 */
/* 2294 */	0x6b,		/* 107 */
			0x26,		/* 38 */
/* 2296 */	0xb5,		/* 181 */
			0x4d,		/* 77 */
/* 2298 */	
			0x21,		/* FC_BOGUS_ARRAY */
			0x3,		/* 3 */
/* 2300 */	NdrFcShort( 0x0 ),	/* 0 */
/* 2302 */	0x29,		/* Corr desc:  parameter, FC_ULONG */
			0x0,		/*  */
/* 2304 */	NdrFcShort( 0x4 ),	/* x86 Stack size/offset = 4 */
/* 2306 */	NdrFcShort( 0x1 ),	/* Corr flags:  early, */
/* 2308 */	NdrFcLong( 0xffffffff ),	/* -1 */
/* 2312 */	NdrFcShort( 0x0 ),	/* Corr flags:  */
/* 2314 */	0x4c,		/* FC_EMBEDDED_COMPLEX */
			0x0,		/* 0 */
/* 2316 */	NdrFcShort( 0xffdc ),	/* Offset= -36 (2280) */
/* 2318 */	0x5c,		/* FC_PAD */
			0x5b,		/* FC_END */
/* 2320 */	
			0x11, 0x10,	/* FC_RP [pointer_deref] */
/* 2322 */	NdrFcShort( 0x2 ),	/* Offset= 2 (2324) */
/* 2324 */	
			0x2f,		/* FC_IP */
			0x5a,		/* FC_CONSTANT_IID */
/* 2326 */	NdrFcLong( 0x83d4d877 ),	/* -2083202953 */
/* 2330 */	NdrFcShort( 0xaa5d ),	/* -21923 */
/* 2332 */	NdrFcShort( 0x4a5b ),	/* 19035 */
/* 2334 */	0x8d,		/* 141 */
			0xe,		/* 14 */
/* 2336 */	0x0,		/* 0 */
			0x2a,		/* 42 */
/* 2338 */	0x80,		/* 128 */
			0x67,		/* 103 */
/* 2340 */	0xe0,		/* 224 */
			0xe8,		/* 232 */
/* 2342 */	
			0x11, 0x10,	/* FC_RP [pointer_deref] */
/* 2344 */	NdrFcShort( 0x2 ),	/* Offset= 2 (2346) */
/* 2346 */	
			0x2f,		/* FC_IP */
			0x5a,		/* FC_CONSTANT_IID */
/* 2348 */	NdrFcLong( 0x17d7cdfc ),	/* 400018940 */
/* 2352 */	NdrFcShort( 0xb007 ),	/* -20473 */
/* 2354 */	NdrFcShort( 0x484c ),	/* 18508 */
/* 2356 */	0x99,		/* 153 */
			0xd2,		/* 210 */
/* 2358 */	0x86,		/* 134 */
			0xa8,		/* 168 */
/* 2360 */	0xa8,		/* 168 */
			0x20,		/* 32 */
/* 2362 */	0x99,		/* 153 */
			0x1d,		/* 29 */
/* 2364 */	
			0x11, 0x8,	/* FC_RP [simple_pointer] */
/* 2366 */	0x6,		/* FC_SHORT */
			0x5c,		/* FC_PAD */
/* 2368 */	
			0x11, 0x0,	/* FC_RP */
/* 2370 */	NdrFcShort( 0x14 ),	/* Offset= 20 (2390) */
/* 2372 */	
			0x2f,		/* FC_IP */
			0x5a,		/* FC_CONSTANT_IID */
/* 2374 */	NdrFcLong( 0xbc6a90dd ),	/* -1133866787 */
/* 2378 */	NdrFcShort( 0xad9a ),	/* -21094 */
/* 2380 */	NdrFcShort( 0x48da ),	/* 18650 */
/* 2382 */	0x9b,		/* 155 */
			0xc,		/* 12 */
/* 2384 */	0x25,		/* 37 */
			0x15,		/* 21 */
/* 2386 */	0xe3,		/* 227 */
			0x85,		/* 133 */
/* 2388 */	0x21,		/* 33 */
			0xad,		/* 173 */
/* 2390 */	
			0x21,		/* FC_BOGUS_ARRAY */
			0x3,		/* 3 */
/* 2392 */	NdrFcShort( 0x0 ),	/* 0 */
/* 2394 */	0x29,		/* Corr desc:  parameter, FC_ULONG */
			0x0,		/*  */
/* 2396 */	NdrFcShort( 0x4 ),	/* x86 Stack size/offset = 4 */
/* 2398 */	NdrFcShort( 0x1 ),	/* Corr flags:  early, */
/* 2400 */	NdrFcLong( 0xffffffff ),	/* -1 */
/* 2404 */	NdrFcShort( 0x0 ),	/* Corr flags:  */
/* 2406 */	0x4c,		/* FC_EMBEDDED_COMPLEX */
			0x0,		/* 0 */
/* 2408 */	NdrFcShort( 0xffdc ),	/* Offset= -36 (2372) */
/* 2410 */	0x5c,		/* FC_PAD */
			0x5b,		/* FC_END */
/* 2412 */	
			0x11, 0x10,	/* FC_RP [pointer_deref] */
/* 2414 */	NdrFcShort( 0x2 ),	/* Offset= 2 (2416) */
/* 2416 */	
			0x2f,		/* FC_IP */
			0x5a,		/* FC_CONSTANT_IID */
/* 2418 */	NdrFcLong( 0x708c2ab7 ),	/* 1888234167 */
/* 2422 */	NdrFcShort( 0x8bf8 ),	/* -29704 */
/* 2424 */	NdrFcShort( 0x42f8 ),	/* 17144 */
/* 2426 */	0x8c,		/* 140 */
			0x7d,		/* 125 */
/* 2428 */	0x63,		/* 99 */
			0x51,		/* 81 */
/* 2430 */	0x97,		/* 151 */
			0xad,		/* 173 */
/* 2432 */	0x55,		/* 85 */
			0x39,		/* 57 */

			0x0
        }
    };

static const USER_MARSHAL_ROUTINE_QUADRUPLE UserMarshalRoutines[ WIRE_MARSHAL_TABLE_SIZE ] = 
        {
            
            {
            BSTR_UserSize
            ,BSTR_UserMarshal
            ,BSTR_UserUnmarshal
            ,BSTR_UserFree
            },
            {
            VARIANT_UserSize
            ,VARIANT_UserMarshal
            ,VARIANT_UserUnmarshal
            ,VARIANT_UserFree
            }

        };



/* Standard interface: __MIDL_itf_rtccore_0000, ver. 0.0,
   GUID={0x00000000,0x0000,0x0000,{0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00}} */


/* Object interface: IUnknown, ver. 0.0,
   GUID={0x00000000,0x0000,0x0000,{0xC0,0x00,0x00,0x00,0x00,0x00,0x00,0x46}} */


/* Object interface: IRTCClient, ver. 0.0,
   GUID={0x07829e45,0x9a34,0x408e,{0xa0,0x11,0xbd,0xdf,0x13,0x48,0x7c,0xd1}} */

#pragma code_seg(".orpc")
static const unsigned short IRTCClient_FormatStringOffsetTable[] =
    {
    0,
    30,
    60,
    90,
    126,
    162,
    204,
    240,
    276,
    336,
    372,
    408,
    456,
    498,
    540,
    582,
    624,
    666,
    708,
    750,
    792,
    834,
    870,
    906,
    942,
    978,
    1014,
    1050,
    1086,
    1122,
    1158,
    1194,
    1230,
    1260,
    1302,
    1338,
    1374,
    1410,
    1446,
    1488,
    1524,
    1560
    };

static const MIDL_STUBLESS_PROXY_INFO IRTCClient_ProxyInfo =
    {
    &Object_StubDesc,
    __MIDL_ProcFormatString.Format,
    &IRTCClient_FormatStringOffsetTable[-3],
    0,
    0,
    0
    };


static const MIDL_SERVER_INFO IRTCClient_ServerInfo = 
    {
    &Object_StubDesc,
    0,
    __MIDL_ProcFormatString.Format,
    &IRTCClient_FormatStringOffsetTable[-3],
    0,
    0,
    0,
    0};
CINTERFACE_PROXY_VTABLE(45) _IRTCClientProxyVtbl = 
{
    &IRTCClient_ProxyInfo,
    &IID_IRTCClient,
    IUnknown_QueryInterface_Proxy,
    IUnknown_AddRef_Proxy,
    IUnknown_Release_Proxy ,
    (void *) (INT_PTR) -1 /* IRTCClient::Initialize */ ,
    (void *) (INT_PTR) -1 /* IRTCClient::Shutdown */ ,
    (void *) (INT_PTR) -1 /* IRTCClient::PrepareForShutdown */ ,
    (void *) (INT_PTR) -1 /* IRTCClient::put_EventFilter */ ,
    (void *) (INT_PTR) -1 /* IRTCClient::get_EventFilter */ ,
    (void *) (INT_PTR) -1 /* IRTCClient::SetPreferredMediaTypes */ ,
    (void *) (INT_PTR) -1 /* IRTCClient::get_PreferredMediaTypes */ ,
    (void *) (INT_PTR) -1 /* IRTCClient::get_MediaCapabilities */ ,
    (void *) (INT_PTR) -1 /* IRTCClient::CreateSession */ ,
    (void *) (INT_PTR) -1 /* IRTCClient::put_ListenForIncomingSessions */ ,
    (void *) (INT_PTR) -1 /* IRTCClient::get_ListenForIncomingSessions */ ,
    (void *) (INT_PTR) -1 /* IRTCClient::get_NetworkAddresses */ ,
    (void *) (INT_PTR) -1 /* IRTCClient::put_Volume */ ,
    (void *) (INT_PTR) -1 /* IRTCClient::get_Volume */ ,
    (void *) (INT_PTR) -1 /* IRTCClient::put_AudioMuted */ ,
    (void *) (INT_PTR) -1 /* IRTCClient::get_AudioMuted */ ,
    (void *) (INT_PTR) -1 /* IRTCClient::get_IVideoWindow */ ,
    (void *) (INT_PTR) -1 /* IRTCClient::put_PreferredAudioDevice */ ,
    (void *) (INT_PTR) -1 /* IRTCClient::get_PreferredAudioDevice */ ,
    (void *) (INT_PTR) -1 /* IRTCClient::put_PreferredVolume */ ,
    (void *) (INT_PTR) -1 /* IRTCClient::get_PreferredVolume */ ,
    (void *) (INT_PTR) -1 /* IRTCClient::put_PreferredAEC */ ,
    (void *) (INT_PTR) -1 /* IRTCClient::get_PreferredAEC */ ,
    (void *) (INT_PTR) -1 /* IRTCClient::put_PreferredVideoDevice */ ,
    (void *) (INT_PTR) -1 /* IRTCClient::get_PreferredVideoDevice */ ,
    (void *) (INT_PTR) -1 /* IRTCClient::get_ActiveMedia */ ,
    (void *) (INT_PTR) -1 /* IRTCClient::put_MaxBitrate */ ,
    (void *) (INT_PTR) -1 /* IRTCClient::get_MaxBitrate */ ,
    (void *) (INT_PTR) -1 /* IRTCClient::put_TemporalSpatialTradeOff */ ,
    (void *) (INT_PTR) -1 /* IRTCClient::get_TemporalSpatialTradeOff */ ,
    (void *) (INT_PTR) -1 /* IRTCClient::get_NetworkQuality */ ,
    (void *) (INT_PTR) -1 /* IRTCClient::StartT120Applet */ ,
    (void *) (INT_PTR) -1 /* IRTCClient::StopT120Applets */ ,
    (void *) (INT_PTR) -1 /* IRTCClient::get_IsT120AppletRunning */ ,
    (void *) (INT_PTR) -1 /* IRTCClient::get_LocalUserURI */ ,
    (void *) (INT_PTR) -1 /* IRTCClient::put_LocalUserURI */ ,
    (void *) (INT_PTR) -1 /* IRTCClient::get_LocalUserName */ ,
    (void *) (INT_PTR) -1 /* IRTCClient::put_LocalUserName */ ,
    (void *) (INT_PTR) -1 /* IRTCClient::PlayRing */ ,
    (void *) (INT_PTR) -1 /* IRTCClient::SendDTMF */ ,
    (void *) (INT_PTR) -1 /* IRTCClient::InvokeTuningWizard */ ,
    (void *) (INT_PTR) -1 /* IRTCClient::get_IsTuned */
};

const CInterfaceStubVtbl _IRTCClientStubVtbl =
{
    &IID_IRTCClient,
    &IRTCClient_ServerInfo,
    45,
    0, /* pure interpreted */
    CStdStubBuffer_METHODS
};


/* Object interface: IRTCClient2, ver. 0.0,
   GUID={0x0C91D71D,0x1064,0x42da,{0xBF,0xA5,0x57,0x2B,0xEB,0x8E,0xEA,0x84}} */

#pragma code_seg(".orpc")
static const unsigned short IRTCClient2_FormatStringOffsetTable[] =
    {
    0,
    30,
    60,
    90,
    126,
    162,
    204,
    240,
    276,
    336,
    372,
    408,
    456,
    498,
    540,
    582,
    624,
    666,
    708,
    750,
    792,
    834,
    870,
    906,
    942,
    978,
    1014,
    1050,
    1086,
    1122,
    1158,
    1194,
    1230,
    1260,
    1302,
    1338,
    1374,
    1410,
    1446,
    1488,
    1524,
    1560,
    1596,
    1638,
    1680,
    1728,
    1764,
    1800,
    1836,
    1872,
    1932,
    1968,
    2010,
    2052,
    2094
    };

static const MIDL_STUBLESS_PROXY_INFO IRTCClient2_ProxyInfo =
    {
    &Object_StubDesc,
    __MIDL_ProcFormatString.Format,
    &IRTCClient2_FormatStringOffsetTable[-3],
    0,
    0,
    0
    };


static const MIDL_SERVER_INFO IRTCClient2_ServerInfo = 
    {
    &Object_StubDesc,
    0,
    __MIDL_ProcFormatString.Format,
    &IRTCClient2_FormatStringOffsetTable[-3],
    0,
    0,
    0,
    0};
CINTERFACE_PROXY_VTABLE(58) _IRTCClient2ProxyVtbl = 
{
    &IRTCClient2_ProxyInfo,
    &IID_IRTCClient2,
    IUnknown_QueryInterface_Proxy,
    IUnknown_AddRef_Proxy,
    IUnknown_Release_Proxy ,
    (void *) (INT_PTR) -1 /* IRTCClient::Initialize */ ,
    (void *) (INT_PTR) -1 /* IRTCClient::Shutdown */ ,
    (void *) (INT_PTR) -1 /* IRTCClient::PrepareForShutdown */ ,
    (void *) (INT_PTR) -1 /* IRTCClient::put_EventFilter */ ,
    (void *) (INT_PTR) -1 /* IRTCClient::get_EventFilter */ ,
    (void *) (INT_PTR) -1 /* IRTCClient::SetPreferredMediaTypes */ ,
    (void *) (INT_PTR) -1 /* IRTCClient::get_PreferredMediaTypes */ ,
    (void *) (INT_PTR) -1 /* IRTCClient::get_MediaCapabilities */ ,
    (void *) (INT_PTR) -1 /* IRTCClient::CreateSession */ ,
    (void *) (INT_PTR) -1 /* IRTCClient::put_ListenForIncomingSessions */ ,
    (void *) (INT_PTR) -1 /* IRTCClient::get_ListenForIncomingSessions */ ,
    (void *) (INT_PTR) -1 /* IRTCClient::get_NetworkAddresses */ ,
    (void *) (INT_PTR) -1 /* IRTCClient::put_Volume */ ,
    (void *) (INT_PTR) -1 /* IRTCClient::get_Volume */ ,
    (void *) (INT_PTR) -1 /* IRTCClient::put_AudioMuted */ ,
    (void *) (INT_PTR) -1 /* IRTCClient::get_AudioMuted */ ,
    (void *) (INT_PTR) -1 /* IRTCClient::get_IVideoWindow */ ,
    (void *) (INT_PTR) -1 /* IRTCClient::put_PreferredAudioDevice */ ,
    (void *) (INT_PTR) -1 /* IRTCClient::get_PreferredAudioDevice */ ,
    (void *) (INT_PTR) -1 /* IRTCClient::put_PreferredVolume */ ,
    (void *) (INT_PTR) -1 /* IRTCClient::get_PreferredVolume */ ,
    (void *) (INT_PTR) -1 /* IRTCClient::put_PreferredAEC */ ,
    (void *) (INT_PTR) -1 /* IRTCClient::get_PreferredAEC */ ,
    (void *) (INT_PTR) -1 /* IRTCClient::put_PreferredVideoDevice */ ,
    (void *) (INT_PTR) -1 /* IRTCClient::get_PreferredVideoDevice */ ,
    (void *) (INT_PTR) -1 /* IRTCClient::get_ActiveMedia */ ,
    (void *) (INT_PTR) -1 /* IRTCClient::put_MaxBitrate */ ,
    (void *) (INT_PTR) -1 /* IRTCClient::get_MaxBitrate */ ,
    (void *) (INT_PTR) -1 /* IRTCClient::put_TemporalSpatialTradeOff */ ,
    (void *) (INT_PTR) -1 /* IRTCClient::get_TemporalSpatialTradeOff */ ,
    (void *) (INT_PTR) -1 /* IRTCClient::get_NetworkQuality */ ,
    (void *) (INT_PTR) -1 /* IRTCClient::StartT120Applet */ ,
    (void *) (INT_PTR) -1 /* IRTCClient::StopT120Applets */ ,
    (void *) (INT_PTR) -1 /* IRTCClient::get_IsT120AppletRunning */ ,
    (void *) (INT_PTR) -1 /* IRTCClient::get_LocalUserURI */ ,
    (void *) (INT_PTR) -1 /* IRTCClient::put_LocalUserURI */ ,
    (void *) (INT_PTR) -1 /* IRTCClient::get_LocalUserName */ ,
    (void *) (INT_PTR) -1 /* IRTCClient::put_LocalUserName */ ,
    (void *) (INT_PTR) -1 /* IRTCClient::PlayRing */ ,
    (void *) (INT_PTR) -1 /* IRTCClient::SendDTMF */ ,
    (void *) (INT_PTR) -1 /* IRTCClient::InvokeTuningWizard */ ,
    (void *) (INT_PTR) -1 /* IRTCClient::get_IsTuned */ ,
    (void *) (INT_PTR) -1 /* IRTCClient2::put_AnswerMode */ ,
    (void *) (INT_PTR) -1 /* IRTCClient2::get_AnswerMode */ ,
    (void *) (INT_PTR) -1 /* IRTCClient2::InvokeTuningWizardEx */ ,
    (void *) (INT_PTR) -1 /* IRTCClient2::get_Version */ ,
    (void *) (INT_PTR) -1 /* IRTCClient2::put_ClientName */ ,
    (void *) (INT_PTR) -1 /* IRTCClient2::put_ClientCurVer */ ,
    (void *) (INT_PTR) -1 /* IRTCClient2::InitializeEx */ ,
    (void *) (INT_PTR) -1 /* IRTCClient2::CreateSessionWithDescription */ ,
    (void *) (INT_PTR) -1 /* IRTCClient2::SetSessionDescriptionManager */ ,
    (void *) (INT_PTR) -1 /* IRTCClient2::put_PreferredSecurityLevel */ ,
    (void *) (INT_PTR) -1 /* IRTCClient2::get_PreferredSecurityLevel */ ,
    (void *) (INT_PTR) -1 /* IRTCClient2::put_AllowedPorts */ ,
    (void *) (INT_PTR) -1 /* IRTCClient2::get_AllowedPorts */
};

const CInterfaceStubVtbl _IRTCClient2StubVtbl =
{
    &IID_IRTCClient2,
    &IRTCClient2_ServerInfo,
    58,
    0, /* pure interpreted */
    CStdStubBuffer_METHODS
};


/* Object interface: IRTCClientPresence, ver. 0.0,
   GUID={0x11c3cbcc,0x0744,0x42d1,{0x96,0x8a,0x51,0xaa,0x1b,0xb2,0x74,0xc6}} */

#pragma code_seg(".orpc")
static const unsigned short IRTCClientPresence_FormatStringOffsetTable[] =
    {
    2136,
    2178,
    2214,
    2256,
    2292,
    2328,
    2370,
    2442,
    2478,
    2514,
    2550,
    2592,
    2658,
    2694,
    2736,
    2772,
    2808,
    2844
    };

static const MIDL_STUBLESS_PROXY_INFO IRTCClientPresence_ProxyInfo =
    {
    &Object_StubDesc,
    __MIDL_ProcFormatString.Format,
    &IRTCClientPresence_FormatStringOffsetTable[-3],
    0,
    0,
    0
    };


static const MIDL_SERVER_INFO IRTCClientPresence_ServerInfo = 
    {
    &Object_StubDesc,
    0,
    __MIDL_ProcFormatString.Format,
    &IRTCClientPresence_FormatStringOffsetTable[-3],
    0,
    0,
    0,
    0};
CINTERFACE_PROXY_VTABLE(21) _IRTCClientPresenceProxyVtbl = 
{
    &IRTCClientPresence_ProxyInfo,
    &IID_IRTCClientPresence,
    IUnknown_QueryInterface_Proxy,
    IUnknown_AddRef_Proxy,
    IUnknown_Release_Proxy ,
    (void *) (INT_PTR) -1 /* IRTCClientPresence::EnablePresence */ ,
    (void *) (INT_PTR) -1 /* IRTCClientPresence::Export */ ,
    (void *) (INT_PTR) -1 /* IRTCClientPresence::Import */ ,
    (void *) (INT_PTR) -1 /* IRTCClientPresence::EnumerateBuddies */ ,
    (void *) (INT_PTR) -1 /* IRTCClientPresence::get_Buddies */ ,
    (void *) (INT_PTR) -1 /* IRTCClientPresence::get_Buddy */ ,
    (void *) (INT_PTR) -1 /* IRTCClientPresence::AddBuddy */ ,
    (void *) (INT_PTR) -1 /* IRTCClientPresence::RemoveBuddy */ ,
    (void *) (INT_PTR) -1 /* IRTCClientPresence::EnumerateWatchers */ ,
    (void *) (INT_PTR) -1 /* IRTCClientPresence::get_Watchers */ ,
    (void *) (INT_PTR) -1 /* IRTCClientPresence::get_Watcher */ ,
    (void *) (INT_PTR) -1 /* IRTCClientPresence::AddWatcher */ ,
    (void *) (INT_PTR) -1 /* IRTCClientPresence::RemoveWatcher */ ,
    (void *) (INT_PTR) -1 /* IRTCClientPresence::SetLocalPresenceInfo */ ,
    (void *) (INT_PTR) -1 /* IRTCClientPresence::get_OfferWatcherMode */ ,
    (void *) (INT_PTR) -1 /* IRTCClientPresence::put_OfferWatcherMode */ ,
    (void *) (INT_PTR) -1 /* IRTCClientPresence::get_PrivacyMode */ ,
    (void *) (INT_PTR) -1 /* IRTCClientPresence::put_PrivacyMode */
};

const CInterfaceStubVtbl _IRTCClientPresenceStubVtbl =
{
    &IID_IRTCClientPresence,
    &IRTCClientPresence_ServerInfo,
    21,
    0, /* pure interpreted */
    CStdStubBuffer_METHODS
};


/* Object interface: IRTCClientPresence2, ver. 0.0,
   GUID={0xAD1809E8,0x62F7,0x4783,{0x90,0x9A,0x29,0xC9,0xD2,0xCB,0x1D,0x34}} */

#pragma code_seg(".orpc")
static const unsigned short IRTCClientPresence2_FormatStringOffsetTable[] =
    {
    2136,
    2178,
    2214,
    2256,
    2292,
    2328,
    2370,
    2442,
    2478,
    2514,
    2550,
    2592,
    2658,
    2694,
    2736,
    2772,
    2808,
    2844,
    2880,
    2928,
    2958,
    3018,
    3054,
    3090,
    3126,
    3168,
    3252,
    3300,
    3342,
    3384,
    3426,
    3468,
    3510
    };

static const MIDL_STUBLESS_PROXY_INFO IRTCClientPresence2_ProxyInfo =
    {
    &Object_StubDesc,
    __MIDL_ProcFormatString.Format,
    &IRTCClientPresence2_FormatStringOffsetTable[-3],
    0,
    0,
    0
    };


static const MIDL_SERVER_INFO IRTCClientPresence2_ServerInfo = 
    {
    &Object_StubDesc,
    0,
    __MIDL_ProcFormatString.Format,
    &IRTCClientPresence2_FormatStringOffsetTable[-3],
    0,
    0,
    0,
    0};
CINTERFACE_PROXY_VTABLE(36) _IRTCClientPresence2ProxyVtbl = 
{
    &IRTCClientPresence2_ProxyInfo,
    &IID_IRTCClientPresence2,
    IUnknown_QueryInterface_Proxy,
    IUnknown_AddRef_Proxy,
    IUnknown_Release_Proxy ,
    (void *) (INT_PTR) -1 /* IRTCClientPresence::EnablePresence */ ,
    (void *) (INT_PTR) -1 /* IRTCClientPresence::Export */ ,
    (void *) (INT_PTR) -1 /* IRTCClientPresence::Import */ ,
    (void *) (INT_PTR) -1 /* IRTCClientPresence::EnumerateBuddies */ ,
    (void *) (INT_PTR) -1 /* IRTCClientPresence::get_Buddies */ ,
    (void *) (INT_PTR) -1 /* IRTCClientPresence::get_Buddy */ ,
    (void *) (INT_PTR) -1 /* IRTCClientPresence::AddBuddy */ ,
    (void *) (INT_PTR) -1 /* IRTCClientPresence::RemoveBuddy */ ,
    (void *) (INT_PTR) -1 /* IRTCClientPresence::EnumerateWatchers */ ,
    (void *) (INT_PTR) -1 /* IRTCClientPresence::get_Watchers */ ,
    (void *) (INT_PTR) -1 /* IRTCClientPresence::get_Watcher */ ,
    (void *) (INT_PTR) -1 /* IRTCClientPresence::AddWatcher */ ,
    (void *) (INT_PTR) -1 /* IRTCClientPresence::RemoveWatcher */ ,
    (void *) (INT_PTR) -1 /* IRTCClientPresence::SetLocalPresenceInfo */ ,
    (void *) (INT_PTR) -1 /* IRTCClientPresence::get_OfferWatcherMode */ ,
    (void *) (INT_PTR) -1 /* IRTCClientPresence::put_OfferWatcherMode */ ,
    (void *) (INT_PTR) -1 /* IRTCClientPresence::get_PrivacyMode */ ,
    (void *) (INT_PTR) -1 /* IRTCClientPresence::put_PrivacyMode */ ,
    (void *) (INT_PTR) -1 /* IRTCClientPresence2::EnablePresenceEx */ ,
    (void *) (INT_PTR) -1 /* IRTCClientPresence2::DisablePresence */ ,
    (void *) (INT_PTR) -1 /* IRTCClientPresence2::AddGroup */ ,
    (void *) (INT_PTR) -1 /* IRTCClientPresence2::RemoveGroup */ ,
    (void *) (INT_PTR) -1 /* IRTCClientPresence2::EnumerateGroups */ ,
    (void *) (INT_PTR) -1 /* IRTCClientPresence2::get_Groups */ ,
    (void *) (INT_PTR) -1 /* IRTCClientPresence2::get_Group */ ,
    (void *) (INT_PTR) -1 /* IRTCClientPresence2::AddWatcherEx */ ,
    (void *) (INT_PTR) -1 /* IRTCClientPresence2::get_WatcherEx */ ,
    (void *) (INT_PTR) -1 /* IRTCClientPresence2::put_PresenceProperty */ ,
    (void *) (INT_PTR) -1 /* IRTCClientPresence2::get_PresenceProperty */ ,
    (void *) (INT_PTR) -1 /* IRTCClientPresence2::SetPresenceData */ ,
    (void *) (INT_PTR) -1 /* IRTCClientPresence2::GetPresenceData */ ,
    (void *) (INT_PTR) -1 /* IRTCClientPresence2::GetLocalPresenceInfo */ ,
    (void *) (INT_PTR) -1 /* IRTCClientPresence2::AddBuddyEx */
};

const CInterfaceStubVtbl _IRTCClientPresence2StubVtbl =
{
    &IID_IRTCClientPresence2,
    &IRTCClientPresence2_ServerInfo,
    36,
    0, /* pure interpreted */
    CStdStubBuffer_METHODS
};


/* Object interface: IRTCClientProvisioning, ver. 0.0,
   GUID={0xB9F5CF06,0x65B9,0x4a80,{0xA0,0xE6,0x73,0xCA,0xE3,0xEF,0x38,0x22}} */

#pragma code_seg(".orpc")
static const unsigned short IRTCClientProvisioning_FormatStringOffsetTable[] =
    {
    3588,
    3630,
    3672,
    3708,
    2292,
    3744,
    204
    };

static const MIDL_STUBLESS_PROXY_INFO IRTCClientProvisioning_ProxyInfo =
    {
    &Object_StubDesc,
    __MIDL_ProcFormatString.Format,
    &IRTCClientProvisioning_FormatStringOffsetTable[-3],
    0,
    0,
    0
    };


static const MIDL_SERVER_INFO IRTCClientProvisioning_ServerInfo = 
    {
    &Object_StubDesc,
    0,
    __MIDL_ProcFormatString.Format,
    &IRTCClientProvisioning_FormatStringOffsetTable[-3],
    0,
    0,
    0,
    0};
CINTERFACE_PROXY_VTABLE(10) _IRTCClientProvisioningProxyVtbl = 
{
    &IRTCClientProvisioning_ProxyInfo,
    &IID_IRTCClientProvisioning,
    IUnknown_QueryInterface_Proxy,
    IUnknown_AddRef_Proxy,
    IUnknown_Release_Proxy ,
    (void *) (INT_PTR) -1 /* IRTCClientProvisioning::CreateProfile */ ,
    (void *) (INT_PTR) -1 /* IRTCClientProvisioning::EnableProfile */ ,
    (void *) (INT_PTR) -1 /* IRTCClientProvisioning::DisableProfile */ ,
    (void *) (INT_PTR) -1 /* IRTCClientProvisioning::EnumerateProfiles */ ,
    (void *) (INT_PTR) -1 /* IRTCClientProvisioning::get_Profiles */ ,
    (void *) (INT_PTR) -1 /* IRTCClientProvisioning::GetProfile */ ,
    (void *) (INT_PTR) -1 /* IRTCClientProvisioning::get_SessionCapabilities */
};

const CInterfaceStubVtbl _IRTCClientProvisioningStubVtbl =
{
    &IID_IRTCClientProvisioning,
    &IRTCClientProvisioning_ServerInfo,
    10,
    0, /* pure interpreted */
    CStdStubBuffer_METHODS
};


/* Object interface: IRTCClientProvisioning2, ver. 0.0,
   GUID={0xA70909B5,0xF40E,0x4587,{0xBB,0x75,0xE6,0xBC,0x08,0x45,0x02,0x3E}} */

#pragma code_seg(".orpc")
static const unsigned short IRTCClientProvisioning2_FormatStringOffsetTable[] =
    {
    3588,
    3630,
    3672,
    3708,
    2292,
    3744,
    204,
    3810
    };

static const MIDL_STUBLESS_PROXY_INFO IRTCClientProvisioning2_ProxyInfo =
    {
    &Object_StubDesc,
    __MIDL_ProcFormatString.Format,
    &IRTCClientProvisioning2_FormatStringOffsetTable[-3],
    0,
    0,
    0
    };


static const MIDL_SERVER_INFO IRTCClientProvisioning2_ServerInfo = 
    {
    &Object_StubDesc,
    0,
    __MIDL_ProcFormatString.Format,
    &IRTCClientProvisioning2_FormatStringOffsetTable[-3],
    0,
    0,
    0,
    0};
CINTERFACE_PROXY_VTABLE(11) _IRTCClientProvisioning2ProxyVtbl = 
{
    &IRTCClientProvisioning2_ProxyInfo,
    &IID_IRTCClientProvisioning2,
    IUnknown_QueryInterface_Proxy,
    IUnknown_AddRef_Proxy,
    IUnknown_Release_Proxy ,
    (void *) (INT_PTR) -1 /* IRTCClientProvisioning::CreateProfile */ ,
    (void *) (INT_PTR) -1 /* IRTCClientProvisioning::EnableProfile */ ,
    (void *) (INT_PTR) -1 /* IRTCClientProvisioning::DisableProfile */ ,
    (void *) (INT_PTR) -1 /* IRTCClientProvisioning::EnumerateProfiles */ ,
    (void *) (INT_PTR) -1 /* IRTCClientProvisioning::get_Profiles */ ,
    (void *) (INT_PTR) -1 /* IRTCClientProvisioning::GetProfile */ ,
    (void *) (INT_PTR) -1 /* IRTCClientProvisioning::get_SessionCapabilities */ ,
    (void *) (INT_PTR) -1 /* IRTCClientProvisioning2::EnableProfileEx */
};

const CInterfaceStubVtbl _IRTCClientProvisioning2StubVtbl =
{
    &IID_IRTCClientProvisioning2,
    &IRTCClientProvisioning2_ServerInfo,
    11,
    0, /* pure interpreted */
    CStdStubBuffer_METHODS
};


/* Object interface: IRTCProfile, ver. 0.0,
   GUID={0xd07eca9e,0x4062,0x4dd4,{0x9e,0x7d,0x72,0x2a,0x49,0xba,0x73,0x03}} */

#pragma code_seg(".orpc")
static const unsigned short IRTCProfile_FormatStringOffsetTable[] =
    {
    3858,
    3894,
    3930,
    3966,
    4002,
    4044,
    4080,
    4116,
    4152,
    4188,
    4224,
    4260,
    4296,
    4332,
    4368,
    4404,
    4452,
    4488
    };

static const MIDL_STUBLESS_PROXY_INFO IRTCProfile_ProxyInfo =
    {
    &Object_StubDesc,
    __MIDL_ProcFormatString.Format,
    &IRTCProfile_FormatStringOffsetTable[-3],
    0,
    0,
    0
    };


static const MIDL_SERVER_INFO IRTCProfile_ServerInfo = 
    {
    &Object_StubDesc,
    0,
    __MIDL_ProcFormatString.Format,
    &IRTCProfile_FormatStringOffsetTable[-3],
    0,
    0,
    0,
    0};
CINTERFACE_PROXY_VTABLE(21) _IRTCProfileProxyVtbl = 
{
    &IRTCProfile_ProxyInfo,
    &IID_IRTCProfile,
    IUnknown_QueryInterface_Proxy,
    IUnknown_AddRef_Proxy,
    IUnknown_Release_Proxy ,
    (void *) (INT_PTR) -1 /* IRTCProfile::get_Key */ ,
    (void *) (INT_PTR) -1 /* IRTCProfile::get_Name */ ,
    (void *) (INT_PTR) -1 /* IRTCProfile::get_XML */ ,
    (void *) (INT_PTR) -1 /* IRTCProfile::get_ProviderName */ ,
    (void *) (INT_PTR) -1 /* IRTCProfile::get_ProviderURI */ ,
    (void *) (INT_PTR) -1 /* IRTCProfile::get_ProviderData */ ,
    (void *) (INT_PTR) -1 /* IRTCProfile::get_ClientName */ ,
    (void *) (INT_PTR) -1 /* IRTCProfile::get_ClientBanner */ ,
    (void *) (INT_PTR) -1 /* IRTCProfile::get_ClientMinVer */ ,
    (void *) (INT_PTR) -1 /* IRTCProfile::get_ClientCurVer */ ,
    (void *) (INT_PTR) -1 /* IRTCProfile::get_ClientUpdateURI */ ,
    (void *) (INT_PTR) -1 /* IRTCProfile::get_ClientData */ ,
    (void *) (INT_PTR) -1 /* IRTCProfile::get_UserURI */ ,
    (void *) (INT_PTR) -1 /* IRTCProfile::get_UserName */ ,
    (void *) (INT_PTR) -1 /* IRTCProfile::get_UserAccount */ ,
    (void *) (INT_PTR) -1 /* IRTCProfile::SetCredentials */ ,
    (void *) (INT_PTR) -1 /* IRTCProfile::get_SessionCapabilities */ ,
    (void *) (INT_PTR) -1 /* IRTCProfile::get_State */
};

const CInterfaceStubVtbl _IRTCProfileStubVtbl =
{
    &IID_IRTCProfile,
    &IRTCProfile_ServerInfo,
    21,
    0, /* pure interpreted */
    CStdStubBuffer_METHODS
};


/* Object interface: IRTCProfile2, ver. 0.0,
   GUID={0x4B81F84E,0xBDC7,0x4184,{0x91,0x54,0x3C,0xB2,0xDD,0x79,0x17,0xFB}} */

#pragma code_seg(".orpc")
static const unsigned short IRTCProfile2_FormatStringOffsetTable[] =
    {
    3858,
    3894,
    3930,
    3966,
    4002,
    4044,
    4080,
    4116,
    4152,
    4188,
    4224,
    4260,
    4296,
    4332,
    4368,
    4404,
    4452,
    4488,
    4524,
    4560,
    4596,
    4632
    };

static const MIDL_STUBLESS_PROXY_INFO IRTCProfile2_ProxyInfo =
    {
    &Object_StubDesc,
    __MIDL_ProcFormatString.Format,
    &IRTCProfile2_FormatStringOffsetTable[-3],
    0,
    0,
    0
    };


static const MIDL_SERVER_INFO IRTCProfile2_ServerInfo = 
    {
    &Object_StubDesc,
    0,
    __MIDL_ProcFormatString.Format,
    &IRTCProfile2_FormatStringOffsetTable[-3],
    0,
    0,
    0,
    0};
CINTERFACE_PROXY_VTABLE(25) _IRTCProfile2ProxyVtbl = 
{
    &IRTCProfile2_ProxyInfo,
    &IID_IRTCProfile2,
    IUnknown_QueryInterface_Proxy,
    IUnknown_AddRef_Proxy,
    IUnknown_Release_Proxy ,
    (void *) (INT_PTR) -1 /* IRTCProfile::get_Key */ ,
    (void *) (INT_PTR) -1 /* IRTCProfile::get_Name */ ,
    (void *) (INT_PTR) -1 /* IRTCProfile::get_XML */ ,
    (void *) (INT_PTR) -1 /* IRTCProfile::get_ProviderName */ ,
    (void *) (INT_PTR) -1 /* IRTCProfile::get_ProviderURI */ ,
    (void *) (INT_PTR) -1 /* IRTCProfile::get_ProviderData */ ,
    (void *) (INT_PTR) -1 /* IRTCProfile::get_ClientName */ ,
    (void *) (INT_PTR) -1 /* IRTCProfile::get_ClientBanner */ ,
    (void *) (INT_PTR) -1 /* IRTCProfile::get_ClientMinVer */ ,
    (void *) (INT_PTR) -1 /* IRTCProfile::get_ClientCurVer */ ,
    (void *) (INT_PTR) -1 /* IRTCProfile::get_ClientUpdateURI */ ,
    (void *) (INT_PTR) -1 /* IRTCProfile::get_ClientData */ ,
    (void *) (INT_PTR) -1 /* IRTCProfile::get_UserURI */ ,
    (void *) (INT_PTR) -1 /* IRTCProfile::get_UserName */ ,
    (void *) (INT_PTR) -1 /* IRTCProfile::get_UserAccount */ ,
    (void *) (INT_PTR) -1 /* IRTCProfile::SetCredentials */ ,
    (void *) (INT_PTR) -1 /* IRTCProfile::get_SessionCapabilities */ ,
    (void *) (INT_PTR) -1 /* IRTCProfile::get_State */ ,
    (void *) (INT_PTR) -1 /* IRTCProfile2::get_Realm */ ,
    (void *) (INT_PTR) -1 /* IRTCProfile2::put_Realm */ ,
    (void *) (INT_PTR) -1 /* IRTCProfile2::get_AllowedAuth */ ,
    (void *) (INT_PTR) -1 /* IRTCProfile2::put_AllowedAuth */
};

const CInterfaceStubVtbl _IRTCProfile2StubVtbl =
{
    &IID_IRTCProfile2,
    &IRTCProfile2_ServerInfo,
    25,
    0, /* pure interpreted */
    CStdStubBuffer_METHODS
};


/* Object interface: IRTCProfile3, ver. 0.0,
   GUID={0x051caa1d,0x2e4e,0x4187,{0xb9,0x47,0x69,0xa0,0xc9,0x9b,0xa7,0x0b}} */

#pragma code_seg(".orpc")
static const unsigned short IRTCProfile3_FormatStringOffsetTable[] =
    {
    3858,
    3894,
    3930,
    3966,
    4002,
    4044,
    4080,
    4116,
    4152,
    4188,
    4224,
    4260,
    4296,
    4332,
    4368,
    4404,
    4452,
    4488,
    4524,
    4560,
    4596,
    4632,
    4668
    };

static const MIDL_STUBLESS_PROXY_INFO IRTCProfile3_ProxyInfo =
    {
    &Object_StubDesc,
    __MIDL_ProcFormatString.Format,
    &IRTCProfile3_FormatStringOffsetTable[-3],
    0,
    0,
    0
    };


static const MIDL_SERVER_INFO IRTCProfile3_ServerInfo = 
    {
    &Object_StubDesc,
    0,
    __MIDL_ProcFormatString.Format,
    &IRTCProfile3_FormatStringOffsetTable[-3],
    0,
    0,
    0,
    0};
CINTERFACE_PROXY_VTABLE(26) _IRTCProfile3ProxyVtbl = 
{
    &IRTCProfile3_ProxyInfo,
    &IID_IRTCProfile3,
    IUnknown_QueryInterface_Proxy,
    IUnknown_AddRef_Proxy,
    IUnknown_Release_Proxy ,
    (void *) (INT_PTR) -1 /* IRTCProfile::get_Key */ ,
    (void *) (INT_PTR) -1 /* IRTCProfile::get_Name */ ,
    (void *) (INT_PTR) -1 /* IRTCProfile::get_XML */ ,
    (void *) (INT_PTR) -1 /* IRTCProfile::get_ProviderName */ ,
    (void *) (INT_PTR) -1 /* IRTCProfile::get_ProviderURI */ ,
    (void *) (INT_PTR) -1 /* IRTCProfile::get_ProviderData */ ,
    (void *) (INT_PTR) -1 /* IRTCProfile::get_ClientName */ ,
    (void *) (INT_PTR) -1 /* IRTCProfile::get_ClientBanner */ ,
    (void *) (INT_PTR) -1 /* IRTCProfile::get_ClientMinVer */ ,
    (void *) (INT_PTR) -1 /* IRTCProfile::get_ClientCurVer */ ,
    (void *) (INT_PTR) -1 /* IRTCProfile::get_ClientUpdateURI */ ,
    (void *) (INT_PTR) -1 /* IRTCProfile::get_ClientData */ ,
    (void *) (INT_PTR) -1 /* IRTCProfile::get_UserURI */ ,
    (void *) (INT_PTR) -1 /* IRTCProfile::get_UserName */ ,
    (void *) (INT_PTR) -1 /* IRTCProfile::get_UserAccount */ ,
    (void *) (INT_PTR) -1 /* IRTCProfile::SetCredentials */ ,
    (void *) (INT_PTR) -1 /* IRTCProfile::get_SessionCapabilities */ ,
    (void *) (INT_PTR) -1 /* IRTCProfile::get_State */ ,
    (void *) (INT_PTR) -1 /* IRTCProfile2::get_Realm */ ,
    (void *) (INT_PTR) -1 /* IRTCProfile2::put_Realm */ ,
    (void *) (INT_PTR) -1 /* IRTCProfile2::get_AllowedAuth */ ,
    (void *) (INT_PTR) -1 /* IRTCProfile2::put_AllowedAuth */ ,
    (void *) (INT_PTR) -1 /* IRTCProfile3::GetServer */
};

const CInterfaceStubVtbl _IRTCProfile3StubVtbl =
{
    &IID_IRTCProfile3,
    &IRTCProfile3_ServerInfo,
    26,
    0, /* pure interpreted */
    CStdStubBuffer_METHODS
};


/* Object interface: IRTCSession, ver. 0.0,
   GUID={0x387c8086,0x99be,0x42fb,{0x99,0x73,0x7c,0x0f,0xc0,0xca,0x9f,0xa8}} */

#pragma code_seg(".orpc")
static const unsigned short IRTCSession_FormatStringOffsetTable[] =
    {
    4710,
    4746,
    4782,
    4818,
    2292,
    4854,
    4884,
    4920,
    4974,
    5022,
    5058,
    5094,
    4296,
    4332,
    5130,
    5160,
    5208,
    5250,
    5292,
    5334
    };

static const MIDL_STUBLESS_PROXY_INFO IRTCSession_ProxyInfo =
    {
    &Object_StubDesc,
    __MIDL_ProcFormatString.Format,
    &IRTCSession_FormatStringOffsetTable[-3],
    0,
    0,
    0
    };


static const MIDL_SERVER_INFO IRTCSession_ServerInfo = 
    {
    &Object_StubDesc,
    0,
    __MIDL_ProcFormatString.Format,
    &IRTCSession_FormatStringOffsetTable[-3],
    0,
    0,
    0,
    0};
CINTERFACE_PROXY_VTABLE(23) _IRTCSessionProxyVtbl = 
{
    &IRTCSession_ProxyInfo,
    &IID_IRTCSession,
    IUnknown_QueryInterface_Proxy,
    IUnknown_AddRef_Proxy,
    IUnknown_Release_Proxy ,
    (void *) (INT_PTR) -1 /* IRTCSession::get_Client */ ,
    (void *) (INT_PTR) -1 /* IRTCSession::get_State */ ,
    (void *) (INT_PTR) -1 /* IRTCSession::get_Type */ ,
    (void *) (INT_PTR) -1 /* IRTCSession::get_Profile */ ,
    (void *) (INT_PTR) -1 /* IRTCSession::get_Participants */ ,
    (void *) (INT_PTR) -1 /* IRTCSession::Answer */ ,
    (void *) (INT_PTR) -1 /* IRTCSession::Terminate */ ,
    (void *) (INT_PTR) -1 /* IRTCSession::Redirect */ ,
    (void *) (INT_PTR) -1 /* IRTCSession::AddParticipant */ ,
    (void *) (INT_PTR) -1 /* IRTCSession::RemoveParticipant */ ,
    (void *) (INT_PTR) -1 /* IRTCSession::EnumerateParticipants */ ,
    (void *) (INT_PTR) -1 /* IRTCSession::get_CanAddParticipants */ ,
    (void *) (INT_PTR) -1 /* IRTCSession::get_RedirectedUserURI */ ,
    (void *) (INT_PTR) -1 /* IRTCSession::get_RedirectedUserName */ ,
    (void *) (INT_PTR) -1 /* IRTCSession::NextRedirectedUser */ ,
    (void *) (INT_PTR) -1 /* IRTCSession::SendMessage */ ,
    (void *) (INT_PTR) -1 /* IRTCSession::SendMessageStatus */ ,
    (void *) (INT_PTR) -1 /* IRTCSession::AddStream */ ,
    (void *) (INT_PTR) -1 /* IRTCSession::RemoveStream */ ,
    (void *) (INT_PTR) -1 /* IRTCSession::put_EncryptionKey */
};

const CInterfaceStubVtbl _IRTCSessionStubVtbl =
{
    &IID_IRTCSession,
    &IRTCSession_ServerInfo,
    23,
    0, /* pure interpreted */
    CStdStubBuffer_METHODS
};


/* Object interface: IRTCSession2, ver. 0.0,
   GUID={0x17D7CDFC,0xB007,0x484c,{0x99,0xD2,0x86,0xA8,0xA8,0x20,0x99,0x1D}} */

#pragma code_seg(".orpc")
static const unsigned short IRTCSession2_FormatStringOffsetTable[] =
    {
    4710,
    4746,
    4782,
    4818,
    2292,
    4854,
    4884,
    4920,
    4974,
    5022,
    5058,
    5094,
    4296,
    4332,
    5130,
    5160,
    5208,
    5250,
    5292,
    5334,
    5376,
    5424,
    5466,
    5508,
    5550,
    5592
    };

static const MIDL_STUBLESS_PROXY_INFO IRTCSession2_ProxyInfo =
    {
    &Object_StubDesc,
    __MIDL_ProcFormatString.Format,
    &IRTCSession2_FormatStringOffsetTable[-3],
    0,
    0,
    0
    };


static const MIDL_SERVER_INFO IRTCSession2_ServerInfo = 
    {
    &Object_StubDesc,
    0,
    __MIDL_ProcFormatString.Format,
    &IRTCSession2_FormatStringOffsetTable[-3],
    0,
    0,
    0,
    0};
CINTERFACE_PROXY_VTABLE(29) _IRTCSession2ProxyVtbl = 
{
    &IRTCSession2_ProxyInfo,
    &IID_IRTCSession2,
    IUnknown_QueryInterface_Proxy,
    IUnknown_AddRef_Proxy,
    IUnknown_Release_Proxy ,
    (void *) (INT_PTR) -1 /* IRTCSession::get_Client */ ,
    (void *) (INT_PTR) -1 /* IRTCSession::get_State */ ,
    (void *) (INT_PTR) -1 /* IRTCSession::get_Type */ ,
    (void *) (INT_PTR) -1 /* IRTCSession::get_Profile */ ,
    (void *) (INT_PTR) -1 /* IRTCSession::get_Participants */ ,
    (void *) (INT_PTR) -1 /* IRTCSession::Answer */ ,
    (void *) (INT_PTR) -1 /* IRTCSession::Terminate */ ,
    (void *) (INT_PTR) -1 /* IRTCSession::Redirect */ ,
    (void *) (INT_PTR) -1 /* IRTCSession::AddParticipant */ ,
    (void *) (INT_PTR) -1 /* IRTCSession::RemoveParticipant */ ,
    (void *) (INT_PTR) -1 /* IRTCSession::EnumerateParticipants */ ,
    (void *) (INT_PTR) -1 /* IRTCSession::get_CanAddParticipants */ ,
    (void *) (INT_PTR) -1 /* IRTCSession::get_RedirectedUserURI */ ,
    (void *) (INT_PTR) -1 /* IRTCSession::get_RedirectedUserName */ ,
    (void *) (INT_PTR) -1 /* IRTCSession::NextRedirectedUser */ ,
    (void *) (INT_PTR) -1 /* IRTCSession::SendMessage */ ,
    (void *) (INT_PTR) -1 /* IRTCSession::SendMessageStatus */ ,
    (void *) (INT_PTR) -1 /* IRTCSession::AddStream */ ,
    (void *) (INT_PTR) -1 /* IRTCSession::RemoveStream */ ,
    (void *) (INT_PTR) -1 /* IRTCSession::put_EncryptionKey */ ,
    (void *) (INT_PTR) -1 /* IRTCSession2::SendInfo */ ,
    (void *) (INT_PTR) -1 /* IRTCSession2::put_PreferredSecurityLevel */ ,
    (void *) (INT_PTR) -1 /* IRTCSession2::get_PreferredSecurityLevel */ ,
    (void *) (INT_PTR) -1 /* IRTCSession2::IsSecurityEnabled */ ,
    (void *) (INT_PTR) -1 /* IRTCSession2::AnswerWithSessionDescription */ ,
    (void *) (INT_PTR) -1 /* IRTCSession2::ReInviteWithSessionDescription */
};

const CInterfaceStubVtbl _IRTCSession2StubVtbl =
{
    &IID_IRTCSession2,
    &IRTCSession2_ServerInfo,
    29,
    0, /* pure interpreted */
    CStdStubBuffer_METHODS
};


/* Object interface: IRTCSession3, ver. 0.0,
   GUID={0xA46E81AD,0x1D5A,0x4063,{0x95,0x21,0x62,0xE1,0xFA,0x85,0xDF,0x5C}} */

#pragma code_seg(".orpc")
static const unsigned short IRTCSession3_FormatStringOffsetTable[] =
    {
    4710,
    4746,
    4782,
    4818,
    2292,
    4854,
    4884,
    4920,
    4974,
    5022,
    5058,
    5094,
    4296,
    4332,
    5130,
    5160,
    5208,
    5250,
    5292,
    5334,
    5376,
    5424,
    5466,
    5508,
    5550,
    5592,
    5640
    };

static const MIDL_STUBLESS_PROXY_INFO IRTCSession3_ProxyInfo =
    {
    &Object_StubDesc,
    __MIDL_ProcFormatString.Format,
    &IRTCSession3_FormatStringOffsetTable[-3],
    0,
    0,
    0
    };


static const MIDL_SERVER_INFO IRTCSession3_ServerInfo = 
    {
    &Object_StubDesc,
    0,
    __MIDL_ProcFormatString.Format,
    &IRTCSession3_FormatStringOffsetTable[-3],
    0,
    0,
    0,
    0};
CINTERFACE_PROXY_VTABLE(30) _IRTCSession3ProxyVtbl = 
{
    &IRTCSession3_ProxyInfo,
    &IID_IRTCSession3,
    IUnknown_QueryInterface_Proxy,
    IUnknown_AddRef_Proxy,
    IUnknown_Release_Proxy ,
    (void *) (INT_PTR) -1 /* IRTCSession::get_Client */ ,
    (void *) (INT_PTR) -1 /* IRTCSession::get_State */ ,
    (void *) (INT_PTR) -1 /* IRTCSession::get_Type */ ,
    (void *) (INT_PTR) -1 /* IRTCSession::get_Profile */ ,
    (void *) (INT_PTR) -1 /* IRTCSession::get_Participants */ ,
    (void *) (INT_PTR) -1 /* IRTCSession::Answer */ ,
    (void *) (INT_PTR) -1 /* IRTCSession::Terminate */ ,
    (void *) (INT_PTR) -1 /* IRTCSession::Redirect */ ,
    (void *) (INT_PTR) -1 /* IRTCSession::AddParticipant */ ,
    (void *) (INT_PTR) -1 /* IRTCSession::RemoveParticipant */ ,
    (void *) (INT_PTR) -1 /* IRTCSession::EnumerateParticipants */ ,
    (void *) (INT_PTR) -1 /* IRTCSession::get_CanAddParticipants */ ,
    (void *) (INT_PTR) -1 /* IRTCSession::get_RedirectedUserURI */ ,
    (void *) (INT_PTR) -1 /* IRTCSession::get_RedirectedUserName */ ,
    (void *) (INT_PTR) -1 /* IRTCSession::NextRedirectedUser */ ,
    (void *) (INT_PTR) -1 /* IRTCSession::SendMessage */ ,
    (void *) (INT_PTR) -1 /* IRTCSession::SendMessageStatus */ ,
    (void *) (INT_PTR) -1 /* IRTCSession::AddStream */ ,
    (void *) (INT_PTR) -1 /* IRTCSession::RemoveStream */ ,
    (void *) (INT_PTR) -1 /* IRTCSession::put_EncryptionKey */ ,
    (void *) (INT_PTR) -1 /* IRTCSession2::SendInfo */ ,
    (void *) (INT_PTR) -1 /* IRTCSession2::put_PreferredSecurityLevel */ ,
    (void *) (INT_PTR) -1 /* IRTCSession2::get_PreferredSecurityLevel */ ,
    (void *) (INT_PTR) -1 /* IRTCSession2::IsSecurityEnabled */ ,
    (void *) (INT_PTR) -1 /* IRTCSession2::AnswerWithSessionDescription */ ,
    (void *) (INT_PTR) -1 /* IRTCSession2::ReInviteWithSessionDescription */ ,
    (void *) (INT_PTR) -1 /* IRTCSession3::AddParticipantEx */
};

const CInterfaceStubVtbl _IRTCSession3StubVtbl =
{
    &IID_IRTCSession3,
    &IRTCSession3_ServerInfo,
    30,
    0, /* pure interpreted */
    CStdStubBuffer_METHODS
};


/* Object interface: IRTCSessionCallControl, ver. 0.0,
   GUID={0xE9A50D94,0x190B,0x4F82,{0x95,0x30,0x3B,0x8E,0xBF,0x60,0x75,0x8A}} */

#pragma code_seg(".orpc")
static const unsigned short IRTCSessionCallControl_FormatStringOffsetTable[] =
    {
    5694,
    5730,
    5766,
    5802,
    5844,
    4044,
    5880,
    5916,
    5952
    };

static const MIDL_STUBLESS_PROXY_INFO IRTCSessionCallControl_ProxyInfo =
    {
    &Object_StubDesc,
    __MIDL_ProcFormatString.Format,
    &IRTCSessionCallControl_FormatStringOffsetTable[-3],
    0,
    0,
    0
    };


static const MIDL_SERVER_INFO IRTCSessionCallControl_ServerInfo = 
    {
    &Object_StubDesc,
    0,
    __MIDL_ProcFormatString.Format,
    &IRTCSessionCallControl_FormatStringOffsetTable[-3],
    0,
    0,
    0,
    0};
CINTERFACE_PROXY_VTABLE(12) _IRTCSessionCallControlProxyVtbl = 
{
    &IRTCSessionCallControl_ProxyInfo,
    &IID_IRTCSessionCallControl,
    IUnknown_QueryInterface_Proxy,
    IUnknown_AddRef_Proxy,
    IUnknown_Release_Proxy ,
    (void *) (INT_PTR) -1 /* IRTCSessionCallControl::Hold */ ,
    (void *) (INT_PTR) -1 /* IRTCSessionCallControl::UnHold */ ,
    (void *) (INT_PTR) -1 /* IRTCSessionCallControl::Forward */ ,
    (void *) (INT_PTR) -1 /* IRTCSessionCallControl::Refer */ ,
    (void *) (INT_PTR) -1 /* IRTCSessionCallControl::put_ReferredByURI */ ,
    (void *) (INT_PTR) -1 /* IRTCSessionCallControl::get_ReferredByURI */ ,
    (void *) (INT_PTR) -1 /* IRTCSessionCallControl::put_ReferCookie */ ,
    (void *) (INT_PTR) -1 /* IRTCSessionCallControl::get_ReferCookie */ ,
    (void *) (INT_PTR) -1 /* IRTCSessionCallControl::get_IsReferred */
};

const CInterfaceStubVtbl _IRTCSessionCallControlStubVtbl =
{
    &IID_IRTCSessionCallControl,
    &IRTCSessionCallControl_ServerInfo,
    12,
    0, /* pure interpreted */
    CStdStubBuffer_METHODS
};


/* Object interface: IRTCParticipant, ver. 0.0,
   GUID={0xae86add5,0x26b1,0x4414,{0xaf,0x1d,0xb9,0x4c,0xd9,0x38,0xd7,0x39}} */

#pragma code_seg(".orpc")
static const unsigned short IRTCParticipant_FormatStringOffsetTable[] =
    {
    3858,
    3894,
    5988,
    6024,
    6060
    };

static const MIDL_STUBLESS_PROXY_INFO IRTCParticipant_ProxyInfo =
    {
    &Object_StubDesc,
    __MIDL_ProcFormatString.Format,
    &IRTCParticipant_FormatStringOffsetTable[-3],
    0,
    0,
    0
    };


static const MIDL_SERVER_INFO IRTCParticipant_ServerInfo = 
    {
    &Object_StubDesc,
    0,
    __MIDL_ProcFormatString.Format,
    &IRTCParticipant_FormatStringOffsetTable[-3],
    0,
    0,
    0,
    0};
CINTERFACE_PROXY_VTABLE(8) _IRTCParticipantProxyVtbl = 
{
    &IRTCParticipant_ProxyInfo,
    &IID_IRTCParticipant,
    IUnknown_QueryInterface_Proxy,
    IUnknown_AddRef_Proxy,
    IUnknown_Release_Proxy ,
    (void *) (INT_PTR) -1 /* IRTCParticipant::get_UserURI */ ,
    (void *) (INT_PTR) -1 /* IRTCParticipant::get_Name */ ,
    (void *) (INT_PTR) -1 /* IRTCParticipant::get_Removable */ ,
    (void *) (INT_PTR) -1 /* IRTCParticipant::get_State */ ,
    (void *) (INT_PTR) -1 /* IRTCParticipant::get_Session */
};

const CInterfaceStubVtbl _IRTCParticipantStubVtbl =
{
    &IID_IRTCParticipant,
    &IRTCParticipant_ServerInfo,
    8,
    0, /* pure interpreted */
    CStdStubBuffer_METHODS
};


/* Object interface: IRTCParticipant2, ver. 0.0,
   GUID={0xB492D4B4,0x42DF,0x430a,{0x84,0x8F,0x36,0xFB,0x39,0xFD,0x00,0x5F}} */

#pragma code_seg(".orpc")
static const unsigned short IRTCParticipant2_FormatStringOffsetTable[] =
    {
    3858,
    3894,
    5988,
    6024,
    6060,
    4044,
    204
    };

static const MIDL_STUBLESS_PROXY_INFO IRTCParticipant2_ProxyInfo =
    {
    &Object_StubDesc,
    __MIDL_ProcFormatString.Format,
    &IRTCParticipant2_FormatStringOffsetTable[-3],
    0,
    0,
    0
    };


static const MIDL_SERVER_INFO IRTCParticipant2_ServerInfo = 
    {
    &Object_StubDesc,
    0,
    __MIDL_ProcFormatString.Format,
    &IRTCParticipant2_FormatStringOffsetTable[-3],
    0,
    0,
    0,
    0};
CINTERFACE_PROXY_VTABLE(10) _IRTCParticipant2ProxyVtbl = 
{
    &IRTCParticipant2_ProxyInfo,
    &IID_IRTCParticipant2,
    IUnknown_QueryInterface_Proxy,
    IUnknown_AddRef_Proxy,
    IUnknown_Release_Proxy ,
    (void *) (INT_PTR) -1 /* IRTCParticipant::get_UserURI */ ,
    (void *) (INT_PTR) -1 /* IRTCParticipant::get_Name */ ,
    (void *) (INT_PTR) -1 /* IRTCParticipant::get_Removable */ ,
    (void *) (INT_PTR) -1 /* IRTCParticipant::get_State */ ,
    (void *) (INT_PTR) -1 /* IRTCParticipant::get_Session */ ,
    (void *) (INT_PTR) -1 /* IRTCParticipant2::get_DeviceID */ ,
    (void *) (INT_PTR) -1 /* IRTCParticipant2::get_FederationFlag */
};

const CInterfaceStubVtbl _IRTCParticipant2StubVtbl =
{
    &IID_IRTCParticipant2,
    &IRTCParticipant2_ServerInfo,
    10,
    0, /* pure interpreted */
    CStdStubBuffer_METHODS
};


/* Object interface: IDispatch, ver. 0.0,
   GUID={0x00020400,0x0000,0x0000,{0xC0,0x00,0x00,0x00,0x00,0x00,0x00,0x46}} */


/* Object interface: IRTCRoamingEvent, ver. 0.0,
   GUID={0x79960a6b,0x0cb1,0x4dc8,{0xa8,0x05,0x73,0x18,0xe9,0x99,0x02,0xe8}} */

#pragma code_seg(".orpc")
static const unsigned short IRTCRoamingEvent_FormatStringOffsetTable[] =
    {
    (unsigned short) -1,
    (unsigned short) -1,
    (unsigned short) -1,
    (unsigned short) -1,
    6096,
    6132,
    204,
    5916
    };

static const MIDL_STUBLESS_PROXY_INFO IRTCRoamingEvent_ProxyInfo =
    {
    &Object_StubDesc,
    __MIDL_ProcFormatString.Format,
    &IRTCRoamingEvent_FormatStringOffsetTable[-3],
    0,
    0,
    0
    };


static const MIDL_SERVER_INFO IRTCRoamingEvent_ServerInfo = 
    {
    &Object_StubDesc,
    0,
    __MIDL_ProcFormatString.Format,
    &IRTCRoamingEvent_FormatStringOffsetTable[-3],
    0,
    0,
    0,
    0};
CINTERFACE_PROXY_VTABLE(11) _IRTCRoamingEventProxyVtbl = 
{
    &IRTCRoamingEvent_ProxyInfo,
    &IID_IRTCRoamingEvent,
    IUnknown_QueryInterface_Proxy,
    IUnknown_AddRef_Proxy,
    IUnknown_Release_Proxy ,
    0 /* (void *) (INT_PTR) -1 /* IDispatch::GetTypeInfoCount */ ,
    0 /* (void *) (INT_PTR) -1 /* IDispatch::GetTypeInfo */ ,
    0 /* (void *) (INT_PTR) -1 /* IDispatch::GetIDsOfNames */ ,
    0 /* IDispatch_Invoke_Proxy */ ,
    (void *) (INT_PTR) -1 /* IRTCRoamingEvent::get_EventType */ ,
    (void *) (INT_PTR) -1 /* IRTCRoamingEvent::get_Profile */ ,
    (void *) (INT_PTR) -1 /* IRTCRoamingEvent::get_StatusCode */ ,
    (void *) (INT_PTR) -1 /* IRTCRoamingEvent::get_StatusText */
};


static const PRPC_STUB_FUNCTION IRTCRoamingEvent_table[] =
{
    STUB_FORWARDING_FUNCTION,
    STUB_FORWARDING_FUNCTION,
    STUB_FORWARDING_FUNCTION,
    STUB_FORWARDING_FUNCTION,
    NdrStubCall2,
    NdrStubCall2,
    NdrStubCall2,
    NdrStubCall2
};

CInterfaceStubVtbl _IRTCRoamingEventStubVtbl =
{
    &IID_IRTCRoamingEvent,
    &IRTCRoamingEvent_ServerInfo,
    11,
    &IRTCRoamingEvent_table[-3],
    CStdStubBuffer_DELEGATING_METHODS
};


/* Object interface: IRTCProfileEvent, ver. 0.0,
   GUID={0xD6D5AB3B,0x770E,0x43e8,{0x80,0x0A,0x79,0xB0,0x62,0x39,0x5F,0xCA}} */

#pragma code_seg(".orpc")
static const unsigned short IRTCProfileEvent_FormatStringOffsetTable[] =
    {
    (unsigned short) -1,
    (unsigned short) -1,
    (unsigned short) -1,
    (unsigned short) -1,
    6168,
    6204,
    204
    };

static const MIDL_STUBLESS_PROXY_INFO IRTCProfileEvent_ProxyInfo =
    {
    &Object_StubDesc,
    __MIDL_ProcFormatString.Format,
    &IRTCProfileEvent_FormatStringOffsetTable[-3],
    0,
    0,
    0
    };


static const MIDL_SERVER_INFO IRTCProfileEvent_ServerInfo = 
    {
    &Object_StubDesc,
    0,
    __MIDL_ProcFormatString.Format,
    &IRTCProfileEvent_FormatStringOffsetTable[-3],
    0,
    0,
    0,
    0};
CINTERFACE_PROXY_VTABLE(10) _IRTCProfileEventProxyVtbl = 
{
    &IRTCProfileEvent_ProxyInfo,
    &IID_IRTCProfileEvent,
    IUnknown_QueryInterface_Proxy,
    IUnknown_AddRef_Proxy,
    IUnknown_Release_Proxy ,
    0 /* (void *) (INT_PTR) -1 /* IDispatch::GetTypeInfoCount */ ,
    0 /* (void *) (INT_PTR) -1 /* IDispatch::GetTypeInfo */ ,
    0 /* (void *) (INT_PTR) -1 /* IDispatch::GetIDsOfNames */ ,
    0 /* IDispatch_Invoke_Proxy */ ,
    (void *) (INT_PTR) -1 /* IRTCProfileEvent::get_Profile */ ,
    (void *) (INT_PTR) -1 /* IRTCProfileEvent::get_Cookie */ ,
    (void *) (INT_PTR) -1 /* IRTCProfileEvent::get_StatusCode */
};


static const PRPC_STUB_FUNCTION IRTCProfileEvent_table[] =
{
    STUB_FORWARDING_FUNCTION,
    STUB_FORWARDING_FUNCTION,
    STUB_FORWARDING_FUNCTION,
    STUB_FORWARDING_FUNCTION,
    NdrStubCall2,
    NdrStubCall2,
    NdrStubCall2
};

CInterfaceStubVtbl _IRTCProfileEventStubVtbl =
{
    &IID_IRTCProfileEvent,
    &IRTCProfileEvent_ServerInfo,
    10,
    &IRTCProfileEvent_table[-3],
    CStdStubBuffer_DELEGATING_METHODS
};


/* Object interface: IRTCProfileEvent2, ver. 0.0,
   GUID={0x62E56EDC,0x03FA,0x4121,{0x94,0xFB,0x23,0x49,0x3F,0xD0,0xAE,0x64}} */

#pragma code_seg(".orpc")
static const unsigned short IRTCProfileEvent2_FormatStringOffsetTable[] =
    {
    (unsigned short) -1,
    (unsigned short) -1,
    (unsigned short) -1,
    (unsigned short) -1,
    6168,
    6204,
    204,
    6240
    };

static const MIDL_STUBLESS_PROXY_INFO IRTCProfileEvent2_ProxyInfo =
    {
    &Object_StubDesc,
    __MIDL_ProcFormatString.Format,
    &IRTCProfileEvent2_FormatStringOffsetTable[-3],
    0,
    0,
    0
    };


static const MIDL_SERVER_INFO IRTCProfileEvent2_ServerInfo = 
    {
    &Object_StubDesc,
    0,
    __MIDL_ProcFormatString.Format,
    &IRTCProfileEvent2_FormatStringOffsetTable[-3],
    0,
    0,
    0,
    0};
CINTERFACE_PROXY_VTABLE(11) _IRTCProfileEvent2ProxyVtbl = 
{
    &IRTCProfileEvent2_ProxyInfo,
    &IID_IRTCProfileEvent2,
    IUnknown_QueryInterface_Proxy,
    IUnknown_AddRef_Proxy,
    IUnknown_Release_Proxy ,
    0 /* (void *) (INT_PTR) -1 /* IDispatch::GetTypeInfoCount */ ,
    0 /* (void *) (INT_PTR) -1 /* IDispatch::GetTypeInfo */ ,
    0 /* (void *) (INT_PTR) -1 /* IDispatch::GetIDsOfNames */ ,
    0 /* IDispatch_Invoke_Proxy */ ,
    (void *) (INT_PTR) -1 /* IRTCProfileEvent::get_Profile */ ,
    (void *) (INT_PTR) -1 /* IRTCProfileEvent::get_Cookie */ ,
    (void *) (INT_PTR) -1 /* IRTCProfileEvent::get_StatusCode */ ,
    (void *) (INT_PTR) -1 /* IRTCProfileEvent2::get_EventType */
};


static const PRPC_STUB_FUNCTION IRTCProfileEvent2_table[] =
{
    STUB_FORWARDING_FUNCTION,
    STUB_FORWARDING_FUNCTION,
    STUB_FORWARDING_FUNCTION,
    STUB_FORWARDING_FUNCTION,
    NdrStubCall2,
    NdrStubCall2,
    NdrStubCall2,
    NdrStubCall2
};

CInterfaceStubVtbl _IRTCProfileEvent2StubVtbl =
{
    &IID_IRTCProfileEvent2,
    &IRTCProfileEvent2_ServerInfo,
    11,
    &IRTCProfileEvent2_table[-3],
    CStdStubBuffer_DELEGATING_METHODS
};


/* Object interface: IRTCClientEvent, ver. 0.0,
   GUID={0x2b493b7a,0x3cba,0x4170,{0x9c,0x8b,0x76,0xa9,0xda,0xcd,0xd6,0x44}} */

#pragma code_seg(".orpc")
static const unsigned short IRTCClientEvent_FormatStringOffsetTable[] =
    {
    (unsigned short) -1,
    (unsigned short) -1,
    (unsigned short) -1,
    (unsigned short) -1,
    6096,
    6276
    };

static const MIDL_STUBLESS_PROXY_INFO IRTCClientEvent_ProxyInfo =
    {
    &Object_StubDesc,
    __MIDL_ProcFormatString.Format,
    &IRTCClientEvent_FormatStringOffsetTable[-3],
    0,
    0,
    0
    };


static const MIDL_SERVER_INFO IRTCClientEvent_ServerInfo = 
    {
    &Object_StubDesc,
    0,
    __MIDL_ProcFormatString.Format,
    &IRTCClientEvent_FormatStringOffsetTable[-3],
    0,
    0,
    0,
    0};
CINTERFACE_PROXY_VTABLE(9) _IRTCClientEventProxyVtbl = 
{
    &IRTCClientEvent_ProxyInfo,
    &IID_IRTCClientEvent,
    IUnknown_QueryInterface_Proxy,
    IUnknown_AddRef_Proxy,
    IUnknown_Release_Proxy ,
    0 /* (void *) (INT_PTR) -1 /* IDispatch::GetTypeInfoCount */ ,
    0 /* (void *) (INT_PTR) -1 /* IDispatch::GetTypeInfo */ ,
    0 /* (void *) (INT_PTR) -1 /* IDispatch::GetIDsOfNames */ ,
    0 /* IDispatch_Invoke_Proxy */ ,
    (void *) (INT_PTR) -1 /* IRTCClientEvent::get_EventType */ ,
    (void *) (INT_PTR) -1 /* IRTCClientEvent::get_Client */
};


static const PRPC_STUB_FUNCTION IRTCClientEvent_table[] =
{
    STUB_FORWARDING_FUNCTION,
    STUB_FORWARDING_FUNCTION,
    STUB_FORWARDING_FUNCTION,
    STUB_FORWARDING_FUNCTION,
    NdrStubCall2,
    NdrStubCall2
};

CInterfaceStubVtbl _IRTCClientEventStubVtbl =
{
    &IID_IRTCClientEvent,
    &IRTCClientEvent_ServerInfo,
    9,
    &IRTCClientEvent_table[-3],
    CStdStubBuffer_DELEGATING_METHODS
};


/* Object interface: IRTCRegistrationStateChangeEvent, ver. 0.0,
   GUID={0x62d0991b,0x50ab,0x4f02,{0xb9,0x48,0xca,0x94,0xf2,0x6f,0x8f,0x95}} */

#pragma code_seg(".orpc")
static const unsigned short IRTCRegistrationStateChangeEvent_FormatStringOffsetTable[] =
    {
    (unsigned short) -1,
    (unsigned short) -1,
    (unsigned short) -1,
    (unsigned short) -1,
    6168,
    6312,
    204,
    5916
    };

static const MIDL_STUBLESS_PROXY_INFO IRTCRegistrationStateChangeEvent_ProxyInfo =
    {
    &Object_StubDesc,
    __MIDL_ProcFormatString.Format,
    &IRTCRegistrationStateChangeEvent_FormatStringOffsetTable[-3],
    0,
    0,
    0
    };


static const MIDL_SERVER_INFO IRTCRegistrationStateChangeEvent_ServerInfo = 
    {
    &Object_StubDesc,
    0,
    __MIDL_ProcFormatString.Format,
    &IRTCRegistrationStateChangeEvent_FormatStringOffsetTable[-3],
    0,
    0,
    0,
    0};
CINTERFACE_PROXY_VTABLE(11) _IRTCRegistrationStateChangeEventProxyVtbl = 
{
    &IRTCRegistrationStateChangeEvent_ProxyInfo,
    &IID_IRTCRegistrationStateChangeEvent,
    IUnknown_QueryInterface_Proxy,
    IUnknown_AddRef_Proxy,
    IUnknown_Release_Proxy ,
    0 /* (void *) (INT_PTR) -1 /* IDispatch::GetTypeInfoCount */ ,
    0 /* (void *) (INT_PTR) -1 /* IDispatch::GetTypeInfo */ ,
    0 /* (void *) (INT_PTR) -1 /* IDispatch::GetIDsOfNames */ ,
    0 /* IDispatch_Invoke_Proxy */ ,
    (void *) (INT_PTR) -1 /* IRTCRegistrationStateChangeEvent::get_Profile */ ,
    (void *) (INT_PTR) -1 /* IRTCRegistrationStateChangeEvent::get_State */ ,
    (void *) (INT_PTR) -1 /* IRTCRegistrationStateChangeEvent::get_StatusCode */ ,
    (void *) (INT_PTR) -1 /* IRTCRegistrationStateChangeEvent::get_StatusText */
};


static const PRPC_STUB_FUNCTION IRTCRegistrationStateChangeEvent_table[] =
{
    STUB_FORWARDING_FUNCTION,
    STUB_FORWARDING_FUNCTION,
    STUB_FORWARDING_FUNCTION,
    STUB_FORWARDING_FUNCTION,
    NdrStubCall2,
    NdrStubCall2,
    NdrStubCall2,
    NdrStubCall2
};

CInterfaceStubVtbl _IRTCRegistrationStateChangeEventStubVtbl =
{
    &IID_IRTCRegistrationStateChangeEvent,
    &IRTCRegistrationStateChangeEvent_ServerInfo,
    11,
    &IRTCRegistrationStateChangeEvent_table[-3],
    CStdStubBuffer_DELEGATING_METHODS
};


/* Object interface: IRTCSessionStateChangeEvent, ver. 0.0,
   GUID={0xb5bad703,0x5952,0x48b3,{0x93,0x21,0x7f,0x45,0x00,0x52,0x15,0x06}} */

#pragma code_seg(".orpc")
static const unsigned short IRTCSessionStateChangeEvent_FormatStringOffsetTable[] =
    {
    (unsigned short) -1,
    (unsigned short) -1,
    (unsigned short) -1,
    (unsigned short) -1,
    6060,
    6312,
    204,
    5916
    };

static const MIDL_STUBLESS_PROXY_INFO IRTCSessionStateChangeEvent_ProxyInfo =
    {
    &Object_StubDesc,
    __MIDL_ProcFormatString.Format,
    &IRTCSessionStateChangeEvent_FormatStringOffsetTable[-3],
    0,
    0,
    0
    };


static const MIDL_SERVER_INFO IRTCSessionStateChangeEvent_ServerInfo = 
    {
    &Object_StubDesc,
    0,
    __MIDL_ProcFormatString.Format,
    &IRTCSessionStateChangeEvent_FormatStringOffsetTable[-3],
    0,
    0,
    0,
    0};
CINTERFACE_PROXY_VTABLE(11) _IRTCSessionStateChangeEventProxyVtbl = 
{
    &IRTCSessionStateChangeEvent_ProxyInfo,
    &IID_IRTCSessionStateChangeEvent,
    IUnknown_QueryInterface_Proxy,
    IUnknown_AddRef_Proxy,
    IUnknown_Release_Proxy ,
    0 /* (void *) (INT_PTR) -1 /* IDispatch::GetTypeInfoCount */ ,
    0 /* (void *) (INT_PTR) -1 /* IDispatch::GetTypeInfo */ ,
    0 /* (void *) (INT_PTR) -1 /* IDispatch::GetIDsOfNames */ ,
    0 /* IDispatch_Invoke_Proxy */ ,
    (void *) (INT_PTR) -1 /* IRTCSessionStateChangeEvent::get_Session */ ,
    (void *) (INT_PTR) -1 /* IRTCSessionStateChangeEvent::get_State */ ,
    (void *) (INT_PTR) -1 /* IRTCSessionStateChangeEvent::get_StatusCode */ ,
    (void *) (INT_PTR) -1 /* IRTCSessionStateChangeEvent::get_StatusText */
};


static const PRPC_STUB_FUNCTION IRTCSessionStateChangeEvent_table[] =
{
    STUB_FORWARDING_FUNCTION,
    STUB_FORWARDING_FUNCTION,
    STUB_FORWARDING_FUNCTION,
    STUB_FORWARDING_FUNCTION,
    NdrStubCall2,
    NdrStubCall2,
    NdrStubCall2,
    NdrStubCall2
};

CInterfaceStubVtbl _IRTCSessionStateChangeEventStubVtbl =
{
    &IID_IRTCSessionStateChangeEvent,
    &IRTCSessionStateChangeEvent_ServerInfo,
    11,
    &IRTCSessionStateChangeEvent_table[-3],
    CStdStubBuffer_DELEGATING_METHODS
};


/* Object interface: IRTCSessionStateChangeEvent2, ver. 0.0,
   GUID={0x4F933171,0x6F95,0x4880,{0x80,0xD9,0x2E,0xC8,0xD4,0x95,0xD2,0x61}} */

#pragma code_seg(".orpc")
static const unsigned short IRTCSessionStateChangeEvent2_FormatStringOffsetTable[] =
    {
    (unsigned short) -1,
    (unsigned short) -1,
    (unsigned short) -1,
    (unsigned short) -1,
    6060,
    6312,
    204,
    5916,
    6348,
    6384,
    6426,
    6462
    };

static const MIDL_STUBLESS_PROXY_INFO IRTCSessionStateChangeEvent2_ProxyInfo =
    {
    &Object_StubDesc,
    __MIDL_ProcFormatString.Format,
    &IRTCSessionStateChangeEvent2_FormatStringOffsetTable[-3],
    0,
    0,
    0
    };


static const MIDL_SERVER_INFO IRTCSessionStateChangeEvent2_ServerInfo = 
    {
    &Object_StubDesc,
    0,
    __MIDL_ProcFormatString.Format,
    &IRTCSessionStateChangeEvent2_FormatStringOffsetTable[-3],
    0,
    0,
    0,
    0};
CINTERFACE_PROXY_VTABLE(15) _IRTCSessionStateChangeEvent2ProxyVtbl = 
{
    &IRTCSessionStateChangeEvent2_ProxyInfo,
    &IID_IRTCSessionStateChangeEvent2,
    IUnknown_QueryInterface_Proxy,
    IUnknown_AddRef_Proxy,
    IUnknown_Release_Proxy ,
    0 /* (void *) (INT_PTR) -1 /* IDispatch::GetTypeInfoCount */ ,
    0 /* (void *) (INT_PTR) -1 /* IDispatch::GetTypeInfo */ ,
    0 /* (void *) (INT_PTR) -1 /* IDispatch::GetIDsOfNames */ ,
    0 /* IDispatch_Invoke_Proxy */ ,
    (void *) (INT_PTR) -1 /* IRTCSessionStateChangeEvent::get_Session */ ,
    (void *) (INT_PTR) -1 /* IRTCSessionStateChangeEvent::get_State */ ,
    (void *) (INT_PTR) -1 /* IRTCSessionStateChangeEvent::get_StatusCode */ ,
    (void *) (INT_PTR) -1 /* IRTCSessionStateChangeEvent::get_StatusText */ ,
    (void *) (INT_PTR) -1 /* IRTCSessionStateChangeEvent2::get_MediaTypes */ ,
    (void *) (INT_PTR) -1 /* IRTCSessionStateChangeEvent2::get_RemotePreferredSecurityLevel */ ,
    (void *) (INT_PTR) -1 /* IRTCSessionStateChangeEvent2::get_IsForked */ ,
    (void *) (INT_PTR) -1 /* IRTCSessionStateChangeEvent2::GetRemoteSessionDescription */
};


static const PRPC_STUB_FUNCTION IRTCSessionStateChangeEvent2_table[] =
{
    STUB_FORWARDING_FUNCTION,
    STUB_FORWARDING_FUNCTION,
    STUB_FORWARDING_FUNCTION,
    STUB_FORWARDING_FUNCTION,
    NdrStubCall2,
    NdrStubCall2,
    NdrStubCall2,
    NdrStubCall2,
    NdrStubCall2,
    NdrStubCall2,
    NdrStubCall2,
    NdrStubCall2
};

CInterfaceStubVtbl _IRTCSessionStateChangeEvent2StubVtbl =
{
    &IID_IRTCSessionStateChangeEvent2,
    &IRTCSessionStateChangeEvent2_ServerInfo,
    15,
    &IRTCSessionStateChangeEvent2_table[-3],
    CStdStubBuffer_DELEGATING_METHODS
};


/* Object interface: IRTCSessionOperationCompleteEvent, ver. 0.0,
   GUID={0xa6bff4c0,0xf7c8,0x4d3c,{0x9a,0x41,0x35,0x50,0xf7,0x8a,0x95,0xb0}} */

#pragma code_seg(".orpc")
static const unsigned short IRTCSessionOperationCompleteEvent_FormatStringOffsetTable[] =
    {
    (unsigned short) -1,
    (unsigned short) -1,
    (unsigned short) -1,
    (unsigned short) -1,
    6060,
    6204,
    204,
    5916
    };

static const MIDL_STUBLESS_PROXY_INFO IRTCSessionOperationCompleteEvent_ProxyInfo =
    {
    &Object_StubDesc,
    __MIDL_ProcFormatString.Format,
    &IRTCSessionOperationCompleteEvent_FormatStringOffsetTable[-3],
    0,
    0,
    0
    };


static const MIDL_SERVER_INFO IRTCSessionOperationCompleteEvent_ServerInfo = 
    {
    &Object_StubDesc,
    0,
    __MIDL_ProcFormatString.Format,
    &IRTCSessionOperationCompleteEvent_FormatStringOffsetTable[-3],
    0,
    0,
    0,
    0};
CINTERFACE_PROXY_VTABLE(11) _IRTCSessionOperationCompleteEventProxyVtbl = 
{
    &IRTCSessionOperationCompleteEvent_ProxyInfo,
    &IID_IRTCSessionOperationCompleteEvent,
    IUnknown_QueryInterface_Proxy,
    IUnknown_AddRef_Proxy,
    IUnknown_Release_Proxy ,
    0 /* (void *) (INT_PTR) -1 /* IDispatch::GetTypeInfoCount */ ,
    0 /* (void *) (INT_PTR) -1 /* IDispatch::GetTypeInfo */ ,
    0 /* (void *) (INT_PTR) -1 /* IDispatch::GetIDsOfNames */ ,
    0 /* IDispatch_Invoke_Proxy */ ,
    (void *) (INT_PTR) -1 /* IRTCSessionOperationCompleteEvent::get_Session */ ,
    (void *) (INT_PTR) -1 /* IRTCSessionOperationCompleteEvent::get_Cookie */ ,
    (void *) (INT_PTR) -1 /* IRTCSessionOperationCompleteEvent::get_StatusCode */ ,
    (void *) (INT_PTR) -1 /* IRTCSessionOperationCompleteEvent::get_StatusText */
};


static const PRPC_STUB_FUNCTION IRTCSessionOperationCompleteEvent_table[] =
{
    STUB_FORWARDING_FUNCTION,
    STUB_FORWARDING_FUNCTION,
    STUB_FORWARDING_FUNCTION,
    STUB_FORWARDING_FUNCTION,
    NdrStubCall2,
    NdrStubCall2,
    NdrStubCall2,
    NdrStubCall2
};

CInterfaceStubVtbl _IRTCSessionOperationCompleteEventStubVtbl =
{
    &IID_IRTCSessionOperationCompleteEvent,
    &IRTCSessionOperationCompleteEvent_ServerInfo,
    11,
    &IRTCSessionOperationCompleteEvent_table[-3],
    CStdStubBuffer_DELEGATING_METHODS
};


/* Object interface: IRTCSessionOperationCompleteEvent2, ver. 0.0,
   GUID={0xf6fc2a9b,0xd5bc,0x4241,{0xb4,0x36,0x1b,0x84,0x60,0xc1,0x38,0x32}} */

#pragma code_seg(".orpc")
static const unsigned short IRTCSessionOperationCompleteEvent2_FormatStringOffsetTable[] =
    {
    (unsigned short) -1,
    (unsigned short) -1,
    (unsigned short) -1,
    (unsigned short) -1,
    6060,
    6204,
    204,
    5916,
    6504,
    6540
    };

static const MIDL_STUBLESS_PROXY_INFO IRTCSessionOperationCompleteEvent2_ProxyInfo =
    {
    &Object_StubDesc,
    __MIDL_ProcFormatString.Format,
    &IRTCSessionOperationCompleteEvent2_FormatStringOffsetTable[-3],
    0,
    0,
    0
    };


static const MIDL_SERVER_INFO IRTCSessionOperationCompleteEvent2_ServerInfo = 
    {
    &Object_StubDesc,
    0,
    __MIDL_ProcFormatString.Format,
    &IRTCSessionOperationCompleteEvent2_FormatStringOffsetTable[-3],
    0,
    0,
    0,
    0};
CINTERFACE_PROXY_VTABLE(13) _IRTCSessionOperationCompleteEvent2ProxyVtbl = 
{
    &IRTCSessionOperationCompleteEvent2_ProxyInfo,
    &IID_IRTCSessionOperationCompleteEvent2,
    IUnknown_QueryInterface_Proxy,
    IUnknown_AddRef_Proxy,
    IUnknown_Release_Proxy ,
    0 /* (void *) (INT_PTR) -1 /* IDispatch::GetTypeInfoCount */ ,
    0 /* (void *) (INT_PTR) -1 /* IDispatch::GetTypeInfo */ ,
    0 /* (void *) (INT_PTR) -1 /* IDispatch::GetIDsOfNames */ ,
    0 /* IDispatch_Invoke_Proxy */ ,
    (void *) (INT_PTR) -1 /* IRTCSessionOperationCompleteEvent::get_Session */ ,
    (void *) (INT_PTR) -1 /* IRTCSessionOperationCompleteEvent::get_Cookie */ ,
    (void *) (INT_PTR) -1 /* IRTCSessionOperationCompleteEvent::get_StatusCode */ ,
    (void *) (INT_PTR) -1 /* IRTCSessionOperationCompleteEvent::get_StatusText */ ,
    (void *) (INT_PTR) -1 /* IRTCSessionOperationCompleteEvent2::get_Participant */ ,
    (void *) (INT_PTR) -1 /* IRTCSessionOperationCompleteEvent2::GetRemoteSessionDescription */
};


static const PRPC_STUB_FUNCTION IRTCSessionOperationCompleteEvent2_table[] =
{
    STUB_FORWARDING_FUNCTION,
    STUB_FORWARDING_FUNCTION,
    STUB_FORWARDING_FUNCTION,
    STUB_FORWARDING_FUNCTION,
    NdrStubCall2,
    NdrStubCall2,
    NdrStubCall2,
    NdrStubCall2,
    NdrStubCall2,
    NdrStubCall2
};

CInterfaceStubVtbl _IRTCSessionOperationCompleteEvent2StubVtbl =
{
    &IID_IRTCSessionOperationCompleteEvent2,
    &IRTCSessionOperationCompleteEvent2_ServerInfo,
    13,
    &IRTCSessionOperationCompleteEvent2_table[-3],
    CStdStubBuffer_DELEGATING_METHODS
};


/* Object interface: IRTCParticipantStateChangeEvent, ver. 0.0,
   GUID={0x09bcb597,0xf0fa,0x48f9,{0xb4,0x20,0x46,0x8c,0xea,0x7f,0xde,0x04}} */

#pragma code_seg(".orpc")
static const unsigned short IRTCParticipantStateChangeEvent_FormatStringOffsetTable[] =
    {
    (unsigned short) -1,
    (unsigned short) -1,
    (unsigned short) -1,
    (unsigned short) -1,
    6582,
    6312,
    204
    };

static const MIDL_STUBLESS_PROXY_INFO IRTCParticipantStateChangeEvent_ProxyInfo =
    {
    &Object_StubDesc,
    __MIDL_ProcFormatString.Format,
    &IRTCParticipantStateChangeEvent_FormatStringOffsetTable[-3],
    0,
    0,
    0
    };


static const MIDL_SERVER_INFO IRTCParticipantStateChangeEvent_ServerInfo = 
    {
    &Object_StubDesc,
    0,
    __MIDL_ProcFormatString.Format,
    &IRTCParticipantStateChangeEvent_FormatStringOffsetTable[-3],
    0,
    0,
    0,
    0};
CINTERFACE_PROXY_VTABLE(10) _IRTCParticipantStateChangeEventProxyVtbl = 
{
    &IRTCParticipantStateChangeEvent_ProxyInfo,
    &IID_IRTCParticipantStateChangeEvent,
    IUnknown_QueryInterface_Proxy,
    IUnknown_AddRef_Proxy,
    IUnknown_Release_Proxy ,
    0 /* (void *) (INT_PTR) -1 /* IDispatch::GetTypeInfoCount */ ,
    0 /* (void *) (INT_PTR) -1 /* IDispatch::GetTypeInfo */ ,
    0 /* (void *) (INT_PTR) -1 /* IDispatch::GetIDsOfNames */ ,
    0 /* IDispatch_Invoke_Proxy */ ,
    (void *) (INT_PTR) -1 /* IRTCParticipantStateChangeEvent::get_Participant */ ,
    (void *) (INT_PTR) -1 /* IRTCParticipantStateChangeEvent::get_State */ ,
    (void *) (INT_PTR) -1 /* IRTCParticipantStateChangeEvent::get_StatusCode */
};


static const PRPC_STUB_FUNCTION IRTCParticipantStateChangeEvent_table[] =
{
    STUB_FORWARDING_FUNCTION,
    STUB_FORWARDING_FUNCTION,
    STUB_FORWARDING_FUNCTION,
    STUB_FORWARDING_FUNCTION,
    NdrStubCall2,
    NdrStubCall2,
    NdrStubCall2
};

CInterfaceStubVtbl _IRTCParticipantStateChangeEventStubVtbl =
{
    &IID_IRTCParticipantStateChangeEvent,
    &IRTCParticipantStateChangeEvent_ServerInfo,
    10,
    &IRTCParticipantStateChangeEvent_table[-3],
    CStdStubBuffer_DELEGATING_METHODS
};


/* Object interface: IRTCMediaEvent, ver. 0.0,
   GUID={0x099944fb,0xbcda,0x453e,{0x8c,0x41,0xe1,0x3d,0xa2,0xad,0xf7,0xf3}} */

#pragma code_seg(".orpc")
static const unsigned short IRTCMediaEvent_FormatStringOffsetTable[] =
    {
    (unsigned short) -1,
    (unsigned short) -1,
    (unsigned short) -1,
    (unsigned short) -1,
    126,
    6312,
    6618
    };

static const MIDL_STUBLESS_PROXY_INFO IRTCMediaEvent_ProxyInfo =
    {
    &Object_StubDesc,
    __MIDL_ProcFormatString.Format,
    &IRTCMediaEvent_FormatStringOffsetTable[-3],
    0,
    0,
    0
    };


static const MIDL_SERVER_INFO IRTCMediaEvent_ServerInfo = 
    {
    &Object_StubDesc,
    0,
    __MIDL_ProcFormatString.Format,
    &IRTCMediaEvent_FormatStringOffsetTable[-3],
    0,
    0,
    0,
    0};
CINTERFACE_PROXY_VTABLE(10) _IRTCMediaEventProxyVtbl = 
{
    &IRTCMediaEvent_ProxyInfo,
    &IID_IRTCMediaEvent,
    IUnknown_QueryInterface_Proxy,
    IUnknown_AddRef_Proxy,
    IUnknown_Release_Proxy ,
    0 /* (void *) (INT_PTR) -1 /* IDispatch::GetTypeInfoCount */ ,
    0 /* (void *) (INT_PTR) -1 /* IDispatch::GetTypeInfo */ ,
    0 /* (void *) (INT_PTR) -1 /* IDispatch::GetIDsOfNames */ ,
    0 /* IDispatch_Invoke_Proxy */ ,
    (void *) (INT_PTR) -1 /* IRTCMediaEvent::get_MediaType */ ,
    (void *) (INT_PTR) -1 /* IRTCMediaEvent::get_EventType */ ,
    (void *) (INT_PTR) -1 /* IRTCMediaEvent::get_EventReason */
};


static const PRPC_STUB_FUNCTION IRTCMediaEvent_table[] =
{
    STUB_FORWARDING_FUNCTION,
    STUB_FORWARDING_FUNCTION,
    STUB_FORWARDING_FUNCTION,
    STUB_FORWARDING_FUNCTION,
    NdrStubCall2,
    NdrStubCall2,
    NdrStubCall2
};

CInterfaceStubVtbl _IRTCMediaEventStubVtbl =
{
    &IID_IRTCMediaEvent,
    &IRTCMediaEvent_ServerInfo,
    10,
    &IRTCMediaEvent_table[-3],
    CStdStubBuffer_DELEGATING_METHODS
};


/* Object interface: IRTCIntensityEvent, ver. 0.0,
   GUID={0x4c23bf51,0x390c,0x4992,{0xa4,0x1d,0x41,0xee,0xc0,0x5b,0x2a,0x4b}} */

#pragma code_seg(".orpc")
static const unsigned short IRTCIntensityEvent_FormatStringOffsetTable[] =
    {
    (unsigned short) -1,
    (unsigned short) -1,
    (unsigned short) -1,
    (unsigned short) -1,
    126,
    6204,
    204,
    6240
    };

static const MIDL_STUBLESS_PROXY_INFO IRTCIntensityEvent_ProxyInfo =
    {
    &Object_StubDesc,
    __MIDL_ProcFormatString.Format,
    &IRTCIntensityEvent_FormatStringOffsetTable[-3],
    0,
    0,
    0
    };


static const MIDL_SERVER_INFO IRTCIntensityEvent_ServerInfo = 
    {
    &Object_StubDesc,
    0,
    __MIDL_ProcFormatString.Format,
    &IRTCIntensityEvent_FormatStringOffsetTable[-3],
    0,
    0,
    0,
    0};
CINTERFACE_PROXY_VTABLE(11) _IRTCIntensityEventProxyVtbl = 
{
    &IRTCIntensityEvent_ProxyInfo,
    &IID_IRTCIntensityEvent,
    IUnknown_QueryInterface_Proxy,
    IUnknown_AddRef_Proxy,
    IUnknown_Release_Proxy ,
    0 /* (void *) (INT_PTR) -1 /* IDispatch::GetTypeInfoCount */ ,
    0 /* (void *) (INT_PTR) -1 /* IDispatch::GetTypeInfo */ ,
    0 /* (void *) (INT_PTR) -1 /* IDispatch::GetIDsOfNames */ ,
    0 /* IDispatch_Invoke_Proxy */ ,
    (void *) (INT_PTR) -1 /* IRTCIntensityEvent::get_Level */ ,
    (void *) (INT_PTR) -1 /* IRTCIntensityEvent::get_Min */ ,
    (void *) (INT_PTR) -1 /* IRTCIntensityEvent::get_Max */ ,
    (void *) (INT_PTR) -1 /* IRTCIntensityEvent::get_Direction */
};


static const PRPC_STUB_FUNCTION IRTCIntensityEvent_table[] =
{
    STUB_FORWARDING_FUNCTION,
    STUB_FORWARDING_FUNCTION,
    STUB_FORWARDING_FUNCTION,
    STUB_FORWARDING_FUNCTION,
    NdrStubCall2,
    NdrStubCall2,
    NdrStubCall2,
    NdrStubCall2
};

CInterfaceStubVtbl _IRTCIntensityEventStubVtbl =
{
    &IID_IRTCIntensityEvent,
    &IRTCIntensityEvent_ServerInfo,
    11,
    &IRTCIntensityEvent_table[-3],
    CStdStubBuffer_DELEGATING_METHODS
};


/* Object interface: IRTCMessagingEvent, ver. 0.0,
   GUID={0xd3609541,0x1b29,0x4de5,{0xa4,0xad,0x5a,0xeb,0xaf,0x31,0x95,0x12}} */

#pragma code_seg(".orpc")
static const unsigned short IRTCMessagingEvent_FormatStringOffsetTable[] =
    {
    (unsigned short) -1,
    (unsigned short) -1,
    (unsigned short) -1,
    (unsigned short) -1,
    6060,
    6654,
    6618,
    5916,
    4152,
    6690
    };

static const MIDL_STUBLESS_PROXY_INFO IRTCMessagingEvent_ProxyInfo =
    {
    &Object_StubDesc,
    __MIDL_ProcFormatString.Format,
    &IRTCMessagingEvent_FormatStringOffsetTable[-3],
    0,
    0,
    0
    };


static const MIDL_SERVER_INFO IRTCMessagingEvent_ServerInfo = 
    {
    &Object_StubDesc,
    0,
    __MIDL_ProcFormatString.Format,
    &IRTCMessagingEvent_FormatStringOffsetTable[-3],
    0,
    0,
    0,
    0};
CINTERFACE_PROXY_VTABLE(13) _IRTCMessagingEventProxyVtbl = 
{
    &IRTCMessagingEvent_ProxyInfo,
    &IID_IRTCMessagingEvent,
    IUnknown_QueryInterface_Proxy,
    IUnknown_AddRef_Proxy,
    IUnknown_Release_Proxy ,
    0 /* (void *) (INT_PTR) -1 /* IDispatch::GetTypeInfoCount */ ,
    0 /* (void *) (INT_PTR) -1 /* IDispatch::GetTypeInfo */ ,
    0 /* (void *) (INT_PTR) -1 /* IDispatch::GetIDsOfNames */ ,
    0 /* IDispatch_Invoke_Proxy */ ,
    (void *) (INT_PTR) -1 /* IRTCMessagingEvent::get_Session */ ,
    (void *) (INT_PTR) -1 /* IRTCMessagingEvent::get_Participant */ ,
    (void *) (INT_PTR) -1 /* IRTCMessagingEvent::get_EventType */ ,
    (void *) (INT_PTR) -1 /* IRTCMessagingEvent::get_Message */ ,
    (void *) (INT_PTR) -1 /* IRTCMessagingEvent::get_MessageHeader */ ,
    (void *) (INT_PTR) -1 /* IRTCMessagingEvent::get_UserStatus */
};


static const PRPC_STUB_FUNCTION IRTCMessagingEvent_table[] =
{
    STUB_FORWARDING_FUNCTION,
    STUB_FORWARDING_FUNCTION,
    STUB_FORWARDING_FUNCTION,
    STUB_FORWARDING_FUNCTION,
    NdrStubCall2,
    NdrStubCall2,
    NdrStubCall2,
    NdrStubCall2,
    NdrStubCall2,
    NdrStubCall2
};

CInterfaceStubVtbl _IRTCMessagingEventStubVtbl =
{
    &IID_IRTCMessagingEvent,
    &IRTCMessagingEvent_ServerInfo,
    13,
    &IRTCMessagingEvent_table[-3],
    CStdStubBuffer_DELEGATING_METHODS
};


/* Object interface: IRTCBuddyEvent, ver. 0.0,
   GUID={0xf36d755d,0x17e6,0x404e,{0x95,0x4f,0x0f,0xc0,0x75,0x74,0xc7,0x8d}} */

#pragma code_seg(".orpc")
static const unsigned short IRTCBuddyEvent_FormatStringOffsetTable[] =
    {
    (unsigned short) -1,
    (unsigned short) -1,
    (unsigned short) -1,
    (unsigned short) -1,
    6726
    };

static const MIDL_STUBLESS_PROXY_INFO IRTCBuddyEvent_ProxyInfo =
    {
    &Object_StubDesc,
    __MIDL_ProcFormatString.Format,
    &IRTCBuddyEvent_FormatStringOffsetTable[-3],
    0,
    0,
    0
    };


static const MIDL_SERVER_INFO IRTCBuddyEvent_ServerInfo = 
    {
    &Object_StubDesc,
    0,
    __MIDL_ProcFormatString.Format,
    &IRTCBuddyEvent_FormatStringOffsetTable[-3],
    0,
    0,
    0,
    0};
CINTERFACE_PROXY_VTABLE(8) _IRTCBuddyEventProxyVtbl = 
{
    &IRTCBuddyEvent_ProxyInfo,
    &IID_IRTCBuddyEvent,
    IUnknown_QueryInterface_Proxy,
    IUnknown_AddRef_Proxy,
    IUnknown_Release_Proxy ,
    0 /* (void *) (INT_PTR) -1 /* IDispatch::GetTypeInfoCount */ ,
    0 /* (void *) (INT_PTR) -1 /* IDispatch::GetTypeInfo */ ,
    0 /* (void *) (INT_PTR) -1 /* IDispatch::GetIDsOfNames */ ,
    0 /* IDispatch_Invoke_Proxy */ ,
    (void *) (INT_PTR) -1 /* IRTCBuddyEvent::get_Buddy */
};


static const PRPC_STUB_FUNCTION IRTCBuddyEvent_table[] =
{
    STUB_FORWARDING_FUNCTION,
    STUB_FORWARDING_FUNCTION,
    STUB_FORWARDING_FUNCTION,
    STUB_FORWARDING_FUNCTION,
    NdrStubCall2
};

CInterfaceStubVtbl _IRTCBuddyEventStubVtbl =
{
    &IID_IRTCBuddyEvent,
    &IRTCBuddyEvent_ServerInfo,
    8,
    &IRTCBuddyEvent_table[-3],
    CStdStubBuffer_DELEGATING_METHODS
};


/* Object interface: IRTCBuddyEvent2, ver. 0.0,
   GUID={0x484A7F1E,0x73F0,0x4990,{0xBF,0xC2,0x60,0xBC,0x39,0x78,0xA7,0x20}} */

#pragma code_seg(".orpc")
static const unsigned short IRTCBuddyEvent2_FormatStringOffsetTable[] =
    {
    (unsigned short) -1,
    (unsigned short) -1,
    (unsigned short) -1,
    (unsigned short) -1,
    6726,
    6312,
    204,
    5916
    };

static const MIDL_STUBLESS_PROXY_INFO IRTCBuddyEvent2_ProxyInfo =
    {
    &Object_StubDesc,
    __MIDL_ProcFormatString.Format,
    &IRTCBuddyEvent2_FormatStringOffsetTable[-3],
    0,
    0,
    0
    };


static const MIDL_SERVER_INFO IRTCBuddyEvent2_ServerInfo = 
    {
    &Object_StubDesc,
    0,
    __MIDL_ProcFormatString.Format,
    &IRTCBuddyEvent2_FormatStringOffsetTable[-3],
    0,
    0,
    0,
    0};
CINTERFACE_PROXY_VTABLE(11) _IRTCBuddyEvent2ProxyVtbl = 
{
    &IRTCBuddyEvent2_ProxyInfo,
    &IID_IRTCBuddyEvent2,
    IUnknown_QueryInterface_Proxy,
    IUnknown_AddRef_Proxy,
    IUnknown_Release_Proxy ,
    0 /* (void *) (INT_PTR) -1 /* IDispatch::GetTypeInfoCount */ ,
    0 /* (void *) (INT_PTR) -1 /* IDispatch::GetTypeInfo */ ,
    0 /* (void *) (INT_PTR) -1 /* IDispatch::GetIDsOfNames */ ,
    0 /* IDispatch_Invoke_Proxy */ ,
    (void *) (INT_PTR) -1 /* IRTCBuddyEvent::get_Buddy */ ,
    (void *) (INT_PTR) -1 /* IRTCBuddyEvent2::get_EventType */ ,
    (void *) (INT_PTR) -1 /* IRTCBuddyEvent2::get_StatusCode */ ,
    (void *) (INT_PTR) -1 /* IRTCBuddyEvent2::get_StatusText */
};


static const PRPC_STUB_FUNCTION IRTCBuddyEvent2_table[] =
{
    STUB_FORWARDING_FUNCTION,
    STUB_FORWARDING_FUNCTION,
    STUB_FORWARDING_FUNCTION,
    STUB_FORWARDING_FUNCTION,
    NdrStubCall2,
    NdrStubCall2,
    NdrStubCall2,
    NdrStubCall2
};

CInterfaceStubVtbl _IRTCBuddyEvent2StubVtbl =
{
    &IID_IRTCBuddyEvent2,
    &IRTCBuddyEvent2_ServerInfo,
    11,
    &IRTCBuddyEvent2_table[-3],
    CStdStubBuffer_DELEGATING_METHODS
};


/* Object interface: IRTCWatcherEvent, ver. 0.0,
   GUID={0xf30d7261,0x587a,0x424f,{0x82,0x2c,0x31,0x27,0x88,0xf4,0x35,0x48}} */

#pragma code_seg(".orpc")
static const unsigned short IRTCWatcherEvent_FormatStringOffsetTable[] =
    {
    (unsigned short) -1,
    (unsigned short) -1,
    (unsigned short) -1,
    (unsigned short) -1,
    6762
    };

static const MIDL_STUBLESS_PROXY_INFO IRTCWatcherEvent_ProxyInfo =
    {
    &Object_StubDesc,
    __MIDL_ProcFormatString.Format,
    &IRTCWatcherEvent_FormatStringOffsetTable[-3],
    0,
    0,
    0
    };


static const MIDL_SERVER_INFO IRTCWatcherEvent_ServerInfo = 
    {
    &Object_StubDesc,
    0,
    __MIDL_ProcFormatString.Format,
    &IRTCWatcherEvent_FormatStringOffsetTable[-3],
    0,
    0,
    0,
    0};
CINTERFACE_PROXY_VTABLE(8) _IRTCWatcherEventProxyVtbl = 
{
    &IRTCWatcherEvent_ProxyInfo,
    &IID_IRTCWatcherEvent,
    IUnknown_QueryInterface_Proxy,
    IUnknown_AddRef_Proxy,
    IUnknown_Release_Proxy ,
    0 /* (void *) (INT_PTR) -1 /* IDispatch::GetTypeInfoCount */ ,
    0 /* (void *) (INT_PTR) -1 /* IDispatch::GetTypeInfo */ ,
    0 /* (void *) (INT_PTR) -1 /* IDispatch::GetIDsOfNames */ ,
    0 /* IDispatch_Invoke_Proxy */ ,
    (void *) (INT_PTR) -1 /* IRTCWatcherEvent::get_Watcher */
};


static const PRPC_STUB_FUNCTION IRTCWatcherEvent_table[] =
{
    STUB_FORWARDING_FUNCTION,
    STUB_FORWARDING_FUNCTION,
    STUB_FORWARDING_FUNCTION,
    STUB_FORWARDING_FUNCTION,
    NdrStubCall2
};

CInterfaceStubVtbl _IRTCWatcherEventStubVtbl =
{
    &IID_IRTCWatcherEvent,
    &IRTCWatcherEvent_ServerInfo,
    8,
    &IRTCWatcherEvent_table[-3],
    CStdStubBuffer_DELEGATING_METHODS
};


/* Object interface: IRTCWatcherEvent2, ver. 0.0,
   GUID={0xE52891E8,0x188C,0x49AF,{0xB0,0x05,0x98,0xED,0x13,0xF8,0x3F,0x9C}} */

#pragma code_seg(".orpc")
static const unsigned short IRTCWatcherEvent2_FormatStringOffsetTable[] =
    {
    (unsigned short) -1,
    (unsigned short) -1,
    (unsigned short) -1,
    (unsigned short) -1,
    6762,
    6312,
    204
    };

static const MIDL_STUBLESS_PROXY_INFO IRTCWatcherEvent2_ProxyInfo =
    {
    &Object_StubDesc,
    __MIDL_ProcFormatString.Format,
    &IRTCWatcherEvent2_FormatStringOffsetTable[-3],
    0,
    0,
    0
    };


static const MIDL_SERVER_INFO IRTCWatcherEvent2_ServerInfo = 
    {
    &Object_StubDesc,
    0,
    __MIDL_ProcFormatString.Format,
    &IRTCWatcherEvent2_FormatStringOffsetTable[-3],
    0,
    0,
    0,
    0};
CINTERFACE_PROXY_VTABLE(10) _IRTCWatcherEvent2ProxyVtbl = 
{
    &IRTCWatcherEvent2_ProxyInfo,
    &IID_IRTCWatcherEvent2,
    IUnknown_QueryInterface_Proxy,
    IUnknown_AddRef_Proxy,
    IUnknown_Release_Proxy ,
    0 /* (void *) (INT_PTR) -1 /* IDispatch::GetTypeInfoCount */ ,
    0 /* (void *) (INT_PTR) -1 /* IDispatch::GetTypeInfo */ ,
    0 /* (void *) (INT_PTR) -1 /* IDispatch::GetIDsOfNames */ ,
    0 /* IDispatch_Invoke_Proxy */ ,
    (void *) (INT_PTR) -1 /* IRTCWatcherEvent::get_Watcher */ ,
    (void *) (INT_PTR) -1 /* IRTCWatcherEvent2::get_EventType */ ,
    (void *) (INT_PTR) -1 /* IRTCWatcherEvent2::get_StatusCode */
};


static const PRPC_STUB_FUNCTION IRTCWatcherEvent2_table[] =
{
    STUB_FORWARDING_FUNCTION,
    STUB_FORWARDING_FUNCTION,
    STUB_FORWARDING_FUNCTION,
    STUB_FORWARDING_FUNCTION,
    NdrStubCall2,
    NdrStubCall2,
    NdrStubCall2
};

CInterfaceStubVtbl _IRTCWatcherEvent2StubVtbl =
{
    &IID_IRTCWatcherEvent2,
    &IRTCWatcherEvent2_ServerInfo,
    10,
    &IRTCWatcherEvent2_table[-3],
    CStdStubBuffer_DELEGATING_METHODS
};


/* Object interface: IRTCBuddyGroupEvent, ver. 0.0,
   GUID={0x3A79E1D1,0xB736,0x4414,{0x96,0xF8,0xBB,0xC7,0xF0,0x88,0x63,0xE4}} */

#pragma code_seg(".orpc")
static const unsigned short IRTCBuddyGroupEvent_FormatStringOffsetTable[] =
    {
    (unsigned short) -1,
    (unsigned short) -1,
    (unsigned short) -1,
    (unsigned short) -1,
    6096,
    6798,
    6834,
    240
    };

static const MIDL_STUBLESS_PROXY_INFO IRTCBuddyGroupEvent_ProxyInfo =
    {
    &Object_StubDesc,
    __MIDL_ProcFormatString.Format,
    &IRTCBuddyGroupEvent_FormatStringOffsetTable[-3],
    0,
    0,
    0
    };


static const MIDL_SERVER_INFO IRTCBuddyGroupEvent_ServerInfo = 
    {
    &Object_StubDesc,
    0,
    __MIDL_ProcFormatString.Format,
    &IRTCBuddyGroupEvent_FormatStringOffsetTable[-3],
    0,
    0,
    0,
    0};
CINTERFACE_PROXY_VTABLE(11) _IRTCBuddyGroupEventProxyVtbl = 
{
    &IRTCBuddyGroupEvent_ProxyInfo,
    &IID_IRTCBuddyGroupEvent,
    IUnknown_QueryInterface_Proxy,
    IUnknown_AddRef_Proxy,
    IUnknown_Release_Proxy ,
    0 /* (void *) (INT_PTR) -1 /* IDispatch::GetTypeInfoCount */ ,
    0 /* (void *) (INT_PTR) -1 /* IDispatch::GetTypeInfo */ ,
    0 /* (void *) (INT_PTR) -1 /* IDispatch::GetIDsOfNames */ ,
    0 /* IDispatch_Invoke_Proxy */ ,
    (void *) (INT_PTR) -1 /* IRTCBuddyGroupEvent::get_EventType */ ,
    (void *) (INT_PTR) -1 /* IRTCBuddyGroupEvent::get_Group */ ,
    (void *) (INT_PTR) -1 /* IRTCBuddyGroupEvent::get_Buddy */ ,
    (void *) (INT_PTR) -1 /* IRTCBuddyGroupEvent::get_StatusCode */
};


static const PRPC_STUB_FUNCTION IRTCBuddyGroupEvent_table[] =
{
    STUB_FORWARDING_FUNCTION,
    STUB_FORWARDING_FUNCTION,
    STUB_FORWARDING_FUNCTION,
    STUB_FORWARDING_FUNCTION,
    NdrStubCall2,
    NdrStubCall2,
    NdrStubCall2,
    NdrStubCall2
};

CInterfaceStubVtbl _IRTCBuddyGroupEventStubVtbl =
{
    &IID_IRTCBuddyGroupEvent,
    &IRTCBuddyGroupEvent_ServerInfo,
    11,
    &IRTCBuddyGroupEvent_table[-3],
    CStdStubBuffer_DELEGATING_METHODS
};


/* Object interface: IRTCInfoEvent, ver. 0.0,
   GUID={0x4E1D68AE,0x1912,0x4f49,{0xB2,0xC3,0x59,0x4F,0xAD,0xFD,0x42,0x5F}} */

#pragma code_seg(".orpc")
static const unsigned short IRTCInfoEvent_FormatStringOffsetTable[] =
    {
    (unsigned short) -1,
    (unsigned short) -1,
    (unsigned short) -1,
    (unsigned short) -1,
    6870,
    6906,
    4080,
    5916
    };

static const MIDL_STUBLESS_PROXY_INFO IRTCInfoEvent_ProxyInfo =
    {
    &Object_StubDesc,
    __MIDL_ProcFormatString.Format,
    &IRTCInfoEvent_FormatStringOffsetTable[-3],
    0,
    0,
    0
    };


static const MIDL_SERVER_INFO IRTCInfoEvent_ServerInfo = 
    {
    &Object_StubDesc,
    0,
    __MIDL_ProcFormatString.Format,
    &IRTCInfoEvent_FormatStringOffsetTable[-3],
    0,
    0,
    0,
    0};
CINTERFACE_PROXY_VTABLE(11) _IRTCInfoEventProxyVtbl = 
{
    &IRTCInfoEvent_ProxyInfo,
    &IID_IRTCInfoEvent,
    IUnknown_QueryInterface_Proxy,
    IUnknown_AddRef_Proxy,
    IUnknown_Release_Proxy ,
    0 /* (void *) (INT_PTR) -1 /* IDispatch::GetTypeInfoCount */ ,
    0 /* (void *) (INT_PTR) -1 /* IDispatch::GetTypeInfo */ ,
    0 /* (void *) (INT_PTR) -1 /* IDispatch::GetIDsOfNames */ ,
    0 /* IDispatch_Invoke_Proxy */ ,
    (void *) (INT_PTR) -1 /* IRTCInfoEvent::get_Session */ ,
    (void *) (INT_PTR) -1 /* IRTCInfoEvent::get_Participant */ ,
    (void *) (INT_PTR) -1 /* IRTCInfoEvent::get_Info */ ,
    (void *) (INT_PTR) -1 /* IRTCInfoEvent::get_InfoHeader */
};


static const PRPC_STUB_FUNCTION IRTCInfoEvent_table[] =
{
    STUB_FORWARDING_FUNCTION,
    STUB_FORWARDING_FUNCTION,
    STUB_FORWARDING_FUNCTION,
    STUB_FORWARDING_FUNCTION,
    NdrStubCall2,
    NdrStubCall2,
    NdrStubCall2,
    NdrStubCall2
};

CInterfaceStubVtbl _IRTCInfoEventStubVtbl =
{
    &IID_IRTCInfoEvent,
    &IRTCInfoEvent_ServerInfo,
    11,
    &IRTCInfoEvent_table[-3],
    CStdStubBuffer_DELEGATING_METHODS
};


/* Object interface: IRTCMediaRequestEvent, ver. 0.0,
   GUID={0x52572D15,0x148C,0x4d97,{0xA3,0x6C,0x2D,0xA5,0x5C,0x28,0x9D,0x63}} */

#pragma code_seg(".orpc")
static const unsigned short IRTCMediaRequestEvent_FormatStringOffsetTable[] =
    {
    (unsigned short) -1,
    (unsigned short) -1,
    (unsigned short) -1,
    (unsigned short) -1,
    6870,
    6204,
    204,
    6942,
    6978,
    7020,
    372
    };

static const MIDL_STUBLESS_PROXY_INFO IRTCMediaRequestEvent_ProxyInfo =
    {
    &Object_StubDesc,
    __MIDL_ProcFormatString.Format,
    &IRTCMediaRequestEvent_FormatStringOffsetTable[-3],
    0,
    0,
    0
    };


static const MIDL_SERVER_INFO IRTCMediaRequestEvent_ServerInfo = 
    {
    &Object_StubDesc,
    0,
    __MIDL_ProcFormatString.Format,
    &IRTCMediaRequestEvent_FormatStringOffsetTable[-3],
    0,
    0,
    0,
    0};
CINTERFACE_PROXY_VTABLE(14) _IRTCMediaRequestEventProxyVtbl = 
{
    &IRTCMediaRequestEvent_ProxyInfo,
    &IID_IRTCMediaRequestEvent,
    IUnknown_QueryInterface_Proxy,
    IUnknown_AddRef_Proxy,
    IUnknown_Release_Proxy ,
    0 /* (void *) (INT_PTR) -1 /* IDispatch::GetTypeInfoCount */ ,
    0 /* (void *) (INT_PTR) -1 /* IDispatch::GetTypeInfo */ ,
    0 /* (void *) (INT_PTR) -1 /* IDispatch::GetIDsOfNames */ ,
    0 /* IDispatch_Invoke_Proxy */ ,
    (void *) (INT_PTR) -1 /* IRTCMediaRequestEvent::get_Session */ ,
    (void *) (INT_PTR) -1 /* IRTCMediaRequestEvent::get_ProposedMedia */ ,
    (void *) (INT_PTR) -1 /* IRTCMediaRequestEvent::get_CurrentMedia */ ,
    (void *) (INT_PTR) -1 /* IRTCMediaRequestEvent::Accept */ ,
    (void *) (INT_PTR) -1 /* IRTCMediaRequestEvent::get_RemotePreferredSecurityLevel */ ,
    (void *) (INT_PTR) -1 /* IRTCMediaRequestEvent::Reject */ ,
    (void *) (INT_PTR) -1 /* IRTCMediaRequestEvent::get_State */
};


static const PRPC_STUB_FUNCTION IRTCMediaRequestEvent_table[] =
{
    STUB_FORWARDING_FUNCTION,
    STUB_FORWARDING_FUNCTION,
    STUB_FORWARDING_FUNCTION,
    STUB_FORWARDING_FUNCTION,
    NdrStubCall2,
    NdrStubCall2,
    NdrStubCall2,
    NdrStubCall2,
    NdrStubCall2,
    NdrStubCall2,
    NdrStubCall2
};

CInterfaceStubVtbl _IRTCMediaRequestEventStubVtbl =
{
    &IID_IRTCMediaRequestEvent,
    &IRTCMediaRequestEvent_ServerInfo,
    14,
    &IRTCMediaRequestEvent_table[-3],
    CStdStubBuffer_DELEGATING_METHODS
};


/* Object interface: IRTCReInviteEvent, ver. 0.0,
   GUID={0x11558D84,0x204C,0x43e7,{0x99,0xB0,0x20,0x34,0xE9,0x41,0x7F,0x7D}} */

#pragma code_seg(".orpc")
static const unsigned short IRTCReInviteEvent_FormatStringOffsetTable[] =
    {
    (unsigned short) -1,
    (unsigned short) -1,
    (unsigned short) -1,
    (unsigned short) -1,
    6870,
    7050,
    7092,
    6240,
    7122
    };

static const MIDL_STUBLESS_PROXY_INFO IRTCReInviteEvent_ProxyInfo =
    {
    &Object_StubDesc,
    __MIDL_ProcFormatString.Format,
    &IRTCReInviteEvent_FormatStringOffsetTable[-3],
    0,
    0,
    0
    };


static const MIDL_SERVER_INFO IRTCReInviteEvent_ServerInfo = 
    {
    &Object_StubDesc,
    0,
    __MIDL_ProcFormatString.Format,
    &IRTCReInviteEvent_FormatStringOffsetTable[-3],
    0,
    0,
    0,
    0};
CINTERFACE_PROXY_VTABLE(12) _IRTCReInviteEventProxyVtbl = 
{
    &IRTCReInviteEvent_ProxyInfo,
    &IID_IRTCReInviteEvent,
    IUnknown_QueryInterface_Proxy,
    IUnknown_AddRef_Proxy,
    IUnknown_Release_Proxy ,
    0 /* (void *) (INT_PTR) -1 /* IDispatch::GetTypeInfoCount */ ,
    0 /* (void *) (INT_PTR) -1 /* IDispatch::GetTypeInfo */ ,
    0 /* (void *) (INT_PTR) -1 /* IDispatch::GetIDsOfNames */ ,
    0 /* IDispatch_Invoke_Proxy */ ,
    (void *) (INT_PTR) -1 /* IRTCReInviteEvent::get_Session */ ,
    (void *) (INT_PTR) -1 /* IRTCReInviteEvent::Accept */ ,
    (void *) (INT_PTR) -1 /* IRTCReInviteEvent::Reject */ ,
    (void *) (INT_PTR) -1 /* IRTCReInviteEvent::get_State */ ,
    (void *) (INT_PTR) -1 /* IRTCReInviteEvent::GetRemoteSessionDescription */
};


static const PRPC_STUB_FUNCTION IRTCReInviteEvent_table[] =
{
    STUB_FORWARDING_FUNCTION,
    STUB_FORWARDING_FUNCTION,
    STUB_FORWARDING_FUNCTION,
    STUB_FORWARDING_FUNCTION,
    NdrStubCall2,
    NdrStubCall2,
    NdrStubCall2,
    NdrStubCall2,
    NdrStubCall2
};

CInterfaceStubVtbl _IRTCReInviteEventStubVtbl =
{
    &IID_IRTCReInviteEvent,
    &IRTCReInviteEvent_ServerInfo,
    12,
    &IRTCReInviteEvent_table[-3],
    CStdStubBuffer_DELEGATING_METHODS
};


/* Object interface: IRTCPresencePropertyEvent, ver. 0.0,
   GUID={0xF777F570,0xA820,0x49d5,{0x86,0xBD,0xE0,0x99,0x49,0x3F,0x15,0x18}} */

#pragma code_seg(".orpc")
static const unsigned short IRTCPresencePropertyEvent_FormatStringOffsetTable[] =
    {
    (unsigned short) -1,
    (unsigned short) -1,
    (unsigned short) -1,
    (unsigned short) -1,
    126,
    4044,
    6618,
    5916
    };

static const MIDL_STUBLESS_PROXY_INFO IRTCPresencePropertyEvent_ProxyInfo =
    {
    &Object_StubDesc,
    __MIDL_ProcFormatString.Format,
    &IRTCPresencePropertyEvent_FormatStringOffsetTable[-3],
    0,
    0,
    0
    };


static const MIDL_SERVER_INFO IRTCPresencePropertyEvent_ServerInfo = 
    {
    &Object_StubDesc,
    0,
    __MIDL_ProcFormatString.Format,
    &IRTCPresencePropertyEvent_FormatStringOffsetTable[-3],
    0,
    0,
    0,
    0};
CINTERFACE_PROXY_VTABLE(11) _IRTCPresencePropertyEventProxyVtbl = 
{
    &IRTCPresencePropertyEvent_ProxyInfo,
    &IID_IRTCPresencePropertyEvent,
    IUnknown_QueryInterface_Proxy,
    IUnknown_AddRef_Proxy,
    IUnknown_Release_Proxy ,
    0 /* (void *) (INT_PTR) -1 /* IDispatch::GetTypeInfoCount */ ,
    0 /* (void *) (INT_PTR) -1 /* IDispatch::GetTypeInfo */ ,
    0 /* (void *) (INT_PTR) -1 /* IDispatch::GetIDsOfNames */ ,
    0 /* IDispatch_Invoke_Proxy */ ,
    (void *) (INT_PTR) -1 /* IRTCPresencePropertyEvent::get_StatusCode */ ,
    (void *) (INT_PTR) -1 /* IRTCPresencePropertyEvent::get_StatusText */ ,
    (void *) (INT_PTR) -1 /* IRTCPresencePropertyEvent::get_PresenceProperty */ ,
    (void *) (INT_PTR) -1 /* IRTCPresencePropertyEvent::get_Value */
};


static const PRPC_STUB_FUNCTION IRTCPresencePropertyEvent_table[] =
{
    STUB_FORWARDING_FUNCTION,
    STUB_FORWARDING_FUNCTION,
    STUB_FORWARDING_FUNCTION,
    STUB_FORWARDING_FUNCTION,
    NdrStubCall2,
    NdrStubCall2,
    NdrStubCall2,
    NdrStubCall2
};

CInterfaceStubVtbl _IRTCPresencePropertyEventStubVtbl =
{
    &IID_IRTCPresencePropertyEvent,
    &IRTCPresencePropertyEvent_ServerInfo,
    11,
    &IRTCPresencePropertyEvent_table[-3],
    CStdStubBuffer_DELEGATING_METHODS
};


/* Object interface: IRTCPresenceDataEvent, ver. 0.0,
   GUID={0x38F0E78C,0x8B87,0x4c04,{0xA8,0x2D,0xAE,0xDD,0x83,0xC9,0x09,0xBB}} */

#pragma code_seg(".orpc")
static const unsigned short IRTCPresenceDataEvent_FormatStringOffsetTable[] =
    {
    (unsigned short) -1,
    (unsigned short) -1,
    (unsigned short) -1,
    (unsigned short) -1,
    126,
    4044,
    7164
    };

static const MIDL_STUBLESS_PROXY_INFO IRTCPresenceDataEvent_ProxyInfo =
    {
    &Object_StubDesc,
    __MIDL_ProcFormatString.Format,
    &IRTCPresenceDataEvent_FormatStringOffsetTable[-3],
    0,
    0,
    0
    };


static const MIDL_SERVER_INFO IRTCPresenceDataEvent_ServerInfo = 
    {
    &Object_StubDesc,
    0,
    __MIDL_ProcFormatString.Format,
    &IRTCPresenceDataEvent_FormatStringOffsetTable[-3],
    0,
    0,
    0,
    0};
CINTERFACE_PROXY_VTABLE(10) _IRTCPresenceDataEventProxyVtbl = 
{
    &IRTCPresenceDataEvent_ProxyInfo,
    &IID_IRTCPresenceDataEvent,
    IUnknown_QueryInterface_Proxy,
    IUnknown_AddRef_Proxy,
    IUnknown_Release_Proxy ,
    0 /* (void *) (INT_PTR) -1 /* IDispatch::GetTypeInfoCount */ ,
    0 /* (void *) (INT_PTR) -1 /* IDispatch::GetTypeInfo */ ,
    0 /* (void *) (INT_PTR) -1 /* IDispatch::GetIDsOfNames */ ,
    0 /* IDispatch_Invoke_Proxy */ ,
    (void *) (INT_PTR) -1 /* IRTCPresenceDataEvent::get_StatusCode */ ,
    (void *) (INT_PTR) -1 /* IRTCPresenceDataEvent::get_StatusText */ ,
    (void *) (INT_PTR) -1 /* IRTCPresenceDataEvent::GetPresenceData */
};


static const PRPC_STUB_FUNCTION IRTCPresenceDataEvent_table[] =
{
    STUB_FORWARDING_FUNCTION,
    STUB_FORWARDING_FUNCTION,
    STUB_FORWARDING_FUNCTION,
    STUB_FORWARDING_FUNCTION,
    NdrStubCall2,
    NdrStubCall2,
    NdrStubCall2
};

CInterfaceStubVtbl _IRTCPresenceDataEventStubVtbl =
{
    &IID_IRTCPresenceDataEvent,
    &IRTCPresenceDataEvent_ServerInfo,
    10,
    &IRTCPresenceDataEvent_table[-3],
    CStdStubBuffer_DELEGATING_METHODS
};


/* Object interface: IRTCPresenceStatusEvent, ver. 0.0,
   GUID={0x78673F32,0x4A0F,0x462c,{0x89,0xAA,0xEE,0x77,0x06,0x70,0x76,0x78}} */

#pragma code_seg(".orpc")
static const unsigned short IRTCPresenceStatusEvent_FormatStringOffsetTable[] =
    {
    (unsigned short) -1,
    (unsigned short) -1,
    (unsigned short) -1,
    (unsigned short) -1,
    126,
    4044,
    7206
    };

static const MIDL_STUBLESS_PROXY_INFO IRTCPresenceStatusEvent_ProxyInfo =
    {
    &Object_StubDesc,
    __MIDL_ProcFormatString.Format,
    &IRTCPresenceStatusEvent_FormatStringOffsetTable[-3],
    0,
    0,
    0
    };


static const MIDL_SERVER_INFO IRTCPresenceStatusEvent_ServerInfo = 
    {
    &Object_StubDesc,
    0,
    __MIDL_ProcFormatString.Format,
    &IRTCPresenceStatusEvent_FormatStringOffsetTable[-3],
    0,
    0,
    0,
    0};
CINTERFACE_PROXY_VTABLE(10) _IRTCPresenceStatusEventProxyVtbl = 
{
    &IRTCPresenceStatusEvent_ProxyInfo,
    &IID_IRTCPresenceStatusEvent,
    IUnknown_QueryInterface_Proxy,
    IUnknown_AddRef_Proxy,
    IUnknown_Release_Proxy ,
    0 /* (void *) (INT_PTR) -1 /* IDispatch::GetTypeInfoCount */ ,
    0 /* (void *) (INT_PTR) -1 /* IDispatch::GetTypeInfo */ ,
    0 /* (void *) (INT_PTR) -1 /* IDispatch::GetIDsOfNames */ ,
    0 /* IDispatch_Invoke_Proxy */ ,
    (void *) (INT_PTR) -1 /* IRTCPresenceStatusEvent::get_StatusCode */ ,
    (void *) (INT_PTR) -1 /* IRTCPresenceStatusEvent::get_StatusText */ ,
    (void *) (INT_PTR) -1 /* IRTCPresenceStatusEvent::GetLocalPresenceInfo */
};


static const PRPC_STUB_FUNCTION IRTCPresenceStatusEvent_table[] =
{
    STUB_FORWARDING_FUNCTION,
    STUB_FORWARDING_FUNCTION,
    STUB_FORWARDING_FUNCTION,
    STUB_FORWARDING_FUNCTION,
    NdrStubCall2,
    NdrStubCall2,
    NdrStubCall2
};

CInterfaceStubVtbl _IRTCPresenceStatusEventStubVtbl =
{
    &IID_IRTCPresenceStatusEvent,
    &IRTCPresenceStatusEvent_ServerInfo,
    10,
    &IRTCPresenceStatusEvent_table[-3],
    CStdStubBuffer_DELEGATING_METHODS
};


/* Object interface: IRTCCollection, ver. 0.0,
   GUID={0xEC7C8096,0xB918,0x4044,{0x94,0xF1,0xE4,0xFB,0xA0,0x36,0x1D,0x5C}} */

#pragma code_seg(".orpc")
static const unsigned short IRTCCollection_FormatStringOffsetTable[] =
    {
    (unsigned short) -1,
    (unsigned short) -1,
    (unsigned short) -1,
    (unsigned short) -1,
    126,
    7248,
    7290
    };

static const MIDL_STUBLESS_PROXY_INFO IRTCCollection_ProxyInfo =
    {
    &Object_StubDesc,
    __MIDL_ProcFormatString.Format,
    &IRTCCollection_FormatStringOffsetTable[-3],
    0,
    0,
    0
    };


static const MIDL_SERVER_INFO IRTCCollection_ServerInfo = 
    {
    &Object_StubDesc,
    0,
    __MIDL_ProcFormatString.Format,
    &IRTCCollection_FormatStringOffsetTable[-3],
    0,
    0,
    0,
    0};
CINTERFACE_PROXY_VTABLE(10) _IRTCCollectionProxyVtbl = 
{
    &IRTCCollection_ProxyInfo,
    &IID_IRTCCollection,
    IUnknown_QueryInterface_Proxy,
    IUnknown_AddRef_Proxy,
    IUnknown_Release_Proxy ,
    0 /* (void *) (INT_PTR) -1 /* IDispatch::GetTypeInfoCount */ ,
    0 /* (void *) (INT_PTR) -1 /* IDispatch::GetTypeInfo */ ,
    0 /* (void *) (INT_PTR) -1 /* IDispatch::GetIDsOfNames */ ,
    0 /* IDispatch_Invoke_Proxy */ ,
    (void *) (INT_PTR) -1 /* IRTCCollection::get_Count */ ,
    (void *) (INT_PTR) -1 /* IRTCCollection::get_Item */ ,
    (void *) (INT_PTR) -1 /* IRTCCollection::get__NewEnum */
};


static const PRPC_STUB_FUNCTION IRTCCollection_table[] =
{
    STUB_FORWARDING_FUNCTION,
    STUB_FORWARDING_FUNCTION,
    STUB_FORWARDING_FUNCTION,
    STUB_FORWARDING_FUNCTION,
    NdrStubCall2,
    NdrStubCall2,
    NdrStubCall2
};

CInterfaceStubVtbl _IRTCCollectionStubVtbl =
{
    &IID_IRTCCollection,
    &IRTCCollection_ServerInfo,
    10,
    &IRTCCollection_table[-3],
    CStdStubBuffer_DELEGATING_METHODS
};


/* Object interface: IRTCEnumParticipants, ver. 0.0,
   GUID={0xfcd56f29,0x4a4f,0x41b2,{0xba,0x5c,0xf5,0xbc,0xcc,0x06,0x0b,0xf6}} */

#pragma code_seg(".orpc")
static const unsigned short IRTCEnumParticipants_FormatStringOffsetTable[] =
    {
    7326,
    30,
    7374,
    7410
    };

static const MIDL_STUBLESS_PROXY_INFO IRTCEnumParticipants_ProxyInfo =
    {
    &Object_StubDesc,
    __MIDL_ProcFormatString.Format,
    &IRTCEnumParticipants_FormatStringOffsetTable[-3],
    0,
    0,
    0
    };


static const MIDL_SERVER_INFO IRTCEnumParticipants_ServerInfo = 
    {
    &Object_StubDesc,
    0,
    __MIDL_ProcFormatString.Format,
    &IRTCEnumParticipants_FormatStringOffsetTable[-3],
    0,
    0,
    0,
    0};
CINTERFACE_PROXY_VTABLE(7) _IRTCEnumParticipantsProxyVtbl = 
{
    &IRTCEnumParticipants_ProxyInfo,
    &IID_IRTCEnumParticipants,
    IUnknown_QueryInterface_Proxy,
    IUnknown_AddRef_Proxy,
    IUnknown_Release_Proxy ,
    (void *) (INT_PTR) -1 /* IRTCEnumParticipants::Next */ ,
    (void *) (INT_PTR) -1 /* IRTCEnumParticipants::Reset */ ,
    (void *) (INT_PTR) -1 /* IRTCEnumParticipants::Skip */ ,
    (void *) (INT_PTR) -1 /* IRTCEnumParticipants::Clone */
};

const CInterfaceStubVtbl _IRTCEnumParticipantsStubVtbl =
{
    &IID_IRTCEnumParticipants,
    &IRTCEnumParticipants_ServerInfo,
    7,
    0, /* pure interpreted */
    CStdStubBuffer_METHODS
};


/* Object interface: IRTCEnumProfiles, ver. 0.0,
   GUID={0x29b7c41c,0xed82,0x4bca,{0x84,0xad,0x39,0xd5,0x10,0x1b,0x58,0xe3}} */

#pragma code_seg(".orpc")
static const unsigned short IRTCEnumProfiles_FormatStringOffsetTable[] =
    {
    7446,
    30,
    7374,
    3708
    };

static const MIDL_STUBLESS_PROXY_INFO IRTCEnumProfiles_ProxyInfo =
    {
    &Object_StubDesc,
    __MIDL_ProcFormatString.Format,
    &IRTCEnumProfiles_FormatStringOffsetTable[-3],
    0,
    0,
    0
    };


static const MIDL_SERVER_INFO IRTCEnumProfiles_ServerInfo = 
    {
    &Object_StubDesc,
    0,
    __MIDL_ProcFormatString.Format,
    &IRTCEnumProfiles_FormatStringOffsetTable[-3],
    0,
    0,
    0,
    0};
CINTERFACE_PROXY_VTABLE(7) _IRTCEnumProfilesProxyVtbl = 
{
    &IRTCEnumProfiles_ProxyInfo,
    &IID_IRTCEnumProfiles,
    IUnknown_QueryInterface_Proxy,
    IUnknown_AddRef_Proxy,
    IUnknown_Release_Proxy ,
    (void *) (INT_PTR) -1 /* IRTCEnumProfiles::Next */ ,
    (void *) (INT_PTR) -1 /* IRTCEnumProfiles::Reset */ ,
    (void *) (INT_PTR) -1 /* IRTCEnumProfiles::Skip */ ,
    (void *) (INT_PTR) -1 /* IRTCEnumProfiles::Clone */
};

const CInterfaceStubVtbl _IRTCEnumProfilesStubVtbl =
{
    &IID_IRTCEnumProfiles,
    &IRTCEnumProfiles_ServerInfo,
    7,
    0, /* pure interpreted */
    CStdStubBuffer_METHODS
};


/* Object interface: IRTCEnumBuddies, ver. 0.0,
   GUID={0xf7296917,0x5569,0x4b3b,{0xb3,0xaf,0x98,0xd1,0x14,0x4b,0x2b,0x87}} */

#pragma code_seg(".orpc")
static const unsigned short IRTCEnumBuddies_FormatStringOffsetTable[] =
    {
    7494,
    30,
    7374,
    7542
    };

static const MIDL_STUBLESS_PROXY_INFO IRTCEnumBuddies_ProxyInfo =
    {
    &Object_StubDesc,
    __MIDL_ProcFormatString.Format,
    &IRTCEnumBuddies_FormatStringOffsetTable[-3],
    0,
    0,
    0
    };


static const MIDL_SERVER_INFO IRTCEnumBuddies_ServerInfo = 
    {
    &Object_StubDesc,
    0,
    __MIDL_ProcFormatString.Format,
    &IRTCEnumBuddies_FormatStringOffsetTable[-3],
    0,
    0,
    0,
    0};
CINTERFACE_PROXY_VTABLE(7) _IRTCEnumBuddiesProxyVtbl = 
{
    &IRTCEnumBuddies_ProxyInfo,
    &IID_IRTCEnumBuddies,
    IUnknown_QueryInterface_Proxy,
    IUnknown_AddRef_Proxy,
    IUnknown_Release_Proxy ,
    (void *) (INT_PTR) -1 /* IRTCEnumBuddies::Next */ ,
    (void *) (INT_PTR) -1 /* IRTCEnumBuddies::Reset */ ,
    (void *) (INT_PTR) -1 /* IRTCEnumBuddies::Skip */ ,
    (void *) (INT_PTR) -1 /* IRTCEnumBuddies::Clone */
};

const CInterfaceStubVtbl _IRTCEnumBuddiesStubVtbl =
{
    &IID_IRTCEnumBuddies,
    &IRTCEnumBuddies_ServerInfo,
    7,
    0, /* pure interpreted */
    CStdStubBuffer_METHODS
};


/* Object interface: IRTCEnumWatchers, ver. 0.0,
   GUID={0xa87d55d7,0xdb74,0x4ed1,{0x9c,0xa4,0x77,0xa0,0xe4,0x1b,0x41,0x3e}} */

#pragma code_seg(".orpc")
static const unsigned short IRTCEnumWatchers_FormatStringOffsetTable[] =
    {
    7578,
    30,
    7374,
    7626
    };

static const MIDL_STUBLESS_PROXY_INFO IRTCEnumWatchers_ProxyInfo =
    {
    &Object_StubDesc,
    __MIDL_ProcFormatString.Format,
    &IRTCEnumWatchers_FormatStringOffsetTable[-3],
    0,
    0,
    0
    };


static const MIDL_SERVER_INFO IRTCEnumWatchers_ServerInfo = 
    {
    &Object_StubDesc,
    0,
    __MIDL_ProcFormatString.Format,
    &IRTCEnumWatchers_FormatStringOffsetTable[-3],
    0,
    0,
    0,
    0};
CINTERFACE_PROXY_VTABLE(7) _IRTCEnumWatchersProxyVtbl = 
{
    &IRTCEnumWatchers_ProxyInfo,
    &IID_IRTCEnumWatchers,
    IUnknown_QueryInterface_Proxy,
    IUnknown_AddRef_Proxy,
    IUnknown_Release_Proxy ,
    (void *) (INT_PTR) -1 /* IRTCEnumWatchers::Next */ ,
    (void *) (INT_PTR) -1 /* IRTCEnumWatchers::Reset */ ,
    (void *) (INT_PTR) -1 /* IRTCEnumWatchers::Skip */ ,
    (void *) (INT_PTR) -1 /* IRTCEnumWatchers::Clone */
};

const CInterfaceStubVtbl _IRTCEnumWatchersStubVtbl =
{
    &IID_IRTCEnumWatchers,
    &IRTCEnumWatchers_ServerInfo,
    7,
    0, /* pure interpreted */
    CStdStubBuffer_METHODS
};


/* Object interface: IRTCEnumGroups, ver. 0.0,
   GUID={0x742378D6,0xA141,0x4415,{0x8F,0x27,0x35,0xD9,0x90,0x76,0xCF,0x5D}} */

#pragma code_seg(".orpc")
static const unsigned short IRTCEnumGroups_FormatStringOffsetTable[] =
    {
    7662,
    30,
    7374,
    7710
    };

static const MIDL_STUBLESS_PROXY_INFO IRTCEnumGroups_ProxyInfo =
    {
    &Object_StubDesc,
    __MIDL_ProcFormatString.Format,
    &IRTCEnumGroups_FormatStringOffsetTable[-3],
    0,
    0,
    0
    };


static const MIDL_SERVER_INFO IRTCEnumGroups_ServerInfo = 
    {
    &Object_StubDesc,
    0,
    __MIDL_ProcFormatString.Format,
    &IRTCEnumGroups_FormatStringOffsetTable[-3],
    0,
    0,
    0,
    0};
CINTERFACE_PROXY_VTABLE(7) _IRTCEnumGroupsProxyVtbl = 
{
    &IRTCEnumGroups_ProxyInfo,
    &IID_IRTCEnumGroups,
    IUnknown_QueryInterface_Proxy,
    IUnknown_AddRef_Proxy,
    IUnknown_Release_Proxy ,
    (void *) (INT_PTR) -1 /* IRTCEnumGroups::Next */ ,
    (void *) (INT_PTR) -1 /* IRTCEnumGroups::Reset */ ,
    (void *) (INT_PTR) -1 /* IRTCEnumGroups::Skip */ ,
    (void *) (INT_PTR) -1 /* IRTCEnumGroups::Clone */
};

const CInterfaceStubVtbl _IRTCEnumGroupsStubVtbl =
{
    &IID_IRTCEnumGroups,
    &IRTCEnumGroups_ServerInfo,
    7,
    0, /* pure interpreted */
    CStdStubBuffer_METHODS
};


/* Object interface: IRTCPresenceContact, ver. 0.0,
   GUID={0x8b22f92c,0xcd90,0x42db,{0xa7,0x33,0x21,0x22,0x05,0xc3,0xe3,0xdf}} */

#pragma code_seg(".orpc")
static const unsigned short IRTCPresenceContact_FormatStringOffsetTable[] =
    {
    3858,
    7746,
    3930,
    7782,
    7818,
    7854,
    7890,
    7926
    };

static const MIDL_STUBLESS_PROXY_INFO IRTCPresenceContact_ProxyInfo =
    {
    &Object_StubDesc,
    __MIDL_ProcFormatString.Format,
    &IRTCPresenceContact_FormatStringOffsetTable[-3],
    0,
    0,
    0
    };


static const MIDL_SERVER_INFO IRTCPresenceContact_ServerInfo = 
    {
    &Object_StubDesc,
    0,
    __MIDL_ProcFormatString.Format,
    &IRTCPresenceContact_FormatStringOffsetTable[-3],
    0,
    0,
    0,
    0};
CINTERFACE_PROXY_VTABLE(11) _IRTCPresenceContactProxyVtbl = 
{
    &IRTCPresenceContact_ProxyInfo,
    &IID_IRTCPresenceContact,
    IUnknown_QueryInterface_Proxy,
    IUnknown_AddRef_Proxy,
    IUnknown_Release_Proxy ,
    (void *) (INT_PTR) -1 /* IRTCPresenceContact::get_PresentityURI */ ,
    (void *) (INT_PTR) -1 /* IRTCPresenceContact::put_PresentityURI */ ,
    (void *) (INT_PTR) -1 /* IRTCPresenceContact::get_Name */ ,
    (void *) (INT_PTR) -1 /* IRTCPresenceContact::put_Name */ ,
    (void *) (INT_PTR) -1 /* IRTCPresenceContact::get_Data */ ,
    (void *) (INT_PTR) -1 /* IRTCPresenceContact::put_Data */ ,
    (void *) (INT_PTR) -1 /* IRTCPresenceContact::get_Persistent */ ,
    (void *) (INT_PTR) -1 /* IRTCPresenceContact::put_Persistent */
};

const CInterfaceStubVtbl _IRTCPresenceContactStubVtbl =
{
    &IID_IRTCPresenceContact,
    &IRTCPresenceContact_ServerInfo,
    11,
    0, /* pure interpreted */
    CStdStubBuffer_METHODS
};


/* Object interface: IRTCBuddy, ver. 0.0,
   GUID={0xfcb136c8,0x7b90,0x4e0c,{0xbe,0xfe,0x56,0xed,0xf0,0xba,0x6f,0x1c}} */

#pragma code_seg(".orpc")
static const unsigned short IRTCBuddy_FormatStringOffsetTable[] =
    {
    3858,
    7746,
    3930,
    7782,
    7818,
    7854,
    7890,
    7926,
    7962,
    4188
    };

static const MIDL_STUBLESS_PROXY_INFO IRTCBuddy_ProxyInfo =
    {
    &Object_StubDesc,
    __MIDL_ProcFormatString.Format,
    &IRTCBuddy_FormatStringOffsetTable[-3],
    0,
    0,
    0
    };


static const MIDL_SERVER_INFO IRTCBuddy_ServerInfo = 
    {
    &Object_StubDesc,
    0,
    __MIDL_ProcFormatString.Format,
    &IRTCBuddy_FormatStringOffsetTable[-3],
    0,
    0,
    0,
    0};
CINTERFACE_PROXY_VTABLE(13) _IRTCBuddyProxyVtbl = 
{
    &IRTCBuddy_ProxyInfo,
    &IID_IRTCBuddy,
    IUnknown_QueryInterface_Proxy,
    IUnknown_AddRef_Proxy,
    IUnknown_Release_Proxy ,
    (void *) (INT_PTR) -1 /* IRTCPresenceContact::get_PresentityURI */ ,
    (void *) (INT_PTR) -1 /* IRTCPresenceContact::put_PresentityURI */ ,
    (void *) (INT_PTR) -1 /* IRTCPresenceContact::get_Name */ ,
    (void *) (INT_PTR) -1 /* IRTCPresenceContact::put_Name */ ,
    (void *) (INT_PTR) -1 /* IRTCPresenceContact::get_Data */ ,
    (void *) (INT_PTR) -1 /* IRTCPresenceContact::put_Data */ ,
    (void *) (INT_PTR) -1 /* IRTCPresenceContact::get_Persistent */ ,
    (void *) (INT_PTR) -1 /* IRTCPresenceContact::put_Persistent */ ,
    (void *) (INT_PTR) -1 /* IRTCBuddy::get_Status */ ,
    (void *) (INT_PTR) -1 /* IRTCBuddy::get_Notes */
};

const CInterfaceStubVtbl _IRTCBuddyStubVtbl =
{
    &IID_IRTCBuddy,
    &IRTCBuddy_ServerInfo,
    13,
    0, /* pure interpreted */
    CStdStubBuffer_METHODS
};


/* Object interface: IRTCBuddy2, ver. 0.0,
   GUID={0x102F9588,0x23E7,0x40e3,{0x95,0x4D,0xCD,0x7A,0x1D,0x5C,0x03,0x61}} */

#pragma code_seg(".orpc")
static const unsigned short IRTCBuddy2_FormatStringOffsetTable[] =
    {
    3858,
    7746,
    3930,
    7782,
    7818,
    7854,
    7890,
    7926,
    7962,
    4188,
    7998,
    8034,
    8064,
    8100,
    8136,
    8178,
    8214,
    4488
    };

static const MIDL_STUBLESS_PROXY_INFO IRTCBuddy2_ProxyInfo =
    {
    &Object_StubDesc,
    __MIDL_ProcFormatString.Format,
    &IRTCBuddy2_FormatStringOffsetTable[-3],
    0,
    0,
    0
    };


static const MIDL_SERVER_INFO IRTCBuddy2_ServerInfo = 
    {
    &Object_StubDesc,
    0,
    __MIDL_ProcFormatString.Format,
    &IRTCBuddy2_FormatStringOffsetTable[-3],
    0,
    0,
    0,
    0};
CINTERFACE_PROXY_VTABLE(21) _IRTCBuddy2ProxyVtbl = 
{
    &IRTCBuddy2_ProxyInfo,
    &IID_IRTCBuddy2,
    IUnknown_QueryInterface_Proxy,
    IUnknown_AddRef_Proxy,
    IUnknown_Release_Proxy ,
    (void *) (INT_PTR) -1 /* IRTCPresenceContact::get_PresentityURI */ ,
    (void *) (INT_PTR) -1 /* IRTCPresenceContact::put_PresentityURI */ ,
    (void *) (INT_PTR) -1 /* IRTCPresenceContact::get_Name */ ,
    (void *) (INT_PTR) -1 /* IRTCPresenceContact::put_Name */ ,
    (void *) (INT_PTR) -1 /* IRTCPresenceContact::get_Data */ ,
    (void *) (INT_PTR) -1 /* IRTCPresenceContact::put_Data */ ,
    (void *) (INT_PTR) -1 /* IRTCPresenceContact::get_Persistent */ ,
    (void *) (INT_PTR) -1 /* IRTCPresenceContact::put_Persistent */ ,
    (void *) (INT_PTR) -1 /* IRTCBuddy::get_Status */ ,
    (void *) (INT_PTR) -1 /* IRTCBuddy::get_Notes */ ,
    (void *) (INT_PTR) -1 /* IRTCBuddy2::get_Profile */ ,
    (void *) (INT_PTR) -1 /* IRTCBuddy2::Refresh */ ,
    (void *) (INT_PTR) -1 /* IRTCBuddy2::EnumerateGroups */ ,
    (void *) (INT_PTR) -1 /* IRTCBuddy2::get_Groups */ ,
    (void *) (INT_PTR) -1 /* IRTCBuddy2::get_PresenceProperty */ ,
    (void *) (INT_PTR) -1 /* IRTCBuddy2::EnumeratePresenceDevices */ ,
    (void *) (INT_PTR) -1 /* IRTCBuddy2::get_PresenceDevices */ ,
    (void *) (INT_PTR) -1 /* IRTCBuddy2::get_SubscriptionType */
};

const CInterfaceStubVtbl _IRTCBuddy2StubVtbl =
{
    &IID_IRTCBuddy2,
    &IRTCBuddy2_ServerInfo,
    21,
    0, /* pure interpreted */
    CStdStubBuffer_METHODS
};


/* Object interface: IRTCWatcher, ver. 0.0,
   GUID={0xc7cedad8,0x346b,0x4d1b,{0xac,0x02,0xa2,0x08,0x8d,0xf9,0xbe,0x4f}} */

#pragma code_seg(".orpc")
static const unsigned short IRTCWatcher_FormatStringOffsetTable[] =
    {
    3858,
    7746,
    3930,
    7782,
    7818,
    7854,
    7890,
    7926,
    7962,
    336
    };

static const MIDL_STUBLESS_PROXY_INFO IRTCWatcher_ProxyInfo =
    {
    &Object_StubDesc,
    __MIDL_ProcFormatString.Format,
    &IRTCWatcher_FormatStringOffsetTable[-3],
    0,
    0,
    0
    };


static const MIDL_SERVER_INFO IRTCWatcher_ServerInfo = 
    {
    &Object_StubDesc,
    0,
    __MIDL_ProcFormatString.Format,
    &IRTCWatcher_FormatStringOffsetTable[-3],
    0,
    0,
    0,
    0};
CINTERFACE_PROXY_VTABLE(13) _IRTCWatcherProxyVtbl = 
{
    &IRTCWatcher_ProxyInfo,
    &IID_IRTCWatcher,
    IUnknown_QueryInterface_Proxy,
    IUnknown_AddRef_Proxy,
    IUnknown_Release_Proxy ,
    (void *) (INT_PTR) -1 /* IRTCPresenceContact::get_PresentityURI */ ,
    (void *) (INT_PTR) -1 /* IRTCPresenceContact::put_PresentityURI */ ,
    (void *) (INT_PTR) -1 /* IRTCPresenceContact::get_Name */ ,
    (void *) (INT_PTR) -1 /* IRTCPresenceContact::put_Name */ ,
    (void *) (INT_PTR) -1 /* IRTCPresenceContact::get_Data */ ,
    (void *) (INT_PTR) -1 /* IRTCPresenceContact::put_Data */ ,
    (void *) (INT_PTR) -1 /* IRTCPresenceContact::get_Persistent */ ,
    (void *) (INT_PTR) -1 /* IRTCPresenceContact::put_Persistent */ ,
    (void *) (INT_PTR) -1 /* IRTCWatcher::get_State */ ,
    (void *) (INT_PTR) -1 /* IRTCWatcher::put_State */
};

const CInterfaceStubVtbl _IRTCWatcherStubVtbl =
{
    &IID_IRTCWatcher,
    &IRTCWatcher_ServerInfo,
    13,
    0, /* pure interpreted */
    CStdStubBuffer_METHODS
};


/* Object interface: IRTCWatcher2, ver. 0.0,
   GUID={0xD4D9967F,0xD011,0x4b1d,{0x91,0xE3,0xAB,0xA7,0x8F,0x96,0x39,0x3D}} */

#pragma code_seg(".orpc")
static const unsigned short IRTCWatcher2_FormatStringOffsetTable[] =
    {
    3858,
    7746,
    3930,
    7782,
    7818,
    7854,
    7890,
    7926,
    7962,
    336,
    7998,
    8250
    };

static const MIDL_STUBLESS_PROXY_INFO IRTCWatcher2_ProxyInfo =
    {
    &Object_StubDesc,
    __MIDL_ProcFormatString.Format,
    &IRTCWatcher2_FormatStringOffsetTable[-3],
    0,
    0,
    0
    };


static const MIDL_SERVER_INFO IRTCWatcher2_ServerInfo = 
    {
    &Object_StubDesc,
    0,
    __MIDL_ProcFormatString.Format,
    &IRTCWatcher2_FormatStringOffsetTable[-3],
    0,
    0,
    0,
    0};
CINTERFACE_PROXY_VTABLE(15) _IRTCWatcher2ProxyVtbl = 
{
    &IRTCWatcher2_ProxyInfo,
    &IID_IRTCWatcher2,
    IUnknown_QueryInterface_Proxy,
    IUnknown_AddRef_Proxy,
    IUnknown_Release_Proxy ,
    (void *) (INT_PTR) -1 /* IRTCPresenceContact::get_PresentityURI */ ,
    (void *) (INT_PTR) -1 /* IRTCPresenceContact::put_PresentityURI */ ,
    (void *) (INT_PTR) -1 /* IRTCPresenceContact::get_Name */ ,
    (void *) (INT_PTR) -1 /* IRTCPresenceContact::put_Name */ ,
    (void *) (INT_PTR) -1 /* IRTCPresenceContact::get_Data */ ,
    (void *) (INT_PTR) -1 /* IRTCPresenceContact::put_Data */ ,
    (void *) (INT_PTR) -1 /* IRTCPresenceContact::get_Persistent */ ,
    (void *) (INT_PTR) -1 /* IRTCPresenceContact::put_Persistent */ ,
    (void *) (INT_PTR) -1 /* IRTCWatcher::get_State */ ,
    (void *) (INT_PTR) -1 /* IRTCWatcher::put_State */ ,
    (void *) (INT_PTR) -1 /* IRTCWatcher2::get_Profile */ ,
    (void *) (INT_PTR) -1 /* IRTCWatcher2::get_Scope */
};

const CInterfaceStubVtbl _IRTCWatcher2StubVtbl =
{
    &IID_IRTCWatcher2,
    &IRTCWatcher2_ServerInfo,
    15,
    0, /* pure interpreted */
    CStdStubBuffer_METHODS
};


/* Object interface: IRTCBuddyGroup, ver. 0.0,
   GUID={0x60361E68,0x9164,0x4389,{0xA4,0xC6,0xD0,0xB3,0x92,0x5B,0xDA,0x5E}} */

#pragma code_seg(".orpc")
static const unsigned short IRTCBuddyGroup_FormatStringOffsetTable[] =
    {
    3858,
    7746,
    8286,
    8322,
    8358,
    8394,
    4080,
    8430,
    8466
    };

static const MIDL_STUBLESS_PROXY_INFO IRTCBuddyGroup_ProxyInfo =
    {
    &Object_StubDesc,
    __MIDL_ProcFormatString.Format,
    &IRTCBuddyGroup_FormatStringOffsetTable[-3],
    0,
    0,
    0
    };


static const MIDL_SERVER_INFO IRTCBuddyGroup_ServerInfo = 
    {
    &Object_StubDesc,
    0,
    __MIDL_ProcFormatString.Format,
    &IRTCBuddyGroup_FormatStringOffsetTable[-3],
    0,
    0,
    0,
    0};
CINTERFACE_PROXY_VTABLE(12) _IRTCBuddyGroupProxyVtbl = 
{
    &IRTCBuddyGroup_ProxyInfo,
    &IID_IRTCBuddyGroup,
    IUnknown_QueryInterface_Proxy,
    IUnknown_AddRef_Proxy,
    IUnknown_Release_Proxy ,
    (void *) (INT_PTR) -1 /* IRTCBuddyGroup::get_Name */ ,
    (void *) (INT_PTR) -1 /* IRTCBuddyGroup::put_Name */ ,
    (void *) (INT_PTR) -1 /* IRTCBuddyGroup::AddBuddy */ ,
    (void *) (INT_PTR) -1 /* IRTCBuddyGroup::RemoveBuddy */ ,
    (void *) (INT_PTR) -1 /* IRTCBuddyGroup::EnumerateBuddies */ ,
    (void *) (INT_PTR) -1 /* IRTCBuddyGroup::get_Buddies */ ,
    (void *) (INT_PTR) -1 /* IRTCBuddyGroup::get_Data */ ,
    (void *) (INT_PTR) -1 /* IRTCBuddyGroup::put_Data */ ,
    (void *) (INT_PTR) -1 /* IRTCBuddyGroup::get_Profile */
};

const CInterfaceStubVtbl _IRTCBuddyGroupStubVtbl =
{
    &IID_IRTCBuddyGroup,
    &IRTCBuddyGroup_ServerInfo,
    12,
    0, /* pure interpreted */
    CStdStubBuffer_METHODS
};


/* Object interface: IRTCEventNotification, ver. 0.0,
   GUID={0x13fa24c7,0x5748,0x4b21,{0x91,0xf5,0x73,0x97,0x60,0x9c,0xe7,0x47}} */

#pragma code_seg(".orpc")
static const unsigned short IRTCEventNotification_FormatStringOffsetTable[] =
    {
    8502
    };

static const MIDL_STUBLESS_PROXY_INFO IRTCEventNotification_ProxyInfo =
    {
    &Object_StubDesc,
    __MIDL_ProcFormatString.Format,
    &IRTCEventNotification_FormatStringOffsetTable[-3],
    0,
    0,
    0
    };


static const MIDL_SERVER_INFO IRTCEventNotification_ServerInfo = 
    {
    &Object_StubDesc,
    0,
    __MIDL_ProcFormatString.Format,
    &IRTCEventNotification_FormatStringOffsetTable[-3],
    0,
    0,
    0,
    0};
CINTERFACE_PROXY_VTABLE(4) _IRTCEventNotificationProxyVtbl = 
{
    &IRTCEventNotification_ProxyInfo,
    &IID_IRTCEventNotification,
    IUnknown_QueryInterface_Proxy,
    IUnknown_AddRef_Proxy,
    IUnknown_Release_Proxy ,
    (void *) (INT_PTR) -1 /* IRTCEventNotification::Event */
};

const CInterfaceStubVtbl _IRTCEventNotificationStubVtbl =
{
    &IID_IRTCEventNotification,
    &IRTCEventNotification_ServerInfo,
    4,
    0, /* pure interpreted */
    CStdStubBuffer_METHODS
};


/* Object interface: IRTCPortManager, ver. 0.0,
   GUID={0xDA77C14B,0x6208,0x43ca,{0x8D,0xDF,0x5B,0x60,0xA0,0xA6,0x9F,0xAC}} */

#pragma code_seg(".orpc")
static const unsigned short IRTCPortManager_FormatStringOffsetTable[] =
    {
    8544,
    8610,
    8670
    };

static const MIDL_STUBLESS_PROXY_INFO IRTCPortManager_ProxyInfo =
    {
    &Object_StubDesc,
    __MIDL_ProcFormatString.Format,
    &IRTCPortManager_FormatStringOffsetTable[-3],
    0,
    0,
    0
    };


static const MIDL_SERVER_INFO IRTCPortManager_ServerInfo = 
    {
    &Object_StubDesc,
    0,
    __MIDL_ProcFormatString.Format,
    &IRTCPortManager_FormatStringOffsetTable[-3],
    0,
    0,
    0,
    0};
CINTERFACE_PROXY_VTABLE(6) _IRTCPortManagerProxyVtbl = 
{
    &IRTCPortManager_ProxyInfo,
    &IID_IRTCPortManager,
    IUnknown_QueryInterface_Proxy,
    IUnknown_AddRef_Proxy,
    IUnknown_Release_Proxy ,
    (void *) (INT_PTR) -1 /* IRTCPortManager::GetMapping */ ,
    (void *) (INT_PTR) -1 /* IRTCPortManager::UpdateRemoteAddress */ ,
    (void *) (INT_PTR) -1 /* IRTCPortManager::ReleaseMapping */
};

const CInterfaceStubVtbl _IRTCPortManagerStubVtbl =
{
    &IID_IRTCPortManager,
    &IRTCPortManager_ServerInfo,
    6,
    0, /* pure interpreted */
    CStdStubBuffer_METHODS
};


/* Object interface: IRTCPortManager2, ver. 0.0,
   GUID={0x269F36EF,0x334C,0x43f7,{0xB6,0xE2,0x36,0x7E,0x8D,0x30,0x7A,0xEB}} */

#pragma code_seg(".orpc")
static const unsigned short IRTCPortManager2_FormatStringOffsetTable[] =
    {
    8544,
    8610,
    8670,
    8724
    };

static const MIDL_STUBLESS_PROXY_INFO IRTCPortManager2_ProxyInfo =
    {
    &Object_StubDesc,
    __MIDL_ProcFormatString.Format,
    &IRTCPortManager2_FormatStringOffsetTable[-3],
    0,
    0,
    0
    };


static const MIDL_SERVER_INFO IRTCPortManager2_ServerInfo = 
    {
    &Object_StubDesc,
    0,
    __MIDL_ProcFormatString.Format,
    &IRTCPortManager2_FormatStringOffsetTable[-3],
    0,
    0,
    0,
    0};
CINTERFACE_PROXY_VTABLE(7) _IRTCPortManager2ProxyVtbl = 
{
    &IRTCPortManager2_ProxyInfo,
    &IID_IRTCPortManager2,
    IUnknown_QueryInterface_Proxy,
    IUnknown_AddRef_Proxy,
    IUnknown_Release_Proxy ,
    (void *) (INT_PTR) -1 /* IRTCPortManager::GetMapping */ ,
    (void *) (INT_PTR) -1 /* IRTCPortManager::UpdateRemoteAddress */ ,
    (void *) (INT_PTR) -1 /* IRTCPortManager::ReleaseMapping */ ,
    (void *) (INT_PTR) -1 /* IRTCPortManager2::UpdateRemoteAddressEx */
};

const CInterfaceStubVtbl _IRTCPortManager2StubVtbl =
{
    &IID_IRTCPortManager2,
    &IRTCPortManager2_ServerInfo,
    7,
    0, /* pure interpreted */
    CStdStubBuffer_METHODS
};


/* Object interface: IRTCSessionPortManagement, ver. 0.0,
   GUID={0xa072f1d6,0x0286,0x4e1f,{0x85,0xf2,0x17,0xa2,0x94,0x84,0x56,0xec}} */

#pragma code_seg(".orpc")
static const unsigned short IRTCSessionPortManagement_FormatStringOffsetTable[] =
    {
    8790
    };

static const MIDL_STUBLESS_PROXY_INFO IRTCSessionPortManagement_ProxyInfo =
    {
    &Object_StubDesc,
    __MIDL_ProcFormatString.Format,
    &IRTCSessionPortManagement_FormatStringOffsetTable[-3],
    0,
    0,
    0
    };


static const MIDL_SERVER_INFO IRTCSessionPortManagement_ServerInfo = 
    {
    &Object_StubDesc,
    0,
    __MIDL_ProcFormatString.Format,
    &IRTCSessionPortManagement_FormatStringOffsetTable[-3],
    0,
    0,
    0,
    0};
CINTERFACE_PROXY_VTABLE(4) _IRTCSessionPortManagementProxyVtbl = 
{
    &IRTCSessionPortManagement_ProxyInfo,
    &IID_IRTCSessionPortManagement,
    IUnknown_QueryInterface_Proxy,
    IUnknown_AddRef_Proxy,
    IUnknown_Release_Proxy ,
    (void *) (INT_PTR) -1 /* IRTCSessionPortManagement::SetPortManager */
};

const CInterfaceStubVtbl _IRTCSessionPortManagementStubVtbl =
{
    &IID_IRTCSessionPortManagement,
    &IRTCSessionPortManagement_ServerInfo,
    4,
    0, /* pure interpreted */
    CStdStubBuffer_METHODS
};


/* Object interface: IRTCClientPortManagement, ver. 0.0,
   GUID={0xd5df3f03,0x4bde,0x4417,{0xae,0xfe,0x71,0x17,0x7b,0xda,0xea,0x66}} */

#pragma code_seg(".orpc")
static const unsigned short IRTCClientPortManagement_FormatStringOffsetTable[] =
    {
    8826,
    8868,
    8910
    };

static const MIDL_STUBLESS_PROXY_INFO IRTCClientPortManagement_ProxyInfo =
    {
    &Object_StubDesc,
    __MIDL_ProcFormatString.Format,
    &IRTCClientPortManagement_FormatStringOffsetTable[-3],
    0,
    0,
    0
    };


static const MIDL_SERVER_INFO IRTCClientPortManagement_ServerInfo = 
    {
    &Object_StubDesc,
    0,
    __MIDL_ProcFormatString.Format,
    &IRTCClientPortManagement_FormatStringOffsetTable[-3],
    0,
    0,
    0,
    0};
CINTERFACE_PROXY_VTABLE(6) _IRTCClientPortManagementProxyVtbl = 
{
    &IRTCClientPortManagement_ProxyInfo,
    &IID_IRTCClientPortManagement,
    IUnknown_QueryInterface_Proxy,
    IUnknown_AddRef_Proxy,
    IUnknown_Release_Proxy ,
    (void *) (INT_PTR) -1 /* IRTCClientPortManagement::StartListenAddressAndPort */ ,
    (void *) (INT_PTR) -1 /* IRTCClientPortManagement::StopListenAddressAndPort */ ,
    (void *) (INT_PTR) -1 /* IRTCClientPortManagement::GetPortRange */
};

const CInterfaceStubVtbl _IRTCClientPortManagementStubVtbl =
{
    &IID_IRTCClientPortManagement,
    &IRTCClientPortManagement_ServerInfo,
    6,
    0, /* pure interpreted */
    CStdStubBuffer_METHODS
};


/* Object interface: IRTCUserSearch, ver. 0.0,
   GUID={0xB619882B,0x860C,0x4db4,{0xBE,0x1B,0x69,0x3B,0x65,0x05,0xBB,0xE5}} */

#pragma code_seg(".orpc")
static const unsigned short IRTCUserSearch_FormatStringOffsetTable[] =
    {
    8958,
    8994
    };

static const MIDL_STUBLESS_PROXY_INFO IRTCUserSearch_ProxyInfo =
    {
    &Object_StubDesc,
    __MIDL_ProcFormatString.Format,
    &IRTCUserSearch_FormatStringOffsetTable[-3],
    0,
    0,
    0
    };


static const MIDL_SERVER_INFO IRTCUserSearch_ServerInfo = 
    {
    &Object_StubDesc,
    0,
    __MIDL_ProcFormatString.Format,
    &IRTCUserSearch_FormatStringOffsetTable[-3],
    0,
    0,
    0,
    0};
CINTERFACE_PROXY_VTABLE(5) _IRTCUserSearchProxyVtbl = 
{
    &IRTCUserSearch_ProxyInfo,
    &IID_IRTCUserSearch,
    IUnknown_QueryInterface_Proxy,
    IUnknown_AddRef_Proxy,
    IUnknown_Release_Proxy ,
    (void *) (INT_PTR) -1 /* IRTCUserSearch::CreateQuery */ ,
    (void *) (INT_PTR) -1 /* IRTCUserSearch::ExecuteSearch */
};

const CInterfaceStubVtbl _IRTCUserSearchStubVtbl =
{
    &IID_IRTCUserSearch,
    &IRTCUserSearch_ServerInfo,
    5,
    0, /* pure interpreted */
    CStdStubBuffer_METHODS
};


/* Object interface: IRTCUserSearchQuery, ver. 0.0,
   GUID={0x288300F5,0xD23A,0x4365,{0x9A,0x73,0x99,0x85,0xC9,0x8C,0x28,0x81}} */

#pragma code_seg(".orpc")
static const unsigned short IRTCUserSearchQuery_FormatStringOffsetTable[] =
    {
    9042,
    9084,
    3930,
    9126,
    9168,
    7854,
    4080
    };

static const MIDL_STUBLESS_PROXY_INFO IRTCUserSearchQuery_ProxyInfo =
    {
    &Object_StubDesc,
    __MIDL_ProcFormatString.Format,
    &IRTCUserSearchQuery_FormatStringOffsetTable[-3],
    0,
    0,
    0
    };


static const MIDL_SERVER_INFO IRTCUserSearchQuery_ServerInfo = 
    {
    &Object_StubDesc,
    0,
    __MIDL_ProcFormatString.Format,
    &IRTCUserSearchQuery_FormatStringOffsetTable[-3],
    0,
    0,
    0,
    0};
CINTERFACE_PROXY_VTABLE(10) _IRTCUserSearchQueryProxyVtbl = 
{
    &IRTCUserSearchQuery_ProxyInfo,
    &IID_IRTCUserSearchQuery,
    IUnknown_QueryInterface_Proxy,
    IUnknown_AddRef_Proxy,
    IUnknown_Release_Proxy ,
    (void *) (INT_PTR) -1 /* IRTCUserSearchQuery::put_SearchTerm */ ,
    (void *) (INT_PTR) -1 /* IRTCUserSearchQuery::get_SearchTerm */ ,
    (void *) (INT_PTR) -1 /* IRTCUserSearchQuery::get_SearchTerms */ ,
    (void *) (INT_PTR) -1 /* IRTCUserSearchQuery::put_SearchPreference */ ,
    (void *) (INT_PTR) -1 /* IRTCUserSearchQuery::get_SearchPreference */ ,
    (void *) (INT_PTR) -1 /* IRTCUserSearchQuery::put_SearchDomain */ ,
    (void *) (INT_PTR) -1 /* IRTCUserSearchQuery::get_SearchDomain */
};

const CInterfaceStubVtbl _IRTCUserSearchQueryStubVtbl =
{
    &IID_IRTCUserSearchQuery,
    &IRTCUserSearchQuery_ServerInfo,
    10,
    0, /* pure interpreted */
    CStdStubBuffer_METHODS
};


/* Object interface: IRTCUserSearchResult, ver. 0.0,
   GUID={0x851278B2,0x9592,0x480f,{0x8D,0xB5,0x2D,0xE8,0x6B,0x26,0xB5,0x4D}} */

#pragma code_seg(".orpc")
static const unsigned short IRTCUserSearchResult_FormatStringOffsetTable[] =
    {
    9210
    };

static const MIDL_STUBLESS_PROXY_INFO IRTCUserSearchResult_ProxyInfo =
    {
    &Object_StubDesc,
    __MIDL_ProcFormatString.Format,
    &IRTCUserSearchResult_FormatStringOffsetTable[-3],
    0,
    0,
    0
    };


static const MIDL_SERVER_INFO IRTCUserSearchResult_ServerInfo = 
    {
    &Object_StubDesc,
    0,
    __MIDL_ProcFormatString.Format,
    &IRTCUserSearchResult_FormatStringOffsetTable[-3],
    0,
    0,
    0,
    0};
CINTERFACE_PROXY_VTABLE(4) _IRTCUserSearchResultProxyVtbl = 
{
    &IRTCUserSearchResult_ProxyInfo,
    &IID_IRTCUserSearchResult,
    IUnknown_QueryInterface_Proxy,
    IUnknown_AddRef_Proxy,
    IUnknown_Release_Proxy ,
    (void *) (INT_PTR) -1 /* IRTCUserSearchResult::get_Value */
};

const CInterfaceStubVtbl _IRTCUserSearchResultStubVtbl =
{
    &IID_IRTCUserSearchResult,
    &IRTCUserSearchResult_ServerInfo,
    4,
    0, /* pure interpreted */
    CStdStubBuffer_METHODS
};


/* Object interface: IRTCEnumUserSearchResults, ver. 0.0,
   GUID={0x83D4D877,0xAA5D,0x4a5b,{0x8D,0x0E,0x00,0x2A,0x80,0x67,0xE0,0xE8}} */

#pragma code_seg(".orpc")
static const unsigned short IRTCEnumUserSearchResults_FormatStringOffsetTable[] =
    {
    9252,
    30,
    7374,
    9300
    };

static const MIDL_STUBLESS_PROXY_INFO IRTCEnumUserSearchResults_ProxyInfo =
    {
    &Object_StubDesc,
    __MIDL_ProcFormatString.Format,
    &IRTCEnumUserSearchResults_FormatStringOffsetTable[-3],
    0,
    0,
    0
    };


static const MIDL_SERVER_INFO IRTCEnumUserSearchResults_ServerInfo = 
    {
    &Object_StubDesc,
    0,
    __MIDL_ProcFormatString.Format,
    &IRTCEnumUserSearchResults_FormatStringOffsetTable[-3],
    0,
    0,
    0,
    0};
CINTERFACE_PROXY_VTABLE(7) _IRTCEnumUserSearchResultsProxyVtbl = 
{
    &IRTCEnumUserSearchResults_ProxyInfo,
    &IID_IRTCEnumUserSearchResults,
    IUnknown_QueryInterface_Proxy,
    IUnknown_AddRef_Proxy,
    IUnknown_Release_Proxy ,
    (void *) (INT_PTR) -1 /* IRTCEnumUserSearchResults::Next */ ,
    (void *) (INT_PTR) -1 /* IRTCEnumUserSearchResults::Reset */ ,
    (void *) (INT_PTR) -1 /* IRTCEnumUserSearchResults::Skip */ ,
    (void *) (INT_PTR) -1 /* IRTCEnumUserSearchResults::Clone */
};

const CInterfaceStubVtbl _IRTCEnumUserSearchResultsStubVtbl =
{
    &IID_IRTCEnumUserSearchResults,
    &IRTCEnumUserSearchResults_ServerInfo,
    7,
    0, /* pure interpreted */
    CStdStubBuffer_METHODS
};


/* Object interface: IRTCUserSearchResultsEvent, ver. 0.0,
   GUID={0xD8C8C3CD,0x7FAC,0x4088,{0x81,0xC5,0xC2,0x4C,0xBC,0x09,0x38,0xE3}} */

#pragma code_seg(".orpc")
static const unsigned short IRTCUserSearchResultsEvent_FormatStringOffsetTable[] =
    {
    (unsigned short) -1,
    (unsigned short) -1,
    (unsigned short) -1,
    (unsigned short) -1,
    9336,
    8394,
    9372,
    9408,
    6348,
    9444,
    6426
    };

static const MIDL_STUBLESS_PROXY_INFO IRTCUserSearchResultsEvent_ProxyInfo =
    {
    &Object_StubDesc,
    __MIDL_ProcFormatString.Format,
    &IRTCUserSearchResultsEvent_FormatStringOffsetTable[-3],
    0,
    0,
    0
    };


static const MIDL_SERVER_INFO IRTCUserSearchResultsEvent_ServerInfo = 
    {
    &Object_StubDesc,
    0,
    __MIDL_ProcFormatString.Format,
    &IRTCUserSearchResultsEvent_FormatStringOffsetTable[-3],
    0,
    0,
    0,
    0};
CINTERFACE_PROXY_VTABLE(14) _IRTCUserSearchResultsEventProxyVtbl = 
{
    &IRTCUserSearchResultsEvent_ProxyInfo,
    &IID_IRTCUserSearchResultsEvent,
    IUnknown_QueryInterface_Proxy,
    IUnknown_AddRef_Proxy,
    IUnknown_Release_Proxy ,
    0 /* (void *) (INT_PTR) -1 /* IDispatch::GetTypeInfoCount */ ,
    0 /* (void *) (INT_PTR) -1 /* IDispatch::GetTypeInfo */ ,
    0 /* (void *) (INT_PTR) -1 /* IDispatch::GetIDsOfNames */ ,
    0 /* IDispatch_Invoke_Proxy */ ,
    (void *) (INT_PTR) -1 /* IRTCUserSearchResultsEvent::EnumerateResults */ ,
    (void *) (INT_PTR) -1 /* IRTCUserSearchResultsEvent::get_Results */ ,
    (void *) (INT_PTR) -1 /* IRTCUserSearchResultsEvent::get_Profile */ ,
    (void *) (INT_PTR) -1 /* IRTCUserSearchResultsEvent::get_Query */ ,
    (void *) (INT_PTR) -1 /* IRTCUserSearchResultsEvent::get_Cookie */ ,
    (void *) (INT_PTR) -1 /* IRTCUserSearchResultsEvent::get_StatusCode */ ,
    (void *) (INT_PTR) -1 /* IRTCUserSearchResultsEvent::get_MoreAvailable */
};


static const PRPC_STUB_FUNCTION IRTCUserSearchResultsEvent_table[] =
{
    STUB_FORWARDING_FUNCTION,
    STUB_FORWARDING_FUNCTION,
    STUB_FORWARDING_FUNCTION,
    STUB_FORWARDING_FUNCTION,
    NdrStubCall2,
    NdrStubCall2,
    NdrStubCall2,
    NdrStubCall2,
    NdrStubCall2,
    NdrStubCall2,
    NdrStubCall2
};

CInterfaceStubVtbl _IRTCUserSearchResultsEventStubVtbl =
{
    &IID_IRTCUserSearchResultsEvent,
    &IRTCUserSearchResultsEvent_ServerInfo,
    14,
    &IRTCUserSearchResultsEvent_table[-3],
    CStdStubBuffer_DELEGATING_METHODS
};


/* Object interface: IRTCSessionReferStatusEvent, ver. 0.0,
   GUID={0x3D8FC2CD,0x5D76,0x44AB,{0xBB,0x68,0x2A,0x80,0x35,0x3B,0x34,0xA2}} */

#pragma code_seg(".orpc")
static const unsigned short IRTCSessionReferStatusEvent_FormatStringOffsetTable[] =
    {
    (unsigned short) -1,
    (unsigned short) -1,
    (unsigned short) -1,
    (unsigned short) -1,
    9480,
    6312,
    204,
    5916
    };

static const MIDL_STUBLESS_PROXY_INFO IRTCSessionReferStatusEvent_ProxyInfo =
    {
    &Object_StubDesc,
    __MIDL_ProcFormatString.Format,
    &IRTCSessionReferStatusEvent_FormatStringOffsetTable[-3],
    0,
    0,
    0
    };


static const MIDL_SERVER_INFO IRTCSessionReferStatusEvent_ServerInfo = 
    {
    &Object_StubDesc,
    0,
    __MIDL_ProcFormatString.Format,
    &IRTCSessionReferStatusEvent_FormatStringOffsetTable[-3],
    0,
    0,
    0,
    0};
CINTERFACE_PROXY_VTABLE(11) _IRTCSessionReferStatusEventProxyVtbl = 
{
    &IRTCSessionReferStatusEvent_ProxyInfo,
    &IID_IRTCSessionReferStatusEvent,
    IUnknown_QueryInterface_Proxy,
    IUnknown_AddRef_Proxy,
    IUnknown_Release_Proxy ,
    0 /* (void *) (INT_PTR) -1 /* IDispatch::GetTypeInfoCount */ ,
    0 /* (void *) (INT_PTR) -1 /* IDispatch::GetTypeInfo */ ,
    0 /* (void *) (INT_PTR) -1 /* IDispatch::GetIDsOfNames */ ,
    0 /* IDispatch_Invoke_Proxy */ ,
    (void *) (INT_PTR) -1 /* IRTCSessionReferStatusEvent::get_Session */ ,
    (void *) (INT_PTR) -1 /* IRTCSessionReferStatusEvent::get_ReferStatus */ ,
    (void *) (INT_PTR) -1 /* IRTCSessionReferStatusEvent::get_StatusCode */ ,
    (void *) (INT_PTR) -1 /* IRTCSessionReferStatusEvent::get_StatusText */
};


static const PRPC_STUB_FUNCTION IRTCSessionReferStatusEvent_table[] =
{
    STUB_FORWARDING_FUNCTION,
    STUB_FORWARDING_FUNCTION,
    STUB_FORWARDING_FUNCTION,
    STUB_FORWARDING_FUNCTION,
    NdrStubCall2,
    NdrStubCall2,
    NdrStubCall2,
    NdrStubCall2
};

CInterfaceStubVtbl _IRTCSessionReferStatusEventStubVtbl =
{
    &IID_IRTCSessionReferStatusEvent,
    &IRTCSessionReferStatusEvent_ServerInfo,
    11,
    &IRTCSessionReferStatusEvent_table[-3],
    CStdStubBuffer_DELEGATING_METHODS
};


/* Object interface: IRTCSessionReferredEvent, ver. 0.0,
   GUID={0x176A6828,0x4FCC,0x4F28,{0xA8,0x62,0x04,0x59,0x7A,0x6C,0xF1,0xC4}} */

#pragma code_seg(".orpc")
static const unsigned short IRTCSessionReferredEvent_FormatStringOffsetTable[] =
    {
    (unsigned short) -1,
    (unsigned short) -1,
    (unsigned short) -1,
    (unsigned short) -1,
    9480,
    4044,
    4080,
    5916,
    9516,
    7020,
    9546
    };

static const MIDL_STUBLESS_PROXY_INFO IRTCSessionReferredEvent_ProxyInfo =
    {
    &Object_StubDesc,
    __MIDL_ProcFormatString.Format,
    &IRTCSessionReferredEvent_FormatStringOffsetTable[-3],
    0,
    0,
    0
    };


static const MIDL_SERVER_INFO IRTCSessionReferredEvent_ServerInfo = 
    {
    &Object_StubDesc,
    0,
    __MIDL_ProcFormatString.Format,
    &IRTCSessionReferredEvent_FormatStringOffsetTable[-3],
    0,
    0,
    0,
    0};
CINTERFACE_PROXY_VTABLE(14) _IRTCSessionReferredEventProxyVtbl = 
{
    &IRTCSessionReferredEvent_ProxyInfo,
    &IID_IRTCSessionReferredEvent,
    IUnknown_QueryInterface_Proxy,
    IUnknown_AddRef_Proxy,
    IUnknown_Release_Proxy ,
    0 /* (void *) (INT_PTR) -1 /* IDispatch::GetTypeInfoCount */ ,
    0 /* (void *) (INT_PTR) -1 /* IDispatch::GetTypeInfo */ ,
    0 /* (void *) (INT_PTR) -1 /* IDispatch::GetIDsOfNames */ ,
    0 /* IDispatch_Invoke_Proxy */ ,
    (void *) (INT_PTR) -1 /* IRTCSessionReferredEvent::get_Session */ ,
    (void *) (INT_PTR) -1 /* IRTCSessionReferredEvent::get_ReferredByURI */ ,
    (void *) (INT_PTR) -1 /* IRTCSessionReferredEvent::get_ReferToURI */ ,
    (void *) (INT_PTR) -1 /* IRTCSessionReferredEvent::get_ReferCookie */ ,
    (void *) (INT_PTR) -1 /* IRTCSessionReferredEvent::Accept */ ,
    (void *) (INT_PTR) -1 /* IRTCSessionReferredEvent::Reject */ ,
    (void *) (INT_PTR) -1 /* IRTCSessionReferredEvent::SetReferredSessionState */
};


static const PRPC_STUB_FUNCTION IRTCSessionReferredEvent_table[] =
{
    STUB_FORWARDING_FUNCTION,
    STUB_FORWARDING_FUNCTION,
    STUB_FORWARDING_FUNCTION,
    STUB_FORWARDING_FUNCTION,
    NdrStubCall2,
    NdrStubCall2,
    NdrStubCall2,
    NdrStubCall2,
    NdrStubCall2,
    NdrStubCall2,
    NdrStubCall2
};

CInterfaceStubVtbl _IRTCSessionReferredEventStubVtbl =
{
    &IID_IRTCSessionReferredEvent,
    &IRTCSessionReferredEvent_ServerInfo,
    14,
    &IRTCSessionReferredEvent_table[-3],
    CStdStubBuffer_DELEGATING_METHODS
};


/* Object interface: IRTCSessionDescriptionManager, ver. 0.0,
   GUID={0xBA7F518E,0xD336,0x4070,{0x93,0xA6,0x86,0x53,0x95,0xC8,0x43,0xF9}} */

#pragma code_seg(".orpc")
static const unsigned short IRTCSessionDescriptionManager_FormatStringOffsetTable[] =
    {
    9582
    };

static const MIDL_STUBLESS_PROXY_INFO IRTCSessionDescriptionManager_ProxyInfo =
    {
    &Object_StubDesc,
    __MIDL_ProcFormatString.Format,
    &IRTCSessionDescriptionManager_FormatStringOffsetTable[-3],
    0,
    0,
    0
    };


static const MIDL_SERVER_INFO IRTCSessionDescriptionManager_ServerInfo = 
    {
    &Object_StubDesc,
    0,
    __MIDL_ProcFormatString.Format,
    &IRTCSessionDescriptionManager_FormatStringOffsetTable[-3],
    0,
    0,
    0,
    0};
CINTERFACE_PROXY_VTABLE(4) _IRTCSessionDescriptionManagerProxyVtbl = 
{
    &IRTCSessionDescriptionManager_ProxyInfo,
    &IID_IRTCSessionDescriptionManager,
    IUnknown_QueryInterface_Proxy,
    IUnknown_AddRef_Proxy,
    IUnknown_Release_Proxy ,
    (void *) (INT_PTR) -1 /* IRTCSessionDescriptionManager::EvaluateSessionDescription */
};

const CInterfaceStubVtbl _IRTCSessionDescriptionManagerStubVtbl =
{
    &IID_IRTCSessionDescriptionManager,
    &IRTCSessionDescriptionManager_ServerInfo,
    4,
    0, /* pure interpreted */
    CStdStubBuffer_METHODS
};


/* Object interface: IRTCEnumPresenceDevices, ver. 0.0,
   GUID={0x708C2AB7,0x8BF8,0x42f8,{0x8C,0x7D,0x63,0x51,0x97,0xAD,0x55,0x39}} */

#pragma code_seg(".orpc")
static const unsigned short IRTCEnumPresenceDevices_FormatStringOffsetTable[] =
    {
    9630,
    30,
    7374,
    9678
    };

static const MIDL_STUBLESS_PROXY_INFO IRTCEnumPresenceDevices_ProxyInfo =
    {
    &Object_StubDesc,
    __MIDL_ProcFormatString.Format,
    &IRTCEnumPresenceDevices_FormatStringOffsetTable[-3],
    0,
    0,
    0
    };


static const MIDL_SERVER_INFO IRTCEnumPresenceDevices_ServerInfo = 
    {
    &Object_StubDesc,
    0,
    __MIDL_ProcFormatString.Format,
    &IRTCEnumPresenceDevices_FormatStringOffsetTable[-3],
    0,
    0,
    0,
    0};
CINTERFACE_PROXY_VTABLE(7) _IRTCEnumPresenceDevicesProxyVtbl = 
{
    &IRTCEnumPresenceDevices_ProxyInfo,
    &IID_IRTCEnumPresenceDevices,
    IUnknown_QueryInterface_Proxy,
    IUnknown_AddRef_Proxy,
    IUnknown_Release_Proxy ,
    (void *) (INT_PTR) -1 /* IRTCEnumPresenceDevices::Next */ ,
    (void *) (INT_PTR) -1 /* IRTCEnumPresenceDevices::Reset */ ,
    (void *) (INT_PTR) -1 /* IRTCEnumPresenceDevices::Skip */ ,
    (void *) (INT_PTR) -1 /* IRTCEnumPresenceDevices::Clone */
};

const CInterfaceStubVtbl _IRTCEnumPresenceDevicesStubVtbl =
{
    &IID_IRTCEnumPresenceDevices,
    &IRTCEnumPresenceDevices_ServerInfo,
    7,
    0, /* pure interpreted */
    CStdStubBuffer_METHODS
};


/* Object interface: IRTCPresenceDevice, ver. 0.0,
   GUID={0xBC6A90DD,0xAD9A,0x48da,{0x9B,0x0C,0x25,0x15,0xE3,0x85,0x21,0xAD}} */

#pragma code_seg(".orpc")
static const unsigned short IRTCPresenceDevice_FormatStringOffsetTable[] =
    {
    9714,
    3894,
    9750,
    9792
    };

static const MIDL_STUBLESS_PROXY_INFO IRTCPresenceDevice_ProxyInfo =
    {
    &Object_StubDesc,
    __MIDL_ProcFormatString.Format,
    &IRTCPresenceDevice_FormatStringOffsetTable[-3],
    0,
    0,
    0
    };


static const MIDL_SERVER_INFO IRTCPresenceDevice_ServerInfo = 
    {
    &Object_StubDesc,
    0,
    __MIDL_ProcFormatString.Format,
    &IRTCPresenceDevice_FormatStringOffsetTable[-3],
    0,
    0,
    0,
    0};
CINTERFACE_PROXY_VTABLE(7) _IRTCPresenceDeviceProxyVtbl = 
{
    &IRTCPresenceDevice_ProxyInfo,
    &IID_IRTCPresenceDevice,
    IUnknown_QueryInterface_Proxy,
    IUnknown_AddRef_Proxy,
    IUnknown_Release_Proxy ,
    (void *) (INT_PTR) -1 /* IRTCPresenceDevice::get_Status */ ,
    (void *) (INT_PTR) -1 /* IRTCPresenceDevice::get_Notes */ ,
    (void *) (INT_PTR) -1 /* IRTCPresenceDevice::get_PresenceProperty */ ,
    (void *) (INT_PTR) -1 /* IRTCPresenceDevice::GetPresenceData */
};

const CInterfaceStubVtbl _IRTCPresenceDeviceStubVtbl =
{
    &IID_IRTCPresenceDevice,
    &IRTCPresenceDevice_ServerInfo,
    7,
    0, /* pure interpreted */
    CStdStubBuffer_METHODS
};


/* Object interface: IRTCPresenceDevice2, ver. 0.0,
   GUID={0x00DE7891,0x77A8,0x4123,{0xA9,0xA4,0x4E,0x57,0x28,0xBD,0x8A,0xC3}} */

#pragma code_seg(".orpc")
static const unsigned short IRTCPresenceDevice2_FormatStringOffsetTable[] =
    {
    9714,
    3894,
    9750,
    9792,
    7818
    };

static const MIDL_STUBLESS_PROXY_INFO IRTCPresenceDevice2_ProxyInfo =
    {
    &Object_StubDesc,
    __MIDL_ProcFormatString.Format,
    &IRTCPresenceDevice2_FormatStringOffsetTable[-3],
    0,
    0,
    0
    };


static const MIDL_SERVER_INFO IRTCPresenceDevice2_ServerInfo = 
    {
    &Object_StubDesc,
    0,
    __MIDL_ProcFormatString.Format,
    &IRTCPresenceDevice2_FormatStringOffsetTable[-3],
    0,
    0,
    0,
    0};
CINTERFACE_PROXY_VTABLE(8) _IRTCPresenceDevice2ProxyVtbl = 
{
    &IRTCPresenceDevice2_ProxyInfo,
    &IID_IRTCPresenceDevice2,
    IUnknown_QueryInterface_Proxy,
    IUnknown_AddRef_Proxy,
    IUnknown_Release_Proxy ,
    (void *) (INT_PTR) -1 /* IRTCPresenceDevice::get_Status */ ,
    (void *) (INT_PTR) -1 /* IRTCPresenceDevice::get_Notes */ ,
    (void *) (INT_PTR) -1 /* IRTCPresenceDevice::get_PresenceProperty */ ,
    (void *) (INT_PTR) -1 /* IRTCPresenceDevice::GetPresenceData */ ,
    (void *) (INT_PTR) -1 /* IRTCPresenceDevice2::get_DeviceID */
};

const CInterfaceStubVtbl _IRTCPresenceDevice2StubVtbl =
{
    &IID_IRTCPresenceDevice2,
    &IRTCPresenceDevice2_ServerInfo,
    8,
    0, /* pure interpreted */
    CStdStubBuffer_METHODS
};

static const MIDL_STUB_DESC Object_StubDesc = 
    {
    0,
    NdrOleAllocate,
    NdrOleFree,
    0,
    0,
    0,
    0,
    0,
    __MIDL_TypeFormatString.Format,
    1, /* -error bounds_check flag */
    0x50002, /* Ndr library version */
    0,
    0x600016e, /* MIDL Version 6.0.366 */
    0,
    UserMarshalRoutines,
    0,  /* notify & notify_flag routine table */
    0x1, /* MIDL flag */
    0, /* cs routines */
    0,   /* proxy/server info */
    0   /* Reserved5 */
    };

const CInterfaceProxyVtbl * _rtccore_ProxyVtblList[] = 
{
    ( CInterfaceProxyVtbl *) &_IRTCClientPortManagementProxyVtbl,
    ( CInterfaceProxyVtbl *) &_IRTCSessionStateChangeEventProxyVtbl,
    ( CInterfaceProxyVtbl *) &_IRTCClientProvisioningProxyVtbl,
    ( CInterfaceProxyVtbl *) &_IRTCMediaRequestEventProxyVtbl,
    ( CInterfaceProxyVtbl *) &_IRTCEnumBuddiesProxyVtbl,
    ( CInterfaceProxyVtbl *) &_IRTCRegistrationStateChangeEventProxyVtbl,
    ( CInterfaceProxyVtbl *) &_IRTCEnumProfilesProxyVtbl,
    ( CInterfaceProxyVtbl *) &_IRTCProfile3ProxyVtbl,
    ( CInterfaceProxyVtbl *) &_IRTCClient2ProxyVtbl,
    ( CInterfaceProxyVtbl *) &_IRTCBuddyEvent2ProxyVtbl,
    ( CInterfaceProxyVtbl *) &_IRTCSessionReferredEventProxyVtbl,
    ( CInterfaceProxyVtbl *) &_IRTCEnumParticipantsProxyVtbl,
    ( CInterfaceProxyVtbl *) &_IRTCUserSearchProxyVtbl,
    ( CInterfaceProxyVtbl *) &_IRTCPresenceContactProxyVtbl,
    ( CInterfaceProxyVtbl *) &_IRTCPresenceStatusEventProxyVtbl,
    ( CInterfaceProxyVtbl *) &_IRTCProfileEventProxyVtbl,
    ( CInterfaceProxyVtbl *) &_IRTCMessagingEventProxyVtbl,
    ( CInterfaceProxyVtbl *) &_IRTCClientProxyVtbl,
    ( CInterfaceProxyVtbl *) &_IRTCPortManagerProxyVtbl,
    ( CInterfaceProxyVtbl *) &_IRTCProfile2ProxyVtbl,
    ( CInterfaceProxyVtbl *) &_IRTCIntensityEventProxyVtbl,
    ( CInterfaceProxyVtbl *) &_IRTCBuddyEventProxyVtbl,
    ( CInterfaceProxyVtbl *) &_IRTCWatcherEventProxyVtbl,
    ( CInterfaceProxyVtbl *) &_IRTCBuddyGroupProxyVtbl,
    ( CInterfaceProxyVtbl *) &_IRTCRoamingEventProxyVtbl,
    ( CInterfaceProxyVtbl *) &_IRTCPresencePropertyEventProxyVtbl,
    ( CInterfaceProxyVtbl *) &_IRTCSessionStateChangeEvent2ProxyVtbl,
    ( CInterfaceProxyVtbl *) &_IRTCEnumUserSearchResultsProxyVtbl,
    ( CInterfaceProxyVtbl *) &_IRTCClientEventProxyVtbl,
    ( CInterfaceProxyVtbl *) &_IRTCWatcher2ProxyVtbl,
    ( CInterfaceProxyVtbl *) &_IRTCReInviteEventProxyVtbl,
    ( CInterfaceProxyVtbl *) &_IRTCSessionProxyVtbl,
    ( CInterfaceProxyVtbl *) &_IRTCBuddy2ProxyVtbl,
    ( CInterfaceProxyVtbl *) &_IRTCPresenceDataEventProxyVtbl,
    ( CInterfaceProxyVtbl *) &_IRTCSessionDescriptionManagerProxyVtbl,
    ( CInterfaceProxyVtbl *) &_IRTCPresenceDevice2ProxyVtbl,
    ( CInterfaceProxyVtbl *) &_IRTCSessionCallControlProxyVtbl,
    ( CInterfaceProxyVtbl *) &_IRTCCollectionProxyVtbl,
    ( CInterfaceProxyVtbl *) &_IRTCParticipantStateChangeEventProxyVtbl,
    ( CInterfaceProxyVtbl *) &_IRTCSessionOperationCompleteEvent2ProxyVtbl,
    ( CInterfaceProxyVtbl *) &_IRTCProfileProxyVtbl,
    ( CInterfaceProxyVtbl *) &_IRTCSession3ProxyVtbl,
    ( CInterfaceProxyVtbl *) &_IRTCInfoEventProxyVtbl,
    ( CInterfaceProxyVtbl *) &_IRTCUserSearchResultProxyVtbl,
    ( CInterfaceProxyVtbl *) &_IRTCParticipant2ProxyVtbl,
    ( CInterfaceProxyVtbl *) &_IRTCClientProvisioning2ProxyVtbl,
    ( CInterfaceProxyVtbl *) &_IRTCEnumPresenceDevicesProxyVtbl,
    ( CInterfaceProxyVtbl *) &_IRTCSessionOperationCompleteEventProxyVtbl,
    ( CInterfaceProxyVtbl *) &_IRTCEventNotificationProxyVtbl,
    ( CInterfaceProxyVtbl *) &_IRTCBuddyProxyVtbl,
    ( CInterfaceProxyVtbl *) &_IRTCClientPresenceProxyVtbl,
    ( CInterfaceProxyVtbl *) &_IRTCSessionReferStatusEventProxyVtbl,
    ( CInterfaceProxyVtbl *) &_IRTCUserSearchResultsEventProxyVtbl,
    ( CInterfaceProxyVtbl *) &_IRTCBuddyGroupEventProxyVtbl,
    ( CInterfaceProxyVtbl *) &_IRTCParticipantProxyVtbl,
    ( CInterfaceProxyVtbl *) &_IRTCEnumGroupsProxyVtbl,
    ( CInterfaceProxyVtbl *) &_IRTCSessionPortManagementProxyVtbl,
    ( CInterfaceProxyVtbl *) &_IRTCEnumWatchersProxyVtbl,
    ( CInterfaceProxyVtbl *) &_IRTCWatcherProxyVtbl,
    ( CInterfaceProxyVtbl *) &_IRTCProfileEvent2ProxyVtbl,
    ( CInterfaceProxyVtbl *) &_IRTCPresenceDeviceProxyVtbl,
    ( CInterfaceProxyVtbl *) &_IRTCClientPresence2ProxyVtbl,
    ( CInterfaceProxyVtbl *) &_IRTCWatcherEvent2ProxyVtbl,
    ( CInterfaceProxyVtbl *) &_IRTCPortManager2ProxyVtbl,
    ( CInterfaceProxyVtbl *) &_IRTCUserSearchQueryProxyVtbl,
    ( CInterfaceProxyVtbl *) &_IRTCMediaEventProxyVtbl,
    ( CInterfaceProxyVtbl *) &_IRTCSession2ProxyVtbl,
    0
};

const CInterfaceStubVtbl * _rtccore_StubVtblList[] = 
{
    ( CInterfaceStubVtbl *) &_IRTCClientPortManagementStubVtbl,
    ( CInterfaceStubVtbl *) &_IRTCSessionStateChangeEventStubVtbl,
    ( CInterfaceStubVtbl *) &_IRTCClientProvisioningStubVtbl,
    ( CInterfaceStubVtbl *) &_IRTCMediaRequestEventStubVtbl,
    ( CInterfaceStubVtbl *) &_IRTCEnumBuddiesStubVtbl,
    ( CInterfaceStubVtbl *) &_IRTCRegistrationStateChangeEventStubVtbl,
    ( CInterfaceStubVtbl *) &_IRTCEnumProfilesStubVtbl,
    ( CInterfaceStubVtbl *) &_IRTCProfile3StubVtbl,
    ( CInterfaceStubVtbl *) &_IRTCClient2StubVtbl,
    ( CInterfaceStubVtbl *) &_IRTCBuddyEvent2StubVtbl,
    ( CInterfaceStubVtbl *) &_IRTCSessionReferredEventStubVtbl,
    ( CInterfaceStubVtbl *) &_IRTCEnumParticipantsStubVtbl,
    ( CInterfaceStubVtbl *) &_IRTCUserSearchStubVtbl,
    ( CInterfaceStubVtbl *) &_IRTCPresenceContactStubVtbl,
    ( CInterfaceStubVtbl *) &_IRTCPresenceStatusEventStubVtbl,
    ( CInterfaceStubVtbl *) &_IRTCProfileEventStubVtbl,
    ( CInterfaceStubVtbl *) &_IRTCMessagingEventStubVtbl,
    ( CInterfaceStubVtbl *) &_IRTCClientStubVtbl,
    ( CInterfaceStubVtbl *) &_IRTCPortManagerStubVtbl,
    ( CInterfaceStubVtbl *) &_IRTCProfile2StubVtbl,
    ( CInterfaceStubVtbl *) &_IRTCIntensityEventStubVtbl,
    ( CInterfaceStubVtbl *) &_IRTCBuddyEventStubVtbl,
    ( CInterfaceStubVtbl *) &_IRTCWatcherEventStubVtbl,
    ( CInterfaceStubVtbl *) &_IRTCBuddyGroupStubVtbl,
    ( CInterfaceStubVtbl *) &_IRTCRoamingEventStubVtbl,
    ( CInterfaceStubVtbl *) &_IRTCPresencePropertyEventStubVtbl,
    ( CInterfaceStubVtbl *) &_IRTCSessionStateChangeEvent2StubVtbl,
    ( CInterfaceStubVtbl *) &_IRTCEnumUserSearchResultsStubVtbl,
    ( CInterfaceStubVtbl *) &_IRTCClientEventStubVtbl,
    ( CInterfaceStubVtbl *) &_IRTCWatcher2StubVtbl,
    ( CInterfaceStubVtbl *) &_IRTCReInviteEventStubVtbl,
    ( CInterfaceStubVtbl *) &_IRTCSessionStubVtbl,
    ( CInterfaceStubVtbl *) &_IRTCBuddy2StubVtbl,
    ( CInterfaceStubVtbl *) &_IRTCPresenceDataEventStubVtbl,
    ( CInterfaceStubVtbl *) &_IRTCSessionDescriptionManagerStubVtbl,
    ( CInterfaceStubVtbl *) &_IRTCPresenceDevice2StubVtbl,
    ( CInterfaceStubVtbl *) &_IRTCSessionCallControlStubVtbl,
    ( CInterfaceStubVtbl *) &_IRTCCollectionStubVtbl,
    ( CInterfaceStubVtbl *) &_IRTCParticipantStateChangeEventStubVtbl,
    ( CInterfaceStubVtbl *) &_IRTCSessionOperationCompleteEvent2StubVtbl,
    ( CInterfaceStubVtbl *) &_IRTCProfileStubVtbl,
    ( CInterfaceStubVtbl *) &_IRTCSession3StubVtbl,
    ( CInterfaceStubVtbl *) &_IRTCInfoEventStubVtbl,
    ( CInterfaceStubVtbl *) &_IRTCUserSearchResultStubVtbl,
    ( CInterfaceStubVtbl *) &_IRTCParticipant2StubVtbl,
    ( CInterfaceStubVtbl *) &_IRTCClientProvisioning2StubVtbl,
    ( CInterfaceStubVtbl *) &_IRTCEnumPresenceDevicesStubVtbl,
    ( CInterfaceStubVtbl *) &_IRTCSessionOperationCompleteEventStubVtbl,
    ( CInterfaceStubVtbl *) &_IRTCEventNotificationStubVtbl,
    ( CInterfaceStubVtbl *) &_IRTCBuddyStubVtbl,
    ( CInterfaceStubVtbl *) &_IRTCClientPresenceStubVtbl,
    ( CInterfaceStubVtbl *) &_IRTCSessionReferStatusEventStubVtbl,
    ( CInterfaceStubVtbl *) &_IRTCUserSearchResultsEventStubVtbl,
    ( CInterfaceStubVtbl *) &_IRTCBuddyGroupEventStubVtbl,
    ( CInterfaceStubVtbl *) &_IRTCParticipantStubVtbl,
    ( CInterfaceStubVtbl *) &_IRTCEnumGroupsStubVtbl,
    ( CInterfaceStubVtbl *) &_IRTCSessionPortManagementStubVtbl,
    ( CInterfaceStubVtbl *) &_IRTCEnumWatchersStubVtbl,
    ( CInterfaceStubVtbl *) &_IRTCWatcherStubVtbl,
    ( CInterfaceStubVtbl *) &_IRTCProfileEvent2StubVtbl,
    ( CInterfaceStubVtbl *) &_IRTCPresenceDeviceStubVtbl,
    ( CInterfaceStubVtbl *) &_IRTCClientPresence2StubVtbl,
    ( CInterfaceStubVtbl *) &_IRTCWatcherEvent2StubVtbl,
    ( CInterfaceStubVtbl *) &_IRTCPortManager2StubVtbl,
    ( CInterfaceStubVtbl *) &_IRTCUserSearchQueryStubVtbl,
    ( CInterfaceStubVtbl *) &_IRTCMediaEventStubVtbl,
    ( CInterfaceStubVtbl *) &_IRTCSession2StubVtbl,
    0
};

PCInterfaceName const _rtccore_InterfaceNamesList[] = 
{
    "IRTCClientPortManagement",
    "IRTCSessionStateChangeEvent",
    "IRTCClientProvisioning",
    "IRTCMediaRequestEvent",
    "IRTCEnumBuddies",
    "IRTCRegistrationStateChangeEvent",
    "IRTCEnumProfiles",
    "IRTCProfile3",
    "IRTCClient2",
    "IRTCBuddyEvent2",
    "IRTCSessionReferredEvent",
    "IRTCEnumParticipants",
    "IRTCUserSearch",
    "IRTCPresenceContact",
    "IRTCPresenceStatusEvent",
    "IRTCProfileEvent",
    "IRTCMessagingEvent",
    "IRTCClient",
    "IRTCPortManager",
    "IRTCProfile2",
    "IRTCIntensityEvent",
    "IRTCBuddyEvent",
    "IRTCWatcherEvent",
    "IRTCBuddyGroup",
    "IRTCRoamingEvent",
    "IRTCPresencePropertyEvent",
    "IRTCSessionStateChangeEvent2",
    "IRTCEnumUserSearchResults",
    "IRTCClientEvent",
    "IRTCWatcher2",
    "IRTCReInviteEvent",
    "IRTCSession",
    "IRTCBuddy2",
    "IRTCPresenceDataEvent",
    "IRTCSessionDescriptionManager",
    "IRTCPresenceDevice2",
    "IRTCSessionCallControl",
    "IRTCCollection",
    "IRTCParticipantStateChangeEvent",
    "IRTCSessionOperationCompleteEvent2",
    "IRTCProfile",
    "IRTCSession3",
    "IRTCInfoEvent",
    "IRTCUserSearchResult",
    "IRTCParticipant2",
    "IRTCClientProvisioning2",
    "IRTCEnumPresenceDevices",
    "IRTCSessionOperationCompleteEvent",
    "IRTCEventNotification",
    "IRTCBuddy",
    "IRTCClientPresence",
    "IRTCSessionReferStatusEvent",
    "IRTCUserSearchResultsEvent",
    "IRTCBuddyGroupEvent",
    "IRTCParticipant",
    "IRTCEnumGroups",
    "IRTCSessionPortManagement",
    "IRTCEnumWatchers",
    "IRTCWatcher",
    "IRTCProfileEvent2",
    "IRTCPresenceDevice",
    "IRTCClientPresence2",
    "IRTCWatcherEvent2",
    "IRTCPortManager2",
    "IRTCUserSearchQuery",
    "IRTCMediaEvent",
    "IRTCSession2",
    0
};

const IID *  _rtccore_BaseIIDList[] = 
{
    0,
    &IID_IDispatch,
    0,
    &IID_IDispatch,
    0,
    &IID_IDispatch,
    0,
    0,
    0,
    &IID_IDispatch,
    &IID_IDispatch,
    0,
    0,
    0,
    &IID_IDispatch,
    &IID_IDispatch,
    &IID_IDispatch,
    0,
    0,
    0,
    &IID_IDispatch,
    &IID_IDispatch,
    &IID_IDispatch,
    0,
    &IID_IDispatch,
    &IID_IDispatch,
    &IID_IDispatch,
    0,
    &IID_IDispatch,
    0,
    &IID_IDispatch,
    0,
    0,
    &IID_IDispatch,
    0,
    0,
    0,
    &IID_IDispatch,
    &IID_IDispatch,
    &IID_IDispatch,
    0,
    0,
    &IID_IDispatch,
    0,
    0,
    0,
    0,
    &IID_IDispatch,
    0,
    0,
    0,
    &IID_IDispatch,
    &IID_IDispatch,
    &IID_IDispatch,
    0,
    0,
    0,
    0,
    0,
    &IID_IDispatch,
    0,
    0,
    &IID_IDispatch,
    0,
    0,
    &IID_IDispatch,
    0,
    0
};


#define _rtccore_CHECK_IID(n)	IID_GENERIC_CHECK_IID( _rtccore, pIID, n)

int __stdcall _rtccore_IID_Lookup( const IID * pIID, int * pIndex )
{
    IID_BS_LOOKUP_SETUP

    IID_BS_LOOKUP_INITIAL_TEST( _rtccore, 67, 64 )
    IID_BS_LOOKUP_NEXT_TEST( _rtccore, 32 )
    IID_BS_LOOKUP_NEXT_TEST( _rtccore, 16 )
    IID_BS_LOOKUP_NEXT_TEST( _rtccore, 8 )
    IID_BS_LOOKUP_NEXT_TEST( _rtccore, 4 )
    IID_BS_LOOKUP_NEXT_TEST( _rtccore, 2 )
    IID_BS_LOOKUP_NEXT_TEST( _rtccore, 1 )
    IID_BS_LOOKUP_RETURN_RESULT( _rtccore, 67, *pIndex )
    
}

const ExtendedProxyFileInfo rtccore_ProxyFileInfo = 
{
    (PCInterfaceProxyVtblList *) & _rtccore_ProxyVtblList,
    (PCInterfaceStubVtblList *) & _rtccore_StubVtblList,
    (const PCInterfaceName * ) & _rtccore_InterfaceNamesList,
    (const IID ** ) & _rtccore_BaseIIDList,
    & _rtccore_IID_Lookup, 
    67,
    2,
    0, /* table of [async_uuid] interfaces */
    0, /* Filler1 */
    0, /* Filler2 */
    0  /* Filler3 */
};
#pragma optimize("", on )
#if _MSC_VER >= 1200
#pragma warning(pop)
#endif


#endif /* !defined(_M_IA64) && !defined(_M_AMD64)*/

