#pragma once
#include "Object.h"

class Square;
class GameBoard;
class Block :
    public Object
{
protected:
    GameBoard* m_Owner;

    Square* m_Squares[4];
    Square* m_Center;
    BLOCK_TYPE m_Type;

    BLOCK_STATE m_State;

    Vec2 m_MatrixCoord;

public:
    virtual void Update() override;
    virtual void Render(HDC _dc) override;

    virtual GameBoard* GetOwner() { return m_Owner; }
    
    virtual void Down();
    virtual void DownByDestroy(int _row, int _count);
    virtual void Right();
    virtual void Left();
    virtual void RotateRight();
    virtual void RotateLeft();

    virtual void Recheck();
    virtual void RecheckWithRow(int _row, int _count);
    virtual void Uncheck();

    virtual void SetMatrixCoord(Vec2 _coord) { m_MatrixCoord = _coord; Recheck(); }
    virtual Vec2 GetMatrixCoord() { return m_MatrixCoord; }

    virtual std::vector<Vec2> GetLowestCoord();
    virtual std::vector<Vec2> GetRightmostCoord();
    virtual std::vector<Vec2> GetLeftmostCoord();

    virtual void DestoryASquare(int idx);
    Square* GetSquare(int idx) { return m_Squares[idx]; }
    Square* GetSquare() 
    { 
        for (int i = 0; i < 4; i++)
        {
            if(m_Squares[i] != nullptr)
                return m_Squares[i]; 
        }
        return nullptr;
    }

public:
    Block(BLOCK_TYPE _type, GameBoard* _gb);
    virtual ~Block() override;

    friend GameBoard;
};

