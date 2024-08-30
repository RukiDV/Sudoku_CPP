#pragma once

#include <SDL2/SDL.h>
#include <SDL2/SDL_opengl.h>
#include <glm/vec2.hpp>
#include <glm/vec3.hpp>
#include "board.hpp"

constexpr glm::uvec2 WINDOW_SIZE{1200, 1200};
constexpr int32_t GRID_SIZE = 9;
constexpr float EXTENT = 0.06f;
constexpr glm::ivec2 CELL_SIZE{WINDOW_SIZE.x / GRID_SIZE, WINDOW_SIZE.y / GRID_SIZE};
constexpr glm::vec2 CELL_OPENGL_SIZE{2.0 / float(GRID_SIZE), 2.0 / float(GRID_SIZE)};

class Window
{
public:
    Window(int width, int height, const char* title);

    void swapBuffers();
    bool pollEvents(SDL_Event& event);
    void clear();
    void draw_board(const Board& board, const glm::ivec2 selected_cell);

private:
    SDL_Window* window;
    SDL_GLContext context;
    int width; 
    int height;

    void draw_grid(glm::ivec2 marked_cell = glm::ivec2(-1, -1));
    void draw_cell(float pos_x, float pos_y, float size, const glm::vec3& color = glm::vec3(1.0, 0.0, 1.0));
    void draw_dice_number(glm::ivec2 pos, uint32_t number, float extent, const glm::vec3& color = glm::vec3(1.0, 1.0, 1.0));
};