#pragma once

#include <cmath>
#include <vector>

#include "Position.hpp"

enum class Direction { N, NE, SE, S, SW, NW };
class Hex {
   public:
    char symbol = 'X';
    Position position;

    Hex(int q, int r) : position(q, r) {}

    int distance(const Hex& other) const {
        return position.distance(other.position);
    }

    std::vector<Hex> neighbors() const {
        return {
            {position.q, position.r - 1},     {position.q + 1, position.r - 1},
            {position.q + 1, position.r},     {position.q, position.r + 1},
            {position.q - 1, position.r + 1}, {position.q - 1, position.r}};
    }

    Hex neighbor(Direction direction) const {
        switch (direction) {
            case Direction::N:
                return {position.q, position.r - 1};
            case Direction::NE:
                return {position.q + 1, position.r - 1};
            case Direction::SE:
                return {position.q + 1, position.r};
            case Direction::S:
                return {position.q, position.r + 1};
            case Direction::SW:
                return {position.q - 1, position.r + 1};
            case Direction::NW:
                return {position.q - 1, position.r};
        }
    }
};