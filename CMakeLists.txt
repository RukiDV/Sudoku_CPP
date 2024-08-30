cmake_minimum_required(VERSION 3.19)
project(Sudoku_CPP)
set(CMAKE_CXX_STANDARD 23)

set(SOURCE_FILES src/main.cpp src/board.cpp src/rules.cpp src/random_generator.cpp src/board_factory.cpp src/bot.cpp src/window_basic_sudoku.cpp)

add_executable(Sudoku_CPP ${SOURCE_FILES})
include_directories(Sudoku_CPP PUBLIC "${PROJECT_SOURCE_DIR}/include")
find_package(SDL2 REQUIRED)
find_package(OpenGL)
find_package(glm)

target_include_directories(Sudoku_CPP PRIVATE ${GLM_INCLUDE_DIRS})
target_link_libraries(Sudoku_CPP SDL2::SDL2main SDL2::SDL2 OpenGL::OpenGL)

