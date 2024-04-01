#pragma once

#include <cmath>

// axial position for hexagonal grid
class Position {
   public:
    Position(int q, int r) : q(q), r(r) {}

    int q;
    int r;

    int length() const {
        return (std::abs(q) + std::abs(r) + std::abs(-q - r)) / 2;
    }

    int distance(const Position& other) const {
        return (std::abs(q - other.q) + std::abs(r - other.r) +
                std::abs(-q - r + other.q + other.r)) /
               2;
    }
};