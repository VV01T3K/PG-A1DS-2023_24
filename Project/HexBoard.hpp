#pragma once

#include <cmath>
#include <iostream>
#include <vector>

#include "Hex.hpp"

class HexBoard {
   public:
    int size;
    std::vector<Hex *> hexes;

    HexBoard(int size) : size(size) {
        hexes.reserve(size * size);
        for (int i = 0; i < size * size; i++) {
            int q = i % size;
            int r = i / size;
            hexes.push_back(new Hex(q, r, *this));
        }
    }
    ~HexBoard() {
        for (auto hex : hexes) {
            delete hex;
        }
    }

    Hex *getHex(int q, int r) const {
        if (q < 0 || r < 0 || q >= size || r >= size) {
            return nullptr;
        }
        return hexes[q + r * size];
    }

    void print() const {
        for (int r = 0; r < size; r++) {
            for (int q = 0; q < size; q++) {
                Hex *hex = getHex(q, r);
                if (hex != nullptr) {
                    std::cout << hex->symbol;
                } else {
                    std::cout << '.';
                }
            }
            std::cout << std::endl;
        }
    }
};