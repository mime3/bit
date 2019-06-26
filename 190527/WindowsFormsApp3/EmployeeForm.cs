using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Forms;

namespace WindowsFormsApp3
{
	public partial class EmployeeForm : Form
	{
		public EmployeeForm()
		{
			InitializeComponent();

			lvEmployee.View = View.Details;
			lvEmployee.BeginUpdate();
			lvEmployee.Columns.Add("Employee_ID", -2);
			lvEmployee.Columns.Add("First_Name", -2);
			lvEmployee.Columns.Add("Last_Name", -2);
			lvEmployee.Columns.Add("Email", 100);
			lvEmployee.Columns.Add("Phone_Number", 100);
			lvEmployee.Columns.Add("Hire_Date", 100);
			lvEmployee.Columns.Add("Job_ID", 100);
			lvEmployee.Columns.Add("Salary", -2);
			lvEmployee.Columns.Add("Commission_PCT", -2);
			lvEmployee.Columns.Add("Manager_ID", -2);
			lvEmployee.Columns.Add("Department_ID", -2);
			lvEmployee.EndUpdate();
		}

		private void BtnSelect_Click(object sender, EventArgs e)
		{
			Employee employee = new Employee();
			employee = HrDAC.Instance.GetEmployee(long.Parse(txtEmployeeID.Text));

			txtFirstName.Text = employee.First_Name;
			txtLastName.Text = employee.Last_Name;
			txtEmail.Text = employee.Email;
			txtPhoneNumber.Text = employee.Phone_Number;
			txtHireDate.Text = employee.Hire_Date.ToShortTimeString();
			txtJobID.Text = employee.Job_ID;
			txtSalary.Text = employee.Salary.ToString();
			txtCommisssion.Text = employee.Commission.ToString();
			txtManagerID.Text = employee.Manager_ID.ToString();
			txtDepartmentID.Text = employee.Department_ID.ToString();
		}

		private void BtnAllSelect_Click(object sender, EventArgs e)
		{
			lvEmployee.BeginUpdate();
			lvEmployee.Items.Clear();
			List<Employee> employees = HrDAC.Instance.GetEmployees();
			foreach(Employee emp in employees)
			{
				ListViewItem item = new ListViewItem(emp.Employee_ID.ToString());
				//item.SubItems.Add(emp.Employee_ID.ToString());
				item.SubItems.Add(emp.First_Name);
				item.SubItems.Add(emp.Last_Name);
				item.SubItems.Add(emp.Email);
				item.SubItems.Add(emp.Phone_Number);
				item.SubItems.Add(emp.Hire_Date.ToShortTimeString());
				item.SubItems.Add(emp.Job_ID);
				item.SubItems.Add(emp.Salary.ToString());
				item.SubItems.Add(emp.Commission.ToString());
				item.SubItems.Add(emp.Manager_ID.ToString());
				item.SubItems.Add(emp.Department_ID.ToString());
				lvEmployee.Items.Add(item);
			}
			lvEmployee.EndUpdate();
		}
	}
}
