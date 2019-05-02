#include <stdio.h>
#include <iostream>
#include "template.h"
#include <vector>
#include <list>
#include <deque>
#include <algorithm>
#include <stack>

using namespace std;

int main()
{
	int a = 10;
	int b = 5;

	double c = 1.1, d = 2.2;

	cout << Add(a, b) << endl;
	cout << Add(c, d) << endl;
	string s1 = "aaa";
	string s2 = "bbb";
	cout << Add(s1, s2) << endl;


	Point<int> a1(10, 20);
	Point<char> a2('a', 'b');


	vector<int> v;
	deque<int> de;
	stack<int> st;

	return 0;
}