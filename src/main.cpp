#include <iostream>
#include <limits>

#include "board.hpp"
#include "board_factory.hpp"
#include "log.hpp"
#include "rules.hpp"

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
    Board board = build_sudoku_board(40);

    bool quit = false;
    while (!quit)
    {
        std::cout << board << std::endl;
        // Input x-coordinate
        std::cout << "Enter your x-coordinate\n";
        int32_t user_input_x = get_user_integer(1, 9) - 1;
        // Input y-coordinate
        std::cout << "Enter your y-coordinate\n";
        int32_t user_input_y = get_user_integer(1, 9) - 1;
        // Input value
        std::cout << "Enter your value (0 to delete)\n";
        int32_t user_input_value = get_user_integer(0, 9);
        if (!(board.get_flags(user_input_x, user_input_y) & CONTENT_FLAGS_PRE_SET) && !(board.get_flags(user_input_x, user_input_y) & CONTENT_FLAGS_BOT_SET))
        {
            if (user_input_value == 0) board.set_flags(user_input_x, user_input_y, CONTENT_FLAGS_INVALID);
            else board.set_field(user_input_x, user_input_y, user_input_value, CONTENT_FLAGS_USER_SET);
        } else
        {
            std::cout << get_colored("You can not overwrite given field values!\n", Color::Red);
        }
        bool done = true;
        for (uint32_t i = 0; i < board.get_size_x(); ++i)
        {
            for (uint32_t j = 0; j < board.get_size_y(); ++j)
            {
                done &= !(board.get_flags(i, j) & CONTENT_FLAGS_INVALID);
            }
        }
        done &= rules::check_rules(board);
        quit |= done;
    }
    std::cout << get_colored("Congratulations, your sudoku is correct!\n", Color::Pink);

    return 0;
}

