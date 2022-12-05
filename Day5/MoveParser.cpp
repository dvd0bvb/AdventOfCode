#include "MoveParser.h"

#include <string>
#include <istream>
#include <ranges>
#include <charconv>

Move MoveParser::Parse(std::istream& is)
{
    Move result;
    std::string buffer;
    if (std::getline(is, buffer))
    {
        bool move = false;
        bool from = false;
        bool to = false;

        for (auto token : buffer | std::views::split(' ') | std::views::transform([](auto&& rng) {
            return std::string_view(&*rng.begin(), std::ranges::distance(rng)); } ))
        {
            if (token == "move") { move = true; }
            else if (token == "from") { from = true; }
            else if (token == "to") { to = true; }
            else
            {
                std::size_t value{};
                std::from_chars(token.data(), token.data() + token.size(), value);

                if (move) { result.num_to_move = value; move = false; }
                else if (from) { result.from_column = value - 1; from = false; }
                else if (to) { result.to_column = value - 1; to = false; }
            }
        }
    }

    return result;
}