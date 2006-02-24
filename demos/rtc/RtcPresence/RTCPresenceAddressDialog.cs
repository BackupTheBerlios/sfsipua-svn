/*++

Copyright © Microsoft Corporation

Module Name:

    RTCPresenceAddressDialog.cs

Abstract:
	
--*/

using System;
using System.Drawing;
using System.Collections;
using System.ComponentModel;
using System.Windows.Forms;

namespace Microsoft.Rtc.Sdk.Samples.RtcPresence
{
    /// <summary>
    /// Summary description for RTCPresenceAddressDialog.
    /// </summary>
    public class AddressDialog : System.Windows.Forms.Form
    {
        private System.Windows.Forms.Button okButton;
        private System.Windows.Forms.Button cancelButton;
        private System.Windows.Forms.TextBox uriBox;
        private System.Windows.Forms.Label uriLabel;
        /// <summary>
        /// Required designer variable.
        /// </summary>
        private System.ComponentModel.Container components = null;

        public string Uri
        {
            get {return uriBox.Text;}
        }

        public AddressDialog(string title)
        {
            //
            // Required for Windows Form Designer support
            //
            InitializeComponent();

            this.uriBox.Text = string.Empty;
            this.Text = title;

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
            this.okButton.Location = new System.Drawing.Point(192, 40);
            this.okButton.Name = "okButton";
            this.okButton.Size = new System.Drawing.Size(64, 23);
            this.okButton.TabIndex = 3;
            this.okButton.Text = "OK";
            // 
            // cancelButton
            // 
            this.cancelButton.DialogResult = System.Windows.Forms.DialogResult.Cancel;
            this.cancelButton.Location = new System.Drawing.Point(264, 40);
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
            // AddressDialog
            // 
            this.AcceptButton = this.okButton;
            this.AutoScaleBaseSize = new System.Drawing.Size(5, 13);
            this.CancelButton = this.cancelButton;
            this.ClientSize = new System.Drawing.Size(330, 71);
            this.ControlBox = false;
            this.Controls.Add(this.uriLabel);
            this.Controls.Add(this.cancelButton);
            this.Controls.Add(this.okButton);
            this.Controls.Add(this.uriBox);
            this.FormBorderStyle = System.Windows.Forms.FormBorderStyle.FixedDialog;
            this.MaximizeBox = false;
            this.MinimizeBox = false;
            this.Name = "AddressDialog";
            this.Text = "Address";
            this.ResumeLayout(false);

        }
        #endregion

        private void OKButton_Click(object sender, System.EventArgs e)
        {
            this.Close();
        }

        private void CancelButton_Click(object sender, System.EventArgs e)
        {
            this.Close();
        }
    }
}
