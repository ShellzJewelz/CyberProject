namespace ServerController
{
    partial class FormServerController
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
            this.components = new System.ComponentModel.Container();
            this.tcServerTabs = new System.Windows.Forms.TabControl();
            this.tpServerSettings = new System.Windows.Forms.TabPage();
            this.gbGUISettings = new System.Windows.Forms.GroupBox();
            this.rbUseCustomGUISettings = new System.Windows.Forms.RadioButton();
            this.rbUseDefaultGUISettings = new System.Windows.Forms.RadioButton();
            this.tbGUIIP = new System.Windows.Forms.TextBox();
            this.tbGUIPort = new System.Windows.Forms.TextBox();
            this.laGUIIP = new System.Windows.Forms.Label();
            this.laGUIPort = new System.Windows.Forms.Label();
            this.rbUseCustomSettings = new System.Windows.Forms.RadioButton();
            this.gbServerSettings = new System.Windows.Forms.GroupBox();
            this.rbUseCustomServerSettings = new System.Windows.Forms.RadioButton();
            this.rbUseDefaultServerSettings = new System.Windows.Forms.RadioButton();
            this.tbServerBacklog = new System.Windows.Forms.TextBox();
            this.laBacklog = new System.Windows.Forms.Label();
            this.tbServerPort = new System.Windows.Forms.TextBox();
            this.tbServerIP = new System.Windows.Forms.TextBox();
            this.laServerPort = new System.Windows.Forms.Label();
            this.laServerIP = new System.Windows.Forms.Label();
            this.rbUseDefaultSettings = new System.Windows.Forms.RadioButton();
            this.tpServer = new System.Windows.Forms.TabPage();
            this.gbServerControls = new System.Windows.Forms.GroupBox();
            this.btRestart = new System.Windows.Forms.Button();
            this.btStop = new System.Windows.Forms.Button();
            this.btStart = new System.Windows.Forms.Button();
            this.gbClientList = new System.Windows.Forms.GroupBox();
            this.lbClients = new System.Windows.Forms.ListBox();
            this.gbServerLog = new System.Windows.Forms.GroupBox();
            this.rtbServerLog = new System.Windows.Forms.RichTextBox();
            this.tpClient = new System.Windows.Forms.TabPage();
            this.gbClient = new System.Windows.Forms.GroupBox();
            this.tbComputerPort = new System.Windows.Forms.TextBox();
            this.tbComputerIP = new System.Windows.Forms.TextBox();
            this.tbUserName = new System.Windows.Forms.TextBox();
            this.tbComputerName = new System.Windows.Forms.TextBox();
            this.laWhitelistedFiles = new System.Windows.Forms.Label();
            this.lbWhitelistedFiles = new System.Windows.Forms.ListBox();
            this.laWhitelistedFilesUsed = new System.Windows.Forms.Label();
            this.lbWhitelistedFilesUsed = new System.Windows.Forms.ListBox();
            this.laRunningProcesses = new System.Windows.Forms.Label();
            this.lbRunningProcesses = new System.Windows.Forms.ListBox();
            this.laComputerPort = new System.Windows.Forms.Label();
            this.laComputerIP = new System.Windows.Forms.Label();
            this.laUserName = new System.Windows.Forms.Label();
            this.laComputerName = new System.Windows.Forms.Label();
            this.tpRequests = new System.Windows.Forms.TabPage();
            this.gbRequestingClients = new System.Windows.Forms.GroupBox();
            this.lbRequestingClients = new System.Windows.Forms.ListBox();
            this.gbRequestedFiles = new System.Windows.Forms.GroupBox();
            this.lbRequestedFiles = new System.Windows.Forms.ListBox();
            this.epRequest = new System.Windows.Forms.ErrorProvider(this.components);
            this.laErrorProviderPlaceholder = new System.Windows.Forms.Label();
            this.epInput = new System.Windows.Forms.ErrorProvider(this.components);
            this.gbRequestControls = new System.Windows.Forms.GroupBox();
            this.btDeny = new System.Windows.Forms.Button();
            this.btAcceptAll = new System.Windows.Forms.Button();
            this.btAccept = new System.Windows.Forms.Button();
            this.btDenyAll = new System.Windows.Forms.Button();
            this.tcServerTabs.SuspendLayout();
            this.tpServerSettings.SuspendLayout();
            this.gbGUISettings.SuspendLayout();
            this.gbServerSettings.SuspendLayout();
            this.tpServer.SuspendLayout();
            this.gbServerControls.SuspendLayout();
            this.gbClientList.SuspendLayout();
            this.gbServerLog.SuspendLayout();
            this.tpClient.SuspendLayout();
            this.gbClient.SuspendLayout();
            this.tpRequests.SuspendLayout();
            this.gbRequestingClients.SuspendLayout();
            this.gbRequestedFiles.SuspendLayout();
            ((System.ComponentModel.ISupportInitialize)(this.epRequest)).BeginInit();
            ((System.ComponentModel.ISupportInitialize)(this.epInput)).BeginInit();
            this.gbRequestControls.SuspendLayout();
            this.SuspendLayout();
            // 
            // tcServerTabs
            // 
            this.tcServerTabs.Controls.Add(this.tpServerSettings);
            this.tcServerTabs.Controls.Add(this.tpServer);
            this.tcServerTabs.Controls.Add(this.tpClient);
            this.tcServerTabs.Controls.Add(this.tpRequests);
            this.tcServerTabs.Location = new System.Drawing.Point(12, 12);
            this.tcServerTabs.Name = "tcServerTabs";
            this.tcServerTabs.SelectedIndex = 0;
            this.tcServerTabs.Size = new System.Drawing.Size(739, 547);
            this.tcServerTabs.TabIndex = 0;
            this.tcServerTabs.Selected += new System.Windows.Forms.TabControlEventHandler(this.tcServerTabs_Selected);
            // 
            // tpServerSettings
            // 
            this.tpServerSettings.Controls.Add(this.gbGUISettings);
            this.tpServerSettings.Controls.Add(this.rbUseCustomSettings);
            this.tpServerSettings.Controls.Add(this.gbServerSettings);
            this.tpServerSettings.Controls.Add(this.rbUseDefaultSettings);
            this.tpServerSettings.Location = new System.Drawing.Point(4, 22);
            this.tpServerSettings.Name = "tpServerSettings";
            this.tpServerSettings.Padding = new System.Windows.Forms.Padding(3);
            this.tpServerSettings.Size = new System.Drawing.Size(731, 521);
            this.tpServerSettings.TabIndex = 0;
            this.tpServerSettings.Text = "Server Settings";
            this.tpServerSettings.UseVisualStyleBackColor = true;
            // 
            // gbGUISettings
            // 
            this.gbGUISettings.Controls.Add(this.rbUseCustomGUISettings);
            this.gbGUISettings.Controls.Add(this.rbUseDefaultGUISettings);
            this.gbGUISettings.Controls.Add(this.tbGUIIP);
            this.gbGUISettings.Controls.Add(this.tbGUIPort);
            this.gbGUISettings.Controls.Add(this.laGUIIP);
            this.gbGUISettings.Controls.Add(this.laGUIPort);
            this.gbGUISettings.Location = new System.Drawing.Point(3, 230);
            this.gbGUISettings.Name = "gbGUISettings";
            this.gbGUISettings.Size = new System.Drawing.Size(719, 201);
            this.gbGUISettings.TabIndex = 26;
            this.gbGUISettings.TabStop = false;
            this.gbGUISettings.Text = "GUI Settings";
            // 
            // rbUseCustomGUISettings
            // 
            this.rbUseCustomGUISettings.AutoSize = true;
            this.rbUseCustomGUISettings.Enabled = false;
            this.rbUseCustomGUISettings.Location = new System.Drawing.Point(12, 113);
            this.rbUseCustomGUISettings.Name = "rbUseCustomGUISettings";
            this.rbUseCustomGUISettings.Size = new System.Drawing.Size(145, 17);
            this.rbUseCustomGUISettings.TabIndex = 29;
            this.rbUseCustomGUISettings.Text = "Use Custom GUI Settings";
            this.rbUseCustomGUISettings.UseVisualStyleBackColor = true;
            this.rbUseCustomGUISettings.CheckedChanged += new System.EventHandler(this.rbUseCustomGUISettings_CheckedChanged);
            // 
            // rbUseDefaultGUISettings
            // 
            this.rbUseDefaultGUISettings.AutoSize = true;
            this.rbUseDefaultGUISettings.Checked = true;
            this.rbUseDefaultGUISettings.Enabled = false;
            this.rbUseDefaultGUISettings.Location = new System.Drawing.Point(12, 90);
            this.rbUseDefaultGUISettings.Name = "rbUseDefaultGUISettings";
            this.rbUseDefaultGUISettings.Size = new System.Drawing.Size(144, 17);
            this.rbUseDefaultGUISettings.TabIndex = 28;
            this.rbUseDefaultGUISettings.TabStop = true;
            this.rbUseDefaultGUISettings.Text = "Use Default GUI Settings";
            this.rbUseDefaultGUISettings.UseVisualStyleBackColor = true;
            // 
            // tbGUIIP
            // 
            this.tbGUIIP.BackColor = System.Drawing.Color.Silver;
            this.tbGUIIP.Enabled = false;
            this.tbGUIIP.Location = new System.Drawing.Point(98, 26);
            this.tbGUIIP.Name = "tbGUIIP";
            this.tbGUIIP.Size = new System.Drawing.Size(207, 20);
            this.tbGUIIP.TabIndex = 19;
            // 
            // tbGUIPort
            // 
            this.tbGUIPort.BackColor = System.Drawing.Color.Silver;
            this.tbGUIPort.Enabled = false;
            this.tbGUIPort.Location = new System.Drawing.Point(98, 52);
            this.tbGUIPort.Name = "tbGUIPort";
            this.tbGUIPort.Size = new System.Drawing.Size(207, 20);
            this.tbGUIPort.TabIndex = 20;
            // 
            // laGUIIP
            // 
            this.laGUIIP.AutoSize = true;
            this.laGUIIP.Location = new System.Drawing.Point(9, 29);
            this.laGUIIP.Name = "laGUIIP";
            this.laGUIIP.Size = new System.Drawing.Size(42, 13);
            this.laGUIIP.TabIndex = 6;
            this.laGUIIP.Text = "GUI IP:";
            // 
            // laGUIPort
            // 
            this.laGUIPort.AutoSize = true;
            this.laGUIPort.Location = new System.Drawing.Point(9, 55);
            this.laGUIPort.Name = "laGUIPort";
            this.laGUIPort.Size = new System.Drawing.Size(51, 13);
            this.laGUIPort.TabIndex = 10;
            this.laGUIPort.Text = "GUI Port:";
            // 
            // rbUseCustomSettings
            // 
            this.rbUseCustomSettings.AutoSize = true;
            this.rbUseCustomSettings.Location = new System.Drawing.Point(3, 489);
            this.rbUseCustomSettings.Name = "rbUseCustomSettings";
            this.rbUseCustomSettings.Size = new System.Drawing.Size(123, 17);
            this.rbUseCustomSettings.TabIndex = 31;
            this.rbUseCustomSettings.Text = "Use Custom Settings";
            this.rbUseCustomSettings.UseVisualStyleBackColor = true;
            this.rbUseCustomSettings.CheckedChanged += new System.EventHandler(this.rbUseCustomSettings_CheckedChanged);
            // 
            // gbServerSettings
            // 
            this.gbServerSettings.Controls.Add(this.rbUseCustomServerSettings);
            this.gbServerSettings.Controls.Add(this.rbUseDefaultServerSettings);
            this.gbServerSettings.Controls.Add(this.tbServerBacklog);
            this.gbServerSettings.Controls.Add(this.laBacklog);
            this.gbServerSettings.Controls.Add(this.tbServerPort);
            this.gbServerSettings.Controls.Add(this.tbServerIP);
            this.gbServerSettings.Controls.Add(this.laServerPort);
            this.gbServerSettings.Controls.Add(this.laServerIP);
            this.gbServerSettings.Location = new System.Drawing.Point(6, 6);
            this.gbServerSettings.Name = "gbServerSettings";
            this.gbServerSettings.Size = new System.Drawing.Size(719, 218);
            this.gbServerSettings.TabIndex = 1;
            this.gbServerSettings.TabStop = false;
            this.gbServerSettings.Text = "Server Settings";
            // 
            // rbUseCustomServerSettings
            // 
            this.rbUseCustomServerSettings.AutoSize = true;
            this.rbUseCustomServerSettings.Enabled = false;
            this.rbUseCustomServerSettings.Location = new System.Drawing.Point(9, 139);
            this.rbUseCustomServerSettings.Name = "rbUseCustomServerSettings";
            this.rbUseCustomServerSettings.Size = new System.Drawing.Size(157, 17);
            this.rbUseCustomServerSettings.TabIndex = 27;
            this.rbUseCustomServerSettings.Text = "Use Custom Server Settings";
            this.rbUseCustomServerSettings.UseVisualStyleBackColor = true;
            this.rbUseCustomServerSettings.CheckedChanged += new System.EventHandler(this.rbUseCustomServerSettings_CheckedChanged);
            // 
            // rbUseDefaultServerSettings
            // 
            this.rbUseDefaultServerSettings.AutoSize = true;
            this.rbUseDefaultServerSettings.Checked = true;
            this.rbUseDefaultServerSettings.Enabled = false;
            this.rbUseDefaultServerSettings.Location = new System.Drawing.Point(9, 116);
            this.rbUseDefaultServerSettings.Name = "rbUseDefaultServerSettings";
            this.rbUseDefaultServerSettings.Size = new System.Drawing.Size(156, 17);
            this.rbUseDefaultServerSettings.TabIndex = 26;
            this.rbUseDefaultServerSettings.TabStop = true;
            this.rbUseDefaultServerSettings.Text = "Use Default Server Settings";
            this.rbUseDefaultServerSettings.UseVisualStyleBackColor = true;
            // 
            // tbServerBacklog
            // 
            this.tbServerBacklog.BackColor = System.Drawing.Color.Silver;
            this.tbServerBacklog.Enabled = false;
            this.tbServerBacklog.Location = new System.Drawing.Point(98, 78);
            this.tbServerBacklog.Name = "tbServerBacklog";
            this.tbServerBacklog.Size = new System.Drawing.Size(207, 20);
            this.tbServerBacklog.TabIndex = 23;
            // 
            // laBacklog
            // 
            this.laBacklog.AutoSize = true;
            this.laBacklog.Location = new System.Drawing.Point(6, 81);
            this.laBacklog.Name = "laBacklog";
            this.laBacklog.Size = new System.Drawing.Size(83, 13);
            this.laBacklog.TabIndex = 22;
            this.laBacklog.Text = "Server Backlog:";
            // 
            // tbServerPort
            // 
            this.tbServerPort.BackColor = System.Drawing.Color.Silver;
            this.tbServerPort.Enabled = false;
            this.tbServerPort.Location = new System.Drawing.Point(98, 52);
            this.tbServerPort.Name = "tbServerPort";
            this.tbServerPort.Size = new System.Drawing.Size(207, 20);
            this.tbServerPort.TabIndex = 19;
            // 
            // tbServerIP
            // 
            this.tbServerIP.BackColor = System.Drawing.Color.Silver;
            this.tbServerIP.Enabled = false;
            this.tbServerIP.Location = new System.Drawing.Point(98, 26);
            this.tbServerIP.Name = "tbServerIP";
            this.tbServerIP.Size = new System.Drawing.Size(207, 20);
            this.tbServerIP.TabIndex = 18;
            // 
            // laServerPort
            // 
            this.laServerPort.AutoSize = true;
            this.laServerPort.Location = new System.Drawing.Point(6, 55);
            this.laServerPort.Name = "laServerPort";
            this.laServerPort.Size = new System.Drawing.Size(63, 13);
            this.laServerPort.TabIndex = 2;
            this.laServerPort.Text = "Server Port:";
            // 
            // laServerIP
            // 
            this.laServerIP.AutoSize = true;
            this.laServerIP.Location = new System.Drawing.Point(6, 29);
            this.laServerIP.Name = "laServerIP";
            this.laServerIP.Size = new System.Drawing.Size(54, 13);
            this.laServerIP.TabIndex = 0;
            this.laServerIP.Text = "Server IP:";
            // 
            // rbUseDefaultSettings
            // 
            this.rbUseDefaultSettings.AutoSize = true;
            this.rbUseDefaultSettings.Checked = true;
            this.rbUseDefaultSettings.Location = new System.Drawing.Point(3, 466);
            this.rbUseDefaultSettings.Name = "rbUseDefaultSettings";
            this.rbUseDefaultSettings.Size = new System.Drawing.Size(122, 17);
            this.rbUseDefaultSettings.TabIndex = 30;
            this.rbUseDefaultSettings.TabStop = true;
            this.rbUseDefaultSettings.Text = "Use Default Settings";
            this.rbUseDefaultSettings.UseVisualStyleBackColor = true;
            // 
            // tpServer
            // 
            this.tpServer.Controls.Add(this.gbServerControls);
            this.tpServer.Controls.Add(this.gbClientList);
            this.tpServer.Controls.Add(this.gbServerLog);
            this.tpServer.Location = new System.Drawing.Point(4, 22);
            this.tpServer.Name = "tpServer";
            this.tpServer.Padding = new System.Windows.Forms.Padding(3);
            this.tpServer.Size = new System.Drawing.Size(731, 521);
            this.tpServer.TabIndex = 1;
            this.tpServer.Text = "Server";
            this.tpServer.UseVisualStyleBackColor = true;
            // 
            // gbServerControls
            // 
            this.gbServerControls.Controls.Add(this.btRestart);
            this.gbServerControls.Controls.Add(this.btStop);
            this.gbServerControls.Controls.Add(this.btStart);
            this.gbServerControls.Location = new System.Drawing.Point(10, 390);
            this.gbServerControls.Name = "gbServerControls";
            this.gbServerControls.Size = new System.Drawing.Size(284, 125);
            this.gbServerControls.TabIndex = 10;
            this.gbServerControls.TabStop = false;
            this.gbServerControls.Text = "Server Controls";
            // 
            // btRestart
            // 
            this.btRestart.Enabled = false;
            this.btRestart.Location = new System.Drawing.Point(71, 56);
            this.btRestart.Name = "btRestart";
            this.btRestart.Size = new System.Drawing.Size(141, 23);
            this.btRestart.TabIndex = 1;
            this.btRestart.Text = "Restart";
            this.btRestart.UseVisualStyleBackColor = true;
            this.btRestart.Click += new System.EventHandler(this.btRestart_Click);
            // 
            // btStop
            // 
            this.btStop.Enabled = false;
            this.btStop.Location = new System.Drawing.Point(71, 96);
            this.btStop.Name = "btStop";
            this.btStop.Size = new System.Drawing.Size(141, 23);
            this.btStop.TabIndex = 2;
            this.btStop.Text = "Stop";
            this.btStop.UseVisualStyleBackColor = true;
            this.btStop.Click += new System.EventHandler(this.btStop_Click);
            // 
            // btStart
            // 
            this.btStart.Location = new System.Drawing.Point(71, 18);
            this.btStart.Name = "btStart";
            this.btStart.Size = new System.Drawing.Size(141, 23);
            this.btStart.TabIndex = 0;
            this.btStart.Text = "Start";
            this.btStart.UseVisualStyleBackColor = true;
            this.btStart.Click += new System.EventHandler(this.btStart_Click);
            // 
            // gbClientList
            // 
            this.gbClientList.Controls.Add(this.lbClients);
            this.gbClientList.Location = new System.Drawing.Point(10, 6);
            this.gbClientList.Name = "gbClientList";
            this.gbClientList.Size = new System.Drawing.Size(290, 378);
            this.gbClientList.TabIndex = 8;
            this.gbClientList.TabStop = false;
            this.gbClientList.Text = "Client List";
            // 
            // lbClients
            // 
            this.lbClients.BackColor = System.Drawing.Color.LightSteelBlue;
            this.lbClients.FormattingEnabled = true;
            this.lbClients.Location = new System.Drawing.Point(7, 17);
            this.lbClients.Name = "lbClients";
            this.lbClients.Size = new System.Drawing.Size(277, 355);
            this.lbClients.TabIndex = 5;
            // 
            // gbServerLog
            // 
            this.gbServerLog.Controls.Add(this.rtbServerLog);
            this.gbServerLog.Location = new System.Drawing.Point(306, 6);
            this.gbServerLog.Name = "gbServerLog";
            this.gbServerLog.Size = new System.Drawing.Size(419, 509);
            this.gbServerLog.TabIndex = 9;
            this.gbServerLog.TabStop = false;
            this.gbServerLog.Text = "Server Log";
            // 
            // rtbServerLog
            // 
            this.rtbServerLog.BackColor = System.Drawing.Color.LightSteelBlue;
            this.rtbServerLog.Location = new System.Drawing.Point(6, 19);
            this.rtbServerLog.Name = "rtbServerLog";
            this.rtbServerLog.Size = new System.Drawing.Size(407, 484);
            this.rtbServerLog.TabIndex = 4;
            this.rtbServerLog.Text = "";
            // 
            // tpClient
            // 
            this.tpClient.Controls.Add(this.gbClient);
            this.tpClient.Location = new System.Drawing.Point(4, 22);
            this.tpClient.Name = "tpClient";
            this.tpClient.Padding = new System.Windows.Forms.Padding(3);
            this.tpClient.Size = new System.Drawing.Size(731, 521);
            this.tpClient.TabIndex = 2;
            this.tpClient.Text = "Client";
            this.tpClient.UseVisualStyleBackColor = true;
            // 
            // gbClient
            // 
            this.gbClient.Controls.Add(this.tbComputerPort);
            this.gbClient.Controls.Add(this.tbComputerIP);
            this.gbClient.Controls.Add(this.tbUserName);
            this.gbClient.Controls.Add(this.tbComputerName);
            this.gbClient.Controls.Add(this.laWhitelistedFiles);
            this.gbClient.Controls.Add(this.lbWhitelistedFiles);
            this.gbClient.Controls.Add(this.laWhitelistedFilesUsed);
            this.gbClient.Controls.Add(this.lbWhitelistedFilesUsed);
            this.gbClient.Controls.Add(this.laRunningProcesses);
            this.gbClient.Controls.Add(this.lbRunningProcesses);
            this.gbClient.Controls.Add(this.laComputerPort);
            this.gbClient.Controls.Add(this.laComputerIP);
            this.gbClient.Controls.Add(this.laUserName);
            this.gbClient.Controls.Add(this.laComputerName);
            this.gbClient.Location = new System.Drawing.Point(6, 6);
            this.gbClient.Name = "gbClient";
            this.gbClient.Size = new System.Drawing.Size(719, 509);
            this.gbClient.TabIndex = 0;
            this.gbClient.TabStop = false;
            this.gbClient.Text = "Client Not Selected";
            // 
            // tbComputerPort
            // 
            this.tbComputerPort.BackColor = System.Drawing.SystemColors.Info;
            this.tbComputerPort.Location = new System.Drawing.Point(98, 104);
            this.tbComputerPort.Name = "tbComputerPort";
            this.tbComputerPort.Size = new System.Drawing.Size(207, 20);
            this.tbComputerPort.TabIndex = 21;
            // 
            // tbComputerIP
            // 
            this.tbComputerIP.BackColor = System.Drawing.SystemColors.Info;
            this.tbComputerIP.Location = new System.Drawing.Point(98, 78);
            this.tbComputerIP.Name = "tbComputerIP";
            this.tbComputerIP.Size = new System.Drawing.Size(207, 20);
            this.tbComputerIP.TabIndex = 20;
            // 
            // tbUserName
            // 
            this.tbUserName.BackColor = System.Drawing.SystemColors.Info;
            this.tbUserName.Location = new System.Drawing.Point(98, 52);
            this.tbUserName.Name = "tbUserName";
            this.tbUserName.Size = new System.Drawing.Size(207, 20);
            this.tbUserName.TabIndex = 19;
            // 
            // tbComputerName
            // 
            this.tbComputerName.BackColor = System.Drawing.SystemColors.Info;
            this.tbComputerName.Location = new System.Drawing.Point(98, 26);
            this.tbComputerName.Name = "tbComputerName";
            this.tbComputerName.Size = new System.Drawing.Size(207, 20);
            this.tbComputerName.TabIndex = 18;
            // 
            // laWhitelistedFiles
            // 
            this.laWhitelistedFiles.AutoSize = true;
            this.laWhitelistedFiles.Location = new System.Drawing.Point(414, 152);
            this.laWhitelistedFiles.Name = "laWhitelistedFiles";
            this.laWhitelistedFiles.Size = new System.Drawing.Size(105, 13);
            this.laWhitelistedFiles.TabIndex = 17;
            this.laWhitelistedFiles.Text = "Whitelisted Files List:";
            // 
            // lbWhitelistedFiles
            // 
            this.lbWhitelistedFiles.BackColor = System.Drawing.SystemColors.Info;
            this.lbWhitelistedFiles.FormattingEnabled = true;
            this.lbWhitelistedFiles.Location = new System.Drawing.Point(417, 168);
            this.lbWhitelistedFiles.Name = "lbWhitelistedFiles";
            this.lbWhitelistedFiles.Size = new System.Drawing.Size(296, 329);
            this.lbWhitelistedFiles.TabIndex = 16;
            // 
            // laWhitelistedFilesUsed
            // 
            this.laWhitelistedFilesUsed.AutoSize = true;
            this.laWhitelistedFilesUsed.Location = new System.Drawing.Point(6, 334);
            this.laWhitelistedFilesUsed.Name = "laWhitelistedFilesUsed";
            this.laWhitelistedFilesUsed.Size = new System.Drawing.Size(133, 13);
            this.laWhitelistedFilesUsed.TabIndex = 15;
            this.laWhitelistedFilesUsed.Text = "Whitelisted Files Used List:";
            // 
            // lbWhitelistedFilesUsed
            // 
            this.lbWhitelistedFilesUsed.BackColor = System.Drawing.SystemColors.Info;
            this.lbWhitelistedFilesUsed.FormattingEnabled = true;
            this.lbWhitelistedFilesUsed.Location = new System.Drawing.Point(9, 350);
            this.lbWhitelistedFilesUsed.Name = "lbWhitelistedFilesUsed";
            this.lbWhitelistedFilesUsed.Size = new System.Drawing.Size(296, 147);
            this.lbWhitelistedFilesUsed.TabIndex = 14;
            // 
            // laRunningProcesses
            // 
            this.laRunningProcesses.AutoSize = true;
            this.laRunningProcesses.Location = new System.Drawing.Point(6, 152);
            this.laRunningProcesses.Name = "laRunningProcesses";
            this.laRunningProcesses.Size = new System.Drawing.Size(121, 13);
            this.laRunningProcesses.TabIndex = 13;
            this.laRunningProcesses.Text = "Running Processes List:";
            // 
            // lbRunningProcesses
            // 
            this.lbRunningProcesses.BackColor = System.Drawing.SystemColors.Info;
            this.lbRunningProcesses.FormattingEnabled = true;
            this.lbRunningProcesses.Location = new System.Drawing.Point(9, 168);
            this.lbRunningProcesses.Name = "lbRunningProcesses";
            this.lbRunningProcesses.Size = new System.Drawing.Size(296, 147);
            this.lbRunningProcesses.TabIndex = 12;
            // 
            // laComputerPort
            // 
            this.laComputerPort.AutoSize = true;
            this.laComputerPort.Location = new System.Drawing.Point(6, 107);
            this.laComputerPort.Name = "laComputerPort";
            this.laComputerPort.Size = new System.Drawing.Size(77, 13);
            this.laComputerPort.TabIndex = 10;
            this.laComputerPort.Text = "Computer Port:";
            // 
            // laComputerIP
            // 
            this.laComputerIP.AutoSize = true;
            this.laComputerIP.Location = new System.Drawing.Point(6, 81);
            this.laComputerIP.Name = "laComputerIP";
            this.laComputerIP.Size = new System.Drawing.Size(68, 13);
            this.laComputerIP.TabIndex = 6;
            this.laComputerIP.Text = "Computer IP:";
            // 
            // laUserName
            // 
            this.laUserName.AutoSize = true;
            this.laUserName.Location = new System.Drawing.Point(6, 55);
            this.laUserName.Name = "laUserName";
            this.laUserName.Size = new System.Drawing.Size(63, 13);
            this.laUserName.TabIndex = 2;
            this.laUserName.Text = "User Name:";
            // 
            // laComputerName
            // 
            this.laComputerName.AutoSize = true;
            this.laComputerName.Location = new System.Drawing.Point(6, 29);
            this.laComputerName.Name = "laComputerName";
            this.laComputerName.Size = new System.Drawing.Size(86, 13);
            this.laComputerName.TabIndex = 0;
            this.laComputerName.Text = "Computer Name:";
            // 
            // tpRequests
            // 
            this.tpRequests.Controls.Add(this.gbRequestControls);
            this.tpRequests.Controls.Add(this.gbRequestingClients);
            this.tpRequests.Controls.Add(this.gbRequestedFiles);
            this.tpRequests.Location = new System.Drawing.Point(4, 22);
            this.tpRequests.Name = "tpRequests";
            this.tpRequests.Padding = new System.Windows.Forms.Padding(3);
            this.tpRequests.Size = new System.Drawing.Size(731, 521);
            this.tpRequests.TabIndex = 3;
            this.tpRequests.Text = "Requests";
            this.tpRequests.UseVisualStyleBackColor = true;
            // 
            // gbRequestingClients
            // 
            this.gbRequestingClients.Controls.Add(this.lbRequestingClients);
            this.gbRequestingClients.Location = new System.Drawing.Point(8, 6);
            this.gbRequestingClients.Name = "gbRequestingClients";
            this.gbRequestingClients.Size = new System.Drawing.Size(290, 509);
            this.gbRequestingClients.TabIndex = 10;
            this.gbRequestingClients.TabStop = false;
            this.gbRequestingClients.Text = "Requesting Clients";
            // 
            // lbRequestingClients
            // 
            this.lbRequestingClients.BackColor = System.Drawing.Color.PeachPuff;
            this.lbRequestingClients.FormattingEnabled = true;
            this.lbRequestingClients.Location = new System.Drawing.Point(7, 17);
            this.lbRequestingClients.Name = "lbRequestingClients";
            this.lbRequestingClients.Size = new System.Drawing.Size(277, 485);
            this.lbRequestingClients.TabIndex = 5;
            // 
            // gbRequestedFiles
            // 
            this.gbRequestedFiles.Controls.Add(this.lbRequestedFiles);
            this.gbRequestedFiles.Location = new System.Drawing.Point(304, 6);
            this.gbRequestedFiles.Name = "gbRequestedFiles";
            this.gbRequestedFiles.Size = new System.Drawing.Size(419, 411);
            this.gbRequestedFiles.TabIndex = 11;
            this.gbRequestedFiles.TabStop = false;
            this.gbRequestedFiles.Text = "Requested Files";
            // 
            // lbRequestedFiles
            // 
            this.lbRequestedFiles.BackColor = System.Drawing.Color.PeachPuff;
            this.lbRequestedFiles.FormattingEnabled = true;
            this.lbRequestedFiles.Location = new System.Drawing.Point(6, 17);
            this.lbRequestedFiles.Name = "lbRequestedFiles";
            this.lbRequestedFiles.Size = new System.Drawing.Size(407, 381);
            this.lbRequestedFiles.TabIndex = 6;
            // 
            // epRequest
            // 
            this.epRequest.BlinkStyle = System.Windows.Forms.ErrorBlinkStyle.NeverBlink;
            this.epRequest.ContainerControl = this;
            this.epRequest.RightToLeft = true;
            // 
            // laErrorProviderPlaceholder
            // 
            this.laErrorProviderPlaceholder.AutoSize = true;
            this.laErrorProviderPlaceholder.Location = new System.Drawing.Point(259, 16);
            this.laErrorProviderPlaceholder.Name = "laErrorProviderPlaceholder";
            this.laErrorProviderPlaceholder.Size = new System.Drawing.Size(0, 13);
            this.laErrorProviderPlaceholder.TabIndex = 1;
            // 
            // epInput
            // 
            this.epInput.BlinkStyle = System.Windows.Forms.ErrorBlinkStyle.NeverBlink;
            this.epInput.ContainerControl = this;
            // 
            // gbRequestControls
            // 
            this.gbRequestControls.Controls.Add(this.btDenyAll);
            this.gbRequestControls.Controls.Add(this.btDeny);
            this.gbRequestControls.Controls.Add(this.btAcceptAll);
            this.gbRequestControls.Controls.Add(this.btAccept);
            this.gbRequestControls.Location = new System.Drawing.Point(304, 423);
            this.gbRequestControls.Name = "gbRequestControls";
            this.gbRequestControls.Size = new System.Drawing.Size(419, 92);
            this.gbRequestControls.TabIndex = 12;
            this.gbRequestControls.TabStop = false;
            this.gbRequestControls.Text = "Request Controls";
            // 
            // btDeny
            // 
            this.btDeny.Enabled = false;
            this.btDeny.Location = new System.Drawing.Point(66, 57);
            this.btDeny.Name = "btDeny";
            this.btDeny.Size = new System.Drawing.Size(141, 23);
            this.btDeny.TabIndex = 1;
            this.btDeny.Text = "Deny";
            this.btDeny.UseVisualStyleBackColor = true;
            // 
            // btAcceptAll
            // 
            this.btAcceptAll.Enabled = false;
            this.btAcceptAll.Location = new System.Drawing.Point(213, 19);
            this.btAcceptAll.Name = "btAcceptAll";
            this.btAcceptAll.Size = new System.Drawing.Size(141, 23);
            this.btAcceptAll.TabIndex = 2;
            this.btAcceptAll.Text = "Accept All";
            this.btAcceptAll.UseVisualStyleBackColor = true;
            // 
            // btAccept
            // 
            this.btAccept.Enabled = false;
            this.btAccept.Location = new System.Drawing.Point(66, 19);
            this.btAccept.Name = "btAccept";
            this.btAccept.Size = new System.Drawing.Size(141, 23);
            this.btAccept.TabIndex = 0;
            this.btAccept.Text = "Accept";
            this.btAccept.UseVisualStyleBackColor = true;
            // 
            // btDenyAll
            // 
            this.btDenyAll.Enabled = false;
            this.btDenyAll.Location = new System.Drawing.Point(213, 57);
            this.btDenyAll.Name = "btDenyAll";
            this.btDenyAll.Size = new System.Drawing.Size(141, 23);
            this.btDenyAll.TabIndex = 3;
            this.btDenyAll.Text = "Deny All";
            this.btDenyAll.UseVisualStyleBackColor = true;
            // 
            // FormServerController
            // 
            this.AutoScaleDimensions = new System.Drawing.SizeF(6F, 13F);
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
            this.AutoSizeMode = System.Windows.Forms.AutoSizeMode.GrowAndShrink;
            this.ClientSize = new System.Drawing.Size(763, 571);
            this.Controls.Add(this.laErrorProviderPlaceholder);
            this.Controls.Add(this.tcServerTabs);
            this.MaximumSize = new System.Drawing.Size(779, 610);
            this.MinimumSize = new System.Drawing.Size(779, 610);
            this.Name = "FormServerController";
            this.Text = "Server Controller";
            this.FormClosing += new System.Windows.Forms.FormClosingEventHandler(this.FormServerController_FormClosing);
            this.tcServerTabs.ResumeLayout(false);
            this.tpServerSettings.ResumeLayout(false);
            this.tpServerSettings.PerformLayout();
            this.gbGUISettings.ResumeLayout(false);
            this.gbGUISettings.PerformLayout();
            this.gbServerSettings.ResumeLayout(false);
            this.gbServerSettings.PerformLayout();
            this.tpServer.ResumeLayout(false);
            this.gbServerControls.ResumeLayout(false);
            this.gbClientList.ResumeLayout(false);
            this.gbServerLog.ResumeLayout(false);
            this.tpClient.ResumeLayout(false);
            this.gbClient.ResumeLayout(false);
            this.gbClient.PerformLayout();
            this.tpRequests.ResumeLayout(false);
            this.gbRequestingClients.ResumeLayout(false);
            this.gbRequestedFiles.ResumeLayout(false);
            ((System.ComponentModel.ISupportInitialize)(this.epRequest)).EndInit();
            ((System.ComponentModel.ISupportInitialize)(this.epInput)).EndInit();
            this.gbRequestControls.ResumeLayout(false);
            this.ResumeLayout(false);
            this.PerformLayout();

        }

        #endregion

        private System.Windows.Forms.TabControl tcServerTabs;
        private System.Windows.Forms.TabPage tpServerSettings;
        private System.Windows.Forms.TabPage tpServer;
        private System.Windows.Forms.TabPage tpClient;
        private System.Windows.Forms.TabPage tpRequests;
        private System.Windows.Forms.RichTextBox rtbServerLog;
        private System.Windows.Forms.Button btStop;
        private System.Windows.Forms.Button btRestart;
        private System.Windows.Forms.Button btStart;
        private System.Windows.Forms.ListBox lbClients;
        private System.Windows.Forms.GroupBox gbClient;
        private System.Windows.Forms.Label laComputerName;
        private System.Windows.Forms.Label laWhitelistedFilesUsed;
        private System.Windows.Forms.ListBox lbWhitelistedFilesUsed;
        private System.Windows.Forms.Label laRunningProcesses;
        private System.Windows.Forms.ListBox lbRunningProcesses;
        private System.Windows.Forms.Label laComputerPort;
        private System.Windows.Forms.Label laComputerIP;
        private System.Windows.Forms.Label laUserName;
        private System.Windows.Forms.ErrorProvider epRequest;
        private System.Windows.Forms.Label laErrorProviderPlaceholder;
        private System.Windows.Forms.GroupBox gbClientList;
        private System.Windows.Forms.GroupBox gbServerLog;
        private System.Windows.Forms.GroupBox gbServerControls;
        private System.Windows.Forms.Label laWhitelistedFiles;
        private System.Windows.Forms.ListBox lbWhitelistedFiles;
        private System.Windows.Forms.TextBox tbComputerPort;
        private System.Windows.Forms.TextBox tbComputerIP;
        private System.Windows.Forms.TextBox tbComputerName;
        private System.Windows.Forms.TextBox tbUserName;
        private System.Windows.Forms.GroupBox gbRequestingClients;
        private System.Windows.Forms.ListBox lbRequestingClients;
        private System.Windows.Forms.GroupBox gbRequestedFiles;
        private System.Windows.Forms.ListBox lbRequestedFiles;
        private System.Windows.Forms.GroupBox gbServerSettings;
        private System.Windows.Forms.TextBox tbGUIPort;
        private System.Windows.Forms.TextBox tbServerPort;
        private System.Windows.Forms.TextBox tbServerIP;
        private System.Windows.Forms.Label laGUIPort;
        private System.Windows.Forms.Label laGUIIP;
        private System.Windows.Forms.Label laServerPort;
        private System.Windows.Forms.Label laServerIP;
        private System.Windows.Forms.TextBox tbServerBacklog;
        private System.Windows.Forms.Label laBacklog;
        private System.Windows.Forms.RadioButton rbUseCustomSettings;
        private System.Windows.Forms.RadioButton rbUseDefaultSettings;
        private System.Windows.Forms.GroupBox gbGUISettings;
        private System.Windows.Forms.RadioButton rbUseCustomGUISettings;
        private System.Windows.Forms.RadioButton rbUseDefaultGUISettings;
        private System.Windows.Forms.TextBox tbGUIIP;
        private System.Windows.Forms.RadioButton rbUseCustomServerSettings;
        private System.Windows.Forms.RadioButton rbUseDefaultServerSettings;
        private System.Windows.Forms.ErrorProvider epInput;
        private System.Windows.Forms.GroupBox gbRequestControls;
        private System.Windows.Forms.Button btDenyAll;
        private System.Windows.Forms.Button btDeny;
        private System.Windows.Forms.Button btAcceptAll;
        private System.Windows.Forms.Button btAccept;
    }
}

