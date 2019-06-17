using System;
using System.Collections.Generic;
using System.Data;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using Oracle.ManagedDataAccess.Client;

namespace _190603_2
{
	class HrDAC
	{
		private string _connectionString;
		private static readonly HrDAC instance = new HrDAC();
		private HrDAC()
		{
            //_connectionString = Properties.Settings.Default.ConnectionInfo;
            _connectionString = "DATA SOURCE=XE; User Id=c##hr;Password=tiger";
        }
		public static HrDAC Instance
		{ get { return instance; } }
		public Employee GetEmployee(long id)
		{
			Employee employee = new Employee();
			string sql =
				"SELECT EMPLOYEE_ID, FIRST_NAME, LAST_NAME, EMAIL" +
				", PHONE_NUMBER, HIRE_DATE, JOB_ID, SALARY, COMMISSION_PCT" +
				", MANAGER_ID, DEPARTMENT_ID FROM EMPLOYEES WHERE EMPLOYEE_ID = :EMPLOYEE_ID";
			using (OracleConnection conn = new OracleConnection(_connectionString))
			{
				OracleCommand cmd = new OracleCommand(sql, conn)
				{
					CommandType = CommandType.Text,
					BindByName = true
				};
				cmd.Parameters.Add(":EMPLOYEE_ID", OracleDbType.Long).Value = id;
				conn.Open();

				using (OracleDataReader reader = cmd.ExecuteReader(CommandBehavior.SingleRow))
				{
					if(reader.Read())
					{
						employee.Employee_ID = reader.GetInt64(reader.GetOrdinal("EMPLOYEE_ID"));
						employee.First_Name = reader.GetString(reader.GetOrdinal("FIRST_NAME"));
						employee.Last_Name = reader.GetString(reader.GetOrdinal("LAST_NAME"));
						employee.Email = reader.GetString(reader.GetOrdinal("EMAIL"));
						employee.Phone_Number = reader.GetString(reader.GetOrdinal("PHONE_NUMBER"));

						employee.Hire_Date = reader.GetDateTime(reader.GetOrdinal("HIRE_DATE"));
						employee.Job_ID = reader.GetString(reader.GetOrdinal("JOB_ID"));
						employee.Salary = reader.GetDouble(reader.GetOrdinal("SALARY"));
						employee.Commission = reader.IsDBNull(reader.GetOrdinal("COMMISSION_PCT")) ? 0.0 : reader.GetDouble(reader.GetOrdinal("COMMISSION_PCT"));
						employee.Manager_ID = reader.IsDBNull(reader.GetOrdinal("MANAGER_ID")) ? 0 : reader.GetInt64(reader.GetOrdinal("MANAGER_ID"));
						employee.Department_ID = reader.IsDBNull(reader.GetOrdinal("DEPARTMENT_ID")) ? 0 : reader.GetInt32(reader.GetOrdinal("DEPARTMENT_ID")); ;
					}
				}
				return employee;
			}
		}
		
		public List<Employee> GetEmployees()
		{
			List<Employee> employees = new List<Employee>();
			string sql =
				"SELECT EMPLOYEE_ID, FIRST_NAME, LAST_NAME, EMAIL" +
				", PHONE_NUMBER, HIRE_DATE, JOB_ID, SALARY, COMMISSION_PCT" +
				", MANAGER_ID, DEPARTMENT_ID FROM EMPLOYEES";

			using (OracleConnection conn = new OracleConnection(_connectionString))
			{
				OracleCommand cmd = new OracleCommand(sql, conn)
				{
					CommandType = CommandType.Text,
					BindByName = true
				};

				conn.Open();
				using (OracleDataReader reader = cmd.ExecuteReader(CommandBehavior.Default))
				{
					while (reader.Read())
					{
						Employee employee = new Employee();
						employee.Employee_ID = reader.GetInt64(reader.GetOrdinal("EMPLOYEE_ID"));
						employee.First_Name = reader.GetString(reader.GetOrdinal("FIRST_NAME"));
						employee.Last_Name = reader.GetString(reader.GetOrdinal("LAST_NAME"));
						employee.Email = reader.GetString(reader.GetOrdinal("EMAIL"));
						employee.Phone_Number = reader.GetString(reader.GetOrdinal("PHONE_NUMBER"));

						employee.Hire_Date = reader.GetDateTime(reader.GetOrdinal("HIRE_DATE"));
						employee.Job_ID = reader.GetString(reader.GetOrdinal("JOB_ID"));
						employee.Salary = reader.GetDouble(reader.GetOrdinal("SALARY"));
						employee.Commission = reader.IsDBNull(reader.GetOrdinal("COMMISSION_PCT")) ? 0.0 : reader.GetDouble(reader.GetOrdinal("COMMISSION_PCT"));
						employee.Manager_ID = reader.IsDBNull(reader.GetOrdinal("MANAGER_ID")) ? 0 : reader.GetInt64(reader.GetOrdinal("MANAGER_ID"));
						employee.Department_ID = reader.IsDBNull(reader.GetOrdinal("DEPARTMENT_ID")) ? 0 : reader.GetInt32(reader.GetOrdinal("DEPARTMENT_ID")); ;
						employees.Add(employee);
					}
				}
			}
			return employees;
		}
	}
}
