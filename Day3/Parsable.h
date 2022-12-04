#pragma once

#include <string_view>

struct Parsable
{
    virtual void Parse(std::string_view data) = 0;
};