#pragma once

#include <iosfwd>
#include <string>


#include "Register.h"

class Screen
{
public:
    Screen(std::size_t rows, std::size_t cols, Register& reg);

    friend std::ostream& operator<< (std::ostream& os, const Screen& screen);
    void OnCycle();
    bool Ready() const;
    void Clear();

private:
    std::size_t _rows;
    std::size_t _cols;
    Register& _reg;
    std::string _screen;
};