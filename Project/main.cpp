#include <iostream>
#include <string>
#include <vector>

#include "HexBoard.hpp"
#include "Path.hpp"
using namespace std;

Info getQuery();

int main() {
    ios_base::sync_with_stdio(false);
    HexBoard board;
    // board.load();
    // board.print();
    // Path path = board.findWiningPath(Player::RED);
    // if (path.length == MAX_INT) {
    //     cout << "No path found\n";
    //     return 0;
    // }
    // for (auto hex : path.hexes) {
    //     // cout << hex->position.q << ' ' << hex->position.r << '\n';
    //     hex->state = Hex::State::UNDEFINED;
    //     cout << '\n';
    //     board.print();
    // }
    while (true) {
        board.load();
        board.print();
        Info query = getQuery();
        // std::cout << "checking\n";
        // if (query == Info::STOP) break;
        // board.fetchInfo(query);
        // // cout << '\n';
        board.reset();
    }

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