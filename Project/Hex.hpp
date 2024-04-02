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
    enum class Edge : char {
        RED = 'r',
        BLUE = 'b',
        BOTH = '.',
        NOT_EDGE = '!',
    };
    State state = State::UNDEFINED;
    Position position;
    HexBoard& board;
    Edge edge = Edge::NOT_EDGE;

    Hex(int q, int r, HexBoard& board);

    int distance(const Hex* other) const;
    int distance(const Hex& other) const;

    Hex* neighbor(Direction direction) const;
    Hex* neighbor(int direct) const;

    std::vector<Hex*> neighbors() const;
};