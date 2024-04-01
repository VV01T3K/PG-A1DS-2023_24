#include "Position.hpp"

class Hex {
   public:
    Position position;
    char color = 'X';

    Hex() : position(0, 0, 0) {}
    Hex(int q, int r, int s) : position(q, r, s) {
        if (position.q + position.r + position.s != 0) {
            throw std::invalid_argument("q + r + s must be 0");
        }
    }

    Hex operator+(const Hex &b) const {
        return Hex(position.q + b.position.q, position.r + b.position.r,
                   position.s + b.position.s);
    }
    Hex operator-(const Hex &b) const {
        return Hex(position.q - b.position.q, position.r - b.position.r,
                   position.s - b.position.s);
    }
    Hex operator*(int k) const {
        return Hex(position.q * k, position.r * k, position.s * k);
    }

    Hex neighbor(int direction) const { return *this + directions[direction]; }

    std::vector<Hex> neighbors() const {
        std::vector<Hex> result;
        result.reserve(6);
        for (int i = 0; i < 6; i++) {
            result.push_back(neighbor(i));
        }
        return result;
    }

    int length() const {
        return (std::abs(position.q) + std::abs(position.r) +
                std::abs(position.s)) /
               2;
    }

    int distance(const Hex &b) const {
        return (std::abs(position.q - b.position.q) +
                std::abs(position.r - b.position.r) +
                std::abs(position.s - b.position.s)) /
               2;
    }

    static const std::vector<Hex> directions;

    static Hex direction(int direction) { return directions[direction]; }
};