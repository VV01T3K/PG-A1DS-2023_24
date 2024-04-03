#pragma once

#include <cmath>
#include <forward_list>
#include <iostream>
#include <stack>
#include <vector>

#include "Hex.hpp"
#include "Path.hpp"

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
    void readBoardFromInput() {
        int index = 0;
        char c;
        while (std::cin.get(c)) {
            if (c == EOF) break;
            if (c == '-' || c == ' ' || c == '>') continue;
            if (c == '<') {
                std::cin >> c;
                if (c == '>') c = 'x';
                tmp[index++] = static_cast<Hex::State>(c);
            }
            if (c >= 'A' && c <= 'B') break;
        }
        size = std::sqrt(index);
    }

   public:
    int size = 0;
    Hex* hexes[MAX_BOARD_SIZE * MAX_BOARD_SIZE];
    int red_stones = 0;
    int blue_stones = 0;
    std::vector<Hex*> red_edge_1;
    std::vector<Hex*> red_edge_2;
    std::vector<Hex*> blue_edge_1;
    std::vector<Hex*> blue_edge_2;
    // Player won = Player::NONE;

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
        red_edge_1.clear();
        red_edge_2.clear();
        blue_edge_1.clear();
        blue_edge_2.clear();
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
                    std::cout << static_cast<char>(hex->state);
                } else {
                    std::cout << '.';
                }
            }
            std::cout << '\n';
        }
    }

    void load() {
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
                hex->position = Position(tmp_q, tmp_r);
                tmp_q++;
                tmp_r--;
            }
            if (i < size - 1)
                r++;
            else
                q++;
        }
        for (int i = 0; i < size; i++) {
            red_edge_1.push_back(getHex(0, i));
            red_edge_2.push_back(getHex(size - 1, i));
            blue_edge_1.push_back(getHex(i, 0));
            blue_edge_2.push_back(getHex(i, size - 1));
        }
    }

    void unVisitAll() {
        for (int r = 0; r < size; r++) {
            for (int q = 0; q < size; q++) {
                getHex(q, r)->visited = false;
            }
        }
    }

    Path pathDfs(Hex* start, Hex* end, Hex::State player) {
        unVisitAll();
        std::forward_list<Hex*> stack;
        std::forward_list<Hex*> path;
        int length = 0;
        stack.push_front(start);
        while (!stack.empty()) {
            Hex* current = stack.front();
            stack.pop_front();
            current->visited = true;
            path.push_front(current);
            length++;
            if (current == end) {
                return Path(path, length, 0);
            }
            std::vector<Hex*> neighbors = current->findNeighbors();
            std::sort(neighbors.begin(), neighbors.end(),
                      [end](Hex* a, Hex* b) {
                          return a->distance(end) < b->distance(end);
                      });
            bool hasUnvisitedNeighbor = false;
            for (auto neighbor : neighbors) {
                if (neighbor->state == player && !neighbor->visited) {
                    stack.push_front(neighbor);
                    hasUnvisitedNeighbor = true;
                }
            }
            if (!hasUnvisitedNeighbor) {
                path.pop_front();
                length--;
            }
        }
        return Path();
    }

    Path findWiningPath(Player player) {
        if (player == Player::RED) {
            for (auto hex1 : red_edge_1) {
                if (hex1->state != Hex::State::RED) continue;
                if (hex1->blocked) continue;
                for (auto hex2 : red_edge_2) {
                    if (hex2->state != Hex::State::RED) continue;
                    if (hex2->blocked) continue;
                    Path path = pathDfs(hex1, hex2, Hex::State::RED);
                    if (path.length != MAX_INT) {
                        return path;
                    }
                }
            }
        } else {
            for (auto hex1 : blue_edge_1) {
                if (hex1->state != Hex::State::BLUE) continue;
                if (hex1->blocked) continue;
                for (auto hex2 : blue_edge_2) {
                    if (hex2->state != Hex::State::BLUE) continue;
                    if (hex2->blocked) continue;
                    Path path = pathDfs(hex1, hex2, Hex::State::BLUE);
                    if (path.length != MAX_INT) {
                        return path;
                    }
                }
            }
        }
        return Path();
    }

    bool has_win(Player player) {
        Path path = findWiningPath(player);
        if (path.length != MAX_INT) return true;
        return false;
    }

    bool is_correct() {
        if ((red_stones == blue_stones || red_stones == blue_stones + 1))
            return true;
        return false;
    }

    void fetchInfo(Info info) {
        using namespace std;
        Path path;
        switch (info) {
            case Info::BOARD_SIZE:
                cout << size << '\n';
                break;
            case Info::PAWNS_NUMBER:
                cout << red_stones + blue_stones << '\n';
                break;
            case Info::IS_BOARD_CORRECT:
                if (is_correct())
                    cout << "YES" << '\n';
                else
                    cout << "NO" << '\n';
                break;
            case Info::IS_GAME_OVER:
                if (!is_correct())
                    cout << "NO" << '\n';
                else if (has_win(Player::RED)) {
                    cout << "YES RED" << '\n';
                } else if (has_win(Player::BLUE)) {
                    cout << "YES BLUE" << '\n';
                } else
                    cout << "NO" << '\n';
                break;
            case Info::IS_BOARD_POSSIBLE:
                if (!is_correct()) {
                    cout << "NO" << '\n';
                    break;
                }
                if (red_stones != blue_stones + 1 && has_win(Player::RED)) {
                    cout << "NO" << '\n';
                    break;
                }
                if (red_stones != blue_stones && has_win(Player::BLUE)) {
                    cout << "NO" << '\n';
                    break;
                }
                if (has_win(Player::RED)) {
                    for (int r = 0; r < size; r++) {
                        for (int q = 0; q < size; q++) {
                            Hex* hex = getHex(q, r);
                            if (hex->state == Hex::State::RED) {
                                hex->blocked = true;
                                if (!has_win(Player::RED)) {
                                    cout << "YES" << '\n';
                                    return;
                                }
                                hex->blocked = false;
                            }
                        }
                    }
                    cout << "NO" << '\n';
                    break;
                }
                if (has_win(Player::BLUE)) {
                    for (int r = 0; r < size; r++) {
                        for (int q = 0; q < size; q++) {
                            Hex* hex = getHex(q, r);
                            if (hex->state == Hex::State::BLUE) {
                                hex->blocked = true;
                                if (!has_win(Player::BLUE)) {
                                    cout << "YES" << '\n';
                                    return;
                                }
                                hex->blocked = false;
                            }
                        }
                    }
                    cout << "NO" << '\n';
                    break;
                }
                cout << "YES" << '\n';
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