
#if !defined(AFX_CNOutBarEDIT_H__18A5D73E_2167_4872_9C44_61123C233826__INCLUDED_)
#define AFX_CNOutBarEDIT_H__18A5D73E_2167_4872_9C44_61123C233826__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// CNOutBarEdit.h : header file
//

class CNOutBarCtrl;

/////////////////////////////////////////////////////////////////////////////
// CNOutBarEdit window

class CNOutBarEdit : public CEdit
{
// Construction
public:
	CNOutBarEdit(CNOutBarCtrl *l, int obj, int index);

// Attributes
public:
	int obj;
	int index;

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CNOutBarEdit)
	public:
	virtual BOOL PreTranslateMessage(MSG* pMsg);
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~CNOutBarEdit();

private:
	CNOutBarCtrl *listener;

	// Generated message map functions
protected:
	//{{AFX_MSG(CNOutBarEdit)
	afx_msg void OnKillFocus(CWnd* pNewWnd);
	//}}AFX_MSG

	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_CNOutBarEDIT_H__18A5D73E_2167_4872_9C44_61123C233826__INCLUDED_)
