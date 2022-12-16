#include <iostream>
#include <fstream>
#include <vector>
#include <ranges>
#include <map>
#include <queue>

#include "MonkeyFactory.h"

int main(int argc, char* argv[])
{
    try
    {
        if (argc != 2)
        {
            std::cout << "Incorrect number of arguments\n";
            return 1;
        }

        if (std::ifstream data(argv[1]); data)
        {
            std::vector<Monkey> monkes;
            std::vector<Monkey> monkes_copy;
            std::map<int, int> inspection_map;
            std::map<int, int> inspection_map_p2;

            while (data)
            {
                monkes.push_back(MakeMonkey(data));
            }

            monkes_copy = monkes;

            constexpr auto num_rounds_part1{ 20 };
            for (auto _ : std::views::iota(0, num_rounds_part1))
            {
                for (auto& monke : monkes)
                {
                    while (monke.HasItem())
                    {
                        const auto worry = monke.Inspect();
                        monke.UpdateWorry(worry, false);
                        const auto throw_id = monke.Test();
                        monke.Throw(monkes[throw_id]);
                        ++inspection_map[monke.GetId()];
                    }
                }
            }

            constexpr auto num_rounds_part2{ 10000 };
            for (auto _ : std::views::iota(0, num_rounds_part2))
            {
                for (auto& monke : monkes_copy)
                {
                    while (monke.HasItem())
                    {
                        const auto worry = monke.Inspect();
                        monke.UpdateWorry(worry, true);
                        const auto throw_id = monke.Test();
                        monke.Throw(monkes_copy[throw_id]);
                        ++inspection_map_p2[monke.GetId()];
                    }
                }
            }

            std::cout << "Part 1:\n";
            for (auto& [id, inspected] : inspection_map)
            {
                std::cout << "Monkey " << id << " inspected items " << inspected << " times.\n";
            }
            
            auto product_top2 = [](const std::map<int, int>& map) {
                auto insp_view = map | std::views::values;
                std::priority_queue q(std::ranges::begin(insp_view), std::ranges::end(insp_view));
                uint64_t product = q.top();
                q.pop();
                product *= q.top();
                return product;
            };

            std::cout << "Product of top 2: " << product_top2(inspection_map) << '\n';

            std::cout << "\nPart 2:\n";
            for (auto& [id, inspected] : inspection_map_p2)
            {
                std::cout << "Monkey " << id << " inspected items " << inspected << " times.\n";
            }

            std::cout << "Product of top 2: " << product_top2(inspection_map_p2) << '\n';

            return 0;
        }

        std::cout << "There was an issue opening " << argv[1] << '\n';
        return 1;
    }
    catch (const std::exception& e)
    {
        std::cerr << e.what() << '\n';
        return 1;
    }
}