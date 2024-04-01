#pragma once

#include <cmath>
#include <memory>
#include <stdexcept>
#include <vector>

#include "Hex.hpp"

class HexBoard {
   public:
    HexBoard(int size) : size(size) {
        if (size < 1) {
            throw std::invalid_argument("invalid board size");
        }
        hexes.resize(size * size);
    }

    int size;

    std::vector<Hex> hexes;

    Hex &hex(int q, int r, int s) { return hexes[q + r * size]; }

    Hex &hex(const Hex &h) { return hexes[h.q + h.r * size]; }

    const Hex &hex(int q, int r, int s) const { return hexes[q + r * size]; }

    const Hex &hex(const Hex &h) const { return hexes[h.q + h.r * size]; }

    bool is_valid(const Hex &h) const {
        return 0 <= h.q && h.q < size && 0 <= h.r && h.r < size;
    }

    bool is_valid(int q, int r, int s) const {
        return 0 <= q && q < size && 0 <= r && r < size;
    }

    std::vector<Hex> neighbors(const Hex &h) const {
        std::vector<Hex> result;
        result.reserve(6);
        for (int i = 0; i < 6; i++) {
            Hex neighbor = h + Hex::direction(i);
            if (is_valid(neighbor)) {
                result.push_back(neighbor);
            }
        }
        return result;
    }

    std::vector<Hex> neighbors(int q, int r, int s) const {
        return neighbors(Hex(q, r, s));
    }
};