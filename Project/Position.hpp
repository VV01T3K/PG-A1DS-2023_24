#pragma once

#include <cmath>
#include <memory>
#include <stdexcept>
#include <vector>

class Position {
   public:
    Position() : q(0), r(0), s(0) {}
    Position(int q, int r, int s) : q(q), r(r), s(s) {
        if (q + r + s != 0) {
            throw std::invalid_argument("q + r + s must be 0");
        }
    }

    int q, r, s;

    Position operator+(const Position &b) const {
        return Position(q + b.q, r + b.r, s + b.s);
    }

    Position operator-(const Position &b) const {
        return Position(q - b.q, r - b.r, s - b.s);
    }

    Position operator*(int k) const { return Position(q * k, r * k, s * k); }

    Position neighbor(int direction) const {
        return *this + directions[direction];
    }

    std::vector<Position> neighbors() const {
        std::vector<Position> result;
        result.reserve(6);
        for (int i = 0; i < 6; i++) {
            result.push_back(neighbor(i));
        }
        return result;
    }

    int length() const { return (std::abs(q) + std::abs(r) + std::abs(s)) / 2; }

    int distance(const Position &b) const {
        return (std::abs(q - b.q) + std::abs(r - b.r) + std::abs(s - b.s)) / 2;
    }

    static const std::vector<Position> directions;

    static Position direction(int direction) { return directions[direction]; }
};