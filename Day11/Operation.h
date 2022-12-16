#pragma once

#include "Item.h"
#include "Value.h"

class Operation
{
public:
    virtual ~Operation() = default;
    virtual std::uint64_t operator() (const Item& item) = 0;
    virtual Value* GetValue() = 0;
    virtual const Value* GetValue() const = 0;
    virtual std::unique_ptr<Operation> Clone() const = 0;
};

template<class Callable>
class Op : public Operation
{
public:
    Op(Callable op, std::unique_ptr<Value> value) : _op(op), _value(std::move(value))
    {

    }

    std::uint64_t operator() (const Item& item)
    {
        return _op(item.worry_level, _value->GetValue(item));
    }

    Value* GetValue()
    {
        return _value.get();
    }

    const Value* GetValue() const
    {
        return _value.get();
    }

    std::unique_ptr<Operation> Clone() const
    {
        Op new_op;
        new_op._op = this->_op;
        new_op._value = this->_value->Clone();
        return std::make_unique<Op>(std::move(new_op));
    }

private:
    Op() = default;

    Callable _op;
    std::unique_ptr<Value> _value;
};