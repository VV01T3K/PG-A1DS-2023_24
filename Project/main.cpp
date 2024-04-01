#include <iostream>

#include "HexBoard.hpp"
using namespace std;

int main() {
    int size = 11;
    HexBoard board(size);

    // char c;
    // while (cin.get(c)) {
    //     if (c == '.') break;
    //     if (c == '\n' || c == ' ' || c == '-') continue;
    //     cout << c << endl;
    // }

    board.hex(0, 0, 0).color = '0';

    // Hex* current = &board.hex(0, 0, 0);
    // current->neighbor(0).color = '0';

    board.print();
};