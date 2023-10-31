#pragma once
#include "Block.h"
class GhostBlock :
    public Block
{
private:
    Block* m_Target;
    int distance;

public:
    void Update() override;
    void Render(HDC _dc) override;

    void SetTarget(Block* _target) { m_Target = _target; }
    Block* GetTarget() { return m_Target; }

    void SetDistance(int _dist) { distance = _dist; }
    int GetDistance() { return distance; }

public:
    GhostBlock(GameBoard* _gb);
    ~GhostBlock() override;
};

