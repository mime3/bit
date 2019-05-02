
// ChildView.h: CChildView 클래스의 인터페이스
//


#pragma once


// CChildView 창

class CChildView : public CWnd
{
public:
	enum SHAPE
	{
		CIRCLE = 1,
		RECT,
		LINE,
		CROSS,
		APPLE
	};
// 생성입니다.
public:
	CChildView();

// 특성입니다.
public:
	SHAPE _option;
// 작업입니다.
public:

// 재정의입니다.
	protected:
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);

// 구현입니다.
public:
	virtual ~CChildView();

	// 생성된 메시지 맵 함수
protected:
	afx_msg void OnPaint();
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnFigCir();
	afx_msg void OnFigRect();
	afx_msg void OnFigLine();
	afx_msg void OnFigCross();
	afx_msg void OnFigApple();
};

