#include "rules.hpp"
#include "board.hpp"
#include <iostream>
#include <unordered_set>

bool check_row(const Board& board, uint32_t x)
{
    std::unordered_set<uint8_t> map;
    // check if value is in map, if true return false
    for (int i = 0; i < board.get_size_x(); i++)
    {
        if (board.get_flags(x, i) & CONTENT_FLAGS_INVALID) continue;
        if (!map.emplace(board.get_value(x, i)).second) return false;
    }
    return true;
}

bool check_column(const Board& board, uint32_t x)
{
    std::unordered_set<uint8_t> map;
    // check if value is in map, if true return false
    for (int i = 0; i < board.get_size_y(); i++)
    {
        if (board.get_flags(i, x) & CONTENT_FLAGS_INVALID) continue;
        if (!map.emplace(board.get_value(i, x)).second) return false;
    }
    return true;
}

bool check_square(const Board& board, uint32_t x, uint32_t y)
{
    std::unordered_set<uint8_t> map;
    for (int i = 3 * x; i < 3 * (x + 1); i++)
    {
        for (int j = 3 * y; j < 3 * (y + 1); j++)
        {
            if (board.get_flags(i, j) & CONTENT_FLAGS_INVALID) continue;
            if (!map.emplace(board.get_value(i, j)).second) return false;
        }
    }
    return true;
}

namespace basic_sudoku
{
bool check_rules(const Board& board)
{
    bool valid = true;
    for (int i = 0; i < board.get_size_y(); i++)
    {
        valid &= check_row(board, i);
    }
    for (int i = 0; i < board.get_size_x(); i++)
    {
        valid &= check_column(board, i);
    }
    for (int i = 0; i < board.get_size_x() / 3; i++)
    {
        for (int j = 0; j < board.get_size_y() / 3; j++)
        {
            valid &= check_square(board, i, j);
        }
    }
    return valid;
}

bool is_dependent(uint32_t x0, uint32_t y0, uint32_t x1, uint32_t y1)
{
    if (x0 == x1 || y0 == y1) return true;
    else if (x0 / 3 == x1 / 3 && y0 / 3 == y1 / 3) return true;
    else return false;
}

bool is_finished(const Board& board)
{
    bool finished = check_rules(board);
    for (int i = 0; i < board.get_size_x(); i++)
    {
        for (int j = 0; j < board.get_size_y(); j++)
        {
            finished &= !(board.get_flags(i, j) & CONTENT_FLAGS_INVALID);
        }
    }
    return finished;
}
} // namespace basic_sudoku

