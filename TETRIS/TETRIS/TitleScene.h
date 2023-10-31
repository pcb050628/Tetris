#pragma once
#include "Scene.h"
class TitleScene :
    public Scene
{
    typedef Scene Super;

public:
    void Render(HDC _dc) override;

    void Enter() override;
    void Exit() override;

public:
    TitleScene();
    ~TitleScene() override;
};

