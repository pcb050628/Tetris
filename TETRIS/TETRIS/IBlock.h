#pragma once
#include "Block.h"
class IBlock :
    public Block
{
public:
    IBlock(GameBoard* _gb);
    ~IBlock() override;
};

