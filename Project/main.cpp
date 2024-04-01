#include <iostream>
#include <vector>

#include "HexBoard.hpp"
using namespace std;

int main() {
    // enum State { EMPTY = ' ', RED = 'r', BLUE = 'b' };
    int index = 0;
    char tmp[11 * 11];
    int size = 0;
    int width = 0;
    char c;
    while (cin.get(c)) {
        if (c == EOF) break;
        if (c == '-' || c == ' ' || c == '>') continue;
        if (c == '<') {
            width++;
            cin >> c;
            if (c == '>') c = 'x';
            tmp[index++] = c;
        }
        if (c == '\n') {
            size = max(size, width);
            width = 0;
        }
    }
    HexBoard board(11);
    int q = 0;
    int r = 0;
    index = 0;
    for (int i = 0; i < 2 * size - 1; i++) {
        int tmp_q = q;
        int tmp_r = r;
        for (int j = 0; j < abs(q - r) + 1; j++) {
            board.getHex(tmp_q, tmp_r)->symbol = tmp[index++];
            tmp_q++;
            tmp_r--;
        }
        if (i < size - 1)
            r++;
        else
            q++;
    }

    board.print();

    return 0;
}