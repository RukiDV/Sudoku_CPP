#include "board.hpp"
#include <cassert>
#include <sstream>
#include <iostream>
#include <log.hpp>

Board::Board(uint32_t size_x, uint32_t size_y) : size_x(size_x), size_y(size_y), content(size_x * size_y, CONTENT_FLAGS_INVALID)
{}

uint32_t Board::get_field_content(uint32_t x, uint32_t y) const
{
    assert(x < size_x && y < size_y && x >= 0 && y >= 0);
    return content[size_x * y + x];
}

uint32_t& Board::get_field_ref(uint32_t x, uint32_t y)
{
    assert(x < size_x && y < size_y && x >= 0 && y >= 0);
    return content[size_x * y + x];
}

void Board::set_field(uint32_t x, uint32_t y, uint8_t value, ContentFlags flags)
{
    assert(!(flags & value_mask));
    get_field_ref(x, y) = uint32_t(value) | flags;
}

std::pair<uint8_t, uint32_t> Board::get_field(uint32_t x, uint32_t y) const
{
    return std::make_pair<uint8_t, uint32_t>(get_value(x, y), get_flags(x, y));
}

void Board::set_value(uint32_t x, uint32_t y, uint8_t value)
{
    assert(!(value & flag_mask));
    get_field_ref(x, y) &= flag_mask;
    get_field_ref(x, y) |= uint32_t(value);
}

uint8_t Board::get_value(uint32_t x, uint32_t y) const
{
    return get_field_content(x, y) & value_mask;
}

void Board::set_flags(uint32_t x, uint32_t y, ContentFlags flags)
{
    assert(!(flags & value_mask));
    get_field_ref(x, y) &= value_mask;
    get_field_ref(x, y) |= flags;
}

uint32_t Board::get_flags(uint32_t x, uint32_t y) const
{
    return get_field_content(x, y) & flag_mask;
}

uint32_t Board::get_size_x() const 
{
    return size_x;
}

uint32_t Board::get_size_y() const
{
    return size_y;
}

std::string Board::to_string(bool compact) const
{
    std::stringstream board_string;
    std::string big_horizontal_separator = "=====================================\n";
    std::string small_horizontal_separator = "-------------------------------------\n";
    std::string big_vertical_separator = "║";
    std::string small_vertical_separator = "|";
    if (compact)
    {
        big_horizontal_separator = "-------------------------\n";
        small_horizontal_separator = "";
        big_vertical_separator = small_vertical_separator;
        small_vertical_separator = "";
    }
    for (int i = 0; i < size_x; i++)
    {
        board_string << (i % 3 == 0 ? big_horizontal_separator : small_horizontal_separator);
        board_string << big_vertical_separator << " ";
        for (int j = 0; j < size_y; j++)
        {
            uint32_t flags = get_flags(i, j);
            if (flags & CONTENT_FLAGS_INVALID) board_string << " ";
            else if (flags & CONTENT_FLAGS_PRE_SET) board_string << get_colored(uint32_t(get_value(i, j)), Color::White);
            else if (flags & CONTENT_FLAGS_USER_SET) board_string << get_colored(uint32_t(get_value(i, j)), Color::LightBlue);
            else ERROR("Failed to determine set flags.");
            if (j != size_y - 1)
            {
                std::string output = " ";
                if (j % 3 == 2) output.append(big_vertical_separator + " ");
                else if (!small_vertical_separator.empty()) output.append(small_vertical_separator + " ");
                board_string << output;
            }
        }
        board_string << " " << big_vertical_separator << "\n";
    }
    board_string << big_horizontal_separator << std::flush;
    return board_string.str();
}

std::ostream& operator<<(std::ostream& os, const Board& board)
{
    os << board.to_string();
    return os;
}

