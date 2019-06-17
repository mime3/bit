using System;
using System.Collections.Generic;
using System.Globalization;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Data;

namespace _190603
{
	[ValueConversion(typeof(DateTime), typeof(String))]
	class Converter : IValueConverter
	{
		public object Convert(object value, Type targetType, object parameter, CultureInfo culture)
		{
			DateTime ret = (DateTime)value;
			return ret.ToShortDateString();
		}

		public object ConvertBack(object value, Type targetType, object parameter, CultureInfo culture)
		{
			string ret = value as string;
			DateTime result;
			if (DateTime.TryParse(ret, out result))
				return result;
			return 0;
		}
	}
}
