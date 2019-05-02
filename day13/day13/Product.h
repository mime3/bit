#pragma once
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

class Product
{
	char*	_name;
	int		_value;
public:
	Product(char* name, int value);
	Product(const Product&) = delete;
	~Product();

	void PrintInfo();
	void SetInfo(char* name, int value);
};


class ProductContainer
{
	Product**	_product;
	const int	_maxProduct;
	int			_topIndex;

public:
	ProductContainer(int maxProduct);
	ProductContainer(const ProductContainer&) = delete;
	~ProductContainer();

	bool AddProduct(char* name, int value);
	bool ModProduct(int index, char* name, int value);
	void PrintProduct();
	void PrintProduct(int index);
};