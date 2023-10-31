#pragma once
#include "Entity.h"

class Object :
    public Entity
{
protected:
    Vec2 m_Pos;
    Vec2 m_Scale;

public:
    virtual void Update() = 0;
    virtual void Render(HDC _dc) = 0;

    virtual void SetPos(Vec2 _pos) { m_Pos = _pos; }
    virtual void SetScale(Vec2 _scale) { m_Scale = _scale; }
    virtual Vec2 GetPos() { return m_Pos; }
    virtual Vec2 GetScale() { return m_Scale; }

    void Destroy() { SetDead(); }

public:
    Object();
    virtual ~Object() override = 0;

};

