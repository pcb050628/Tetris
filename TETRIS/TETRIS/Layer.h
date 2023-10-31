#pragma once
#include "Entity.h"

class Object;
class Layer :
    public Entity
{
private:
    std::vector<Object*> m_Objs;

public:
    void Update();
    void Render(HDC _dc);

    void AddObject(Object* obj);

    void DeleteAllObject();

public:
    Layer();
    ~Layer() override;
};

