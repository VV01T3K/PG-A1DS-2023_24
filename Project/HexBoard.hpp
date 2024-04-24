#pragma once

#include <cmath>
#include <cstdio>

#include "ForwardList.hpp"
#include "Hex.hpp"
#include "Stack.hpp"
#include "UtilityAlgorithms.hpp"

#define MAX_BOARD_SIZE 11

enum class Info {
    STOP,
    BOARD_SIZE,
    PAWNS_NUMBER,
    IS_BOARD_CORRECT,
    IS_GAME_OVER,
    IS_BOARD_POSSIBLE,
    CAN_RED_WIN_IN_1_MOVE_WITH_NAIVE_OPPONENT,
    CAN_BLUE_WIN_IN_1_MOVE_WITH_NAIVE_OPPONENT,
    CAN_RED_WIN_IN_2_MOVES_WITH_NAIVE_OPPONENT,
    CAN_BLUE_WIN_IN_2_MOVES_WITH_NAIVE_OPPONENT,
    CAN_RED_WIN_IN_1_MOVE_WITH_PERFECT_OPPONENT,
    CAN_BLUE_WIN_IN_1_MOVE_WITH_PERFECT_OPPONENT,
    CAN_RED_WIN_IN_2_MOVES_WITH_PERFECT_OPPONENT,
    CAN_BLUE_WIN_IN_2_MOVES_WITH_PERFECT_OPPONENT,
};

enum class Player { RED, BLUE, NONE };
class HexBoard {
   public:
    HexBoard();
    ~HexBoard();
    void load();
    void fetch(Info info);
    Hex* getHex(int q, int r) const;

   private:
    Hex::State tmp[MAX_BOARD_SIZE * MAX_BOARD_SIZE];
    Hex* hexes[MAX_BOARD_SIZE * MAX_BOARD_SIZE];
    int visit_id = 0;
    int size = 0;
    int red_stones = 0;
    int blue_stones = 0;

    // evaluators
    bool isCorrect();
    bool hasWin(Player player);
    bool isBoardPossible();
    bool canNaivelyWinIn_N(const Player player, const int n);
    bool canNaivelyWinIn_1(const Player player);
    bool canNaivelyWinIn_2(const Player player);
    bool canPerfectlyWinIn_N(const Player player, const int n);
    bool canPerfectlyWinIn_1(const Player player);
    bool canPerfectlyWinIn_2(const Player player);
    bool dfs(Hex* start, Edge end, Hex::State player);
    bool recursiveDfs(Hex* start, Edge end, Hex::State player);
    bool findWiningPath(Player player);
    // -----------
    void readBoardFromInput();
    void reset();
    void setEdges();
    Player whoStarts();
    void placeStone(Hex* hex, Player player);
    void removeStone(Hex* hex, Player player);
    void replaceStone(Hex* hex, Player player);
    void unVisitAll();
};