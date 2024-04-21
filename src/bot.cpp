#include "bot.hpp"

#include <limits>
#include <vector>
#include <unordered_map>
#include <cassert>

#include "rules.hpp"

uint64_t get_key(uint32_t x, uint32_t y)
{
    return (uint64_t(x) << 32) | y;
}

std::pair<uint32_t, uint32_t> get_indices(uint64_t key)
{
    return std::make_pair(key >> 32, key & 0x00000000ffffffff);
}

void init(Board& board, std::unordered_map<uint64_t, std::vector<int32_t>>& buckets)
{
    buckets.clear();
    // iterates over the whole board, at each field it saves all correct values in a bucket
    for (uint32_t i = 0; i < board.get_size_x(); i++)
    {
        for (uint32_t j = 0; j < board.get_size_y(); j++)
        {
            if (!(board.get_flags(i, j) & CONTENT_FLAGS_INVALID)) continue;
            uint64_t key = get_key(i, j);
            buckets.emplace(key, std::vector<int32_t>());
            for (int k = 1; k < 10; k++)
            {
                board.set_field(i, j, k, CONTENT_FLAGS_BOT_SET);
                if (rules::check_rules(board)) buckets.at(key).push_back(k);
                board.set_field(i, j, 0, CONTENT_FLAGS_INVALID);
            }
        }
    }
}

void update_buckets(uint32_t x, uint32_t y, int32_t value, std::unordered_map<uint64_t, std::vector<int32_t>>& buckets)
{
    for (auto& [key, b] : buckets)
    {
        auto [x1, y1] = get_indices(key);
        if (rules::is_dependent(x, y, x1, y1))
        {
            for (auto it = b.begin(); it != b.end(); it++)
            {
                if (*it == value)
                {
                    b.erase(it);
                    break;
                }
            }
        }
    }
}

bool solve(Board& board, std::unordered_map<uint64_t, std::vector<int32_t>>& buckets, bool test_uniquely_solvable = false)
{
    bool done = false;
    while (!done)
    {
        if (buckets.empty())
        {
            // no empty fields, board has to be valid as we should never have created an invalid board
            // assert that every field contains value and board is valid
            assert(rules::is_finished(board));
            return true;
        }
        uint64_t min_key = 0;
        uint32_t min = std::numeric_limits<uint32_t>::max();
        for (const auto& [key, b] : buckets)
        {
            if (b.size() < min)
            {
                min = b.size();
                min_key = key;
            }
        }
        auto [x, y] = get_indices(min_key);

        if (min == 0)
        {
            // empty field with no possible value, returns false because unsolvable
            assert(!rules::is_finished(board));
            return false;
        }
        else if (min == 1) // field with only one possible value
        {
            board.set_field(x, y, buckets.at(min_key)[0], CONTENT_FLAGS_BOT_SET);
            update_buckets(x, y, buckets.at(min_key)[0], buckets);
            buckets.erase(min_key);
        }
        else // multiple choices possible, guess one element, try if it works out
        {
            for (uint32_t i = 0; buckets.at(min_key).size(); i++)
            {
                int32_t value = buckets.at(min_key).back();
                buckets.at(min_key).pop_back();
                Board board_copy(board);
                std::unordered_map<uint64_t, std::vector<int32_t>> buckets_copy = buckets;
                board_copy.set_field(x, y, value, CONTENT_FLAGS_BOT_SET);
                update_buckets(x, y, value, buckets_copy);
                buckets_copy.erase(min_key);
                if (solve(board_copy, buckets_copy))
                {
                    if (!test_uniquely_solvable)
                    {
                        board = board_copy;
                        buckets.erase(min_key);
                        return true;
                    }
                    board.set_field(x, y, value, CONTENT_FLAGS_BOT_SET);
                    update_buckets(x, y, value, buckets);
                }
            }
        }
    }
    assert(false);
    return false;
}

bool Bot::solve(Board& board)
{
    std::unordered_map<uint64_t, std::vector<int32_t>> buckets;
    init(board, buckets);
    return ::solve(board, buckets);
}

Bot::Bot(const Board& board) : solved_board(board)
{
    solve(solved_board);
}

Bot::Step Bot::step(const Board& board) const
{
    if (is_solvable())
    {
        for (uint32_t i = 0; i < board.get_size_x(); i++)
        {
            for (uint32_t j = 0; j < board.get_size_y(); j++)
            {
                if((board.get_flags(i, j) & CONTENT_FLAGS_INVALID)) return Bot::Step{.x = i, .y = j, .value = solved_board.get_value(i, j)};
            }
        }
    }
    return Bot::Step();
}

bool Bot::is_solvable() const
{
    return rules::is_finished(solved_board);
}

uint32_t Bot::get_solution(uint32_t x, uint32_t y) const
{
    return get_solution().get_value(x, y);
}

Board Bot::get_solution() const
{
    return solved_board;
}

