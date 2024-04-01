#pragma once

#include <cmath>
#include <memory>
#include <stdexcept>
#include <vector>

class Hex {
   public:
    Hex() : q(0), r(0), s(0) {}
    Hex(int q, int r, int s) : q(q), r(r), s(s) {
        if (q + r + s != 0) {
            throw std::invalid_argument("q + r + s must be 0");
        }
    }

    int q, r, s;

    char color = 'X';

    Hex operator+(const Hex &b) const { return Hex(q + b.q, r + b.r, s + b.s); }

    Hex operator-(const Hex &b) const { return Hex(q - b.q, r - b.r, s - b.s); }

    Hex operator*(int k) const { return Hex(q * k, r * k, s * k); }

    Hex neighbor(int direction) const { return *this + directions[direction]; }

    std::vector<Hex> neighbors() const {
        std::vector<Hex> result;
        result.reserve(6);
        for (int i = 0; i < 6; i++) {
            result.push_back(neighbor(i));
        }
        return result;
    }

    int length() const { return (std::abs(q) + std::abs(r) + std::abs(s)) / 2; }

    int distance(const Hex &b) const {
        return (std::abs(q - b.q) + std::abs(r - b.r) + std::abs(s - b.s)) / 2;
    }

    static const std::vector<Hex> directions;

    static Hex direction(int direction) { return directions[direction]; }
};