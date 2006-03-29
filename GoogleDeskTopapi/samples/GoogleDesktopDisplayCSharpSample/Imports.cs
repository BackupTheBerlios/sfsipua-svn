// Copyright 2005 Google Inc.
// All Rights Reserved.

using System;
using System.Drawing;
using System.Runtime.InteropServices;
using System.Runtime.Serialization;
using System.Windows.Forms;
using Microsoft.Win32;

namespace GoogleDesktopDisplayCSharpSample {
  #region Imported structures

  [ComVisible(false)]
  public struct PROPPAGEINFO {
    public UInt32 cb;
    public IntPtr szTitle;
    public Size size;
    public IntPtr szDocString;
    public IntPtr szHelpFile;
    public UInt32 dwHelpContext;
  };

  [ComVisible(false)]
  public struct CAUUID {
    UInt32 cElems;
    IntPtr pElems;

    public void SetPages(Guid[] thePages) {
      cElems = (UInt32)thePages.Length;
      pElems = Marshal.AllocCoTaskMem((int)(cElems * 16));

      int pos = 0;
      for (UInt32 i = 0; i < cElems; ++i) {
        Byte[] b = thePages[i].ToByteArray();
        for (int j = 0; j < 16; ++j, ++pos) {
          Marshal.WriteByte(pElems, pos, b[j]);
        }
      }
    }
  };

  #endregion

  #region Imported interfaces

  // IUnknown
  [ComImport]
  [Guid("00000000-0000-0000-C000-000000000046")]
  [InterfaceType(ComInterfaceType.InterfaceIsIUnknown)]
  public interface IUnknown {
    void QueryInterface([MarshalAs(UnmanagedType.IUnknown)] out Object obj);
    [PreserveSig]
    UInt32 AddRef();
    [PreserveSig]
    UInt32 Release();
  };

  // ISpecifyPropertyPages
  [ComImport]
  [Guid("B196B28B-BAB4-101A-B69C-00AA00341D07")]
  [InterfaceType(ComInterfaceType.InterfaceIsIUnknown)]
  public interface ISpecifyPropertyPages {
    void GetPages(ref CAUUID pages);
  };

  // IPropertyPageSite
  [ComImport]
  [Guid("B196B28C-BAB4-101A-B69C-00AA00341D07")]
  [InterfaceType(ComInterfaceType.InterfaceIsIUnknown)]
  public interface IPropertyPageSite {
    void OnStatusChange (UInt32 dwFlags);
    void GetLocaleID (out UInt32 LocaleID);
    void GetPageContainer ([MarshalAs(UnmanagedType.IUnknown)] out Object objs);
    [PreserveSig]
    UInt32 TranslateAccelerator(ref Message msg);
  };

  // IPropertyPage
  [ComImport]
  [Guid("B196B28D-BAB4-101A-B69C-00AA00341D07")]
  [InterfaceType(ComInterfaceType.InterfaceIsIUnknown)]
  public interface IPropertyPage {
    void SetPageSite(IPropertyPageSite site);
    void Activate(IntPtr wndParent, ref Rectangle rect, bool modal);
    void Deactivate();
    void GetPageInfo(ref PROPPAGEINFO info);
    void SetObjects(UInt32 count, [MarshalAs(UnmanagedType.LPArray,
      ArraySubType = UnmanagedType.IUnknown, SizeParamIndex=0)] Object[] objs);
    void Show(UInt32 cmdShow);
    void Move(ref Rectangle rect);
    [PreserveSig]
    UInt32 IsPageDirty();
    void Apply();
    void Help([MarshalAs(UnmanagedType.LPWStr)] ref String helpDir);
    [PreserveSig]
    UInt32 TranslateAccelerator(ref Message msg);
  };

  // IPersistStreamInit
  [ComImport]
  [Guid("7FD52380-4E07-101B-AE2D-08002B2EC713")]
  [InterfaceType(ComInterfaceType.InterfaceIsIUnknown)]
  public interface IPersistStreamInit {
    void GetClassID(out Guid classId);
    [PreserveSig]
    UInt32 IsDirty();
    void Load(UCOMIStream stm);
    void Save(UCOMIStream stm, bool clearDirty);
    ulong GetSizeMax();
    void InitNew();
  };

  // IObjectWithSite
  [ComImport]
  [Guid("FC4801A3-2BA9-11CF-A229-00AA003D7352")]
  [InterfaceType(ComInterfaceType.InterfaceIsIUnknown)]
  public interface IObjectWithSite {
    void SetSite([MarshalAs(UnmanagedType.IUnknown)] Object site);
    void GetPageContainer([MarshalAs(UnmanagedType.IUnknown)] out Object site);    
  };

  // IPropertyNotifySink
  [ComImport]
  [Guid("9BFBBC02-EFF1-101A-84ED-00AA00341D07")]
  [InterfaceType(ComInterfaceType.InterfaceIsIUnknown)]
  public interface IPropertyNotifySink {
    [PreserveSig]
    int OnChanged(int dispId);
    [PreserveSig]
    int OnRequestEdit(int dispId);
  }

  #endregion
}
