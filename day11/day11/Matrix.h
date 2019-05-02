#pragma once
#include <stdlib.h>
#include <stdio.h>
class Martix
{
	int rows;
	int cols;
	int** mat;
public:
	Martix(int row, int col);
	~Martix();
	int& Element(const int row, const int col);
	int Rows() const;
	int Cols() const;
	void Print() const;
	void SetRand();
	int MaxPixel() const;
};
