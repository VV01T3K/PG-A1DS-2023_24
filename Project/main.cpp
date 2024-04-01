#include <iostream>
#include <vector>

#include "HexBoard.hpp"
using namespace std;

int main() {
    // enum State { EMPTY = ' ', RED = 'r', BLUE = 'b' };

    vector<vector<char>> tmp;
    int size = 0;
    int width = 0;
    char c;
    while (cin.get(c)) {
        if (c == '.') break;
        if (c == '-') continue;
        if (c == ' ') continue;
        if (c == '<') {
            width++;
            cin >> c;
            if (c == '>') c = 'x';
            tmp.back().push_back(c);
        }
        if (c == '>') continue;
        if (c == '\n') {
            // if (width < size) break;
            size = max(size, width);
            width = 0;
            tmp.push_back({});
            continue;
        }
    }
    for (int i = 0; i < tmp.size(); i++) {
        for (int j = 0; j < tmp[i].size(); j++) {
            cout << tmp[i][j];
        }
        cout << endl;
    }
    HexBoard board(11);

    size = 3;
    board.getHex(0, 0)->symbol = tmp[0][0];

    board.getHex(0, 1)->symbol = tmp[1][0];
    board.getHex(1, 0)->symbol = tmp[1][1];

    board.getHex(0, 2)->symbol = tmp[2][0];
    board.getHex(1, 1)->symbol = tmp[2][1];
    board.getHex(2, 0)->symbol = tmp[2][2];

    board.getHex(1, 2)->symbol = tmp[3][0];
    board.getHex(2, 1)->symbol = tmp[3][1];

    board.getHex(2, 2)->symbol = tmp[4][0];

    cout << endl << "==================" << endl;
    board.print();

    return 0;
}