using System;
using static System.Console;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Threading;
using System.IO;

namespace _190516
{
	class Counter
	{
		const int LOOP_COUNT = 1000;

		readonly object thisLock;
		private int count;
		bool lockedCount = false;

		public int Count
		{
			get;
		}

		public Counter()
		{
			thisLock = new object();
			count = 0;
		}

		public void Increase()
		{
			int loopCount = LOOP_COUNT;
			while(loopCount-- > 0)
			{
				//Interlocked.Increment(ref count);
				lock(thisLock)
				{
					if(count > 0 || lockedCount == true)
					{
						Monitor.Wait(thisLock);
					}
					lockedCount = true;
					count++;
					lockedCount = false;

					Monitor.Pulse(thisLock);
				}

				//Monitor.Enter(thisLock);
				//try
				//{
				//	count++;
				//}
				//finally
				//{
				//	Monitor.Exit(thisLock);
				//}
				////lock(thisLock)
				////{
				////	count++;
				////}
				//Thread.Sleep(1);
			}
		}

		public void Decrease()
		{
			int loopCount = LOOP_COUNT;
			while (loopCount-- > 0)
			{
				lock (thisLock)
				{
					if (count < 0 || lockedCount == true)
					{
						Monitor.Wait(thisLock);
					}
					lockedCount = true;
					count--;
					lockedCount = false;

					Monitor.Pulse(thisLock);
				}

				//Monitor.Enter(thisLock);
				//try
				//{
				//	count--;
				//}
				//finally
				//{
				//	Monitor.Exit(thisLock);
				//}
				//Thread.Sleep(1);
			}
		}
	}

	class Program
	{
		async static private void MyMethodAsync(int count)
		{
			WriteLine("C");
			WriteLine("D");

			await Task.Run(() =>
			{
				for (int i = 1; i <= count; i++)
				{
					WriteLine($"{i}/{count}...");
					Thread.Sleep(100);
				}
			});

			WriteLine("G");
			WriteLine("H");
		}

		static void Caller()
		{
			WriteLine("A");
			WriteLine("B");

			MyMethodAsync(5);
			
			WriteLine("E");
			WriteLine("F");
		}
		static bool IsPrime(long number)
		{
			if (number < 2)
				return false;

			if (number % 2 == 0 && number != 2)
				return false;

			for(long i = 2; i < number; i++)
			{
				if (number % i == 0)
					return false;
			}

			return true;
		}

		static Boolean setStop = false;
		static void BlueFlag()
		{
			try
			{
				while (!setStop)
				{
					WriteLine("청기");
					Thread.Sleep(10);
				}
			}
			catch(ThreadInterruptedException e)
			{
				WriteLine(e);
			}
			finally
			{
				WriteLine("리소스 해제");
			}
			WriteLine("추가작업");
		}
		static void Main(string[] args)
		{
			//Thread thread = new Thread(new ThreadStart(BlueFlag));
			//WriteLine("start thread");
			//thread.Start();
			//Thread.Sleep(100);
			//WriteLine("abort thread");
			////thread.Abort();
			////setStop = true;
			//thread.Interrupt();
			//for (int i = 0; i < 10; i++)
			//{
			//	WriteLine("백기");
			//	Thread.Sleep(10);
			//}
			//WriteLine("wait thread stop");
			//thread.Join();
			//WriteLine("end");


			//Counter counter = new Counter();

			//Thread incThread = new Thread(new ThreadStart(counter.Increase));
			//Thread decThread = new Thread(new ThreadStart(counter.Decrease));

			//incThread.Start();
			//decThread.Start();

			//incThread.Join();
			//decThread.Join();

			//WriteLine(counter.Count);

			//string srcFile = args[0];

			//Action<object> FileCopyAction = (object state) =>
			//{
			//	string[] paths = (string[])state;
			//	File.Copy(paths[0], paths[1]);
			//	WriteLine("TaskID:{0}, ThreadID:{1}, {2} was copied to {3}",
			//		Task.CurrentId, Thread.CurrentThread.ManagedThreadId,
			//		paths[0], paths[1]);
			//};

			//Task t1 = new Task(FileCopyAction, new string[] { srcFile, srcFile + "copy1" });
			//t1.Start();

			//Task t2 = Task.Run(() => { FileCopyAction(new string[] { srcFile, srcFile + "copy2" }); });

			//Task t3 = new Task(FileCopyAction, new string[] { srcFile, srcFile + "copy3" });

			//t3.RunSynchronously();

			//t1.Wait();
			//t2.Wait();


			//long from = Convert.ToInt64(args[0]);
			//long to = Convert.ToInt64(args[1]);
			//int taskCount = Convert.ToInt32(args[2]);

			//Func<object, List<long>> FindPrimeFunc = (objRange) =>
			//{
			//	long[] range = (long[])objRange;
			//	List<long> found = new List<long>();

			//	for (long i = range[0]; i <= range[1]; i++)
			//	{
			//		if (IsPrime(i))
			//			found.Add(i);
			//	}
			//	return found;
			//};

			//Task<List<long>>[] tasks = new Task<List<long>>[taskCount];
			//long currentFrom = from;
			//long currentTo = from + (to - from) / tasks.Length;

			//for(int i = 0; i < tasks.Length; i++)
			//{
			//	WriteLine("Task[{0}] :: {1} ~ {2}", i, currentFrom, currentTo);

			//	tasks[i] = new Task<List<long>>(FindPrimeFunc, new long[] { currentFrom, currentTo });

			//	currentFrom = currentTo + 1;

			//	if (i == tasks.Length - 2)
			//		currentTo = to;
			//	else
			//		currentTo += ((to - from) / tasks.Length);
			//}

			//WriteLine("enter to start");
			//ReadLine();
			//WriteLine("start");

			//DateTime startTime = DateTime.Now;

			//foreach (Task<List<long>> task in tasks)
			//	task.Start();

			//List<long> total = new List<long>();
			//foreach (Task<List<long>> task in tasks)
			//	total.AddRange(task.Result.ToArray());

			//DateTime endTime = DateTime.Now;

			//TimeSpan ellapsed = endTime - startTime;

			//WriteLine("between {0} abd {1} : {2}", from, to, total.Count);
			//WriteLine("time : {0}", ellapsed);



			//long from = Convert.ToInt64(args[0]);
			//long to = Convert.ToInt64(args[1]);

			//WriteLine("enter to start");
			//ReadLine();
			//WriteLine("start");

			//DateTime startTime = DateTime.Now;
			//List<long> total = new List<long>();

			//Parallel.For(from ,to + 1, (long i) => 
			//{
			//if (IsPrime(i))
			//	total.Add(i);
			//});

			//DateTime endTime = DateTime.Now;
			//TimeSpan esllapsed = endTime - startTime;

			//WriteLine("prime number count between {0} abd {1}", from, to, total.Count);
			//WriteLine("ellapsed time : {0}", esllapsed);


			Caller();


			ReadKey();
		}
	}
}
