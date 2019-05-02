#pragma once

//class Car 형태를 만들려고 한다.
//다음과 같이 3개의 멤버 변수가 있다.
//power
//gas
//brake
//Car ob0;    //10 , 10, 10
//Car ob1(200)   //200, 10, 10
//Car ob2(200, 30)  //200, 30, 10
//Car ob3(200, 30 , 40) //200, 30, 40 
//되도록 생성자를 구현하시오

class Car
{
	int power;
	int gas;
	int brake;
public:
	Car(int power = 10, int gas = 10, int brake = 10) :power(power), gas(gas), brake(brake)
	{
		//this->power = power;
		//this->gas = gas;
		//this->brake = brake;
	}
	void View()
	{
		printf("power = %d , gas = %d, brake = %d\n", power, gas, brake);
	}
};