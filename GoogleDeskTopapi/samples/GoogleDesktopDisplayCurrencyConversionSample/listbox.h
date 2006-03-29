// Copyright 2005 Google Inc
// All rights reserved
// 
#ifndef LISTBOX_H
#define LISTBOX_H
// listbox.h -- thinest wrapper for Win32 ListBox control

#include "stdafx.h"

// Simplistic wrapper for Win32 ListBox. Methods are not extensively
// commented because their names match Win32 LB_ messages and documented 
// in Win32 API Docs.

class CListBox : public CWindow {
public:
  // Add String to the ListBox. Beware of sorted listboxes
  void AddString(const TCHAR* str);
  // Find string in the ListBox and return zero based index. -1 if not found
  int FindString(const TCHAR* str);
  // Delete item from ListBox and return remaining item count
  int DeleteItem(int itemIndex); 
  // Return item count
  int GetItemCount();
  // Return item text length in characters
  int GetItemTextLen(int itemIndex);
  // Return item text
  CString GetItemText(int itemIndex);
  // Return selection ahcnor index (for multiple selection listboxes)
  int GetAnchorIndex();
  // Select range of items
  void SelectItemRange(int fromInclusive, int toInclusive);
  // Unselect range of items
  void UnselectItemRange(int fromInclusive, int toInclusive);
  // Return number of selected items
  int GetSelectedCount();
  // Return int array filled with indexes of selected items.
  int GetSelectedItems(CIntArray * a);
};

#endif // LISTBOX_H
