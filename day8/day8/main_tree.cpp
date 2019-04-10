#include <stdio.h>
#include "Queue.h"

struct Node
{
	int value;
	Node * left;
	Node * right;
};
Node * head, *tail;

void preOrder(Node * root)
{
	if (root != nullptr)
	{
		printf("%d ", root->value);
		preOrder(root->left);
		preOrder(root->right);
	}
}
// bst ����Ž��Ʈ���� �˻��ϸ� ���ĵ� ������ ����
void inOrder(Node * root)
{
	if (root != nullptr)
	{
		inOrder(root->left);
		printf("%d ", root->value);
		inOrder(root->right);
	}
}

void level(Node * root)
{
	Queue<Node *> q;
	q.EnQueue(root);
	while (!q.isEmpty())
	{
		Node * get;
		q.DeQueue(&get);
		printf("%d ", get->value);
		if (get->left != nullptr)
			q.EnQueue(get->left);
		if (get->right != nullptr)
			q.EnQueue(get->right);
	}
}

void postOrder(Node * root)
{
	if (root != nullptr)
	{
		postOrder(root->left);
		postOrder(root->right);
		printf("%d ", root->value);
	}
}

int get_Depth(Node * root, int dep)
{
	int l_dep, r_dep;
	l_dep = r_dep = dep;

	if (root->left != nullptr)
		l_dep = get_Depth(root->left, dep + 1);
	if (root->right != nullptr)
		r_dep = get_Depth(root->right, dep + 1);

	if (l_dep >= r_dep)
		return l_dep;
	else
		return r_dep;
}

int main()
{
	Node a1 = { 1, nullptr, nullptr };
	Node b2 = { 2, nullptr, nullptr };
	Node c3 = { 3, nullptr, nullptr };
	Node d4 = { 4, nullptr, nullptr };
	Node e5 = { 5, nullptr, nullptr };
	Node f6 = { 6, nullptr, nullptr };

	c3.left = &a1;
	a1.right = &b2;
	c3.right = &d4;
	d4.right = &e5;
	e5.right = &f6;

	preOrder(&c3);
	puts("");
	inOrder(&c3);
	puts("");
	postOrder(&c3);
	puts("");
	level(&c3);
	puts("");

	printf("%d\n", get_Depth(&c3, 0));
	printf("%d\n", get_Depth(c3.left, 0));
	printf("%d\n", get_Depth(c3.right, 0));
	getchar();
	return 0;
}

// ������ ����� ���� ��ȸ
// ��Ʈ�� push
// 
// while
// stack�� ������� ������ pop�ؼ� key�� ���
// pop�� �༮�� ������, ���ʼ����� push

// ���� ��ȸ
// while
// 1. ��Ʈ�� push
// 2. ���� ����Ʈ�� ���while push
// 3. ���̻� ������ pop �� key���
// 4. ������ ����Ʈ���� ���� ����Ʈ���� ��� push

// ���� ��ȸ
// ť ���
// root enqueue
// while
// ������� ������ dequeue
// dequeue�� �༮�� left, right enqueue