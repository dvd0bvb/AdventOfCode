#include <iostream>
#include <fstream>
#include <string>
#include <ranges>

#include "Register.h"
#include "OperationFactory.h"
#include "Screen.h"

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
            int total{ 0 };
            std::size_t cycle_num{ 0 };
            Register reg{ 1 };
            Screen screen(6, 40, reg);

            std::string buffer;
            while (std::getline(data, buffer))
            {
                if (auto op = MakeOperation(buffer))
                {
                    for (auto i : std::views::iota(0u, op->NumCycles()))
                    {
                        ++cycle_num;
                        if (((cycle_num + 20) % 40) == 0)
                        {
                            total += cycle_num * reg.value;
                        }

                        screen.OnCycle();
                        if (screen.Ready())
                        {
                            std::cout << screen << '\n';
                            screen.Clear();
                        }
                    }
                    op->DoOp(reg);
                }
            }

            std::cout << "Sum: " << total << '\n';
            return 0;
        }

        std::cout << "There was a problem opening " << argv[1] << '\n';
        return 1;
    }
    catch (const std::exception& e)
    {
        std::cerr << e.what() << '\n';
        return 1;
    }
}