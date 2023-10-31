#pragma once
#include "Object.h"

class Block;
class Square :
    public Object
{
private:
    COLOR m_Color;
    Vec2 m_AdditionalCoord;
    Vec2 m_RealCoord;

    Block* m_Owner;
    int idx;

public:
    void Update() override;
    void Render(HDC _dc) override;

    void SetIdx(int _idx) { idx = _idx; }
    int GetIdx(int _idx) { return idx ; }

    void SetOwner(Block* _owner) { m_Owner = _owner; }
    Block* GetOwner() { return m_Owner; }

    void SetColor(COLOR _color) { m_Color = _color; }
    COLOR GetColor() { return m_Color; }

    void SetAdditionalCoord(Vec2 _coord) { m_AdditionalCoord = _coord; }
    void SetMatrixCoord(Vec2 _coord) { m_RealCoord = _coord; }

    Vec2 GetAdditionalCoord() { return m_AdditionalCoord; }
    Vec2 GetMatrixCoord() { return m_RealCoord; }

    void RotateRight() 
    {
        m_AdditionalCoord.Switch();
        m_AdditionalCoord.x *= -1;
    }

    void RotateLeft()
    {
        m_AdditionalCoord.x *= -1;
        m_AdditionalCoord.Switch();
    }

    Vec2 CoordToChangeRight();
    Vec2 CoordToChangeleft();

    void SetPosByMatrixCoord();

    void DestroyASquare();

public:
    Square();
    virtual ~Square() override;

    friend Block;
};

