#pragma once

#include <cmath>
#include <iostream>
#include <memory>
#include <stdexcept>
#include <vector>

#include "Hex.hpp"

class HexBoard {
   public:
    int size;
    std::vector<Hex> hexes;

    HexBoard(int size) : size(size) { hexes.resize(size * size); }

    Hex& hex(int q, int r, int s) {
        if (q + r + s != 0)
            throw std::invalid_argument("Invalid cube coordinates");
        return hexes[q + r * size + s * size * size];
    }

    Hex& hex(const Hex& h) {
        return hex(h.position.q, h.position.r, h.position.s);
    }

    Hex& hex(const Position& p) { return hex(p.q, p.r, p.s); }

    std::vector<Hex> neighbors(const Hex& h) { return h.neighbors(); }

    std::vector<Hex> neighbors(const Position& p) { return hex(p).neighbors(); }

    std::vector<Hex> neighbors(int q, int r, int s) {
        return hex(q, r, s).neighbors();
    }

    void print() {
        int boardDimension = 11;
        for (int i = 0; i < boardDimension; ++i) {
            for (int j = 0; j < boardDimension; ++j) {
                std::cout << hexes[i * boardDimension + j].color << " ";
            }
            std::cout << std::endl;
        }
    }
};