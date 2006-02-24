// rtcwatcher.h
//

#ifndef _RTCWATCHER_H_
#define _RTCWATCHER_H_

#define WM_POPULATE WM_USER+200

// Class for the watcher window
class CRTCWatcher
{
public:
    CRTCWatcher();
    ~CRTCWatcher();

    // Registers the window class
    static HRESULT RegisterClass();    

    // Window procedure
    static LRESULT CALLBACK WindowProc(
        HWND hWnd,      // handle to window
        UINT uMsg,      // message identifier
        WPARAM wParam,  // first message parameter
        LPARAM lParam   // second message parameter
        );

private:

    friend class CRTCWin;

    CRTCWin * m_pWin;
    IRTCClient * m_pClient;

    HWND    m_hWnd;
    HWND    m_hWatcherList;

    // Update a watcher entry in the watcher list
    HRESULT UpdateWatcherList(IRTCWatcher * pWatcher);

    // Clear the watcher list
    HRESULT ClearWatcherList(IRTCWatcher * pWatcher);
    HRESULT ClearWatcherList();

    // Populate the watcher list
    HRESULT PopulateWatcherList();

    // Add a watcher
    HRESULT DoAddWatcher(BSTR bstrURI, BSTR bstrName, RTC_WATCHER_STATE enState);

    // Remove a watcher
    HRESULT DoRemoveWatcher(IRTCWatcher *pWatcher);

    // Allow/Block a watcher
    HRESULT DoSetWatcherState(IRTCWatcher *pWatcher, RTC_WATCHER_STATE enState);

    // Window message handlers
    LRESULT OnCreate(UINT uMsg, WPARAM wParam, LPARAM lParam);
    LRESULT OnDestroy(UINT uMsg, WPARAM wParam, LPARAM lParam);
    LRESULT OnClose(UINT uMsg, WPARAM wParam, LPARAM lParam);
    LRESULT OnSize(UINT uMsg, WPARAM wParam, LPARAM lParam);
    LRESULT OnCommand(UINT uMsg, WPARAM wParam, LPARAM lParam);
    LRESULT OnNotify(UINT uMsg, WPARAM wParam, LPARAM lParam);

    // Event handlers
    HRESULT DeliverWatcher(IRTCWatcher * pWatcher, RTC_WATCHER_EVENT_TYPE enType, LONG lStatus);
};

#endif //_RTCWATCHER_H_
