#include "HexBoard.hpp"
using namespace std;

Info getQuery();

int main() {
    HexBoard board;

    while (true) {
        board.load();
        Info query;
        for (int i = 0; i < 4; ++i) {
            query = getQuery();
            if (query == Info::STOP) break;
            board.fetchInfo(query);
        }
        if (query == Info::STOP) break;
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
            ignoreChars(3);
            if (getc(stdin) == 'R') {
                ignoreChars(10);
                if (getc(stdin) == '1')
                    query = Info::CAN_RED_WIN_IN_1_MOVE_WITH_NAIVE_OPPONENT;
                else
                    query = Info::CAN_RED_WIN_IN_2_MOVE_WITH_NAIVE_OPPONENT;
            } else {
                ignoreChars(11);
                if (getc(stdin) == '1')
                    query = Info::CAN_BLUE_WIN_IN_1_MOVE_WITH_NAIVE_OPPONENT;
                else
                    query = Info::CAN_BLUE_WIN_IN_2_MOVE_WITH_NAIVE_OPPONENT;
            }
            break;
    }
    char c;
    while (true) {
        c = getc(stdin);
        if (c == '-' || c == EOF || c == '\n') break;
    }
    return query;
}