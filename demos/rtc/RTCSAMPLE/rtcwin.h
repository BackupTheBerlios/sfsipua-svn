// rtcwin.h
//

#ifndef _RTCWIN_H_
#define _RTCWIN_H_

// RTC events will be posted to the message queue with
// this user defined window message
#define WM_RTC_EVENT      WM_USER+100


#define RTCWIN_OPTIONS_MAXBW			0x00000001
#define RTCWIN_OPTIONS_T120             0x00000004

struct OPTIONS_DATA {
	DWORD EnabledOptions;
	BSTR  bstrAppName;
	BSTR  bstrAppVer;
	long  lMaxBW;
	RTC_SECURITY_LEVEL  enAVLevel;
	RTC_SECURITY_LEVEL  enT120Level;
};

class CRTCEvents;
class CRTCSession;
class CRTCSearch;
class CRTCWatcher;
class CRTCGroup;

// Class for the application window
class CRTCWin
{
public:
    CRTCWin();
    ~CRTCWin();

    // Registers the window class
    static HRESULT RegisterClass();    

    // Window procedure
    static LRESULT CALLBACK WindowProc(
        HWND hWnd,      // handle to window
        UINT uMsg,      // message identifier
        WPARAM wParam,  // first message parameter
        LPARAM lParam   // second message parameter
        );

	// Helper function for finding a node in the tree for a particular buddy.
	HRESULT TreeViewHelper_FindBuddyNode(
		IRTCBuddy * pBuddy,
		LPTVITEMEX pTvix,
		int * whichTree
		);

	// Helper function for inserting a node in the tree into the right place
	HRESULT TreeViewHelper_InsertNode(
		IRTCBuddy * pBuddy,
		WCHAR * szBuddy,
		int enStatus
		);

    // Remove a session from the session list
    HRESULT RemoveSession(
        CRTCSession * pSessWindow
        );    

    // Remove a search from the user search list
    HRESULT RemoveUserSearch(
        CRTCSearch * pSearchWindow
        );  

    // Remove a window from the watchers list
    HRESULT RemoveWatchers(
        CRTCWatcher * pWatcherWindow
        ); 

    // Remove a window from the groups list
    HRESULT RemoveGroups(
        CRTCGroup * pGroupWindow
        ); 

    // Get the local user URI
    HRESULT GetUserURI(BSTR *pbstrURI); 

    // Get the local user name
    HRESULT GetUserName(BSTR *pbstrName);

    // Get a cookie
    long GetCookie()
    {
        return m_lCookie++;
    }

    // Add a buddy
    HRESULT DoAddBuddy(BSTR bstrURI, BSTR bstrName);

    // Place a call (AV or IM)
    HRESULT DoCall(RTC_SESSION_TYPE enType, BSTR bstrURI, BSTR bstrName);

private:

    HWND    m_hWnd;
    HWND    m_hStatusBar;
	HWND	m_hBuddyTree;
	HWND	m_hOfflineParent;
	HWND	m_hOnlineParent;

    IRTCClient2 * m_pClient;
    IRTCProfile2 * m_pProfile;
    CRTCEvents * m_pEvents; 
    RTC_REGISTRATION_STATE m_enState;
    BOOL m_fPresenceEnabled;
    long m_lCookie;
	int m_nLogonAttemptCount;
	OPTIONS_DATA m_OD;
    
    std::vector<CRTCSession *> m_SessionList;
    std::vector<CRTCSearch *>  m_UserSearchList;
    std::vector<CRTCWatcher *>  m_WatchersList;
    std::vector<CRTCGroup *>  m_GroupsList;

    // Helpers
    void ShowMessageBox(PWSTR szText);
    void SetStatusText(PWSTR szText);

    // Add a session to the session list
    HRESULT AddSession(
        IRTCSession * pSession,
        RTC_SESSION_TYPE enType
        );

    // Find a session in the session list
    HRESULT FindSession(
        IRTCSession * pSession,
        CRTCSession ** ppSessWindow
        );

    // Cleanup the session list
    HRESULT CleanupSessions();

    // Add a search to the user search list
    HRESULT AddUserSearch();

    // Find a search in the user search list
    HRESULT FindUserSearch(
        LONG_PTR lCookie,
        CRTCSearch ** ppSearchWindow
        );

    // Cleanup the user search list
    HRESULT CleanupUserSearches();

    // Add a window to the watchers list
    HRESULT AddWatchers();

    // Cleanup the watchers list
    HRESULT CleanupWatchers();

    // Add a window to the groups list
    HRESULT AddGroups();

    // Cleanup the groups list
    HRESULT CleanupGroups();

    // Update a buddy entry in the buddy list
    HRESULT UpdateBuddyList(IRTCBuddy * pBuddy);

    // Clear the buddy list
    HRESULT ClearBuddyList(IRTCBuddy * pBuddy);
    HRESULT ClearBuddyList();

    // Populate the buddy list
    HRESULT PopulateBuddyList();

    // Logon
    HRESULT DoLogOn(BSTR bstrURI, BSTR bstrServer, BSTR bstrTransport);
    HRESULT OnLoggingOn();
    HRESULT OnLoggedOn();

    // Logoff
    HRESULT DoLogOff();  
    HRESULT OnLoggingOff();
    HRESULT OnLoggedOff();

    // Authentication
    HRESULT DoAuth(BSTR bstrURI, BSTR bstrAccount, BSTR bstrPassword);

    // Enable presence
    HRESULT DoEnablePresence(BOOL fEnable);

    // In-band provisioning
    HRESULT DoGetProfile(BSTR bstrURI, BSTR bstrServer, BSTR bstrTransport);

    // Enable profile
    HRESULT DoEnableProfile(BOOL fEnable, long lRegisterFlags, long lRoamingFlags);

    // Register with server
    HRESULT DoRegister();

    // Refresh a buddy
    HRESULT DoRefreshBuddy(IRTCBuddy *pBuddy);

    // Remove a buddy
    HRESULT DoRemoveBuddy(IRTCBuddy *pBuddy);

    // Start the tuning wizard
    HRESULT DoTuningWizard();

    // Set local presence status
    HRESULT DoSetPresence(RTC_PRESENCE_STATUS enStatus);    

	//Sets the Options
	HRESULT DoOptions();

	//Displays Buddy Properties
	HRESULT	DoBuddyProperties(IRTCBuddy *pBuddy);

	//Displays DTMF Dialpad (doesn't care if there is an IM/AV call active or not)
	HRESULT DoDTMFDialpad();

    // Window message handlers
    LRESULT OnCreate(UINT uMsg, WPARAM wParam, LPARAM lParam);
    LRESULT OnDestroy(UINT uMsg, WPARAM wParam, LPARAM lParam);
    LRESULT OnClose(UINT uMsg, WPARAM wParam, LPARAM lParam);
    LRESULT OnSize(UINT uMsg, WPARAM wParam, LPARAM lParam);
    LRESULT OnCommand(UINT uMsg, WPARAM wParam, LPARAM lParam);
    LRESULT OnNotify(UINT uMsg, WPARAM wParam, LPARAM lParam);
    LRESULT OnRTCEvent(UINT uMsg, WPARAM wParam, LPARAM lParam);

    // RTC event handlers
    void OnRTCRegistrationStateChangeEvent(
                IRTCRegistrationStateChangeEvent *pEvent
                );

    void OnRTCSessionStateChangeEvent(
                IRTCSessionStateChangeEvent *pEvent
                );

    void OnRTCParticipantStateChangeEvent(
                IRTCParticipantStateChangeEvent *pEvent
                );

    void OnRTCMessagingEvent(
                IRTCMessagingEvent *pEvent
                );

    void OnRTCMediaEvent(
                IRTCMediaEvent *pEvent
                );

    void OnRTCIntensityEvent(
                IRTCIntensityEvent *pEvent
                );

    void OnRTCClientEvent(
                IRTCClientEvent *pEvent
                );

    void OnRTCBuddyEvent(
                IRTCBuddyEvent2 *pEvent
                );

    void OnRTCBuddyGroupEvent(
                IRTCBuddyGroupEvent *pEvent
                );

    void OnRTCWatcherEvent(
                IRTCWatcherEvent2 *pEvent
                );

    void OnRTCUserSearchResultsEvent(
                IRTCUserSearchResultsEvent *pEvent
                );

    void OnRTCRoamingEvent(
                IRTCRoamingEvent *pEvent
                );

    void OnRTCProfileEvent(
                IRTCProfileEvent2 *pEvent
                );

    void OnRTCPresencePropertyEvent(
                IRTCPresencePropertyEvent *pEvent
                );

    void OnRTCPresenceDataEvent(
                IRTCPresenceDataEvent *pEvent
                );

    void OnRTCPresenceStatusEvent(
                IRTCPresenceStatusEvent *pEvent
                );

    void OnRTCMediaRequestEvent(
				IRTCMediaRequestEvent *pEvent
				);
};

#endif //_RTCWIN_H_
