#include "Square.h"
#include "Engine.h"
#include "Camera.h"

#include "Block.h"

Square::Square()
{
	m_Scale = SQUARESIZE;
}

Square::~Square()
{
}

void Square::Update()
{

}

void Square::Render(HDC _dc)
{
	HPEN prev = (HPEN)SelectObject(_dc, Engine::GetInst()->GetPen(COLOR::BLACK));

	Vec2 rPos = m_Pos - GBOARDHALF;
	Camera::GetInst()->GetRenderPos(rPos);

	Rectangle(_dc, rPos.x - m_Scale.x / 2, rPos.y - m_Scale.y / 2, rPos.x + m_Scale.x / 2, rPos.y + m_Scale.y / 2);

	RECT rect = 
	{ 
		(rPos.x - m_Scale.x / 2) + 2, // l
		(rPos.y - m_Scale.y / 2) + 2, // t
		(rPos.x + m_Scale.x / 2) - 2, // r 
		(rPos.y + m_Scale.y / 2) - 2  // b
	};
	FillRect(_dc, &rect, Engine::GetInst()->GetBrush(m_Color));

	SelectObject(_dc, prev);
}

Vec2 Square::CoordToChangeRight()
{
	Vec2 value = m_AdditionalCoord;
	value.Switch();
	value.x *= -1;

	return value + m_Owner->GetMatrixCoord();
}

Vec2 Square::CoordToChangeleft()
{
	Vec2 value = m_AdditionalCoord;
	value.x *= -1;
	value.Switch();

	return value + m_Owner->GetMatrixCoord();
}

void Square::SetPosByMatrixCoord()
{
	m_RealCoord = m_Owner->GetMatrixCoord() + m_AdditionalCoord;

	Vec2 pCoord = m_RealCoord;
	pCoord.Switch();
	SetPos(m_Owner->GetPos() + (pCoord * SQUARESIZE));
}

void Square::DestroyASquare()
{
	m_Owner->DestoryASquare(idx);
}

