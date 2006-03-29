// Plugin.cpp : Implementation of C[!output PROJECT_NAME]PluginDetailsView

#include "stdafx.h"
#include "DetailsView.h"

//------ C[!output PROJECT_NAME]PluginDetailsView: the custom details view

C[!output PROJECT_NAME]PluginDetailsView::C[!output PROJECT_NAME]PluginDetailsView() {
  // Uncomment the line below if you want your details view to be a window. This is
  // required if you want to use standard windows controls in your details view.
  // Also you should comment out the COM_INTERFACE_ENTRY(IOleInPlaceObjectWindowless)
  // in this class's COM map (in the header file)
  //
  // m_bWindowOnly = TRUE;
}

HRESULT C[!output PROJECT_NAME]PluginDetailsView::FinalConstruct() {
  return S_OK;
}

void C[!output PROJECT_NAME]PluginDetailsView::FinalRelease() {
  // Free your resources/GDI objects here
}

HRESULT C[!output PROJECT_NAME]PluginDetailsView::OnDraw(ATL_DRAWINFO& di) {
  // Draw the content
  HDC dc = di.hdcDraw;
  RECT rc = {
    di.prcBounds->left, di.prcBounds->top, di.prcBounds->right, di.prcBounds->bottom
  };

  HGDIOBJ oldpen = ::SelectObject(dc, ::GetStockObject(NULL_PEN));
  HGDIOBJ oldfont = ::SelectObject(dc, ::GetStockObject(DEFAULT_GUI_FONT));
  ::FillRect(dc, &rc, reinterpret_cast<HBRUSH>(COLOR_WINDOW+1));
  ::DrawText(dc, text_, text_.GetLength(), &rc, DT_WORDBREAK);
  ::SelectObject(dc, oldfont);
  ::SelectObject(dc, oldpen);

  return S_OK;
}

STDMETHODIMP C[!output PROJECT_NAME]PluginDetailsView::SetContent(BSTR text) {
  text_ = text;
  return S_OK;
}

HRESULT C[!output PROJECT_NAME]PluginDetailsView::OnPostVerbInPlaceActivate() {
  // Create your child windows/controls/resources/GDI objects here
  return S_OK;
}
