#pragma once

//class Car ���¸� ������� �Ѵ�.
//������ ���� 3���� ��� ������ �ִ�.
//power
//gas
//brake
//Car ob0;    //10 , 10, 10
//Car ob1(200)   //200, 10, 10
//Car ob2(200, 30)  //200, 30, 10
//Car ob3(200, 30 , 40) //200, 30, 40 
//�ǵ��� �����ڸ� �����Ͻÿ�

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