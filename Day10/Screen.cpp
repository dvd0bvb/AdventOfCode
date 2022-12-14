#include "Screen.h"

#include <ostream>
#include <ranges>

Screen::Screen(std::size_t rows, std::size_t cols, Register& reg) :
    _rows(rows),
    _cols(cols),
    _reg(reg)
{
    _screen.reserve(_rows * _cols);
}

void Screen::OnCycle()
{
    constexpr int sprite_size = 3;
    constexpr int sprite_range = sprite_size / 2;

    const int sprite_center = _reg.value;
    const auto current_pixel = _screen.size() % _cols;

    if ((sprite_center - sprite_range) <= current_pixel && current_pixel <= (sprite_center + sprite_range))
    {
        _screen.append("#");
    }
    else
    {
        _screen.append(".");
    }
}

bool Screen::Ready() const
{
    return _screen.size() == _rows * _cols;
}

void Screen::Clear()
{
    _screen.clear();
}

std::ostream& operator<< (std::ostream& os, const Screen& screen)
{
    //again wishing I had std::views::slide...
    for (auto i : std::views::iota(0u, screen._rows))
    {
        auto view = screen._screen | std::views::drop(i * screen._cols) | std::views::take(screen._cols);
        os << std::string_view{ std::ranges::begin(view), std::ranges::end(view) } << '\n';
    }
    return os;
}