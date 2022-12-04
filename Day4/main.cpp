#include <iostream>
#include <fstream>
#include <algorithm>
#include <string>
#include <vector>
#include <string_view>

std::vector<std::string> SplitString(std::string_view to_split, std::string_view delim)
{
    std::vector<std::string> substrs;
    auto found = to_split.find(delim);
    decltype(found) prev_found = 0;
    while (true)
    {
        auto substr = to_split.substr(prev_found, found);
        substrs.emplace_back(substr.data(), substr.size());
        if (found == std::string_view::npos)
        {
            break;
        }
        prev_found = found + delim.size();
        found = to_split.find(delim, prev_found);
    }
    return substrs;
}

int main(int argc, char* argv[])
{
    try
    {
        if (argc != 2)
        {
            std::cout << "Incorrect number of arguments\n";
            return 1;
        }

        if (std::fstream data(argv[1]); data)
        {
            unsigned subsets{};
            unsigned intersections{};
            std::string range;
            while (std::getline(data, range))
            {
                std::vector<std::pair<int, int>> ranges_ints;
                auto ranges_strs = SplitString(range, ",");
                for (auto rng_str : ranges_strs)
                {
                    const auto rng = SplitString(rng_str, "-");
                    ranges_ints.emplace_back(std::atoi(rng.front().c_str()), std::atoi(rng.back().c_str()));
                }

                const auto& [lowest_min, highest_min] = [&ranges_ints]() -> std::pair<const std::pair<int, int>&, const std::pair<int, int>&> {
                    const auto& front = ranges_ints.front();
                    const auto& back = ranges_ints.back();
                    if (front.first < back.first)
                    {
                        return { front, back };
                    }
                    return { back, front };
                }();

                //part 1
                if (lowest_min.first == highest_min.first || lowest_min.second >= highest_min.second)
                {
                    ++subsets;
                }
                //part 2
                if (lowest_min.second >= highest_min.first)
                {
                    ++intersections;
                }
            }

            std::cout << "Subsets (Part 1): " << subsets << 
                "\nIntersections (Part 2): " << intersections << '\n';
            return 0;
        }

        std::cout << "Failed to open file: " << argv[1] << '\n';
        return 1;
    }
    catch (const std::exception& e)
    {
        std::cerr << e.what() << '\n';
        return 1;
    }
}