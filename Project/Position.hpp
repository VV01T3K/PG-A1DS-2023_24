#pragma once

#include <cmath>
#include <cstdint>
#include <vector>

class Position {
   public:
    static const Position directions[6];

    int x, y, z;

    Position(int x, int y, int z) : x(x), y(y), z(z) {}

    Position() : x(0), y(0), z(0) {}

    Position(const Position &p) : x(p.x), y(p.y), z(p.z) {}

    Position &operator=(const Position &p) {
        x = p.x;
        y = p.y;
        z = p.z;
        return *this;
    }
    Position operator+(const Position &p) const {
        return Position(x + p.x, y + p.y, z + p.z);
    }

    // Manhattan distance
    int distance(const Position &p) const {
        return (abs(x - p.x) + abs(y - p.y) + abs(z - p.z)) / 2;
    }
};

enum Direction : uint8_t { N, NE, SE, S, SW, NW };

const Position Position::directions[6] = {
    Position(0, -1, 1), Position(1, -1, 0), Position(1, 0, -1),
    Position(0, 1, -1), Position(-1, 1, 0), Position(-1, 0, 1)};