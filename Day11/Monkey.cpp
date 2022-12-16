#include "Monkey.h"

#include <ostream>

uint64_t Monkey::worry_modulus = 1;

Monkey::Monkey(const Monkey& other) : 
    _id(other._id), 
    _test_true_id(other._test_true_id),
    _test_false_id(other._test_false_id),
    _op(other._op->Clone()),
    _test(other._test->Clone()),
    _items(other._items)
{
    
}

Monkey& Monkey::operator= (const Monkey& other)
{
    _id = other._id;
    _test_true_id = other._test_true_id;
    _test_false_id = other._test_false_id;
    _op = other._op->Clone();
    _test = other._test->Clone();
    _items = other._items;
    return *this;
}

bool Monkey::HasItem() const
{
    return !_items.empty();
}

std::uint64_t Monkey::Inspect() const
{
    return (*_op)(_items.front());
}

void Monkey::UpdateWorry(std::uint64_t worry, bool self_managing)
{
    if (self_managing)
    {
        _items.front().worry_level = worry % worry_modulus;
    }
    else
    {
        _items.front().worry_level = worry / 3;
    }
}

int Monkey::Test() const
{
    return (*_test)(_items.front()) == 0 ? _test_true_id : _test_false_id;
}

void Monkey::Throw(Monkey& other)
{
    other._items.push_back(this->_items.front());
    this->_items.pop_front();
}

std::ostream& operator<< (std::ostream& os, const Monkey& monkey)
{
    os << "Monkey " << monkey._id << ": ";
    if (!monkey._items.empty())
    {
        os << monkey._items.front().worry_level;
        for (auto& item : monkey._items | std::views::drop(1))
        {
            os << ", " << item.worry_level;
        }
    }
    return os;
}