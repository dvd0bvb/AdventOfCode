#include "Part1.h"

#include <iostream>
#include <fstream>
#include <numeric>

#include "Rucksack.h"
#include "Item.h"

int Part1(int argc, char* argv[])
{
    if (argc != 2)
    {
        std::cout << "Incorrect number of arguments\n";
        return 1;
    }

    if (std::ifstream data(argv[1]); data)
    {
        std::string line;
        Rucksack rucksack;
        unsigned total_priority{};

        while (std::getline(data, line))
        {
            rucksack.Parse(line);
            const auto common_items = rucksack.GetCommonItems();
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