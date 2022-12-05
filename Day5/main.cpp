#include <iostream>
#include <fstream>
#include <string>

#include "StackParser.h"
#include "MoveParser.h"

int main(int argc, char* argv[])
{
    if (std::ifstream data(argv[1]); data)
    {
        auto stacks = StackParser().Parse(data);
        auto stacks_copy = stacks;

        MoveParser move_parser;
        while (true)
        {
            const auto move = move_parser.Parse(data);
            if (!data)
            {
                break;
            }

            stacks.ApplyMove(move);
            stacks_copy.ApplyGroupedMove(move);
        }

        std::cout << "Part1\n";
        for (auto& stack : stacks.stacks)
        {
            std::cout << stack.back();
        }
        std::cout << '\n';

        std::cout << "Part2\n";
        for (auto& stack : stacks_copy.stacks)
        {
            std::cout << stack.back();
        }
        std::cout << '\n';

        return 0;
    }

    std::cout << "Could not open file " << argv[1] << '\n';
    return 1;
}