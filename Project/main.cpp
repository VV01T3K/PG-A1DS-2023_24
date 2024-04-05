#include <iostream>  // TODO remove later

#include "HexBoard.hpp"
using namespace std;

Info getQuery();

int main() {
    HexBoard board;

    while (true) {
        board.load();
        Info query = getQuery();
        if (query == Info::STOP) break;
        board.fetchInfo(query);
        board.reset();
    }

    return 0;
}

void ignoreChars(int n) {
    for (int i = 0; i < n; i++) getc(stdin);
}

Info getQuery() {
    Info query = Info::STOP;
    switch (getc(stdin)) {
        case 'B':
            query = Info::BOARD_SIZE;
            break;
        case 'P':
            query = Info::PAWNS_NUMBER;
            break;
        case 'I':
            ignoreChars(8);
            switch (getc(stdin)) {
                case 'C':
                    query = Info::IS_BOARD_CORRECT;
                    break;
                case 'V':
                    query = Info::IS_GAME_OVER;
                    break;
                case 'P':
                    query = Info::IS_BOARD_POSSIBLE;
                    break;
            }
            break;
        case 'C':
            // TODO
            break;
    }
    char c;
    while (true) {
        c = getc(stdin);
        if (c == '\n' || c == EOF) break;
    }
    return query;
}