#pragma once

#include "Operation.h"
#include "Register.h"

class Addx : public Operation
{
public:
    Addx(int to_add) : value(to_add)
    {

    }

    void DoOp(Register& reg)
    {
        reg.value += this->value;
    }

    constexpr std::size_t NumCycles() const
    {
        return 2;
    }

private:
    const int value;
};