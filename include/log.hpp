#pragma once

#include <sstream>
#include <iostream>
#include <format>

enum class Color
{
    Red,
    Green,
    Yellow,
    Blue,
    Pink,
    LightBlue,
    White
};

template<class T>
std::string get_colored(const T& value, const Color color)
{
    std::stringstream colored_value;
    switch (color)
    {
        case Color::Red:
            colored_value << "\033[91m";
            break;
        case Color::Green:
            colored_value << "\033[92m";
            break;
        case Color::Yellow:
            colored_value << "\033[93m";
            break;
        case Color::Blue:
            colored_value << "\033[94m";
            break;
        case Color::Pink:
            colored_value << "\033[95m";
            break;
        case Color::LightBlue:
            colored_value << "\033[96m";
            break;
        case Color::White:
            colored_value << "\033[0m";
            break;
        default:
            colored_value << "";
            break;
    }
    colored_value << value << "\033[0m";
    return colored_value.str();
}

#define ERROR(...)                                              \
{                                                               \
    std::string s = std::format("{}:{}", __FILE__, __LINE__);   \
    std::cerr << get_colored("ERROR: ", Color::Red);            \
    std::cerr << s << "\n" << __VA_ARGS__ << std::endl;         \
    throw std::runtime_error(s);                                \
}                                                               \

