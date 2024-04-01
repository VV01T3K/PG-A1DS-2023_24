#pragma once

#include "Position.hpp"

class Hex {
   public:
    Position position;

    Hex(Position position) : position(position) {}

    Hex() : position(Position()) {}

    Hex(const Hex &h) : position(h.position) {}

    Hex &operator=(const Hex &h) {
        position = h.position;
        return *this;
    }

    // Hexagon neighbor
    Hex neighbor(int direction) const {
        return Hex(position + Position::directions[direction]);
    }

    // Hexagon neighbors
    std::vector<Hex> neighbors() const {
        std::vector<Hex> result;
        for (int i = 0; i < 6; i++) {
            result.push_back(neighbor(i));
        }
        return result;
    }

    // Hexagon distance
    int distance(const Hex &h) const { return position.distance(h.position); }
};