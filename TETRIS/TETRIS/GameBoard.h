#pragma once
#include "Object.h"
#include <random>

class Block;
class GhostBlock;
class Square;
class GameBoard :
    public Object
{
private:
    Square* m_Matrix[20][10];

    Block* m_CurBlock;
    GhostBlock* m_GhostBlock;
    Block* m_SaveBlockToRender;
    BLOCK_TYPE m_SaveBlockType;
    std::vector<BLOCK_TYPE> m_BlockBag1;
    std::queue<BLOCK_TYPE> m_BlockBag2;
    bool mb_canChange;

    std::vector<Block*> m_NextBlockToRender;

    std::queue<int> m_LineToDestroy;

    float DownCount;
    float moveInterval;

    float InputCount;
    float InputInterval;

    float ClearCount;
    float ClearInterval;

    std::random_device rd;

public:
    void Update() override;
    void Render(HDC _dc) override;

    void CreateBlock();
    void CreateBlock(BLOCK_TYPE _type);
    void SetGhostBlockDistance();
    void BlockChange();

    void BoardClear();

    void MatrixFill(Vec2 _coord, Square* _square)
    {
        if (_coord.x > -1 && _coord.y > -1)
            m_Matrix[(int)_coord.x][(int)_coord.y] = _square;
    }

    bool CanMoveDown();
    bool CanMoveRight();
    bool CanMoveLeft();
    bool CanRotateRight();
    bool CanRotateleft();

    void LineCheck();
    void DestroyLine(); 
    void LineDown(int _row, int _count);

public:
    GameBoard();
    ~GameBoard() override;
};

