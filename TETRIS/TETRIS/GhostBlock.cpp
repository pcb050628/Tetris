#include "GhostBlock.h"
#include "Engine.h"
#include "Camera.h"

#include "Square.h"

GhostBlock::GhostBlock(GameBoard* _gb) : Block(BLOCK_TYPE::GHOST, _gb)
	,m_Target(nullptr)
	,distance(0)
{
	m_Scale = SQUARESIZE / 2;
}

GhostBlock::~GhostBlock()
{
}

void GhostBlock::Update()
{
	if (m_Target != nullptr)
	{
		m_Pos = m_Target->GetPos();
	}
}

void GhostBlock::Render(HDC _dc)
{
	if (m_Target != nullptr)
	{
		//COLOR color = m_Target->GetSquare()->GetColor();

		for (int i = 0; i < 4; i++)
		{
			Square* sq = m_Target->GetSquare(i);

			//HPEN prev = (HPEN)SelectObject(_dc, Engine::GetInst()->GetPen(COLOR::BLACK));

			Vec2 rPos = sq->GetPos() - GBOARDHALF + Vec2(0, distance * SQUARESIZE);
			Camera::GetInst()->GetRenderPos(rPos);

			//Rectangle(_dc, rPos.x - m_Scale.x / 2, rPos.y - m_Scale.y / 2, rPos.x + m_Scale.x / 2, rPos.y + m_Scale.y / 2);

			RECT rect =
			{
				(rPos.x - m_Scale.x / 2) + 2, // l
				(rPos.y - m_Scale.y / 2) + 2, // t
				(rPos.x + m_Scale.x / 2) - 2, // r 
				(rPos.y + m_Scale.y / 2) - 2  // b
			};
			FillRect(_dc, &rect, Engine::GetInst()->GetBrush(COLOR::BLACK) /*+ RGB(20, 20, 20)*/);

			//SelectObject(_dc, prev);
		}
	}
}
