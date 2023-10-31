#pragma once
#include "Block.h"
class OBlock :
    public Block
{
public:
    void RotateRight() override;
    void RotateLeft() override;

public:
    OBlock(GameBoard* _gb);
    ~OBlock() override;
};

