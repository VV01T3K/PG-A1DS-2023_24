#include "Hex.hpp"

#include "HexBoard.hpp"

Hex::Hex(int q, int r, HexBoard& board) : position(q, r), board(board) {}

int Hex::distance(const Hex& other) const {
    return position.distance(other.position);
}

Hex* Hex::neighbor(Direction direction) const {
    int q = position.q;
    int r = position.r;
    switch (direction) {
        case Direction::N:
            return board.getHex(q - 1, r - 1);
        case Direction::S:
            return board.getHex(q + 1, r + 1);
        case Direction::NE:
            return board.getHex(q, r - 1);
        case Direction::SW:
            return board.getHex(q, r + 1);
        case Direction::NW:
            return board.getHex(q - 1, r);
        case Direction::SE:
            return board.getHex(q + 1, r);
    }
    return nullptr;
}

std::vector<Hex*> Hex::neighbors() const {
    std::vector<Hex*> result;
    for (int i = 0; i < 6; ++i) {
        Hex* neighbor_hex = neighbor(static_cast<Direction>(i));
        if (neighbor_hex != nullptr) {
            result.push_back(neighbor_hex);
        }
    }
    return result;
}