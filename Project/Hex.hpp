#pragma once

#include <cmath>
#include <vector>

// #include "HexBoard.hpp"
#include "Position.hpp"

enum class Direction { N, NE, SE, S, SW, NW };

class HexBoard;
class Hex {
   public:
    char symbol = 129;
    Position position;
    HexBoard& board;

    Hex(int q, int r, HexBoard& board);

    int distance(const Hex& other) const;

    Hex* neighbor(Direction direction) const;
    Hex* neighbor(int direct) const;

    std::vector<Hex*> neighbors() const;
};