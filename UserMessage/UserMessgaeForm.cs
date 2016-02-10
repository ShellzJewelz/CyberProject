using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Threading;
using System.Threading.Tasks;
using System.Windows.Forms;

namespace UserMessage
{
    public partial class UserMessgaeForm : Form
    {
        bool bClosing = false;
        bool bWaiting = true;
        ThreadStart tsWaitingFunction;
        Thread tWaitingThread;

        public UserMessgaeForm()
        {
            InitializeComponent();
        }

        void WaitingFunction()
        {
            while (bWaiting)
            {
                for (int iCycle = 0; iCycle < 3; iCycle++)
                {
                    string text = "Waiting for admin approval";
                    for (int iDotCount = 0; iDotCount < iCycle + 1; iDotCount++)
                        text += '.';
                    this.messageLabel.Text = text;
                    Thread.Sleep((iCycle + 1) * 500);
                }
            }
        }

        private void okButton_Click(object sender, EventArgs e)
        {
            this.okButton.Visible = false;
            tsWaitingFunction = new ThreadStart(WaitingFunction);
            tWaitingThread = new Thread(tsWaitingFunction);
            tWaitingThread.Start();
        }

        private void cancleButton_Click(object sender, EventArgs e)
        {
            if (!this.okButton.Visible)
            {
                bWaiting = false;
                tWaitingThread.Join();
            }
            bClosing = true;
            Application.Exit();
        }

        private void UserMessgaeForm_FormClosing(object sender, FormClosingEventArgs e)
        {
            if (!bClosing)
                e.Cancel = true;
        }
    }
}
