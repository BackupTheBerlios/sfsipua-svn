// RichEditCtrlEx.cpp : implementation file
//
#include "stdafx.h"

#include "RichEditCtrlEx.h"
#include "CNIcq.h"
#include "ImageDataObject.h"

_AFX_RICHEDITEX_STATE::_AFX_RICHEDITEX_STATE()
{
	m_hInstRichEdit20 = NULL ;
}

_AFX_RICHEDITEX_STATE::~_AFX_RICHEDITEX_STATE()
{
	if( m_hInstRichEdit20 != NULL )
	{
		::FreeLibrary( m_hInstRichEdit20 ) ;
	}
}

_AFX_RICHEDITEX_STATE _afxRichEditStateEx ;

BOOL PASCAL AfxInitRichEditEx()
{
	if( ! ::AfxInitRichEdit() )
	{
		return FALSE ;
	}

	_AFX_RICHEDITEX_STATE* l_pState = &_afxRichEditStateEx ;

	if( l_pState->m_hInstRichEdit20 == NULL )
	{
		l_pState->m_hInstRichEdit20 = LoadLibraryA( "RICHED20.DLL" ) ;
	}

	return l_pState->m_hInstRichEdit20 != NULL ;
}

LPCTSTR CRichEditCtrlEx::Emotions[] = {
	"/:O", "/:-/", "/:*", "/>:", "/8-)", "/:(", "/:$", "/:-X", "/:-Z", "/:'(",
	"/:-|", "/:@", "/:P", "/:D", "/:)", "/<D>", "/<J>", "/<H>", "/<M>", "/<QQ>",
	"/<MM>", "/<L>", "/<S>", "/<K>", "/<T>", "/<$>", "/<O>", "/<&>", "/<B>", "/<F>",
	"/<U>", "/<V>", "/<W>", "/<Y1>", "/<Y2>", "/<%>", "/<@@>", "/<X>", "/<I>", "/<G>",
	"/<!!>", "/<~>", "/<C>", "/<Z>", "/<*>", "/<)>", "/<OK>", "/<NO>", "/<00>", "/<11>",
};
int CRichEditCtrlEx::FindEmotion(const char *str)
{
	for (int i = 0; i < NR_EMOTIONS; ++i) {
		const char *dst = Emotions[i];
		const char *src = str;
		while (*++dst && *++src && *dst == *src);

		if (!*dst)
			return i;
	}
	return -1;
}

/////////////////////////////////////////////////////////////////////////////
// CRichEditCtrlEx

CRichEditCtrlEx::CRichEditCtrlEx()
{
}

CRichEditCtrlEx::~CRichEditCtrlEx()
{
}


BEGIN_MESSAGE_MAP(CRichEditCtrlEx, CRichEditCtrl)
	//{{AFX_MSG_MAP(CRichEditCtrlEx)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CRichEditCtrlEx message handlers

BOOL CRichEditCtrlEx::Create(
	DWORD		in_dwStyle, 
	const RECT&	in_rcRect, 
	CWnd*		in_pParentWnd, 
	UINT		in_nID )
{

	if( ! ::AfxInitRichEditEx() )
	{
		return FALSE ;
	}

	CWnd* l_pWnd = this ;

	return l_pWnd->Create( _T( "RichEdit20A" ), NULL, in_dwStyle, in_rcRect, in_pParentWnd, in_nID ) ;
	
//	return CRichEditCtrl::Create(in_dwStyle,in_rcRect,in_pParentWnd,in_nID);
}

void CRichEditCtrlEx::PreSubclassWindow() 
{
	// TODO: Add your specialized code here and/or call the base class
	
	CRichEditCtrl::PreSubclassWindow();
	//SetBackgroundColor( FALSE, ::GetSysColor( COLOR_BTNFACE ));// RGB(0,0,0) );
	//Enable();
	//Disable( ) ;
	//ReadOnly( ) ;
}
void CRichEditCtrlEx::SetText(LPCTSTR text)
{
	SetSel(0, -1);
	Clear();
	InsertText(text);
}
CString CRichEditCtrlEx::GetText(CString &text)
{
	CString str;
	GetWindowText(str);

	IRichEditOle *ole = GetIRichEditOle();
	int n = ole->GetObjectCount();
	REOBJECT reo;
	reo.cbStruct = sizeof(reo);

	text.Empty();
	int pos = 0;
	for (int i = 0; i < n; ++i) 
	{
		ole->GetObject(i, &reo, REO_GETOBJ_NO_INTERFACES);
		text += str.Mid(pos, reo.cp - pos);
		text += Emotions[reo.dwUser];
		pos = reo.cp + 1;
	}
	text += str.Mid(pos);

	return text;

}
void CRichEditCtrlEx::InsertText(LPCTSTR text)
{
	LPCTSTR p, start, prev;
	start = prev = text;

	while ((p = strchr(prev, '/')) != NULL) 
	{
		int i = FindEmotion(p);
		if (i >= 0) 
		{
			ReplaceSel(CString(start, p - start));
			InsertEmotion(i);
			start = prev = p + strlen(Emotions[i]);
		} else	prev = p + 1;
	}

	ReplaceSel(start);
}
void CRichEditCtrlEx::InsertEmotion(int i)
{
	CSkin *m_pSkin = &(((CCNIcqApp *)AfxGetApp())->m_IMSkin);

	CImageList& m_pEmotion = m_pSkin->m_pILEmotions;

	CImageDataObject::InsertBitmap(GetIRichEditOle(),
		m_pSkin->GetImage(m_pEmotion,i,RGB(255,255,255)),i);
}


//
// GLOBAL STREAM MANIPULATORS
CRTFBuilder& doWrite(CRTFBuilder&r, CRichEditCtrl& c) throw ( )
{																					 
	r.write( c ) ;
	return r ;
}

CRTFBuilder& doSize(CRTFBuilder& r, int n ) throw ( )
{																					 
	r.size( n ) ;
	return r ;
}

CRTFBuilder& doBold(CRTFBuilder& r,bool	 b )
{
	r.bold( b ) ;
	return r ;
}

CRTFBuilder& doStrike(CRTFBuilder& r,bool b )
{
	r.strike( b ) ;
	return r ;
}

CRTFBuilder& doItalic(CRTFBuilder& r,bool b )
{
	r.italic( b ) ;
	return r ;
}

CRTFBuilder& doUnderline(CRTFBuilder& r,bool b )
{
	r.underline( b ) ;
	return r ;
}

CRTFBuilder& doFont(CRTFBuilder& r,int	n)
{
	r.font( n ) ;
	return r ;
}

CRTFBuilder& doColor(CRTFBuilder& r,int	n)
{
	r.color( (COLORREF)n ) ;
	return r ;
}

CRTFBuilder& doBackColor(CRTFBuilder& r,int n)
{
	r.backColor( (COLORREF)n ) ;
	return r ;
}

CRTFBuilder& doAddColor(CRTFBuilder& r,int n)
{
	r.addColor( (COLORREF)n ) ;
	return r ;
}

CRTFBuilder& doFont(CRTFBuilder& r,CString& s)
{
	r.font( s ) ;
	return r ;
}

CRTFBuilder& doAddFont(	CRTFBuilder& r,CString&	s)
{
	r.addFont( s ) ;
	return r ;
}


CControlManip write( CRichEditCtrl& c ) throw ( )
{
	return CControlManip(	&doWrite, c) ;
}

CIntManip size( int n ) throw( )
{
	return CIntManip( &doSize, n ) ;
}

CIntManip font( int n ) throw( )
{
	return CIntManip( &doFont,n ) ;
}

CIntManip color( int n ) throw( )
{
	return CIntManip( &doColor, n ) ;
}

CIntManip backColor( int n ) throw( )
{
	return CIntManip( &doBackColor, n ) ;
}

CIntManip addColor( int n ) throw( )
{
	return CIntManip( &doAddColor, n ) ;
}

CStringManip font( LPCTSTR s ) throw( )
{
	return CStringManip(&doFont,s ) ;
}

CStringManip addFont( LPCTSTR s ) throw( )
{
	return CStringManip(&doAddFont, s ) ;
}

CBoolManip bold( bool b ) throw( )
{
	return CBoolManip(&doBold, b ) ;
}

CBoolManip strike( bool b ) throw( )
{
	return CBoolManip(&doStrike, b ) ;
}

CBoolManip italic( bool b ) throw( )
{
	return CBoolManip(&doItalic, b ) ;
}

CBoolManip underline( bool b ) throw( )
{
	return CBoolManip(&doUnderline, b ) ;
}


CRTFBuilder& operator << (CRTFBuilder&	b, RTFSM_PFUNC f ) 
{
	return f( b );
}


CRTFBuilder& operator << (CRTFBuilder& b,CManip& f ) 
{
	return f.go( b );
}

//CRTFBuilder& 
//operator << (	CRTFBuilder&		b, 
//							CControlManip&	f ) 
//{
//	return f.go( b );
//}

CRTFBuilder& normal( CRTFBuilder& b )
{
	b.normal( ) ;
	return b ;
}

CRTFBuilder& black( CRTFBuilder& b )
{
	b.black( ) ;
	return b ;
}

CRTFBuilder& push( CRTFBuilder& b )
{
	b.push( ) ;
	return b ;
}

CRTFBuilder& pull( CRTFBuilder& b )
{
	b.pull( ) ;
	return b ;
}

CRTFBuilder& red( CRTFBuilder& b )
{
	b.red( ) ;
	return b ;
}

CRTFBuilder& green( CRTFBuilder& b )
{
	b.green( ) ;
	return b ;
}

CRTFBuilder& blue( CRTFBuilder& b )
{
	b.blue( ) ;
	return b ;
}

CRTFBuilder& bold( CRTFBuilder& b )
{
	b.bold( ) ;
	return b ;
}

CRTFBuilder& strike( CRTFBuilder& b )
{
	b.strike( ) ;
	return b ;
}

CRTFBuilder& italic( CRTFBuilder& b )
{
	b.italic( ) ;
	return b ;
}

CRTFBuilder& underline( CRTFBuilder& b )
{
	b.underline( ) ;
	return b ;
}

CRTFBuilder::CRTFBuilder()
{
	m_fontList.add( "Arial" ) ;
	m_colorList.add( RGB( 0,0,0 )  ) ;
	m_colorList.add( RGB( 255,0,0 )  ) ;
	m_colorList.add( RGB( 0,255,0 )  ) ;
	m_colorList.add( RGB( 0,0,255 )  ) ;
	size(35);
}

CRTFBuilder::~CRTFBuilder()
{

}


void CRTFBuilder::push( )
{
	m_attrStack.push(m_attr);
}

void CRTFBuilder::pull( )
{
	m_attr = m_attrStack.top( ) ;
	m_attrStack.pop( ) ;
}

void CRTFBuilder::color( COLORREF c )
{
	int n ( m_colorList.find( c )  );
	m_attr.m_nColorFground= n<0 ? m_colorList.add( c )
															:	n ;
}

void CRTFBuilder::backColor( COLORREF c )
{
	int n ( m_colorList.find( c )  )	;
	m_attr.m_nColorBground= n<0 ? m_colorList.add( c )
															: n ;
}

void CRTFBuilder::black()
{
	m_attr.m_nColorFground = 0 ;
}


void CRTFBuilder::red()
{
	m_attr.m_nColorFground = 1 ;
}

void CRTFBuilder::green()
{
	m_attr.m_nColorFground = 2 ;

}

void CRTFBuilder::blue()
{
	m_attr.m_nColorFground = 3 ;
}

void CRTFBuilder::size(int n)
{
	m_attr.m_nFontSize = n ;
}


void CRTFBuilder::font( const CString& strFont)
{

	int nCount =  0 ;
	for ( list<CString>::iterator i = m_fontList.begin( ) ; i != m_fontList.end( ) ; i++, nCount++ )
	{
		if ( (*i) == strFont )
		{
			m_attr.m_nFontNumber = nCount ;
			return ;
		}
	}
	//not there, lets add it
	m_fontList.add( strFont ) ;
	m_attr.m_nFontNumber = nCount ;
}


void CRTFBuilder::bold(bool b)
{
	m_attr.m_bsBold= b ;
}

void CRTFBuilder::strike(bool b)
{
	m_attr.m_bsStrike= b ;
}

void CRTFBuilder::italic(bool b)
{
	m_attr.m_bsItalic = b ;
}

void CRTFBuilder::underline(bool b)
{
	m_attr.m_bsUnderline = b ;
}

void CRTFBuilder::normal( )
{
	bold(false);
	italic(false);
	underline(false);
	strike(false);
}

static DWORD CALLBACK EditStreamCallBack(DWORD dwCookie, LPBYTE pbBuff, LONG cb, LONG *pcb )
{
	CString *pstr = (CString *)dwCookie;

	if( pstr->GetLength() < cb )
	{
		*pcb = pstr->GetLength();
		memcpy(pbBuff, (LPCSTR)*pstr, *pcb );
		pstr->Empty();
	}
	else
	{
		*pcb = cb;
		memcpy(	pbBuff, (LPCSTR)*pstr, *pcb ) ;
		*pstr = pstr->Right( pstr->GetLength() - cb ) ;
	}
	return 0;
}


void CRTFBuilder::write( CRichEditCtrl& c )
{
	m_string += '}';

//	CRtfStringDlg d( m_string ) ;

	EDITSTREAM es = {(DWORD)&m_string, 0, EditStreamCallBack };

	// richEd is the rich edit control
	c.StreamIn( SF_RTF | SFF_SELECTION, es);

	m_string.Empty( ) ;
}



CRTFBuilder& CRTFBuilder::operator+=( LPCTSTR p )
{
	CString s( p ) , s2 ;
	for ( int i = 0 ; i < s.GetLength( ) ; i ++ )
		if ( s[i]=='\n' )
			s2+= (CString)"\r\n" += "\\par ";//\\par " ;
		else
			s2+= s[i] ;

	m_string += 
	(CString)"{\\rtf1\\ansi\\ansicpg1252\\deff0\\deftab720" += 
	(CString)m_fontList +=
	(CString)m_colorList += 
	(CString)m_attr += s2  ;
	return *this ;
}

CRTFBuilder& CRTFBuilder::operator << ( LPCTSTR p )
{
	*this+=p ;
	return *this ;
}

CRTFBuilder& CRTFBuilder::operator << ( int n )
{
	CString s ;
	s.Format( "%d", n ) ;
	*this += (LPCTSTR)s ;
	return *this ;
}


CRTFBuilder& CRTFBuilder::operator >> ( CRichEditCtrl& e )
{
	write( e ) ;
	return *this ;
}

