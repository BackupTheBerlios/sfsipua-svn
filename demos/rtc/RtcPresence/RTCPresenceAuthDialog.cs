/*++

Copyright © Microsoft Corporation

Module Name:

    RTCPresenceAuthDialog.cs

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
	/// Summary description for AuthDialog.
	/// </summary>
	public class AuthDialog : System.Windows.Forms.Form
	{
        private System.Windows.Forms.Button okButton;
        private System.Windows.Forms.Button cancelButton;
        private System.Windows.Forms.TextBox uriBox;
        private System.Windows.Forms.Label uriLabel;
        private System.Windows.Forms.Label accountLabel;
        private System.Windows.Forms.TextBox accountBox;
        private System.Windows.Forms.Label passwordLabel;
        private System.Windows.Forms.TextBox passwordBox;
		/// <summary>
		/// Required designer variable.
		/// </summary>
		private System.ComponentModel.Container components = null;

        public string Uri
        {
            get {return uriBox.Text;}
        }

        public string Account
        {
            get {return accountBox.Text;}
        }

        public string Password
        {
            get {return passwordBox.Text;}
        }

        public AuthDialog()
		{
			//
			// Required for Windows Form Designer support
			//
			InitializeComponent();

            // Create or open a key
            RegistryKey rk = Registry.CurrentUser.CreateSubKey("Software\\Microsoft\\rtcpresence");

            // Get the data from a specified item in the key.
            this.uriBox.Text = (String)rk.GetValue("uri", "sip uri");
            this.accountBox.Text = (String)rk.GetValue("account", "sip account");

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
            this.accountLabel = new System.Windows.Forms.Label();
            this.accountBox = new System.Windows.Forms.TextBox();
            this.passwordLabel = new System.Windows.Forms.Label();
            this.passwordBox = new System.Windows.Forms.TextBox();
            this.SuspendLayout();
            // 
            // uriBox
            // 
            this.uriBox.Location = new System.Drawing.Point(72, 8);
            this.uriBox.Name = "uriBox";
            this.uriBox.Size = new System.Drawing.Size(248, 20);
            this.uriBox.TabIndex = 0;
            this.uriBox.Text = string.Empty;
            // 
            // okButton
            // 
            this.okButton.DialogResult = System.Windows.Forms.DialogResult.OK;
            this.okButton.Location = new System.Drawing.Point(184, 96);
            this.okButton.Name = "okButton";
            this.okButton.Size = new System.Drawing.Size(64, 23);
            this.okButton.TabIndex = 3;
            this.okButton.Text = "OK";
            // 
            // cancelButton
            // 
            this.cancelButton.DialogResult = System.Windows.Forms.DialogResult.Cancel;
            this.cancelButton.Location = new System.Drawing.Point(264, 96);
            this.cancelButton.Name = "cancelButton";
            this.cancelButton.Size = new System.Drawing.Size(56, 23);
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
            // accountLabel
            // 
            this.accountLabel.Location = new System.Drawing.Point(8, 40);
            this.accountLabel.Name = "accountLabel";
            this.accountLabel.Size = new System.Drawing.Size(64, 23);
            this.accountLabel.TabIndex = 4;
            this.accountLabel.Text = "User Name";
            // 
            // accountBox
            // 
            this.accountBox.Location = new System.Drawing.Point(72, 40);
            this.accountBox.Name = "accountBox";
            this.accountBox.Size = new System.Drawing.Size(248, 20);
            this.accountBox.TabIndex = 1;
            this.accountBox.Text = string.Empty;
            // 
            // passwordLabel
            // 
            this.passwordLabel.Location = new System.Drawing.Point(8, 72);
            this.passwordLabel.Name = "passwordLabel";
            this.passwordLabel.Size = new System.Drawing.Size(64, 23);
            this.passwordLabel.TabIndex = 7;
            this.passwordLabel.Text = "Password";
            // 
            // passwordBox
            // 
            this.passwordBox.AcceptsReturn = true;
            this.passwordBox.Location = new System.Drawing.Point(72, 72);
            this.passwordBox.Name = "passwordBox";
            this.passwordBox.PasswordChar = '*';
            this.passwordBox.Size = new System.Drawing.Size(248, 20);
            this.passwordBox.TabIndex = 2;
            this.passwordBox.Text = string.Empty;
            // 
            // AuthDialog
            // 
            this.AcceptButton = this.okButton;
            this.AutoScaleBaseSize = new System.Drawing.Size(5, 13);
            this.CancelButton = this.cancelButton;
            this.ClientSize = new System.Drawing.Size(330, 127);
            this.ControlBox = false;
            this.Controls.Add(this.passwordBox);
            this.Controls.Add(this.passwordLabel);
            this.Controls.Add(this.accountBox);
            this.Controls.Add(this.accountLabel);
            this.Controls.Add(this.uriLabel);
            this.Controls.Add(this.cancelButton);
            this.Controls.Add(this.okButton);
            this.Controls.Add(this.uriBox);
            this.FormBorderStyle = System.Windows.Forms.FormBorderStyle.FixedDialog;
            this.MaximizeBox = false;
            this.MinimizeBox = false;
            this.Name = "AuthDialog";
            this.Text = "Authentication";
            this.ResumeLayout(false);

        }
		#endregion

        private void OKButton_Click(object sender, System.EventArgs e)
        {
            // Create or open a key
            RegistryKey rk = Registry.CurrentUser.CreateSubKey("Software\\Microsoft\\rtcpresence");

            rk.SetValue("uri", this.Uri);
            rk.SetValue("account", this.Account);

            this.Close();
        }

        private void CancelButton_Click(object sender, System.EventArgs e)
        {
            this.Close();
        }
	}
}
