#pragma once

template <typename T>
class BinarySearchTree
{
	struct Node
	{
		T data;
		Node * parent;
		Node * left;
		NOde * right;
	};

	Node *	_root;
	int		_size;

public:
	BinarySearchTree();
	void Insert(T data);
	bool Delete(T data);
	bool Find(T data);
};

template<typename T>
inline BinarySearchTree<T>::BinarySearchTree()
{
}
