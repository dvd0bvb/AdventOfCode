#include <iostream>
#include <fstream>
#include <string>
#include <charconv>
#include <system_error>
#include <ranges>
#include <set>
#include <vector>

using Position = std::pair<int, int>;

struct Rope
{
    std::vector<Position> pos;
};

enum class Direction
{
    up,
    down,
    left,
    right,
    invalid
};

void PerformNextMove(Position& from, Position& to)
{
    const auto x_distance = std::max(from.first, to.first) - std::min(from.first, to.first);
    const auto y_distance = std::max(from.second, to.second) - std::min(from.second, to.second);

    if (x_distance > 1 || (y_distance > 1 && x_distance == 1))
    {
        from.first > to.first ? ++to.first : --to.first;
    }

    if (y_distance > 1 || (x_distance > 1 && y_distance == 1))
    {
        from.second > to.second ? ++to.second : --to.second;
    }
}

void PerformMove(Rope& rope, Direction dir)
{
    auto& head = rope.pos.front();
    switch (dir)
    {
    case Direction::up:
        ++head.first;
        break;
    case Direction::down:
        --head.first;
        break;
    case Direction::left:
        --head.second;
        break;
    case Direction::right:
        ++head.second;
        break;
    }

    //std::slide_view would be great for this...
    for (auto i : std::views::iota(0u, rope.pos.size() - 1))
    {
        PerformNextMove(rope.pos[i], rope.pos[i + 1]);
    }
}

Direction CharToDirection(char c)
{
    switch (c)
    {
    case 'U':
        return Direction::up;
    case 'D':
        return Direction::down;
    case 'L':
        return Direction::left;
    case 'R':
        return Direction::right;
    }
}

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
            Rope rope1{ .pos{2} };
            Rope rope2{ .pos{10} };

            std::set<Position> rope1_tail_positions;
            std::set<Position> rope2_tail_positions;

            rope1_tail_positions.insert(rope1.pos.back());
            rope2_tail_positions.insert(rope2.pos.back());
            
            std::string buffer;
            while (std::getline(data, buffer))
            {
                std::string_view buf_view{ buffer };
                if (auto space = buf_view.find(' '); space != std::string_view::npos && space > 0)
                {
                    auto dir = CharToDirection(buf_view[space - 1]);
                    std::size_t num_times{};
                    if (auto [ptr, ec] = std::from_chars(buf_view.data() + space + 1, buf_view.data() + buf_view.size(), num_times); ec != std::errc())
                    {
                        const auto code = std::make_error_code(ec);
                        std::cout << "There was an issue converting part of " << buf_view << " to a number\n"
                            << code.value() << ' ' << code.message() << '\n';
                        break;
                    }

                    for (auto i : std::views::iota(0u, num_times))
                    {
                        PerformMove(rope1, dir);
                        PerformMove(rope2, dir);

                        rope1_tail_positions.insert(rope1.pos.back());
                        rope2_tail_positions.insert(rope2.pos.back());
                    }
                }
            }

            std::cout << "Part1: " << rope1_tail_positions.size() << '\n'
                << "Part2: " << rope2_tail_positions.size() << '\n';
        }

        std::cout << "There was an issue opening " << argv[1] << '\n';
        return 1;
    }
    catch (const std::exception& e)
    {
        std::cerr << e.what() << '\n';
        return 1;
    }
}