#include "URLStack.h"

bool URLStack::Push(char * url)
{
	if (MAX_HISTORY <= _current)
		return false;
	_history[++_current] = url;
	_top = _current;
	return true;
}

bool URLStack::Pop(char ** url)
{
	if (_top < 0)
		return false;
	*url = _history[_top--];
	return true;
}

bool URLStack::SavePoP(char ** url)
{
	if (_current < 0)
		return false;
	*url = _history[_current--];
	return true;
}

bool URLStack::Peek(const char ** url, int jump)
{
	if (_current - jump < 0)
		return false;
	*url = _history[_current - jump];
	return true;
}
