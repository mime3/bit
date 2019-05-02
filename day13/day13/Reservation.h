#pragma once

enum SEAT
{
	FIRST_CLASS,
	BUSIENESS_CLASS,
	ECONOMY_CLASS
};

enum MILEAGE
{
	VIP,
	FAMILY,
	WELCOME
};


class Reservation
{
	int date;
	int dest;
	SEAT seat;
	int discount;
	MILEAGE mileage;
};