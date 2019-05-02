#pragma once
#include <string>
#include <iostream>
#include <stdlib.h>

template <typename T>
T Add(T fir, T sec)
{
	return fir + sec;
}

template<>
std::string Add<std::string>(std::string fir, std::string sec)
{
	std::string temp = fir + sec;
	return temp;
}


template<typename T>
class Point
{
	T fir;
	T sec;
public:
	Point(T fir, T sec) : fir(fir), sec(sec) {}
};

template <>
class Point<char>
{
	char fir;
	char sec;
public:
	Point(char fir, char sec) : fir(fir), sec(sec) { std::cout << __max(fir, sec) << std::endl; }
};