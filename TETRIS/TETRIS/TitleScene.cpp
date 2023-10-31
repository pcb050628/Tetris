#include "TitleScene.h"
#include "StartButton.h"

#include "Engine.h"
#include "Camera.h"

TitleScene::TitleScene()
{
}

TitleScene::~TitleScene()
{
}

void TitleScene::Render(HDC _dc)
{
	Super::Render(_dc);

	HPEN prev = (HPEN)SelectObject(_dc, Engine::GetInst()->GetPen(COLOR::GREY));

	{ // T
		for (int row = 0; row < 7; row++)
		{
			for (int col = 0; col < 5; col++)
			{
				if (row == 0 || col == 2)
				{
					Vec2 lPos = (Vec2(col, row) * SQUARESIZE) + (Vec2(-17, -8) * SQUARESIZE);
					Camera::GetInst()->GetRenderPos(lPos);

					Rectangle(_dc, (lPos.x - SQUARESIZE / 2), (lPos.y - SQUARESIZE / 2), (lPos.x + SQUARESIZE / 2), (lPos.y + SQUARESIZE / 2));
				}
			}
		}
	}

	{ // E
		for (int row = 0; row < 7; row++)
		{
			for (int col = 0; col < 5; col++)
			{
				if (row == 0 || row == 3 || row == 6 || col == 0)
				{
					Vec2 lPos = (Vec2(col, row) * SQUARESIZE) + (Vec2(-11, -8) * SQUARESIZE);
					Camera::GetInst()->GetRenderPos(lPos);

					Rectangle(_dc, (lPos.x - SQUARESIZE / 2), (lPos.y - SQUARESIZE / 2), (lPos.x + SQUARESIZE / 2), (lPos.y + SQUARESIZE / 2));
				}
			}
		}
	}

	{ // T
		for (int row = 0; row < 7; row++)
		{
			for (int col = 0; col < 5; col++)
			{
				if (row == 0 || col == 2)
				{
					Vec2 lPos = (Vec2(col, row) * SQUARESIZE) + (Vec2(-5, -8) * SQUARESIZE);
					Camera::GetInst()->GetRenderPos(lPos);

					Rectangle(_dc, (lPos.x - SQUARESIZE / 2), (lPos.y - SQUARESIZE / 2), (lPos.x + SQUARESIZE / 2), (lPos.y + SQUARESIZE / 2));
				}
			}
		}
	}

	{ // R
		for (int row = 0; row < 7; row++)
		{
			for (int col = 0; col < 5; col++)
			{
				if (col == 0 || (col != 4 && row == 0) || (col != 4 && row == 3) || (row != 0 && row != 3 && col == 4))
				{
					Vec2 lPos = (Vec2(col, row) * SQUARESIZE) + (Vec2(1, -8) * SQUARESIZE);
					Camera::GetInst()->GetRenderPos(lPos);

					Rectangle(_dc, (lPos.x - SQUARESIZE / 2), (lPos.y - SQUARESIZE / 2), (lPos.x + SQUARESIZE / 2), (lPos.y + SQUARESIZE / 2));
				}
			}
		}
	}

	{ // I
		for (int row = 0; row < 7; row++)
		{
			for (int col = 0; col < 5; col++)
			{
				if (row == 0 || col == 2 || row == 6)
				{
					Vec2 lPos = (Vec2(col, row) * SQUARESIZE) + (Vec2(7, -8) * SQUARESIZE);
					Camera::GetInst()->GetRenderPos(lPos);

					Rectangle(_dc, (lPos.x - SQUARESIZE / 2), (lPos.y - SQUARESIZE / 2), (lPos.x + SQUARESIZE / 2), (lPos.y + SQUARESIZE / 2));
				}
			}
		}
	}

	{ // S
		for (int row = 0; row < 7; row++)
		{
			for (int col = 0; col < 5; col++)
			{
				if ((col == 0 && (row == 1 || row == 2 || row == 5 )) ||
					((col == 1 || col == 2 || col == 3) && (row == 0 || row == 3 || row == 6)) ||
					(col == 4 && (row == 1 || row == 4 || row == 5)))
				{	
					Vec2 lPos = (Vec2(col, row) * SQUARESIZE) + (Vec2(13, -8) * SQUARESIZE);
					Camera::GetInst()->GetRenderPos(lPos);

					Rectangle(_dc, (lPos.x - SQUARESIZE / 2), (lPos.y - SQUARESIZE / 2), (lPos.x + SQUARESIZE / 2), (lPos.y + SQUARESIZE / 2));
				}
			}
		}
	}

	SelectObject(_dc, prev);
}

void TitleScene::Enter()
{
	StartButton* sbtn = new StartButton();

	AddObject(LAYER::UI, sbtn);
}

void TitleScene::Exit()
{
	DeleteAllObjectAllLayer();
}
