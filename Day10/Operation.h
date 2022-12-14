#pragma once

#include <cstddef>

struct Register;

class Operation
{
public:
    virtual ~Operation() = default;
    virtual void DoOp(Register& reg) = 0;
    virtual constexpr std::size_t NumCycles() const = 0;
};