#include "Engine.h"

Engine::Engine(int horsePower) : _horsePower(horsePower)
{
	if (_horsePower < HORSE_MIN)
		_horsePower = HORSE_MIN;
	if (HORSE_MAX < _horsePower)
		_horsePower = HORSE_MAX;
}

int Engine::GetHorsePower() const
{
	return _horsePower;
}

void Engine::PrintData() const
{
	printf("���� : %d \n", _horsePower);
}

InterCoolerEngine::InterCoolerEngine(int horsePower, const char* coolerType) :Engine(horsePower)
{
	if (strcmp("����", coolerType) != 0 &&
		strcmp("��", coolerType) != 0)
		coolerType = "����";
	_cooler = new char[strlen(coolerType) + 1];
	StringCchCopyA(_cooler, strlen(coolerType) + 1, coolerType);
	//strcpy_s(_cooler, strlen(coolerType) + 1, coolerType);
}

InterCoolerEngine::InterCoolerEngine(InterCoolerEngine& copy) : Engine(copy.GetHorsePower())
{
	_cooler = new char[strlen(copy._cooler) + 1];
	StringCchCopyA(_cooler, strlen(copy._cooler) + 1, copy._cooler);
	//strcpy_s(_cooler, strlen(copy._cooler) + 1, copy._cooler);
}

InterCoolerEngine::~InterCoolerEngine()
{
	delete _cooler;
}

void InterCoolerEngine::PrintData() const
{
	//Engine::PrintData();
	printf("���� : %d , ���� : %s\n",GetHorsePower(), _cooler);
}

char* InterCoolerEngine::GetCooler() const
{
	return _cooler;
}

TurboEngine::TurboEngine(int horsePower, const char* coolerType, const char turborType)
	: InterCoolerEngine(horsePower, coolerType), _turborChager(turborType)
{
	if (_turborChager != 'A' &&
		_turborChager != 'B' &&
		_turborChager != 'C')
		_turborChager = 'A';
}

void TurboEngine::PrintData() const
{
	//InterCoolerEngine::PrintData();
	printf("���� : %d , ���� : %s , ���� : %c\n", GetHorsePower(), GetCooler(), _turborChager);
}
