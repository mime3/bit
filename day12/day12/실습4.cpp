
#include <iostream>
#include <cstring>
#include <stdio.h>
using namespace std;

class String
{
private:
	int len;
	char* str;
public:
	String();
	String(const char* s);
	String(const String& s);
	~String();
	String& operator= (const String& s);
	String& operator+= (const String& s);
	bool operator== (const String& s);
	String operator+ (const String& s);

	friend ostream& operator<< (ostream& os, const String& s);
	friend istream& operator>> (istream& is, String& s);
};

String::String() : len(0), str(nullptr)
{
}

String::String(const char* s)
{
	len = (int)strlen(s) + 1;
	str = new char[len];
	strcpy_s(str, len, s);
}

String::String(const String& s)
	: len(s.len)
{
	str = new char[len];
	strcpy_s(str, len, s.str);
}

String::~String()
{
	delete[] str;
}

String& String::operator=(const String& s)
{
	if (str != nullptr)
		delete[] str;
	if (s.str == nullptr)
		return *this;
	len = s.len;
	str = new char(len);
	strcpy_s(str, len, s.str);
	return *this;
}

String& String::operator+=(const String& s)
{
	if (s.str == nullptr)
		return *this;

	char* temp = new char[__int64(len) + s.len - 1];
	strcpy_s(temp, len, str);
	strcat_s(temp, __int64(len) + s.len - 1, s.str);
	//strcpy_s(temp + s.len - 1, s.len, s.str);
	len += s.len - 1;

	delete[] str;
	str = temp;
	return *this;
}

bool String::operator==(const String& s)
{
	return strcmp(str, s.str) == 0;
}

String String::operator+(const String& s)
{
	String ret;
	ret.len = len + s.len - 1;
	ret.str = new char[ret.len];
	strcpy_s(ret.str, len, str);
	strcat_s(ret.str, ret.len, s.str);
	//strcpy_s(ret.str + s.len - 1, s.len, s.str);
	return ret;
}

int main(void)
{
	String str1 = "I like ";
	String str2 = "string class";
	String str3 = str1 + str2;

	cout << str1 << endl;
	cout << str2 << endl;
	cout << str3 << endl;

	str1 += str2;
	if (str1 == str3)
		cout << "동일 문자열!" << endl;
	else
		cout << "동일하지 않은 문자열!" << endl;

	String str4;
	cout << "문자열 입력: ";
	cin >> str4;
	cout << "입력한 문자열: " << str4 << endl;
	return 0;
}

ostream& operator<<(ostream& os, const String& s)
{
	cout << s.str;
	return os;
}

istream& operator>>(istream& is, String& s)
{
	if (s.str == nullptr)
		s.str = new char[256];


	gets_s(s.str, 256);
	s.len = (int)strlen(s.str) + 1;
	return is;
}
