#include "StackParser.h"

#include <istream>
#include <string>
#include <ranges>
#include <algorithm>

CrateStacks StackParser::Parse(std::istream& is)
{
    static constexpr std::size_t col_width{ 4 };

    //input crate stack matrix represented by 2d array of chars (otherwise known as a string)
    const auto [accumulated, rows] = ReadUntilEmptyLine(is);
    const auto row_width = accumulated.length() / rows;
    const auto cols = row_width / col_width;

    CrateStacks stacks{ .stacks{cols} };

    std::size_t column{};
    std::string_view accum_view{ accumulated };

    //c++23 has chunk_view which would be perfect for this...
    //read each entry, add it to stacks structure
    //rows - 1 because we don't need the row id - which is the last row - to be part of the stacks
    for (auto i : std::views::iota(0u, (rows - 1) * cols)) 
    {
        auto entry = accum_view.substr(i * col_width, col_width) | std::views::filter([](auto a) { return !std::isspace(a) && a != '[' && a != ']'; });
        if (!std::ranges::empty(entry))
        {
            stacks.stacks[column % cols].push_front(*std::ranges::begin(entry));
        }
        ++column;
    }

    return stacks;
}

std::pair<std::string, std::size_t> StackParser::ReadUntilEmptyLine(std::istream& is)
{
    std::size_t rows{};
    std::string buffer;
    std::string accumulated;
    while (std::getline(is, buffer) && !buffer.empty())
    {
        accumulated += buffer + " ";
        ++rows;
    }

    return { accumulated, rows };
}