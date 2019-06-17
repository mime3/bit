using System;
using static System.Console;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace _190513
{
    class Car
    {
        protected string model;
        protected string powerTrain;
        protected string color;

        public Car()
        {
            model = "세단";
            color = "흰색";
        }

        public Car(string m, string c, string powerTrain = "전기")
        {
            model = m;
            color = c;
            this.powerTrain = powerTrain;
        }

        public void ShowStatus()
        {
            WriteLine($"Model : {model}, Color : {color}");
        }

        public /*virtual*/ void Drive()
        {
            WriteLine("달린다~~~");
        }
        ~Car()
        {
            WriteLine("소멸자 실행");
        }
    }

    class GasolineCar : Car
    {
        public GasolineCar(string model, string powerTrain) : base(model, "ll", powerTrain)
        {

        }
        public /*override*/ new void Drive()
        {
            //base.Drive();
            WriteLine($"{model} {powerTrain} 부르릉~");
        }
    }

    class HybridCar : Car
    {
        public HybridCar(string model, string powerTrain) : base(model, "l2", powerTrain)
        {

        }
        public /*override*/ new void Drive()
        {
            //base.Drive();
            WriteLine($"{model} {powerTrain} 스르륵~");
        }
    }


    class StaticField
    {
        public static int count = 0;

        public static void ShowCount()
        {
            WriteLine($"StaticField.count : {count}");
        }
    }

    class ClassA
    {
        public ClassA()
        {
            StaticField.count++;
        }
    }

    class ClassB
    {
        public ClassB()
        {
            StaticField.count++;
        }
    }

    class ShallowDeepCopy
    {
        public int field1;
        public int field2;

        public ShallowDeepCopy DeepCopy()
        {
            ShallowDeepCopy newClass = new ShallowDeepCopy();
            newClass.field1 = field1;
            newClass.field2 = field2;

            return newClass;
        }
    }

    class Employee
    {
        private string name;
        private string position;

        public void SetName(string name)
        {
            this.name = name;
        }
        public string GetName()
        {
            return name;
        }
        public void SetPosition(string position)
        {
            this.position = position;
        }
        public string GetPosition()
        {
            return position;
        }
    }

    class ThisConstructor
    {
        private int a, b, c;

        public ThisConstructor()
        {
            a = 1111;
            WriteLine("ThisConstructor");
        }

        public ThisConstructor(int b) : this()
        {
            this.b = b;
            WriteLine("ThisConstructor(int)");
        }

        public ThisConstructor(int b, int c) : this(b)
        {
            this.c = c;
            WriteLine("ThisConstructor(int, int)");
        }

        public void PrintField()
        {
            WriteLine($"{a}, {b}, {c}");
        }
    }
   
    class Parent
    {
        protected string name;

        public Parent()
        {
            name = "김철수";
            WriteLine($"{this.name}.Parent()");
        }
        public Parent(string name)
        {
            this.name = name;
            WriteLine($"{this.name}.Parent(string)");
        }
        ~Parent()
        {
            WriteLine($"{this.name}.~Parent()");
        }
        public void ParentMethod()
        {
            WriteLine($"{this.name}.ParenteMethod");
        }
    }

    class Child : Parent
    {
        public Child()
        {
            WriteLine($"{this.name}.Child()");
        }
        public Child(string name) : base(name)
        {
            WriteLine($"{this.name}.Child(string)");
        }
        ~Child()
        {
            WriteLine($"{this.name}.~Child()");
        }

        public void ChildMethod()
        {
            WriteLine($"{this.name}.ChildMethod()");
        }
    }

    class Mammal
    {
        public void Nurse()
        {
            WriteLine("Nursing~~");
        }
    }

    class Dog : Mammal
    {
        public void Bark()
        {
            WriteLine("Barking~~");
        }
    }

    class Human : Mammal
    {
        public void Speak()
        {
            WriteLine("Speaking~~");
        }
    }

    class Configuration
    {
        List<ItemValue> listConfig = new List<ItemValue>();

        public void SetConfig(string item, string value)
        {
            ItemValue iv = new ItemValue();
            iv.SetValue(this, item, value);
        }

        public string GetConfig(string item)
        {
            foreach(ItemValue iv in listConfig)
            {
                if (iv.GetItem() == item)
                    return iv.GetValue();
            }
            return "";
        }

        private class ItemValue
        {
            private string item;
            private string value;

            public void SetValue(Configuration config, string item, string value)
            {
                this.item = item;
                this.value = value;

                bool found = false;
                for(int i = 0; i < config.listConfig.Count; i++)
                {
                    if(config.listConfig[i].item == item)
                    {
                        config.listConfig[i] = this;
                        found = true;
                        break;
                    }
                }
                if (found == false)
                {
                    config.listConfig.Add(this);
                }
            }

            public string GetItem()
            {
                return item;
            }

            public string GetValue()
            {
                return value;
            }
        }
    }

    partial class AAA
    {
        public void Method1()
        {
            WriteLine("Method1");
        }

        public void Method2()
        {
            WriteLine("Method2");
        }
    }

    partial class AAA
    {
        public void Method3()
        {
            WriteLine("Method3");
        }
        public void Method4()
        {
            WriteLine("Method4");
        }
    }

    public static class EnhancedInteger
    {
        public static int Square(this int input)
        {
            return input * input;
        }

        public static int Power(this int input, int exponent)
        {
            int result = input;
            for (int i = 1; i < exponent; i++)
                result *= input;
            return result;
        }
    }

    struct Point3D
    {
        public int x;
        public int y;
        public int z;

        public Point3D(int x, int y, int z)
        {
            this.x = x;
            this.y = y;
            this.z = z;
        }

        public override string ToString()
        {
            return string.Format($"{x}, {y}, {z}");
        }
    }

    abstract class AbstractBase
    {
        protected void PrivateMethodA()
        {
            WriteLine("AbstractBase.PrivateMethodA()");
        }

        public void PublicMethodA()
        {
            WriteLine("AbstractBase.PublicMethodA()");
        }

        public abstract void AbstractMethodA();
    }

    class Derived : AbstractBase
    {
        public override void AbstractMethodA()
        {
            WriteLine("Derived.AbstractMethod()");
            PrivateMethodA();
        }
    }

    class MainApp
    {
        static int Sum(params int[] args)
        {
            int sum = 0;
            for(int i = 0; i < args.Length; i++)
            {
                if(i > 0)
                    Write(", ");
                Write(args[i]);
                sum += args[i];
            }
            WriteLine();
            return sum;
        }

        static void PrintProfile(string name, string phone = "")
        {
            WriteLine($"Name: {name}, Phone: {phone}");
        }

        static string ToLowerString(string str)
        {
            var arr = str.ToCharArray();
            for(int i = 0; i < arr.Length; i++)
            {
                arr[i] = ToLowerChar(i);
            }

            char ToLowerChar(int i)
            {
                if (arr[i] < 65 || arr[i] > 90)
                    return arr[i];
                else
                    return (char)(arr[i] + 32);
            }
            return new string(arr);
        }

        static void Main(string[] args)
        {
			int sum = Sum(1, 2, 3, 4, 5, 6, 7, 8, 9, 10);
			WriteLine($"Sum: {sum}");

			WriteLine();
			WriteLine();

			PrintProfile("홍길동");
			PrintProfile("홍길동", "010-1111-2222");
			PrintProfile(name: "김유신");
			PrintProfile(phone: "010-5555-6666", name: "이순신");

			WriteLine();
			WriteLine();

			WriteLine(ToLowerString("Hello"));
			WriteLine(ToLowerString("World"));
			WriteLine(ToLowerString("C# Programming"));

			WriteLine();
			WriteLine();

			Car myCar = new Car();
			Car yourCar = new Car("SUV", "블랙");
			myCar.ShowStatus();
			yourCar.ShowStatus();

			ClassA a = new ClassA();
			ClassB b = new ClassB();
			StaticField.ShowCount();
			WriteLine(StaticField.count);

			WriteLine();
			WriteLine();

			WriteLine("shallow Copy");
			ShallowDeepCopy source = new ShallowDeepCopy();
			source.field1 = 10;
			source.field2 = 20;

			ShallowDeepCopy target = source;
			target.field2 = 30;
			WriteLine($"{source.field1} {source.field2}");
			WriteLine($"{target.field1} {target.field2}");

			WriteLine("deep Copy");
			ShallowDeepCopy deepSource = new ShallowDeepCopy();
			deepSource.field1 = 10;
			deepSource.field2 = 20;

			ShallowDeepCopy deepTarget = deepSource.DeepCopy();
			deepTarget.field2 = 30;
			WriteLine($"{deepSource.field1} {deepSource.field2}");
			WriteLine($"{deepTarget.field1} {deepTarget.field2}");

			WriteLine();
			WriteLine();

			Employee worker = new Employee();
			worker.SetName("홍길동");
			worker.SetPosition("Guard");
			WriteLine($"{worker.GetName()} {worker.GetPosition()}");

			ThisConstructor thisConstructor = new ThisConstructor();
			thisConstructor.PrintField();
			ThisConstructor thisConstructor2 = new ThisConstructor(2222);
			thisConstructor2.PrintField();
			ThisConstructor thisConstructor3 = new ThisConstructor(2222, 3333);
			thisConstructor3.PrintField();

			Parent parent = new Parent("홍길동아버지");
			parent.ParentMethod();
			WriteLine();

			Child child = new Child("홍길동");
			child.ParentMethod();
			child.ChildMethod();
			WriteLine();

			Child child2 = new Child();
			child2.ParentMethod();
			child2.ChildMethod();
			WriteLine();

			//Mammal mammal = new Mammal();
			//mammal.Nurse();
			//WriteLine();

			//mammal = new Dog();
			//mammal.Nurse();
			//WriteLine();
			//if (mammal is Dog)
			//{
			//    Dog dog = (Dog)mammal;
			//    dog.Nurse();
			//    dog.Bark();
			//    WriteLine();
			//}
			//mammal = new Human();
			//mammal.Nurse();
			//WriteLine();

			////Human human = (Human)mammal;
			//Human human = mammal as Human;
			//if (human != null)
			//{
			//    human.Nurse();
			//    human.Speak();
			//}
			//else
			//    WriteLine("human is not Human");

			//GasolineCar gasolineCar = new GasolineCar("소나타", "가솔린엔진");
			//gasolineCar.Drive();

			//HybridCar hybridCar = new HybridCar("프리우스", "가솔린엔진, 전기모터");
			//hybridCar.Drive();

			//Configuration config = new Configuration();
			//config.SetConfig("Version", "V5.0");
			//config.SetConfig("Size", "655,324 KB");

			//WriteLine(config.GetConfig("Version"));
			//WriteLine(config.GetConfig("Size"));

			//config.SetConfig("Version", "V5.1");
			//WriteLine(config.GetConfig("Version"));

			//AAA obj = new AAA();
			//obj.Method1();
			//obj.Method2();
			//obj.Method3();
			//obj.Method4();

			//WriteLine($"3^2 : {3.Square()}");
			//WriteLine($"3^4 : {3.Power(4)}");
			//WriteLine($"2^10 : {2.Power(10)}");

			//Point3D point1;
			//point1.x = 10;
			//point1.y = 20;
			//point1.z = 30;

			//WriteLine(point1.ToString());

			//Point3D point2 = new Point3D(100, 200, 300);
			//Point3D point3 = point2;

			//point3.z = 400;

			//WriteLine(point2.ToString());
			//WriteLine(point3.ToString());


			//var a = ("홍길동", 20);
			//WriteLine($"{a.Item1}, {a.Item2}");

			//var b = (Name: "이순신",Age: 40);
			//WriteLine($"{b.Item1}, {b.Item2}");

			//var (name, age) = b;
			//WriteLine($"{name}, {age}");

			//b = a;
			//WriteLine($"{b.Name}, {b.Age}");

			AbstractBase obj = new Derived();
            obj.AbstractMethodA();
            obj.PublicMethodA();

			ReadKey();
        }
    }
}
