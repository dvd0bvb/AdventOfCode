#include "CrateStacks.h"

#include <ranges>

void CrateStacks::ApplyMove(const Move& move)
{
    if (stacks.size() < move.from_column || stacks[move.from_column].empty())
    {
        return;
    }

    for (auto _ : std::views::iota(0u, move.num_to_move))
    {
        auto& item = stacks[move.from_column].back();
        stacks[move.to_column].push_back(item);
        stacks[move.from_column].pop_back();
    }
}

void CrateStacks::ApplyGroupedMove(const Move& move)
{
    if (stacks.size() < move.from_column || stacks[move.from_column].empty())
    {
        return;
    }

    std::vector<char> group;
    for (auto _ : std::views::iota(0u, move.num_to_move))
    {
        group.push_back(stacks[move.from_column].back());
        stacks[move.from_column].pop_back();
    }

    for (auto item : group | std::views::reverse)
    {
        stacks[move.to_column].push_back(item);
    }
}