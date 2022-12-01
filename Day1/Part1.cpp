#include "Part1.h"

#include <fstream>
#include <iostream>
#include <vector>
#include <algorithm>
#include <string>
#include <charconv>
#include <numeric>

std::vector<unsigned> ReadUntilEmptyLine(std::istream& file)
{
    std::vector<unsigned> lines;
    std::string buffer;
    while (std::getline(file, buffer) && !buffer.empty())
    {
        unsigned data = 0;
        const auto result = std::from_chars(buffer.c_str(), buffer.c_str() + buffer.length(), data);
        if (result.ec == std::errc())
        {
            lines.push_back(data);
        }
        else
        {
            //throw the error code
        }
    }

    return lines;
}

std::vector<unsigned> GetSums(std::istream& data)
{
    std::vector<unsigned> sums;
    while (data)
    {
        const auto elf_load = ReadUntilEmptyLine(data);
        if (!elf_load.empty())
        {
            const unsigned total_load = std::accumulate(elf_load.begin(), elf_load.end(), 0);
            sums.push_back(total_load);
        }
    }

    return sums;
}

int Part1(int argc, char* argv[])
{
    if (argc != 2)
    {
        std::cout << "Incorrect number of arguments\n";
        return 1;
    }

    if (std::ifstream data_file(argv[1]); data_file)
    {
        if (const auto sums = GetSums(data_file); !sums.empty())
        {
            std::cout << *std::max_element(sums.begin(), sums.end()) << '\n';
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