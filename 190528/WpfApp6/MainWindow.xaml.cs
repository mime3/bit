﻿using System;
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

namespace WpfApp6
{
	/// <summary>
	/// MainWindow.xaml에 대한 상호 작용 논리
	/// </summary>
	public partial class MainWindow : Window
	{
		public MainWindow()
		{
			InitializeComponent();
			AddHandler(CheckBox.CheckedEvent, new RoutedEventHandler(chk_Checked));
			AddHandler(CheckBox.UncheckedEvent, new RoutedEventHandler(chk_Unchecked));
		}


		private void chk_Checked(object sender, RoutedEventArgs e)
		{
			CheckBox chk = (CheckBox)e.OriginalSource;
			DependencyObject obj = LogicalTreeHelper.FindLogicalNode(this, chk.Content.ToString());
			((FrameworkElement)obj).Visibility = Visibility.Visible;
		}

		private void chk_Unchecked(object sender, RoutedEventArgs e)
		{
			CheckBox chk = (CheckBox)e.OriginalSource;
			DependencyObject obj = LogicalTreeHelper.FindLogicalNode(this, chk.Content.ToString());
			((FrameworkElement)obj).Visibility = Visibility.Collapsed;
		}
	}
}
