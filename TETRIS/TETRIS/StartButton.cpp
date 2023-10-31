#include "StartButton.h"
#include "SceneManager.h"

StartButton::StartButton()
{
}

StartButton::~StartButton()
{
}

void StartButton::Update()
{
	Super::Update();
}

void StartButton::Render(HDC _dc)
{
	Super::Render(_dc);
}

void StartButton::OnClick(Vec2 _MousePos)
{
	SceneManager::GetInst()->ChangeScene(SCENE_TYPE::PLAY);
}

void StartButton::OnHold(Vec2 _MousePos)
{
}

void StartButton::OnRelease(Vec2 _MousePos)
{
}

