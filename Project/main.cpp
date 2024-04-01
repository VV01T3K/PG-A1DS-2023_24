#include <iostream>
#include <string>
#include <vector>

#include "HexBoard.hpp"
using namespace std;

#define MAX_BOARD_SIZE 11

Info getQuery() {
    string query;
    char c;
    while (cin.get(c)) {
        if (c >= 'A' && c <= 'B') break;
        if (c == EOF) return Info::STOP;
    }
    cin >> query;
    cin.ignore();
    if (query == "RD_SIZE") return Info::BOARD_SIZE;
    if (query == "NS_NUMBER") return Info::PAWNS_NUMBER;
    if (query == "BOARD_CORRECT") return Info::IS_BOARD_CORRECT;
    if (query == "GAME_OVER") return Info::IS_GAME_OVER;
    if (query == "BOARD_POSSIBLE") return Info::IS_BOARD_POSSIBLE;
    if (query == "_RED_WIN_IN_N_MOVE_WITH_NAIVE_OPPONENT")
        return Info::CAN_RED_WIN_IN_N_MOVE_WITH_NAIVE_OPPONENT;
    if (query == "_RED_WIN_IN_N_MOVE_WITH_PERFECT_OPPONENT")
        return Info::CAN_RED_WIN_IN_N_MOVE_WITH_PERFECT_OPPONENT;
    return Info::STOP;
}

int main() {
    HexBoard board;
    board.loadBoard();
    Info query = getQuery();
    board.fetchInfo(query);
    board.reset();

    while (true) {
        board.loadBoard();
        Info query = getQuery();
        if (query == Info::STOP) break;
        board.fetchInfo(query);
        board.reset();
    }

    return 0;
}