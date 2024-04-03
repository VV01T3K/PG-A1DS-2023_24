#pragma once

#include <cmath>
#include <vector>

// #include "HexBoard.hpp"
#include "Position.hpp"

enum class Direction { N, NE, SE, S, SW, NW };

class HexBoard;
class Hex {
   public:
    enum class State : char {
        RED = 'r',
        BLUE = 'b',
        EMPTY = 'x',
        UNDEFINED = '.'
    };
    State state = State::UNDEFINED;
    Position position = Position(-1, -1);
    HexBoard& board;
    std::vector<Hex*> neighbors;

    bool visited = false;
    bool blocked = false;

    Hex(HexBoard& board);
    Hex(int q, int r, HexBoard& board);

    int distance(const Hex* other) const;
    int distance(const Hex& other) const;

    Hex* neighbor(Direction direction) const;
    Hex* neighbor(int direct) const;

    std::vector<Hex*> findNeighbors();

    void reset() {
        state = State::UNDEFINED;
        position = Position(-1, -1);
        neighbors.clear();
        visited = false;
        blocked = false;
    }
};