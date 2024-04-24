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
   private:
    Hex::State tmp[MAX_BOARD_SIZE * MAX_BOARD_SIZE];
    Hex* hexes[MAX_BOARD_SIZE * MAX_BOARD_SIZE];
    int visit_id = 0;
    int size = 0;
    int red_stones = 0;
    int blue_stones = 0;

   public:
    void fetch(Info info) {
        switch (info) {
            case Info::BOARD_SIZE:
                printf("%d\n", size);
                break;
            case Info::PAWNS_NUMBER:
                printf("%d\n", red_stones + blue_stones);
                break;
            case Info::IS_BOARD_CORRECT:
                isCorrect() ? printf("YES\n") : printf("NO\n");
                break;
            case Info::IS_GAME_OVER:
                if (!isCorrect())
                    printf("NO\n");
                else if (hasWin(Player::RED))
                    printf("YES RED\n");
                else if (hasWin(Player::BLUE))
                    printf("YES BLUE\n");
                else
                    printf("NO\n");
                break;
            case Info::IS_BOARD_POSSIBLE:
                isBoardPossible() ? printf("YES\n") : printf("NO\n");
                break;
            case Info::CAN_RED_WIN_IN_1_MOVE_WITH_NAIVE_OPPONENT:
                canNaivelyWinIn_N(Player::RED, 1) ? printf("YES\n")
                                                  : printf("NO\n");
                break;
            case Info::CAN_BLUE_WIN_IN_1_MOVE_WITH_NAIVE_OPPONENT:
                canNaivelyWinIn_N(Player::BLUE, 1) ? printf("YES\n")
                                                   : printf("NO\n");
                break;
            case Info::CAN_RED_WIN_IN_2_MOVES_WITH_NAIVE_OPPONENT:
                canNaivelyWinIn_N(Player::RED, 2) ? printf("YES\n")
                                                  : printf("NO\n");
                break;
            case Info::CAN_BLUE_WIN_IN_2_MOVES_WITH_NAIVE_OPPONENT:
                canNaivelyWinIn_N(Player::BLUE, 2) ? printf("YES\n")
                                                   : printf("NO\n");
                break;
            case Info::CAN_RED_WIN_IN_1_MOVE_WITH_PERFECT_OPPONENT:
                canPerfectlyWinIn_N(Player::RED, 1) ? printf("YES\n")
                                                    : printf("NO\n");
                break;
            case Info::CAN_BLUE_WIN_IN_1_MOVE_WITH_PERFECT_OPPONENT:
                canPerfectlyWinIn_N(Player::BLUE, 1) ? printf("YES\n")
                                                     : printf("NO\n");
                break;
            case Info::CAN_RED_WIN_IN_2_MOVES_WITH_PERFECT_OPPONENT:
                canPerfectlyWinIn_N(Player::RED, 2) ? printf("YES\n")
                                                    : printf("NO\n");
                break;
            case Info::CAN_BLUE_WIN_IN_2_MOVES_WITH_PERFECT_OPPONENT:
                canPerfectlyWinIn_N(Player::BLUE, 2) ? printf("YES\n")
                                                     : printf("NO\n");
                break;
        }
    }

    bool isBoardPossible() {
        if (!isCorrect()) return false;
        for (Player player : {Player::RED, Player::BLUE}) {
            if (hasWin(player)) {
                Hex::State state;
                if (player == Player::RED) {
                    if (red_stones != blue_stones + 1) return false;
                    state = Hex::State::RED;
                } else {
                    if (red_stones != blue_stones) return false;
                    state = Hex::State::BLUE;
                }
                for (int i = 0; i < size * size; i++) {
                    if (hexes[i]->state != state) continue;
                    removeStone(hexes[i], player);
                    if (!hasWin(player)) return true;
                    placeStone(hexes[i], player);
                }
                return false;
            }
        }
        return true;
    }

    void load() {
        reset();
        readBoardFromInput();
        int index = 0;
        int q = 0;
        int r = 0;
        for (int i = 0; i < 2 * size - 1; i++) {
            int tmp_q = q;
            int tmp_r = r;
            for (int j = 0; j < std::abs(q - r) + 1; j++) {
                if (tmp[index] == Hex::State::RED) red_stones++;
                if (tmp[index] == Hex::State::BLUE) blue_stones++;
                Hex* hex = getHex(tmp_q, tmp_r);
                hex->state = tmp[index++];
                hex->q = tmp_q++;
                hex->r = tmp_r--;
            }
            (i < size - 1) ? r++ : q++;
        }
        setEdges();
    }

    HexBoard() {
        for (int i = 0; i < MAX_BOARD_SIZE * MAX_BOARD_SIZE; i++)
            hexes[i] = new Hex(*this);
    }
    ~HexBoard() {
        for (auto hex : hexes) delete hex;
    }

    Hex* getHex(int q, int r) const {
        if (q < 0 || r < 0 || q >= size || r >= size) return nullptr;
        return hexes[q + r * size];
    }

   private:
    void readBoardFromInput() {
        int index = 0;
        char c;
        while (c = getc(stdin)) {
            if (c == EOF || c == -1) break;
            if (c == '<') {
                getc(stdin);
                c = getc(stdin);
                if (c == ' ')
                    tmp[index++] = Hex::State::EMPTY;
                else
                    tmp[index++] = static_cast<Hex::State>(c);
            } else if (c >= 'A' && c <= 'Z') {
                ungetc(c, stdin);
                break;
            }
        }
        size = std::sqrt(index);
    }

    void reset() {
        for (auto hex : hexes) hex->reset();
        size = 0;
        red_stones = 0;
        blue_stones = 0;
        visit_id = 0;
    }

    void setEdges() {
        if (size == 0) return;
        for (int i = 0; i < size; i++) {
            getHex(0, i)->edge = Edge::RED_1;
            getHex(size - 1, i)->edge = Edge::RED_2;
            getHex(i, 0)->edge = Edge::BLUE_1;
            getHex(i, size - 1)->edge = Edge::BLUE_2;
        }
        getHex(0, 0)->alt_edge = Edge::RED_1;
        getHex(0, 0)->edge = Edge::BLUE_1;
        getHex(0, size - 1)->alt_edge = Edge::RED_1;
        getHex(0, size - 1)->edge = Edge::BLUE_2;
        getHex(size - 1, size - 1)->alt_edge = Edge::RED_2;
        getHex(size - 1, size - 1)->edge = Edge::BLUE_2;
        getHex(size - 1, 0)->alt_edge = Edge::RED_2;
        getHex(size - 1, 0)->edge = Edge::BLUE_1;
    }

    bool dfs(Hex* start, Edge end, Hex::State player) {
        Stack<Hex*> stack(player == Hex::State::RED ? red_stones : blue_stones);
        stack.push(start);
        start->visited = visit_id;
        while (!stack.empty()) {
            Hex* hex = stack.pop();
            if (hex->state == player &&
                (hex->edge == end || hex->alt_edge == end)) {
                unVisitAll();
                return true;
            }
            for (auto neighbor : hex->findNeighborsEdge(end)) {
                if (neighbor->state != player || neighbor->visited == visit_id)
                    continue;
                stack.push(neighbor);
                neighbor->visited = visit_id;
            }
        }
        return false;
    }

    bool findWiningPath(Player player) {
        if (player == Player::RED) {
            for (int i = 0; i < size; i++) {
                Hex* hex = getHex(0, i);
                if (hex->state != Hex::State::RED || hex->visited == visit_id)
                    continue;
                if (dfs(hex, Edge::RED_2, Hex::State::RED)) return true;
            }
        } else {
            for (int i = 0; i < size; i++) {
                Hex* hex = getHex(i, 0);
                if (hex->state != Hex::State::BLUE || hex->visited == visit_id)
                    continue;
                if (dfs(hex, Edge::BLUE_2, Hex::State::BLUE)) return true;
            }
        }
        return false;
    }

    bool hasWin(Player player) {
        if (player == Player::RED && red_stones < size) return false;
        if (player == Player::BLUE && blue_stones < size) return false;
        if (size == 1 && player == Player::RED && red_stones == 1) return true;
        if (findWiningPath(player)) return true;
        return false;
    }

    bool isCorrect() {
        if ((red_stones == blue_stones || red_stones == blue_stones + 1))
            return true;
        return false;
    }

    Player whoStarts() {
        if (red_stones == blue_stones)
            return Player::RED;
        else
            return Player::BLUE;
    }

    void placeStone(Hex* hex, Player player) {
        if (player == Player::RED) {
            hex->state = Hex::State::RED;
            red_stones++;
        } else {
            hex->state = Hex::State::BLUE;
            blue_stones++;
        }
    }

    void removeStone(Hex* hex, Player player) {
        if (player == Player::RED) {
            hex->state = Hex::State::EMPTY;
            red_stones--;
        } else {
            hex->state = Hex::State::EMPTY;
            blue_stones--;
        }
    }

    void replaceStone(Hex* hex, Player player) {
        if (player == Player::RED) {
            hex->state = Hex::State::RED;
            red_stones++;
            blue_stones--;
        } else {
            hex->state = Hex::State::BLUE;
            blue_stones++;
            red_stones--;
        }
    }

    void unVisitAll() { visit_id++; }

    bool canNaivelyWinIn_1(const Player player) {
        for (int i = 0; i < size * size; i++) {
            if (hexes[i]->state != Hex::State::EMPTY) continue;
            placeStone(hexes[i], player);
            unVisitAll();
            if (hasWin(player)) {
                removeStone(hexes[i], player);
                return true;
            }
            removeStone(hexes[i], player);
        }
        return false;
    }
    bool canNaivelyWinIn_2(const Player player) {
        for (int i = 0; i < size * size; i++) {
            if (hexes[i]->state != Hex::State::EMPTY) continue;
            placeStone(hexes[i], player);
            if (hasWin(player)) {
                removeStone(hexes[i], player);
                continue;
            }
            for (int j = 0; j < size * size; j++) {
                if (hexes[j]->state != Hex::State::EMPTY) continue;
                placeStone(hexes[j], player);
                unVisitAll();
                if (hasWin(player)) {
                    removeStone(hexes[i], player);
                    removeStone(hexes[j], player);
                    return true;
                }
                removeStone(hexes[j], player);
            }
            removeStone(hexes[i], player);
        }
        return false;
    }

    bool canNaivelyWinIn_N(const Player player, const int n) {
        if (!isCorrect()) return false;
        if (hasWin(Player::RED)) return false;
        if (hasWin(Player::BLUE)) return false;
        if (red_stones + blue_stones + n + n / 2 +
                (whoStarts() == player ? 0 : 1) >
            size * size)
            return false;
        if (n == 1) return canNaivelyWinIn_1(player);
        if (n == 2) return canNaivelyWinIn_2(player);
        return false;
    }

    bool canPerfectlyWinIn_1(const Player player) {
        const Player opponent =
            player == Player::RED ? Player::BLUE : Player::RED;
        if (player == whoStarts()) {
            return canNaivelyWinIn_1(player);
        } else {
            for (int i = 0; i < size * size; i++) {
                if (hexes[i]->state != Hex::State::EMPTY) continue;
                placeStone(hexes[i], player);
                unVisitAll();
                if (hasWin(player)) {
                    replaceStone(hexes[i], opponent);
                    if (canNaivelyWinIn_1(player)) {
                        removeStone(hexes[i], opponent);
                        return true;
                    }
                    replaceStone(hexes[i], player);
                }
                removeStone(hexes[i], player);
            }
        }
        return false;
    }
    bool canPerfectlyWinIn_2(const Player player) {
        const Player opponent =
            player == Player::RED ? Player::BLUE : Player::RED;
        if (player == whoStarts()) {
            for (int i = 0; i < size * size; i++) {
                if (hexes[i]->state != Hex::State::EMPTY) continue;
                placeStone(hexes[i], player);
                unVisitAll();
                if (hasWin(player)) {
                    removeStone(hexes[i], player);
                    continue;
                }
                for (int j = 0; j < size * size; j++) {
                    if (hexes[j]->state != Hex::State::EMPTY) continue;
                    placeStone(hexes[j], player);
                    unVisitAll();
                    if (hasWin(player)) {
                        removeStone(hexes[j], player);
                        if (canPerfectlyWinIn_1(player)) {
                            removeStone(hexes[i], player);
                            return true;
                        }
                        placeStone(hexes[j], player);
                    }
                    removeStone(hexes[j], player);
                }
                removeStone(hexes[i], player);
            }
            return false;
        } else {
            if (canNaivelyWinIn_1(opponent)) return false;
            if (!canNaivelyWinIn_2(player)) return false;
            for (int i = 0; i < size * size; i++) {
                if (hexes[i]->state != Hex::State::EMPTY) continue;
                placeStone(hexes[i], opponent);
                unVisitAll();
                if (!canPerfectlyWinIn_2(player)) {
                    removeStone(hexes[i], opponent);
                    return false;
                }
                removeStone(hexes[i], opponent);
            }
            return true;
        }
        return false;
    }

    bool canPerfectlyWinIn_N(const Player player, const int n) {
        if (!isCorrect()) return false;
        if (hasWin(Player::RED)) return false;
        if (hasWin(Player::BLUE)) return false;
        if (red_stones + blue_stones + n + n / 2 +
                (whoStarts() == player ? 0 : 1) >
            size * size)
            return false;
        if (n == 1) return canPerfectlyWinIn_1(player);
        if (n == 2) return canPerfectlyWinIn_2(player);

        return false;
    }
};