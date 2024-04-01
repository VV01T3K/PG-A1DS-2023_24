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
    current->symbol = 'S';
    for (int i = 0; i < 6; i++) {
        current->neighbor(i)->symbol = 49 + i;
    }
    // 12X
    // 6S3
    // X54

    board.print();

    return 0;
}