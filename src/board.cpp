#include "board.hpp"
#include <cassert>

Board::Board(uint32_t size_x, uint32_t size_y) : size_x(size_x), size_y(size_y), content(size_x * size_y, 0)
{}

uint32_t Board::get_field_content(uint32_t x, uint32_t y) const
{
    assert(x < size_x && y < size_y);
    return content[size_x * y + x];
}

uint32_t& Board::get_field_ref(uint32_t x, uint32_t y)
{
    assert(x < size_x && y < size_y);
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
    get_field_ref(x, y) |= value;
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

