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
	printf("마력 : %d \n", _horsePower);
}

InterCoolerEngine::InterCoolerEngine(int horsePower, const char* coolerType) :Engine(horsePower)
{
	if (strcmp("오일", coolerType) != 0 &&
		strcmp("물", coolerType) != 0)
		coolerType = "오일";
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
	printf("마력 : %d , 오일 : %s\n",GetHorsePower(), _cooler);
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
	printf("마력 : %d , 오일 : %s , 차저 : %c\n", GetHorsePower(), GetCooler(), _turborChager);
}
