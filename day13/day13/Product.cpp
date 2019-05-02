#include "Product.h"

Product::Product(char* name, int value) : _value(value)
{
	int size = strlen(name) + 1;
	_name = new char[size];
	strcpy_s(_name, size, name);
}

Product::~Product()
{
	printf("%s 삭제\n", _name);
	delete[] _name;
}

void Product::PrintInfo()
{
	printf("상품 : %s\n가격 : %d\n", _name, _value);
}

void Product::SetInfo(char* name, int value)
{
	delete[] _name;
	int size = strlen(name) + 1;
	_name = new char[size];
	strcpy_s(_name, size, name);
	_value = value;
}

ProductContainer::ProductContainer(int maxProduct)
	: _maxProduct(maxProduct), _topIndex(0)
{
	_product = new Product * [_maxProduct];
}

ProductContainer::~ProductContainer()
{
	for (int i = 0; i < _topIndex; i++)
		delete _product[i];
	delete[] _product; 
}

bool ProductContainer::AddProduct(char * name, int value)
{
	if (_topIndex >= _maxProduct)
		return false;
	_product[_topIndex++] = new Product(name, value);
	return true;
}

bool ProductContainer::ModProduct(int index, char* name, int value)
{
	if (index >= _topIndex || index < 0)
		return false;
	_product[index]->SetInfo(name, value);
	return true;
}

void ProductContainer::PrintProduct()
{
	for (int i = 0; i < _topIndex; i++)
	{
		printf("[%d]번\n", i);
		_product[i]->PrintInfo();
	}
}

void ProductContainer::PrintProduct(int index)
{
	if(index < _topIndex && index >= 0)
		_product[index]->PrintInfo();
}
