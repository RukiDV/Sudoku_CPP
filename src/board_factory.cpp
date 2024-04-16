#include "board_factory.hpp"

#include <cassert>

#include "board.hpp"
#include "rules.hpp"
#include "random_generator.hpp"
#include "bot.hpp"

void delete_values(Board& board, uint32_t value_count)
{
    assert(value_count <= board.get_size_x() * board.get_size_y());
    for (uint32_t i = 0; i < value_count;)
    {
        int32_t x = rnd::random_int(0, 9);
        int32_t y = rnd::random_int(0, 9);
        if (!(board.get_flags(x,y) & CONTENT_FLAGS_INVALID))
        {
            board.set_flags(x, y, CONTENT_FLAGS_INVALID);
            i++;
        }
    }
}

Board build_sudoku_board(uint32_t value_count)
{
    Board board(9, 9);
    int32_t y = rnd::random_int(0, 9);
    int32_t x = rnd::random_int(0, 9);
    int32_t value = rnd::random_int(1, 10);
    board.set_field(x, y, value, CONTENT_FLAGS_PRE_SET);

    Bot::solve(board);
    for (uint32_t i = 0; i < board.get_size_x(); i++)
    {
        for (uint32_t j = 0; j < board.get_size_y(); j++)
        {
            if (!(board.get_flags(i, j) & CONTENT_FLAGS_INVALID)) board.set_flags(i, j, CONTENT_FLAGS_PRE_SET);
        }
    }
    delete_values(board, value_count);
    return board;
}

