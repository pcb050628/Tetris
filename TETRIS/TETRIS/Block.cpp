#include "Block.h"
#include "Square.h"
#include "GameBoard.h"

void Block::Update()
{
	bool dstry = true;
	for (int i = 0; i < 4; i++)
	{
		if (m_Squares[i] != nullptr)
			dstry = false;
	}

	if (dstry)
		Destroy();
}

void Block::Render(HDC _dc)
{
	for (int i = 0; i < 4; i++)
	{
		if(m_Squares[i] != nullptr)
			m_Squares[i]->Render(_dc);
	}
}

void Block::Down()
{
	Uncheck();

	m_MatrixCoord += Vec2(1, 0);

	Recheck();
}

void Block::DownByDestroy(int _row, int _count)
{
	Uncheck();

	m_MatrixCoord += Vec2(1 * _count, 0);

	RecheckWithRow(_row, _count);
}

void Block::Right()
{
	Uncheck();

	m_MatrixCoord += Vec2(0, 1);

	Recheck();
}

void Block::Left()
{
	Uncheck();

	m_MatrixCoord += Vec2(0, -1);

	Recheck();
}

void Block::RotateRight()
{
	Uncheck();

	for (int sq = 0; sq < 4; sq++)
	{
		if (m_Squares[sq] != nullptr)
		{
			m_Squares[sq]->RotateRight();
		}
	}

	Recheck();
}

void Block::RotateLeft()
{
	Uncheck();

	for (int sq = 0; sq < 4; sq++)
	{
		if (m_Squares[sq] != nullptr)
		{
			m_Squares[sq]->RotateLeft();
		}
	}

	Recheck();
}

void Block::Recheck()
{
	for (int sq = 0; sq < 4; sq++)
	{
		if (m_Squares[sq] != nullptr)
		{
			m_Squares[sq]->SetMatrixCoord(m_Squares[sq]->m_AdditionalCoord + m_MatrixCoord);
			if (m_Squares[sq]->GetMatrixCoord().x > (GBOARD_ROW - 1))
			{
				delete m_Squares[sq];
				m_Squares[sq] = nullptr;
				continue;
			}

			m_Owner->MatrixFill(m_Squares[sq]->GetMatrixCoord(), m_Squares[sq]);
			m_Squares[sq]->SetPosByMatrixCoord();
		}
	}
}

void Block::RecheckWithRow(int _row, int _count)
{
	for (int sq = 0; sq < 4; sq++)
	{
		if (m_Squares[sq] != nullptr)
		{
			m_Squares[sq]->SetMatrixCoord(m_Squares[sq]->m_AdditionalCoord + m_MatrixCoord);
			if (_row < m_Squares[sq]->GetMatrixCoord().x - _count)
			{
				m_Squares[sq]->SetAdditionalCoord(m_Squares[sq]->GetAdditionalCoord() + Vec2(-1 * _count, 0));
				m_Squares[sq]->SetMatrixCoord(m_Squares[sq]->m_AdditionalCoord + m_MatrixCoord);
			}
			else if (m_Squares[sq]->GetMatrixCoord().x > (GBOARD_ROW - 1))
			{
				delete m_Squares[sq];
				m_Squares[sq] = nullptr;
				continue;
			}
			
			m_Owner->MatrixFill(m_Squares[sq]->GetMatrixCoord(), m_Squares[sq]);
			m_Squares[sq]->SetPosByMatrixCoord();
		}
	}
}

void Block::Uncheck()
{
	for (int sq = 0; sq < 4; sq++)
	{
		if (m_Squares[sq] != nullptr)
		{
			m_Owner->MatrixFill(m_Squares[sq]->m_AdditionalCoord + m_MatrixCoord, nullptr);
		}
	}
}

std::vector<Vec2> Block::GetLowestCoord()
{
	std::vector<Vec2> lowests;

	for (int sq = 0; sq < 4; sq++)
	{
		if (m_Squares[sq] == nullptr)
			continue;
		
		bool can = true;
		for (int oq = 0; oq < 4; oq++)
		{
			if (sq == oq || m_Squares[oq] == nullptr)
				continue;

			if (m_Squares[sq]->m_AdditionalCoord.y == m_Squares[oq]->m_AdditionalCoord.y && m_Squares[sq]->m_AdditionalCoord.x < m_Squares[oq]->m_AdditionalCoord.x)
				can = false;
		}

		if (can)
		{
			lowests.push_back(m_Squares[sq]->GetMatrixCoord());
		}
	}

	return lowests;
}

std::vector<Vec2> Block::GetRightmostCoord()
{
	std::vector<Vec2> mostRight;

	for (int sq = 0; sq < 4; sq++)
	{
		if (m_Squares[sq] == nullptr)
			continue;

		bool can = true;
		for (int oq = 0; oq < 4; oq++)
		{
			if (sq == oq || m_Squares[oq] == nullptr)
				continue;

			if (m_Squares[sq]->m_AdditionalCoord.x == m_Squares[oq]->m_AdditionalCoord.x && m_Squares[sq]->m_AdditionalCoord.y < m_Squares[oq]->m_AdditionalCoord.y)
				can = false;
		}

		if(can)
			mostRight.push_back(m_Squares[sq]->m_AdditionalCoord + m_MatrixCoord);
	}

	return mostRight;
}

std::vector<Vec2> Block::GetLeftmostCoord()
{
	std::vector<Vec2> mostLeft;

	for (int sq = 0; sq < 4; sq++)
	{
		if (m_Squares[sq] == nullptr)
			continue;

		bool can = true;
		for (int oq = 0; oq < 4; oq++)
		{
			if (sq == oq || m_Squares[oq] == nullptr)
				continue;

			if (m_Squares[sq]->m_AdditionalCoord.x == m_Squares[oq]->m_AdditionalCoord.x && m_Squares[sq]->m_AdditionalCoord.y > m_Squares[oq]->m_AdditionalCoord.y)
				can = false;
		}

		if (can)
			mostLeft.push_back(m_Squares[sq]->m_AdditionalCoord + m_MatrixCoord);
	}

	return mostLeft;
}

void Block::DestoryASquare(int idx)
{
	m_Owner->MatrixFill(m_Squares[idx]->GetMatrixCoord(), nullptr);

	m_Squares[idx]->Destroy();
	m_Squares[idx] = nullptr;
}

Block::Block(BLOCK_TYPE _type, GameBoard* _gb)
	:m_Type(_type)
	,m_Owner(_gb)
{
	for (int i = 0; i < 4; i++)
	{
		m_Squares[i] = new Square();
		m_Squares[i]->m_Owner = this;
		m_Squares[i]->idx = i;
	}
}

Block::~Block()
{
	for (int i = 0; i < 4; i++)
	{
		if(m_Squares[i] != nullptr)
			delete m_Squares[i];
	}
}
