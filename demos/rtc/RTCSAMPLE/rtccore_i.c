

/* this ALWAYS GENERATED file contains the IIDs and CLSIDs */

/* link this file in with the server and any clients */


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

#pragma warning( disable: 4049 )  /* more than 64k source lines */


#ifdef __cplusplus
extern "C"{
#endif 


#include <rpc.h>
#include <rpcndr.h>

#ifdef _MIDL_USE_GUIDDEF_

#ifndef INITGUID
#define INITGUID
#include <guiddef.h>
#undef INITGUID
#else
#include <guiddef.h>
#endif

#define MIDL_DEFINE_GUID(type,name,l,w1,w2,b1,b2,b3,b4,b5,b6,b7,b8) \
        DEFINE_GUID(name,l,w1,w2,b1,b2,b3,b4,b5,b6,b7,b8)

#else // !_MIDL_USE_GUIDDEF_

#ifndef __IID_DEFINED__
#define __IID_DEFINED__

typedef struct _IID
{
    unsigned long x;
    unsigned short s1;
    unsigned short s2;
    unsigned char  c[8];
} IID;

#endif // __IID_DEFINED__

#ifndef CLSID_DEFINED
#define CLSID_DEFINED
typedef IID CLSID;
#endif // CLSID_DEFINED

#define MIDL_DEFINE_GUID(type,name,l,w1,w2,b1,b2,b3,b4,b5,b6,b7,b8) \
        const type name = {l,w1,w2,{b1,b2,b3,b4,b5,b6,b7,b8}}

#endif !_MIDL_USE_GUIDDEF_

MIDL_DEFINE_GUID(IID, IID_IRTCClient,0x07829e45,0x9a34,0x408e,0xa0,0x11,0xbd,0xdf,0x13,0x48,0x7c,0xd1);


MIDL_DEFINE_GUID(IID, IID_IRTCClient2,0x0C91D71D,0x1064,0x42da,0xBF,0xA5,0x57,0x2B,0xEB,0x8E,0xEA,0x84);


MIDL_DEFINE_GUID(IID, IID_IRTCClientPresence,0x11c3cbcc,0x0744,0x42d1,0x96,0x8a,0x51,0xaa,0x1b,0xb2,0x74,0xc6);


MIDL_DEFINE_GUID(IID, IID_IRTCClientPresence2,0xAD1809E8,0x62F7,0x4783,0x90,0x9A,0x29,0xC9,0xD2,0xCB,0x1D,0x34);


MIDL_DEFINE_GUID(IID, IID_IRTCClientProvisioning,0xB9F5CF06,0x65B9,0x4a80,0xA0,0xE6,0x73,0xCA,0xE3,0xEF,0x38,0x22);


MIDL_DEFINE_GUID(IID, IID_IRTCClientProvisioning2,0xA70909B5,0xF40E,0x4587,0xBB,0x75,0xE6,0xBC,0x08,0x45,0x02,0x3E);


MIDL_DEFINE_GUID(IID, IID_IRTCProfile,0xd07eca9e,0x4062,0x4dd4,0x9e,0x7d,0x72,0x2a,0x49,0xba,0x73,0x03);


MIDL_DEFINE_GUID(IID, IID_IRTCProfile2,0x4B81F84E,0xBDC7,0x4184,0x91,0x54,0x3C,0xB2,0xDD,0x79,0x17,0xFB);


MIDL_DEFINE_GUID(IID, IID_IRTCProfile3,0x051caa1d,0x2e4e,0x4187,0xb9,0x47,0x69,0xa0,0xc9,0x9b,0xa7,0x0b);


MIDL_DEFINE_GUID(IID, IID_IRTCSession,0x387c8086,0x99be,0x42fb,0x99,0x73,0x7c,0x0f,0xc0,0xca,0x9f,0xa8);


MIDL_DEFINE_GUID(IID, IID_IRTCSession2,0x17D7CDFC,0xB007,0x484c,0x99,0xD2,0x86,0xA8,0xA8,0x20,0x99,0x1D);


MIDL_DEFINE_GUID(IID, IID_IRTCSession3,0xA46E81AD,0x1D5A,0x4063,0x95,0x21,0x62,0xE1,0xFA,0x85,0xDF,0x5C);


MIDL_DEFINE_GUID(IID, IID_IRTCSessionCallControl,0xE9A50D94,0x190B,0x4F82,0x95,0x30,0x3B,0x8E,0xBF,0x60,0x75,0x8A);


MIDL_DEFINE_GUID(IID, IID_IRTCParticipant,0xae86add5,0x26b1,0x4414,0xaf,0x1d,0xb9,0x4c,0xd9,0x38,0xd7,0x39);


MIDL_DEFINE_GUID(IID, IID_IRTCParticipant2,0xB492D4B4,0x42DF,0x430a,0x84,0x8F,0x36,0xFB,0x39,0xFD,0x00,0x5F);


MIDL_DEFINE_GUID(IID, IID_IRTCRoamingEvent,0x79960a6b,0x0cb1,0x4dc8,0xa8,0x05,0x73,0x18,0xe9,0x99,0x02,0xe8);


MIDL_DEFINE_GUID(IID, IID_IRTCProfileEvent,0xD6D5AB3B,0x770E,0x43e8,0x80,0x0A,0x79,0xB0,0x62,0x39,0x5F,0xCA);


MIDL_DEFINE_GUID(IID, IID_IRTCProfileEvent2,0x62E56EDC,0x03FA,0x4121,0x94,0xFB,0x23,0x49,0x3F,0xD0,0xAE,0x64);


MIDL_DEFINE_GUID(IID, IID_IRTCClientEvent,0x2b493b7a,0x3cba,0x4170,0x9c,0x8b,0x76,0xa9,0xda,0xcd,0xd6,0x44);


MIDL_DEFINE_GUID(IID, IID_IRTCRegistrationStateChangeEvent,0x62d0991b,0x50ab,0x4f02,0xb9,0x48,0xca,0x94,0xf2,0x6f,0x8f,0x95);


MIDL_DEFINE_GUID(IID, IID_IRTCSessionStateChangeEvent,0xb5bad703,0x5952,0x48b3,0x93,0x21,0x7f,0x45,0x00,0x52,0x15,0x06);


MIDL_DEFINE_GUID(IID, IID_IRTCSessionStateChangeEvent2,0x4F933171,0x6F95,0x4880,0x80,0xD9,0x2E,0xC8,0xD4,0x95,0xD2,0x61);


MIDL_DEFINE_GUID(IID, IID_IRTCSessionOperationCompleteEvent,0xa6bff4c0,0xf7c8,0x4d3c,0x9a,0x41,0x35,0x50,0xf7,0x8a,0x95,0xb0);


MIDL_DEFINE_GUID(IID, IID_IRTCSessionOperationCompleteEvent2,0xf6fc2a9b,0xd5bc,0x4241,0xb4,0x36,0x1b,0x84,0x60,0xc1,0x38,0x32);


MIDL_DEFINE_GUID(IID, IID_IRTCParticipantStateChangeEvent,0x09bcb597,0xf0fa,0x48f9,0xb4,0x20,0x46,0x8c,0xea,0x7f,0xde,0x04);


MIDL_DEFINE_GUID(IID, IID_IRTCMediaEvent,0x099944fb,0xbcda,0x453e,0x8c,0x41,0xe1,0x3d,0xa2,0xad,0xf7,0xf3);


MIDL_DEFINE_GUID(IID, IID_IRTCIntensityEvent,0x4c23bf51,0x390c,0x4992,0xa4,0x1d,0x41,0xee,0xc0,0x5b,0x2a,0x4b);


MIDL_DEFINE_GUID(IID, IID_IRTCMessagingEvent,0xd3609541,0x1b29,0x4de5,0xa4,0xad,0x5a,0xeb,0xaf,0x31,0x95,0x12);


MIDL_DEFINE_GUID(IID, IID_IRTCBuddyEvent,0xf36d755d,0x17e6,0x404e,0x95,0x4f,0x0f,0xc0,0x75,0x74,0xc7,0x8d);


MIDL_DEFINE_GUID(IID, IID_IRTCBuddyEvent2,0x484A7F1E,0x73F0,0x4990,0xBF,0xC2,0x60,0xBC,0x39,0x78,0xA7,0x20);


MIDL_DEFINE_GUID(IID, IID_IRTCWatcherEvent,0xf30d7261,0x587a,0x424f,0x82,0x2c,0x31,0x27,0x88,0xf4,0x35,0x48);


MIDL_DEFINE_GUID(IID, IID_IRTCWatcherEvent2,0xE52891E8,0x188C,0x49AF,0xB0,0x05,0x98,0xED,0x13,0xF8,0x3F,0x9C);


MIDL_DEFINE_GUID(IID, IID_IRTCBuddyGroupEvent,0x3A79E1D1,0xB736,0x4414,0x96,0xF8,0xBB,0xC7,0xF0,0x88,0x63,0xE4);


MIDL_DEFINE_GUID(IID, IID_IRTCInfoEvent,0x4E1D68AE,0x1912,0x4f49,0xB2,0xC3,0x59,0x4F,0xAD,0xFD,0x42,0x5F);


MIDL_DEFINE_GUID(IID, IID_IRTCMediaRequestEvent,0x52572D15,0x148C,0x4d97,0xA3,0x6C,0x2D,0xA5,0x5C,0x28,0x9D,0x63);


MIDL_DEFINE_GUID(IID, IID_IRTCReInviteEvent,0x11558D84,0x204C,0x43e7,0x99,0xB0,0x20,0x34,0xE9,0x41,0x7F,0x7D);


MIDL_DEFINE_GUID(IID, IID_IRTCPresencePropertyEvent,0xF777F570,0xA820,0x49d5,0x86,0xBD,0xE0,0x99,0x49,0x3F,0x15,0x18);


MIDL_DEFINE_GUID(IID, IID_IRTCPresenceDataEvent,0x38F0E78C,0x8B87,0x4c04,0xA8,0x2D,0xAE,0xDD,0x83,0xC9,0x09,0xBB);


MIDL_DEFINE_GUID(IID, IID_IRTCPresenceStatusEvent,0x78673F32,0x4A0F,0x462c,0x89,0xAA,0xEE,0x77,0x06,0x70,0x76,0x78);


MIDL_DEFINE_GUID(IID, IID_IRTCCollection,0xEC7C8096,0xB918,0x4044,0x94,0xF1,0xE4,0xFB,0xA0,0x36,0x1D,0x5C);


MIDL_DEFINE_GUID(IID, IID_IRTCEnumParticipants,0xfcd56f29,0x4a4f,0x41b2,0xba,0x5c,0xf5,0xbc,0xcc,0x06,0x0b,0xf6);


MIDL_DEFINE_GUID(IID, IID_IRTCEnumProfiles,0x29b7c41c,0xed82,0x4bca,0x84,0xad,0x39,0xd5,0x10,0x1b,0x58,0xe3);


MIDL_DEFINE_GUID(IID, IID_IRTCEnumBuddies,0xf7296917,0x5569,0x4b3b,0xb3,0xaf,0x98,0xd1,0x14,0x4b,0x2b,0x87);


MIDL_DEFINE_GUID(IID, IID_IRTCEnumWatchers,0xa87d55d7,0xdb74,0x4ed1,0x9c,0xa4,0x77,0xa0,0xe4,0x1b,0x41,0x3e);


MIDL_DEFINE_GUID(IID, IID_IRTCEnumGroups,0x742378D6,0xA141,0x4415,0x8F,0x27,0x35,0xD9,0x90,0x76,0xCF,0x5D);


MIDL_DEFINE_GUID(IID, IID_IRTCPresenceContact,0x8b22f92c,0xcd90,0x42db,0xa7,0x33,0x21,0x22,0x05,0xc3,0xe3,0xdf);


MIDL_DEFINE_GUID(IID, IID_IRTCBuddy,0xfcb136c8,0x7b90,0x4e0c,0xbe,0xfe,0x56,0xed,0xf0,0xba,0x6f,0x1c);


MIDL_DEFINE_GUID(IID, IID_IRTCBuddy2,0x102F9588,0x23E7,0x40e3,0x95,0x4D,0xCD,0x7A,0x1D,0x5C,0x03,0x61);


MIDL_DEFINE_GUID(IID, IID_IRTCWatcher,0xc7cedad8,0x346b,0x4d1b,0xac,0x02,0xa2,0x08,0x8d,0xf9,0xbe,0x4f);


MIDL_DEFINE_GUID(IID, IID_IRTCWatcher2,0xD4D9967F,0xD011,0x4b1d,0x91,0xE3,0xAB,0xA7,0x8F,0x96,0x39,0x3D);


MIDL_DEFINE_GUID(IID, IID_IRTCBuddyGroup,0x60361E68,0x9164,0x4389,0xA4,0xC6,0xD0,0xB3,0x92,0x5B,0xDA,0x5E);


MIDL_DEFINE_GUID(IID, IID_IRTCEventNotification,0x13fa24c7,0x5748,0x4b21,0x91,0xf5,0x73,0x97,0x60,0x9c,0xe7,0x47);


MIDL_DEFINE_GUID(IID, DIID_IRTCDispatchEventNotification,0x176ddfbe,0xfec0,0x4d55,0xbc,0x87,0x84,0xcf,0xf1,0xef,0x7f,0x91);


MIDL_DEFINE_GUID(IID, IID_IRTCPortManager,0xDA77C14B,0x6208,0x43ca,0x8D,0xDF,0x5B,0x60,0xA0,0xA6,0x9F,0xAC);


MIDL_DEFINE_GUID(IID, IID_IRTCPortManager2,0x269F36EF,0x334C,0x43f7,0xB6,0xE2,0x36,0x7E,0x8D,0x30,0x7A,0xEB);


MIDL_DEFINE_GUID(IID, IID_IRTCSessionPortManagement,0xa072f1d6,0x0286,0x4e1f,0x85,0xf2,0x17,0xa2,0x94,0x84,0x56,0xec);


MIDL_DEFINE_GUID(IID, IID_IRTCClientPortManagement,0xd5df3f03,0x4bde,0x4417,0xae,0xfe,0x71,0x17,0x7b,0xda,0xea,0x66);


MIDL_DEFINE_GUID(IID, IID_IRTCUserSearch,0xB619882B,0x860C,0x4db4,0xBE,0x1B,0x69,0x3B,0x65,0x05,0xBB,0xE5);


MIDL_DEFINE_GUID(IID, IID_IRTCUserSearchQuery,0x288300F5,0xD23A,0x4365,0x9A,0x73,0x99,0x85,0xC9,0x8C,0x28,0x81);


MIDL_DEFINE_GUID(IID, IID_IRTCUserSearchResult,0x851278B2,0x9592,0x480f,0x8D,0xB5,0x2D,0xE8,0x6B,0x26,0xB5,0x4D);


MIDL_DEFINE_GUID(IID, IID_IRTCEnumUserSearchResults,0x83D4D877,0xAA5D,0x4a5b,0x8D,0x0E,0x00,0x2A,0x80,0x67,0xE0,0xE8);


MIDL_DEFINE_GUID(IID, IID_IRTCUserSearchResultsEvent,0xD8C8C3CD,0x7FAC,0x4088,0x81,0xC5,0xC2,0x4C,0xBC,0x09,0x38,0xE3);


MIDL_DEFINE_GUID(IID, IID_IRTCSessionReferStatusEvent,0x3D8FC2CD,0x5D76,0x44AB,0xBB,0x68,0x2A,0x80,0x35,0x3B,0x34,0xA2);


MIDL_DEFINE_GUID(IID, IID_IRTCSessionReferredEvent,0x176A6828,0x4FCC,0x4F28,0xA8,0x62,0x04,0x59,0x7A,0x6C,0xF1,0xC4);


MIDL_DEFINE_GUID(IID, IID_IRTCSessionDescriptionManager,0xBA7F518E,0xD336,0x4070,0x93,0xA6,0x86,0x53,0x95,0xC8,0x43,0xF9);


MIDL_DEFINE_GUID(IID, IID_IRTCEnumPresenceDevices,0x708C2AB7,0x8BF8,0x42f8,0x8C,0x7D,0x63,0x51,0x97,0xAD,0x55,0x39);


MIDL_DEFINE_GUID(IID, IID_IRTCPresenceDevice,0xBC6A90DD,0xAD9A,0x48da,0x9B,0x0C,0x25,0x15,0xE3,0x85,0x21,0xAD);


MIDL_DEFINE_GUID(IID, IID_IRTCPresenceDevice2,0x00DE7891,0x77A8,0x4123,0xA9,0xA4,0x4E,0x57,0x28,0xBD,0x8A,0xC3);


MIDL_DEFINE_GUID(IID, LIBID_RTCCORELib,0xcd260094,0xde10,0x4aee,0xac,0x73,0xef,0x87,0xf6,0xe1,0x26,0x83);


MIDL_DEFINE_GUID(CLSID, CLSID_RTCClient,0x7a42ea29,0xa2b7,0x40c4,0xb0,0x91,0xf6,0xf0,0x24,0xaa,0x89,0xbe);

#undef MIDL_DEFINE_GUID

#ifdef __cplusplus
}
#endif



