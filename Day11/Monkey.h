#pragma once

#include <deque>
#include <memory>
#include <ranges>
#include <iosfwd>

#include "Item.h"
#include "Operation.h"

class Monkey
{
public:
    template<std::ranges::range Items>
    Monkey(int id, int true_id, int false_id, std::unique_ptr<Operation> op, std::unique_ptr<Operation> test, Items&& items) :
        _id(id),
        _test_true_id(true_id),
        _test_false_id(false_id),
        _op(std::move(op)),
        _test(std::move(test)),
        _items(std::ranges::begin(items), std::ranges::end(items))
    {
        worry_modulus *= _test->GetValue()->GetValue({});
    }
    
    //deep copy
    Monkey(const Monkey& other);
    Monkey& operator= (const Monkey& other);

    int GetId() const { return _id; }

    bool HasItem() const;
    std::uint64_t Inspect() const;
    void UpdateWorry(std::uint64_t worry, bool self_managing);
    int Test() const;
    void Throw(Monkey& other);

    friend std::ostream& operator<< (std::ostream& os, const Monkey& monkey);

private:
    static uint64_t worry_modulus;

    int _id;
    int _test_true_id;
    int _test_false_id; 
    std::unique_ptr<Operation> _op;
    std::unique_ptr<Operation> _test;
    std::deque<Item> _items;
};
