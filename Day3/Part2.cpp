#include "Part2.h"

#include <iostream>
#include <fstream>
#include <ranges>
#include <sstream>
#include <numeric>
#include <array>

#include "Rucksack.h"
#include "Item.h"

int Part2(int argc, char* argv[])
{
    if (argc != 2)
    {
        std::cout << "Incorrect number of arguments\n";
        return 1;
    }

    if (std::ifstream data(argv[1]); data)
    {
        std::string line;
        std::array<Rucksack, 3> group{};
        unsigned total_priority{};

        while (true)
        {
            for (auto& sack : group)
            {
                std::getline(data, line);
                sack.Parse(line);
            }

            if (!data)
            {
                break;
            }

            const auto common_items = group[0].GetCommonItems(group[1], group[2]);
            total_priority = std::accumulate(common_items.begin(), common_items.end(), total_priority, [](unsigned sum, const Item& item) {
                return sum + item.GetPriority();
                });
        }

        std::cout << "Total: " << total_priority << '\n';
        return 0;
    }

    std::cout << "Failed to open file: " << argv[1] << '\n';
    return 1;
}