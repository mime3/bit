#pragma once

constexpr int MAX_HISTORY = 50;

class URLStack
{
public:
	int _top = -1;
	int _current = -1;
	char * _history[MAX_HISTORY];
	
	bool Push(char * url);
	bool Pop(char ** url);
	bool SavePoP(char ** url);
	bool Peek(const char ** url, int jump = 0);
};