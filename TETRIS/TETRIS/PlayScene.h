#pragma once
#include "Scene.h"
class PlayScene :
    public Scene
{
public:
    void Enter() override;
    void Exit() override;

public:
    PlayScene();
    ~PlayScene() override;
};

