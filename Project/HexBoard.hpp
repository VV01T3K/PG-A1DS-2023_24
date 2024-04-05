#pragma once

#include <cmath>
#include <cstdio>
#include <vector>

#include "ArrayStack.hpp"
#include "ForwardList.hpp"
#include "Hex.hpp"
#include "UtilityAlgorithms.hpp"

#define MAX_BOARD_SIZE 11

enum class Info {
    BOARD_SIZE,
    PAWNS_NUMBER,
    IS_BOARD_CORRECT,
    IS_GAME_OVER,
    IS_BOARD_POSSIBLE,
    CAN_RED_WIN_IN_N_MOVE_WITH_NAIVE_OPPONENT,
    CAN_RED_WIN_IN_N_MOVE_WITH_PERFECT_OPPONENT,
    STOP
};

enum class Player { RED, BLUE, NONE };

class HexBoard {
   private:
    Hex::State tmp[MAX_BOARD_SIZE * MAX_BOARD_SIZE];
    ForwardList<Hex*> red_stones_list;
    ForwardList<Hex*> blue_stones_list;
    int visit_id = 0;

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

   public:
    int size = 0;
    Hex* hexes[MAX_BOARD_SIZE * MAX_BOARD_SIZE];
    int red_stones = 0;
    int blue_stones = 0;

    HexBoard() {
        for (int i = 0; i < MAX_BOARD_SIZE * MAX_BOARD_SIZE; i++) {
            hexes[i] = new Hex(*this);
        }
    }
    ~HexBoard() {
        for (auto hex : hexes) {
            delete hex;
        }
    }

    void reset() {
        for (auto hex : hexes) {
            hex->reset();
        }
        size = 0;
        red_stones = 0;
        blue_stones = 0;
        visit_id = 0;
        red_stones_list.clear();
        blue_stones_list.clear();
    }

    Hex* getHex(int q, int r) const {
        if (q < 0 || r < 0 || q >= size || r >= size) {
            return nullptr;
        }
        return hexes[q + r * size];
    }

    void print() const {
        for (int r = 0; r < size; r++) {
            for (int q = 0; q < size; q++) {
                Hex* hex = getHex(q, r);
                if (hex != nullptr) {
                    printf("%c", static_cast<char>(hex->state));
                } else {
                    printf(".");
                }
            }
            printf("\n");
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

    bool pathDfs(Hex* start, Edge end, Hex::State player) {
        ArrayStack<Hex*> stack(player == Hex::State::RED ? red_stones
                                                         : blue_stones);
        stack.push(start);
        start->visited = visit_id;
        while (!stack.empty()) {
            Hex* hex = stack.pop();
            if (hex->state == player &&
                (hex->edge == end || hex->alt_edge == end)) {
                visit_id++;
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
                if (pathDfs(hex, Edge::RED_2, Hex::State::RED)) {
                    return true;
                }
                // hex = getHex(size - 1, i);
                // if (hex->state != Hex::State::RED || hex->visited) continue;
                // if (pathDfs(hex, Edge::RED_1, Hex::State::RED, visited)) {
                //     return true;
                // }
            }
        } else {
            for (int i = 0; i < size; i++) {
                Hex* hex = getHex(i, 0);
                if (hex->state != Hex::State::BLUE || hex->visited == visit_id)
                    continue;
                if (pathDfs(hex, Edge::BLUE_2, Hex::State::BLUE)) {
                    return true;
                }
                // hex = getHex(i, size - 1);
                // if (hex->state != Hex::State::BLUE || hex->visited) continue;
                // if (pathDfs(hex, Edge::BLUE_1, Hex::State::BLUE, visited)) {
                //     return true;
                // }
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
            case Info::CAN_RED_WIN_IN_N_MOVE_WITH_NAIVE_OPPONENT:
                // TODO: Implement this
                break;
            case Info::CAN_RED_WIN_IN_N_MOVE_WITH_PERFECT_OPPONENT:
                // TODO: Implement this
                break;
        }
    }
};