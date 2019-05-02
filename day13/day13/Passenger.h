#pragma once
#include <stdio.h>
#include "Reservation.h"
class Passenger
{
protected:
	// 예약기능
	Reservation reserve;
	int baggage;
	// 수화물
	virtual void Work();
};

class Stewardess : public Passenger
{
	// 안내
	virtual void Work();
};

class Copolit : public Passenger
{
	// 기장돕기
	virtual void Work();
};

class Captain : public Copolit
{
	// 비행기 운전
	virtual void Work();
};

