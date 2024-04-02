#include <iostream>

#include "board.hpp"

int main (int argc, char** argv)
{
    Board board(9, 9);
    std::cout << board << std::endl;
    return 0;
}

