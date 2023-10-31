#include "Engine.h"

#include "Camera.h"
#include "Input.h"
#include "Time.h"
#include "SceneManager.h"

Engine* Engine::Inst = nullptr;

Engine::Engine()
	:m_hWnd(nullptr)
	,m_DC(nullptr)
	,m_SubDC(nullptr)
	,m_SubBitmap(nullptr)
{
}

Engine::~Engine()
{
}

void Engine::Init(HWND _hwnd, POINT _resolution)
{
	m_hWnd = _hwnd;
	ChangeWindowSize(_resolution, false);
	ShowWindow(m_hWnd, true);

	// DC : Device Context
	// pen : Black 
	// brush : White
	// Bitmap(ê·¸ë¦¼ ê·¸ë¦´ ê³? : ?¸ë“¤???´ë‹¹?˜ëŠ” ?ˆë„??ë¹„íŠ¸ë§?
	m_DC = GetDC(m_hWnd);

	// ì¶”ê? ë¹„íŠ¸ë§?ë²„í¼
	m_SubBitmap = CreateCompatibleBitmap(m_DC, m_Resolution.x, m_Resolution.y);
	m_SubDC = CreateCompatibleDC(m_DC);

	// m_SubDC ê°€ m_SubBitmap ??ëª©ì ì§€ë¡?ì§€?•í•˜ê³? ?ëž˜ ëª©ì ì§€ë¡?ì§€?•í•˜ê³??ˆë˜ BitMap ??ë°˜í™˜ê°’ìœ¼ë¡??˜ì˜¤?”ë°, 
	// ?´ê±¸ ë°”ë¡œ DeleteObject ?¨ìˆ˜???„ë‹¬?œì¼œ???? œ?”ì²­?œë‹¤.
	DeleteObject((HBITMAP)SelectObject(m_SubDC, m_SubBitmap));

	m_arrPen[(UINT)COLOR::RED] = CreatePen(PS_SOLID, 4, RGB(255, 10, 10));
	m_arrPen[(UINT)COLOR::BLUE] = CreatePen(PS_SOLID, 4, RGB(20, 10, 255));
	m_arrPen[(UINT)COLOR::GREEN] = CreatePen(PS_SOLID, 4, RGB(20, 255, 10));
	m_arrPen[(UINT)COLOR::YELLOW] = CreatePen(PS_SOLID, 4, RGB(255, 255, 10));
	m_arrPen[(UINT)COLOR::PURPLE] = CreatePen(PS_SOLID, 4, RGB(255, 10, 255));
	m_arrPen[(UINT)COLOR::MINT] = CreatePen(PS_SOLID, 4, RGB(100, 240, 216));
	m_arrPen[(UINT)COLOR::ORANGE] = CreatePen(PS_SOLID, 4, RGB(255, 102, 10));
	m_arrPen[(UINT)COLOR::GREY] = CreatePen(PS_SOLID, 4, RGB(128, 128, 128));
	m_arrPen[(UINT)COLOR::BLACK] = CreatePen(PS_SOLID, 4, RGB(10, 10, 10));
	m_arrPen[(UINT)COLOR::WHITE] = CreatePen(PS_SOLID, 4, RGB(255, 255, 255));

	m_arrBrush[(UINT)COLOR::RED] = CreateSolidBrush(RGB(255, 10, 10));
	m_arrBrush[(UINT)COLOR::BLUE] = CreateSolidBrush(RGB(10, 10, 255));
	m_arrBrush[(UINT)COLOR::GREEN] = CreateSolidBrush(RGB(10, 255, 10));
	m_arrBrush[(UINT)COLOR::YELLOW] = CreateSolidBrush(RGB(255, 255, 10));
	m_arrBrush[(UINT)COLOR::PURPLE] = CreateSolidBrush(RGB(255, 10, 255));
	m_arrBrush[(UINT)COLOR::MINT] = CreateSolidBrush(RGB(100, 240, 216));
	m_arrBrush[(UINT)COLOR::ORANGE] = CreateSolidBrush(RGB(255, 102, 10));
	m_arrBrush[(UINT)COLOR::GREY] = CreateSolidBrush(RGB(128, 128, 128));
	m_arrBrush[(UINT)COLOR::BLACK] = CreateSolidBrush(RGB(10, 10, 10));
	m_arrBrush[(UINT)COLOR::WHITE] = CreateSolidBrush(RGB(255, 255, 255));

	Time::GetInst()->Init();
	Input::GetInst()->Init();
	SceneManager::GetInst()->Init();
}

void Engine::Run()
{
	Update();
	Render();
}

void Engine::Update()
{
	Time::GetInst()->Update();
	Input::GetInst()->Update();
	Camera::GetInst()->Update();
	SceneManager::GetInst()->Update();
}

void Engine::Render()
{
	RECT rt = {};
	GetClientRect(m_hWnd, &rt);
	m_Resolution.x = rt.right;
	m_Resolution.y = rt.bottom;

	RECT rect = RECT(-1, -1, m_Resolution.x + 1, m_Resolution.y + 1);
	FillRect(m_SubDC, &rect, m_arrBrush[(UINT)COLOR::BLACK]);
	
	SceneManager::GetInst()->Render(m_SubDC);

	BitBlt(m_DC, 0, 0, m_Resolution.x, m_Resolution.y, m_SubDC, 0, 0, SRCCOPY);
}

void Engine::ChangeWindowSize(POINT _resolution, bool _menu)
{
	m_Resolution = _resolution;

	RECT rt = { 0, 0, m_Resolution.x, m_Resolution.y };
	AdjustWindowRect(&rt, WS_OVERLAPPEDWINDOW, _menu);
	SetWindowPos(m_hWnd, nullptr, 10, 10, rt.right - rt.left, rt.bottom - rt.top, 0);
}