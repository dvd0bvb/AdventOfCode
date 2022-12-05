#pragma once

#include "Parser.h"
#include "Move.h"

class MoveParser : public Parser<Move>
{
public:
    Move Parse(std::istream& is);
};