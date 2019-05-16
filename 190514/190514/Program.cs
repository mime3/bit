using System;
using static System.Console;
using System.IO;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Collections;

namespace _190514
{
    interface INamedValue
    {
        string Name
        {
            get; set;
        }
        string Value
        {
            get; set;
        }
    }

    class NamedValue : INamedValue
    {
        public string Name
        {
            get; set;
        }
        public string Value
        {
            get; set;
        }
    }
    interface ILogger
    {
        void WriteLog(string message);
    }
    interface IFormattableLogger : ILogger
    {
        void WriteLog(string format, params Object[] args);
    }

    class ConsoleLogger : IFormattableLogger
    {
        public void WriteLog(string message)
        {
            WriteLine("{0}:{1}", DateTime.Now.ToLocalTime(), message);
        }

        public void WriteLog(string format, params object[] args)
        {
            string message = String.Format(format, args);
            WriteLine("{0}:{1}", DateTime.Now.ToLocalTime(), message);
        }
    }

    class FileLogger : ILogger
    {
        private StreamWriter writer;

        public FileLogger(string path)
        {
            writer = File.CreateText(path);
            writer.AutoFlush = true;
        }

        public void WriteLog(string message)
        {
            writer.WriteLine("{0}:{1}", DateTime.Now.ToLocalTime(), message);
        }
    }

    class ClimateMonitor
    {
        private ILogger logger;

        public ClimateMonitor(ILogger logger)
        {
            this.logger = logger;
        }

        public void Start()
        {
            while(true)
            {
                Write("온도 입력:");
                string temperture = ReadLine();

                if (temperture == "")
                    break;

                logger.WriteLog("현재온도 : " + temperture);
            }
        }
    }

    class BirthdayInfo
    {
        public string Name
        {
            get; set;
        } = "Anonymous";

        public DateTime Birthday
        {
            get; set;
        } = new DateTime(1, 1, 1);

        public int Age
        {
            get
            {
                return new DateTime(DateTime.Now.Subtract(Birthday).Ticks).Year;
            }
        }
    }

    abstract class Product
    {
        private static int serial = 0;
        public string SerialID
        {
            get { return String.Format("{0:d5}", serial++); }
        }
        abstract public DateTime ProductDate
        {
            get; set;
        }
    }

    class MyProduct : Product
    {
        public override DateTime ProductDate { get; set; }
    }

    class MyList<T>
    {
        private T[] array;

        public MyList()
        {
            array = new T[3];
        }
        
        public T this[int index]
        {
            get
            {
                return array[index];
            }
            set
            {
                if(index >= array.Length)
                {
                    Array.Resize<T>(ref array, index + 1);
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
    }

    class Program
    {
        private static bool CheckPassed(int score)
        {
            if (score >= 60)
                return true;
            return false;
        }

        static void CopyArray<T>(T[] source, T[] target)
        {
            for (int i = 0; i < source.Length; i++)
                target[i] = source[i];
        }
        static void Main(string[] args)
        {
            //WriteLine("FileLogger Start");
            //ClimateMonitor monitor = new ClimateMonitor(new FileLogger("C:/temp/MyLog.txt"));
            //monitor.Start();

            //WriteLine("ConsoleLogger Start");
            //ClimateMonitor monitor2 = new ClimateMonitor(new ConsoleLogger());
            //monitor2.Start();

            //IFormattableLogger logger = new ConsoleLogger();
            //logger.WriteLog("hihihihi");
            //logger.WriteLog("---{0}---", "22222222");

            //BirthdayInfo birth = new BirthdayInfo();
            //WriteLine($"Name: {birth.Name}");
            //WriteLine($"Birthday: {birth.Birthday.ToShortDateString()}");
            //WriteLine($"Age: {birth.Age}");

            ////BirthdayInfo birth = new BirthdayInfo()
            ////{
            ////    Name = "홍길동",
            ////    Birthday = new DateTime(1990, 5, 10)
            ////};

            //birth.Name = "홍길동";
            //birth.Birthday = new DateTime(1990, 5, 10);
            //WriteLine($"Name: {birth.Name}");
            //WriteLine($"Birthday: {birth.Birthday.ToShortDateString()}");
            //WriteLine($"Age: {birth.Age}");

            //var a = new { Name = "홍길동", Age = 20 };
            //WriteLine($"Name: {a.Name}, Age:{a.Age}");

            //var b = new { Subject = "수학", Scores = new int[] { 90, 85, 80, 75 } };
            //Write($"Subject:{b.Subject}, Scores: ");
            //foreach(var score in b.Scores)
            //{
            //    Write($"{score} ");
            //}
            //WriteLine();

            //NamedValue name = new NamedValue() { Name = "이름", Value = "홍길동" };
            //NamedValue height = new NamedValue() { Name = "키", Value = "170cm" };
            //NamedValue weight = new NamedValue() { Name = "체중", Value = "80kg" };
            //WriteLine($"{name.Name} : {name.Value}");
            //WriteLine($"{height.Name} : {height.Value}");
            //WriteLine($"{weight.Name} : {weight.Value}");

            //Product product1 = new MyProduct()
            //{
            //    ProductDate = new DateTime(2018, 09, 09)
            //};
            //WriteLine("Product: {0}, Product Date {1}", product1.SerialID, product1.ProductDate);
            //Product product2 = new MyProduct()
            //{
            //    ProductDate = new DateTime(2018, 03, 03)
            //};
            //WriteLine("Product: {0}, Product Date {1}", product2.SerialID, product2.ProductDate);

            //string[] array1 = new string[3] { "C++", "C#", "Java" };
            //foreach (string subject in array1)
            //    WriteLine($"{subject}");
            //WriteLine();

            //string[] array2 = new string[] { "C++", "C#", "Java" };
            //foreach (string subject in array2)
            //    WriteLine($"{subject}");
            //WriteLine();

            //string[] array3 = { "C++", "C#", "Java" };
            //foreach (string subject in array3)
            //    WriteLine($"{subject}");

            //int[] scores = new int[] { 90, 75, 80, 94, 50 };

            //foreach (int score in scores)
            //    Write($"{score} ");
            //WriteLine();

            //Array.Sort(scores);
            //foreach (int score in scores)
            //    Write($"{score} ");
            //WriteLine();

            //WriteLine($"Number of dimensions : {scores.Rank}");
            //WriteLine("Binary Search : 80 is at {0}", Array.BinarySearch<int>(scores, 80));
            //WriteLine("Linear Search : 94 is at {0}", Array.IndexOf(scores, 94));

            //WriteLine("Everyone passed ? : {0}", Array.TrueForAll<int>(scores, CheckPassed));
            //WriteLine($"Old lenth of scores : {scores.GetLength(0)}");

            //Array.Resize<int>(ref scores, 10);
            //WriteLine($"New length of scores : {scores.Length}");

            //foreach (int score in scores)
            //    Write($"{score} ");
            //WriteLine();

            //Array.Clear(scores, 3, 7);
            //foreach(int score in scores)
            //    Write($"{score} ");
            //WriteLine();


            //int[,] arr = new int[2, 3] { { 1, 2, 3 }, { 4, 5, 6 } };
            //for(int i = 0; i< arr.GetLength(0); i++)
            //{
            //    for(int j = 0; j < arr.GetLength(1); j++)
            //        Write($"[{i}, {j}] : {arr[i,j]} ");
            //    WriteLine();
            //}

            //int[,] arr2 = new int[,] { { 1, 2, 3 }, { 4, 5, 6 } };
            //for (int i = 0; i < arr2.GetLength(0); i++)
            //{
            //    for (int j = 0; j < arr2.GetLength(1); j++)
            //        Write($"[{i}, {j}] : {arr2[i, j]} ");
            //    WriteLine();
            //}

            //int[,] arr3 =  { { 1, 2, 3 }, { 4, 5, 6 } };
            //for (int i = 0; i < arr3.GetLength(0); i++)
            //{
            //    for (int j = 0; j < arr3.GetLength(1); j++)
            //        Write($"[{i}, {j}] : {arr3[i, j]} ");
            //    WriteLine();
            //}
            //WriteLine();

            //int[][] jagged = new int[3][];
            //jagged[0] = new int[5] { 1, 2, 3, 4, 5 };
            //jagged[1] = new int[] { 10, 20, 30 };
            //jagged[2] = new int[] { 100, 200 };

            //foreach(int[] arr in jagged)
            //{
            //    Write($"Length : {arr.Length}, ");
            //    foreach (int e in arr)
            //        Write($"{e} ");
            //    WriteLine();
            //}
            //WriteLine();

            //int[][] jagged2 = new int[2][]
            //{
            //     new int[] { 100, 200 },
            //     new int[4] { 6,7,8,9 }
            //};
            //foreach(int[] arr in jagged2)
            //{
            //    Write($"Length {arr.Length}, ");
            //    foreach (int e in arr)
            //        Write($"{e} ");
            //    WriteLine();
            //}

            //ArrayList list = new ArrayList();
            //for (int i = 0; i < 5; i++)
            //    list.Add(i);

            //foreach (object obj in list)
            //    Write($"{obj} ");
            //WriteLine();

            //list.RemoveAt(2);

            //foreach (object obj in list)
            //    Write($"{obj} ");
            //WriteLine();

            //list.Insert(2, 2);

            //foreach (object obj in list)
            //    Write($"{obj} ");
            //WriteLine();

            //list.Add("abc");
            //list.Add("def");

            //for(int i = 0; i < list.Count; i++)
            //    Write($"{list[i]} ");
            //WriteLine();

            //Queue que = new Queue();
            //que.Enqueue(1);
            //que.Enqueue(2);
            //que.Enqueue(3);
            //que.Enqueue(4);
            //que.Enqueue(5);
            //while (que.Count > 0)
            //    WriteLine(que.Dequeue());


            //Hashtable hashtable = new Hashtable();
            //hashtable["하나"] = "one";
            //hashtable["둘"] = "two";
            //hashtable["셋"] = "three";
            //hashtable["넷"] = "four";
            //hashtable["다섯"] = "five";

            //WriteLine(hashtable["하나"]);
            //WriteLine(hashtable["둘"]);
            //WriteLine(hashtable["셋"]);
            //WriteLine(hashtable["넷"]);
            //WriteLine(hashtable["다섯"]);


            //int[] source = { 1, 2, 3, 4, 5 };
            //int[] target = new int[source.Length];

            //CopyArray<int>(source, target);

            //foreach (int i in target)
            //    Write("{0} ", i);
            //WriteLine();

            //string[] source2 = { "C++", "C#", "Java", "Python" };
            //string[] target2 = new string[source2.Length];

            //CopyArray<string>(source2, target2);

            //foreach (string i in target2)
            //    Write("{0} ", i);
            //WriteLine();


            //MyList list = new MyList();
            //for (int i = 0; i < 5; i++)
            //    list[i] = i;

            //for (int i = 0; i < list.Length; i++)
            //    WriteLine(list[i]);


            MyList<string> str_list = new MyList<string>();
            str_list[0] = "abc";
            str_list[1] = "def";
            str_list[2] = "ghi";
            str_list[3] = "jkl";
            str_list[4] = "mno";
            for (int i = 0; i < str_list.Length; i++)
                WriteLine(str_list[i]);

            MyList<int> int_list = new MyList<int>();
            for (int i = 0; i < 5; i++)
                int_list[i] = i;
            for (int i = 0; i < int_list.Length; i++)
                WriteLine(int_list[i]);



            ReadKey();
        }
    }
}
