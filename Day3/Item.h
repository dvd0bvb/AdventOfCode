#pragma once

class Item
{
public:
    Item(char c);
    int GetPriority() const;

private:
    char item;
};