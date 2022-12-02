#include "Part1.h"

#include <iostream>
#include <fstream>

#include "RockPaperScissors.h"

int Part1(int argc, char* argv[])
{
    if (argc != 2)
    {
        std::cout << "Invalid number of arguments\n";
        return 1;
    }

    if (std::ifstream data(argv[1]); data)
    {
        char elf_throw{};
        char my_throw{};

        unsigned my_total_points{};

        while (true)
        {
            data >> elf_throw >> my_throw;
            if (!data)
            {
                break;
            }

            const auto elf_shape = CharToShape(elf_throw);
            const auto my_shape = CharToShape(my_throw);
            if (elf_shape == my_shape)
            {
                const auto points = GetOutcomePoints(Outcome::tie) + ShapeToPoints(elf_shape);
                my_total_points += points;
            }
            else
            {
                my_total_points += GetOutcomePoints(elf_shape < my_shape ? Outcome::win : Outcome::lose) + ShapeToPoints(my_shape);
            }
        }
        std::cout << "Total: " << my_total_points << '\n';
    }

    return 0;
}