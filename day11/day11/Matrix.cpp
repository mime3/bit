#include "Matrix.h"

Martix::Martix(int row, int col) : rows(row), cols(col)
{
	mat = (int **)new int[col * row];
}

Martix::~Martix()
{
	delete mat;
}

int& Martix::Element(const int row, const int col)
{
	return *(int *)(mat + row * cols + col);
}


int Martix::Rows() const
{
	return rows;
}

int Martix::Cols() const
{
	return cols;
}

void Martix::Print() const
{
	for (int i = 0; i < cols; i++)
	{
		int* move = ((int *)mat + i * rows);
		for (int j = 0; j < rows; j++)
		{
			printf("%d ", *(move + j));
		}
		puts("");
	}
}

void Martix::SetRand()
{
	for (int i = 0; i < cols * rows; i++)
	{
		*((int *)mat + i) = rand() % 10;
	}
}

int Martix::MaxPixel() const
{
	int max = 0;
	for (int i = 0; i < cols * rows; i++)
	{
		if (max < *((int *)mat + i))
			max = *((int*)mat + i);
	}
	return max;
}
