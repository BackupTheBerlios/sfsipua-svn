// rtcdialogs.cpp
//

#include "stdafx.h"

/////////////////////////////////////////////
//
// RegistryGet
//

HRESULT RegistryGet(WCHAR * szValueName, WCHAR * szData)
{
    HKEY hKey;
    LONG lResult;
    DWORD cbSize = MAX_STRING * sizeof(WCHAR);

    lResult = RegOpenKeyW(
        HKEY_CURRENT_USER,
        L"Software\\Microsoft\\rtcsample",
        &hKey);

    if (lResult != ERROR_SUCCESS)
    {
        // RegOpenKeyW failed
        return E_FAIL;
    }    

    lResult = RegQueryValueExW(
        hKey,
        szValueName,
        NULL,
        NULL,
        (LPBYTE)szData,
        &cbSize
        );

    RegCloseKey(hKey);

    if (lResult != ERROR_SUCCESS)
    {
        // RegQueryValueExW failed
        return E_FAIL;
    }

    return S_OK;
}

/////////////////////////////////////////////
//
// RegistrySet
//

HRESULT RegistrySet(WCHAR * szValueName, WCHAR * szData)
{
    HKEY hKey;
    LONG lResult;

    lResult = RegCreateKeyW(
        HKEY_CURRENT_USER,
        L"Software\\Microsoft\\rtcsample",
        &hKey);

    if (lResult != ERROR_SUCCESS)
    {
        // RegOpenKeyW failed
        return E_FAIL;
    }

    lResult = RegSetValueExW(
        hKey,
        szValueName,
        0,
        REG_SZ,
        (LPBYTE)szData,
        (DWORD) ((wcslen(szData) + 1) * sizeof(WCHAR))
        );

    RegCloseKey(hKey);

    if (lResult != ERROR_SUCCESS)
    {
        // RegSetValueExW failed
        return E_FAIL;
    }

    return S_OK;
}

/////////////////////////////////////////////
//
// CleanUserURI
//
// Assume buffer length of MAX_STRING
//

void CleanUserURI(WCHAR * szURI)
{
    // If the user URI does not start with sip: then
    // add it
    if (wcsncmp(szURI, L"sip:", 4))
    {
        WCHAR szTemp[MAX_STRING];

        wcsncpy(szTemp, szURI, MAX_STRING-1);
        szTemp[MAX_STRING-1] = L'\0';
        _snwprintf(szURI, MAX_STRING, L"sip:%s", szTemp);
        szURI[MAX_STRING-1] = L'\0';
    }

    // Also, strip off any parameters to the user URI
    WCHAR *ch = wcschr(szURI, L';');

    if (ch != NULL)
    {
        *ch = L'\0';
    }
}

/////////////////////////////////////////////
//
// LOGON_DATA
//

struct LOGON_DATA
{
    WCHAR szUserURI[MAX_STRING];
    WCHAR szServer[MAX_STRING];
    WCHAR szTransport[MAX_STRING];
};

/////////////////////////////////////////////
//
// LogonDialogProc
// 

INT_PTR CALLBACK LogonDialogProc(
  HWND hwndDlg,  // handle to dialog box
  UINT uMsg,     // message
  WPARAM wParam, // first message parameter
  LPARAM lParam  // second message parameter
)
{
    LOGON_DATA *pLD;
    pLD = (LOGON_DATA *)GetWindowLongPtr(hwndDlg, DWLP_USER);

    switch (uMsg) 
    { 
    case WM_INITDIALOG:
        {
            // Store the LOGON_DATA pointer in the
            // window's user data
            SetWindowLongPtr(hwndDlg, DWLP_USER, lParam);

            pLD = (LOGON_DATA *)lParam;

            // Populate the transport combo box
            HWND hwndCombo = GetDlgItem(hwndDlg, IDC_COMBO_LOGON_TRANSPORT);
        
            SendMessageW(hwndCombo, CB_ADDSTRING, 0, (LPARAM)L"TCP");
            SendMessageW(hwndCombo, CB_ADDSTRING, 0, (LPARAM)L"UDP");
            SendMessageW(hwndCombo, CB_ADDSTRING, 0, (LPARAM)L"TLS");
            SendMessage(hwndCombo, CB_SETCURSEL, 0, 0);

            if (RegistryGet(L"UserURI", pLD->szUserURI) == S_OK)
            {
                SetDlgItemTextW(hwndDlg, IDC_EDIT_LOGON_USERURI,
                                pLD->szUserURI);
            }

            if (RegistryGet(L"Server", pLD->szServer) == S_OK)
            {
                SetDlgItemTextW(hwndDlg, IDC_EDIT_LOGON_SERVER,
                                pLD->szServer);
            }

            if (RegistryGet(L"Transport", pLD->szTransport) == S_OK)
            {
                SetDlgItemTextW(hwndDlg, IDC_COMBO_LOGON_TRANSPORT,
                                pLD->szTransport);
            }

        }
        return TRUE;

    case WM_COMMAND: 
        switch (LOWORD(wParam)) 
        { 
        case IDOK: 
            {
                GetDlgItemTextW(
                    hwndDlg,
                    IDC_EDIT_LOGON_USERURI, 
                    pLD->szUserURI,
                    MAX_STRING
                    );

                GetDlgItemTextW(
                    hwndDlg,
                    IDC_EDIT_LOGON_SERVER, 
                    pLD->szServer,
                    MAX_STRING
                    );

                GetDlgItemTextW(
                    hwndDlg,
                    IDC_COMBO_LOGON_TRANSPORT, 
                    pLD->szTransport,
                    MAX_STRING
                    );

                RegistrySet(L"UserURI", pLD->szUserURI);
                RegistrySet(L"Server", pLD->szServer);
                RegistrySet(L"Transport", pLD->szTransport);

		if ((wcscmp(pLD->szUserURI, L"")==0) && (wcscmp(pLD->szServer, L"")==0))
		    MessageBox(hwndDlg,L"Please Enter Values for Server and URI", L"Error", MB_OK);

                // Fall through
            }

        case IDCANCEL: 
            EndDialog(hwndDlg, wParam); 
			
			//if ((wcscmp(bstrURI, L"")==0) && (wcscmp(bstrServer, L"")==0))
		    //MessageBox(hwndDlg,L"BSTRURI",L"test", MB_OK);

            return TRUE; 
        } 
    } 

    return FALSE; 
}

/////////////////////////////////////////////
//
// ShowLogonDialog
//

HRESULT ShowLogonDialog(HWND hWndParent,
                        BSTR *pbstrURI, BSTR *pbstrServer, BSTR *pbstrTransport)
{
    INT_PTR iRes;
    LOGON_DATA ld;
    
    // Show the dialog
    iRes = DialogBoxParam(
        GetModuleHandle(NULL),
        MAKEINTRESOURCE(IDD_DIALOG_LOGON),
        hWndParent,
        (DLGPROC)LogonDialogProc,
        (LPARAM)&ld
        );

    if (iRes == IDOK)
    {
        // Check for empty strings
        if (ld.szUserURI[0] == L'\0')
        {
            return E_FAIL;
        }

        // Cleanup the user URI
        CleanUserURI(ld.szUserURI);

        *pbstrURI = SysAllocString(ld.szUserURI);

        if (!(*pbstrURI))
        {
            // Out of memory
            return E_OUTOFMEMORY;
        }

        *pbstrServer = SysAllocString(ld.szServer);

        if (!(*pbstrServer))
        {
            // Out of memory
            SAFE_FREE_STRING(*pbstrURI);
            return E_OUTOFMEMORY;
        }

        *pbstrTransport = SysAllocString(ld.szTransport);

        if (!(*pbstrTransport))
        {
            // Out of memory
            SAFE_FREE_STRING(*pbstrURI);
            SAFE_FREE_STRING(*pbstrServer);
            return E_OUTOFMEMORY;
        }

        return S_OK;
    }

    return E_FAIL;
}

/////////////////////////////////////////////
//
// AUTH_DATA
//

struct AUTH_DATA
{
    WCHAR szUserURI[MAX_STRING];
    WCHAR szAccount[MAX_STRING];
    WCHAR szPassword[MAX_STRING];
    WCHAR szServer[MAX_STRING];
    WCHAR szTransport[MAX_STRING];
    PWSTR szRealm;
};

/////////////////////////////////////////////
//
// AuthDialogProc
// 

INT_PTR CALLBACK AuthDialogProc(
  HWND hwndDlg,  // handle to dialog box
  UINT uMsg,     // message
  WPARAM wParam, // first message parameter
  LPARAM lParam  // second message parameter
)
{
    AUTH_DATA *pAD;
    pAD = (AUTH_DATA *)GetWindowLongPtr(hwndDlg, DWLP_USER);

    switch (uMsg) 
    { 
    case WM_INITDIALOG:
        {
            // Store the AUTH_DATA pointer in the
            // window's user data
            SetWindowLongPtr(hwndDlg, DWLP_USER, lParam);

            pAD = (AUTH_DATA *)lParam;

            if (pAD->szRealm != NULL)
            {
                SetDlgItemTextW(hwndDlg, IDC_STATIC_AUTH_REALM,
                                pAD->szRealm);
            }

            if (RegistryGet(L"UserURI", pAD->szUserURI) == S_OK)
            {
                SetDlgItemTextW(hwndDlg, IDC_EDIT_AUTH_USERURI,
                                pAD->szUserURI);
            }

            if (RegistryGet(L"Account", pAD->szAccount) == S_OK)
            {
                SetDlgItemTextW(hwndDlg, IDC_EDIT_AUTH_ACCOUNT,
                                pAD->szAccount);
            }

            RegistryGet(L"Server", pAD->szServer);
            RegistryGet(L"Transport", pAD->szTransport);
        }
        return TRUE;

    case WM_COMMAND: 
        switch (LOWORD(wParam)) 
        { 
        case IDOK: 
            {
                GetDlgItemTextW(
                    hwndDlg,
                    IDC_EDIT_AUTH_USERURI, 
                    pAD->szUserURI,
                    MAX_STRING
                    );

                GetDlgItemTextW(
                    hwndDlg,
                    IDC_EDIT_AUTH_ACCOUNT, 
                    pAD->szAccount,
                    MAX_STRING
                    );

                GetDlgItemTextW(
                    hwndDlg,
                    IDC_EDIT_AUTH_PASSWORD, 
                    pAD->szPassword,
                    MAX_STRING
                    );

                RegistrySet(L"UserURI", pAD->szUserURI);
                RegistrySet(L"Account", pAD->szAccount);

                // Fall through
            }

        case IDCANCEL: 
            EndDialog(hwndDlg, wParam); 
            return TRUE; 
        } 
    } 

    return FALSE; 
}

/////////////////////////////////////////////
//
// ShowAuthDialog
//

HRESULT ShowAuthDialog(HWND hWndParent, PWSTR szRealm,
                       BSTR *pbstrURI, BSTR *pbstrAccount, BSTR *pbstrPassword,
                       BSTR *pbstrServer, BSTR *pbstrTransport)
{
    INT_PTR iRes;
    AUTH_DATA ad;

    ad.szRealm = szRealm;
    
    // Show the dialog
    iRes = DialogBoxParam(
        GetModuleHandle(NULL),
        MAKEINTRESOURCE(IDD_DIALOG_AUTH),
        hWndParent,
        (DLGPROC)AuthDialogProc,
        (LPARAM)&ad
        );

    if (iRes == IDOK)
    {
        // Check for empty strings
        if ((ad.szUserURI[0] == L'\0') ||
            (ad.szAccount[0] == L'\0') ||
            (ad.szPassword[0] == L'\0'))
        {
            return E_FAIL;
        }

        // Cleanup the user URI
        CleanUserURI(ad.szUserURI);

        *pbstrURI = SysAllocString(ad.szUserURI);

        if (!(*pbstrURI))
        {
            // Out of memory
            return E_OUTOFMEMORY;
        }

        *pbstrAccount = SysAllocString(ad.szAccount);

        if (!(*pbstrAccount))
        {
            // Out of memory
            SAFE_FREE_STRING(*pbstrURI);
            return E_OUTOFMEMORY;
        }

        *pbstrPassword = SysAllocString(ad.szPassword);

        if (!(*pbstrPassword))
        {
            // Out of memory
            SAFE_FREE_STRING(*pbstrURI);
            SAFE_FREE_STRING(*pbstrAccount);
            return E_OUTOFMEMORY;
        }

        *pbstrServer = SysAllocString(ad.szServer);

        if (!(*pbstrServer))
        {
            // Out of memory
            SAFE_FREE_STRING(*pbstrURI);
            SAFE_FREE_STRING(*pbstrAccount);
            SAFE_FREE_STRING(*pbstrPassword);
            return E_OUTOFMEMORY;
        }

        *pbstrTransport = SysAllocString(ad.szTransport);

        if (!(*pbstrTransport))
        {
            // Out of memory
            SAFE_FREE_STRING(*pbstrURI);
            SAFE_FREE_STRING(*pbstrAccount);
            SAFE_FREE_STRING(*pbstrPassword);
            SAFE_FREE_STRING(*pbstrServer);
            return E_OUTOFMEMORY;
        }

        return S_OK;
    }

    return E_FAIL;
}

/////////////////////////////////////////////
//
// WATCHER_DATA
// 

struct WATCHER_DATA
{
    BSTR bstrName;
    BSTR bstrURI;
    BOOL fAllow;
    BOOL fAddBuddy;
};

/////////////////////////////////////////////
//
// WatcherDialogProc
// 

INT_PTR CALLBACK WatcherDialogProc(
  HWND hwndDlg,  // handle to dialog box
  UINT uMsg,     // message
  WPARAM wParam, // first message parameter
  LPARAM lParam  // second message parameter
)
{
    WATCHER_DATA *pWD;
    pWD = (WATCHER_DATA *)GetWindowLongPtr(hwndDlg, DWLP_USER);

    switch (uMsg) 
    { 
    case WM_INITDIALOG:
        {
            // Store the WATCHER_DATA pointer in the
            // window's user data
            SetWindowLongPtr(hwndDlg, DWLP_USER, lParam);
            pWD = (WATCHER_DATA *)lParam;

            // Populate the watcher text
            SendDlgItemMessageW(hwndDlg, IDC_STATIC_WATCHER_NAME,
                WM_SETTEXT, 0, (LPARAM)(pWD->bstrName));

            SendDlgItemMessageW(hwndDlg, IDC_STATIC_WATCHER_URI,
                WM_SETTEXT, 0, (LPARAM)(pWD->bstrURI));

            // Check the add buddy box by default
            SendDlgItemMessage(hwndDlg, IDC_CHECK_WATCHER_ADD_BUDDY,
                                BM_SETCHECK, BST_CHECKED, 0);
        }
        return TRUE;

    case WM_COMMAND: 
        switch (LOWORD(wParam)) 
        { 
        case IDC_BUTTON_WATCHER_ALLOW: 
            {
                pWD->fAddBuddy = (SendDlgItemMessage( 
                                hwndDlg, 
                                IDC_CHECK_WATCHER_ADD_BUDDY,
                                BM_GETCHECK, 
                                0, 0) == BST_CHECKED);

                pWD->fAllow = TRUE;

                EndDialog(hwndDlg, IDOK); 
            }
            return TRUE;

        case IDC_BUTTON_WATCHER_BLOCK:
            {
                pWD->fAddBuddy = (SendDlgItemMessage( 
                                hwndDlg, 
                                IDC_CHECK_WATCHER_ADD_BUDDY,
                                BM_GETSTATE, 
                                0, 0) == BST_CHECKED);

                pWD->fAllow = FALSE;

                EndDialog(hwndDlg, IDOK); 
            }
            return TRUE;

        case IDCANCEL: 
            EndDialog(hwndDlg, wParam); 
            return TRUE; 
        } 
    } 

    return FALSE; 
}

/////////////////////////////////////////////
//
// ShowWatcherDialog
//

HRESULT ShowWatcherDialog(
        HWND hWndParent,
        BSTR bstrName, BSTR bstrURI,
        BOOL *pfAllow, BOOL *pfAddBuddy)
{
    INT_PTR iRes;
    WATCHER_DATA wd;
    
    wd.bstrName = bstrName;
    wd.bstrURI = bstrURI;

    // Show the dialog
    iRes = (int) DialogBoxParam(
        GetModuleHandle(NULL),
        MAKEINTRESOURCE(IDD_DIALOG_WATCHER),
        hWndParent,
        (DLGPROC)WatcherDialogProc,
        (LPARAM)&wd
        );

    if (iRes == IDOK)
    {
        *pfAllow = wd.fAllow;
        *pfAddBuddy = wd.fAddBuddy;

        return S_OK;
    }

    return E_FAIL;
}

/////////////////////////////////////////////
//
// ADDRESS_DATA
// 

struct ADDRESS_DATA
{
    PWSTR szTitle;
    WCHAR szURI[MAX_STRING];
    WCHAR szName[MAX_STRING];
};

/////////////////////////////////////////////
//
// AddressDialogProc
// 

INT_PTR CALLBACK AddressDialogProc(
  HWND hwndDlg,  // handle to dialog box
  UINT uMsg,     // message
  WPARAM wParam, // first message parameter
  LPARAM lParam  // second message parameter
)
{
    ADDRESS_DATA *pAD;
    pAD = (ADDRESS_DATA *)GetWindowLongPtr(hwndDlg, DWLP_USER);
                
    switch (uMsg) 
    { 
    case WM_INITDIALOG:
        {
            // Store the ADDRESS_DATA pointer in the
            // window's user data
            SetWindowLongPtr(hwndDlg, DWLP_USER, lParam);
            pAD = (ADDRESS_DATA *)lParam;

            // Set the dialog title
            SetWindowText(hwndDlg, pAD->szTitle);
			
            if (RegistryGet(L"LastCalledURI", pAD->szURI) == S_OK)
            {
                SetDlgItemTextW(hwndDlg, IDC_EDIT_ADDRESS_URI,
                                pAD->szURI);
            }

        }
        return TRUE;

    case WM_COMMAND: 
        switch (LOWORD(wParam)) 
        { 
        case IDOK: 
            {
                GetDlgItemTextW(
                    hwndDlg,
                    IDC_EDIT_ADDRESS_URI, 
                    pAD->szURI,
                    MAX_STRING
                    );

                GetDlgItemTextW(
                    hwndDlg,
                    IDC_EDIT_ADDRESS_NAME, 
                    pAD->szName,
                    MAX_STRING
                    );

                RegistrySet(L"LastCalledURI", pAD->szURI);

                // Fall through
            }

        case IDCANCEL: 
            EndDialog(hwndDlg, wParam); 
            return TRUE; 
        } 
    } 

    return FALSE; 
}

/////////////////////////////////////////////
//
// ShowAddressDialog
//

HRESULT ShowAddressDialog(HWND hWndParent,
                          PWSTR szTitle,
                          BSTR *pbstrURI, BSTR *pbstrName)
{
    INT_PTR iRes;
    ADDRESS_DATA ad;
    
    ad.szTitle = szTitle;

    // Show the dialog
    iRes = DialogBoxParam(
        GetModuleHandle(NULL),
        MAKEINTRESOURCE(pbstrName ? (pbstrURI ? IDD_DIALOG_ADDRESS_NAME : IDD_DIALOG_NAME) : IDD_DIALOG_ADDRESS),
        hWndParent,
        (DLGPROC)AddressDialogProc,
        (LPARAM)&ad
        );

    if (iRes == IDOK)
    {
        if (pbstrURI)
        {
            // Check for empty strings
            if (ad.szURI[0] == L'\0')
            {
                return E_FAIL;
            }

            *pbstrURI = SysAllocString(ad.szURI);

            if (!(*pbstrURI))
            {
                // Out of memory
                return E_OUTOFMEMORY;
            }
        }

        if (pbstrName)
        {
            *pbstrName = SysAllocString(ad.szName);

            if (!(*pbstrName))
            {
                // Out of memory
                if(pbstrURI)
                {
                    SAFE_FREE_STRING(*pbstrURI);
                }

                return E_OUTOFMEMORY;
            }
        }

        return S_OK;
    }

    return E_FAIL;
}

/////////////////////////////////////////////
//
// SESSION_DATA
// 

struct SESSION_DATA
{
    BSTR bstrName;
    BSTR bstrURI;
    BOOL fAccept;
};

/////////////////////////////////////////////
//
// SessionDialogProc
// 

INT_PTR CALLBACK SessionDialogProc(
  HWND hwndDlg,  // handle to dialog box
  UINT uMsg,     // message
  WPARAM wParam, // first message parameter
  LPARAM lParam  // second message parameter
)
{
    SESSION_DATA *pSD;
    pSD = (SESSION_DATA *)GetWindowLongPtr(hwndDlg, DWLP_USER);

    switch (uMsg) 
    { 
    case WM_INITDIALOG:
        {
            // Store the SESSION_DATA pointer in the
            // window's user data
            SetWindowLongPtr(hwndDlg, DWLP_USER, lParam);
            pSD = (SESSION_DATA *)lParam;

            // Populate the session text
            SendDlgItemMessageW(hwndDlg, IDC_STATIC_SESSION_NAME,
                WM_SETTEXT, 0, (LPARAM)(pSD->bstrName));

            SendDlgItemMessageW(hwndDlg, IDC_STATIC_SESSION_URI,
                WM_SETTEXT, 0, (LPARAM)(pSD->bstrURI));
        }
        return TRUE;

    case WM_COMMAND: 
        switch (LOWORD(wParam)) 
        { 
        case IDC_BUTTON_SESSION_ACCEPT: 
            {
                pSD->fAccept = TRUE;

                EndDialog(hwndDlg, IDOK); 
            }
            return TRUE;

        case IDC_BUTTON_SESSION_REJECT:
        case IDCANCEL: 
            {
                pSD->fAccept = FALSE;

                EndDialog(hwndDlg, IDOK); 
            }
            return TRUE; 
        } 
    } 

    return FALSE; 
}

/////////////////////////////////////////////
//
// ShowSessionDialog
//

HRESULT ShowSessionDialog(
        HWND hWndParent,
        BSTR bstrName, BSTR bstrURI,
        BOOL *pfAccept)
{
    INT_PTR iRes;
    SESSION_DATA sd;
    
    sd.bstrName = bstrName;
    sd.bstrURI = bstrURI;

    // Show the dialog
    iRes = DialogBoxParam(
        GetModuleHandle(NULL),
        MAKEINTRESOURCE(IDD_DIALOG_SESSION),
        hWndParent,
        (DLGPROC)SessionDialogProc,
        (LPARAM)&sd
        );

    if (iRes == IDOK)
    {
        *pfAccept = sd.fAccept;

        return S_OK;
    }

    return E_FAIL;
}



//Use SysFreeString to free pbstr
void
GetStringFromEditBox(HWND hwndDlg, int nDlgItem, BSTR *pbstr) 
{
	int len;

	len = (int) SendDlgItemMessage(hwndDlg, nDlgItem, WM_GETTEXTLENGTH,0,0);


	if(len) {
		*pbstr= ::SysAllocStringLen(NULL, len + 1);
		SendDlgItemMessage(hwndDlg, nDlgItem, WM_GETTEXT, len+1, (LPARAM) (*pbstr));
	} else
		*pbstr = NULL;

	return;
}

void
SetStringInEditBox(HWND hwndDlg, int nDlgItem, BSTR bstr)
{
	SendDlgItemMessage(hwndDlg, nDlgItem, WM_SETTEXT, 0,(LPARAM) bstr);
}


BOOL
GetIntFromEditBox(HWND hwndDlg, int DlgItem, int* pi)
{
	BSTR p = NULL;

	GetStringFromEditBox(hwndDlg, DlgItem, &p);

	if( p == NULL)
		return FALSE;

	long l = -1;
	l = wcstol(p,NULL,10);
	SysFreeString(p);

	*pi = (int) l;
	return TRUE;
}

void
SetIntInEditBox(HWND hwndDlg, int DlgItem, int i)
{
		
	WCHAR p[MAX_PATH] = {0};
	swprintf(p,L"%d",i);
	BSTR bstrP = ::SysAllocString(p);

	if (bstrP)
	{
		SetStringInEditBox(hwndDlg, DlgItem, bstrP);
		::SysFreeString(bstrP);
	}
}




/////////////////////////////////////////////
//
// OptionsDialogProc
//
INT_PTR CALLBACK OptionsDialogProc(
  HWND hwndDlg,  // handle to dialog box
  UINT uMsg,     // message
  WPARAM wParam, // first message parameter
  LPARAM lParam  // second message parameter
)
{
    OPTIONS_DATA *pOD;
    pOD = (OPTIONS_DATA *)GetWindowLongPtr(hwndDlg, DWLP_USER);

    switch (uMsg) 
    { 
    case WM_INITDIALOG:
		{
			// Store the OPTIONS_DATA pointer in the
            // window's user data
            SetWindowLongPtr(hwndDlg, DWLP_USER, lParam);

			pOD = (OPTIONS_DATA *) lParam;

			//Display the settings that were last saved
			//BEGIN
			if(pOD->bstrAppName)
				SetStringInEditBox(hwndDlg, IDC_EDIT_OPTIONS_NAME, pOD->bstrAppName);
			
			if(pOD->bstrAppVer)
				SetStringInEditBox(hwndDlg, IDC_EDIT_OPTIONS_NUM, pOD->bstrAppVer);
			
			//If MaxBW was previously enforced
			if(pOD->EnabledOptions & RTCWIN_OPTIONS_MAXBW) {
				//Check the checkbox
				SendDlgItemMessage(hwndDlg, IDC_CHECK_OPTIONS_APPBW, BM_SETCHECK, BST_CHECKED, 0);	
				SetIntInEditBox(hwndDlg, IDC_EDIT_OPTIONS_APPBW, pOD->lMaxBW);		
			}

			//If T120 negotiation was previously enforced
			if(pOD->EnabledOptions & RTCWIN_OPTIONS_T120) {
				//Check the checkbox
				SendDlgItemMessage(hwndDlg, IDC_CHECK_OPTIONS_T120, BM_SETCHECK, BST_CHECKED, 0);	
			}


			//Display Encryption Settings
			int nDlgItm;

			//Check the right radio button for AV encryption
			switch(pOD->enAVLevel) {
			case RTCSECL_UNSUPPORTED:		
					nDlgItm = IDC_RADIO_AVENC_OPTIONS_UNSUPP;
					break;						
			case RTCSECL_SUPPORTED:
					nDlgItm = IDC_RADIO_AVENC_OPTIONS_SUPP;
					break;						

			case RTCSECL_REQUIRED:
					nDlgItm = IDC_RADIO_AVENC_OPTIONS_REQ;
					break;

			default:
					nDlgItm = -1;
					break;						
			}

			if (nDlgItm != -1)
			{
				CheckRadioButton(hwndDlg, 
						 IDC_RADIO_AVENC_OPTIONS_UNSUPP, IDC_RADIO_AVENC_OPTIONS_REQ,
						 nDlgItm);
			}


			//Check the right radio button for T120 encryption
			switch(pOD->enT120Level) {
			case RTCSECL_UNSUPPORTED:
					nDlgItm = IDC_RADIO_T120ENC_OPTIONS_UNSUPP; 
					break;						
			case RTCSECL_SUPPORTED:
					nDlgItm = IDC_RADIO_T120ENC_OPTIONS_SUPP;
					break;						

			case RTCSECL_REQUIRED:
					nDlgItm = IDC_RADIO_T120ENC_OPTIONS_REQ;
					break;						
			}

			CheckRadioButton(hwndDlg, 
							 IDC_RADIO_T120ENC_OPTIONS_UNSUPP, IDC_RADIO_T120ENC_OPTIONS_REQ,
							 nDlgItm);
			

			//Display the settings that were last saved
			//END           
		}

        return TRUE;

    case WM_COMMAND: 
        switch (LOWORD(wParam)) 
        { 
        case IDOK: 
            {
				//We are about to get the strings from the edit control. Free up the older strings.
				if(pOD->bstrAppName)
					SysFreeString(pOD->bstrAppName);

				if(pOD->bstrAppVer)
					SysFreeString(pOD->bstrAppVer);

				//Copy the AppName and AppVer strings from the edit control buffer to the OPTIONS_DATA structure

				GetStringFromEditBox(hwndDlg, IDC_EDIT_OPTIONS_NAME, &pOD->bstrAppName);
				GetStringFromEditBox(hwndDlg, IDC_EDIT_OPTIONS_NUM, &pOD->bstrAppVer);
				
				//MaxBW
				if( BST_CHECKED == SendDlgItemMessage(hwndDlg, IDC_CHECK_OPTIONS_APPBW, BM_GETCHECK, 0, 0))
				{
					//the item is checked. lets get the string from the edit box, convert to string and send it.
					int i;

					if( GetIntFromEditBox(hwndDlg, IDC_EDIT_OPTIONS_APPBW, &i) == TRUE) {
						pOD->lMaxBW = i;
						pOD->EnabledOptions |= RTCWIN_OPTIONS_MAXBW;
					}

				} else {
					//Edit control box was NOT checked
					pOD->EnabledOptions &=  ~RTCWIN_OPTIONS_MAXBW;
					pOD->lMaxBW = 0;
				}


				//T120 negotiation
				if( BST_CHECKED == SendDlgItemMessage(hwndDlg, IDC_CHECK_OPTIONS_T120, BM_GETCHECK, 0, 0))
				{
					pOD->EnabledOptions |= RTCWIN_OPTIONS_T120;

				} else {
					//Checkbox was NOT checked
					pOD->EnabledOptions &=  ~RTCWIN_OPTIONS_T120;
				}


				//***** Encryption Settings
				
				//AV Encryption Settings
				if(BST_CHECKED == IsDlgButtonChecked(hwndDlg, IDC_RADIO_AVENC_OPTIONS_UNSUPP)) 
					pOD->enAVLevel = RTCSECL_UNSUPPORTED;
				else if(BST_CHECKED == IsDlgButtonChecked(hwndDlg, IDC_RADIO_AVENC_OPTIONS_SUPP)) 
					pOD->enAVLevel = RTCSECL_SUPPORTED;
				else
					pOD->enAVLevel = RTCSECL_REQUIRED;
				
				//T120  Settings
				if(BST_CHECKED == IsDlgButtonChecked(hwndDlg, IDC_RADIO_T120ENC_OPTIONS_UNSUPP)) 
					pOD->enT120Level = RTCSECL_UNSUPPORTED;
				else if(BST_CHECKED == IsDlgButtonChecked(hwndDlg, IDC_RADIO_T120ENC_OPTIONS_SUPP))
					pOD->enT120Level = RTCSECL_SUPPORTED;
				else
					pOD->enT120Level = RTCSECL_REQUIRED;
				
                EndDialog(hwndDlg, IDOK); 
				return TRUE; 
            }
            
         
		case IDCANCEL:		{
				EndDialog(hwndDlg, IDCANCEL);
				return TRUE;
			}

		default: 
			return FALSE;
		}

		return FALSE;
    } 

    return FALSE; 
}


////////////////////////////////////////////
//
//	ShowOptionsDialog
//

HRESULT	ShowOptionsDialog(
		HWND hWndParent,
		OPTIONS_DATA *pOD)
{
	INT_PTR iRes;

	// Show the dialog
        iRes = DialogBoxParam(
        	GetModuleHandle(NULL),
        	MAKEINTRESOURCE(IDD_DIALOG_OPTIONS),
        	hWndParent,
        	(DLGPROC)OptionsDialogProc,
			(LPARAM) pOD
        );

    
	if (iRes == IDOK)
    {
        return S_OK;
    }
   
    return  S_OK;    
}




////////////////////////////////////////////
//
//	ShowBuddyPropertiesDialog
//

HRESULT ShowBuddyPropertiesDialog(
    HWND hWndParent,
    IRTCBuddy2 *pBuddy)
{
    HRESULT hr = S_OK;
    int nRemainingLength = 0;

    // String to store all of the information:
    WCHAR wszBuddyInformation[MAX_XML_STRING] = {0};

    // String to store device information:
    WCHAR wszDevices[MAX_XML_STRING] = {0};

    // String to store Groups information:
    WCHAR wszGroups[MAX_XML_STRING] = {0};

    BSTR bstrName = NULL;
    BSTR bstrURI = NULL;
    VARIANT_BOOL fPersistent;
    RTC_PRESENCE_STATUS enStatus = RTCXS_PRESENCE_OFFLINE;
    BSTR bstrNotes = NULL;

    WCHAR *wszPresenceStates[] = {
        L"RTCXS_PRESENCE_OFFLINE",
        L"RTCXS_PRESENCE_ONLINE",
        L"RTCXS_PRESENCE_AWAY",
        L"RTCXS_PRESENCE_IDLE",
        L"RTCXS_PRESENCE_BUSY",
        L"RTCXS_PRESENCE_BE_RIGHT_BACK",
        L"RTCXS_PRESENCE_ON_THE_PHONE",
        L"RTCXS_PRESENCE_OUT_TO_LUNCH",
        L"UNKNOWN_PRESENCE_STATE"
        };

////////////
//
// Begin RTC Functionality Code
//
// This code demonstrates obtaining presence properties in order to display in UI
//
////////////

    // Generic Buddy Information:

    hr = pBuddy->get_PresenceProperty(RTCPP_DISPLAYNAME, &bstrName);
    if (FAILED(hr))
    {
        DEBUG_PRINT(("get_PresenceProperty Failed 0x%8x", hr));
    }

    hr = pBuddy->get_PresentityURI(&bstrURI);
    if (FAILED(hr))
    {
        DEBUG_PRINT(("get_PresentityURI Failed 0x%8x", hr));
    }

    hr = pBuddy->get_Persistent(&fPersistent);
    if (FAILED(hr))
    {
        DEBUG_PRINT(("get_Persistent Failed 0x%8x", hr));
    }

    hr = pBuddy->get_Status(&enStatus);
    if (FAILED(hr))
    {
        DEBUG_PRINT(("get_Status Failed 0x%8x", hr));
    }

    hr = pBuddy->get_Notes(&bstrNotes);
    if (FAILED(hr))
    {
        DEBUG_PRINT(("get_Notes Failed 0x%8x", hr));
    }

    // Multiple Presence Devices Information

    IRTCEnumPresenceDevices *pEnumDev = NULL;
    int nDeviceCount = 0;

    hr = pBuddy->EnumeratePresenceDevices(&pEnumDev);
    if (FAILED(hr))
    {
        DEBUG_PRINT(("Enumerate Devices Failed 0x%8x", hr));
    }
    else
    {
        IRTCPresenceDevice *pDevice = NULL;               
        IRTCPresenceDevice2 *pDevice2 = NULL;               

        while (S_OK == pEnumDev->Next(1, &pDevice, NULL))
        {
            WCHAR wszOneDevice[MAX_XML_STRING] = {0};

            BSTR bstrDeviceNotes = NULL;
            BSTR bstrPresenceData = NULL;
            BSTR bstrPresenceDataNamespace = NULL;
            BSTR bstrDeviceID=NULL;
            RTC_PRESENCE_STATUS enDeviceStatus = RTCXS_PRESENCE_OFFLINE;

            hr = pDevice->get_Status(&enDeviceStatus);
            if (FAILED(hr))
            {
                DEBUG_PRINT(("Device::get_Status Failed 0x%8x", hr));
            }

            hr = pDevice->get_Notes(&bstrDeviceNotes);
            if (FAILED(hr))
            {
                DEBUG_PRINT(("Device::get_Notes Failed 0x%8x", hr));
            }

            hr = pDevice->GetPresenceData(&bstrPresenceDataNamespace, &bstrPresenceData);
            if (FAILED(hr))
            {
                DEBUG_PRINT(("Device::get_PresenceData Failed 0x%8x", hr));
            }

            pDevice2=NULL;
            hr=pDevice->QueryInterface(__uuidof(IRTCPresenceDevice2),(LPVOID *)&pDevice2);
            if (FAILED(hr))
            {
                DEBUG_PRINT(("QueryInterface Failed 0x%8x", hr));
            }

            if(pDevice2)
            {
                hr=pDevice2->get_DeviceID(&bstrDeviceID);
                if (FAILED(hr))
                {
                    DEBUG_PRINT(("Device::get_DeviceID Failed 0x%8x", hr));
                }
            }

             _snwprintf(wszOneDevice, MAX_XML_STRING-1,
                L"\nDevice #%d: Status = %s, Notes = %s, Data = %s, Device ID= %s",
                nDeviceCount, 
                wszPresenceStates[enDeviceStatus],
                bstrDeviceNotes,
                bstrPresenceData,
                bstrDeviceID
                );
            wszOneDevice[MAX_XML_STRING-1] = L'\0';

            nRemainingLength = MAX_XML_STRING - 1 - (int) wcslen(wszDevices);
            if (nRemainingLength > 0)
            {
                wcsncat(wszDevices, wszOneDevice, nRemainingLength-1);
            }

            wszDevices[MAX_XML_STRING-1] = L'\0';

            SAFE_FREE_STRING(bstrDeviceNotes);
            SAFE_FREE_STRING(bstrPresenceData);
            SAFE_FREE_STRING(bstrDeviceID);


            SAFE_RELEASE(pDevice);
            SAFE_RELEASE(pDevice2);
            nDeviceCount++;
        }

        SAFE_RELEASE(pEnumDev);
    }


    // Concatenate the Buddy Information to the main string
    _snwprintf(wszBuddyInformation, MAX_XML_STRING-1, L"Name = %s\nURI = %s\nStatus = %s\nPersistent = %s\nNotes = %s\nNumber of Device = %d",
        bstrName, 
        bstrURI,
        wszPresenceStates[enStatus],
        fPersistent? L"True":L"False",
        bstrNotes,
        nDeviceCount);

    // Get the Group Membership
    IRTCEnumGroups *pEnumGroups = NULL;
    IRTCBuddyGroup *pGroup = NULL;

    hr = pBuddy->EnumerateGroups(&pEnumGroups);
    if (FAILED(hr))
    {
        DEBUG_PRINT(("Enumerate Groups Failed 0x%8x", hr));
    }
	else
	{
		nRemainingLength = MAX_XML_STRING - 1 - (int) wcslen(wszGroups);
		if (nRemainingLength > 0)
		{
			wcsncat(wszGroups, L"\n\nMember of following groups: ", nRemainingLength-1);
		}

		wszGroups[MAX_XML_STRING-1] = L'\0';

		while (S_OK == pEnumGroups->Next(1, &pGroup, NULL))
		{
			BSTR bstrGroupName = NULL;

			hr = pGroup->get_Name(&bstrGroupName);
			if (FAILED(hr))
			{
				DEBUG_PRINT(("Get Group Name Failed 0x%8x", hr));
			}

			nRemainingLength = MAX_XML_STRING - 1 - (int) wcslen(wszGroups);
			if (nRemainingLength > 0)
			{
				wcsncat(wszGroups, L"\n\t", nRemainingLength-1);
			}
			
			wszGroups[MAX_STRING-1] = L'\0';

			nRemainingLength = MAX_XML_STRING - 1 - (int) wcslen(wszGroups);
			if (nRemainingLength > 0)
			{
				wcsncat(wszGroups, bstrGroupName, nRemainingLength-1);
			}
			wszGroups[MAX_XML_STRING-1] = L'\0';

			SAFE_FREE_STRING(bstrGroupName);
			SAFE_RELEASE(pGroup);
		}
		
		SAFE_RELEASE(pEnumGroups);
	}

////////////
//
// End RTC Functionality Code
//
////////////

	
	// Concatenate the Devices and Groups Information to the main string

	nRemainingLength = MAX_XML_STRING - 1 - (int) wcslen(wszBuddyInformation);
	if (nRemainingLength > 0)
	{
		wcsncat(wszBuddyInformation, wszDevices, nRemainingLength-1);
	}
	wszBuddyInformation[MAX_XML_STRING-1] = L'\0';

	nRemainingLength = MAX_XML_STRING - 1 - (int) wcslen(wszBuddyInformation);
	if (nRemainingLength > 0)
	{
		wcsncat(wszBuddyInformation, wszGroups, nRemainingLength-1);
	}
	wszBuddyInformation[MAX_XML_STRING-1] = L'\0';

	// Display the box with all of the information:
	MessageBox(hWndParent, wszBuddyInformation, L"Presence Properties", MB_OK);

	SAFE_FREE_STRING(bstrName);
	SAFE_FREE_STRING(bstrURI);
	SAFE_FREE_STRING(bstrNotes);

	return S_OK;
}






////////////////////////////////////////////
//
//	DialpadDialogProc
//

INT_PTR CALLBACK DialpadDialogProc(
  HWND hwndDlg,  // handle to dialog box
  UINT uMsg,     // message
  WPARAM wParam, // first message parameter
  LPARAM lParam  // second message parameter
)
{
    IRTCClient2 *pClient;
    pClient = (IRTCClient2 *)GetWindowLongPtr(hwndDlg, DWLP_USER);

    switch (uMsg) 
    { 
    case WM_INITDIALOG:
		{
			// Store the IRTCClient2 pointer in the
            // window's user data
            SetWindowLongPtr(hwndDlg, DWLP_USER, lParam);
		}

        return TRUE;

    case WM_COMMAND: 
		switch (LOWORD(wParam)) 
		{ 
		case IDOK: 
			{
				EndDialog(hwndDlg, IDOK); 
				return TRUE; 
			}


		case IDCANCEL:		{
			EndDialog(hwndDlg, IDCANCEL);
			return TRUE;
		
							}
		////////////
		//
		// Begin RTC Functionality Code
		//
		// This code demonstrates sending DTMF tones
		//
		////////////

		//Send DTMFs
		case IDC_BUTTON_DIALPAD_1	:		pClient->SendDTMF(RTC_DTMF_1);  return TRUE;
		case IDC_BUTTON_DIALPAD_2   :		pClient->SendDTMF(RTC_DTMF_2);  return TRUE;
		case IDC_BUTTON_DIALPAD_3   :		pClient->SendDTMF(RTC_DTMF_3);  return TRUE;
		case IDC_BUTTON_DIALPAD_4   :		pClient->SendDTMF(RTC_DTMF_4);  return TRUE;
		case IDC_BUTTON_DIALPAD_5   :		pClient->SendDTMF(RTC_DTMF_5);  return TRUE;
		case IDC_BUTTON_DIALPAD_6   :		pClient->SendDTMF(RTC_DTMF_6);  return TRUE;
		case IDC_BUTTON_DIALPAD_7   :		pClient->SendDTMF(RTC_DTMF_7);  return TRUE;
		case IDC_BUTTON_DIALPAD_8   :		pClient->SendDTMF(RTC_DTMF_8);  return TRUE;
		case IDC_BUTTON_DIALPAD_9   :		pClient->SendDTMF(RTC_DTMF_9);  return TRUE;
		case IDC_BUTTON_DIALPAD_0   :		pClient->SendDTMF(RTC_DTMF_0);  return TRUE;	
		case IDC_BUTTON_DIALPAD_STAR:		pClient->SendDTMF(RTC_DTMF_STAR);  return TRUE;
		case IDC_BUTTON_DIALPAD_HASH:		pClient->SendDTMF(RTC_DTMF_POUND);  return TRUE;

		////////////
		//
		// End RTC Functionality Code
		//
		////////

		default: 
			return FALSE;
		}

		return FALSE;
    } 

	return FALSE;
}


////////////////////////////////////////////
//
//	ShowDtmfDialpad
//
HRESULT ShowDtmfDialpad(
		HWND hWndParent,
		IRTCClient2 *pClient)
{
	INT_PTR iRes;

	// Show the dialog
        iRes = DialogBoxParam(
        	GetModuleHandle(NULL),
        	MAKEINTRESOURCE(IDD_DIALOG_DIALPAD),
        	hWndParent,
        	(DLGPROC)DialpadDialogProc,
			(LPARAM) pClient
        );

       
    return  S_OK;    
}




