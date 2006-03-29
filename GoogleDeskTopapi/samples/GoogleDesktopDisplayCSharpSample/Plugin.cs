// Copyright 2005 Google Inc.
// All Rights Reserved.

using System;
using System.Drawing;
using System.Reflection;
using System.Threading;
using System.IO;
using System.Runtime.InteropServices;
using System.Windows.Forms;
using GoogleDesktopAPILib;
using GoogleDesktopDisplayLib;
using Microsoft.Win32;

namespace GoogleDesktopDisplayCSharpSample {
  /// <summary>
  /// This class is used as a wrapper to access the ImageConverter class and convert
  /// a bitmap to an IPicture
  /// </summary>
  public class ImageConverter: System.Windows.Forms.AxHost {
    public ImageConverter():base("59EE46BA-677D-4d20-BF10-8D8067CB8B33") {
    }
    public static stdole.IPicture ImageToIpicture(System.Drawing.Image image) {
      return (stdole.IPicture) ImageConverter.GetIPictureFromPicture(image);
    }
  }

  /// <summary>
  /// This is our plugin's property page where it shows the plugin's settings and
  /// allows the user to change them.
  /// </summary>
  [GuidAttribute("6DFA0DF1-A98D-4939-A2FB-127BA27F5649")] // CHANGE THIS in your plugin
  [ClassInterface(ClassInterfaceType.None)]
  public class SamplePluginPropertyPage : PropertyPage {
    private System.Windows.Forms.Label label1;
    private System.Windows.Forms.TextBox textBox1;
    private System.ComponentModel.Container components = null;

    public SamplePluginPropertyPage() {
      InitializeComponent();
    }

    protected override void Dispose(bool disposing) {
      if (disposing) {
        if (components != null) {
          components.Dispose();
        }
      }
      base.Dispose(disposing);
    }

    #region Component Designer generated code
    /// <summary> 
    /// Required method for Designer support - do not modify 
    /// the contents of this method with the code editor.
    /// </summary>
    private void InitializeComponent()
    {
      this.label1 = new System.Windows.Forms.Label();
      this.textBox1 = new System.Windows.Forms.TextBox();
      this.SuspendLayout();
      // 
      // label1
      // 
      this.label1.AutoSize = true;
      this.label1.Location = new System.Drawing.Point(24, 66);
      this.label1.Name = "label1";
      this.label1.Size = new System.Drawing.Size(68, 16);
      this.label1.TabIndex = 0;
      this.label1.Text = "Sample &Text";
      // 
      // textBox1
      // 
      this.textBox1.Location = new System.Drawing.Point(96, 64);
      this.textBox1.Name = "textBox1";
      this.textBox1.TabIndex = 1;
      this.textBox1.Text = "";

      // 
      // SamplePluginPropertyPage
      // 
      this.AutoScaleBaseSize = new System.Drawing.Size(5, 13);
      this.ClientSize = new System.Drawing.Size(270, 147);
      this.Controls.Add(this.label1);
      this.Controls.Add(this.textBox1);
      this.Name = "SamplePluginPropertyPage";
      this.Text = "Page 1";
      this.ResumeLayout(false);
    }
    #endregion

    #region PropertyPage handlers/overrides

    /// <summary>
    /// Called when user hits OK in the property page
    /// </summary>
    protected override void OnPageApply() {
      SamplePlugin ctl = dataObject as SamplePlugin;
      if (ctl != null) {
        // Set the new parameter values back to the plugin
        ctl.put_itemStart(Int32.Parse(textBox1.Text));
      }
      base.OnPageApply();
    }

    /// <summary>
    /// Called just before the property page is displayed
    /// </summary>
    protected override void OnPageActivate(System.IntPtr wndParent, Rectangle Rect, bool modal) {
      base.OnPageActivate(wndParent, Rect, modal);

      SamplePlugin ctl = dataObject as SamplePlugin;
      if (ctl != null) {
        // Get the parameter values from the plugin
        textBox1.Text = ctl.get_itemStart().ToString();
      }
    }

    #endregion
  }

  /// <summary>
  /// This class manages each content item shown in the plugin. Each content item
  /// holds the data displayed and handles the events such as user click, opening
  /// item details, deleting the item etc.
  /// </summary>
  public class SamplePluginContentItem : 
      GoogleDesktopDisplayContentItemHelperClass,
      IGoogleDesktopDisplayContentItemHandler {

    #region IGoogleDesktopDisplayContentItemHandler Members
 
    /// <summary>
    /// Called when the user opens the item by double-clicking it
    /// </summary>
    public new void OpenItem() {
      MessageBox.Show("Open: " + heading);
    }

    /// <summary>
    /// Called when the user tries to view the details view of this item. We can
    /// create an activex control which shows the details view content, or use the
    /// details view helper. If we dont want to show the details view return true.
    /// </summary>
    /// <param name="title">title for the details view</param>
    /// <param name="flags">flags specifying the features to include in the details view</param>
    /// <param name="detailsControl">store the details view activex control here</param>
    /// <returns>true if details view should be cancelled, false if not</returns>
    public new bool OnDetailsView(out string title,
        out GoogleDesktopDisplayDetailsViewFlags flags, out object detailsControl) {
      // Here we can create any ActiveX control for displaying the details, and 
      // return it via the detailsControl parameter.  We choose the 
      // 'GoogleDesktopDisplayDetailsViewHelper' control that will give us a 
      // UI that's inline with how the sidebar looks.
      GoogleDesktopDisplayDetailsViewHelperClass details = new
        GoogleDesktopDisplayDetailsViewHelperClass();

      // set the details control's content from our own data
      String text = "Some sample text\r\n\r\nwithout formatting\r\nhttp://www.google.com";
      details.SetContent(source, time_created, text, false, layout);

      detailsControl = details;
      title = heading;
      flags = 
        GoogleDesktopDisplayDetailsViewFlags.GDD_DETAILS_VIEW_FLAG_TOOLBAR_OPEN |
        GoogleDesktopDisplayDetailsViewFlags.GDD_DETAILS_VIEW_FLAG_NEGATIVE_FEEDBACK;

      return false; // return false to show details view, true to cancel it.
    }

    /// <summary>
    /// Called when the user closes the item's details view using any of the special
    /// buttons or just by clicking the close button
    /// </summary>
    /// <param name="flags"></param>
    public new void ProcessDetailsViewFeedback(GoogleDesktopDisplayDetailsViewFlags flags) {
      if ((flags & 
          GoogleDesktopDisplayDetailsViewFlags.GDD_DETAILS_VIEW_FLAG_TOOLBAR_OPEN) != 0) {
        OpenItem();
        return;
      }
      if ((flags & 
          GoogleDesktopDisplayDetailsViewFlags.GDD_DETAILS_VIEW_FLAG_NEGATIVE_FEEDBACK) != 0) {
        MessageBox.Show("Not interesting: " + heading + "Doing default processing");
      }
      // throw this exception to let the default processing happen for all other
      // details view commands
      throw new NotImplementedException();  
    }

    #region Unhandled Members

    // We are not interested in the following members so always throw a not-implemented
    // exception to let default processing happen.
    public new void ToggleItemPinnedState() {
      throw new NotImplementedException();
    }

    public new bool OnRemoveItem() {
      // return true if you don't want the item to be removed/you manually handled the command
      // return false to let the default happen, which will remove the item automatically.
      return false; 
    }

    public new void DrawItem(GoogleDesktopDisplayTarget target,
        Int32 dc,
        ref GoogleDesktopDisplayLib.tagRECT bounds) {
      throw new NotImplementedException();
      // Comment above and uncomment the code below to do custom drawing on your item.
      /*
      Graphics g = Graphics.FromHdc((IntPtr)dc);
      g.TextRenderingHint = System.Drawing.Text.TextRenderingHint.ClearTypeGridFit;
      Rectangle rc = new Rectangle(bounds.left, bounds.top,
        bounds.right - bounds.left, bounds.bottom - bounds.top);
      Font font = new Font("Tahoma", 8);
      Brush brush = Brushes.Black;
      g.DrawString(heading, font, brush, rc);
      */
    }

    public new int GetHeight(GoogleDesktopDisplayTarget displayTarget,
        Int32 dc, int width) {
      throw new NotImplementedException();
    }

    public new void GetIsTooltipRequired(GoogleDesktopDisplayTarget target,
        Int32 dc,
        ref GoogleDesktopDisplayLib.tagRECT bounds, out bool isRequired) {
      throw new NotImplementedException();
    }

    #endregion

    #endregion
  }

  /// <summary>
  /// This is the actual plugin, which uses the helper object to do all the dirty work
  /// and only implements stuff related to creating/fetching the content to display
  /// in the plugin's area.
  /// </summary>
  [GuidAttribute("982D6785-E948-3E35-BED0-88D9AC23853F")] // CHANGE THIS in your plugin
  public class SamplePlugin : GoogleDesktopDisplayPluginHelperClass,
      IGoogleDesktopDisplayPluginHandler,
      ISpecifyPropertyPages,
      IObjectWithSite,
      IPersistStreamInit {
    #region Variables and Strings 

    static String controlGuid = 
      "{982D6785-E948-3E35-BED0-88D9AC23853F}"; // CHANGE THIS in your plugin
    static String pluginName = "Sample C# Display Plugin";
    static String pluginDesc = "<Description>";

    // The about dialog string consists of 3 lines, each shown in a different place
    // in the about dialog. Have a look at the about dialog of existing plugins for
    // an idea of how this works.
    static String aboutStr = "GoogleDesktop Sample C# Display Plugin\n" +
      "© 2005 Google\n" +
      "Shows how to create a GoogleDesktop Display plugin in C# and\n" +
      "  + add content\n" +
      "  + load/save settings\n" +
      "  + perform actions based on user interaction and load/save data.\n\n" +
      "Web: http://desktop.google.com/plugins.html";

    int totalItemsCreatedCount, itemRotate, itemStart;
    GoogleDesktopDisplayContentItemLayout contentLayout;
    bool firstTime, showImages, isDirty;
    stdole.IPicture contentIcon1, contentIcon2;
    IGoogleDesktopDisplaySite displaySite;
    System.Windows.Forms.Timer timer;

    const int itemRotateMax = 6;
    const int itemRotateTimeMs = 4000;
    const int dataVersion = 1;

    #endregion

    #region Plugin

    public SamplePlugin() {
      itemStart = 0;
    }

    void Initialize() {
      // initialize variables
      totalItemsCreatedCount = 0;
      contentLayout = GoogleDesktopDisplayContentItemLayout.GDD_CONTENT_ITEM_LAYOUT_EMAIL;
      totalItemsCreatedCount = 0;
      showImages = true;
      isDirty = false;

      // Load our icons
      contentIcon1 = ImageConverter.ImageToIpicture(new Icon(
        Assembly.GetExecutingAssembly().GetManifestResourceStream(
        "GoogleDesktopDisplayCSharpSample.ico1.ico")).ToBitmap());
      contentIcon2 = ImageConverter.ImageToIpicture(new Icon(
        Assembly.GetExecutingAssembly().GetManifestResourceStream(
        "GoogleDesktopDisplayCSharpSample.ico2.ico")).ToBitmap());

      Stream stream = Assembly.GetExecutingAssembly().GetManifestResourceStream(
        "GoogleDesktopDisplayCSharpSample.plugin.ico");
      Bitmap smallImage = new Icon(stream, 16, 16).ToBitmap();
      stream.Seek(0, System.IO.SeekOrigin.Begin);
      Bitmap largeImage = new Icon(stream, 32, 32).ToBitmap();

      // Set plugin information
      IGoogleDesktopDisplayPluginHelper helper =  (IGoogleDesktopDisplayPluginHelper)this;
      helper.about_text = aboutStr;
      helper.SetIcons(ImageConverter.ImageToIpicture(smallImage),
        ImageConverter.ImageToIpicture(largeImage));
      UpdateTitle();
    }

    /// <summary>
    /// check what is the current display state; if we are minimized show the number
    /// of items as well in the title (as an example showing how to use the title
    /// for showing content when minimized)
    /// </summary>
    void UpdateTitle() {
      title = pluginName;

      // displaySite will be null until plugin is fully initialized.
      if (displaySite != null && displaySite.display_state == 
          GoogleDesktopDisplayTileDisplayState.GDD_TILE_DISPLAY_STATE_MINIMIZED) {
        title = "(" + totalItemsCreatedCount + ") " + pluginName;
      }
    }

    void ClearAndAddFreshItems() {
      // reset everything and start fresh with new layout
      firstTime = true;
      itemRotate = 0;

      IGoogleDesktopDisplayPluginHelper helper = (IGoogleDesktopDisplayPluginHelper)this;

      // we are not going to show any details if we are in the NoWrap layout, instead
      // we use the 'pinning' feature where user can pin items to stay on top of the
      // content list
      GoogleDesktopDisplayContentFlags contentFlags = 
        GoogleDesktopDisplayContentFlags.GDD_CONTENT_FLAG_HAVE_DETAILS;
      if (contentLayout == 
          GoogleDesktopDisplayContentItemLayout.GDD_CONTENT_ITEM_LAYOUT_NOWRAP_ITEMS) {
        contentFlags = GoogleDesktopDisplayContentFlags.GDD_CONTENT_FLAG_PINNABLE;
      }
      helper.SetFlags(GoogleDesktopDisplayPluginFlags.GDD_PLUGIN_FLAG_NONE, contentFlags);

      // since we are going to show items with a new layout, remove all old ones
      helper.RemoveAllContentItems();
      ChangeItems(false);
    }

    void StartShowingContent() {
      ClearAndAddFreshItems(); // this will set the layout and start showing content

      timer = new System.Windows.Forms.Timer();
      timer.Tick += new EventHandler(OnTimer);
      timer.Interval = itemRotateTimeMs;
      timer.Start();
    }

    void StopShowingContent() {
        timer.Stop();
        timer.Dispose();
    }

    void OnTimer(Object myObject, EventArgs eventArgs) {
      // You can add new items asynchronously like shown below
      ChangeItems(false);
      
      // If you want to update the data currently displayed in the plugin, get the
      // items as shown here and update their properties.
      /*
      IGoogleDesktopDisplayPluginHelper helper = (IGoogleDesktopDisplayPluginHelper)this;
      Object[] items = (Object[])helper.content_items;
      ((SamplePluginContentItem)items[0]).snippet = DateTime.UtcNow.ToString();
      */
    }

    /// <summary>
    /// the property page calls this when user sets a new value for the property
    /// </summary>
    /// <param name="val">new value for the parameter</param>
    public void put_itemStart(Int32 val) {
      itemStart = val;
      isDirty = true;
      ClearAndAddFreshItems();
    }

    public Int32 get_itemStart() {
      return itemStart;
    }

    /// <summary>
    /// Create content items and add to the display
    /// </summary>
    /// <param name="refreshOnly">true if the item counter should not be
    /// incremented, false if it should be incremented
    /// </param>
    void ChangeItems(bool refreshOnly) {
      // add content to display.
      int maxItems = (firstTime) ? 1 : 1;
      firstTime = false;

      IGoogleDesktopDisplayPluginHelper pluginHelper = 
        (IGoogleDesktopDisplayPluginHelper)this;

      // Here we show absolute time for items in email layout
      GoogleDesktopDisplayContentItemFlags itemFlags = 
        GoogleDesktopDisplayContentItemFlags.GDD_CONTENT_ITEM_FLAG_NONE;
      if (contentLayout == 
          GoogleDesktopDisplayContentItemLayout.GDD_CONTENT_ITEM_LAYOUT_EMAIL) {
        itemFlags = 
          GoogleDesktopDisplayContentItemFlags.GDD_CONTENT_ITEM_FLAG_TIME_ABSOLUTE;
      }

      for (int j = 0, i = itemStart + itemRotate; j < maxItems; ++j, ++i) {
        // create a new item
        SamplePluginContentItem curItem = new SamplePluginContentItem();
        IGoogleDesktopDisplayContentItemHelper itemHelper = 
          (IGoogleDesktopDisplayContentItemHelper)curItem;

        // the strings to display, different format for odd and even numbered items
        String heading = "Line " + i + " line " + i + " line " + i;
        String source = "Google";
        String snippet = 
          "Google doodles with the idea to create noodles to sell on Froogle.";

        stdole.IPicture image = null;
        if (showImages) {
          // use different images for odd and even numbered items
        bool oddNumberedItem = ((i % 2) == 1);
          image = (oddNumberedItem) ? contentIcon1 : contentIcon2;
        }

        DateTime timeCreated = DateTime.UtcNow;

        // Show the item in the sidebar and optionally in the notifier window 
        // if the sidebar was auto-hidden.
        GoogleDesktopContentItemDisplayOptions options = 
            GoogleDesktopContentItemDisplayOptions.GDD_ITEM_DISPLAY_IN_SIDEBAR | 
            GoogleDesktopContentItemDisplayOptions.GDD_ITEM_DISPLAY_AS_NOTIFICATION_IF_SIDEBAR_HIDDEN;
        pluginHelper.AddContentItem(curItem, options);

        // do the actual setting of properties
        itemHelper.heading = heading;
        itemHelper.tooltip = heading;
        itemHelper.source = source;
        itemHelper.time_created = timeCreated;
        itemHelper.snippet = snippet;
        itemHelper.flags = itemFlags;
        itemHelper.image = image;
        itemHelper.layout = contentLayout;

      }

      if (!refreshOnly) {
        // increment item counter since we are asked to add new content
        itemRotate = (itemRotate + maxItems) % itemRotateMax;
        totalItemsCreatedCount += maxItems;
      }

      // if we are in minimized mode, update the title with latest info.
      // displaySite will be null until plugin is fully initialized.
      if (displaySite != null && displaySite.display_state == 
          GoogleDesktopDisplayTileDisplayState.GDD_TILE_DISPLAY_STATE_MINIMIZED) {
        UpdateTitle();
      }
    }

    #endregion
  
    #region Registration functions

    /// <summary>
    /// Called when the plugin is registered with the system. We add a few registry
    /// keys and register with GoogleDesktop as a plugin.
    /// </summary>
    /// <param name="t"></param>
    [ComRegisterFunctionAttribute]
    static void RegisterFunction(Type t) {
      try {
        // Set the 'MiscStatus' value in registry to a valid value
        string keyName = @"CLSID\" + t.GUID.ToString("B");
        using (RegistryKey key = Registry.ClassesRoot.OpenSubKey(keyName, true)) {
          key.CreateSubKey("Control").Close();
          using (RegistryKey subkey = key.CreateSubKey("MiscStatus")) {
            subkey.SetValue("", "131457");
          }
          key.CreateSubKey("Control").Close();
          key.SetValue("",pluginName);
          using (RegistryKey subkey = key.CreateSubKey("Description")) {
            subkey.SetValue("", pluginDesc);
          }
        }

        // Create the registrar object
        GoogleDesktopRegistrarClass registrar = new GoogleDesktopRegistrarClass();

        // Start component registration by specifying our attributes
        object[] descriptions = {
          "Title", pluginName,
          "Description", pluginName,
          "Icon", ""
        };
        registrar.StartComponentRegistration(controlGuid, descriptions);

        // A single component can register for multiple plugins with Google Desktop.
        // Here we register a single display plugin.
        IGoogleDesktopRegisterDisplayPlugin displayRegistration = 
          (IGoogleDesktopRegisterDisplayPlugin)
          registrar.GetRegistrationInterface("GoogleDesktop.DisplayPluginRegistration");

        displayRegistration.RegisterPlugin(controlGuid, false);

        // Done with component registration.
        registrar.FinishComponentRegistration();
      } catch (Exception e) {
        MessageBox.Show("Exception thrown during registration. Description=" + e.Message);
      }
    }
   
    /// <summary>
    /// Called when the plugin is unregistered. We unregister our plugin with 
    /// GoogleDesktop.
    /// </summary>
    /// <param name="t"></param>
    [ComUnregisterFunctionAttribute]
    static void UnregisterFunction(Type t) {
      try {
        // Create the registrar object
        GoogleDesktopRegistrarClass registrar = new GoogleDesktopRegistrarClass();

        // Unregister ourselves
        registrar.UnregisterComponent(controlGuid);
      } catch (Exception e) {
        MessageBox.Show("Exception thrown during registration. Description=" + e.Message);
      }
    }

    #endregion
  
    #region IGoogleDesktopDisplayPluginHandler Members

    /// <summary>
    /// Called when the user selects any of the plugin's menu options/commands
    /// </summary>
    /// <param name="command">The command id to execute</param>
    public void OnCommand(GoogleDesktopDisplayPluginCommand command) {
      if (command == GoogleDesktopDisplayPluginCommand.GDD_CMD_ABOUT_DLG) {
        // always throw this exception when you dont intend to override the default behavior
        // and you want the plugin helper to do it's usual stuff.
        throw new NotImplementedException();
      }

      MessageBox.Show("Sidebar sent command " + command);
    }

    /// <summary>
    /// Called when the plugin's display state changes
    /// </summary>
    /// <param name="displayState">The new display state</param>
    public void OnDisplayStateChange(GoogleDesktopDisplayTileDisplayState displayState) {
      if (displayState == GoogleDesktopDisplayTileDisplayState.GDD_TILE_DISPLAY_STATE_MINIMIZED || 
          displayState == GoogleDesktopDisplayTileDisplayState.GDD_TILE_DISPLAY_STATE_RESTORED) {
        // switching between minimized and normal mode, so update the title
        UpdateTitle();
      }
    }

    #endregion

    #region ISpecifyPropertyPages Members

    /// <summary>
    /// Return an array of Guids representing our plugin's property pages
    /// </summary>
    /// <param name="pPages">store the Guids and return here</param>
    public void GetPages(ref CAUUID pPages) {
      Guid[] g = new Guid[1];
      g[0] = typeof(SamplePluginPropertyPage).GUID;
      pPages.SetPages(g);
    }

    #endregion

    #region IPersistStreamInit Members

    public void GetClassID(out Guid classId) {
      classId = new Guid ();  // not used now
    }

    public ulong GetSizeMax() {
      return 0; // not used now
    }

    public UInt32 IsDirty() {
      return (UInt32)(isDirty ? 1 : 0);
    }

    /// <summary>
    /// Called to initialize with default settings
    /// </summary>
    public void InitNew() {
      Initialize();
    }

    /// <summary>
    /// Called to read the settings data from the given stream.
    /// </summary>
    /// <param name="stm">stream from which the settings can be read</param>
    public void Load(UCOMIStream stm) {
      const int maxDataLen = 1000;  // read a large enough number of bytes for us.
      byte[] data = new byte[maxDataLen];
      stm.Read(data, data.Length, IntPtr.Zero); 

      MemoryStream memStream = new MemoryStream(data);
      BinaryReader binReader = new BinaryReader(memStream);

      int version = binReader.ReadInt32();
      if (version != dataVersion) {
        MessageBox.Show("Invalid data version, using default values");
      } else {
        // valid version, continue reading data.
        itemStart = binReader.ReadInt32();
      }

      Initialize();
    }

    /// <summary>
    /// Called to save the settings data to the given stream.
    /// </summary>
    /// <param name="stm">stream to save the settings to</param>
    /// <param name="clearDirty">if true, clear our 'dirty' flag</param>
    public void Save(UCOMIStream stm, bool clearDirty) {
      MemoryStream memStream = new MemoryStream();
      BinaryWriter binWriter = new BinaryWriter(memStream);

      // first our version
      binWriter.Write(dataVersion);
      // then the data.
      binWriter.Write(itemStart);
      // cleanup
      binWriter.Flush();

      // write to actual output stream
      byte[] data = memStream.ToArray();
      stm.Write(data, data.Length, IntPtr.Zero);

      if (clearDirty)
        isDirty = false;
    }

    #endregion
  
    #region IObjectWithSite Members

    /// <summary>
    /// Set/reset the object's 'site' which is used to get/set various plugin 
    /// properties later on
    /// </summary>
    /// <param name="site">The site object, null when the site is reset</param>
    public void SetSite(Object site) {
      displaySite = (IGoogleDesktopDisplaySite)site;

      if (displaySite != null) {
        // start adding data since we are completely initialized
        StartShowingContent();
      } else {
        // no more adding data as we are in uninitialized state
        StopShowingContent();
      }
    }

    public void GetPageContainer(out Object site) {
      site = displaySite;
    }

    #endregion
  }
}
