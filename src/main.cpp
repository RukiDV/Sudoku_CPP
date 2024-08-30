#include <iostream>
#include <limits>
#include <SDL2/SDL.h>
#include <SDL2/SDL_opengl.h>
#include <glm/vec3.hpp>

#include "board.hpp"
#include "board_factory.hpp"
#include "log.hpp"
#include "rules.hpp"
#include "bot.hpp"
#include "window_basic_sudoku.hpp"

void apply_user_input(Board& board, glm::uvec2(user_input), uint32_t user_input_value, const Bot& bot)
{
    if (!(board.get_flags(user_input.x, user_input.y) & CONTENT_FLAGS_PRE_SET) && !(board.get_flags(user_input.x, user_input.y) & CONTENT_FLAGS_BOT_SET))
    {
        if (user_input_value == 0) board.set_flags(user_input.x, user_input.y, CONTENT_FLAGS_INVALID);
        else
        {
            board.set_field(user_input.x, user_input.y, user_input_value, CONTENT_FLAGS_USER_SET);
            if (user_input_value != bot.get_solution(user_input.x, user_input.y)) board.add_flag(user_input.x, user_input.y, CONTENT_FLAGS_WRONG);
        }
    } else std::cout << get_colored("You can not overwrite given field values!\n", Color::Red);
}

int main (int argc, char** argv)
{
    Window window(WINDOW_SIZE.x, WINDOW_SIZE.y, "Sudoku Game");

    Board board = build_sudoku_board(10);
    Bot bot(board);

    SDL_Event event;
    glm::ivec2 selected_cell(-1, -1);
    bool quit = false;
    while (!quit)
    {
        while (window.pollEvents(event))
        {
            if (event.type == SDL_QUIT)
            {
                quit = true;
            }
            else if (event.type == SDL_WINDOWEVENT)
            {
                if (event.window.event == SDL_WINDOWEVENT_CLOSE)
                {
                    quit = true;
                }
            }
            else if (event.type == SDL_MOUSEBUTTONDOWN)
            {
                int x, y;
                SDL_GetMouseState(&x, &y);
                selected_cell = glm::ivec2(x / CELL_SIZE.x, y / CELL_SIZE.y);
            }
            else if (event.type == SDL_KEYDOWN)
            {
                int x, y;
                SDL_GetMouseState(&x, &y);
                switch (event.key.keysym.sym)
                {
                    case SDLK_1:
                        apply_user_input(board, selected_cell, 1, bot);
                        break;
                    case SDLK_2:
                        apply_user_input(board, selected_cell, 2, bot);
                        break;
                    case SDLK_3:
                        apply_user_input(board, selected_cell, 3, bot);
                        break;
                    case SDLK_4:
                        apply_user_input(board, selected_cell, 4, bot);
                        break;
                    case SDLK_5:
                        apply_user_input(board, selected_cell, 5, bot);
                        break;
                    case SDLK_6:
                        apply_user_input(board, selected_cell, 6, bot);
                        break;
                    case SDLK_7:
                        apply_user_input(board, selected_cell, 7, bot);
                        break;
                    case SDLK_8:
                        apply_user_input(board, selected_cell, 8, bot);
                        break;
                    case SDLK_9:
                        apply_user_input(board, selected_cell, 9, bot);
                        break;    
                    default:
                        std::cout << "Some other key pressed." << std::endl;
                        break;
                }
                if (rules::is_finished(board))
                {
                    quit = true;
                    std::cout << get_colored("Congratulations, your sudoku is correct!\n", Color::Pink);
                }
            }
        }

        window.clear();
        window.draw_board(board, selected_cell);
        glEnd();
        window.swapBuffers();
    }
    return 0;
}

