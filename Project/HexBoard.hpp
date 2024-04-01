#pragma once

#include <cmath>
#include <iostream>
#include <vector>

#include "Hex.hpp"

#define MAX_BOARD_SIZE 11

class HexBoard {
   private:
    void readBoardFromInput(Hex::State *tmp) {
        int index = 0;
        int width = 0;
        char c;
        while (std::cin.get(c)) {
            if (c == EOF) break;
            if (c == '-' || c == ' ' || c == '>') continue;
            if (c == '<') {
                width++;
                std::cin >> c;
                if (c == '>') c = 'x';
                tmp[index++] = static_cast<Hex::State>(c);
            }
            if (c == '\n') {
                size = std::max(size, width);
                width = 0;
            }
        }
    }

   public:
    int size = 0;
    std::vector<Hex *> hexes;

    HexBoard() {
        hexes.reserve(MAX_BOARD_SIZE * MAX_BOARD_SIZE);
        for (int i = 0; i < MAX_BOARD_SIZE * MAX_BOARD_SIZE; i++) {
            int q = i % MAX_BOARD_SIZE;
            int r = i / MAX_BOARD_SIZE;
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
                    std::cout << static_cast<char>(hex->state);
                } else {
                    std::cout << '.';
                }
            }
            std::cout << std::endl;
        }
    }

    void loadBoard() {
        Hex::State tmp[MAX_BOARD_SIZE * MAX_BOARD_SIZE];
        readBoardFromInput(tmp);
        int index = 0;
        int q = 0;
        int r = 0;
        for (int i = 0; i < 2 * size - 1; i++) {
            int tmp_q = q;
            int tmp_r = r;
            for (int j = 0; j < std::abs(q - r) + 1; j++) {
                getHex(tmp_q, tmp_r)->state = tmp[index++];
                tmp_q++;
                tmp_r--;
            }
            if (i < size - 1)
                r++;
            else
                q++;
        }
    }
};