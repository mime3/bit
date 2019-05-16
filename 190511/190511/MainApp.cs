using System;
using static System.Console;
using System.Globalization;
using System.Collections;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace _190511
{
    class MainApp
    {
        enum COLOR_CODE
        {
            RED = 10,
            BLUE,
            GREEN,
            ORANGE = 100
        }

        static void Divide(int a, int b, out int quotient, out int remainder)
        {
            quotient = a / b;
            remainder = a % b;
        }
        static void Swap(ref int a, ref int b)
        {
            int temp = b;
            b = a;
            a = temp;
        }
        static void Main(string[] args)
        {
            //Console.WriteLine("Hello World!");
            //WriteLine("Hello World!");
            //int e = -10_000_000;
            //uint f = 300_000_000;
            //WriteLine($"e={e}, f={f}");
            //WriteLine("e={0}, f={1}", e, f);


            //float a = 3.1415_9265_7932_3846_2643_3832_79f;
            //double b = 3.1415_9265_7932_3846_2643_3832_79;
            //decimal c = 3.1415_9265_7932_3846_2643_3832_79m;
            //WriteLine(a);
            //WriteLine(b);
            //WriteLine(c);

            //string a1 = "독도는 우리땅";
            //string b1 = "대마도도 우리땅";
            //WriteLine(a1);
            //WriteLine(b1);

            //object a2 = 123;
            //object b2 = 3.14159m;
            //object c2 = true;
            //object d2 = "문자열";
            //WriteLine(a2);
            //WriteLine(b2);
            //WriteLine(c2);
            //WriteLine(d2);

            //int a3 = 123;
            //string b3 = a3.ToString();
            //WriteLine(b3);
            //float c3 = 3.14f;
            //string d3 = c3.ToString();
            //WriteLine(d3);
            //string e3 = "123456";
            //int f3 = int.Parse(e3);
            //WriteLine(f3);
            //string g3 = "1.2345";
            //float h3 = float.Parse(g3);
            //WriteLine(h3);

            //const int MAX_INT = 2147483647;
            //const int MIN_INT = -2147483648;

            //WriteLine((int)COLOR_CODE.RED);
            //WriteLine((int)COLOR_CODE.BLUE);
            //WriteLine(COLOR_CODE.GREEN);
            //WriteLine(COLOR_CODE.ORANGE);
            //COLOR_CODE code = COLOR_CODE.RED;
            //WriteLine(code == COLOR_CODE.BLUE);
            //WriteLine(code == COLOR_CODE.RED);
            //WriteLine((int)COLOR_CODE.GREEN);
            //WriteLine(value: (int)COLOR_CODE.ORANGE);

            //int? a4 = null;
            //WriteLine(a4.HasValue);
            //WriteLine(a4 != null);
            //a4 = 3;
            //WriteLine(a4.HasValue);
            //WriteLine(a4 != null);
            //WriteLine(a4.Value);
            //WriteLine(a4);

            //var a5 = 20;
            //WriteLine("Typr: {0}, Value: {1}", a5.GetType(), a5);

            //var b5 = 3.141592;
            //WriteLine("Typr: {0}, Value: {1}", b5.GetType(), b5);

            //var c5 = "Hello World";
            //WriteLine("Typr: {0}, Value: {1}", c5.GetType(), c5);

            //var d5 = new int[] { 10, 20, 30 };
            //Write("Typr: {0}, Value: ", d5.GetType());

            //foreach (var e5 in d5)
            //{
            //    Write("{0} ", e5);
            //}
            //WriteLine();

            //string str = "This is string sample";
            //WriteLine();
            //WriteLine(str);
            //WriteLine();

            //WriteLine("Index of 'search' : {0}", str.IndexOf("search"));
            //WriteLine("Index of 'h' : {0}", str.IndexOf('h'));
            //WriteLine("StartWith 'This' : {0}", str.StartsWith("This"));
            //WriteLine("StartWith 'string' : {0}", str.StartsWith("string"));
            //WriteLine("EndWith 'This' : {0}", str.EndsWith("This"));
            //WriteLine("EndWith 'sample' : {0}", str.EndsWith("sample"));
            //WriteLine("Contains 'search' : {0}", str.EndsWith("search"));
            //WriteLine("Contains 'school' : {0}", str.EndsWith("school"));
            //WriteLine("Replace 'sample' with 'example' : {0}", str.Replace("sample", "example"));

            //WriteLine("ToLower() : {0}", "Hello World".ToLower());
            //WriteLine("ToUpper() : {0}", "Hello World".ToUpper());
            //WriteLine("Insert() : {0}", "Hello World".Insert(6, "Wonderful "));
            //WriteLine("Remove() : {0}", "Hello Wonderful World".Remove(6, 10));
            //WriteLine("Trim() : {0}", " I am Tom ".Trim());
            //WriteLine("TrimStart() : {0}", " I am Tom ".TrimStart());
            //WriteLine("TrimEnd() : {0}", " I am Tom ".TrimEnd());

            //string str2 = "Welcome to the C# world";
            //WriteLine(str2.Substring(15, 2));
            //WriteLine(str2.Substring(8));
            //WriteLine();

            //string[] arr = str2.Split(new string[] { " " }, StringSplitOptions.RemoveEmptyEntries);
            //WriteLine("Word Count : {0}", arr.Length);

            //foreach (string element in arr)
            //    WriteLine("{0}", element);

            //string fmt = "{0,-10}{1,-5}{2,10}";

            //WriteLine(fmt, "Type", "Size", "Explain");
            //WriteLine(fmt, "byte", "1", "byte타입");
            //WriteLine(fmt, "short", "2", "short타입");
            //WriteLine(fmt, "int", "4", "int타입");
            //WriteLine(fmt, "long", "8", "long타입");

            //WriteLine("10진수: {0:D}", 123);
            //WriteLine("10진수: {0:D5}", 123);
            //WriteLine("16진수: {0:X}", 0xFF1234);
            //WriteLine("16진수: {0:X8}", 0xFF1234);
            //WriteLine("숫자: {0:N}", 123456);
            //WriteLine("숫자: {0:N0}", 123456);
            //WriteLine("고정소수점: {0:F}", 123.456);
            //WriteLine("고정소수점: {0:F5}", 123.456);
            //WriteLine("공학: {0:E}", 123.456789);

            //DateTime dt = DateTime.Now;

            //WriteLine("12시간 형식: {0:yyyy-MM-dd tt hh:mm:ss (ddd)}", dt);
            //WriteLine("24시간 형식: {0:yyyy-MM-dd HH:mm:ss (dddd)}", dt);

            //CultureInfo ciKR = new CultureInfo("ko-KR");
            //WriteLine();
            //WriteLine(dt.ToString("yyyy-MM-dd tt hh:mm:ss (ddd)", ciKR));
            //WriteLine(dt.ToString("yyyy-MM-dd HH:mm:ss (dddd)", ciKR));
            //WriteLine(dt.ToString(ciKR));
            //CultureInfo ciUS = new CultureInfo("en-US");
            //WriteLine();
            //WriteLine(dt.ToString("yyyy-MM-dd tt hh:mm:ss (ddd)", ciUS));
            //WriteLine(dt.ToString("yyyy-MM-dd HH:mm:ss (dddd)", ciUS));
            //WriteLine(dt.ToString(ciUS));

            //string name = "홍길동";
            //int age = 25;
            //WriteLine($"{name,-10}, {age:D3}");
            //name = "김유신";
            //age = 30;
            //WriteLine($"{name}, {age, -10:D3}");
            //name = "박문수";
            //age = 15;
            //WriteLine($"{name}, {(age > 20 ? "성인" : "미성년자")}");

            //ArrayList arrList = null;
            //arrList?.Add("C++");
            //arrList?.Add("C#");
            //WriteLine($"Count : {arrList?.Count}");
            //WriteLine($"{arrList?[0]}");
            //WriteLine($"{arrList?[1]}");

            //arrList = new ArrayList();
            //arrList?.Add("C++");
            //arrList?.Add("C#");
            //WriteLine($"Count : {arrList?.Count}");
            //WriteLine($"{arrList?[0]}");
            //WriteLine($"{arrList?[1]}");

            //int? num = null;
            //WriteLine($"{num ?? 0}");
            //num = 10;
            //WriteLine($"{num ?? 0}");
            //string str3 = null;
            //WriteLine($"{str3 ?? "Default"}");
            //str3 = "I study C#";
            //WriteLine($"{str3 ?? "Default"}");

            //Write("요일을 입력하세요 (월화수목금토) :");
            //string day = ReadLine();

            //switch (day)
            //{
            //    case "일":
            //        WriteLine("Sunday");
            //        break;
            //    case "월":
            //        WriteLine("Monday");
            //        break;
            //    case "화":
            //        WriteLine("Tuesday");
            //        break;
            //    case "수":
            //        WriteLine("Wednesday");
            //        break;
            //    case "목":
            //        WriteLine("Thurday");
            //        break;
            //    case "금":
            //        WriteLine("Friday");
            //        break;
            //    case "토":
            //        WriteLine("Saturday");
            //        break;
            //    default:
            //        WriteLine("요일이 아니라구");
            //        break;
            //}

            //object obj = null;
            //string str4 = ReadLine();
            //if (int.TryParse(str4, out int int_num))
            //    obj = int_num;
            //else if (float.TryParse(str4, out float float_num))
            //    obj = float_num;
            //else
            //    obj = str4;

            //switch (obj)
            //{
            //    case int i_obj:
            //        WriteLine($"{i_obj}는 int 형식");
            //        break;
            //    case float f_obj:
            //        WriteLine($"{f_obj}는 float 형식");
            //        break;
            //    default:
            //        WriteLine($"{obj}는 object 형식");
            //        break;
            //}

            //int[] arr2 = new int[] { 0, 1, 2, 3, 4 };
            //foreach (int i in arr2)
            //    WriteLine(i);

            int result = Calculator.Plus(2, 5);
            WriteLine(result);
            result = Calculator.Minus(10, 4);
            WriteLine(result);

            int x = 3;
            int y = 5;

            WriteLine($"x:{x}, y:{y}");
            Swap(ref x, ref y);
            WriteLine($"x:{x}, y:{y}");


            Product carrot = new Product();
            ref int ref_price = ref carrot.GetPrice();
            int normal_price = carrot.GetPrice();

            carrot.PrintPrice();
            WriteLine($"Ref Pirce : {ref_price}");
            WriteLine($"Normal Pirce : {normal_price}");

            ref_price = 200;
            carrot.PrintPrice();
            WriteLine($"Ref Pirce : {ref_price}");
            WriteLine($"Normal Pirce : {normal_price}");

            int a = 20;
            int b = 3;
            int c;
            int d;
            Divide(a, b, out c, out d);

            WriteLine($"a:{a}, b:{b}, a/b:{c}, a%b:{d}");
        }
    }
    class Calculator
    {
        public static int Plus(int a, int b)
        {
            return a + b;
        }
        public static int Minus(int a, int b)
        {
            return a - b;
        }
    }

    class Product
    {
        private int price = 100;

        public ref int GetPrice()
        {
            return ref price;
        }
        public void PrintPrice()
        {
            WriteLine($"Price : {price}");
        }
    }
}
