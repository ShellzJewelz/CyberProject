namespace UserMessage
{
    partial class UserMessgaeForm
    {
        /// <summary>
        /// Required designer variable.
        /// </summary>
        private System.ComponentModel.IContainer components = null;

        /// <summary>
        /// Clean up any resources being used.
        /// </summary>
        /// <param name="disposing">true if managed resources should be disposed; otherwise, false.</param>
        protected override void Dispose(bool disposing)
        {
            if (disposing && (components != null))
            {
                components.Dispose();
            }
            base.Dispose(disposing);
        }

        #region Windows Form Designer generated code

        /// <summary>
        /// Required method for Designer support - do not modify
        /// the contents of this method with the code editor.
        /// </summary>
        private void InitializeComponent()
        {
            this.cancleButton = new System.Windows.Forms.Button();
            this.okButton = new System.Windows.Forms.Button();
            this.messageLabel = new System.Windows.Forms.Label();
            this.SuspendLayout();
            // 
            // cancleButton
            // 
            this.cancleButton.Location = new System.Drawing.Point(310, 99);
            this.cancleButton.Name = "cancleButton";
            this.cancleButton.Size = new System.Drawing.Size(75, 23);
            this.cancleButton.TabIndex = 5;
            this.cancleButton.Text = "Cancle";
            this.cancleButton.UseVisualStyleBackColor = true;
            this.cancleButton.Click += new System.EventHandler(this.cancleButton_Click);
            // 
            // okButton
            // 
            this.okButton.Location = new System.Drawing.Point(229, 99);
            this.okButton.Name = "okButton";
            this.okButton.Size = new System.Drawing.Size(75, 23);
            this.okButton.TabIndex = 4;
            this.okButton.Text = "OK";
            this.okButton.UseVisualStyleBackColor = true;
            this.okButton.Click += new System.EventHandler(this.okButton_Click);
            // 
            // messageLabel
            // 
            this.messageLabel.AutoSize = true;
            this.messageLabel.Location = new System.Drawing.Point(12, 27);
            this.messageLabel.Name = "messageLabel";
            this.messageLabel.Size = new System.Drawing.Size(231, 26);
            this.messageLabel.TabIndex = 3;
            this.messageLabel.Text = "The File: {0} is protected.\r\nWould you like to ask the admin for permission?";
            // 
            // UserMessgaeForm
            // 
            this.AutoScaleDimensions = new System.Drawing.SizeF(6F, 13F);
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
            this.ClientSize = new System.Drawing.Size(397, 134);
            this.ControlBox = false;
            this.Controls.Add(this.cancleButton);
            this.Controls.Add(this.okButton);
            this.Controls.Add(this.messageLabel);
            this.Name = "UserMessgaeForm";
            this.Text = "This File is Protected!";
            this.FormClosing += new System.Windows.Forms.FormClosingEventHandler(this.UserMessgaeForm_FormClosing);
            this.ResumeLayout(false);
            this.PerformLayout();

        }

        #endregion

        private System.Windows.Forms.Button cancleButton;
        private System.Windows.Forms.Button okButton;
        private System.Windows.Forms.Label messageLabel;
    }
}

