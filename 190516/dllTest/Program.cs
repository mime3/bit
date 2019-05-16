using System;
using static System.Console;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using ClassLibrary1;
using DemoLib;

namespace dllTest
{
	class Program
	{
		static void Main(string[] args)
		{
			Member member = new Member("홍길동", "대한민국");
			Console.WriteLine("이름:{0} 주소:{1}", member.Name, member.Addr);

			DemoClass dc = new DemoClass();
			dc.foo();

			ReadKey();
		}
	}
}
