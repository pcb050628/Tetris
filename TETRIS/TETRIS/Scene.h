#pragma once
#include "Entity.h"
#include "Layer.h"

class Scene :
    public Entity
{
private:
    Layer m_Layers[(unsigned int)LAYER::END];

public:
    virtual void Enter();
    virtual void Exit();

    virtual void Update();
    virtual void Render(HDC _dc);

    virtual void AddObject(LAYER _layer, Object* obj);

    virtual void DeleteAllObjectByLayer(LAYER _layer);
    virtual void DeleteAllObjectAllLayer();

public:
    Scene();
    virtual ~Scene() override;

};

