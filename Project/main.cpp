#include "HexBoard.hpp"
using namespace std;

Info getQuery();

int main() {
    HexBoard board;
    while (true) {
        board.load();
        Info query = getQuery();
        if (query == Info::STOP) break;
        board.fetch(query);
        if (query > Info::IS_BOARD_POSSIBLE) {
            board.fetch(getQuery());
            board.fetch(getQuery());
            board.fetch(getQuery());
        }
    }
    return 0;
}

void ignoreChars(int n) {
    for (int i = 0; i < n; i++) getc(stdin);
}

/**
 * The function `getQuery` reads input characters from standard input and
 * determines the type of query based on the characters read.
 *
 * @return The function `getQuery()` returns an `Info` enum value based on the
 * input read from the standard input. The returned `Info` value corresponds to
 * the type of query being made in the input.
 */
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
                if (getc(stdin) == '1') {
                    ignoreChars(11);
                    if (getc(stdin) == 'N')
                        query = Info::CAN_RED_WIN_IN_1_MOVE_WITH_NAIVE_OPPONENT;
                    else
                        query =
                            Info::CAN_RED_WIN_IN_1_MOVE_WITH_PERFECT_OPPONENT;
                } else {
                    ignoreChars(12);
                    if (getc(stdin) == 'N')
                        query =
                            Info::CAN_RED_WIN_IN_2_MOVES_WITH_NAIVE_OPPONENT;
                    else
                        query =
                            Info::CAN_RED_WIN_IN_2_MOVES_WITH_PERFECT_OPPONENT;
                }
            } else {
                ignoreChars(11);
                if (getc(stdin) == '1') {
                    ignoreChars(11);
                    if (getc(stdin) == 'N')
                        query =
                            Info::CAN_BLUE_WIN_IN_1_MOVE_WITH_NAIVE_OPPONENT;
                    else
                        query =
                            Info::CAN_BLUE_WIN_IN_1_MOVE_WITH_PERFECT_OPPONENT;
                } else {
                    ignoreChars(12);
                    if (getc(stdin) == 'N')
                        query =
                            Info::CAN_BLUE_WIN_IN_2_MOVES_WITH_NAIVE_OPPONENT;
                    else
                        query =
                            Info::CAN_BLUE_WIN_IN_2_MOVES_WITH_PERFECT_OPPONENT;
                }
            }
            break;
    }
    while (true) {
        int c = getc(stdin);
        if (c == '-' || c == EOF || c == '\n') break;
    }
    return query;
}