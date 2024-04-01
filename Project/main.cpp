#include <iostream>
#include <vector>

#include "HexBoard.hpp"
using namespace std;

#define MAX_BOARD_SIZE 11

int main() {
    HexBoard board;

    board.loadBoard();
    board.print();

    return 0;
}