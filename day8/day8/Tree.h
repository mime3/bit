#pragma once

// �켱����ť(heap)  tree -> �迭

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
