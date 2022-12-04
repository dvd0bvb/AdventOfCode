#pragma once

#include <ranges>
#include <unordered_map>
#include <algorithm>

template<class It, std::ranges::range... Rs>
void set_intersection(It&& iter, Rs&&... sorted_ranges)
{
    std::vector<std::common_type_t<Rs...>> ranges{ sorted_ranges... };

    auto range_of_min_size = std::min_element(ranges.begin(), ranges.end(), [](const auto& lh, const auto& rh) {
        return std::ranges::size(lh) < std::ranges::size(rh);
        });

    std::unordered_map<std::ranges::range_value_t<decltype(*range_of_min_size)>, std::size_t> value_map;
    for (const auto& item : *range_of_min_size)
    {
        ++value_map[item];
    }

    for (auto& [key, value] : value_map)
    {
        std::size_t frequency = value;
        for (const auto& range : ranges)
        {
            const auto count = std::ranges::count(range, key);
            if (count < frequency)
            {
                frequency = count;
            }
        }

        if (frequency < value)
        {
            value = frequency;
        }
    }

    for (const auto& [key, value] : value_map)
    {
        for (auto _ : std::views::iota(0u, value))
        {
            iter = key;
        }
    }
}