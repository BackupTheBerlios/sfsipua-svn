// Copyright 2005 Google Inc.
// All Rights Reserved.

using System;
using System.Drawing;
using System.Runtime.InteropServices;
using System.Windows.Forms;

namespace GoogleDesktopDisplayCSharpSample {
  #region Generic PropertyPage base class

  public class PropertyPage : Form, IPropertyPage 
  {
    #region Imported win32 API calls

    [DllImport("user32.dll")]
    public static extern int SetParent(IntPtr wnd, IntPtr newParentWnd);

    [DllImport("user32.dll", SetLastError = true)]
    static extern int SetWindowLong(IntPtr wnd, int index, UInt32 newLong);

    #endregion

    #region Overridables

    protected virtual void OnPageActivate(
        IntPtr wndParent, Rectangle Rect, bool modal) {
    }

    protected virtual void OnPageDeactivate() {
    }

    protected virtual void OnPageApply() {
    }

    #endregion

    #region IPropertyPage Members

    public void SetPageSite(IPropertyPageSite site) {
    }

    public void Help(ref String helpDir) {
    }

    public void Activate(IntPtr wndParent, ref Rectangle rect, bool modal) {
      // Make us a child of the given parent, and remove all window styles except WS_CHILD
      SetParent(Handle, wndParent);
      SetWindowLong(Handle, -16, 0x40000000);

      OnPageActivate(wndParent, rect, modal);  // inform derived class
    }

    public new void Deactivate() {
      OnPageDeactivate();
      Close();
    }

    public void GetPageInfo(ref PROPPAGEINFO info) {
      info.cb = (UInt32)Marshal.SizeOf(typeof(PROPPAGEINFO));
      info.size.Width = Width;
      info.size.Height = Height;
      info.szDocString = IntPtr.Zero;
      info.szHelpFile = IntPtr.Zero;

      // Caller frees this pointer
      info.szTitle = (Text.Length == 0) ? IntPtr.Zero : 
        Marshal.StringToCoTaskMemUni(Text);
    }

    public void SetObjects(UInt32 count, Object[] objs) {
      // Here we just take the first object, but in reality we should take all the
      // given objects and set the properties to them.
      dataObject = (count > 0) ? objs[0] : null;
    }

    public void Show(UInt32 cmdShow) {
      Visible = (cmdShow == 0) ? false : true;
    }

    public new void Move(ref Rectangle rect) {
      Location = rect.Location;
      Size = rect.Size;
    }

    public UInt32 IsPageDirty() {
      return 1; // for our purposes we always say settings have changed
    }

    public void Apply() {
      OnPageApply();  // inform derived class
    }

    public UInt32 TranslateAccelerator(ref Message msg) {
      // Default processing. If you want tabbing to work between the property frame's
      // controls and your controls, you need to add more stuff here.
      return (UInt32)((PreProcessMessage(ref msg) == false) ? 1 : 0);
    }

    #endregion

    public PropertyPage() {
      dataObject = null;

      // Override form defaults
      FormBorderStyle = FormBorderStyle.FixedSingle;
      ControlBox = false;
      MaximizeBox = false;
      MinimizeBox = false;
      ShowInTaskbar = false;
      StartPosition = FormStartPosition.Manual;
      WindowState = FormWindowState.Normal;
      Location = new Point(0);
    }

    // data
    protected Object dataObject;
  }

  #endregion
}
