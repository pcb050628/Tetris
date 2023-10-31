#pragma once
#include "UI.h"
class StartButton :
    public UI
{
    typedef UI Super;

public:
    void Update() override;
    void Render(HDC _dc) override;

    virtual void OnClick(Vec2 _MousePos) override;
    virtual void OnHold(Vec2 _MousePos) override;
    virtual void OnRelease(Vec2 _MousePos) override;

public:
    StartButton();
    ~StartButton() override;

};

