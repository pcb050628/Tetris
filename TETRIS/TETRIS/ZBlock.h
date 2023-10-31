#pragma once
#include "Block.h"
class ZBlock :
    public Block
{
public:
    ZBlock(GameBoard* _gb);
    ~ZBlock() override;
};

