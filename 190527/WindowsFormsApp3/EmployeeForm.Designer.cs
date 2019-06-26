namespace WindowsFormsApp3
{
	partial class EmployeeForm
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
			this.btnSelect = new System.Windows.Forms.Button();
			this.groupBox1 = new System.Windows.Forms.GroupBox();
			this.txtEmployeeID = new System.Windows.Forms.TextBox();
			this.label1 = new System.Windows.Forms.Label();
			this.label2 = new System.Windows.Forms.Label();
			this.label3 = new System.Windows.Forms.Label();
			this.label4 = new System.Windows.Forms.Label();
			this.label5 = new System.Windows.Forms.Label();
			this.label6 = new System.Windows.Forms.Label();
			this.label7 = new System.Windows.Forms.Label();
			this.label8 = new System.Windows.Forms.Label();
			this.label9 = new System.Windows.Forms.Label();
			this.label10 = new System.Windows.Forms.Label();
			this.label11 = new System.Windows.Forms.Label();
			this.groupBox2 = new System.Windows.Forms.GroupBox();
			this.txtManagerID = new System.Windows.Forms.TextBox();
			this.txtDepartmentID = new System.Windows.Forms.TextBox();
			this.txtCommisssion = new System.Windows.Forms.TextBox();
			this.txtPhoneNumber = new System.Windows.Forms.TextBox();
			this.txtSalary = new System.Windows.Forms.TextBox();
			this.txtEmail = new System.Windows.Forms.TextBox();
			this.txtHireDate = new System.Windows.Forms.TextBox();
			this.txtJobID = new System.Windows.Forms.TextBox();
			this.txtLastName = new System.Windows.Forms.TextBox();
			this.txtFirstName = new System.Windows.Forms.TextBox();
			this.button1 = new System.Windows.Forms.Button();
			this.lvEmployee = new System.Windows.Forms.ListView();
			this.btnAllSelect = new System.Windows.Forms.Button();
			this.groupBox1.SuspendLayout();
			this.groupBox2.SuspendLayout();
			this.SuspendLayout();
			// 
			// btnSelect
			// 
			this.btnSelect.Location = new System.Drawing.Point(759, 29);
			this.btnSelect.Name = "btnSelect";
			this.btnSelect.Size = new System.Drawing.Size(74, 60);
			this.btnSelect.TabIndex = 0;
			this.btnSelect.Text = "조회";
			this.btnSelect.UseVisualStyleBackColor = true;
			this.btnSelect.Click += new System.EventHandler(this.BtnSelect_Click);
			// 
			// groupBox1
			// 
			this.groupBox1.Controls.Add(this.txtEmployeeID);
			this.groupBox1.Controls.Add(this.label1);
			this.groupBox1.Location = new System.Drawing.Point(17, 29);
			this.groupBox1.Name = "groupBox1";
			this.groupBox1.Size = new System.Drawing.Size(722, 60);
			this.groupBox1.TabIndex = 1;
			this.groupBox1.TabStop = false;
			this.groupBox1.Text = "[조회]";
			// 
			// txtEmployeeID
			// 
			this.txtEmployeeID.Location = new System.Drawing.Point(107, 21);
			this.txtEmployeeID.Name = "txtEmployeeID";
			this.txtEmployeeID.Size = new System.Drawing.Size(157, 21);
			this.txtEmployeeID.TabIndex = 1;
			// 
			// label1
			// 
			this.label1.AutoSize = true;
			this.label1.Location = new System.Drawing.Point(15, 26);
			this.label1.Name = "label1";
			this.label1.Size = new System.Drawing.Size(85, 12);
			this.label1.TabIndex = 0;
			this.label1.Text = "Employee ID :";
			// 
			// label2
			// 
			this.label2.AutoSize = true;
			this.label2.Location = new System.Drawing.Point(24, 15);
			this.label2.Name = "label2";
			this.label2.Size = new System.Drawing.Size(71, 12);
			this.label2.TabIndex = 2;
			this.label2.Text = "First Name:";
			// 
			// label3
			// 
			this.label3.AutoSize = true;
			this.label3.Location = new System.Drawing.Point(362, 15);
			this.label3.Name = "label3";
			this.label3.Size = new System.Drawing.Size(41, 12);
			this.label3.TabIndex = 3;
			this.label3.Text = "Email:";
			// 
			// label4
			// 
			this.label4.AutoSize = true;
			this.label4.Location = new System.Drawing.Point(192, 15);
			this.label4.Name = "label4";
			this.label4.Size = new System.Drawing.Size(71, 12);
			this.label4.TabIndex = 4;
			this.label4.Text = "Last Name:";
			// 
			// label5
			// 
			this.label5.AutoSize = true;
			this.label5.Location = new System.Drawing.Point(532, 15);
			this.label5.Name = "label5";
			this.label5.Size = new System.Drawing.Size(94, 12);
			this.label5.TabIndex = 5;
			this.label5.Text = "Phone Number:";
			// 
			// label6
			// 
			this.label6.AutoSize = true;
			this.label6.Location = new System.Drawing.Point(532, 60);
			this.label6.Name = "label6";
			this.label6.Size = new System.Drawing.Size(110, 12);
			this.label6.TabIndex = 6;
			this.label6.Text = "Commission PCT:";
			// 
			// label7
			// 
			this.label7.AutoSize = true;
			this.label7.Location = new System.Drawing.Point(192, 60);
			this.label7.Name = "label7";
			this.label7.Size = new System.Drawing.Size(44, 12);
			this.label7.TabIndex = 7;
			this.label7.Text = "Job ID:";
			// 
			// label8
			// 
			this.label8.AutoSize = true;
			this.label8.Location = new System.Drawing.Point(24, 60);
			this.label8.Name = "label8";
			this.label8.Size = new System.Drawing.Size(60, 12);
			this.label8.TabIndex = 8;
			this.label8.Text = "Hire Date:";
			// 
			// label9
			// 
			this.label9.AutoSize = true;
			this.label9.Location = new System.Drawing.Point(362, 60);
			this.label9.Name = "label9";
			this.label9.Size = new System.Drawing.Size(45, 12);
			this.label9.TabIndex = 9;
			this.label9.Text = "Salary:";
			// 
			// label10
			// 
			this.label10.AutoSize = true;
			this.label10.Location = new System.Drawing.Point(713, 60);
			this.label10.Name = "label10";
			this.label10.Size = new System.Drawing.Size(74, 12);
			this.label10.TabIndex = 10;
			this.label10.Text = "Manager ID:";
			// 
			// label11
			// 
			this.label11.AutoSize = true;
			this.label11.Location = new System.Drawing.Point(713, 15);
			this.label11.Name = "label11";
			this.label11.Size = new System.Drawing.Size(88, 12);
			this.label11.TabIndex = 11;
			this.label11.Text = "Department ID:";
			// 
			// groupBox2
			// 
			this.groupBox2.Controls.Add(this.txtManagerID);
			this.groupBox2.Controls.Add(this.txtDepartmentID);
			this.groupBox2.Controls.Add(this.txtCommisssion);
			this.groupBox2.Controls.Add(this.txtPhoneNumber);
			this.groupBox2.Controls.Add(this.txtSalary);
			this.groupBox2.Controls.Add(this.txtEmail);
			this.groupBox2.Controls.Add(this.txtHireDate);
			this.groupBox2.Controls.Add(this.txtJobID);
			this.groupBox2.Controls.Add(this.txtLastName);
			this.groupBox2.Controls.Add(this.label11);
			this.groupBox2.Controls.Add(this.label10);
			this.groupBox2.Controls.Add(this.label9);
			this.groupBox2.Controls.Add(this.label8);
			this.groupBox2.Controls.Add(this.txtFirstName);
			this.groupBox2.Controls.Add(this.label7);
			this.groupBox2.Controls.Add(this.label6);
			this.groupBox2.Controls.Add(this.label5);
			this.groupBox2.Controls.Add(this.label4);
			this.groupBox2.Controls.Add(this.label3);
			this.groupBox2.Controls.Add(this.label2);
			this.groupBox2.Location = new System.Drawing.Point(18, 95);
			this.groupBox2.Name = "groupBox2";
			this.groupBox2.Size = new System.Drawing.Size(898, 105);
			this.groupBox2.TabIndex = 12;
			this.groupBox2.TabStop = false;
			this.groupBox2.Text = "[조회내용]";
			// 
			// txtManagerID
			// 
			this.txtManagerID.Location = new System.Drawing.Point(715, 75);
			this.txtManagerID.Name = "txtManagerID";
			this.txtManagerID.Size = new System.Drawing.Size(100, 21);
			this.txtManagerID.TabIndex = 14;
			// 
			// txtDepartmentID
			// 
			this.txtDepartmentID.Location = new System.Drawing.Point(715, 30);
			this.txtDepartmentID.Name = "txtDepartmentID";
			this.txtDepartmentID.Size = new System.Drawing.Size(100, 21);
			this.txtDepartmentID.TabIndex = 13;
			// 
			// txtCommisssion
			// 
			this.txtCommisssion.Location = new System.Drawing.Point(534, 75);
			this.txtCommisssion.Name = "txtCommisssion";
			this.txtCommisssion.Size = new System.Drawing.Size(100, 21);
			this.txtCommisssion.TabIndex = 12;
			// 
			// txtPhoneNumber
			// 
			this.txtPhoneNumber.Location = new System.Drawing.Point(534, 30);
			this.txtPhoneNumber.Name = "txtPhoneNumber";
			this.txtPhoneNumber.Size = new System.Drawing.Size(100, 21);
			this.txtPhoneNumber.TabIndex = 2;
			// 
			// txtSalary
			// 
			this.txtSalary.Location = new System.Drawing.Point(364, 75);
			this.txtSalary.Name = "txtSalary";
			this.txtSalary.Size = new System.Drawing.Size(100, 21);
			this.txtSalary.TabIndex = 5;
			// 
			// txtEmail
			// 
			this.txtEmail.Location = new System.Drawing.Point(364, 30);
			this.txtEmail.Name = "txtEmail";
			this.txtEmail.Size = new System.Drawing.Size(100, 21);
			this.txtEmail.TabIndex = 6;
			// 
			// txtHireDate
			// 
			this.txtHireDate.Location = new System.Drawing.Point(26, 75);
			this.txtHireDate.Name = "txtHireDate";
			this.txtHireDate.Size = new System.Drawing.Size(100, 21);
			this.txtHireDate.TabIndex = 7;
			// 
			// txtJobID
			// 
			this.txtJobID.Location = new System.Drawing.Point(194, 75);
			this.txtJobID.Name = "txtJobID";
			this.txtJobID.Size = new System.Drawing.Size(100, 21);
			this.txtJobID.TabIndex = 8;
			// 
			// txtLastName
			// 
			this.txtLastName.Location = new System.Drawing.Point(194, 30);
			this.txtLastName.Name = "txtLastName";
			this.txtLastName.Size = new System.Drawing.Size(100, 21);
			this.txtLastName.TabIndex = 3;
			// 
			// txtFirstName
			// 
			this.txtFirstName.Location = new System.Drawing.Point(26, 30);
			this.txtFirstName.Name = "txtFirstName";
			this.txtFirstName.Size = new System.Drawing.Size(100, 21);
			this.txtFirstName.TabIndex = 4;
			// 
			// button1
			// 
			this.button1.Location = new System.Drawing.Point(839, 66);
			this.button1.Name = "button1";
			this.button1.Size = new System.Drawing.Size(75, 23);
			this.button1.TabIndex = 13;
			this.button1.Text = "확인";
			this.button1.UseVisualStyleBackColor = true;
			// 
			// lvEmployee
			// 
			this.lvEmployee.Location = new System.Drawing.Point(18, 206);
			this.lvEmployee.Name = "lvEmployee";
			this.lvEmployee.Size = new System.Drawing.Size(898, 234);
			this.lvEmployee.TabIndex = 14;
			this.lvEmployee.UseCompatibleStateImageBehavior = false;
			// 
			// btnAllSelect
			// 
			this.btnAllSelect.Location = new System.Drawing.Point(839, 29);
			this.btnAllSelect.Name = "btnAllSelect";
			this.btnAllSelect.Size = new System.Drawing.Size(75, 23);
			this.btnAllSelect.TabIndex = 15;
			this.btnAllSelect.Text = "전체조회";
			this.btnAllSelect.UseVisualStyleBackColor = true;
			this.btnAllSelect.Click += new System.EventHandler(this.BtnAllSelect_Click);
			// 
			// EmployeeForm
			// 
			this.AutoScaleDimensions = new System.Drawing.SizeF(7F, 12F);
			this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
			this.ClientSize = new System.Drawing.Size(928, 491);
			this.Controls.Add(this.btnAllSelect);
			this.Controls.Add(this.lvEmployee);
			this.Controls.Add(this.button1);
			this.Controls.Add(this.groupBox2);
			this.Controls.Add(this.groupBox1);
			this.Controls.Add(this.btnSelect);
			this.Name = "EmployeeForm";
			this.Text = "직원조회";
			this.groupBox1.ResumeLayout(false);
			this.groupBox1.PerformLayout();
			this.groupBox2.ResumeLayout(false);
			this.groupBox2.PerformLayout();
			this.ResumeLayout(false);

		}

		#endregion

		private System.Windows.Forms.Button btnSelect;
		private System.Windows.Forms.GroupBox groupBox1;
		private System.Windows.Forms.TextBox txtEmployeeID;
		private System.Windows.Forms.Label label1;
		private System.Windows.Forms.Label label2;
		private System.Windows.Forms.Label label3;
		private System.Windows.Forms.Label label4;
		private System.Windows.Forms.Label label5;
		private System.Windows.Forms.Label label6;
		private System.Windows.Forms.Label label7;
		private System.Windows.Forms.Label label8;
		private System.Windows.Forms.Label label9;
		private System.Windows.Forms.Label label10;
		private System.Windows.Forms.Label label11;
		private System.Windows.Forms.GroupBox groupBox2;
		private System.Windows.Forms.TextBox txtManagerID;
		private System.Windows.Forms.TextBox txtDepartmentID;
		private System.Windows.Forms.TextBox txtCommisssion;
		private System.Windows.Forms.TextBox txtPhoneNumber;
		private System.Windows.Forms.TextBox txtSalary;
		private System.Windows.Forms.TextBox txtEmail;
		private System.Windows.Forms.TextBox txtHireDate;
		private System.Windows.Forms.TextBox txtJobID;
		private System.Windows.Forms.TextBox txtLastName;
		private System.Windows.Forms.TextBox txtFirstName;
		private System.Windows.Forms.Button button1;
		private System.Windows.Forms.ListView lvEmployee;
		private System.Windows.Forms.Button btnAllSelect;
	}
}

