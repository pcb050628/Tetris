#pragma once
#include "Block.h"
class JBlock :
    public Block
{
public:
    JBlock(GameBoard* _gb);
    ~JBlock() override;
};

