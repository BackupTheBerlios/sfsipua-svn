// rtcdialogs.h
//

#ifndef _RTCDIALOGS_H_
#define _RTCDIALOGS_H_

// Show the logon dialog
HRESULT ShowLogonDialog(HWND hWndParent, 
                        BSTR *pbstrURI, BSTR *pbstrServer, BSTR *pbstrTransport);

// Show the authentication dialog
HRESULT ShowAuthDialog(HWND hWndParent, PWSTR szRealm,
                       BSTR *pbstrURI, BSTR *pbstrAccount, BSTR *pbstrPassword,
                       BSTR *pbstrServer, BSTR *pbstrTransport);

// Show the incoming watcher dialog
HRESULT ShowWatcherDialog(HWND hWndParent,
                          BSTR bstrName, BSTR bstrURI,
                          BOOL *pfAllow, BOOL *pfAddBuddy);

// Show the address dialog
HRESULT ShowAddressDialog(HWND hWndParent,
                          PWSTR szTitle,
                          BSTR *pbstrURI, BSTR *pbstrName);

// Show the incoming session dialog
HRESULT ShowSessionDialog(HWND hwndParent,
                          BSTR bstrName, BSTR bstrURI,
                          BOOL *pfAccept);


// Show the AppVersion Dialog Box
HRESULT	ShowOptionsDialog(
		HWND hWndParent,
		OPTIONS_DATA *pOD
		);

// Show additional details about a buddy
HRESULT	ShowBuddyPropertiesDialog(
		HWND hWndParent,
		IRTCBuddy2 *pBuddy);


// Show DTMF DialPad
HRESULT ShowDtmfDialpad(
		HWND hWndParent,
		IRTCClient2 *pClient);

#endif //_RTCDIALOGS_H_
