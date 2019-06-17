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

namespace _190603_2
{
    /// <summary>
    /// MainWindow.xaml에 대한 상호 작용 논리
    /// </summary>
    public partial class MainWindow : Window
    {
        private List<Employee> employees = new List<Employee>();
        public MainWindow()
        {
            InitializeComponent();
        }

        private void cmdGetEmployees_click(object sender, RoutedEventArgs e)
        {
            employees = HrDAC.Instance.GetEmployees();
            gridEmployees.ItemsSource = employees;
        }
    }
}
