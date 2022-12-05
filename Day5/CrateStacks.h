#pragma once

#include <deque>
#include <vector>

#include "Move.h"

struct CrateStacks
{
    void ApplyMove(const Move& move);
    void ApplyGroupedMove(const Move& move);

    std::vector<std::deque<char>> stacks;
};