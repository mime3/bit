namespace WindowsFormsApp1
{
	partial class MainForm
	{
		/// <summary>
		/// 필수 디자이너 변수입니다.
		/// </summary>
		private System.ComponentModel.IContainer components = null;

		/// <summary>
		/// 사용 중인 모든 리소스를 정리합니다.
		/// </summary>
		/// <param name="disposing">관리되는 리소스를 삭제해야 하면 true이고, 그렇지 않으면 false입니다.</param>
		protected override void Dispose(bool disposing)
		{
			if (disposing && (components != null))
			{
				components.Dispose();
			}
			base.Dispose(disposing);
		}

		#region Windows Form 디자이너에서 생성한 코드

		/// <summary>
		/// 디자이너 지원에 필요한 메서드입니다. 
		/// 이 메서드의 내용을 코드 편집기로 수정하지 마세요.
		/// </summary>
		private void InitializeComponent()
		{
			this.lblFont = new System.Windows.Forms.Label();
			this.txtSampleText = new System.Windows.Forms.TextBox();
			this.chkBold = new System.Windows.Forms.CheckBox();
			this.chkItalic = new System.Windows.Forms.CheckBox();
			this.cboFont = new System.Windows.Forms.ComboBox();
			this.grpFont = new System.Windows.Forms.GroupBox();
			this.grpBar = new System.Windows.Forms.GroupBox();
			this.tbDummy = new System.Windows.Forms.TrackBar();
			this.pgDummy = new System.Windows.Forms.ProgressBar();
			this.grpForm = new System.Windows.Forms.GroupBox();
			this.btnModal = new System.Windows.Forms.Button();
			this.btnModaless = new System.Windows.Forms.Button();
			this.btnMsgBox = new System.Windows.Forms.Button();
			this.grpTreeList = new System.Windows.Forms.GroupBox();
			this.tvDummy = new System.Windows.Forms.TreeView();
			this.lvDummy = new System.Windows.Forms.ListView();
			this.btnAddRoot = new System.Windows.Forms.Button();
			this.btnAddChild = new System.Windows.Forms.Button();
			((System.ComponentModel.ISupportInitialize)(this.tbDummy)).BeginInit();
			this.SuspendLayout();
			// 
			// lblFont
			// 
			this.lblFont.AutoSize = true;
			this.lblFont.Location = new System.Drawing.Point(24, 61);
			this.lblFont.Name = "lblFont";
			this.lblFont.Size = new System.Drawing.Size(29, 12);
			this.lblFont.TabIndex = 0;
			this.lblFont.Text = "Font";
			// 
			// txtSampleText
			// 
			this.txtSampleText.Location = new System.Drawing.Point(26, 84);
			this.txtSampleText.Name = "txtSampleText";
			this.txtSampleText.Size = new System.Drawing.Size(415, 21);
			this.txtSampleText.TabIndex = 1;
			this.txtSampleText.Text = "Hello, C#";
			// 
			// chkBold
			// 
			this.chkBold.AutoSize = true;
			this.chkBold.Location = new System.Drawing.Point(204, 58);
			this.chkBold.Name = "chkBold";
			this.chkBold.Size = new System.Drawing.Size(48, 16);
			this.chkBold.TabIndex = 2;
			this.chkBold.Text = "굵게";
			this.chkBold.UseVisualStyleBackColor = true;
			// 
			// chkItalic
			// 
			this.chkItalic.AutoSize = true;
			this.chkItalic.Location = new System.Drawing.Point(308, 58);
			this.chkItalic.Name = "chkItalic";
			this.chkItalic.Size = new System.Drawing.Size(60, 16);
			this.chkItalic.TabIndex = 3;
			this.chkItalic.Text = "이탤릭";
			this.chkItalic.UseVisualStyleBackColor = true;
			// 
			// cboFont
			// 
			this.cboFont.FormattingEnabled = true;
			this.cboFont.Location = new System.Drawing.Point(59, 58);
			this.cboFont.Name = "cboFont";
			this.cboFont.Size = new System.Drawing.Size(121, 20);
			this.cboFont.TabIndex = 4;
			// 
			// grpFont
			// 
			this.grpFont.Location = new System.Drawing.Point(26, 12);
			this.grpFont.Name = "grpFont";
			this.grpFont.Size = new System.Drawing.Size(226, 24);
			this.grpFont.TabIndex = 5;
			this.grpFont.TabStop = false;
			this.grpFont.Text = "ComboBox, CheckBox, TextBox";
			// 
			// grpBar
			// 
			this.grpBar.Location = new System.Drawing.Point(26, 135);
			this.grpBar.Name = "grpBar";
			this.grpBar.Size = new System.Drawing.Size(188, 18);
			this.grpBar.TabIndex = 6;
			this.grpBar.TabStop = false;
			this.grpBar.Text = "TrackBar, ProgressBar";
			// 
			// tbDummy
			// 
			this.tbDummy.Location = new System.Drawing.Point(26, 160);
			this.tbDummy.Maximum = 20;
			this.tbDummy.Name = "tbDummy";
			this.tbDummy.Size = new System.Drawing.Size(415, 45);
			this.tbDummy.TabIndex = 7;
			this.tbDummy.Scroll += new System.EventHandler(this.TbDummy_Scroll);
			// 
			// pgDummy
			// 
			this.pgDummy.Location = new System.Drawing.Point(26, 218);
			this.pgDummy.Maximum = 20;
			this.pgDummy.Name = "pgDummy";
			this.pgDummy.Size = new System.Drawing.Size(417, 25);
			this.pgDummy.TabIndex = 8;
			// 
			// grpForm
			// 
			this.grpForm.Location = new System.Drawing.Point(26, 262);
			this.grpForm.Name = "grpForm";
			this.grpForm.Size = new System.Drawing.Size(200, 20);
			this.grpForm.TabIndex = 9;
			this.grpForm.TabStop = false;
			this.grpForm.Text = "Modal & Modaless";
			// 
			// btnModal
			// 
			this.btnModal.Location = new System.Drawing.Point(26, 306);
			this.btnModal.Name = "btnModal";
			this.btnModal.Size = new System.Drawing.Size(105, 27);
			this.btnModal.TabIndex = 10;
			this.btnModal.Text = "Modal";
			this.btnModal.UseVisualStyleBackColor = true;
			this.btnModal.Click += new System.EventHandler(this.BtnModal_Click);
			// 
			// btnModaless
			// 
			this.btnModaless.Location = new System.Drawing.Point(162, 306);
			this.btnModaless.Name = "btnModaless";
			this.btnModaless.Size = new System.Drawing.Size(105, 27);
			this.btnModaless.TabIndex = 11;
			this.btnModaless.Text = "Modaless";
			this.btnModaless.UseVisualStyleBackColor = true;
			this.btnModaless.Click += new System.EventHandler(this.BtnModaless_Click);
			// 
			// btnMsgBox
			// 
			this.btnMsgBox.Location = new System.Drawing.Point(299, 306);
			this.btnMsgBox.Name = "btnMsgBox";
			this.btnMsgBox.Size = new System.Drawing.Size(105, 27);
			this.btnMsgBox.TabIndex = 12;
			this.btnMsgBox.Text = "MessageBox";
			this.btnMsgBox.UseVisualStyleBackColor = true;
			this.btnMsgBox.Click += new System.EventHandler(this.BtnMsgBox_Click);
			// 
			// grpTreeList
			// 
			this.grpTreeList.Location = new System.Drawing.Point(30, 368);
			this.grpTreeList.Name = "grpTreeList";
			this.grpTreeList.Size = new System.Drawing.Size(150, 20);
			this.grpTreeList.TabIndex = 13;
			this.grpTreeList.TabStop = false;
			this.grpTreeList.Text = "TreeView && ListView";
			// 
			// tvDummy
			// 
			this.tvDummy.Location = new System.Drawing.Point(30, 397);
			this.tvDummy.Name = "tvDummy";
			this.tvDummy.Size = new System.Drawing.Size(184, 97);
			this.tvDummy.TabIndex = 14;
			// 
			// lvDummy
			// 
			this.lvDummy.Location = new System.Drawing.Point(254, 397);
			this.lvDummy.Name = "lvDummy";
			this.lvDummy.Size = new System.Drawing.Size(187, 97);
			this.lvDummy.TabIndex = 15;
			this.lvDummy.UseCompatibleStateImageBehavior = false;
			// 
			// btnAddRoot
			// 
			this.btnAddRoot.Location = new System.Drawing.Point(30, 504);
			this.btnAddRoot.Name = "btnAddRoot";
			this.btnAddRoot.Size = new System.Drawing.Size(75, 23);
			this.btnAddRoot.TabIndex = 16;
			this.btnAddRoot.Text = "루트 추가";
			this.btnAddRoot.UseVisualStyleBackColor = true;
			// 
			// btnAddChild
			// 
			this.btnAddChild.Location = new System.Drawing.Point(111, 504);
			this.btnAddChild.Name = "btnAddChild";
			this.btnAddChild.Size = new System.Drawing.Size(75, 23);
			this.btnAddChild.TabIndex = 17;
			this.btnAddChild.Text = "자식 추가";
			this.btnAddChild.UseVisualStyleBackColor = true;
			// 
			// MainForm
			// 
			this.AutoScaleDimensions = new System.Drawing.SizeF(7F, 12F);
			this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
			this.ClientSize = new System.Drawing.Size(474, 539);
			this.Controls.Add(this.btnAddChild);
			this.Controls.Add(this.btnAddRoot);
			this.Controls.Add(this.lvDummy);
			this.Controls.Add(this.tvDummy);
			this.Controls.Add(this.grpTreeList);
			this.Controls.Add(this.btnMsgBox);
			this.Controls.Add(this.btnModaless);
			this.Controls.Add(this.btnModal);
			this.Controls.Add(this.grpForm);
			this.Controls.Add(this.pgDummy);
			this.Controls.Add(this.tbDummy);
			this.Controls.Add(this.grpBar);
			this.Controls.Add(this.grpFont);
			this.Controls.Add(this.cboFont);
			this.Controls.Add(this.chkItalic);
			this.Controls.Add(this.chkBold);
			this.Controls.Add(this.txtSampleText);
			this.Controls.Add(this.lblFont);
			this.Name = "MainForm";
			this.Text = "Control Test";
			this.Load += new System.EventHandler(this.MainForm_Load);
			((System.ComponentModel.ISupportInitialize)(this.tbDummy)).EndInit();
			this.ResumeLayout(false);
			this.PerformLayout();

		}

		#endregion

		private System.Windows.Forms.Label lblFont;
		private System.Windows.Forms.TextBox txtSampleText;
		private System.Windows.Forms.CheckBox chkBold;
		private System.Windows.Forms.CheckBox chkItalic;
		private System.Windows.Forms.ComboBox cboFont;
		private System.Windows.Forms.GroupBox grpFont;
		private System.Windows.Forms.GroupBox grpBar;
		private System.Windows.Forms.TrackBar tbDummy;
		private System.Windows.Forms.ProgressBar pgDummy;
		private System.Windows.Forms.GroupBox grpForm;
		private System.Windows.Forms.Button btnModal;
		private System.Windows.Forms.Button btnModaless;
		private System.Windows.Forms.Button btnMsgBox;
		private System.Windows.Forms.GroupBox grpTreeList;
		private System.Windows.Forms.TreeView tvDummy;
		private System.Windows.Forms.ListView lvDummy;
		private System.Windows.Forms.Button btnAddRoot;
		private System.Windows.Forms.Button btnAddChild;
	}
}

