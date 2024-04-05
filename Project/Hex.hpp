#pragma once

#include <cmath>
#include <forward_list>

#include "Position.hpp"

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
    State state = State::UNDEFINED;
    Position position = Position(-1, -1);
    HexBoard& board;
    std::forward_list<Hex*> neighbors;

    bool visited = false;
    Edge edge = Edge::NONE;
    Edge alt_edge = Edge::NONE;
    bool found_neighbors = false;

    Hex(HexBoard& board);
    Hex(int q, int r, HexBoard& board);

    int distance(const Hex* other) const;
    int distance(const Hex& other) const;

    Hex* neighbor(Direction direction) const;
    Hex* neighbor(int direct) const;

    std::forward_list<Hex*>& findNeighbors();
    std::forward_list<Hex*>& findNeighborsEdge(Edge target_edge);

    void reset() {
        state = State::UNDEFINED;
        position = Position(-1, -1);
        neighbors.clear();
        visited = false;
        edge = Edge::NONE;
        alt_edge = Edge::NONE;
        found_neighbors = false;
    }
};