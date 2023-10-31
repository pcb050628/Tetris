#include "GameBoard.h"
#include "Engine.h"
#include "Camera.h"
#include "SceneManager.h"

#include "Square.h"
#include "blocks.h"

GameBoard::GameBoard()
	:moveInterval(1.f)
	,InputInterval(0.2f)
	,ClearInterval(1.5f)
	,mb_canChange(false)
{
	m_NextBlockToRender.resize(5);
}

GameBoard::~GameBoard()
{
}

void GameBoard::Update()
{
	if (m_BlockBag1.size() < 5)
	{
		if (m_BlockBag2.empty())
		{
			std::vector<int> created = {};
			while (m_BlockBag2.size() < 5)
			{
				std::mt19937 gen(rd());
				unsigned int r = gen();
				r %= 7;

				while (true)
				{
					bool flag = true;

					for (int i = 0; i < created.size(); i++)
					{
						if (r == created[i])
						{
							flag = false;
						}
					}

					if (flag)
					{
						created.push_back(r);
						break;
					}

					r = gen();
					r %= 7;
				}

				m_BlockBag2.push((BLOCK_TYPE)r);
			}
		}

		m_BlockBag1.push_back(m_BlockBag2.front());
		m_BlockBag2.pop();
	}

	if (m_CurBlock == nullptr)
	{
		if (!mb_canChange)
			mb_canChange = true;
		LineCheck();
		CreateBlock();
	}
	else
	{
		if (moveInterval < DownCount && CanMoveDown())
		{
			m_CurBlock->Down();
			DownCount = 0;
			LineCheck();
		}
		else if (moveInterval < DownCount && !CanMoveDown())
		{
			if (m_CurBlock->GetMatrixCoord().x == 0)
				SceneManager::GetInst()->ChangeScene(SCENE_TYPE::TITLE);

			m_CurBlock = nullptr;
		}
		else
		{
			DownCount += DT;
		}

		if (KEY_HOLD(KEY::R) && ClearCount < ClearInterval)
		{
			ClearCount += DT;
		}
		else if (KEY_HOLD(KEY::R) && ClearCount > ClearInterval)
		{
			ClearCount = 0;
			BoardClear();
			return;
		}

		if (KEY_PRESSED(KEY::SPACE))
		{
			while (CanMoveDown())
			{
				m_CurBlock->Down();
			}

			m_CurBlock = nullptr;
			return;
		}

		if (KEY_PRESSED(KEY::Z) && CanRotateRight())
		{
			m_CurBlock->RotateRight();
		}

		if (KEY_PRESSED(KEY::X) && CanRotateleft())
		{
			m_CurBlock->RotateLeft();
		}

		if (KEY_PRESSED(KEY::C) && mb_canChange) // 메트릭스에서 현재 블럭을 전부 제거 후 변경 하도록 수정해야함
		{
			BlockChange();
			return;
		}

		if (KEY_PRESSED(KEY::RIGHT) && CanMoveRight())
		{
			m_CurBlock->Right();
			InputCount = 0;
		}

		if (KEY_PRESSED(KEY::LEFT) && CanMoveLeft())
		{
			m_CurBlock->Left();
			InputCount = 0;
		}

		if (KEY_PRESSED(KEY::DOWN) && CanMoveDown())
		{
			m_CurBlock->Down();
			InputCount = 0;
		}

		if (InputCount > InputInterval)
		{
			if (KEY_HOLD(KEY::RIGHT) && CanMoveRight())
			{
				m_CurBlock->Right();
			}

			if (KEY_HOLD(KEY::LEFT) && CanMoveLeft())
			{
				m_CurBlock->Left();
			}

			if (KEY_HOLD(KEY::DOWN) && CanMoveDown())
			{
				m_CurBlock->Down();
			}


			InputCount = 0;
		}
		else
		{
			InputCount += DT;
		}

		LineCheck();
		SetGhostBlockDistance();
	}
}

void GameBoard::Render(HDC _dc) 
{
	Vec2 rPos = m_Pos - GBOARDHALF;
	Camera::GetInst()->GetRenderPos(rPos);

	{
		HPEN prev = (HPEN)SelectObject(_dc, Engine::GetInst()->GetPen(COLOR::GREY));
		for (int row = 0; row < GBOARD_ROW; row++)
		{
			for (int col = 0; col < GBOARD_COLUMN; col++)
			{
				Vec2 lPos = rPos + (Vec2(col, row) * SQUARESIZE);

				Rectangle(_dc, (lPos.x - SQUARESIZE / 2), (lPos.y - SQUARESIZE / 2), (lPos.x + SQUARESIZE / 2), (lPos.y + SQUARESIZE / 2));
			}
		}
		SelectObject(_dc, prev);
	}

	// 벽만들어서 m_NextBlockToRender 벽안에 넣기
	{
		HPEN prev = (HPEN)SelectObject(_dc, Engine::GetInst()->GetPen(COLOR::GREY));
		for (int row = 0; row < 21; row++)
		{
			for (int col = 0; col < 8; col++)
			{
				if (row == 0 || col == 0
					|| row == 20 || col == 7)
				{
					Vec2 lPos = rPos + (Vec2(col, row) * SQUARESIZE) + Vec2(480, 0);

					Rectangle(_dc, (lPos.x - SQUARESIZE / 2), (lPos.y - SQUARESIZE / 2), (lPos.x + SQUARESIZE / 2), (lPos.y + SQUARESIZE / 2));
				}
			}
		}

		for (int row = 0; row < 6; row++)
		{
			for (int col = 0; col < 7; col++)
			{
				if (row == 0 || col == 0
					|| row == 5 || col == 6)
				{
					Vec2 lPos = rPos + (Vec2(col, row) * SQUARESIZE) + Vec2(-360, 100);

					Rectangle(_dc, (lPos.x - SQUARESIZE / 2), (lPos.y - SQUARESIZE / 2), (lPos.x + SQUARESIZE / 2), (lPos.y + SQUARESIZE / 2));
				}
			}
		}
		SelectObject(_dc, prev);
	}

	{
		for (int i = 0; i < m_BlockBag1.size(); i++)
		{
			if (m_NextBlockToRender[i] == nullptr
				|| m_NextBlockToRender[i]->m_Type != m_BlockBag1[i])
			{
				if (m_NextBlockToRender[i] != nullptr)
				{
					m_NextBlockToRender[i]->Destroy();
				}

				switch (m_BlockBag1[i])
				{
				case BLOCK_TYPE::L:
					m_NextBlockToRender[i] = new LBlock(this);
					break;
				case BLOCK_TYPE::J:
					m_NextBlockToRender[i] = new JBlock(this);
					break;
				case BLOCK_TYPE::T:
					m_NextBlockToRender[i] = new TBlock(this);
					break;
				case BLOCK_TYPE::I:
					m_NextBlockToRender[i] = new IBlock(this);
					break;
				case BLOCK_TYPE::S:
					m_NextBlockToRender[i] = new SBlock(this);
					break;
				case BLOCK_TYPE::Z:
					m_NextBlockToRender[i] = new ZBlock(this);
					break;
				case BLOCK_TYPE::O:
					m_NextBlockToRender[i] = new OBlock(this);
					break;
				}

				m_NextBlockToRender[i]->SetPos(m_Pos + Vec2(600, 100) + Vec2(0, i * 150));
				for (int s = 0; s < 4; s++)
				{
					m_NextBlockToRender[i]->GetSquare(s)->SetPosByMatrixCoord();
				}
				SceneManager::GetInst()->AddObjAtCurScene(LAYER::BLOCK, m_NextBlockToRender[i]);
			}
		}
	}
}

void GameBoard::CreateBlock()
{
	Block* block = nullptr;

	switch ((*m_BlockBag1.begin()))
	{
	case BLOCK_TYPE::L:
		block = new LBlock(this);
		break;
	case BLOCK_TYPE::J:
		block = new JBlock(this);
		break;
	case BLOCK_TYPE::T:
		block = new TBlock(this);
		break;
	case BLOCK_TYPE::I:
		block = new IBlock(this);
		break;
	case BLOCK_TYPE::S:
		block = new SBlock(this);
		break;
	case BLOCK_TYPE::Z:
		block = new ZBlock(this);
		break;
	case BLOCK_TYPE::O:
		block = new OBlock(this);
		break;
	}

	m_BlockBag1.erase(m_BlockBag1.begin());

	SceneManager::GetInst()->AddObjAtCurScene(LAYER::BLOCK, block);
	m_CurBlock = block;
	m_CurBlock->SetMatrixCoord(Vec2(0, 4));
	if (m_GhostBlock == nullptr)
	{
		m_GhostBlock = new GhostBlock(this);
		SceneManager::GetInst()->AddObjAtCurScene(LAYER::BLOCK, m_GhostBlock);
	}
	m_GhostBlock->SetTarget(m_CurBlock);
}

void GameBoard::CreateBlock(BLOCK_TYPE _type)
{
	Block* block = nullptr;

	switch (_type)
	{
	case BLOCK_TYPE::L:
		block = new LBlock(this);
		break;
	case BLOCK_TYPE::J:
		block = new JBlock(this);
		break;
	case BLOCK_TYPE::T:
		block = new TBlock(this);
		break;
	case BLOCK_TYPE::I:
		block = new IBlock(this);
		break;
	case BLOCK_TYPE::S:
		block = new SBlock(this);
		break;
	case BLOCK_TYPE::Z:
		block = new ZBlock(this);
		break;
	case BLOCK_TYPE::O:
		block = new OBlock(this);
		break;
	}

	SceneManager::GetInst()->AddObjAtCurScene(LAYER::BLOCK, block);
	m_CurBlock = block;
	m_CurBlock->SetMatrixCoord(Vec2(0, 4));
	if (m_GhostBlock == nullptr)
	{
		m_GhostBlock = new GhostBlock(this);
		SceneManager::GetInst()->AddObjAtCurScene(LAYER::BLOCK, m_GhostBlock);
	}
	m_GhostBlock->SetTarget(m_CurBlock);
}

void GameBoard::SetGhostBlockDistance()
{
	if (m_GhostBlock != nullptr && m_CurBlock != nullptr)
	{
		int dist = -1;

		std::vector<Vec2> lowests = m_CurBlock->GetLowestCoord();
		for (Vec2 lowest : lowests)
		{
			if (lowest.x < 0)
				continue;

			int d = 0;

			if (lowest.x == 19)
			{
				m_GhostBlock->SetDistance(0);
				return;
			}

			while (true)
			{
				if (lowest.x + d < (GBOARD_ROW - 1)
					&& (m_Matrix[(unsigned int)lowest.x + d][(unsigned int)lowest.y] == nullptr
						|| m_Matrix[(unsigned int)lowest.x + d][(unsigned int)lowest.y]->GetOwner() == m_CurBlock))
					++d;
				else if (m_Matrix[(unsigned int)lowest.x + d][(unsigned int)lowest.y] != nullptr)
				{
					d--;
					break;
				}
				else
					break;
			}

			if (dist > d || dist == -1)
			{
				dist = d;
			}
		}

		m_GhostBlock->SetDistance(dist);
	}
}

void GameBoard::BlockChange()
{
	if (m_CurBlock != nullptr)
	{
		mb_canChange = false;

		BLOCK_TYPE type = m_SaveBlockType;
		m_SaveBlockType = m_CurBlock->m_Type;
		m_CurBlock->Uncheck();
		m_CurBlock->Destroy();
		m_CurBlock = nullptr;
		if (type != BLOCK_TYPE::GHOST)
		{
			CreateBlock(type);
		}

		if (m_SaveBlockToRender != nullptr)
		{
			m_SaveBlockToRender->Destroy();
			m_SaveBlockToRender = nullptr;
		}

		switch (m_SaveBlockType)
		{
		case BLOCK_TYPE::O:
			m_SaveBlockToRender = new OBlock(this);
			break;
		case BLOCK_TYPE::J:
			m_SaveBlockToRender = new JBlock(this);
			break;
		case BLOCK_TYPE::L:
			m_SaveBlockToRender = new LBlock(this);
			break;
		case BLOCK_TYPE::Z:
			m_SaveBlockToRender = new ZBlock(this);
			break;
		case BLOCK_TYPE::S:
			m_SaveBlockToRender = new SBlock(this);
			break;
		case BLOCK_TYPE::I:
			m_SaveBlockToRender = new IBlock(this);
			break;
		case BLOCK_TYPE::T:
			m_SaveBlockToRender = new TBlock(this);
			break;
		}

		m_SaveBlockToRender->SetPos(m_Pos + Vec2(-250, 200));
		for (int s = 0; s < 4; s++)
		{
			m_SaveBlockToRender->GetSquare(s)->SetPosByMatrixCoord();
		}
		SceneManager::GetInst()->AddObjAtCurScene(LAYER::BLOCK, m_SaveBlockToRender);
		
	}
}

void GameBoard::BoardClear()
{
	for (int row = 0; row < GBOARD_ROW; row++)
	{
		for (int col = 0; col < GBOARD_COLUMN; col++)
		{
			if (m_Matrix[row][col] != nullptr)
			{
				m_Matrix[row][col]->DestroyASquare();
			}
		}
	}

	m_CurBlock = nullptr;

	if (m_GhostBlock != nullptr)
		m_GhostBlock->SetTarget(nullptr);
}

bool GameBoard::CanMoveDown()
{
	if (m_CurBlock != nullptr)
	{
		std::vector<Vec2> lowests = m_CurBlock->GetLowestCoord();
		for (Vec2 lowest : lowests)
		{
			if (lowest.x >= GBOARD_ROW - 1 || m_Matrix[(int)lowest.x + 1][(int)lowest.y] != nullptr)
				return false;
		}

		return true;
	}

	return false;
}

bool GameBoard::CanMoveRight()
{
	if (m_CurBlock != nullptr)
	{
		std::vector<Vec2> mostRights = m_CurBlock->GetRightmostCoord();
		for (Vec2 mostRight : mostRights)
		{
			if (mostRight.x < 0)
				continue;

			if (mostRight.y >= GBOARD_COLUMN - 1 || m_Matrix[(int)mostRight.x][(int)mostRight.y + 1] != nullptr)
				return false;
		}

		return true;
	}

	return false;
}

bool GameBoard::CanMoveLeft()
{
	if (m_CurBlock != nullptr)
	{
		std::vector<Vec2> mostLefts = m_CurBlock->GetLeftmostCoord();
		for (Vec2 mostLeft : mostLefts)
		{
			if (mostLeft.x < 0)
				continue;

			if (mostLeft.y == 0 || m_Matrix[(int)mostLeft.x][(int)mostLeft.y - 1] != nullptr)
				return false;
		}

		return true;
	}

	return false;
}

bool GameBoard::CanRotateRight()
{
	if (m_CurBlock != nullptr)
	{
		for (int i = 0; i < 4; i++)
		{
			Vec2 sMatrixCoord = m_CurBlock->GetSquare(i)->CoordToChangeRight();
			if (sMatrixCoord.x < 0)
				continue;

			if (sMatrixCoord.x >= GBOARD_ROW 
				|| sMatrixCoord.y >= GBOARD_COLUMN || sMatrixCoord.y < 0
				|| m_Matrix[(unsigned int)sMatrixCoord.x][(unsigned int)sMatrixCoord.y] != nullptr
				&& m_Matrix[(unsigned int)sMatrixCoord.x][(unsigned int)sMatrixCoord.y]->GetOwner() != m_CurBlock->GetSquare(i)->GetOwner())
			{
				return false;
			}
		}

		return true;
	}

	return false;
}

bool GameBoard::CanRotateleft()
{
	if (m_CurBlock != nullptr)
	{
		for (int i = 0; i < 4; i++)
		{
			Vec2 sMatrixCoord = m_CurBlock->GetSquare(i)->CoordToChangeleft();
			if (sMatrixCoord.x < 0)
				continue;

			if (sMatrixCoord.x >= GBOARD_ROW 
				|| sMatrixCoord.y >= GBOARD_COLUMN || sMatrixCoord.y < 0
				|| m_Matrix[(unsigned int)sMatrixCoord.x][(unsigned int)sMatrixCoord.y] != nullptr
				&& m_Matrix[(unsigned int)sMatrixCoord.x][(unsigned int)sMatrixCoord.y]->GetOwner() != m_CurBlock->GetSquare(i)->GetOwner())
			{
				return false;
			}
		}

		return true;
	}

	return false;
}

void GameBoard::LineCheck()
{
	for (int row = (GBOARD_ROW - 1); row > -1; row--)
	{
		bool can = true;
		for (int col = 0; col < GBOARD_COLUMN; col++)
		{
			if (m_Matrix[row][col] == nullptr)
				can = false;
			else if (m_Matrix[row][row] != nullptr && m_CurBlock != nullptr && m_Matrix[row][col]->GetOwner() == m_CurBlock)
				can = false;
		}

		if (can)
		{
			m_LineToDestroy.push(row);
		}
	}

	DestroyLine();
}

void GameBoard::DestroyLine()
{
	int highestRow = (GBOARD_ROW - 1);

	int count = 0;
	while (!m_LineToDestroy.empty())
	{
		int row = m_LineToDestroy.front();

		highestRow = row - 1;

		for (int col = 0; col < GBOARD_COLUMN; col++)
		{
			m_Matrix[row][col]->DestroyASquare();
			m_Matrix[row][col] = nullptr;
		}

		m_LineToDestroy.pop(); 
		count++;
	}

	if (highestRow < 19)
	{
		LineDown(highestRow, count);
	}
}

void GameBoard::LineDown(int _row, int _count)
{
	std::vector<Block*> alreadyDown = {};

	for (int row = _row; row > -1; row--)
	{
		for (int col = 0; col < GBOARD_COLUMN; col++)
		{
			if (m_Matrix[row][col] == nullptr)
				continue;

			Square* sq = m_Matrix[row][col];

			MatrixFill(sq->GetMatrixCoord(), nullptr);
			sq->SetAdditionalCoord(sq->GetAdditionalCoord() + Vec2(1 * _count, 0));
			sq->SetPosByMatrixCoord();
			MatrixFill(sq->GetMatrixCoord(), sq);
		}
	}
}
