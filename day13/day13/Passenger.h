#pragma once
#include <stdio.h>
#include "Reservation.h"
class Passenger
{
protected:
	// ������
	Reservation reserve;
	int baggage;
	// ��ȭ��
	virtual void Work();
};

class Stewardess : public Passenger
{
	// �ȳ�
	virtual void Work();
};

class Copolit : public Passenger
{
	// ���嵽��
	virtual void Work();
};

class Captain : public Copolit
{
	// ����� ����
	virtual void Work();
};

