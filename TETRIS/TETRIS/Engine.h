#pragma once
#include "framework.h"
#include "enums.h"

class Engine
{
private:
	Engine();
	~Engine();

	static Engine* Inst;

public:
	static Engine* GetInst()
	{
		if (Inst == nullptr)
			Inst = new Engine;
		
		return Inst;
	}

private:
	HWND	m_hWnd;
	POINT	m_Resolution;

	HDC		m_DC;
	HDC		m_SubDC;
	HBITMAP	m_SubBitmap;

	HPEN	m_arrPen[(UINT)COLOR::END]; // 
	HBRUSH	m_arrBrush[(UINT)COLOR::END];

public:
	void ChangeWindowSize(POINT _resolution, bool _menu);
	POINT GetResolution() { return m_Resolution; }

	HWND GetHwnd() { return m_hWnd; }

	HPEN GetPen(COLOR _color) { return m_arrPen[(UINT)_color]; }
	HBRUSH GetBrush(COLOR _color) { return m_arrBrush[(UINT)_color]; }

public:
	void Init(HWND _hwnd, POINT _resolution);
	void Run();
	void Update();
	void Render();

};

