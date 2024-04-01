#include <iostream>

#include "HexBoard.hpp"
using namespace std;

int main() {
    int size = 11;
    HexBoard board(size);

    char c;
    while (/* condition */) {
        /* code */
    }

    board.hex(0, 0, 0).color = '0';
    board.hex(1, 0, 1).color = '1';
    board.hex(0, 1, 1).color = '2';
    board.hex(2, 0, 2).color = '3';
    board.hex(1, 1, 2).color = '4';
    board.hex(0, 2, 2).color = '5';
    board.hex(3, 0, 3).color = '6';
    board.hex(2, 1, 3).color = '7';
    board.hex(1, 2, 3).color = '8';
    board.hex(0, 3, 3).color = '9';

    for (int i = 0; i < size; i++) {
        for (int j = 0; j < size; j++) {
            std::cout << board.hex(i, j, -i - j).color << " ";
        }
        std::cout << std::endl;
    }
};