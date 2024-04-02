#pragma once

#include <algorithm>
#include <cmath>
#include <iostream>
#include <queue>
#include <unordered_map>
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
    void readBoardFromInput(Hex::State* tmp) {
        int index = 0;
        int width = 0;
        char c;
        while (std::cin.get(c)) {
            if (c == EOF) break;
            if (c == '-' || c == ' ' || c == '>') continue;
            if (c == '<') {
                width++;
                std::cin >> c;
                if (c == '>') c = 'x';
                tmp[index++] = static_cast<Hex::State>(c);
            }
            if (c == '\n') {
                size = std::max(size, width);
                width = 0;
            }
            if (c >= 'A' && c <= 'B') break;
        }
    }

   public:
    int size = 0;
    std::vector<Hex*> hexes;
    int red_stones = 0;
    int blue_stones = 0;
    std::vector<Hex*> red_edge_1;
    std::vector<Hex*> red_edge_2;
    std::vector<Hex*> blue_edge_1;
    std::vector<Hex*> blue_edge_2;
    // Player won = Player::NONE;

    HexBoard() {
        hexes.reserve(MAX_BOARD_SIZE * MAX_BOARD_SIZE);
        for (int i = 0; i < MAX_BOARD_SIZE * MAX_BOARD_SIZE; i++) {
            hexes.push_back(new Hex(-1, -1, *this));
        }
    }
    ~HexBoard() {
        for (auto hex : hexes) {
            delete hex;
        }
    }

    void reset() {
        for (auto hex : hexes) {
            hex->state = Hex::State::UNDEFINED;
            hex->position = Position(-1, -1);
        }
        hexes.clear();
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
        Hex::State tmp[MAX_BOARD_SIZE * MAX_BOARD_SIZE];
        readBoardFromInput(tmp);
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
    Path shortestPath(Hex* start, Hex* end, Hex::State player) {
        // TODO if found path with 0 cost return immediately
        // TODO use less data structures
        // TODO oparate on Path and not on vactor + int
        std::unordered_map<Hex*, Hex*> cameFrom;
        std::unordered_map<Hex*, int> costSoFar;
        std::priority_queue<std::pair<int, Hex*>,
                            std::vector<std::pair<int, Hex*>>, std::greater<>>
            frontier;

        cameFrom[start] = nullptr;
        costSoFar[start] = 0;
        frontier.emplace(0, start);

        if (player == Hex::State::RED && start->state == Hex::State::BLUE) {
            return Path({}, 10000, 10000);
        }
        if (player == Hex::State::BLUE && start->state == Hex::State::RED) {
            return Path({}, 10000, 10000);
        }
        if (player == Hex::State::RED && end->state == Hex::State::BLUE) {
            return Path({}, 10000, 10000);
        }
        if (player == Hex::State::BLUE && end->state == Hex::State::RED) {
            return Path({}, 10000, 10000);
        }
        if (start->state != player) costSoFar[start] = 1;

        while (!frontier.empty()) {
            Hex* current = frontier.top().second;
            frontier.pop();

            if (current == end) {
                break;
            }

            for (Hex* next : current->neighbors()) {
                int newCost = costSoFar[current];
                if (next->state == Hex::State::EMPTY) {
                    newCost += 1;
                } else if (next->state == player) {
                    newCost += 0;
                } else {
                    continue;
                }

                if (!costSoFar.count(next) || newCost < costSoFar[next]) {
                    costSoFar[next] = newCost;
                    int priority = newCost + next->distance(end);
                    frontier.emplace(priority, next);
                    cameFrom[next] = current;
                }
            }
        }

        std::vector<Hex*> path;
        for (Hex* hex = end; hex != nullptr; hex = cameFrom[hex]) {
            path.push_back(hex);
        }

        int length = path.size();
        int cost = costSoFar[end];

        return Path(path, length, cost);
    }

    Path findShortestPathToConectEdges(Player player) {
        Path path;
        if (player == Player::RED) {
            for (auto hex : red_edge_1) {
                for (auto hex2 : red_edge_2) {
                    Path tmp = shortestPath(hex, hex2, Hex::State::RED);
                    if (tmp.cost == 0) return tmp;
                    if (tmp.cost < path.cost) path = tmp;
                }
            }
        } else {
            for (auto hex : blue_edge_1) {
                for (auto hex2 : blue_edge_2) {
                    Path tmp = shortestPath(hex, hex2, Hex::State::BLUE);
                    if (tmp.cost == 0) return tmp;
                    if (tmp.cost < path.cost) path = tmp;
                }
            }
        }
        return path;
    }

    bool is_correct() {
        if ((red_stones == blue_stones || red_stones == blue_stones + 1))
            return true;
        return false;
    }

    void fetchInfo(Info info) {
        using namespace std;
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
                if (!is_correct()) {
                    cout << "NO" << '\n';
                    break;
                }
                if (findShortestPathToConectEdges(Player::RED).cost == 0) {
                    cout << "YES RED" << '\n';
                    break;
                }
                if (findShortestPathToConectEdges(Player::BLUE).cost == 0) {
                    cout << "YES BLUE" << '\n';
                    break;
                }
                cout << "NO" << '\n';
                break;
            case Info::IS_BOARD_POSSIBLE:
                // TODO: Implement this
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