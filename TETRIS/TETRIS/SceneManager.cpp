#include "SceneManager.h"

#include "TitleScene.h"
#include "PlayScene.h"

SceneManager* SceneManager::Inst = nullptr;

SceneManager::SceneManager()
	:next(SCENE_TYPE::END)
{
}

SceneManager::~SceneManager()
{
}

void SceneManager::Init()
{
	CreateScene(SCENE_TYPE::PLAY, new PlayScene());
	CreateScene(SCENE_TYPE::TITLE, new TitleScene());

	ChangeScene(SCENE_TYPE::TITLE);
}

void SceneManager::Release()
{
}

void SceneManager::Update()
{
	if (m_CurScene != nullptr)
		m_CurScene->Update();
}

void SceneManager::Render(HDC _dc)
{
	if (m_CurScene != nullptr)
		m_CurScene->Render(_dc);

	if (next != SCENE_TYPE::END)
	{
		m_CurScene->Exit();
		m_CurScene = m_Scenes[(UINT)next];
		m_CurScene->Enter();
		next = SCENE_TYPE::END;
	}
}

void SceneManager::CreateScene(SCENE_TYPE _type, Scene* _scene)
{
	m_Scenes[(unsigned int)_type] = _scene;

	if (m_CurScene == nullptr)
	{
		m_CurScene = _scene;
		m_CurScene->Enter();
	}
}

void SceneManager::ChangeScene(SCENE_TYPE _type)
{
	next = _type;
}
