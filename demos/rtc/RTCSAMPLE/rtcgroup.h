// rtcgroup.h
//

#ifndef _RTCGROUP_H_
#define _RTCGROUP_H_

#define WM_POPULATE WM_USER+200

// Class for the group window
class CRTCGroup
{
public:
    CRTCGroup();
    ~CRTCGroup();

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
    HWND    m_hGroupList;

    // Update a group entry in the group list
    HRESULT UpdateGroupList(IRTCBuddyGroup * pGroup);

    // Clear the group list
    HRESULT ClearGroupList(IRTCBuddyGroup * pGroup);
    HRESULT ClearGroupList();

    // Populate the group list
    HRESULT PopulateGroupList();

    // Add a group
    HRESULT DoAddGroup(BSTR bstrNamee);

    // Remove a group
    HRESULT DoRemoveGroup(IRTCBuddyGroup *pGroup);

    // Add a buddy to a group
    HRESULT DoAddBuddyToGroup(BSTR bstrBuddyURI, IRTCBuddyGroup *pGroup);

    // Remove a buddy from a group
    HRESULT DoRemoveBuddyFromGroup(BSTR bstrBuddyURI, IRTCBuddyGroup *pGroup);

    // Window message handlers
    LRESULT OnCreate(UINT uMsg, WPARAM wParam, LPARAM lParam);
    LRESULT OnDestroy(UINT uMsg, WPARAM wParam, LPARAM lParam);
    LRESULT OnClose(UINT uMsg, WPARAM wParam, LPARAM lParam);
    LRESULT OnSize(UINT uMsg, WPARAM wParam, LPARAM lParam);
    LRESULT OnCommand(UINT uMsg, WPARAM wParam, LPARAM lParam);
    LRESULT OnNotify(UINT uMsg, WPARAM wParam, LPARAM lParam);

    // Event handlers
    HRESULT DeliverGroup(IRTCBuddyGroup * pGroup, RTC_GROUP_EVENT_TYPE enType, LONG lStatus);
};

#endif //_RTCGROUP_H_
