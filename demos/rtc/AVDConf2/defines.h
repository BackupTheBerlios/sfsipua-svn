// Helper macros
#define SAFE_RELEASE(x) {if(x!=NULL){(x)->Release();(x)=NULL;}}
#define SAFE_FREE_STRING(x) {if(x!=NULL){SysFreeString(x);(x)=NULL;}}

// Timer ID
#define TID_CPUPERFEVENT	1		// CPU Utilization timer event
#define TID_SIPLOGIN		2		// SIP login timeout event

// Default Timer Value
#define	CPU_TIMER_TICK		1000	// 1 sec.
#define	SIP_LOGIN_TIMEOUT	15000	// 15 sec.

// User Define RTC Event
#define WM_RTC_EVENT      WM_USER+100

#define QCIF_CX_SIZE  176
#define QCIF_CY_SIZE  144
#define QQCIF_CX_SIZE (QCIF_CX_SIZE/2)
#define QQCIF_CY_SIZE (QCIF_CY_SIZE/2)

struct SESSION_DATA {
	BSTR	bstrName;
	BSTR	bstrURI;
	BSTR	bstrAccount;
	BSTR	bstrPassword;
	UINT	bAutoAdd;
};

// List of message dialogs

// Status Define macros
#define	STATUS_READY	"Ready"
#define STATUS_DIALING	"Initiating Audio/Video Call"
#define STATUS_INCOMING	"Receiving Audio/Video Call"
#define	STATUS_AVCALL	"Audio/Video Call In-Progress"
#define STATUS_AVHANGUP	"Audio/Video Call Terminated"
#define STATUS_CHAT		"Chat Session In Progress"
#define STATUS_ENDCHAT	"Chat Session Terminated"
#define STATUS_APPSHARE	"Application Sharing Started"
#define	STATUS_ENDAPP	"Application Sharing Terminated"

