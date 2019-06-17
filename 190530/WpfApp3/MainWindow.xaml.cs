using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows;
using System.Windows.Controls;
using System.Windows.Data;
using System.Windows.Documents;
using System.Windows.Input;
using System.Windows.Media;
using System.Windows.Media.Imaging;
using System.Windows.Navigation;
using System.Windows.Shapes;

namespace WpfApp3
{
	/// <summary>
	/// MainWindow.xaml에 대한 상호 작용 논리
	/// </summary>
	public partial class MainWindow : Window
	{
		public MainWindow()
		{
			InitializeComponent();
		}

		private void Button_Click(object sender, RoutedEventArgs e)
		{
			Close();
		}

		private void Get_Emp(object sender, RoutedEventArgs e)
		{
			long id;
			if(long.TryParse(Employee_ID.Text, out id))
			{
				try
				{
					GridEmployee.DataContext = HrDAC.Instance.GetEmployee(id);
				}
				catch
				{
					MessageBox.Show("Error contacting database");
				}
			}
			else
			{
				MessageBox.Show("Invalil ID");
			}

			/*
			Employee employee = new Employee();
			employee = HrDAC.Instance.GetEmployee(long.Parse(Employee_ID.Text));

			First_Name.Text = employee.First_Name;
			Last_Name.Text = employee.Last_Name;
			Email.Text = employee.Email;
			Phone_Number.Text = employee.Phone_Number;
			Hire_Date.Text = employee.Hire_Date.ToShortTimeString();
			Job_ID.Text = employee.Job_ID;
			Salary.Text = employee.Salary.ToString();
			Commission_PCT.Text = employee.Commission.ToString();
			Manager_ID.Text = employee.Manager_ID.ToString();
			Department_ID.Text = employee.Department_ID.ToString();
			*/
		}
	}
}
