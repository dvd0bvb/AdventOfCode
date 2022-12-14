#pragma once

#include <vector>
#include <concepts>
#include <cassert>

template<class T>
class Matrix
{
public:
    Matrix() = default;

    Matrix(std::size_t rows, std::size_t cols) : _rows(rows), _cols(cols), _data(rows * cols)
    {

    }

    std::size_t Size() const
    {
        return _rows * _cols;
    }

    std::size_t NumRows() const
    {
        return _rows;
    }

    std::size_t NumCols() const
    {
        return _cols;
    }

    //returns number of rows
    template<class... Ts>
    std::size_t AddRow(Ts&&... args)
    {
        if constexpr (sizeof...(Ts))
        {
            (_data.insert(_data.end(), std::forward<Ts>(args)), ...);
        }
        return ++_rows;
    }

    template <std::ranges::range Rng>
    std::size_t AddRow(Rng&& rng)
    {
        _data.insert(_data.end(), std::ranges::begin(rng), std::ranges::end(rng));
        if (_cols == 0)
        {
            _cols = std::ranges::size(rng);
        }

        return ++_rows;
    }

    //returns number of columns
    template<class... Ts>
    std::size_t AddCol(Ts&&... args)
    {
        for (auto iter = (_data.begin() + _cols), end = _data.end(); iter != end; iter += _cols)
        {
            if constexpr (sizeof...(Ts))
            {

            }
            else
            {
                _data.insert(iter, {});
            }
        }
        ++_cols;
    }

    //get a view into the row
    auto operator[] (std::size_t row) const
    {
        assert(row < _rows);
        return std::span(_data | std::views::drop(row * _cols) | std::views::take(_cols));
    }

private:
    std::size_t _rows{};
    std::size_t _cols{};
    std::vector<T> _data;
};