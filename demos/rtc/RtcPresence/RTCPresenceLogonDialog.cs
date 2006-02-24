/*++

Copyright © Microsoft Corporation

Module Name:

    RTCPresenceLogonDialog.cs

Abstract:
	
--*/

using System;
using System.Drawing;
using System.Collections;
using System.ComponentModel;
using System.Windows.Forms;
using Microsoft.Win32;

namespace Microsoft.Rtc.Sdk.Samples.RtcPresence
{
	/// <summary>
	/// Summary description for LogonDialog.
	/// </summary>
	public class LogonDialog : System.Windows.Forms.Form
	{
        private System.Windows.Forms.Button okButton;
        private System.Windows.Forms.Button cancelButton;
        private System.Windows.Forms.TextBox uriBox;
        private System.Windows.Forms.Label uriLabel;
        private System.Windows.Forms.Label serverLabel;
        private System.Windows.Forms.Label transportLabel;
        private System.Windows.Forms.TextBox serverBox;
        private System.Windows.Forms.ComboBox transportBox;
		/// <summary>
		/// Required designer variable.
		/// </summary>
		private System.ComponentModel.Container components = null;

        public string Uri
        {
            get {return uriBox.Text;}
        }

        public string Server
        {
            get {return serverBox.Text;}
        }

        public string Transport
        {
            get {return transportBox.Text;}
        }

        public LogonDialog()
		{
			//
			// Required for Windows Form Designer support
			//
			InitializeComponent();

            RegistryKey rk = Registry.CurrentUser.CreateSubKey("Software\\Microsoft\\rtcpresence");

            // Get the data from a specified item in the key.
            this.uriBox.Text = (String)rk.GetValue("uri", "sip uri");
            this.serverBox.Text = (String)rk.GetValue("server", "sip server");
            this.transportBox.Text = (String)rk.GetValue("transport", "TCP");

            okButton.Click +=new EventHandler(OKButton_Click);
            cancelButton.Click +=new EventHandler(CancelButton_Click);
		}

		/// <summary>
		/// Clean up any resources being used.
		/// </summary>
		protected override void Dispose( bool disposing )
		{
			if( disposing )
			{
				if(components != null)
				{
					components.Dispose();
				}
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
            this.uriBox = new System.Windows.Forms.TextBox();
            this.okButton = new System.Windows.Forms.Button();
            this.cancelButton = new System.Windows.Forms.Button();
            this.uriLabel = new System.Windows.Forms.Label();
            this.serverLabel = new System.Windows.Forms.Label();
            this.transportLabel = new System.Windows.Forms.Label();
            this.serverBox = new System.Windows.Forms.TextBox();
            this.transportBox = new System.Windows.Forms.ComboBox();
            this.SuspendLayout();
            // 
            // uriBox
            // 
            this.uriBox.Location = new System.Drawing.Point(72, 8);
            this.uriBox.Name = "uriBox";
            this.uriBox.Size = new System.Drawing.Size(304, 20);
            this.uriBox.TabIndex = 0;
            this.uriBox.Text = "";
            // 
            // okButton
            // 
            this.okButton.DialogResult = System.Windows.Forms.DialogResult.OK;
            this.okButton.Location = new System.Drawing.Point(224, 104);
            this.okButton.Name = "okButton";
            this.okButton.Size = new System.Drawing.Size(64, 23);
            this.okButton.TabIndex = 3;
            this.okButton.Text = "OK";
            // 
            // cancelButton
            // 
            this.cancelButton.DialogResult = System.Windows.Forms.DialogResult.Cancel;
            this.cancelButton.Location = new System.Drawing.Point(312, 104);
            this.cancelButton.Name = "cancelButton";
            this.cancelButton.Size = new System.Drawing.Size(64, 23);
            this.cancelButton.TabIndex = 4;
            this.cancelButton.Text = "Cancel";
            // 
            // uriLabel
            // 
            this.uriLabel.Location = new System.Drawing.Point(8, 8);
            this.uriLabel.Name = "uriLabel";
            this.uriLabel.Size = new System.Drawing.Size(64, 23);
            this.uriLabel.TabIndex = 3;
            this.uriLabel.Text = "User URI";
            // 
            // serverLabel
            // 
            this.serverLabel.Location = new System.Drawing.Point(8, 40);
            this.serverLabel.Name = "serverLabel";
            this.serverLabel.Size = new System.Drawing.Size(40, 23);
            this.serverLabel.TabIndex = 4;
            this.serverLabel.Text = "Server";
            // 
            // transportLabel
            // 
            this.transportLabel.Location = new System.Drawing.Point(8, 72);
            this.transportLabel.Name = "transportLabel";
            this.transportLabel.Size = new System.Drawing.Size(56, 23);
            this.transportLabel.TabIndex = 5;
            this.transportLabel.Text = "Transport";
            // 
            // serverBox
            // 
            this.serverBox.Location = new System.Drawing.Point(72, 40);
            this.serverBox.Name = "serverBox";
            this.serverBox.Size = new System.Drawing.Size(304, 20);
            this.serverBox.TabIndex = 1;
            this.serverBox.Text = "";
            // 
            // transportBox
            // 
            this.transportBox.AllowDrop = true;
            this.transportBox.Items.AddRange(new object[] {
                                                              "TLS",
                                                              "TCP",
                                                              "UDP"});
            this.transportBox.Location = new System.Drawing.Point(72, 72);
            this.transportBox.Name = "transportBox";
            this.transportBox.Size = new System.Drawing.Size(304, 21);
            this.transportBox.TabIndex = 2;
            this.transportBox.Text = "TLS";
            // 
            // LogonDialog
            // 
            this.AcceptButton = this.okButton;
            this.AutoScaleBaseSize = new System.Drawing.Size(5, 13);
            this.CancelButton = this.cancelButton;
            this.ClientSize = new System.Drawing.Size(386, 135);
            this.ControlBox = false;
            this.Controls.Add(this.transportBox);
            this.Controls.Add(this.serverBox);
            this.Controls.Add(this.transportLabel);
            this.Controls.Add(this.serverLabel);
            this.Controls.Add(this.uriLabel);
            this.Controls.Add(this.cancelButton);
            this.Controls.Add(this.okButton);
            this.Controls.Add(this.uriBox);
            this.FormBorderStyle = System.Windows.Forms.FormBorderStyle.FixedDialog;
            this.MaximizeBox = false;
            this.MinimizeBox = false;
            this.Name = "LogonDialog";
            this.Text = "Logon Dialog";
            this.ResumeLayout(false);

        }
		#endregion

        private void OKButton_Click(object sender, System.EventArgs e)
        {
            // Create or open a key
            RegistryKey rk = Registry.CurrentUser.CreateSubKey("Software\\Microsoft\\rtcpresence");

            rk.SetValue("uri", this.Uri);
            rk.SetValue("server", this.Server);
            rk.SetValue("transport", this.Transport);
            this.Close();
        }

        private void CancelButton_Click(object sender, System.EventArgs e)
        {
            this.Close();
        }
	}
}
