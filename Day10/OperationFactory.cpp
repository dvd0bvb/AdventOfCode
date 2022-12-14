#include "OperationFactory.h"

#include <charconv>

std::unique_ptr<Operation> MakeOperation(std::string_view op)
{
    if (op == "noop")
    {
        return std::make_unique<NoOp>();
    }

    if (op.find("addx") == 0)
    {
        if (auto found = op.find(' '); found != std::string_view::npos)
        {
            int value = 0;
            if (auto [ptr, ec] = std::from_chars(op.data() + found + 1, op.data() + op.size(), value); ec == std::errc())
            {
                return std::make_unique<Addx>(value);
            }
        }
    }

    return nullptr;
}