#include <iostream>
#include <fstream>
#include <string>
#include <ranges>
#include <algorithm>
#include <array>
#include <numeric>

#include "Matrix.h"

struct VisibleData
{
    bool reached_edge = true;
    std::size_t how_many{};
};

std::vector<std::size_t> ConvertStringToNumbers(std::string_view str)
{
    std::vector<std::size_t> result;
    std::ranges::transform(str, std::back_inserter(result), [](char c) -> std::size_t {
        return c - '0';
        });
    return result;
}

template<std::three_way_comparable T>
std::array<VisibleData, 4> CountVisibleFromElement(const Matrix<T>& mat, std::size_t row, std::size_t col)
{
    std::array<VisibleData, 4> result;

    const auto value = mat[row][col];
    auto& left = result[0];
    auto& right = result[1];
    auto& up = result[2];
    auto& down = result[3];

    //from left
    for (auto i : std::views::iota(0u, col) | std::views::reverse)
    {
        ++left.how_many;
        if (mat[row][i] >= value)
        {
            left.reached_edge = false;
            break;
        }
    }

    //from right
    for (auto i : std::views::iota(col + 1, mat.NumCols()))
    {
        ++right.how_many;
        if (mat[row][i] >= value)
        {
            right.reached_edge = false;
            break;
        }        
    }

    //from top
    for (auto i : std::views::iota(0u, row) | std::views::reverse)
    {
        ++up.how_many;
        if (mat[i][col] >= value)
        {
            up.reached_edge = false;
            break;
        }        
    }

    //from bottom
    for (auto i : std::views::iota(row + 1, mat.NumRows()))
    {
        ++down.how_many;
        if (mat[i][col] >= value)
        {
            down.reached_edge = false;
            break;
        }
    }

    return result;
}

template<std::three_way_comparable T>
bool MatElementIsVisible(const Matrix<T>& mat, std::size_t row, std::size_t col)
{
    //elements on the edge of the matrix are always visible
    if (row == 0 || col == 0 || row == (mat.NumRows() - 1) || col == (mat.NumCols() - 1))
    {
        return true;
    }

    const auto result = CountVisibleFromElement(mat, row, col);
    return std::ranges::find_if(result, [](const auto& item) { return item.reached_edge; }) != std::ranges::end(result);
}

template<std::three_way_comparable T>
std::size_t GetScenicScore(const Matrix<T>& mat, std::size_t row, std::size_t col)
{
    //elements on the edge of the matrix always have score of 0
    if (row == 0 || col == 0 || row == (mat.NumRows() - 1) || col == (mat.NumCols() - 1))
    {
        return 0;
    }

    const auto result = CountVisibleFromElement(mat, row, col);
    return std::reduce(result.begin(), result.end(), 1u, [](std::size_t current, const auto& item) {
        return current * item.how_many;
        });
}

int main(int argc, char* argv[])
{
    try
    {
        if (argc != 2)
        {
            std::cout << "Incorrect number of arguments\n";
            return 1;
        }

        if (std::ifstream data(argv[1]); data)
        {
            Matrix<std::size_t> mat;
            std::string buffer;
            while (std::getline(data, buffer))
            {
                mat.AddRow(ConvertStringToNumbers(buffer));
            }

            std::size_t max_scenic_score{};
            std::size_t num_visible{};
            for (auto row : std::views::iota(0u, mat.NumRows()))
            {
                for (auto col : std::views::iota(0u, mat.NumCols()))
                {
                    if (MatElementIsVisible(mat, row, col))
                    {
                        ++num_visible;
                    }

                    if (const auto score = GetScenicScore(mat, row, col); score > max_scenic_score)
                    {
                        max_scenic_score = score;
                    }
                }
            }

            std::cout << "Visible: " << num_visible << '\n'
                << "Max Scenic score: " << max_scenic_score << '\n';
            return 0;
        }

        std::cout << "There was a problem opening " << argv[1] << '\n';
        return 1;
    }
    catch (const std::exception& e)
    {
        std::cerr << e.what() << '\n';
        return 1;
    }
}