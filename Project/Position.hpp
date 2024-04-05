#pragma once

#include <cmath>

#include "UtilityAlgorithms.hpp"

// axial position for hexagonal grid
class Position {
   public:
    Position(int q, int r) : q(q), r(r) {}

    int q;
    int r;

    int distance(const Position& other) const {
        int diff_q = std::abs(q - other.q);
        int diff_r = std::abs(r - other.r);
        int diff_s = std::abs((q + r) - (other.q + other.r));
        return min(max(diff_q, diff_r), diff_s);
    }
};