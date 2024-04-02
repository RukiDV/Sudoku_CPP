#pragma once
#include <vector>
#include <cstdint>
#include <string>

enum ContentFlags
{
    CONTENT_FLAGS_NONE = 0,
    CONTENT_FLAGS_PRESET = (1u << 31)
};

class Board
{
public:
    Board(uint32_t size_x, uint32_t size_y);
    void set_field(uint32_t x, uint32_t y, uint8_t value, ContentFlags flags);
    std::pair<uint8_t, uint32_t> get_field(uint32_t x, uint32_t y) const;
    void set_value(uint32_t x, uint32_t y, uint8_t value);
    uint8_t get_value(uint32_t x, uint32_t y) const;
    void set_flags(uint32_t x, uint32_t y, ContentFlags flags);
    uint32_t get_flags(uint32_t x, uint32_t y) const;
    uint32_t get_size_x() const;
    uint32_t get_size_y() const;

    std::string to_string(bool compact = true) const;

private:
    uint32_t size_x = 0;
    uint32_t size_y = 0;
    std::vector<uint32_t> content;
    static const uint32_t flag_mask = 0xffffff00;
    static const uint32_t value_mask = 0x000000ff;

    uint32_t& get_field_ref(uint32_t x, uint32_t y);
    uint32_t get_field_content(uint32_t x, uint32_t y) const;
};

