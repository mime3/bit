#pragma once
#include <Windows.h>

class RB_BinaryTree
{
public:
	enum COLOR
	{
		RED,
		BLACK
	};
	struct NODE
	{
		int data;
		NODE * parent;
		NODE * left;
		NODE * right;
		COLOR color;
		NODE(int data, NODE * parent);
	};
	struct DNODE
	{
		int x;
		int y;
		int px;
		int py;
		NODE * node;
	};
	static NODE * _nilNode;
	
	DNODE arr[100];
	int index = 0;
private:
	NODE * _rootNode;

	HBRUSH _redBrush;
	HBRUSH _blackBrush;

protected:
	bool Search(int data, NODE * &node);
	void LeftRotation(NODE * node);
	void RightRotation(NODE * node);
	bool CheckRedRule(NODE * node);
	void FindReplaceNode(NODE * targetNode, NODE * &replaceNode);
	void InsertDNode(NODE * node, int x, int y, int px, int py);
	void InsertDNode2(NODE * node, RECT rect, int a, int b, int y, int px, int py);
	int CalculateLevel(NODE * node, int level, int *highLevel);
	NODE * Sibling(NODE * node);
public:
	RB_BinaryTree();
	~RB_BinaryTree();
	bool Insert(int data);
	bool Delete(int data);
	void Print(HWND hWnd);
	void PrintDNode(HDC hdc, NODE * node);
};

