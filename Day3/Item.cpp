#include "Item.h"

Item::Item(char c) : item(c)
{

}

int Item::GetPriority() const
{
    if ('A' <= item && item <= 'Z')
    {
        return (static_cast<int>(item - 'A') + 27);
    }
    else if ('a' <= item && item <= 'z')
    {
        return static_cast<int>(item - 'a') + 1;
    }

    //return -1 on error
    return -1;
}