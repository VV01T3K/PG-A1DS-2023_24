#pragma once

#include <cmath>
#include <cstdio>
#include <vector>

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
    void fetchInfo(Info info) {
        switch (info) {
            case Info::BOARD_SIZE:
                printf("%d\n", size);
                break;
            case Info::PAWNS_NUMBER:
                printf("%d\n", red_stones + blue_stones);
                break;
            case Info::IS_BOARD_CORRECT:
                if (is_correct())
                    printf("YES\n");
                else
                    printf("NO\n");
                break;
            case Info::IS_GAME_OVER:
                if (!is_correct())
                    printf("NO\n");
                else if (has_win(Player::RED)) {
                    printf("YES RED\n");
                } else if (has_win(Player::BLUE)) {
                    printf("YES BLUE\n");
                } else
                    printf("NO\n");
                break;
            case Info::IS_BOARD_POSSIBLE:
                if (!is_correct()) {
                    printf("NO\n");
                    break;
                }

                if (has_win(Player::RED)) {
                    if (red_stones != blue_stones + 1) {
                        printf("NO\n");
                        break;
                    }
                    for (auto hex : red_stones_list) {
                        hex->state = Hex::State::EMPTY;
                        red_stones--;
                        if (!has_win(Player::RED)) {
                            printf("YES\n");
                            hex->state = Hex::State::RED;
                            return;
                        }
                        hex->state = Hex::State::RED;
                        red_stones++;
                    }
                    printf("NO\n");
                    break;
                }

                if (has_win((Player::BLUE))) {
                    if (red_stones != blue_stones) {
                        printf("NO\n");
                        break;
                    }
                    for (auto hex : blue_stones_list) {
                        hex->state = Hex::State::EMPTY;
                        blue_stones--;
                        if (!has_win(Player::BLUE)) {
                            printf("YES\n");
                            hex->state = Hex::State::BLUE;
                            return;
                        }
                        hex->state = Hex::State::BLUE;
                        blue_stones++;
                    }
                    printf("NO\n");
                    break;
                }

                printf("YES\n");
                break;
            case Info::CAN_RED_WIN_IN_1_MOVE_WITH_NAIVE_OPPONENT:
                can_naively_win_in_n(Player::RED, 1) ? printf("YES\n")
                                                     : printf("NO\n");
                break;
            case Info::CAN_BLUE_WIN_IN_1_MOVE_WITH_NAIVE_OPPONENT:
                can_naively_win_in_n(Player::BLUE, 1) ? printf("YES\n")
                                                      : printf("NO\n");
                break;
            case Info::CAN_RED_WIN_IN_2_MOVES_WITH_NAIVE_OPPONENT:
                can_naively_win_in_n(Player::RED, 2) ? printf("YES\n")
                                                     : printf("NO\n");
                break;
            case Info::CAN_BLUE_WIN_IN_2_MOVES_WITH_NAIVE_OPPONENT:
                can_naively_win_in_n(Player::BLUE, 2) ? printf("YES\n")
                                                      : printf("NO\n");
                break;
            case Info::CAN_RED_WIN_IN_1_MOVE_WITH_PERFECT_OPPONENT:
                if (!is_correct())
                    printf("NO\n");
                else if (has_win(Player::RED))
                    printf("NO\n");
                else if (has_win(Player::BLUE))
                    printf("NO\n");
                else if (can_perfectly_win_in_n(Player::RED, 1))
                    printf("YES\n");
                else
                    printf("NO\n");
                break;
            case Info::CAN_BLUE_WIN_IN_1_MOVE_WITH_PERFECT_OPPONENT:
                if (!is_correct())
                    printf("NO\n");
                else if (has_win(Player::RED))
                    printf("NO\n");
                else if (has_win(Player::BLUE))
                    printf("NO\n");
                else if (can_perfectly_win_in_n(Player::BLUE, 1))
                    printf("YES\n");
                else
                    printf("NO\n");
                break;
            case Info::CAN_RED_WIN_IN_2_MOVES_WITH_PERFECT_OPPONENT:
                if (!is_correct())
                    printf("NO\n");
                else if (has_win(Player::RED))
                    printf("NO\n");
                else if (has_win(Player::BLUE))
                    printf("NO\n");
                else if (can_perfectly_win_in_n(Player::RED, 2))
                    printf("YES\n");
                else
                    printf("NO\n");
                break;
            case Info::CAN_BLUE_WIN_IN_2_MOVES_WITH_PERFECT_OPPONENT:
                if (!is_correct())
                    printf("NO\n");
                else if (has_win(Player::RED))
                    printf("NO\n");
                else if (has_win(Player::BLUE))
                    printf("NO\n");
                else if (can_perfectly_win_in_n(Player::BLUE, 2))
                    printf("YES\n");
                else
                    printf("NO\n");
                break;
        }
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
                if (tmp[index] == Hex::State::RED) {
                    red_stones++;
                    red_stones_list.push_front(getHex(tmp_q, tmp_r));
                }
                if (tmp[index] == Hex::State::BLUE) {
                    blue_stones++;
                    blue_stones_list.push_front(getHex(tmp_q, tmp_r));
                }
                Hex* hex = getHex(tmp_q, tmp_r);
                hex->state = tmp[index++];
                hex->position = Position(tmp_q, tmp_r);
                tmp_q++;
                tmp_r--;
            }
            if (i < size - 1)
                r++;
            else
                q++;
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
    Hex::State tmp[MAX_BOARD_SIZE * MAX_BOARD_SIZE];
    ForwardList<Hex*> red_stones_list;
    ForwardList<Hex*> blue_stones_list;
    int visit_id = 0;
    int size = 0;
    Hex* hexes[MAX_BOARD_SIZE * MAX_BOARD_SIZE];
    int red_stones = 0;
    int blue_stones = 0;

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
        red_stones_list.clear();
        blue_stones_list.clear();
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
                if (dfs(hex, Edge::RED_2, Hex::State::RED)) {
                    return true;
                }
            }
        } else {
            for (int i = 0; i < size; i++) {
                Hex* hex = getHex(i, 0);
                if (hex->state != Hex::State::BLUE || hex->visited == visit_id)
                    continue;
                if (dfs(hex, Edge::BLUE_2, Hex::State::BLUE)) {
                    return true;
                }
            }
        }
        return false;
    }

    bool has_win(Player player) {
        if (player == Player::RED && red_stones < size) return false;
        if (player == Player::BLUE && blue_stones < size) return false;
        if (size == 1 && player == Player::RED && red_stones == 1) return true;
        if (findWiningPath(player)) return true;
        return false;
    }

    bool is_correct() {
        if ((red_stones == blue_stones || red_stones == blue_stones + 1))
            return true;
        return false;
    }

    Player who_starts() {
        if (red_stones == blue_stones)
            return Player::RED;
        else
            return Player::BLUE;
    }

    void place_tmp_stone(Hex* hex, Player player) {
        if (player == Player::RED) {
            hex->state = Hex::State::RED;
            red_stones++;
        } else {
            hex->state = Hex::State::BLUE;
            blue_stones++;
        }
    }

    void remove_tmp_stone(Hex* hex, Player player) {
        if (player == Player::RED) {
            hex->state = Hex::State::EMPTY;
            red_stones--;
        } else {
            hex->state = Hex::State::EMPTY;
            blue_stones--;
        }
    }

    void replace_tmp_stone(Hex* hex, Player player) {
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

    bool can_naively_win_in_1(const Player player) {
        const Hex::State player_state =
            player == Player::RED ? Hex::State::RED : Hex::State::BLUE;
        const Hex::State opponent_state =
            player == Player::RED ? Hex::State::BLUE : Hex::State::RED;
        int& stones = player == Player::RED ? red_stones : blue_stones;
        int& opponent_stones = player == Player::RED ? blue_stones : red_stones;

        for (int i = 0; i < size * size; i++) {
            if (hexes[i]->state != Hex::State::EMPTY) continue;
            hexes[i]->state = player_state;
            stones++;
            unVisitAll();
            if (has_win(player)) {
                hexes[i]->state = Hex::State::EMPTY;
                stones--;
                return true;
            }
            hexes[i]->state = Hex::State::EMPTY;
            stones--;
        }
        return false;
    }
    bool can_naively_win_in_2(const Player player) {
        const Hex::State player_state =
            player == Player::RED ? Hex::State::RED : Hex::State::BLUE;
        const Hex::State opponent_state =
            player == Player::RED ? Hex::State::BLUE : Hex::State::RED;
        int& stones = player == Player::RED ? red_stones : blue_stones;
        int& opponent_stones = player == Player::RED ? blue_stones : red_stones;

        for (int i = 0; i < size * size; i++) {
            if (hexes[i]->state != Hex::State::EMPTY) continue;
            hexes[i]->state = player_state;
            stones++;
            if (has_win(player)) {
                hexes[i]->state = Hex::State::EMPTY;
                stones--;
                continue;
            }
            for (int j = 0; j < size * size; j++) {
                if (hexes[j]->state != Hex::State::EMPTY) continue;
                hexes[j]->state = player_state;
                stones++;
                unVisitAll();
                if (has_win(player)) {
                    hexes[j]->state = Hex::State::EMPTY;
                    stones--;
                    hexes[i]->state = Hex::State::EMPTY;
                    stones--;
                    return true;
                }
                hexes[j]->state = Hex::State::EMPTY;
                stones--;
            }
            hexes[i]->state = Hex::State::EMPTY;
            stones--;
        }
        return false;
    }

    bool can_naively_win_in_n(const Player player, const int n) {
        if (!is_correct())
            return false;
        else if (has_win(Player::RED))
            return false;
        else if (has_win(Player::BLUE))
            return false;

        const Hex::State player_state =
            player == Player::RED ? Hex::State::RED : Hex::State::BLUE;
        const Hex::State opponent_state =
            player == Player::RED ? Hex::State::BLUE : Hex::State::RED;
        int& stones = player == Player::RED ? red_stones : blue_stones;
        int& opponent_stones = player == Player::RED ? blue_stones : red_stones;

        if (stones + opponent_stones + n + n / 2 +
                (who_starts() == player ? 0 : 1) >
            size * size)
            return false;
        if (n == 1) return can_naively_win_in_1(player);
        if (n == 2) return can_naively_win_in_2(player);
        return false;
    }
    bool can_perfectly_win_in_n(const Player player, const int n) {
        const Player opponent =
            player == Player::RED ? Player::BLUE : Player::RED;
        const Hex::State player_state =
            player == Player::RED ? Hex::State::RED : Hex::State::BLUE;
        const Hex::State opponent_state =
            player == Player::RED ? Hex::State::BLUE : Hex::State::RED;
        int& stones = player == Player::RED ? red_stones : blue_stones;
        int& opponent_stones = player == Player::RED ? blue_stones : red_stones;
        if (stones + opponent_stones + n + n / 2 +
                (who_starts() == player ? 0 : 1) >
            size * size) {
            return false;
        }
        if (n == 1) {
            if (player == who_starts()) {
                return can_naively_win_in_1(player);
            } else {
                for (int i = 0; i < size * size; i++) {
                    if (hexes[i]->state != Hex::State::EMPTY) continue;
                    place_tmp_stone(hexes[i], player);
                    unVisitAll();
                    if (has_win(player)) {
                        replace_tmp_stone(hexes[i], opponent);
                        if (can_naively_win_in_1(player)) {
                            remove_tmp_stone(hexes[i], opponent);
                            return true;
                        }
                        replace_tmp_stone(hexes[i], player);
                    }
                    remove_tmp_stone(hexes[i], player);
                }
                return false;
            }
        }
        if (n == 2) {
            if (player == who_starts()) {
                for (int i = 0; i < size * size; i++) {
                    if (hexes[i]->state != Hex::State::EMPTY) continue;
                    place_tmp_stone(hexes[i], player);
                    unVisitAll();
                    if (has_win(player)) {
                        remove_tmp_stone(hexes[i], player);
                        continue;
                    }
                    for (int j = 0; j < size * size; j++) {
                        if (hexes[j]->state != Hex::State::EMPTY) continue;
                        place_tmp_stone(hexes[j], player);
                        unVisitAll();
                        if (has_win(player)) {
                            remove_tmp_stone(hexes[j], player);
                            if (can_perfectly_win_in_n(player, 1)) {
                                remove_tmp_stone(hexes[i], player);
                                return true;
                            }
                            place_tmp_stone(hexes[j], player);
                        }
                        remove_tmp_stone(hexes[j], player);
                    }
                    remove_tmp_stone(hexes[i], player);
                }
                return false;
            } else {
                if (can_naively_win_in_1(opponent)) return false;
                if (!can_naively_win_in_2(player)) return false;
                for (int i = 0; i < size * size; i++) {
                    if (hexes[i]->state != Hex::State::EMPTY) continue;
                    place_tmp_stone(hexes[i], opponent);
                    unVisitAll();
                    if (!can_perfectly_win_in_n(player, 2)) {
                        remove_tmp_stone(hexes[i], opponent);
                        return false;
                    }
                    remove_tmp_stone(hexes[i], opponent);
                }
                return true;
            }
        }

        return false;
    }
};