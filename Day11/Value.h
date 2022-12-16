#pragma once

#include "Item.h"

struct Value
{
    virtual ~Value() = default;
    virtual std::uint64_t GetValue(const Item& item) = 0;
    virtual std::unique_ptr<Value> Clone() const = 0;
};

struct Self : public Value
{
    std::uint64_t GetValue(const Item& item) { return item.worry_level; }
    std::unique_ptr<Value> Clone() const { return std::make_unique<Self>(); }
};

struct ActualValue : public Value
{
    ActualValue(int val) : value(val) {}
    std::uint64_t GetValue(const Item& item) { return value; }
    std::unique_ptr<Value> Clone() const { return std::make_unique<ActualValue>(value); }
    int value;
};