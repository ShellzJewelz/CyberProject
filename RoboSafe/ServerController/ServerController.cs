using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Diagnostics;
using System.Drawing;
using System.Linq;
using System.Net;
using System.Net.Sockets;
using System.Text;
using System.Text.RegularExpressions;
using System.Threading;
using System.Threading.Tasks;
using System.Windows.Forms;

namespace ServerController
{
    public partial class FormServerController : Form
    {
        const string PROCESS_NAME = @"C:\Users\Admin\Desktop\CyberProject\Release\Server.exe";
        const string DEFAULT_SERVER_IP = "127.0.0.1";
        const int DEFAULT_SERVER_PORT = 20000;
        const int DEFAULT_SERVER_BACKLOG = 5;
        
        const string DEFAULT_GUI_IP = "127.0.0.1";
        const int DEFAULT_GUI_PORT = 20001;
        const int DEFAULT_GUI_BACKLOG = 1;

        const int BUFFER = 1024;

        IPAddress ipaIP;
        IPEndPoint ipepAddress;
        Socket sGUI;
        Socket sServer;
        byte[] byBuffer;
        bool bRunning;       

        Process pServer;
        Thread tProcessCommunication;
        ThreadStart tsProcessCommunicationRoutine;

        Button[] btServerControls;
        TextBox[] tbServerSettingsTextBoxes;
        TextBox[] tbGUISettingsTextBoxes;
        RadioButton[] rbSettingsRadioButtons;

        Regex reIP = new Regex(@"^\d{1,3}\.{3}\d{1,3}$");
        Regex reNumber = new Regex(@"^[0-9]*$");

        private void SetClientInformation(string sClientInformation)
        {
            // Some parsing on sClientInformation

            //this.gbClient.Text = ;
            //this.tbComputerName.Text = ;
            //this.tbComputerIP.Text = ;
            //this.tbComputerPort.Text = ;
            //this.lbRunningProcesses.DataSource = ;
            //this.lbWhitelistedFilesUsed.DataSource = ;
            //this.lbWhitelistedFiles.DataSource = ;
        }

        private void ClearClientInformation()
        {
            this.gbClient.Text = "Client Not Selected";
            this.tbComputerName.Text = "";
            this.tbComputerIP.Text = "";
            this.tbComputerPort.Text = "";
            this.lbRunningProcesses.Items.Clear();
            this.lbWhitelistedFilesUsed.Items.Clear();
            this.lbWhitelistedFiles.Items.Clear();
        }

        private void Send(string sData)
        {
            byBuffer = Encoding.UTF8.GetBytes(sData);
            sServer.Send(byBuffer);
        }

        private string Receive()
        {
            byBuffer = new byte[BUFFER];
            int iLength = sServer.Receive(byBuffer);
            string sData = Encoding.UTF8.GetString(byBuffer).Substring(0, iLength);
            return sData;
        }

        private void CommunicationRoutine()
        {
            this.sGUI = new Socket(
                AddressFamily.InterNetwork,
                SocketType.Stream,
                ProtocolType.Tcp
                );
            if (rbUseDefaultGUISettings.Checked)
            {
                /*
                Use default GUI socket settings
                */
                this.ipaIP = IPAddress.Parse(DEFAULT_GUI_IP);
                this.ipepAddress = new IPEndPoint(ipaIP, DEFAULT_GUI_PORT);
                this.sGUI.Bind(ipepAddress);
                this.sGUI.Listen(DEFAULT_GUI_BACKLOG);             
            }
            else
            {
                /*
                Use custom GUI socket settings
                */
                string sIP = tbGUIIP.Text;
                this.ipaIP = IPAddress.Parse(sIP);
                int iPort = int.Parse(tbGUIPort.Text);
                this.ipepAddress = new IPEndPoint(ipaIP, iPort);
                this.sGUI.Bind(ipepAddress);
                this.sGUI.Listen(DEFAULT_GUI_BACKLOG);
            }

            this.sServer = sGUI.Accept();
            this.sServer.ReceiveTimeout = 500;
            while (this.bRunning)
            {
                try
                {
                    string sData = Receive();
                    //this.epRequest.SetError(this.laErrorProviderPlaceholder, "New Incoming Requests");
                }
                catch (Exception)
                {
                }
            }
            this.sGUI.Close();
        }

        public FormServerController()
        {       
            InitializeComponent();

            /*
            Group up the controllers for
            easier property manipulation
            */
            this.btServerControls = new Button[]
            {
                this.btRestart,
                this.btStop
            };
            this.tbServerSettingsTextBoxes = new TextBox[]
            {
                this.tbServerIP,
                this.tbServerPort,
                this.tbServerBacklog
            };
            this.tbGUISettingsTextBoxes = new TextBox[]
            {
                this.tbGUIIP,
                this.tbGUIPort
            };
            this.rbSettingsRadioButtons = new RadioButton[]
            {
                this.rbUseDefaultServerSettings,
                this.rbUseCustomServerSettings,
                this.rbUseDefaultGUISettings,
                this.rbUseCustomGUISettings
            };

            /*
            Prepare the thread 
            */
            tsProcessCommunicationRoutine = new ThreadStart(CommunicationRoutine);
        }

        private void btStart_Click(object sender, EventArgs e)
        {
            /*
            Set up and start the process
            and the communication with it
            then disable the Start button
            and enable the Stop and Restart
            button
            */

            /*
            Check the input with a regular 
            expression
            */
            string[] sArguments;
            if (this.rbUseCustomServerSettings.Checked)
            {
                sArguments = new string[]
                {
                    this.tbServerIP.Text,
                    this.tbServerPort.Text,
                    this.tbServerBacklog.Text
                };
                this.pServer.StartInfo.Arguments = string.Join(" ", sArguments);
            }

            this.bRunning = true;
            this.tProcessCommunication = new Thread(tsProcessCommunicationRoutine);
            this.tProcessCommunication.IsBackground = false;
            this.tProcessCommunication.Start();

            this.pServer = new Process();
            this.pServer.StartInfo.FileName = PROCESS_NAME;
            this.pServer.StartInfo.CreateNoWindow = true;
            this.pServer.Start();
            this.btStart.Enabled = false;

            foreach (Button btServerControl in this.btServerControls)
                btServerControl.Enabled = true;           
        }

        private void btRestart_Click(object sender, EventArgs e)
        {
            /*
            Restart the process and 
            the communication with it
            */
            if (sServer != null)
            {
                this.bRunning = false;
                this.tProcessCommunication.Join();
            }
            else
                this.tProcessCommunication.Abort();          

            try
            {
                this.pServer.Kill();                
            }
            catch (Exception){}
            finally
            {
                this.pServer.Close();
            }            

            this.bRunning = true;
            this.tProcessCommunication = new Thread(tsProcessCommunicationRoutine);
            this.tProcessCommunication.IsBackground = false;
            this.tProcessCommunication.Start();

            this.pServer = new Process();
            this.pServer.StartInfo.FileName = PROCESS_NAME;
            this.pServer.StartInfo.CreateNoWindow = true;
            this.pServer.Start();
        }

        private void btStop_Click(object sender, EventArgs e)
        {
            /*
            Kill the old process and
            stop the communication
            */
            if (sServer != null)
            {
                this.bRunning = false;
                this.tProcessCommunication.Join();
            }
            else
                this.tProcessCommunication.Abort();
                   
            try
            {
                this.pServer.Kill();
            }
            catch (Exception){}
            finally
            {
                this.pServer.Close();
            }

            foreach (Button btServerControl in this.btServerControls)
                btServerControl.Enabled = false;
            this.btStart.Enabled = true;
        }

        private void tcServerTabs_Selected(object sender, TabControlEventArgs e)
        {
            /*
            Clear the error provider's error
            if the forth tab page is selected           
            */
            if (e.TabPageIndex == 3)
            {
                this.epRequest.Clear();
            }
        }

        private void rbUseCustomSettings_CheckedChanged(object sender, EventArgs e)
        {
            /*
            If the user wants to use custom 
            settings enable the radio buttons 
            that will provide him with option
            to do so where he needs to
            otherwise disable those text boxes
            and radio buttons
            */
            if (rbUseCustomSettings.Checked)
            {
                foreach (RadioButton tbSettingsRadioButton in this.rbSettingsRadioButtons)
                    tbSettingsRadioButton.Enabled = true;
            }
            else
            {
                foreach (TextBox tbServerSetting in tbServerSettingsTextBoxes)
                    tbServerSetting.Enabled = false;
                foreach (TextBox tbGUISetting in tbGUISettingsTextBoxes)
                    tbGUISetting.Enabled = false;
                foreach (RadioButton tbSettingsRadioButton in this.rbSettingsRadioButtons)
                    tbSettingsRadioButton.Enabled = false;
                this.rbUseDefaultServerSettings.Select();
                this.rbUseDefaultGUISettings.Select();             
            }
        }

        private void rbUseCustomServerSettings_CheckedChanged(object sender, EventArgs e)
        {
            /*
            If the user wants to use default
            server settings then disable the 
            text boxes otherwise enable them
            */
            if (this.rbUseCustomServerSettings.Checked)
            {
                foreach (TextBox tbServerSetting in this.tbServerSettingsTextBoxes)
                    tbServerSetting.Enabled = true;
            }
            else
            {
                foreach (TextBox tbServerSetting in tbServerSettingsTextBoxes)
                    tbServerSetting.Enabled = false;
            }
        }

        private void rbUseCustomGUISettings_CheckedChanged(object sender, EventArgs e)
        {
            /*
            If the user wants to use default
            GUI settings then disable the text
            boxes otherwise enable them
            */
            if (this.rbUseCustomGUISettings.Checked)
            {
                foreach (TextBox tbGUISetting in this.tbGUISettingsTextBoxes)
                    tbGUISetting.Enabled = true;
            }
            else
            {
                foreach (TextBox tbGUISetting in tbGUISettingsTextBoxes)
                    tbGUISetting.Enabled = false;
            }
        }

        private void FormServerController_FormClosing(object sender, FormClosingEventArgs e)
        {
            if (this.tProcessCommunication != null)
            {
                this.bRunning = false;
                this.tProcessCommunication.Join();
            }
        }
    }
}