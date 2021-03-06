﻿namespace WindowsFormsApp2
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
			this.btnFindSource = new System.Windows.Forms.Button();
			this.btnFindTarget = new System.Windows.Forms.Button();
			this.btnAsyncCopy = new System.Windows.Forms.Button();
			this.btnSyncCopy = new System.Windows.Forms.Button();
			this.btnCancel = new System.Windows.Forms.Button();
			this.pbCopy = new System.Windows.Forms.ProgressBar();
			this.lblSource = new System.Windows.Forms.Label();
			this.lblTarget = new System.Windows.Forms.Label();
			this.txtSource = new System.Windows.Forms.TextBox();
			this.txtTarget = new System.Windows.Forms.TextBox();
			this.SuspendLayout();
			// 
			// btnFindSource
			// 
			this.btnFindSource.Location = new System.Drawing.Point(300, 24);
			this.btnFindSource.Name = "btnFindSource";
			this.btnFindSource.Size = new System.Drawing.Size(75, 23);
			this.btnFindSource.TabIndex = 0;
			this.btnFindSource.Text = "...";
			this.btnFindSource.UseVisualStyleBackColor = true;
			this.btnFindSource.Click += new System.EventHandler(this.BtnFindSource_Click);
			// 
			// btnFindTarget
			// 
			this.btnFindTarget.Location = new System.Drawing.Point(300, 53);
			this.btnFindTarget.Name = "btnFindTarget";
			this.btnFindTarget.Size = new System.Drawing.Size(75, 23);
			this.btnFindTarget.TabIndex = 1;
			this.btnFindTarget.Text = "...";
			this.btnFindTarget.UseVisualStyleBackColor = true;
			this.btnFindTarget.Click += new System.EventHandler(this.BtnFindTarget_Click);
			// 
			// btnAsyncCopy
			// 
			this.btnAsyncCopy.Location = new System.Drawing.Point(22, 90);
			this.btnAsyncCopy.Name = "btnAsyncCopy";
			this.btnAsyncCopy.Size = new System.Drawing.Size(110, 31);
			this.btnAsyncCopy.TabIndex = 2;
			this.btnAsyncCopy.Text = "Async Copy";
			this.btnAsyncCopy.UseVisualStyleBackColor = true;
			this.btnAsyncCopy.Click += new System.EventHandler(this.BtnAsyncCopy_Click);
			// 
			// btnSyncCopy
			// 
			this.btnSyncCopy.Location = new System.Drawing.Point(138, 90);
			this.btnSyncCopy.Name = "btnSyncCopy";
			this.btnSyncCopy.Size = new System.Drawing.Size(110, 31);
			this.btnSyncCopy.TabIndex = 3;
			this.btnSyncCopy.Text = "Sync Copy";
			this.btnSyncCopy.UseVisualStyleBackColor = true;
			this.btnSyncCopy.Click += new System.EventHandler(this.BtnSyncCopy_Click);
			// 
			// btnCancel
			// 
			this.btnCancel.Location = new System.Drawing.Point(265, 90);
			this.btnCancel.Name = "btnCancel";
			this.btnCancel.Size = new System.Drawing.Size(110, 31);
			this.btnCancel.TabIndex = 4;
			this.btnCancel.Text = "Cancel";
			this.btnCancel.UseVisualStyleBackColor = true;
			this.btnCancel.Click += new System.EventHandler(this.BtnCancel_Click);
			// 
			// pbCopy
			// 
			this.pbCopy.Location = new System.Drawing.Point(22, 142);
			this.pbCopy.Name = "pbCopy";
			this.pbCopy.Size = new System.Drawing.Size(353, 27);
			this.pbCopy.TabIndex = 5;
			// 
			// lblSource
			// 
			this.lblSource.AutoSize = true;
			this.lblSource.Location = new System.Drawing.Point(20, 35);
			this.lblSource.Name = "lblSource";
			this.lblSource.Size = new System.Drawing.Size(45, 12);
			this.lblSource.TabIndex = 6;
			this.lblSource.Text = "Source";
			// 
			// lblTarget
			// 
			this.lblTarget.AutoSize = true;
			this.lblTarget.Location = new System.Drawing.Point(20, 64);
			this.lblTarget.Name = "lblTarget";
			this.lblTarget.Size = new System.Drawing.Size(41, 12);
			this.lblTarget.TabIndex = 7;
			this.lblTarget.Text = "Target";
			// 
			// txtSource
			// 
			this.txtSource.Location = new System.Drawing.Point(78, 25);
			this.txtSource.Name = "txtSource";
			this.txtSource.Size = new System.Drawing.Size(202, 21);
			this.txtSource.TabIndex = 8;
			// 
			// txtTarget
			// 
			this.txtTarget.Location = new System.Drawing.Point(78, 53);
			this.txtTarget.Name = "txtTarget";
			this.txtTarget.Size = new System.Drawing.Size(202, 21);
			this.txtTarget.TabIndex = 9;
			// 
			// MainForm
			// 
			this.AutoScaleDimensions = new System.Drawing.SizeF(7F, 12F);
			this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
			this.ClientSize = new System.Drawing.Size(800, 450);
			this.Controls.Add(this.txtTarget);
			this.Controls.Add(this.txtSource);
			this.Controls.Add(this.lblTarget);
			this.Controls.Add(this.lblSource);
			this.Controls.Add(this.pbCopy);
			this.Controls.Add(this.btnCancel);
			this.Controls.Add(this.btnSyncCopy);
			this.Controls.Add(this.btnAsyncCopy);
			this.Controls.Add(this.btnFindTarget);
			this.Controls.Add(this.btnFindSource);
			this.Name = "MainForm";
			this.Text = "Form1";
			this.ResumeLayout(false);
			this.PerformLayout();

		}

		#endregion

		private System.Windows.Forms.Button btnFindSource;
		private System.Windows.Forms.Button btnFindTarget;
		private System.Windows.Forms.Button btnAsyncCopy;
		private System.Windows.Forms.Button btnSyncCopy;
		private System.Windows.Forms.Button btnCancel;
		private System.Windows.Forms.ProgressBar pbCopy;
		private System.Windows.Forms.Label lblSource;
		private System.Windows.Forms.Label lblTarget;
		private System.Windows.Forms.TextBox txtSource;
		private System.Windows.Forms.TextBox txtTarget;
	}
}

