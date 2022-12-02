#include <iostream>

#include "Part1.h"
#include "Part2.h"

int main(int argc, char* argv[])
{
    try
    {
        //return Part1(argc, argv);
        return Part2(argc, argv);
    }
    catch (const std::exception& e)
    {
        std::cerr << e.what() << '\n';
        return 1;
    }
}