#pragma once
constexpr auto QUEUESIZE = 10;

template <typename Q>
class Queue
{
	Q _queue[QUEUESIZE];
	int _front, _rear;

public:
	Queue()
	{
		_front = 0; 
		_rear = 0; //Ç×»ó ºó°÷ °¡¸®Å´
	}
	bool EnQueue(Q item)
	{
		if (isFull())
			return false;
		_queue[_rear] = item;
		_rear = ++_rear % QUEUESIZE;
		return true;
	}
	bool DeQueue(Q * item)
	{
		if (isEmpty())
			return false;
		*item = _queue[_front];
		_front = ++_front % QUEUESIZE;
		return true;
	}
	bool isFull()
	{
		return (_rear + 1) % QUEUESIZE == _front;
	}
	bool isEmpty()
	{
		return _front == _rear;
	}
	bool find(Q item)
	{
		int move = _front;
		while (move != _rear)
		{
			if (_queue[move] == item)
				return true;
			move = ++move % QUEUESIZE;
		}
		return false;
	}

	void Print()
	{
		int move = _front;
		while (move != _rear)
		{
			printf("%d ", _queue[move]);
			move = ++move % QUEUESIZE;
		}
		puts("");
	}
};
