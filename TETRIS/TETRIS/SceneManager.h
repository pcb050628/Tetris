#pragma once
#include "header.h"
#include "Scene.h"

class SceneManager
{
private:
	SceneManager();
	~SceneManager();

	static SceneManager* Inst;

public:
	static SceneManager* GetInst()
	{
		if (Inst == nullptr)
			Inst = new SceneManager();

		return Inst;
	}

private:
	Scene* m_CurScene;
	Scene* m_Scenes[(UINT)SCENE_TYPE::END];

	SCENE_TYPE next;

public:
	void Update();
	void Render(HDC _dc);

	void CreateScene(SCENE_TYPE _type, Scene* _scene);
	void ChangeScene(SCENE_TYPE _type);

	void AddObjAtCurScene(LAYER _layer, Object* obj)
	{
		if(m_CurScene != nullptr)
			m_CurScene->AddObject(_layer, obj);
	}

public:
	void Init();
	void Release();
};

