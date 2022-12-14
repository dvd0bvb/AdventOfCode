#pragma once

#include "Operation.h"

class NoOp : public Operation
{
public:
    void DoOp(Register& reg)
    { 
    
    };

    constexpr std::size_t NumCycles() const
    {
        return 1;
    }
};