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
        if (!map.emplace(board.get_value(x, i)).second) return false;
    }
}

bool check_column(const Board& board, uint32_t x)
{
    std::unordered_set<uint8_t> map;
    // check if value is in map, if true return false
    for (int i = 0; i < board.get_size_y(); i++)
    {
        if (!map.emplace(board.get_value(i, x)).second) return false;
    }
}

bool check_square(const Board& board, uint32_t x, uint32_t y)
{
    std::unordered_set<uint8_t> map;
    for (int i = 3 * x; i < 3 * (x + 1); i++)
    {
        for (int j = 3 * y; j < 3 * (y + 1); j++)
        {
            if (!map.emplace(board.get_value(i, j)).second) return false;
        }
    }
}

void check_basic_rules(const Board& board)
{
    for (int i = 0; i < board.get_size_y(); i++)
    {
        check_row(board, i);
    }
    for (int i = 0; i < board.get_size_x(); i++)
    {
        check_column(board, i);
    }
    for (int i = 0; i < board.get_size_x() / 3; i++)
    {
        for (int j = 0; j < board.get_size_y() / 3; j++)
        {
            check_square(board, i, j);
        }
    }
}
