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
        setEdges();
    }

    void setEdges() {
        if (size < 1) return;
        for (int i = 1; i < size - 1; i++) {
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

    Path pathDfs(Hex* start, Edge end, Hex::State player,
                 std::forward_list<Hex*>& visited) {
        std::stack<Hex*> stack;
        std::forward_list<Hex*> path;
        stack.push(start);
        visited.push_front(start);
        path.push_front(start);
        start->visited = true;
        int length = 0;
        while (!stack.empty()) {
            Hex* hex = stack.top();
            stack.pop();
            if (hex->state == player &&
                (hex->edge == end || hex->alt_edge == end)) {
                path.push_front(hex);
                for (auto hex : visited) hex->visited = false;
                visited.clear();
                return Path(path, length);
            }
            for (auto neighbor : hex->findNeighbors()) {
                if (neighbor->state != player || neighbor->visited) continue;
                stack.push(neighbor);
                visited.push_front(neighbor);
                neighbor->visited = true;
                length++;
                path.push_front(neighbor);
            }
        }
        for (auto hex : visited) hex->visited = false;
        visited.clear();
        return Path();
    }

    Path findWiningPath(Player player) {
        std::forward_list<Hex*> visited;
        if (player == Player::RED) {
            for (int i = 0; i < size; i++) {
                Hex* hex = getHex(0, i);
                if (hex->state != Hex::State::RED || hex->visited) continue;
                Path path = pathDfs(hex, Edge::RED_2, Hex::State::RED, visited);
                if (path.length != 0) {
                    return path;
                }
                hex = getHex(size - 1, i);
                if (hex->state != Hex::State::RED || hex->visited) continue;
                path = pathDfs(hex, Edge::RED_1, Hex::State::RED, visited);
                if (path.length != 0) {
                    return path;
                }
            }
        } else {
            for (int i = 0; i < size; i++) {
                Hex* hex = getHex(i, 0);
                if (hex->state != Hex::State::BLUE || hex->visited) continue;
                Path path =
                    pathDfs(hex, Edge::BLUE_2, Hex::State::BLUE, visited);
                if (path.length != 0) {
                    return path;
                }
                hex = getHex(i, size - 1);
                if (hex->state != Hex::State::BLUE || hex->visited) continue;
                path = pathDfs(hex, Edge::BLUE_1, Hex::State::BLUE, visited);
                if (path.length != 0) {
                    return path;
                }
            }
        }
        return Path();
    }

    bool has_win(Player player) {
        if (findWiningPath(player).length != 0) return true;
        return false;
    }

    bool is_correct() {
        if ((red_stones == blue_stones || red_stones == blue_stones + 1))
            return true;
        return false;
    }

    void fetchInfo(Info info) {
        Path path;
        switch (info) {
            case Info::BOARD_SIZE:
                std::cout << size << '\n';
                break;
            case Info::PAWNS_NUMBER:
                std::cout << red_stones + blue_stones << '\n';
                break;
            case Info::IS_BOARD_CORRECT:
                if (is_correct())
                    std::cout << "YES\n";
                else
                    std::cout << "NO\n";
                break;
            case Info::IS_GAME_OVER:
                if (!is_correct())
                    std::cout << "NO\n";
                else if (has_win(Player::RED)) {
                    std::cout << "YES RED\n";
                } else if (has_win(Player::BLUE)) {
                    std::cout << "YES BLUE\n";
                } else
                    std::cout << "NO\n";
                break;
            case Info::IS_BOARD_POSSIBLE:
                if (!is_correct()) {
                    std::cout << "NO\n";
                    break;
                }

                path = findWiningPath(Player::RED);
                if (path.length != 0) {  // blue can win
                    if (red_stones != blue_stones + 1) {
                        std::cout << "NO\n";
                        break;
                    }
                    for (auto hex : path.hexes) {
                        hex->state = Hex::State::EMPTY;
                        if (!has_win(Player::RED)) {
                            std::cout << "YES\n";
                            hex->state = Hex::State::RED;
                            return;
                        }
                        hex->state = Hex::State::RED;
                    }
                    std::cout << "NO\n";
                    break;
                }

                path = findWiningPath(Player::BLUE);
                if (path.length != 0) {  // blue can win
                    if (red_stones != blue_stones) {
                        std::cout << "NO\n";
                        break;
                    }
                    for (auto hex : path.hexes) {
                        hex->state = Hex::State::EMPTY;
                        if (!has_win(Player::BLUE)) {
                            std::cout << "YES\n";
                            hex->state = Hex::State::BLUE;
                            return;
                        }
                        hex->state = Hex::State::BLUE;
                    }
                    std::cout << "NO\n";
                    break;
                }

                std::cout << "YES\n";
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