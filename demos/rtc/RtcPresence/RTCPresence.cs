/*++

Copyright © Microsoft Corporation

Module Name:

    RTCPresence.cs

Abstract:

    The UI main window.
	
--*/

using System;
using System.Collections;
using System.Text;
using System.Text.RegularExpressions;
using System.Diagnostics;
using System.Runtime.InteropServices;
using System.Windows.Forms;
using System.ComponentModel;
using System.Drawing;
using RTCCore;


namespace Microsoft.Rtc.Sdk.Samples.RtcPresence
{
    sealed public class RTCPresence : System.Windows.Forms.Form, IRTCPresenceUI
    {
        #region Fields
        private System.Windows.Forms.MenuItem fileMenuItem;
        private System.Windows.Forms.MenuItem busyMenuItem;
        private System.Windows.Forms.MenuItem signasMenuItem;
        private System.Windows.Forms.MenuItem signoutMenuItem;
        private System.Windows.Forms.MenuItem mystatusMenuItem;
        private System.Windows.Forms.MenuItem onlineMenuItem;
        private System.Windows.Forms.MenuItem rightbackMenuItem;
        private System.Windows.Forms.MenuItem awayMenuItem;
        private System.Windows.Forms.MenuItem onthephoneMenuItem;
        private System.Windows.Forms.MenuItem outtolunchMenuItem;
        private System.Windows.Forms.MenuItem offlineMenuItem;
        private System.Windows.Forms.MenuItem closeMenuItem;
        private System.Windows.Forms.MenuItem toolsMenuItem;
        private System.Windows.Forms.MenuItem addcontactMenuItem;
        private System.Windows.Forms.MenuItem pollpresenceMenuItem;
        private System.Windows.Forms.TreeView buddyTree;
        private System.Windows.Forms.StatusBar mainStatusBar;
        private System.Windows.Forms.MainMenu mainMenu;
        internal System.Windows.Forms.ContextMenu contactContextMenu;
        private System.Windows.Forms.MenuItem deletecontactMenuItem;
        private System.Windows.Forms.MenuItem propertiesMenuItem;
        private System.Windows.Forms.StatusBarPanel mainStatusBarPanel;

        //the current local presence status
        private System.Windows.Forms.MenuItem currentMyStatusMenuItem;
        private RTCPresenceCore presenceCore;
        private Hashtable buddyHT;
        private PollDialog pollDialog;
        #endregion
        #region Constructor
        public RTCPresence()
        {
            //string filename = ".\\RTCPresence_trace.txt";

            Trace.Listeners.Add(new TextWriterTraceListener(Console.Out));
            //Trace.Listeners.Add(new TextWriterTraceListener(filename));
            Trace.AutoFlush = true;
            //
            // Required for Windows Form Designer support
            //
            InitializeComponent();

            InitializeComponent2();
            
            InitializeRTCPresence();
        }
        #endregion
        [STAThread]
        public static void Main(string[] args)
        {
            Application.Run(new RTCPresence());
        }
		
        protected override void Dispose( bool disposing )
        {
            if( disposing )
            {
            }
            base.Dispose( disposing );
        }

        #region Windows Form Designer generated code
        /// <summary>
        /// Required method for Designer support - do not modify
        /// the contents of this method with the code editor.
        /// </summary>
        private void InitializeComponent()
        {
            this.buddyTree = new System.Windows.Forms.TreeView();
            this.contactContextMenu = new System.Windows.Forms.ContextMenu();
            this.deletecontactMenuItem = new System.Windows.Forms.MenuItem();
            this.propertiesMenuItem = new System.Windows.Forms.MenuItem();
            this.mainStatusBar = new System.Windows.Forms.StatusBar();
            this.mainStatusBarPanel = new System.Windows.Forms.StatusBarPanel();
            this.fileMenuItem = new System.Windows.Forms.MenuItem();
            this.signasMenuItem = new System.Windows.Forms.MenuItem();
            this.signoutMenuItem = new System.Windows.Forms.MenuItem();
            this.mystatusMenuItem = new System.Windows.Forms.MenuItem();
            this.onlineMenuItem = new System.Windows.Forms.MenuItem();
            this.busyMenuItem = new System.Windows.Forms.MenuItem();
            this.rightbackMenuItem = new System.Windows.Forms.MenuItem();
            this.awayMenuItem = new System.Windows.Forms.MenuItem();
            this.onthephoneMenuItem = new System.Windows.Forms.MenuItem();
            this.outtolunchMenuItem = new System.Windows.Forms.MenuItem();
            this.offlineMenuItem = new System.Windows.Forms.MenuItem();
            this.closeMenuItem = new System.Windows.Forms.MenuItem();
            this.toolsMenuItem = new System.Windows.Forms.MenuItem();
            this.addcontactMenuItem = new System.Windows.Forms.MenuItem();
            this.pollpresenceMenuItem = new System.Windows.Forms.MenuItem();
            this.mainMenu = new System.Windows.Forms.MainMenu();
            ((System.ComponentModel.ISupportInitialize)(this.mainStatusBarPanel)).BeginInit();
            this.SuspendLayout();
            // 
            // buddyTree
            // 
            this.buddyTree.ContextMenu = this.contactContextMenu;
            this.buddyTree.Dock = System.Windows.Forms.DockStyle.Fill;
            this.buddyTree.FullRowSelect = true;
            this.buddyTree.ImageIndex = -1;
            this.buddyTree.Location = new System.Drawing.Point(0, 0);
            this.buddyTree.Name = "buddyTree";
            this.buddyTree.Nodes.AddRange(new System.Windows.Forms.TreeNode[] {
                                                                                  new System.Windows.Forms.TreeNode("Not Online"),
                                                                                  new System.Windows.Forms.TreeNode("Online")});
            this.buddyTree.SelectedImageIndex = -1;
            this.buddyTree.Size = new System.Drawing.Size(256, 345);
            this.buddyTree.Sorted = true;
            this.buddyTree.TabIndex = 0;
            // 
            // contactContextMenu
            // 
            this.contactContextMenu.MenuItems.AddRange(new System.Windows.Forms.MenuItem[] {
                                                                                               this.deletecontactMenuItem,
                                                                                               this.propertiesMenuItem});
            // 
            // deletecontactMenuItem
            // 
            this.deletecontactMenuItem.Index = 0;
            this.deletecontactMenuItem.Text = "R&emove Buddy";
            // 
            // propertiesMenuItem
            // 
            this.propertiesMenuItem.Index = 1;
            this.propertiesMenuItem.Text = "P&roperties";
            // 
            // mainStatusBar
            // 
            this.mainStatusBar.Location = new System.Drawing.Point(0, 321);
            this.mainStatusBar.Name = "mainStatusBar";
            this.mainStatusBar.Panels.AddRange(new System.Windows.Forms.StatusBarPanel[] {
                                                                                             this.mainStatusBarPanel});
            this.mainStatusBar.ShowPanels = true;
            this.mainStatusBar.Size = new System.Drawing.Size(256, 24);
            this.mainStatusBar.TabIndex = 1;
            // 
            // mainStatusBarPanel
            // 
            this.mainStatusBarPanel.AutoSize = System.Windows.Forms.StatusBarPanelAutoSize.Spring;
            this.mainStatusBarPanel.Text = "Logged off";
            this.mainStatusBarPanel.Width = 240;
            // 
            // fileMenuItem
            // 
            this.fileMenuItem.Index = 0;
            this.fileMenuItem.MenuItems.AddRange(new System.Windows.Forms.MenuItem[] {
                                                                                         this.signasMenuItem,
                                                                                         this.signoutMenuItem,
                                                                                         this.mystatusMenuItem,
                                                                                         this.closeMenuItem});
            this.fileMenuItem.Text = "&File";
            // 
            // signasMenuItem
            // 
            this.signasMenuItem.Index = 0;
            this.signasMenuItem.Text = "S&ign In As ...";
            // 
            // signoutMenuItem
            // 
            this.signoutMenuItem.Index = 1;
            this.signoutMenuItem.Text = "Sig&n Out";
            // 
            // mystatusMenuItem
            // 
            this.mystatusMenuItem.Index = 2;
            this.mystatusMenuItem.MenuItems.AddRange(new System.Windows.Forms.MenuItem[] {
                                                                                             this.onlineMenuItem,
                                                                                             this.busyMenuItem,
                                                                                             this.rightbackMenuItem,
                                                                                             this.awayMenuItem,
                                                                                             this.onthephoneMenuItem,
                                                                                             this.outtolunchMenuItem,
                                                                                             this.offlineMenuItem});
            this.mystatusMenuItem.Text = "&My Status";
            // 
            // onlineMenuItem
            // 
            this.onlineMenuItem.Index = 0;
            this.onlineMenuItem.RadioCheck = true;
            this.onlineMenuItem.Text = "&Online";
            // 
            // busyMenuItem
            // 
            this.busyMenuItem.Index = 1;
            this.busyMenuItem.RadioCheck = true;
            this.busyMenuItem.Text = "&Busy";
            // 
            // rightbackMenuItem
            // 
            this.rightbackMenuItem.Index = 2;
            this.rightbackMenuItem.RadioCheck = true;
            this.rightbackMenuItem.Text = "B&e Right Back";
            // 
            // awayMenuItem
            // 
            this.awayMenuItem.Index = 3;
            this.awayMenuItem.RadioCheck = true;
            this.awayMenuItem.Text = "&Away";
            // 
            // onthephoneMenuItem
            // 
            this.onthephoneMenuItem.Index = 4;
            this.onthephoneMenuItem.RadioCheck = true;
            this.onthephoneMenuItem.Text = "On The &Phone";
            // 
            // outtolunchMenuItem
            // 
            this.outtolunchMenuItem.Index = 5;
            this.outtolunchMenuItem.RadioCheck = true;
            this.outtolunchMenuItem.Text = "Out To &Lunch";
            // 
            // offlineMenuItem
            // 
            this.offlineMenuItem.Index = 6;
            this.offlineMenuItem.RadioCheck = true;
            this.offlineMenuItem.Text = "Appear O&ffline";
            // 
            // closeMenuItem
            // 
            this.closeMenuItem.Index = 3;
            this.closeMenuItem.Text = "&Exit";
            // 
            // toolsMenuItem
            // 
            this.toolsMenuItem.Index = 1;
            this.toolsMenuItem.MenuItems.AddRange(new System.Windows.Forms.MenuItem[] {
                                                                                          this.addcontactMenuItem,
                                                                                          this.pollpresenceMenuItem});
            this.toolsMenuItem.Text = "&Actions";
            // 
            // addcontactMenuItem
            // 
            this.addcontactMenuItem.Index = 0;
            this.addcontactMenuItem.Text = "&Add a Contact...";
            // 
            // pollpresenceMenuItem
            // 
            this.pollpresenceMenuItem.Index = 1;
            this.pollpresenceMenuItem.Text = "&Poll a Contact...";
            // 
            // mainMenu
            // 
            this.mainMenu.MenuItems.AddRange(new System.Windows.Forms.MenuItem[] {
                                                                                     this.fileMenuItem,
                                                                                     this.toolsMenuItem});
            // 
            // RTCPresence
            // 
            this.AutoScaleBaseSize = new System.Drawing.Size(5, 13);
            this.ClientSize = new System.Drawing.Size(256, 345);
            this.Controls.Add(this.mainStatusBar);
            this.Controls.Add(this.buddyTree);
            this.Menu = this.mainMenu;
            this.Name = "RTCPresence";
            this.Text = "RTC Presence";
            ((System.ComponentModel.ISupportInitialize)(this.mainStatusBarPanel)).EndInit();
            this.ResumeLayout(false);

        }
        #endregion
        private void InitializeComponent2()
        {

            this.signasMenuItem.Click += new System.EventHandler(this.signasMenuItem_Click);
            this.signoutMenuItem.Click += new System.EventHandler(this.signoutMenuItem_Click);

            this.onlineMenuItem.Click += new System.EventHandler(this.onlineMenuItem_Click);
            this.busyMenuItem.Click += new System.EventHandler(this.busyMenuItem_Click);
            this.rightbackMenuItem.Click += new System.EventHandler(this.rightbackMenuItem_Click);
            this.awayMenuItem.Click += new System.EventHandler(this.awayMenuItem_Click);
            this.onthephoneMenuItem.Click += new System.EventHandler(this.onthephoneMenuItem_Click);
            this.outtolunchMenuItem.Click += new System.EventHandler(this.outtolunchMenuItem_Click);
            this.offlineMenuItem.Click += new System.EventHandler(this.offlineMenuItem_Click);

            this.closeMenuItem.Click += new System.EventHandler(this.closeMenuItem_Click);

            this.addcontactMenuItem.Click += new System.EventHandler(this.addcontactMenuItem_Click);
            this.deletecontactMenuItem.Click += new System.EventHandler(this.deletecontactMenuItem_Click);
            this.propertiesMenuItem.Click += new System.EventHandler(this.propertiesMenuItem_Click);
            this.pollpresenceMenuItem.Click += new System.EventHandler(this.pollpresenceMenuItem_Click);

            this.contactContextMenu.Popup += new System.EventHandler(this.popupEventHandler);

            this.currentMyStatusMenuItem = this.onlineMenuItem;
            this.currentMyStatusMenuItem.Checked = true;

            this.buddyTree.Scrollable = true;
            this.ResizeRedraw = true;

            this.Show();
        }   

        void InitializeRTCPresence()
        {
            Trace.WriteLine("Entering RTCPresence.InitRTCPresence");

            this.buddyHT = new Hashtable();

            this.presenceCore = new RTCPresenceCore(this);
            
            AuthData authData = this.ShowLogonDialog();

            this.presenceCore.DoLogOn(authData);
        }

        void closeMenuItem_Click(object sender, System.EventArgs e)
        {    
            this.Close();
        }

        void signasMenuItem_Click(object sender, System.EventArgs e)
        {    
            Trace.WriteLine("Entering RTCPresence.signasMenuItem_Click");

            AuthData authData = ShowLogonDialog();

            this.presenceCore.DoLogOn(authData);
        }

        void signoutMenuItem_Click(object sender, System.EventArgs e)
        {    
            Trace.WriteLine("Entering RTCPresence.signoutMenuItem_Click");

            if (this.pollDialog != null)
            {
                this.pollDialog.Close();
                this.pollDialog = null;
            }
            this.presenceCore.DoLogOff();
        }

        void onlineMenuItem_Click(object sender, System.EventArgs e)
        {
            this.presenceCore.DoSetPresence(RTC_PRESENCE_STATUS.RTCXS_PRESENCE_ONLINE);
            this.currentMyStatusMenuItem.Checked = false;
            this.currentMyStatusMenuItem = (MenuItem) sender;
            this.currentMyStatusMenuItem.Checked = true;
        }

        void busyMenuItem_Click(object sender, System.EventArgs e)
        {
            this.presenceCore.DoSetPresence(RTC_PRESENCE_STATUS.RTCXS_PRESENCE_BUSY);
            this.currentMyStatusMenuItem.Checked = false;
            this.currentMyStatusMenuItem = (MenuItem) sender;
            this.currentMyStatusMenuItem.Checked = true;
        }

        void rightbackMenuItem_Click(object sender, System.EventArgs e)
        {
            this.presenceCore.DoSetPresence(RTC_PRESENCE_STATUS.RTCXS_PRESENCE_BE_RIGHT_BACK);
            this.currentMyStatusMenuItem.Checked = false;
            this.currentMyStatusMenuItem = (MenuItem) sender;
            this.currentMyStatusMenuItem.Checked = true;
        }

        void awayMenuItem_Click(object sender, System.EventArgs e)
        {
            this.presenceCore.DoSetPresence(RTC_PRESENCE_STATUS.RTCXS_PRESENCE_AWAY);
            this.currentMyStatusMenuItem.Checked = false;
            this.currentMyStatusMenuItem = (MenuItem) sender;
            this.currentMyStatusMenuItem.Checked = true;
        }

        void onthephoneMenuItem_Click(object sender, System.EventArgs e)
        {
            this.presenceCore.DoSetPresence(RTC_PRESENCE_STATUS.RTCXS_PRESENCE_ON_THE_PHONE);
            this.currentMyStatusMenuItem.Checked = false;
            this.currentMyStatusMenuItem = (MenuItem) sender;
            this.currentMyStatusMenuItem.Checked = true;
        }

        void outtolunchMenuItem_Click(object sender, System.EventArgs e)
        {
            this.presenceCore.DoSetPresence(RTC_PRESENCE_STATUS.RTCXS_PRESENCE_OUT_TO_LUNCH);
            this.currentMyStatusMenuItem.Checked = false;
            this.currentMyStatusMenuItem = (MenuItem) sender;
            this.currentMyStatusMenuItem.Checked = true;
        }

        void offlineMenuItem_Click(object sender, System.EventArgs e)
        {
            this.presenceCore.DoSetPresence(RTC_PRESENCE_STATUS.RTCXS_PRESENCE_OFFLINE);
            this.currentMyStatusMenuItem.Checked = false;
            this.currentMyStatusMenuItem = (MenuItem) sender;
            this.currentMyStatusMenuItem.Checked = true;
        }

        void addcontactMenuItem_Click(object sender, System.EventArgs e)
        {
            Trace.WriteLine("Entering RTCPresence.addcontactMenuItem_Click");

            string uri = null;

            AddressDialog dlg = new AddressDialog("Add Contact");

            if (dlg.ShowDialog() == DialogResult.OK ) 
            {
                uri = dlg.Uri;
                this.presenceCore.DoAddBuddy(uri);
            }
            else
            {
                Trace.WriteLine("Add Contact canceled");
            }
        }

        void pollpresenceMenuItem_Click(object sender, System.EventArgs e)
        {
            Trace.WriteLine("Entering RTCPresence.pollpresenceMenuItem_Click");;

            this.pollpresenceMenuItem.Enabled = false;
            pollDialog = new PollDialog("Poll Contact", this);
            pollDialog.Show(); 
        }

        void deletecontactMenuItem_Click(object sender, System.EventArgs e)
        {
            Trace.WriteLine("Entering RTCPresence.deletecontactMenuItem_Click");

            RTCTreeNode node = (RTCTreeNode) (this.buddyTree.SelectedNode);
            this.presenceCore.DoRemoveBuddy((IRTCBuddy) (node.Entity));
        }

        void propertiesMenuItem_Click(object sender, System.EventArgs e)
        {
            Trace.WriteLine("Entering RTCPresence.propertiesMenuItem_Click");

            RTCTreeNode node = (RTCTreeNode) (this.buddyTree.SelectedNode);
            IRTCBuddy2 buddy2 = (IRTCBuddy2) (node.Entity);

            this.ShowMessage(RTCHelp.GetBuddyProperties(buddy2), "Buddy Properties");
        }

        protected override void OnClosing(CancelEventArgs e)
        {
            Trace.WriteLine("Entering RTCPresence.OnClosing");

            base.OnClosing(e);

            if (this.pollDialog != null)
            {
                this.pollDialog.Close();
                this.pollDialog = null;
            }

            if (this.presenceCore.DoShutdown())
            {
                // The RTC client object is preparing to shutdown.
                e.Cancel = true;
                this.Hide();

            }
        }

        protected override void OnClosed(EventArgs e)
        {  
            Trace.WriteLine("Enter OnClosed");

            base.OnClosed(e);
        }

        void popupEventHandler(System.Object sender, System.EventArgs e)
        {
            Trace.WriteLine("Entering RTCPresence.popupEventHandler");

            this.contactContextMenu.MenuItems.Clear();

            if (this.contactContextMenu.SourceControl == this.buddyTree)
            {
                Trace.WriteLine(this.buddyTree.SelectedNode.Text);
                if (this.buddyTree.SelectedNode is RTCTreeNode)
                {
                    this.contactContextMenu.MenuItems.Add(this.deletecontactMenuItem);
                    this.contactContextMenu.MenuItems.Add(this.propertiesMenuItem);
                }
            }
        }

        AuthData ShowLogonDialog()
        {
            Trace.WriteLine("Entering RTCPresence.ShowLogonDialog");

            LogonDialog dlg = new LogonDialog();

            if (dlg.ShowDialog() == DialogResult.OK ) 
            {
                AuthData authData = new AuthData();

                authData.Uri = dlg.Uri;
                authData.Server = dlg.Server;
                authData.Transport = dlg.Transport;
                return authData;
            }

            return null;
        }

        void UpdatePollBuddy(IRTCBuddy2 buddy2)
        {
            Trace.WriteLine("Entering RTCPresence.UpdatePollBuddy");

            if (this.pollDialog == null)
            {
                return;
            }

            if (buddy2 == null)
            {
                Trace.WriteLine("NULL Buddy Object");
                return;
            }

            try
            {

                if (buddy2.PresentityURI != this.pollDialog.Uri
                    && buddy2.PresentityURI != ("sip:" + pollDialog.Uri))
                {
                    Trace.WriteLine("Not Current Poll URI");
                    return;
                }

                this.pollDialog.Properties = RTCHelp.GetBuddyProperties(buddy2);
            }
            catch (COMException)
            {
            }
        }

        public void DoPollBuddy(string uri)
        {
            Trace.WriteLine("Entering RTCPresence.DoPollBuddy");

            this.presenceCore.DoPollBuddy(uri);
        }

        public void CancelPollBuddy()
        {
            Trace.WriteLine("Entering RTCPresence.CancelPollBuddy");

            this.pollDialog = null;
            this.pollpresenceMenuItem.Enabled = true;
        }

        #region IRTCPresenceUI Members
        public void OnLoggedOff()
        {
            Trace.WriteLine("Entering RTCPresence.OnLoggedOff");

            this.mainStatusBarPanel.Text = "Logged off";

            this.signasMenuItem.Enabled = true;
            this.signoutMenuItem.Enabled = false;
            this.mystatusMenuItem.Enabled = false;

            this.addcontactMenuItem.Enabled = false;
            this.pollpresenceMenuItem.Enabled = false;
        }

        public void OnLoggingOff()
        {
            Trace.WriteLine("Entering RTCPresence.OnLoggingOff");

            this.mainStatusBarPanel.Text = this.presenceCore.GetUserURI() + "Logging off";

            this.signasMenuItem.Enabled = true;
            this.signoutMenuItem.Enabled = false;
            this.mystatusMenuItem.Enabled = false;

            this.addcontactMenuItem.Enabled = false;
            this.pollpresenceMenuItem.Enabled = false;
        }

        public void OnLoggingOn()
        {
            Trace.WriteLine("Entering RTCPresence.OnLoggingOn");
            Trace.WriteLine(this.presenceCore.GetUserURI() + " Logging on");

            this.mainStatusBarPanel.Text = this.presenceCore.GetUserURI() + "Logging on";

            this.signasMenuItem.Enabled = false;
            this.signoutMenuItem.Enabled = true;
            this.mystatusMenuItem.Enabled = false;

            this.addcontactMenuItem.Enabled = false;
            this.pollpresenceMenuItem.Enabled = false;
        }

        public void OnLoggedOn()
        {
            Trace.WriteLine("Entering RTCPresence.OnLoggedOn");
            Trace.WriteLine(this.presenceCore.GetUserURI() + " Logged on");

            this.mainStatusBarPanel.Text = this.presenceCore.GetUserURI() + " Logged on";

            this.signasMenuItem.Enabled = false;
            this.signoutMenuItem.Enabled = true;
            this.mystatusMenuItem.Enabled = true;

            this.addcontactMenuItem.Enabled = true;
            this.pollpresenceMenuItem.Enabled = true;
        }

        public void ClearBuddyList()
        {
            Trace.WriteLine("Entering RTCPresence.ClearBuddyList");

            buddyHT = null;
            buddyHT = new Hashtable();

            this.buddyTree.Nodes[0].Nodes.Clear();
            this.buddyTree.Nodes[1].Nodes.Clear();
        }

        public void RemoveBuddy(IRTCBuddy2 buddy2)
        {
            Trace.WriteLine("Entering RTCPresence.RemoveBuddy");

            if (buddyHT.ContainsKey(buddy2))
            {
                ((TreeNode) buddyHT[buddy2]).Remove();
                buddyHT.Remove(buddy2);
            }
        }

        public void UpdateBuddy(IRTCBuddy2 buddy2)
        {
            Trace.WriteLine("Entering RTCPresence.UpdateBuddy");

            this.UpdatePollBuddy(buddy2);

            if (buddy2.SubscriptionType == RTC_BUDDY_SUBSCRIPTION_TYPE.RTCBT_POLL)
            {
                return;
            }

            if (buddyHT.ContainsKey(buddy2))
            {
                ((TreeNode) buddyHT[buddy2]).Remove();
                buddyHT.Remove(buddy2);
            }

            string displayName = RTCHelp.BuildBuddyDisplayName(buddy2);
            if (displayName == null || displayName.Length == 0)
            {
                Trace.WriteLine("NULL Buddy Name");
                return;
            }

            Trace.WriteLine("Display name: " + displayName);

            RTCTreeNode buddyNode = new RTCTreeNode(displayName, buddy2);
            if (buddy2.Status == RTC_PRESENCE_STATUS.RTCXS_PRESENCE_OFFLINE)
            {
                buddyTree.Nodes[0].Nodes.Add(buddyNode);
                buddyTree.Nodes[0].Expand();
            }
            else
            {
                buddyTree.Nodes[1].Nodes.Add(buddyNode);
                buddyTree.Nodes[1].Expand();
            }
            buddyHT.Add(buddy2, buddyNode);

            ArrayList deviceDisplayNameList = RTCHelp.BuildDeviceDisplayNameList(buddy2);
            foreach (string deviceDisplayName in deviceDisplayNameList )
            {
                TreeNode deviceNode = new TreeNode(deviceDisplayName);
                buddyNode.Nodes.Add(deviceNode);
            }

            buddyNode.Expand();
        }

        public void CloseUI()
        {
            this.Close();
        }

        public AuthData ShowAuthDialog()
        {
            Trace.WriteLine("Entering RTCPresence.ShowAuthDialog");

            AuthDialog dlg = new AuthDialog();

            if (dlg.ShowDialog() == DialogResult.OK ) 
            {
                AuthData authData = new AuthData();

                authData.Uri = dlg.Uri;
                authData.Account = dlg.Account;
                authData.Password = dlg.Password;

                return authData;
            }

            return null;
        }

        public void ShowMessage(string message, string caption)
        {
            MessageBox.Show(message, caption);
        }

        public void ShowStatus(string status)
        {
            this.mainStatusBarPanel.Text = status;
        }
        #endregion
    }
}
