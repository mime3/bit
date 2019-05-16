using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace ClassLibrary1
{
    public class Member
    {
		MemberInfo mi = null;


		public string Name
		{
			get
			{
				return mi.Name;
			}
		}
		public string Addr
		{
			get
			{
				return mi.Addr;
			}
		}

		public Member(string name, string addr)
		{
			mi = new MemberInfo(name, addr);
		}

		public override string ToString()
		{
			return mi.ToString();
		}
	}

	class MemberInfo
	{
		internal string Name
		{
			get;
			private set;
		}
		internal string Addr
		{
			get;
			private set;
		}

		internal MemberInfo(string name, string addr)
		{
			Name = name;
			Addr = addr;
		}

		public override string ToString()
		{
			return Name;
		}
	}
}
