#include "UI.h"
#include "Engine.h"
#include "Camera.h"

UI::UI()
	:mb_IsPreesed(false)
{
	m_Scale = SQUARESIZE;
}

UI::~UI()
{
}

void UI::Update()
{
	Vec2 rPos = m_Pos;
	Camera::GetInst()->GetRenderPos(rPos);

	Vec2 LeftTop = rPos - m_Scale / 2;
	Vec2 RightBottom = rPos + m_Scale / 2;

	Vec2 mPos = Input::GetInst()->GetMousePos();

	if (LeftTop.x < mPos.x && LeftTop.y < mPos.y 
		&& RightBottom.x > mPos.x && RightBottom.y > mPos.y)
	{
		if (KEY_PRESSED(KEY::LBTN))
		{
			OnClick(mPos);
			mb_IsPreesed = true;
		}
		else if (KEY_HOLD(KEY::LBTN))
		{
			OnHold(mPos);
			mb_IsPreesed = true;
		}
		else if (KEY_RELEASE(KEY::LBTN))
		{
			OnRelease(mPos);
			mb_IsPreesed = false;
		}
	}
	else
	{
		mb_IsPreesed = false;
	}
}

void UI::Render(HDC _dc)
{
	HPEN prev = (HPEN)SelectObject(_dc, Engine::GetInst()->GetPen(COLOR::BLUE));
	
	Vec2 rPos = m_Pos;
	Camera::GetInst()->GetRenderPos(rPos);
	
	Rectangle(_dc, rPos.x - m_Scale.x / 2, rPos.y - m_Scale.y / 2, rPos.x + m_Scale.x / 2, rPos.y + m_Scale.y / 2);
	
	RECT rect =
	{
		(rPos.x - m_Scale.x / 2) + 2, // l
		(rPos.y - m_Scale.y / 2) + 2, // t
		(rPos.x + m_Scale.x / 2) - 2, // r 
		(rPos.y + m_Scale.y / 2) - 2  // b
	};
	FillRect(_dc, &rect, Engine::GetInst()->GetBrush(COLOR::BLUE));
	
	SelectObject(_dc, prev);
}

void UI::OnClick(Vec2 _MousePos)
{
}

void UI::OnHold(Vec2 _MousePos)
{
}

void UI::OnRelease(Vec2 _MousePos)
{
}
