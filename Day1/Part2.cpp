#include "Part2.h"

#include <iostream>
#include <fstream>
#include <algorithm>
#include <numeric>
#include <ranges>

#include "Part1.h"


template <std::ranges::random_access_range T>
auto GetMaxN(T&& range, unsigned n)
{
    std::ranges::sort(std::forward<T>(range), std::greater{});

    if (range.size() <= n)
    {
        return range | std::views::take(std::ranges::size(range));
    }

    //create sorted view
    //take first n element
    return range | std::views::take(n);
}

int Part2(int argc, char* argv[])
{
    if (argc != 2)
    {
        std::cout << "Incorrect number of arguments\n";
        return 1;
    }

    if (std::ifstream data_file(argv[1]); data_file)
    {
        if (auto sums = GetSums(data_file); !sums.empty())
        {
            auto max_range = GetMaxN(sums, 3);
            std::cout << std::accumulate(std::ranges::begin(max_range), std::ranges::end(max_range), 0) << '\n';
        }
        else
        {
            std::cout << "No elements found in data file " << argv[1] << '\n';
        }
    }
    else
    {
        std::cout << "Could not open file " << argv[1] << '\n';
        return 1;
    }

    return 0;
}