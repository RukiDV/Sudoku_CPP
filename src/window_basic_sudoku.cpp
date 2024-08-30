#include "window_basic_sudoku.hpp"

#include <iostream>

#include "log.hpp"

Window::Window(int width, int height, const char* title): width(width), height(height) {

    if (SDL_Init(SDL_INIT_VIDEO) != 0) {
        std::cout << "SDL_Init Error: " << SDL_GetError() << std::endl;
    }

    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 2);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 1);

    window = SDL_CreateWindow(title, SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, width, height, SDL_WINDOW_OPENGL | SDL_WINDOW_SHOWN);
    if (window == nullptr) {
        std::cout << "SDL_CreateWindow Error: " << SDL_GetError() << std::endl;
        SDL_Quit();
    }

    context = SDL_GL_CreateContext(window);
}

void Window::swapBuffers() {
    SDL_GL_SwapWindow(window);
}

bool Window::pollEvents(SDL_Event& event) {
    return SDL_PollEvent(&event);
}

void Window::clear() {
    glViewport(0, 0, width, height);
    glClearColor(0.05f, 0.05f, 0.05f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT);
}

void Window::draw_board(const Board& board, const glm::ivec2 selected_cell)
{
    draw_grid(selected_cell);
    int32_t number;
    for(uint32_t i = 0; i < GRID_SIZE; ++i)
    {
        for(uint32_t j = 0; j < GRID_SIZE; ++j)
        {
            uint32_t flags = board.get_flags(i, j);
            glm::vec3 color;
            if (flags & CONTENT_FLAGS_INVALID) continue;
            else if (flags & CONTENT_FLAGS_WRONG) color = glm::vec3(1.0, 0.0, 0.0);
            else if (flags & CONTENT_FLAGS_PRE_SET) color = glm::vec3(1.0, 1.0, 1.0);
            else if (flags & CONTENT_FLAGS_USER_SET) color = glm::vec3(0.0, 1.0, 1.0);
            else if (flags & CONTENT_FLAGS_BOT_SET) color = glm::vec3(1.0, 0.0, 1.0);
            else ERROR("Failed to determine set flags.");
            number = board.get_value(i,j);
            draw_dice_number(glm::ivec2(i, j), number, EXTENT, color);
        }
    }
}

void Window::draw_cell(float pos_x, float pos_y, float size, const glm::vec3& color)
{
    glLineWidth(5.0);
    glBegin(GL_LINES);
    glColor3f(color.r, color.g, color.b);
    glVertex2f(pos_x - size / 2.0, pos_y - size / 2.0);
    glVertex2f(pos_x - size / 2.0, pos_y + size / 2.0);
    glVertex2f(pos_x - size / 2.0, pos_y + size / 2.0);
    glVertex2f(pos_x + size / 2.0, pos_y + size / 2.0);
    glVertex2f(pos_x + size / 2.0, pos_y + size / 2.0);
    glVertex2f(pos_x + size / 2.0, pos_y - size / 2.0);
    glVertex2f(pos_x + size / 2.0, pos_y - size / 2.0);
    glVertex2f(pos_x - size / 2.0, pos_y - size / 2.0);
    glEnd();
}

glm::vec2 get_frame_cell_pos(glm::ivec2 cell_pos)
{
    return glm::vec2(-1.0 + CELL_OPENGL_SIZE.x / 2.0 + cell_pos.x * CELL_OPENGL_SIZE.x, 1.0 - CELL_OPENGL_SIZE.y / 2.0 - cell_pos.y * CELL_OPENGL_SIZE.y);
}

void Window::draw_grid(glm::ivec2 marked_cell)
{
    for (uint32_t i = 0; i < GRID_SIZE; i++)
    {
        for (uint32_t j = 0; j < GRID_SIZE; j++)
        {
            const glm::vec2 pos = get_frame_cell_pos({i, j});
            if (i == marked_cell.x && j == marked_cell.y) draw_cell(pos.x, pos.y, CELL_OPENGL_SIZE.y - 0.01, glm::vec3(0.0, 1.0, 1.0));
            else draw_cell(pos.x, pos.y, CELL_OPENGL_SIZE.y - 0.01);
        }
    }
}

void Window::draw_dice_number(glm::ivec2 cell_pos, uint32_t number, float extent, const glm::vec3& color)
{
    const glm::vec2 pos = get_frame_cell_pos(cell_pos);
    glPointSize(12.0);
    glBegin(GL_POINTS);
    glColor3f(color.r, color.g, color.b);
    switch (number) 
    {
        case 9:
            glVertex2f(pos.x + extent, pos.y - extent);
        case 8:
            glVertex2f(pos.x, pos.y - extent);
        case 7:
            glVertex2f(pos.x - extent, pos.y - extent);
        case 6:
            glVertex2f(pos.x + extent, pos.y);
        case 5:
            glVertex2f(pos.x, pos.y);
        case 4:
            glVertex2f(pos.x - extent, pos.y);
        case 3:
            glVertex2f(pos.x + extent, pos.y + extent);
        case 2:
            glVertex2f(pos.x, pos.y + extent);
        case 1:
            glVertex2f(pos.x - extent, pos.y + extent);
        break;
        default:
            std::cout << "Number does not exist" << std::endl;
        break;
    }
    glEnd();
}