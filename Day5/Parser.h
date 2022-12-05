#pragma once

#include <iosfwd>

template <class T>
struct Parser
{
    virtual T Parse(std::istream& is) = 0;
};