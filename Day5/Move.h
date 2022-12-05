#pragma once

#include <cstddef>

struct Move
{
    std::size_t num_to_move{};
    std::size_t from_column{};
    std::size_t to_column{};
};