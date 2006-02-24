// rtcsearch.h
//

#ifndef _RTCSEARCH_H_
#define _RTCSEARCH_H_

// Class for instant messaging session windows
class CRTCSearch
{
public:
    CRTCSearch();
    ~CRTCSearch();

    // Registers the window class
    static HRESULT RegisterClass();

    // Window procedure
    static LRESULT CALLBACK WindowProc(
        HWND hWnd,      // handle to window
        UINT uMsg,      // message identifier
        WPARAM wParam,  // first message parameter
        LPARAM lParam   // second message parameter
        );

    // Subclass procedure for the First Name control
    static LRESULT CALLBACK FNSubclassProc(
        HWND hWnd,      // handle to window
        UINT uMsg,      // message identifier
        WPARAM wParam,  // first message parameter
        LPARAM lParam   // second message parameter
        );

	// Subclass procedure for the Last Name control
    static LRESULT CALLBACK LNSubclassProc(
        HWND hWnd,      // handle to window
        UINT uMsg,      // message identifier
        WPARAM wParam,  // first message parameter
        LPARAM lParam   // second message parameter
        );

	// Subclass procedure for the Email control
    static LRESULT CALLBACK MSubclassProc(
        HWND hWnd,      // handle to window
        UINT uMsg,      // message identifier
        WPARAM wParam,  // first message parameter
        LPARAM lParam   // second message parameter
        );

protected:

    friend class CRTCWin;

    CRTCWin * m_pWin;
    IRTCProfile * m_pProfile;
    IRTCUserSearch * m_pUserSearch;
    long m_lCookie;
    HWND m_hWnd;
    HWND m_hStatusBar;
    HWND m_hFirstName;
	HWND m_hLastName;
	HWND m_hEmail;
    HWND m_hSearch;
    HWND m_hResultList;
	HWND m_hfnLabel;
	HWND m_hlnLabel;
	HWND m_hmLabel;
    WNDPROC m_wpOrigFNProc;
	WNDPROC m_wpOrigLNProc;
	WNDPROC m_wpOrigMProc;

    // Helpers
    void ShowMessageBox(PWSTR szText);
    void SetStatusText(PWSTR szText);

    // Update a result entry in the result list
    HRESULT UpdateResultList(IRTCUserSearchResult * pResult);

    // Clear the result list
    HRESULT ClearResultList();

    // Search
    HRESULT DoSearch();

    // Window message handlers
    LRESULT OnCreate(UINT uMsg, WPARAM wParam, LPARAM lParam);
    LRESULT OnDestroy(UINT uMsg, WPARAM wParam, LPARAM lParam);
    LRESULT OnClose(UINT uMsg, WPARAM wParam, LPARAM lParam);
    LRESULT OnSize(UINT uMsg, WPARAM wParam, LPARAM lParam);
    LRESULT OnCommand(UINT uMsg, WPARAM wParam, LPARAM lParam);
    LRESULT OnNotify(UINT uMsg, WPARAM wParam, LPARAM lParam);

    // Event handlers
    HRESULT DeliverUserSearchResults(HRESULT hrStatus, IRTCEnumUserSearchResults * pEnum);
};

#endif //_RTCSEARCH_H_
