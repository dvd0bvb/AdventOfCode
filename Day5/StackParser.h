#pragma once

#include <utility>
#include <string>

#include "Parser.h"
#include "CrateStacks.h"

class StackParser : public Parser<CrateStacks>
{
public:
    CrateStacks Parse(std::istream& is);

private:
    std::pair<std::string, std::size_t> ReadUntilEmptyLine(std::istream& is);
};