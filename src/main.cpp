#include <iostream>
#include <limits>

#include "board.hpp"
#include "board_factory.hpp"

std::istream& get_user_input()
{
    std::cout << "> ";
    return std::cin;
}

int32_t get_user_integer(int32_t lower_bound = std::numeric_limits<int32_t>::min(), int32_t upper_bound = std::numeric_limits<int32_t>::max())
{
    std::cout << "Possible range: [" << lower_bound << ", " << upper_bound << "]" << std::endl;
    int32_t input;
    get_user_input() >> input;
    while (input > upper_bound || input < lower_bound)
    {
        std::cout << "Outside of permitted range! Try again." << std::endl;
        get_user_input() >> input;
    }
    return input;
}

int main (int argc, char** argv)
{
    Board board(9, 9);
    build_sudoku_board(board, 50);
    while (true)
    {
        std::cout << board << std::endl;
        // Input x-coordinate
        std::cout << "Enter your x-coordinate\n";
        int32_t user_input_x = get_user_integer(1, 9);
        // Input y-coordinate
        std::cout << "Enter your y-coordinate\n";
        int32_t user_input_y = get_user_integer(1, 9);
        // Input value
        std::cout << "Enter your value (0 to delete): ";
        int32_t user_input_value = get_user_integer(0, 9);
        board.set_field(user_input_x - 1, user_input_y - 1, user_input_value, CONTENT_FLAGS_NONE);
    }
    std::cout << board << std::endl;
    return 0;
}

