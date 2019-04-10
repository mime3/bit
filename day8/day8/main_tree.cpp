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
// bst 이진탐색트리를 검색하면 정렬된 순서로 나옴
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

// 스택을 사용한 전위 순회
// 루트를 push
// 
// while
// stack이 비어있지 않으면 pop해서 key를 출력
// pop한 녀석의 오른쪽, 왼쪽순으로 push

// 중위 순회
// while
// 1. 루트를 push
// 2. 왼쪽 서브트리 계속while push
// 3. 더이상 없으면 pop 후 key출력
// 4. 오른쪽 서브트리의 왼쪽 서브트리를 계속 push

// 레벨 순회
// 큐 기반
// root enqueue
// while
// 비어있지 않으면 dequeue
// dequeue한 녀석의 left, right enqueue