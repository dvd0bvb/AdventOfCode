#include "OperationFactory.h"

#include <functional>
#include <charconv>

std::unique_ptr<Value> MakeValue(std::string_view str)
{
    int value;

    if (str == "old")
    {
        return std::make_unique<Self>();
    }
    else if(auto [ptr, ec] = std::from_chars(str.data(), str.data() + str.size(), value); ec == std::errc())
    {
        return std::make_unique<ActualValue>(value);
    }

    return nullptr;
}

std::unique_ptr<Operation> MakeOperation(std::string_view line)
{
    if (auto found = line.find('+'); found != std::string_view::npos)
    {
        using op_type = std::plus<>;
        return std::make_unique<Op<op_type>>(op_type{}, MakeValue(line.substr(found + 2)));

    }
    else if (auto found = line.find('*'); found != std::string_view::npos)
    {
        using op_type = std::multiplies<>;
        return std::make_unique<Op<op_type>>(op_type{}, MakeValue(line.substr(found + 2)));
    }
    else if (line.find("divisible") != std::string_view::npos)
    {
        if (auto found = line.find_last_of(' '); found != std::string_view::npos)
        {
            using op_type = std::modulus<>;
            return std::make_unique<Op<op_type>>(op_type{}, MakeValue(line.substr(found + 1)));
        }
    }

    return nullptr;
}