#pragma once
#include "Block.h"
class TBlock :
    public Block
{
public:
    TBlock(GameBoard* _gb);
    ~TBlock() override;
};

