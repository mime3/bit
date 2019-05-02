#pragma once
#include <iostream>
template<typename T>
class Vector
{
	T count;
	T * vct;
public:
	Vector(int num = 10);
	Vector(const Vector& copy);
	~Vector();

	void RandSet();
	void View(const char* vw);

	void operator = (const Vector& copy);
};

template<typename T>
inline Vector<T>::Vector(int num) : count(num)
{
	vct = new T[num];
}

template<typename T>
inline Vector<T>::Vector(const Vector& copy)
{
	count = copy.count;
	vct = new T[copy.count];
	memcpy_s(vct, sizeof(T) * count, copy.vct, sizeof(T) * copy.count);
}

template<typename T>
inline Vector<T>::~Vector()
{
	delete[] vct;
}

template<typename T>
inline void Vector<T>::RandSet()
{
	for (int i = 0; i < count; i++)
	{
		vct[i] = rand() % 100;
	}
}

template<typename T>
inline void Vector<T>::View(const char *vw)
{
	std::cout << vw << " = < ";
	for (int i = 0; i < count; i++)
	{
		std::cout << vct[i] << ' ';
	}
	std::cout << ">" << endl;
}

template<typename T>
inline void Vector<T>::operator=(const Vector& copy)
{
	delete vct;
	vct = new T[copy.count];
	count = copy.count;
	memcpy_s(vct, sizeof(T) * count, copy.vct, sizeof(T) * copy.count);
}
