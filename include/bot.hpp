#pragma once
#include <cstdint>
#include "board.hpp"

class Bot
{
public:
    struct Step
    {
        uint32_t x = 0;
        uint32_t y = 0;
        uint8_t value = 0;
    };

    Bot(const Board& board);
    bool is_solvable() const;
    uint32_t get_solution(uint32_t x, uint32_t y) const;
    Board get_solution() const;
    Bot::Step step(const Board& board) const;
    static bool solve(Board& board);
private:
    Board solved_board;
};

