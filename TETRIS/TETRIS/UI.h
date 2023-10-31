#pragma once
#include "Object.h"
class UI :
    public Object
{
    typedef Object Super;
private:
    bool mb_IsPreesed;

public:
    virtual void OnClick(Vec2 _MousePos);
    virtual void OnHold(Vec2 _MousePos);
    virtual void OnRelease(Vec2 _MousePos);

public:
    virtual void Update() override;
    virtual void Render(HDC _dc) override;

public:
    UI();
    virtual ~UI() override;
};

