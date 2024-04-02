#pragma once

#include <algorithm>
#include <cmath>
#include <iostream>
#include <queue>
#include <unordered_map>
#include <vector>

#include "Hex.hpp"

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

enum class Player { RED, BLUE };

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
                getHex(tmp_q, tmp_r)->state = tmp[index++];
                getHex(tmp_q, tmp_r)->position.q = tmp_q;
                getHex(tmp_q, tmp_r)->position.r = tmp_r;
                tmp_q++;
                tmp_r--;
            }
            if (i < size - 1)
                r++;
            else
                q++;
        }

        for (int i = 0; i < size; i++) {
            getHex(size - 1, i)->edge = Hex::Edge::RED;
            getHex(0, i)->edge = Hex::Edge::RED;
            getHex(i, size - 1)->edge = Hex::Edge::BLUE;
            getHex(i, 0)->edge = Hex::Edge::BLUE;
        }
        getHex(0, 0)->edge = Hex::Edge::BOTH;
        getHex(size - 1, 0)->edge = Hex::Edge::BOTH;
        getHex(0, size - 1)->edge = Hex::Edge::BOTH;
        getHex(size - 1, size - 1)->edge = Hex::Edge::BOTH;
    }
    std::vector<Hex*> dijkstraShortestPath(Hex* start, Hex* end,
                                           Player player) {
        std::unordered_map<Hex*, Hex*> cameFrom;
        std::unordered_map<Hex*, int> costSoFar;
        std::priority_queue<std::pair<int, Hex*>,
                            std::vector<std::pair<int, Hex*>>, std::greater<>>
            frontier;

        cameFrom[start] = nullptr;
        costSoFar[start] = 0;
        frontier.emplace(0, start);

        while (!frontier.empty()) {
            Hex* current = frontier.top().second;
            frontier.pop();

            if (current == end) {
                break;
            }

            for (Hex* next : current->neighbors()) {
                int newCost = costSoFar[current];
                if ((player == Player::RED && next->state != Hex::State::RED) ||
                    (player == Player::BLUE &&
                     next->state != Hex::State::BLUE)) {
                    newCost += 1;
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
        std::reverse(path.begin(), path.end());

        return path;
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
                if ((red_stones == blue_stones ||
                     red_stones == blue_stones + 1))
                    cout << "YES" << '\n';
                else
                    cout << "NO" << '\n';
                break;
            case Info::IS_GAME_OVER:
                // TODO: Implement this
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