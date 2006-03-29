// Copyright 2005 Google Inc
// All rights reserved
// 
// CListBox.cpp

#include "stdafx.h"
#include "listbox.h"

// Add String to the ListBox. Beware of sorted listboxes

void CListBox::AddString(const TCHAR* s) {
  SendMessage(LB_ADDSTRING, 0, reinterpret_cast<LPARAM>(s)); 
}

// Find string in the ListBox and return zero based index. -1 if not found

int CListBox::FindString(const TCHAR* s) {
  return (int)SendMessage(LB_FINDSTRING, 0, reinterpret_cast<LPARAM>(s)); 
}

// Delete item from ListBox and return remaining item count

int CListBox::DeleteItem(int i) { // returns remaining count
  return (int)SendMessage(LB_DELETESTRING, i, 0); 
}

// Return item count

int CListBox::GetItemCount() {
  return (int)SendMessage(LB_GETCOUNT, 0, 0); 
}

// Return item text length in characters

int CListBox::GetItemTextLen(int i) {
  return (int)SendMessage(LB_GETTEXTLEN, i, 0); 
}

// Return item text

CString CListBox::GetItemText(int i) {
  int len = GetItemTextLen(i);
  ATLASSERT(len >= 0);
  TCHAR* buf = new TCHAR[len + 1];
  if (buf != NULL) {
    ATLVERIFY(len == SendMessage(LB_GETTEXT, i, reinterpret_cast<LPARAM>(buf)));
    CString s(buf);
    delete buf;
    return s;
  } else {
    return _T("");
  }
}

// Return selection ahcnor index (for multiple selection listboxes)

int CListBox::GetAnchorIndex() {
  return (int)SendMessage(LB_GETANCHORINDEX, 0, 0); 
}

// Select range of items

void CListBox::SelectItemRange(int fromInclusive, int toInclusive) {
  SendMessage(LB_SELITEMRANGE, true, MAKELONG(fromInclusive, toInclusive));
}

// Unselect range of items

void CListBox::UnselectItemRange(int fromInclusive, int toInclusive) {
  SendMessage(LB_SELITEMRANGE, false, MAKELONG(fromInclusive, toInclusive));
}

// Return number of selected items

int CListBox::GetSelectedCount() {
  return (int)SendMessage(LB_GETSELCOUNT, 0, 0); 
}

// Return int array filled with indexes of selected items.
 
int CListBox::GetSelectedItems(CIntArray * a) {
  a->RemoveAll();
  int n = GetSelectedCount();
  if (n > 0) {
    int* buf = new int[n];
    if (buf != NULL) {
      ATLVERIFY(n == SendMessage(LB_GETSELITEMS, n, reinterpret_cast<LPARAM>(buf)));
      for (int i = 0; i < n; i++) {
        a->Add(buf[i]);
      }
      delete [] buf;
    }
  }
  return n;
}
