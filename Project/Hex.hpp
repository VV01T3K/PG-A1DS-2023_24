#pragma once

#include <cmath>

#include "ForwardList.hpp"

enum class Direction { N, NE, SE, S, SW, NW };
enum class Edge { RED_1, RED_2, BLUE_1, BLUE_2, NONE };

class HexBoard;
class Hex {
   public:
    enum class State : char {
        RED = 'r',
        BLUE = 'b',
        EMPTY = 'x',
        UNDEFINED = '.'
    };
    static const Direction best_directions[4][6];
    State state = State::UNDEFINED;
    HexBoard& board;
    ForwardList<Hex*> neighbors;
    int q = -1;
    int r = -1;

    int visited = -1;
    Edge edge = Edge::NONE;
    Edge alt_edge = Edge::NONE;
    bool found_neighbors = false;

    Hex(HexBoard& board);
    Hex(int q, int r, HexBoard& board);

    Hex* neighbor(Direction direction) const;
    Hex* neighbor(int direct) const;

    // ForwardList<Hex*>& findNeighbors();
    ForwardList<Hex*>& findNeighborsEdge(Edge target_edge);

    void reset();
};