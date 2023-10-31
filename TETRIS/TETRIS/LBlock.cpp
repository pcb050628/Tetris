#include "LBlock.h"
#include "Square.h"
#include "GameBoard.h"

LBlock::LBlock(GameBoard* _gb) : Block(BLOCK_TYPE::L, _gb)
{
	m_Squares[0]->SetAdditionalCoord(Vec2(0, -1));
	m_Squares[1]->SetAdditionalCoord(Vec2(0, 0));
	m_Squares[2]->SetAdditionalCoord(Vec2(0, 1));
	m_Squares[3]->SetAdditionalCoord(Vec2(-1, 1));

	m_Center = m_Squares[1];

	for (int i = 0; i < 4; i++)
	{
		m_Squares[i]->SetColor(COLOR::ORANGE);
	}
}

LBlock::~LBlock()
{
}