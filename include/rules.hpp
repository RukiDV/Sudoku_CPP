#pragma once
#include <cstdint>

class Board;

namespace basic_sudoku
{
bool check_rules(const Board& board);
bool is_finished(const Board& board);
bool is_dependent(uint32_t x0, uint32_t y0, uint32_t x1, uint32_t y1);
} // namespace basic_sudoku

namespace rules = basic_sudoku;

