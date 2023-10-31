#pragma once
#include "Block.h"
class LBlock :
    public Block
{
public:
    LBlock(GameBoard* _gb);
    ~LBlock() override;
};

