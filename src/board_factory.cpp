#include "board_factory.hpp"

#include <cassert>

#include "board.hpp"
#include "rules.hpp"
#include "random_generator.hpp"

void build_sudoku_board(Board& board, uint32_t value_count)
{
    assert(value_count <= board.get_size_x() * board.get_size_y());
    for (int i = 0; i < value_count;)
    {
        int32_t x = rnd::random_int(0, 9);
        int32_t y = rnd::random_int(0, 9);
        if (board.get_value(x, y) != 0) continue;
        int32_t value = rnd::random_int(1, 10);
        board.set_value(x, y, value);
        if (check_basic_sudoku_rules(board)) i++;
        else board.set_value(x, y, 0);
    }
}

