#include "Part2.h"

#include <iostream>
#include <fstream>

#include "RockPaperScissors.h"

int Part2(int argc, char* argv[])
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
            const auto my_outcome = CharToOutcome(my_throw);
            switch (my_outcome)
            {
            case Outcome::win:
                my_total_points += GetOutcomePoints(Outcome::win) + ShapeToPoints(ShapeNeededToWin(elf_shape));
                break;
            case Outcome::tie:
                my_total_points += GetOutcomePoints(Outcome::tie) + ShapeToPoints(elf_shape);
                break;
            case Outcome::lose:
                my_total_points += GetOutcomePoints(Outcome::lose) + ShapeToPoints(ShapeNeededToLose(elf_shape));
                break;
            }
        }
        std::cout << "Total: " << my_total_points << '\n';
    }

    return 0;
}