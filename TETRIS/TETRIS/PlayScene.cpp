#include "PlayScene.h"
#include "GameBoard.h"

PlayScene::PlayScene()
{
}

PlayScene::~PlayScene()
{
}

void PlayScene::Enter()
{
	GameBoard* gb = new GameBoard();

	AddObject(LAYER::BACKGROUND, gb);
}

void PlayScene::Exit()
{
	DeleteAllObjectAllLayer();
}
