#include <iostream>
#include <string>
#include <vector>

#include "HexBoard.hpp"
using namespace std;

Info getQuery();

int main() {
    ios_base::sync_with_stdio(false);
    HexBoard board;
    board.load();

    // Hex* start = board.getHex(0, 0);
    // Hex* end = board.getHex(1, 2);

    // start->state = Hex::State::RED;
    // end->state = Hex::State::RED;

    // cout << start->distance(end) << endl;

    // board.print();
    // while (true) {
    //     board.load();
    //     Info query = getQuery();
    //     if (query == Info::STOP) break;
    //     board.fetchInfo(query);
    //     board.reset();
    // }
    board.print();

    return 0;
}

Info getQuery() {
    string query;
    cin >> query;
    cin.ignore(2);
    if (query == "OARD_SIZE") return Info::BOARD_SIZE;
    if (query == "WNS_NUMBER") return Info::PAWNS_NUMBER;
    if (query == "OARD_CORRECT") return Info::IS_BOARD_CORRECT;
    if (query == "ME_OVER") return Info::IS_GAME_OVER;
    if (query == "OARD_POSSIBLE") return Info::IS_BOARD_POSSIBLE;
    if (query == "N_RED_WIN_IN_N_MOVE_WITH_NAIVE_OPPONENT")
        return Info::CAN_RED_WIN_IN_N_MOVE_WITH_NAIVE_OPPONENT;
    if (query == "N_RED_WIN_IN_N_MOVE_WITH_PERFECT_OPPONENT")
        return Info::CAN_RED_WIN_IN_N_MOVE_WITH_PERFECT_OPPONENT;
    return Info::STOP;
}