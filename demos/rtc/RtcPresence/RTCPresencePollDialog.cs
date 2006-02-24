/*++

Copyright © Microsoft Corporation

Module Name:

    RTCPresencePollDialog.cs

Abstract:
		
--*/

using System;
using System.Drawing;
using System.Collections;
using System.ComponentModel;
using System.Windows.Forms;
using System.Diagnostics;

namespace Microsoft.Rtc.Sdk.Samples.RtcPresence
{
    public class PollDialog : System.Windows.Forms.Form
    {
        private System.Windows.Forms.Button pollButton;
        private System.Windows.Forms.Button cancelButton;
        private System.Windows.Forms.TextBox uriBox;
        private System.Windows.Forms.Label uriLabel;
        private System.Windows.Forms.RichTextBox richTextBox1;
        private RTCPresence rtcPresence;
        private string pollUri = null;

        /// <summary>
        /// Required designer variable.
        /// </summary>
        private System.ComponentModel.Container components = null;

        public string Uri
        {
            get {return this.pollUri;}
        }

        public string Properties
        {
            get
            {
                return this.richTextBox1.Text;
            }
            set 
            {
                this.richTextBox1.Clear();
                this.richTextBox1.AppendText(value);
            }
        }

        public PollDialog(string title, RTCPresence presence)
        {
            //
            // Required for Windows Form Designer support
            //
            InitializeComponent();

            this.uriBox.Text = string.Empty;
            this.Text = title;

            this.pollButton.Click +=new EventHandler(PollButton_Click);
            this.cancelButton.Click +=new EventHandler(CancelButton_Click);

            this.rtcPresence = presence;
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
            this.pollButton = new System.Windows.Forms.Button();
            this.cancelButton = new System.Windows.Forms.Button();
            this.uriLabel = new System.Windows.Forms.Label();
            this.richTextBox1 = new System.Windows.Forms.RichTextBox();
            this.SuspendLayout();
            // 
            // uriBox
            // 
            this.uriBox.Location = new System.Drawing.Point(72, 8);
            this.uriBox.Name = "uriBox";
            this.uriBox.Size = new System.Drawing.Size(248, 20);
            this.uriBox.TabIndex = 0;
            this.uriBox.Text = "";
            // 
            // pollButton
            // 
            this.pollButton.DialogResult = System.Windows.Forms.DialogResult.OK;
            this.pollButton.Location = new System.Drawing.Point(192, 40);
            this.pollButton.Name = "pollButton";
            this.pollButton.Size = new System.Drawing.Size(64, 23);
            this.pollButton.TabIndex = 3;
            this.pollButton.Text = "Poll";
            // 
            // cancelButton
            // 
            this.cancelButton.DialogResult = System.Windows.Forms.DialogResult.Cancel;
            this.cancelButton.Location = new System.Drawing.Point(264, 40);
            this.cancelButton.Name = "cancelButton";
            this.cancelButton.Size = new System.Drawing.Size(56, 23);
            this.cancelButton.TabIndex = 4;
            this.cancelButton.Text = "Close";
            // 
            // uriLabel
            // 
            this.uriLabel.Location = new System.Drawing.Point(8, 8);
            this.uriLabel.Name = "uriLabel";
            this.uriLabel.Size = new System.Drawing.Size(64, 23);
            this.uriLabel.TabIndex = 3;
            this.uriLabel.Text = "User URI";
            // 
            // richTextBox1
            // 
            this.richTextBox1.Dock = System.Windows.Forms.DockStyle.Bottom;
            this.richTextBox1.Location = new System.Drawing.Point(0, 71);
            this.richTextBox1.Name = "richTextBox1";
            this.richTextBox1.ReadOnly = true;
            this.richTextBox1.Size = new System.Drawing.Size(330, 320);
            this.richTextBox1.TabIndex = 7;
            this.richTextBox1.Text = "";
            this.richTextBox1.WordWrap = false;
            // 
            // PollDialog
            // 
            this.AcceptButton = this.pollButton;
            this.AutoScaleBaseSize = new System.Drawing.Size(5, 13);
            this.CancelButton = this.cancelButton;
            this.ClientSize = new System.Drawing.Size(330, 391);
            this.ControlBox = false;
            this.Controls.Add(this.richTextBox1);
            this.Controls.Add(this.uriLabel);
            this.Controls.Add(this.cancelButton);
            this.Controls.Add(this.pollButton);
            this.Controls.Add(this.uriBox);
            this.MaximizeBox = false;
            this.MinimizeBox = false;
            this.Name = "PollDialog";
            this.Text = "Poll Presence";
            this.ResumeLayout(false);

        }
        #endregion

        private void PollButton_Click(object sender, System.EventArgs e)
        {
            this.pollUri = this.uriBox.Text;
            this.richTextBox1.Clear();

            this.rtcPresence.DoPollBuddy(this.Uri);
        }

        private void CancelButton_Click(object sender, System.EventArgs e)
        {
            Trace.WriteLine("Poll Contact canceled");
            this.Close();
            this.rtcPresence.CancelPollBuddy();
        }
    }
}
