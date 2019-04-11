#include "stdafx.h"
#include "RB_BinaryTree.h"

RB_BinaryTree::NODE::NODE(int data, NODE * parent)
{
	this->data = data;
	this->parent = parent;
	this->left = RB_BinaryTree::_nilNode;
	this->right = RB_BinaryTree::_nilNode;
	color = RED;
}

RB_BinaryTree::RB_BinaryTree()
{
	_nilNode = new NODE(NULL, nullptr);
	_nilNode->color = BLACK;
	_rootNode = _nilNode;

	_redBrush = CreateSolidBrush(RGB(255,0,0));
	_blackBrush = (HBRUSH)GetStockObject(BLACK_BRUSH);
}

RB_BinaryTree::~RB_BinaryTree()
{
	DeleteObject(_redBrush);
	DeleteObject(_blackBrush);
	// 전체삭제
}

bool RB_BinaryTree::Search(int data, NODE * &node)
{
	NODE * target = _rootNode;
	while (true)
	{
		if (data < target->data)
		{
			if (target->left == _nilNode)
				return false;
			target = target->left;
			node = target;
			continue;
		}
		else if (target->data < data)
		{
			if (target->right == _nilNode)
				return false;
			target = target->right;
			node = target;
			continue;
		}
		else
		{
			node = target;
			return true;
		}
	}
}

void RB_BinaryTree::LeftRotation(NODE * node)
{
	if (node != _rootNode)
	{
		if (node == node->parent->left)
			node->parent->left = node->right;
		else
			node->parent->right = node->right;
	}
	else
		_rootNode = node->right;

	NODE * parent = node->parent;
	NODE * right = node->right;

	node->parent = right;
	node->right = right->left;

	right->parent = parent;
	right->left->parent = node;
	right->left = node;
}

void RB_BinaryTree::RightRotation(NODE * node)
{
	if (node != _rootNode)
	{
		if (node == node->parent->left)
			node->parent->left = node->left;
		else
			node->parent->right = node->left;
	}
	else
		_rootNode = node->left;

	NODE * parent = node->parent;
	NODE * left = node->left;

	node->parent = left;
	node->left = left->right;

	left->parent = parent;
	left->right->parent = node;
	left->right = node;
}
// 둘다 레드이면 False;
bool RB_BinaryTree::CheckRedRule(NODE * node)
{
	return (node->color != RED) || (node->parent->color != RED);
}

void RB_BinaryTree::FindReplaceNode(NODE * targetNode, NODE * &replaceNode)
{
	replaceNode = targetNode->left;
	while (true)
	{
		if (replaceNode->right == _nilNode)
			break;
		replaceNode = replaceNode->right;
	}
}

void RB_BinaryTree::InsertDNode(NODE * node, int x, int y, int px, int py)
{
	if (node->left != _nilNode)
		InsertDNode(node->left, x - 50, y + 100, x, y);
	arr[index].node = node;
	arr[index].x = x;
	arr[index].y = y;
	arr[index].px = px;
	arr[index].py = py;
	index++;
	if (node->right != _nilNode)
		InsertDNode(node->right, x + 50, y + 100, x, y);
}

void RB_BinaryTree::InsertDNode2(NODE * node, RECT rect, int a, int b, int y, int px, int py)
{
	arr[index].node = node;
	arr[index].x = (rect.right - rect.left) * a / b;
	arr[index].y = y;
	arr[index].px = px;
	arr[index].py = py;
	index++;
	if (node->left != _nilNode)
		InsertDNode2(node->left, rect, a * 2 - 1, b * 2, y + 50, (rect.right - rect.left) * a / b, y);
	if (node->right != _nilNode)
		InsertDNode2(node->right, rect, a * 2 + 1, b * 2, y + 50, (rect.right - rect.left) * a / b, y);
}

int RB_BinaryTree::CalculateLevel(NODE * node, int level, int *highLevel)
{
	if (*highLevel < level)
		*highLevel = level;
	if (node->left != _nilNode)
		CalculateLevel(node->left, level + 1, highLevel);
	if (node->right != _nilNode)
		CalculateLevel(node->right, level + 1, highLevel);
	return *highLevel;
}

RB_BinaryTree::NODE * RB_BinaryTree::Sibling(NODE * node)
{
	if(node == _rootNode)
		return nullptr;

	if (node == node->parent->left)
		return node->parent->right;
	else
		return node->parent->left;
}

bool RB_BinaryTree::Insert(int data)
{
	NODE * parent = _rootNode;
	if (_rootNode == _nilNode)
	{
		NODE * newNode = new NODE(data, _nilNode);
		_rootNode = newNode;
		_rootNode->color = BLACK;
		return true;
	}

	if (Search(data, parent))
		return false;

	NODE * newNode = new NODE(data, parent);
	if (parent->data < data)
		parent->right = newNode;
	else
		parent->left = newNode;

	// RB규칙 맞추기
	for(NODE * checkNode = newNode; 
		checkNode != _rootNode; 
		checkNode = checkNode->parent)
	{
		parent = checkNode->parent;

		if (CheckRedRule(checkNode))
			continue;
	
		// 부모가 할아버지의 좌측
		if (checkNode->parent == checkNode->parent->parent->left)
		{
			// 3촌 노드가 레드
			if(checkNode->parent->parent->right->color == RED)
			{
				checkNode->parent->color = BLACK;
				if(checkNode->parent->parent == _rootNode)
					checkNode->parent->parent->color = BLACK;
				else
					checkNode->parent->parent->color = RED;
				checkNode->parent->parent->right->color = BLACK;
			}
			// 3촌 노드가 블랙
			else 
			{
				// 내가 부모의 오른쪽
				if (parent->data < checkNode->data)
				{
					LeftRotation(parent);
					NODE * temp = checkNode;
					checkNode = parent;
					parent = temp;
				}
				// 내가 부모의 왼쪽
				RightRotation(parent->parent);
				parent->color = BLACK;
				parent->right->color = RED;
			}
		}
		// 부모가 할아버지의 우측
		else
		{
			// 3촌 노드가 레드
			if (checkNode->parent->parent->left->color == RED)
			{
				checkNode->parent->color = BLACK;
				if (checkNode->parent->parent == _rootNode)
					checkNode->parent->parent->color = BLACK;
				else
					checkNode->parent->parent->color = RED;
				checkNode->parent->parent->left->color = BLACK;
			}
			// 3촌 노드가 블랙
			else
			{
				// 내가 부모의 왼쪽
				if (checkNode->data < parent->data)
				{
					RightRotation(parent);
					NODE * temp = checkNode;
					checkNode = parent;
					parent = temp;
				}
				// 내가 부모의 오른쪽
				LeftRotation(parent->parent);
				parent->color = BLACK;
				parent->left->color = RED;
			}
		}
	}
	_rootNode->color = BLACK;
	return true;
}

bool RB_BinaryTree::Delete(int data)
{
	NODE * target = nullptr;
	if (!Search(data, target))
		return false;

	NODE * replaceNode = target;
	// 자식이 둘이면 대체노드 찾아야함
	if (target->left != _nilNode && target->right != _nilNode)
		FindReplaceNode(target, replaceNode);
	target->data = replaceNode->data;

	// 지우는게 유일한 루트노드
	if (replaceNode == _rootNode && replaceNode->right == _nilNode)
	{
		delete replaceNode;
		_rootNode = _nilNode;
		return true;
	}

	NODE * problem;
	NODE * sibling;
	// 링크 끊고 연결하기
	if (replaceNode == replaceNode->parent->left)
	{
		if (replaceNode->left == _nilNode)
		{
			replaceNode->parent->left = replaceNode->right;
			problem = replaceNode->right;
		}
		else
		{
			replaceNode->parent->left = replaceNode->left;
			problem = replaceNode->left;
		}
	}
	else if (replaceNode == replaceNode->parent->right)
	{
		if (replaceNode->left == _nilNode)
		{
			replaceNode->parent->right = replaceNode->right;
			problem = replaceNode->right;
		}
		else
		{
			replaceNode->parent->right = replaceNode->left;
			problem = replaceNode->left;
		}
	}
	else
	{
		if (replaceNode->left == _nilNode)
		{
			replaceNode->parent->left = replaceNode->right; 
			problem = replaceNode->right;
		}
		else
		{
			replaceNode->parent->left = replaceNode->left;
			problem = replaceNode->left;
		}
	}

	replaceNode->left->parent = replaceNode->parent;

	sibling = Sibling(problem);

	// RB밸런스 맞추기
	// 1. 삭제된 노드가 레드면 그냥 끝
	if (replaceNode->color == RED)
	{
		delete replaceNode;
		return true;
	}

	// ㄹㅇ삭제
	delete replaceNode;

	// 루프시작
	// 2. 삭제된 노드가 블랙
	while (problem!=_rootNode)
	{
		// 2.1 삭제된 노드는 블랙이지만 그 자식이 레드였다
		if (problem->color == RED)
		{
			problem->color = BLACK;
			return true;
		}
		// 그것도 아니었으니 형제노드를 봐야한다
		else
		{
			// 2.2 삭제된 노드의 형제가 레드
			if (sibling->color == RED)
			{
				sibling->color = BLACK;
				problem->parent->color = RED;
				if (problem == problem->parent->left)
					LeftRotation(problem->parent);
				else
					RightRotation(problem->parent);
				sibling = Sibling(problem);
				// 재검사
			}
			// 2.3~
			else
			{
				// 2.3 삭제된 노드의 형제가 블랙이고 형제의 양쪽 자식이 블랙
				if (sibling->left->color == BLACK && sibling->right->color == BLACK)
				{
					sibling->color = RED;
					problem = problem->parent;
					sibling = Sibling(problem);
				}
				else
				{
					// 형제가 부모의 왼쪽일때
					if (sibling == sibling->parent->left)
					{
						// 2.4 삭제 노드의 형제가 블랙이고 형제의 오른자식이 레드
						if (sibling->right->color == RED)
						{
							sibling->right->color = BLACK;
							sibling->color = RED;
							LeftRotation(sibling);
							sibling = problem->parent->left;
						}
						// 2.5 삭제 노드의 형제가 블랙이고 형제의 왼자식이 레드
						sibling->color = problem->parent->color;
						problem->parent->color = BLACK;
						sibling->left->color = BLACK;
						RightRotation(problem->parent);
						return true;
					}
					// 형제가 부모의 오른쪽일때
					else
					{
						// 2.4 삭제 노드의 형제가 블랙이고 형제의 오른자식이 레드
						if (sibling->left->color == RED)
						{
							sibling->left->color = BLACK;
							sibling->color = RED;
							RightRotation(sibling);
							sibling = problem->parent->left;
						}
						// 2.5 삭제 노드의 형제가 블랙이고 형제의 왼자식이 레드
						sibling->color = problem->parent->color;
						problem->parent->color = BLACK;
						sibling->right->color = BLACK;
						LeftRotation(problem->parent);
						return true;
					}
				}
			}
		}
	}

	return true;
}

void RB_BinaryTree::Print(HWND hWnd)
{
	RECT rect;	
	GetClientRect(hWnd, &rect);
	HDC hdc = GetDC(hWnd);
	int radius = 25;
	int parentX, parentY, curX, curY;
	parentX = curX = (rect.right - rect.left) / 2;
	parentY = curY = (30);
	int treeLevel = 1;

	if (_rootNode != _nilNode)
	{
		CalculateLevel(_rootNode, 0, &treeLevel);
		//InsertDNode(_rootNode, curX, curY, parentX, parentY);
		InsertDNode2(_rootNode, rect, 1, 2, 20, 0, 0);
	}

	SelectObject(hdc, PEN(1));
	for (int i = 1; i < index; ++i)
	{
		MoveToEx(hdc, arr[i].x, arr[i].y, NULL);
		LineTo(hdc, arr[i].px, arr[i].py);
	}

	SelectObject(hdc, GDICOLOR()->_nullPen);
	for (int i = 0; i < index; ++i)
	{
		switch (arr[i].node->color)
		{
		case RED:
			SelectObject(hdc, _redBrush);
			break;
		case BLACK:
			SelectObject(hdc, _blackBrush);
			break;
		}
		Pie(hdc, arr[i].x - radius, arr[i].y - radius, arr[i].x + radius, arr[i].y + radius, 0, 0, 0, 0);
		char buffer[32];
		_itoa_s(arr[i].node->data, buffer, 10);
		TextOutA(hdc, arr[i].x, arr[i].y, buffer, (int)strlen(buffer));
	}
	index = 0;
	ReleaseDC(hWnd, hdc);
}

RB_BinaryTree::NODE * RB_BinaryTree::_nilNode;