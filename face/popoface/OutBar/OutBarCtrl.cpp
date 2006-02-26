// CNOutBarCtrl.cpp : implementation file
//

#include "stdafx.h"
#include "CNIcq.h"
#include "OutBarCtrl.h"
#include "OutBarEdit.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

CNOutBarFolder::~CNOutBarFolder()
{
	for (int i = items.size() - 1; i >= 0; i--)
		delete items[i];
}

void CNOutBarFolder::addItem(const char *t, int img)
{
	CNOutBarItem *item = new CNOutBarItem(t, img);
	items.push_back(item);
}

#define IDT_SCROLL		1001
#define IDT_DBLCLK		1002

/////////////////////////////////////////////////////////////////////////////
// CNOutBarCtrl

CNOutBarCtrl::CNOutBarCtrl()
{
	listener = NULL;
	largeIcons = smallIcons = NULL;
	selFolder = 0;
	bgColor = RGB(128, 128, 192);
	fontColor = RGB(0, 0, 0);
	lastHit =
	pressedHit =
	clickedItem = -1;
	dragItem = -1;
	largeIconView = TRUE;

	editCtrl = NULL;

	currentCursor = NULL;
	handCursor = AfxGetApp()->LoadCursor(IDC_HAND);
	forbiddenCursor = AfxGetApp()->LoadCursor(IDC_FORBIDDEN);
	dragCursor = AfxGetApp()->LoadCursor(IDC_DRAG);
}

CNOutBarCtrl::~CNOutBarCtrl()
{
	if (editCtrl)
		delete editCtrl;

	removeAllFolders();
}

int CNOutBarCtrl::addFolder(const char *text)
{
	CNOutBarFolder *f = new CNOutBarFolder(text);
	folders.push_back(f);
	return folders.size() - 1;
}

void CNOutBarCtrl::addItem(int folder, const char *text, int image)
{
	if (folder >= 0 && folder < getFolderCount())
		folders[folder]->addItem(text, image);
}

void CNOutBarCtrl::insertItem(int folder, int pos, CNOutBarItem *item)
{
	if (folder >= 0 && folder < getFolderCount()) {
		vector<CNOutBarItem *> &items = folders[folder]->items;
		items.insert(items.begin() + pos, item);
	}
}

void CNOutBarCtrl::getFolderName(int i, CString &name)
{
	if (i >= 0 && i < getFolderCount())
		name = folders[i]->text;
}

int CNOutBarCtrl::getItemCount(int folder)
{
	return folders[folder]->items.size();
}

/*
 * Returns the current scroll position in the selected folder
 */
int &CNOutBarCtrl::scrollPos()
{
	return folders[selFolder]->scrollPos;
}

/*
 * Returns how many items can be hold in one page according to
 * the current window size
 */
int CNOutBarCtrl::getCountPerPage()
{
	CRect rc;
	getInsideRect(rc);

	int h = (largeIconView ? LARGE_ITEM_H : SMALL_ITEM_H);
	return ((rc.Height() / h) + 1);
}

void CNOutBarCtrl::setSelFolder(int i)
{
	if (i != selFolder && i < getFolderCount())
		selFolder = i;
}

void CNOutBarCtrl::getFolderRect(CRect &rc, int i)
{
	GetClientRect(rc);
	
	if (i <= selFolder)
		rc.top += i * FOLDER_HEIGHT;
	else
		rc.top = rc.bottom - (folders.size() - i) * FOLDER_HEIGHT;
		
	rc.bottom = rc.top + FOLDER_HEIGHT;
}

/*
 * Get the inside rectangle excluding the folders
 */
void CNOutBarCtrl::getInsideRect(CRect &rc)
{
	GetClientRect(rc);
	rc.top += (selFolder + 1) * FOLDER_HEIGHT;
	rc.bottom -= (folders.size() - selFolder - 1) * FOLDER_HEIGHT;
}

void CNOutBarCtrl::getItemRect(CRect &rc, int i)
{
	getInsideRect(rc);
	
	int h = (largeIconView ? LARGE_ITEM_H : SMALL_ITEM_H);
	rc.top += h * (i - scrollPos()) + ICON_OFFSET;	
	rc.bottom = rc.top + h;
}

/*
 * Get the icon rectangle of an item
 */
void CNOutBarCtrl::getIconRect(CRect &rc, int i)
{
	getItemRect(rc, i);
	
	if (largeIconView) {
		rc.left += (rc.Width() - LARGE_ICON_W) / 2;
		rc.right = rc.left + LARGE_ICON_W;
		rc.bottom = rc.top + LARGE_ICON_H;
	} else {
		rc.top += (rc.Height() - SMALL_ICON_H) / 2;
		rc.bottom = rc.top + SMALL_ICON_H;
		rc.left += 2;
		rc.right = rc.left + SMALL_ICON_W;
	}
}

/*
 * Get the text rectangle(below the icon) of an item
 */
void CNOutBarCtrl::getLabelRect(CRect &rc, int i)
{
	getItemRect(rc, i);
	
	if (largeIconView)
		rc.top += LARGE_ICON_H;
	else
		rc.left += SMALL_ICON_W + 2 + 5;
}

/*
 * Get the scroll box rectangle according to the current system settings
 */
void CNOutBarCtrl::getScrollRect(CRect &rc, int i)
{
	getInsideRect(rc);
	int size = GetSystemMetrics(SM_CXVSCROLL);

	rc.right -= 5;
	rc.left = rc.right - size;

	if (i == SCROLL_DIR_UP) {
		rc.top += 5;
		rc.bottom = rc.top + size;
	} else {
		rc.bottom -= 5;
		rc.top = rc.bottom - size;
	}
}

void CNOutBarCtrl::repaintInsideRect()
{
	CRect rc;
	getInsideRect(rc);
	InvalidateRect(rc);
}

/*
 * Return the current object under the certain point
 */
HIT CNOutBarCtrl::hitTest(const CPoint &pt)
{
	int obj = HT_NONE;
	int index = -1;
	CRect rcClient, rc;
	GetClientRect(rcClient);
	getInsideRect(rc);

	if (!rc.PtInRect(pt)) {
		if (pt.y >= 0 && pt.y < rc.top) {
			obj = HT_FOLDER;
			index = (pt.y - 1) / FOLDER_HEIGHT;
		} else if (pt.y > rc.bottom && pt.y < rcClient.bottom - 1) {
			obj = HT_FOLDER;
			index = (pt.y - rc.bottom) / FOLDER_HEIGHT + selFolder + 1;
		}
	} else {
		for (int i = 0; i < 2; i++) {
			if (canScroll(i)) {
				CRect rcScroll;
				getScrollRect(rcScroll, i);
				if (rcScroll.PtInRect(pt))
					return MAKEHIT(HT_SCROLL, i);
			}
		}

		if (largeIconView) {
			int offset = (rc.Width() - LARGE_ICON_W) / 2;
			if (pt.x >= rc.left + offset &&
				pt.x <= rc.right - offset) {
				int y = pt.y - rc.top;
				offset = y % LARGE_ITEM_H - ICON_OFFSET;
				if (offset >= 0 && offset <= LARGE_ICON_H) {
					int i = y / LARGE_ITEM_H + scrollPos();
					if (i <= getMaxVisibleItem()) {
						obj = HT_ITEM;
						index = i;
					}
				}
			}
		} else if (pt.x < SMALL_ICON_W + 32) {
			int i = (pt.y - rc.top) / SMALL_ITEM_H + scrollPos();
			if (i <= getMaxVisibleItem()) {
				obj = HT_ITEM;
				index = i;
			}
		}
	}
	
	return MAKEHIT(obj, index);
}

/*
 * Determine if we can scroll at current scroll position
 */
BOOL CNOutBarCtrl::canScroll(int dir)
{
	if (dir == SCROLL_DIR_UP)
		return (scrollPos() > 0);

	int n = getCountPerPage();
	return (n + scrollPos() <= getMaxVisibleItem() + 1);
}

void CNOutBarCtrl::scroll(int dir, int delta)
{
	if (dir == SCROLL_DIR_UP)
		scrollPos() -= delta;
	else
		scrollPos() += delta;

	if (!canScroll(dir)) {
		KillTimer(IDT_SCROLL);
			
		CClientDC dc(this);
		drawScroll(&dc, dir);
		pressedHit = lastHit = HITNONE;
	}
		
	repaintInsideRect();
}

void CNOutBarCtrl::drawFolder(CDC *pDC, int i, BOOL pressed, BOOL hilight)
{
	CRect rc;
	getFolderRect(rc, i);

	if (pressed) {
		pDC->Draw3dRect(rc, GetSysColor(COLOR_3DDKSHADOW), GetSysColor(COLOR_BTNHILIGHT));
		rc.InflateRect(-1, -1);
		pDC->Draw3dRect(rc, GetSysColor(COLOR_BTNSHADOW), GetSysColor(COLOR_BTNFACE));
	} else if (hilight) {
		pDC->Draw3dRect(rc, GetSysColor(COLOR_BTNHILIGHT), GetSysColor(COLOR_3DDKSHADOW));
		rc.InflateRect(-1, -1);
		pDC->Draw3dRect(rc, GetSysColor(COLOR_BTNFACE), GetSysColor(COLOR_3DDKSHADOW));
	} else
		pDC->Draw3dRect(rc, GetSysColor(COLOR_BTNHILIGHT), GetSysColor(COLOR_3DDKSHADOW));

	rc.InflateRect(-1, -1);
	pDC->FillSolidRect(rc, GetSysColor(COLOR_BTNFACE));
	
	if (pressed)
		rc.OffsetRect(1, 1);

	drawFolderText(pDC, i, rc);
}

void CNOutBarCtrl::drawFolderText(CDC *pDC, int i, CRect &rc)
{
	CFont *oldFont = pDC->SelectObject(CFont::FromHandle((HFONT) GetStockObject(DEFAULT_GUI_FONT)));
	int oldBkMode = pDC->SetBkMode(TRANSPARENT);

	pDC->DrawText(folders[i]->text, rc, DT_SINGLELINE | DT_CENTER | DT_VCENTER);

	pDC->SetBkMode(oldBkMode);
	pDC->SelectObject(oldFont);
}

void CNOutBarCtrl::animateFolder(int from, int to)
{
	CClientDC dc(this);
	CDC memDC;
	memDC.CreateCompatibleDC(&dc);
	CRect rc;
	GetClientRect(rc);
	CBitmap bm;
	bm.CreateCompatibleBitmap(&dc, rc.Width(), rc.Height());
	CBitmap *oldBitmap = memDC.SelectObject(&bm);

	getInsideRect(rc);
	selFolder = to;
	CRect toInsideRect;
	getInsideRect(toInsideRect);

	drawAll(&memDC);

	if (to > from) {
		int srcy = (from + 1) * FOLDER_HEIGHT;
		int y = rc.bottom;

		while (y > rc.top) {
			dc.BitBlt(0, y, rc.Width(), toInsideRect.bottom - y, &memDC, 0, srcy, SRCCOPY);
			y -= FOLDER_HEIGHT;
			Sleep(10);
		}

	} else {
		drawFolder(&dc, to);

		int folderHeight = (from - to) * FOLDER_HEIGHT;
		int h = 0;

		while (h < rc.Height()) {
			int height = h + folderHeight;
			dc.BitBlt(0, toInsideRect.top, rc.Width(), height,
				&memDC, 0, rc.bottom - height, SRCCOPY);
			h += FOLDER_HEIGHT;
			Sleep(10);
		}
	}

	Invalidate();

	memDC.SelectObject(oldBitmap);
}

void CNOutBarCtrl::drawItem(CDC *pDC, int i, BOOL redraw)
{
	CRect rc;
	getIconRect(rc, i);
	if (redraw) {
		CRect clip;
		getInsideRect(clip);
		CRgn rgn;
		rgn.CreateRectRgnIndirect(clip);
		pDC->SelectClipRgn(&rgn);
		drawBackground(pDC, rc);
	}
	drawItemImage(pDC, i, rc);
	if (!redraw)
		drawItemText(pDC, i, fontColor);
}

/*
 * Get the index of the maximum item that can be seen, usually overridden by subclasses
 */
int CNOutBarCtrl::getMaxVisibleItem()
{
	int max = getCountPerPage() + scrollPos();
	int n = getMaxItem();
	if (max > n)
		max = n;
	return (--max);
}

int CNOutBarCtrl::getMaxItem()
{
	return getItemCount();
}

void CNOutBarCtrl::drawBackground(CDC *pDC, CRect &rc)
{
	pDC->FillSolidRect(rc, bgColor);
}

void CNOutBarCtrl::drawItemImage(CDC *pDC, int i, CRect &rc)
{
	int img = folders[selFolder]->items[i]->image;
	CImageList *imageList = (largeIconView ? largeIcons : smallIcons);
	imageList->Draw(pDC, img, rc.TopLeft(), ILD_TRANSPARENT);
}

void CNOutBarCtrl::drawItemText(CDC *pDC, int i, COLORREF color)
{
	CRect rc;
	getLabelRect(rc, i);
	CNOutBarItem *item = folders[selFolder]->items[i];
	int style = DT_SINGLELINE | DT_VCENTER;
	if (largeIconView)
		style |= DT_CENTER;

	CFont *oldFont = pDC->SelectObject(CFont::FromHandle((HFONT) GetStockObject(DEFAULT_GUI_FONT)));
	COLORREF oldColor = pDC->SetTextColor(color);
	int oldBkMode = pDC->SetBkMode(TRANSPARENT);

	pDC->DrawText(item->text, rc, style);

	pDC->SetBkMode(oldBkMode);
	pDC->SetTextColor(oldColor);
	pDC->SelectObject(oldFont);
}

void CNOutBarCtrl::drawAll(CDC *pDC)
{
	CDC memDC;
	memDC.CreateCompatibleDC(pDC);
	CRect rcClient;
	GetClientRect(rcClient);
	CBitmap bm;
	bm.CreateCompatibleBitmap(pDC, rcClient.Width(), rcClient.Height());
	CBitmap *oldBitmap = memDC.SelectObject(&bm);

	int obj = HITOBJ(lastHit);
	int index = HITINDEX(lastHit);

	int i;
	for (i = folders.size() - 1; i >= 0; i--)
		drawFolder(&memDC, i, FALSE, (obj == HT_FOLDER && index == i));

	CRect rc;
	getInsideRect(rc);
	drawBackground(&memDC, rc);

	CRgn rgn;
	rgn.CreateRectRgnIndirect(rc);
	memDC.SelectClipRgn(&rgn);

	int max = getMaxVisibleItem();
	for (i = scrollPos(); i <= max; i++)
		drawItem(&memDC, i);

	if (obj == HT_ITEM)
		hilightItem(&memDC, index, FALSE);

	for (i = 1; i >= 0; i--) {
		if (canScroll(i))
			drawScroll(&memDC, i, pressedHit == MAKEHIT(HT_SCROLL, i));
	}

	pDC->BitBlt(0, 0, rcClient.Width(), rcClient.Height(), &memDC, 0, 0, SRCCOPY);

	memDC.SelectObject(oldBitmap);
}

void CNOutBarCtrl::hilightItem(CDC *pDC, int i, BOOL pressed)
{	
	CRect rc;
	getInsideRect(rc);
	CRgn rgn;
	rgn.CreateRectRgnIndirect(rc);
	pDC->SelectClipRgn(&rgn);
	getIconRect(rc, i);
	
	if (pressed)
		pDC->Draw3dRect(rc, GetSysColor(COLOR_3DDKSHADOW), GetSysColor(COLOR_BTNHILIGHT));
	else
		pDC->Draw3dRect(rc, GetSysColor(COLOR_BTNHILIGHT), GetSysColor(COLOR_3DDKSHADOW));
}

/*
 * Draw the scroll box
 */
void CNOutBarCtrl::drawScroll(CDC *pDC, int i, BOOL pressed)
{
	CRect rc;
	getScrollRect(rc, i);

	int state = (i == SCROLL_DIR_UP ? DFCS_SCROLLUP : DFCS_SCROLLDOWN);
	if (pressed)
		state |= DFCS_PUSHED;
	pDC->DrawFrameControl(rc, DFC_SCROLL, state);
}

void CNOutBarCtrl::removeFolder(int i)
{
	delete folders[i];
	folders.erase(folders.begin() + i);
	Invalidate();
}

void CNOutBarCtrl::removeAllFolders()
{
	for (int i = folders.size() - 1; i >= 0; i--)
		delete folders[i];
	folders.clear();
}

/*
 * Remove an item from the selected folder
 */
void CNOutBarCtrl::removeItem(int folder, int i)
{
	vector<CNOutBarItem *> &items = folders[folder]->items;
	delete items[i];
	items.erase(items.begin() + i);
	lastHit = HITNONE;
	if (folder == selFolder)
		repaintInsideRect();
}

/*
 * Rename a folder or an item
 */
void CNOutBarCtrl::renameUI()
{
	onEditCanceled();
	
	int obj = HITOBJ(lastHit);
	int i = HITINDEX(lastHit);
	DWORD flags = WS_VISIBLE | WS_CHILD | ES_CENTER;
	const char *text = "";

	editCtrl = new CNOutBarEdit(this, obj, i);

	if (obj == HT_FOLDER) {
		text = folders[i]->text;
		editCtrl->Create(flags, CRect(0, 0, 0, 0), this, 1);
		editCtrl->ModifyStyleEx(0, WS_EX_CLIENTEDGE, SWP_FRAMECHANGED);

	} else if (obj == HT_ITEM) {
		CClientDC dc(this);
		drawItem(&dc, i, TRUE);

		text = folders[selFolder]->items[i]->text;
		editCtrl->Create(flags | WS_BORDER, CRect(0, 0, 0, 0), this, 1);
	}

	editCtrl->SetFont(CFont::FromHandle((HFONT) GetStockObject(DEFAULT_GUI_FONT)));
	editCtrl->SetWindowText(text);
	editCtrl->SetFocus();
	editCtrl->SetSel(0, -1);
	resizeEditCtrl();
}

void CNOutBarCtrl::addFolderUI()
{
	CNOutBarFolder *f = new CNOutBarFolder("");
	folders.insert(folders.begin() + selFolder + 1, f);
	Invalidate();

	lastHit = MAKEHIT(HT_FOLDER, selFolder + 1);
	renameUI();
}

/*
 * Resize the edit control according to the current window size
 */
void CNOutBarCtrl::resizeEditCtrl()
{
	if (!editCtrl)
		return;

	int obj = editCtrl->obj;
	int i = editCtrl->index;
	
	CRect rc;
	if (obj == HT_FOLDER) {
		getFolderRect(rc, i);
		rc.InflateRect(-2, -2);
	} else if (obj == HT_ITEM) {
		getLabelRect(rc, i);
		if (largeIconView) {
			rc.left += 5;
			rc.right -= 5;
		}
	}

	editCtrl->MoveWindow(rc);
}

/*
 * Called when 'enter' is pressed in the edit control
 */
void CNOutBarCtrl::onEditFinished()
{
	if (!editCtrl)
		return;
	
	CString text;
	editCtrl->GetWindowText(text);
	int index = editCtrl->index;
	
	if (editCtrl->obj == HT_FOLDER)
		folders[index]->text = text;
	else if (editCtrl->obj == HT_ITEM)
		folders[selFolder]->items[index]->text = text;
		
	if (listener)
		listener->renamed(editCtrl->obj, index, text);

	delete editCtrl;
	editCtrl = NULL;
}

/*
 * Called When 'ESC' is pressed, or the edit control lost its focus
 */
void CNOutBarCtrl::onEditCanceled()
{
	if (editCtrl) {
		delete editCtrl;
		editCtrl = NULL;
	}
}


BEGIN_MESSAGE_MAP(CNOutBarCtrl, CWnd)
	//{{AFX_MSG_MAP(CNOutBarCtrl)
	ON_WM_PAINT()
	ON_WM_MOUSEMOVE()
	ON_WM_LBUTTONDOWN()
	ON_WM_LBUTTONUP()
	ON_WM_LBUTTONDBLCLK()
	ON_WM_TIMER()
	ON_WM_SIZE()
	ON_WM_MOUSEWHEEL()
	ON_WM_RBUTTONDOWN()
	ON_WM_ERASEBKGND()
	ON_WM_SETCURSOR()
	ON_WM_KEYDOWN()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()


/////////////////////////////////////////////////////////////////////////////
// CNOutBarCtrl message handlers

void CNOutBarCtrl::OnPaint() 
{
	CPaintDC dc(this); // device context for painting

	drawAll(&dc);
}

void CNOutBarCtrl::OnMouseMove(UINT nFlags, CPoint point) 
{
	HIT hit = hitTest(point);

	if (hit != lastHit) {
		int newObj = HITOBJ(hit);
		int newIndex = HITINDEX(hit);

		if (!editCtrl) {
			CClientDC dc(this);

			int obj = HITOBJ(lastHit);
			int index = HITINDEX(lastHit);

			if (obj == HT_FOLDER)
				drawFolder(&dc, index, FALSE, FALSE);
			else if (obj == HT_ITEM)
				drawItem(&dc, index, TRUE);
			else if (obj == HT_SCROLL && HITOBJ(pressedHit) == HT_SCROLL) {
				drawScroll(&dc, index);
				KillTimer(IDT_SCROLL);
			}

			if (newObj == HT_FOLDER)
				drawFolder(&dc, newIndex, hit == pressedHit, TRUE);
			else {
				if (newObj == HT_ITEM)
					hilightItem(&dc, newIndex, hit == pressedHit);
			}
		}

		lastHit = hit;

		if (dragItem >= 0) {
			if (newObj == HT_FOLDER && selFolder != newIndex)
				currentCursor = dragCursor;
			else
				currentCursor = forbiddenCursor;
		} else if (newObj == HT_FOLDER)
			currentCursor = handCursor;
		else
			currentCursor = NULL;
	}
	
	CWnd::OnMouseMove(nFlags, point);
}

void CNOutBarCtrl::OnLButtonDown(UINT nFlags, CPoint point) 
{
	if (GetFocus() != this) SetFocus();

	OnMouseMove(nFlags, point);

	int obj = HITOBJ(lastHit);
	int index = HITINDEX(lastHit);

	CClientDC dc(this);

	pressedHit = lastHit;

	if (obj == HT_FOLDER)
		drawFolder(&dc, index, TRUE);
	else if (obj == HT_ITEM) {
		dragItem = index;
		hilightItem(&dc, index, TRUE);
	} else if (obj == HT_SCROLL) {
		SetTimer(IDT_SCROLL, 50, NULL);
		drawScroll(&dc, index, TRUE);
	}

	CWnd::OnLButtonDown(nFlags, point);
}

void CNOutBarCtrl::OnLButtonUp(UINT nFlags, CPoint point) 
{
	OnMouseMove(nFlags, point);
	
	int obj = HITOBJ(lastHit);
	int index = HITINDEX(lastHit);

	if (dragItem >= 0) {
		if (obj == HT_FOLDER) {
			currentCursor = handCursor;
			if (listener && selFolder != index)
				listener->itemDragged(dragItem, index);
		} else
			currentCursor = NULL;
		dragItem = -1;
	}

	CClientDC dc(this);
	
	if (pressedHit == lastHit) {
		if (obj == HT_FOLDER) {
			if (index == selFolder)
				drawFolder(&dc, index);
			else {
				if (listener) {
					listener->selFolderChanged(selFolder);
					animateFolder(selFolder, index);
				}
			}
		} else if (obj == HT_ITEM) {
			hilightItem(&dc, index, FALSE);
			clickedItem = index;
			SetTimer(IDT_DBLCLK, 300, NULL);
		} else if (obj == HT_SCROLL) {
			drawScroll(&dc, index);
			KillTimer(IDT_SCROLL);
		}
	}

	pressedHit = HITNONE;
	
	CWnd::OnLButtonUp(nFlags, point);
}

void CNOutBarCtrl::OnLButtonDblClk(UINT nFlags, CPoint point) 
{
	if (HITOBJ(lastHit) == HT_ITEM) {
		KillTimer(IDT_DBLCLK);
		if (listener && clickedItem >= 0)
			listener->itemDoubleClicked(clickedItem);
		clickedItem = -1;
	}

	CWnd::OnLButtonDblClk(nFlags, point);
}

void CNOutBarCtrl::OnTimer(UINT nIDEvent) 
{
	if (nIDEvent == IDT_SCROLL) {
		if (HITOBJ(pressedHit) == HT_SCROLL)
			scroll(HITINDEX(pressedHit));

	} else if (nIDEvent == IDT_DBLCLK) {
		KillTimer(IDT_DBLCLK);
		if (listener && lastHit == MAKEHIT(HT_ITEM, clickedItem))
			listener->itemClicked(clickedItem);
		clickedItem = -1;

	} else
		CWnd::OnTimer(nIDEvent);
}

void CNOutBarCtrl::OnSize(UINT nType, int cx, int cy) 
{
	CWnd::OnSize(nType, cx, cy);
	
	resizeEditCtrl();
}

BOOL CNOutBarCtrl::OnMouseWheel(UINT nFlags, short zDelta, CPoint pt) 
{
	int dir;
	int delta = zDelta / WHEEL_DELTA;
	
	if (delta > 0)
		dir = SCROLL_DIR_UP;
	else {
		dir = SCROLL_DIR_DOWN;
		delta = -delta;
	}
	if (canScroll(dir))
		scroll(dir, delta);

	return CWnd::OnMouseWheel(nFlags, zDelta, pt);
}

void CNOutBarCtrl::OnRButtonDown(UINT nFlags, CPoint point) 
{
	OnMouseMove(nFlags, point);
	
	if (listener)
		listener->rightButtonDown(HITOBJ(lastHit), HITINDEX(lastHit));
	
	CWnd::OnRButtonDown(nFlags, point);
}

BOOL CNOutBarCtrl::OnEraseBkgnd(CDC* pDC) 
{
	// Do not let Windows to draw the background for us, since
	// we will do the entire painting when WM_PAINT is received.
	return TRUE;
}

BOOL CNOutBarCtrl::OnSetCursor(CWnd* pWnd, UINT nHitTest, UINT message) 
{
	if (currentCursor) {
		SetCursor(currentCursor);
		return TRUE;
	}
	return CWnd::OnSetCursor(pWnd, nHitTest, message);
}

void CNOutBarCtrl::OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags) 
{
	// Find an item when a user pressed the first letter of an item,
	// and set the scroll position properly

	int start = -1;
	if (HITOBJ(lastHit) == HT_ITEM)
		start = HITINDEX(lastHit);

	vector<CNOutBarItem *> &items = folders[selFolder]->items;
	int n = getMaxItem();
	if (isalpha(nChar))
		nChar = toupper(nChar);

	int k = start;
	for (int i = 0; i < n; ++i) {
		int c = items[++k % n]->text[0];
		if (isalpha(c))
			c = toupper(c);
		if (nChar == c)
			break;
	}
	if (i < n) {
		k %= n;
		lastHit = MAKEHIT(HT_ITEM, k);
		scrollToPos(k);
	}

	CWnd::OnKeyDown(nChar, nRepCnt, nFlags);
}
