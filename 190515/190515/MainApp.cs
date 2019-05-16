using System;
using static System.Console;
using System.Collections;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace _190515
{
    delegate int Mydelegate(int a, int b);

    delegate int Compare<T>(T a, T b);

    delegate int Compare(int a, int b);

    delegate void OnlineShopping(string location);

    delegate void Notify(string message);

    delegate int Calculate(int a, int b);

    delegate void EventHandler(string message);

	delegate string Concatenate(string[] args);
    class MyNotifier
    {
        public event EventHandler DoAlarm;

        public void Get369(int num)
        {
            int temp = num % 10;
            if (temp != 0 && temp % 3 == 0)
                DoAlarm(String.Format("{0}: 짝", temp));
        }

    }
    class Calculator
    {
        public int Plus(int a, int b)
        {
            return a + b;
        }

        public int Minus(int a, int b)
        {
            return a - b;
        }
    }
    class InvaildArgmentException : Exception
    {
        public InvaildArgmentException() { }
        public InvaildArgmentException(string message) : base(message) { }

        public object Argment { get; set; }
        public string Range { get; set; }
    }
    class FilterableException : Exception
    {
        public int ErrorNo { get; set; }
    }
    class Notifier
    {
        public Notify EventOccured; // delegage 객체
    }
    class EventListener
    {
        private string name;
        public EventListener(string name)
        {
            this.name = name;
        }

        public void SomethingHappend(string message)
        {
            WriteLine($"{name}.SomethingHappend : {message}");
        }
    }

	class MyList : IEnumerable, IEnumerator
	{
		private int[] array;
		int position = -1;

		public MyList()
		{
			array = new int[3];
		}

		public int this[int index]
		{
			get
			{
				return array[index];
			}
			set
			{
				if (index >= array.Length)
				{
					Array.Resize(ref array, index + 1);
					WriteLine($"Array Resized : {array.Length}");
				}
				array[index] = value;
			}
		}

		public int Length
		{
			get
			{
				return array.Length;
			}
		}

		public object Current => array[position];

		public void Reset()
		{
			position = -1;
		}

		public bool MoveNext()
		{
			if(position == array.Length -1)
			{
				Reset();
				return false;
			}
			position++;
			return (position < array.Length);
		}

		public IEnumerator GetEnumerator()
		{
			for (int i = 0; i < array.Length; i++)
				yield return array[i];
		}
	}
	class MyEnumerator
	{
		private int[] numbers = { 1, 2, 3, 4 };

		public IEnumerator GetEnumerator()
		{
			yield return numbers[0];
			yield return numbers[1];
			yield return numbers[2];
			yield return numbers[3];
		}
	}

    class MainApp
    {
        static public void MyHandler(string message)
        {
            WriteLine(message);
        }
        static int AscendCompare<T>(T a, T b) where T : IComparable<T>
        {
            return a.CompareTo(b);
        }
        static int DecendCompare<T>(T a, T b) where T : IComparable<T>
        {
            return -AscendCompare(a, b);
        }
        //static void BubbleSort<T>(T[] dataSet, Compare<T> comparer)
        //{
        //    int i = 0;
        //    int j = 0;
        //    T temp;

        //    for (i = 0; i < dataSet.Length; i++)
        //    {
        //        for (j = 0; j < dataSet.Length - (i + 1); j++)
        //        {
        //            if (comparer(dataSet[j], dataSet[j + 1]) > 0)
        //            {
        //                temp = dataSet[j + 1];
        //                dataSet[j + 1] = dataSet[j];
        //                dataSet[j] = temp;
        //            }
        //        }
        //    }
        //}

        static void BubbleSort(int[] dataSet, Compare comparer)
        {
            int i = 0;
            int j = 0;
            int temp;

            for (i = 0; i < dataSet.Length; i++)
            {
                for (j = 0; j < dataSet.Length - (i + 1); j++)
                {
                    if (comparer(dataSet[j], dataSet[j + 1]) > 0)
                    {
                        temp = dataSet[j + 1];
                        dataSet[j + 1] = dataSet[j];
                        dataSet[j] = temp;
                    }
                }
            }
        }

        static void SimpleFunc(int arg)
        {
            if (arg <= 10)
                WriteLine($"arg: {arg}");
            else
                throw new Exception("인자값이 10보다 큽니다");
        }

        static int Divide(int divisor, int dividend)
        {
            try
            {
                WriteLine("시작");
                return divisor / dividend;
            }
            catch(DivideByZeroException e)
            {
                WriteLine("예외 발생");
                throw e;
            }
            finally
            {
                WriteLine("종료");
            }
        }

        static uint MergeARGB(uint alpah, uint red, uint green, uint blue)
        {
            uint[] args = new uint[] { alpah, red, green, blue };

            foreach(uint arg in args)
            {
                if (arg > 255)
                {
                    throw new InvaildArgmentException()
                    {
                        Argment = arg,
                        Range = "0~255"
                    };
                }
            }
            return (alpah << 24 & 0xFF000000) | (red << 16 & 0x00FF0000) | (green << 8 & 0x0000FF00) | (blue & 0x000000FF);
        }

        static void OrderGoods(string location)
        {
            WriteLine($"장바구니내 물건을 {location}으로 가져다 주세요");
        }

        static void SpecialOrder(string location)
        {
            WriteLine($"{location}에 사람이 없으면 문앞에 두시고 문자 주세요");
        }
        static void Main(string[] args)
        {
			//List<int> list = new List<int>();
			//for (int i = 0; i < 5; i++)
			//    list.Add(i);

			//foreach (int i in list)
			//    Write($"{i} ");
			//WriteLine();

			//list.RemoveAt(2);

			//foreach (int i in list)
			//    Write($"{i} ");
			//WriteLine();

			//list.Insert(2, 2);

			//foreach (int i in list)
			//    Write($"{i} ");
			//WriteLine();


			//Dictionary<string, int> dic = new Dictionary<string, int>();
			//dic["국어"] = 90;
			//dic["영어"] = 85;
			//dic["수학"] = 95;
			//dic["물리"] = 100;
			//dic["화학"] = 95;

			//foreach (KeyValuePair<string, int> item in dic)
			//    WriteLine($"{item.Key} : {item.Value}");


			//int[] arr = { 1, 2, 3 };

			//try
			//{
			//    for (int i = 0; i < 5; i++)
			//        WriteLine(arr[i]);
			//}
			//catch(IndexOutOfRangeException e)
			//{
			//    WriteLine($"예외 발생 {e.Message}");
			//}
			//WriteLine("종료");

			//try
			//{
			//    SimpleFunc(5);
			//    SimpleFunc(12);
			//}
			//catch(Exception e)
			//{
			//    WriteLine(e.Message);
			//}

			//try
			//{
			//    int? a = null;
			//    int b = a ?? throw new ArgumentNullException();
			//}
			//catch(ArgumentNullException e)
			//{
			//    WriteLine(e);
			//}
			//try
			//{
			//    int[] array = new[] { 1, 2, 3 };
			//    int index = 4;
			//    int value = array[index >= 0 && index < 3 ? index : throw new IndexOutOfRangeException()];
			//}
			//catch(IndexOutOfRangeException e)
			//{
			//    WriteLine(e);
			//}


			//try
			//{
			//    Write("제수 입력 : ");
			//    String temp = ReadLine();
			//    int divisor = Convert.ToInt32(temp);

			//    Write("피제수 입력 : ");
			//    temp = ReadLine();
			//    int dividend = int.Parse(temp);

			//    WriteLine("{0}/{1} = {2}", divisor, dividend, Divide(divisor, dividend));
			//}
			//catch(FormatException e)
			//{
			//    WriteLine("error :" + e.Message);
			//}
			//catch (DivideByZeroException e)
			//{
			//    WriteLine("error :" + e.Message);
			//}
			//finally
			//{
			//    WriteLine("프로그램 종료");
			//}


			//try
			//{
			//    WriteLine("0x{0:X8}", MergeARGB(255, 100, 100, 100));
			//    WriteLine("0x{0:X8}", MergeARGB(1, 165, 190, 125));
			//    WriteLine("0x{0:X8}", MergeARGB(0, 255, 255, 260));
			//}
			//catch(InvaildArgmentException e)
			//{
			//    WriteLine(e.Message);
			//    WriteLine($"Argument: {e.Argment}, Range: {e.Range}");
			//}

			//Write("0~10 ");
			//string input = ReadLine();
			//try
			//{
			//    int num = int.Parse(input);
			//    if (num < 0 || num > 10)
			//        throw new FilterableException() { ErrorNo = num };
			//    else
			//        WriteLine($"Output: {num}");
			//}
			//catch(FilterableException e) when (e.ErrorNo < 0)
			//{
			//    WriteLine("음수 ㄴ");
			//}
			//catch(FilterableException e) when (e.ErrorNo > 10)
			//{
			//    WriteLine("10보다 큰거 ㄴ");
			//}

			//Calculator cal = new Calculator();

			//Mydelegate Callback = new Mydelegate(cal.Plus);
			//WriteLine(Callback(3, 4));

			//Callback = new Mydelegate(cal.Minus);
			//WriteLine(Callback(8, 3));


			//int[] array = { 3, 7, 4, 2, 9 };

			//WriteLine("ascending sort");
			//BubbleSort(array, new Compare(AscendCompare));
			//for (int i = 0; i < array.Length; i++)
			//    Write($"{array[i]} ");
			//WriteLine();

			//WriteLine("decending sort");
			//BubbleSort(array, new Compare(DecendCompare));
			//for (int i = 0; i < array.Length; i++)
			//    Write($"{array[i]} ");
			//WriteLine();

			//WriteLine("ascending sort");
			//BubbleSort<int>(array, new Compare<int>(AscendCompare));
			//for (int i = 0; i < array.Length; i++)
			//    Write($"{array[i]} ");
			//WriteLine();

			//string[] array2 = { "abc", "def", "ghi", "jkl", "mno" };
			//WriteLine("decending sort");
			//BubbleSort<string>(array2, new Compare<string>(DecendCompare));
			//for (int i = 0; i < array2.Length; i++)
			//    Write($"{array2[i]} ");
			//WriteLine();

			//OnlineShopping shopper = new OnlineShopping(OrderGoods) + new OnlineShopping(SpecialOrder);
			//shopper("우리집");

			//Notifier notifier = new Notifier(); // 델리게이트를 가진 객체
			//EventListener listener1 = new EventListener("Listener1");
			//EventListener listener2 = new EventListener("Listener2");
			//EventListener listener3 = new EventListener("Listener3");

			//notifier.EventOccured = listener1.SomethingHappend; // 델리게이트 객체에 메소드를 연결
			//notifier.EventOccured += listener2.SomethingHappend;
			//notifier.EventOccured += listener3.SomethingHappend;
			//notifier.EventOccured("you've got mail"); // 델리게이트 string 넣고 호출
			//WriteLine();

			//Notify notify1 = new Notify(listener1.SomethingHappend); // 델리게이트 만들고
			//Notify notify2 = new Notify(listener2.SomethingHappend); 
			//notifier.EventOccured = (Notify)Delegate.Combine(notify1, notify2); // 명시적으로 연결
			//notifier.EventOccured("fire");
			//WriteLine();

			//notifier.EventOccured = (Notify)Delegate.Remove(notifier.EventOccured, notify2);
			//notifier.EventOccured("game over");


			//Calculate calc = delegate (int a, int b)
			//{
			//    return a + b;
			//};
			//WriteLine("3 + 4 : {0}", calc(3, 4));


			//int[] array = { 3, 7, 4, 2, 9 };

			//WriteLine("ascending sort");
			//BubbleSort(array, delegate (int a, int b)
			//{
			//    if (a > b)
			//        return 1;
			//    else if (a == b)
			//        return 0;
			//    else
			//        return -1;
			//});

			//for (int i = 0; i < array.Length; i++)
			//    Write($"{array[i]} ");
			//WriteLine();

			//WriteLine("decending sort");
			//BubbleSort(array, delegate (int a, int b)
			//{
			//    if (a < b)
			//        return 1;
			//    else if (a == b)
			//        return 0;
			//    else
			//        return -1;
			//});
			//for (int i = 0; i < array.Length; i++)
			//    Write($"{array[i]} ");
			//WriteLine();


			//MyNotifier notifier = new MyNotifier();
			//notifier.DoAlarm += new EventHandler(MyHandler);

			//for(int i = 1; i < 30; i++)
			//{
			//    notifier.Get369(i);
			//}
			////notifier.DoAlarm("이거는 안됌");

			//Calculate cal = (a, b) => a + b;
			//WriteLine($"{3} + {4} : {cal(3, 4)}");

			//string[] strArr = { "Microsoft ", "C# ", "Language" };
			//Concatenate concat = (arr) =>
			//{
			//	string result = "";
			//	foreach (string s in arr)
			//		result += s;
			//	return result;
			//};
			//WriteLine(concat(strArr));

			//Func<int> func1 = () => 10;
			//WriteLine($"func1() : {func1()}");

			//Func<int, int> func2 = (x) => x * 2;
			//WriteLine($"func2() : {func2(4)}");

			//Func<double, double, double> func3 = (x, y) => x / y;
			//WriteLine($"func3() : {func3(23,6)}");


			//Action act1 = () => WriteLine("action()");
			//act1();
			//int result = 0;
			//Action<int> act2 = (x) => result = x * x;
			//act2(3);
			//WriteLine($"result : {result}");

			//Action<double, double> act3 = (x, y) =>
			//{
			//	double d = x / y;
			//	WriteLine($"action<> : ({x}, {y}) : {d}");
			//};
			//act3(10.0, 4.0);


			var obj = new MyEnumerator();
			foreach (int i in obj)
				WriteLine(i);



			MyList list = new MyList();
			for(int i = 0; i< 5;i++)
			{
				list[i] = i;
			}

			for (int i = 0; i < list.Length; i++)
				WriteLine(list[i]);

			foreach (int e in list)
				WriteLine(e);

			ReadKey();
        }
    }
}
