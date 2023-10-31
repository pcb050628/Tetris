#include "OBlock.h"
#include "Square.h"

OBlock::OBlock(GameBoard* _gb) : Block(BLOCK_TYPE::O, _gb)
{
	m_Squares[0]->SetAdditionalCoord(Vec2(0, -1));
	m_Squares[1]->SetAdditionalCoord(Vec2(0, 0));
	m_Squares[2]->SetAdditionalCoord(Vec2(1, -1));
	m_Squares[3]->SetAdditionalCoord(Vec2(1, 0));

	m_Center = m_Squares[1];

	for (int i = 0; i < 4; i++)
	{
		m_Squares[i]->SetColor(COLOR::YELLOW);
	}
}

OBlock::~OBlock()
{
}

void OBlock::RotateRight()
{
}

void OBlock::RotateLeft()
{
}
