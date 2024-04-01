#include "HexBoard.hpp"

int main() {
    HexBoard board(3);

    // board.getHex(0, 0)->symbol = '0';
    // board.getHex(0, 1)->symbol = '1';
    // board.getHex(1, 0)->symbol = '2';
    // board.getHex(0, 2)->symbol = '3';
    // board.getHex(1, 1)->symbol = '4';
    // board.getHex(2, 0)->symbol = '5';
    // // board.getHex(0, 2)->symbol = '6';
    // // board.getHex(1, 2)->symbol = '7';
    // // board.getHex(2, 2)->symbol = '8';

    Hex* current = board.getHex(1, 1);
    current->symbol = '0';
    // current->neighbor(Direction::N)->symbol = 'N';
    // current->neighbor(Direction::NE)->symbol = '0';
    // current->neighbor(Direction::SE)->symbol = '1';
    current->neighbor(Direction::SE)->symbol = '1';
    // current->neighbor(Direction::SW)->symbol = '2';
    // current->neighbor(Direction::NW)->symbol = '3';

    board.print();

    return 0;
}