#include "Layer.h"
#include "Object.h"

Layer::Layer()
{
}

Layer::~Layer()
{
}

void Layer::Update()
{
	for (Object* obj : m_Objs)
	{
		obj->Update();
	}
}

void Layer::Render(HDC _dc)
{
	for (Object* obj : m_Objs)
	{
		obj->Render(_dc);
	}


	std::vector<Object*>::iterator obj = m_Objs.begin();
	for (; obj != m_Objs.end(); )
	{
		if ((*obj)->IsDead())
		{
			delete (*obj);
			obj = m_Objs.erase(obj);
		}
		else
		{
			obj++;
		}
	}
}

void Layer::AddObject(Object* obj)
{
	m_Objs.push_back(obj);
}

void Layer::DeleteAllObject()
{
	std::vector<Object*>::iterator iter = m_Objs.begin();
	while(iter != m_Objs.end())
	{
		delete (*iter);
		iter = m_Objs.erase(iter);
	}
}

