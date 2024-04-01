#include <iostream>
#include <vector>

#include "HexBoard.hpp"
using namespace std;

#define MAX_BOARD_SIZE 11

int main() {
    // enum State { EMPTY = ' ', RED = 'r', BLUE = 'b' };
    HexBoard board;

    board.loadBoard();
    board.print();

    return 0;
}