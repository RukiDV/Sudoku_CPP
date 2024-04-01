cmake_minimum_required(VERSION 3.19)
project(Sudoku_CPP)
set(CMAKE_CXX_STANDARD 23)

set(SOURCE_FILES src/main.cpp src/board.cpp src/rules.cpp)

add_executable(Sudoku_CPP ${SOURCE_FILES})
include_directories(Sudoku_CPP PUBLIC "${PROJECT_SOURCE_DIR}/include")

