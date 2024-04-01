#pragma once

#include <cmath>
#include <vector>

// #include "HexBoard.hpp"
#include "Position.hpp"

enum class Direction { N, NW, NE, S, SW, SE };

class HexBoard;
class Hex {
   public:
    char symbol = 'X';
    Position position;
    HexBoard& board;

    Hex(int q, int r, HexBoard& board);

    int distance(const Hex& other) const;

    Hex* neighbor(Direction direction) const;

    std::vector<Hex*> neighbors() const;
};