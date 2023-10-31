#pragma once
#include "Block.h"
class SBlock :
    public Block
{
public:
    SBlock(GameBoard* _gb);
    ~SBlock() override;
};

