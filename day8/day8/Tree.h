#pragma once

// 우선순위큐(heap)  tree -> 배열

template<typename T>
class Tree
{
	struct Node
	{
		T value;
		Node * left;
		Node * right;
	};

	Node * head;
	Node * tail;
};
