using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace _190603_2
{
	class Employee
	{
		public long Employee_ID { get; set; }
		public string First_Name { get; set; }
		public string Last_Name { get; set; }
		public string Email { get; set; }
		public string Phone_Number { get; set; }
		public DateTime Hire_Date { get; set; }
		public string Job_ID { get; set; }
		public double Salary { get; set; }
		public double Commission { get; set; }
		public long Manager_ID { get; set; }
		public int Department_ID { get; set; }
	}
}
