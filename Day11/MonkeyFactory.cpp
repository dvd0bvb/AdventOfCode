#include "MonkeyFactory.h"

#include <istream>
#include <string>
#include <vector>
#include <string_view>
#include <charconv>
#include <ranges>

#include "OperationFactory.h"

static std::vector<Item> ParseStartingItems(std::string_view line)
{
    std::vector<Item> items;
    if (auto found = line.find(':'); found != std::string_view::npos)
    {
        for (auto val : line.substr(found + 2) | std::views::split(' ') | std::views::transform([](auto&& range) {
            int val{};
            auto data = std::ranges::data(range);
            const bool found_comma = std::ranges::find(range, ',') != std::ranges::end(range);
            std::from_chars(data, data + std::ranges::size(range) - (found_comma ? 1 : 0), val);
            return val;
            }))
        {
            items.emplace_back(val);
        }
    }

    return items;
}

Monkey MakeMonkey(std::istream& is)
{
    std::string buffer;

    int id{};
    int true_id{};
    int false_id{};
    std::unique_ptr<Operation> op;
    std::unique_ptr<Operation> test;
    std::vector<Item> items;

    while (std::getline(is, buffer) && !buffer.empty())
    {
        if (buffer.find("Monkey ") != std::string::npos)
        {
            if (auto found = buffer.find_last_of(' '); found != std::string::npos)
            {
                std::from_chars(buffer.data() + found + 1, buffer.data() + buffer.size() - 1, id);
            }
        }
        else if (buffer.find("Starting items: ") != std::string::npos)
        {
            items = ParseStartingItems(buffer);
        }
        else if (buffer.find("Operation: ") != std::string::npos)
        {
            op = MakeOperation(buffer);
        }
        else if (buffer.find("Test: ") != std::string::npos)
        {
            test = MakeOperation(buffer);
        }
        else if (buffer.find("If true: ") != std::string::npos)
        {
            if (auto found = buffer.find_last_of(' '); found != std::string::npos)
            {
                std::from_chars(buffer.data() + found + 1, buffer.data() + buffer.size(), true_id);
            }
        }
        else if (buffer.find("If false: ") != std::string::npos)
        {
            if (auto found = buffer.find_last_of(' '); found != std::string::npos)
            {
                std::from_chars(buffer.data() + found + 1, buffer.data() + buffer.size(), false_id);
            }
        }
    }

    return Monkey{ id, true_id, false_id, std::move(op), std::move(test), items };
}