#include "Scene.h"
#include "Object.h"

Scene::Scene()
{
}

Scene::~Scene()
{
}

void Scene::Enter()
{
}

void Scene::Exit()
{
}

void Scene::Update()
{
	for (Layer& ly : m_Layers)
	{
		ly.Update();
	}
}

void Scene::Render(HDC _dc)
{
	for (Layer& ly : m_Layers)
	{
		ly.Render(_dc);
	}
}

void Scene::AddObject(LAYER _layer, Object* obj)
{
	m_Layers[(unsigned int)_layer].AddObject(obj);
}

void Scene::DeleteAllObjectAllLayer()
{
	for (Layer& ly : m_Layers)
	{
		ly.DeleteAllObject();
	}
}

void Scene::DeleteAllObjectByLayer(LAYER _layer)
{
	m_Layers[(unsigned int)_layer].DeleteAllObject();
}

