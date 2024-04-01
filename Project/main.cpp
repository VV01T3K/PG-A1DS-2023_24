#include <iostream>

#include "HexBoard.hpp"

int main() {
    int size = 11;
    HexBoard board(size);

    board.hex(0, 0, 0).color = '0';
    board.hex(1, 0, 1).color = '1';
    board.hex(0, 1, 1).color = '2';
    board.hex(1, 1, 1).color = '3';

    for (int i = 0; i < size; i++) {
        for (int j = 0; j < size; j++) {
            std::cout << board.hex(i, j, -i - j).color << " ";
        }
        std::cout << std::endl;
    }
};