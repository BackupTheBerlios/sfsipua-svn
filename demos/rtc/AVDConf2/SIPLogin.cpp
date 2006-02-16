// ------------------------------------------------------------------------------------
// Copyright ©2002 Intel Corporation
// All Rights Reserved
// 
// Permission is granted to use, copy, distribute and prepare derivative works of this 
// software for any purpose and without fee, provided, that the above copyright notice
// and this statement appear in all copies.  Intel makes no representations about the
// suitability of this software for any purpose.  This software is provided "AS IS." 
//
// Intel specifically disclaims all warranties, express or implied, and all liability,
// including consequential and other indirect damages, for the use of this software, 
// including liability for infringement of any proprietary rights, and including the 
// warranties of merchantability and fitness for a particular purpose.  Intel does not
// assume any responsibility for any errors which may appear in this software nor any
// responsibility to update it.
// ------------------------------------------------------------------------------------
//
// SIPLogin.cpp : implementation file
//
// Purpose: Dialog box handler to gather user info and SIP server info for server login
//			and XML blob creator.
//

#include "stdafx.h"
#include <afxcmn.h>
#include <mmsystem.h>
#include "avdconf.h"
#include "SIPLogin.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

extern BSTR	g_bstrXMLBuffer;

/////////////////////////////////////////////////////////////////////////////
// CSIPLogin dialog


CSIPLogin::CSIPLogin(CWnd* pParent /*=NULL*/)
	: CDialog(CSIPLogin::IDD, pParent)
{
	//{{AFX_DATA_INIT(CSIPLogin)
	//}}AFX_DATA_INIT
}


void CSIPLogin::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CSIPLogin)
	DDX_Control(pDX, IDC_SIPSERVERIP, m_cSIPServer);
	DDX_Control(pDX, IDC_TRANSPORT, m_cTransport);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CSIPLogin, CDialog)
	//{{AFX_MSG_MAP(CSIPLogin)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CSIPLogin message handlers

BOOL CSIPLogin::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
	// Make TCP the default transport
	m_cTransport.SelectString (0, "TCP");

	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

void CSIPLogin::OnOK() 
{
	DWORD	dwSIPIPAddress = 0;
	CString csTransport, csUserURI;
	char	szSIPIP[MAX_STRING];

	if (m_cSIPServer.IsBlank())
	{
		MessageBox ( "Please enter a SIP Server IP." );
		return;
	}

	GetDlgItemText ( IDC_USERURI, csUserURI );

	// Get SIP Server IP Address
	m_cSIPServer.GetAddress ( dwSIPIPAddress );

	if (dwSIPIPAddress == 0)
	{
		MessageBox ( "Please enter a valid IP Address." );
	}

	m_cTransport.GetLBText (0, csTransport);

	wsprintf ( szSIPIP, "%d.%d.%d.%d", 
		(dwSIPIPAddress >> 24) & 0xff,
		(dwSIPIPAddress >> 16) & 0xff, 
		(dwSIPIPAddress >> 8) & 0xff,
		dwSIPIPAddress & 0xff);
	
	CreateXMLProvision ( csUserURI.GetBuffer(csUserURI.GetLength()), 
		szSIPIP, csTransport.GetBuffer (csTransport.GetLength()), &g_bstrXMLBuffer );

	CDialog::OnOK();
}

HRESULT CSIPLogin::CreateXMLProvision(LPSTR szURI, LPSTR szSIPIP, 
									  LPSTR szTransport, BSTR *bstrBuf)
{
    WCHAR bszXML[MAX_XML_STRING];
    char szRealm[MAX_STRING];
	char szBuf[MAX_XML_STRING];

    // Allow basic authentication if the protocol is TLS
    BOOL bBasicAuth = !strcmpi(szTransport, "TLS");

    // Use the domain of the user uri as the realm
    char *ch = strchr(szURI, '@');

    if (ch == NULL)
    {
        // User URI has no domain, use empty string
        strcpy(szRealm, "");
    }
    else
    {   
        // Found the domain, copy the string
        ch++;
        strcpy(szRealm, ch);
    }

    // If the user URI does not start with sip: then
    // add it
	char szURIBuf[256];
    if (strncmp(szURI, "sip:", 4))
    {
		wsprintf ( szURIBuf, "sip:%s", szURI );
    }

	char szKey[256];
	wsprintf ( szKey, "AVDConf2_%ld", timeGetTime());
    
	// Generate the XML provisioning document
    wsprintf(szBuf, 
		"<provision key=\"%s\" name=\"AVDConf_2\">"
        "<user uri=\"%s\" account=\"\" password=\"\" realm=\"%s\" />"
        "<sipsrv addr=\"%s\" protocol=\"%s\" %s role=\"proxy\">"
        "<session party=\"first\" type=\"pc2pc\" />"
        "<session party=\"first\" type=\"pc2ph\" />"
        "<session party=\"first\" type=\"im\" />"
        "</sipsrv>"
        "<sipsrv addr=\"%s\" protocol=\"%s\" %s role=\"registrar\"/>"
        "</provision>",
        szKey,
		szURIBuf, szRealm,
        szSIPIP, szTransport, bBasicAuth ? "auth=\"basic\"" : "",
        szSIPIP, szTransport, bBasicAuth ? "auth=\"basic\"" : ""
        );

	mbstowcs (bszXML, szBuf, lstrlen(szBuf) + 1);

    *bstrBuf = SysAllocString(bszXML);

    if (!(*bstrBuf))
    {
        // Out of memory
        return E_OUTOFMEMORY;
    }

	return S_OK;
}
