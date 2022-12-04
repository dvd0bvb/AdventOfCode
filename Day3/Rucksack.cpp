#include "Rucksack.h"

#include <algorithm>
#include <ranges>

void Rucksack::Parse(std::string_view data)
{
    const auto midpoint = data.length() / 2;
    partition_1.assign(data.substr(0, midpoint));
    partition_2.assign(data.substr(midpoint));
}

std::string Rucksack::GetCommonItems() const
{
    //sets must be sorted for set_intersection()
    auto part1_sorted = partition_1;
    auto part2_sorted = partition_2;

    std::ranges::sort(part1_sorted);
    std::ranges::sort(part2_sorted);

    std::string result;
    std::ranges::set_intersection(part1_sorted, part2_sorted, std::back_inserter(result));
    result.erase(std::unique(result.begin(), result.end()), result.end());

    return result;
}