#include "Hex.hpp"

#include "HexBoard.hpp"

int Hex::distance(const Hex& other) const {
    return position.distance(other.position);
}
int Hex::distance(const Hex* other) const {
    return position.distance(other->position);
}

Hex* Hex::neighbor(int direct) const {
    Direction direction = static_cast<Direction>(direct);
    return neighbor(direction);
}

Hex* Hex::neighbor(Direction direction) const {
    int q = position.q;
    int r = position.r;
    switch (direction) {
        case Direction::N:
            return board->getHex(q - 1, r - 1);
        case Direction::S:
            return board->getHex(q + 1, r + 1);
        case Direction::NE:
            return board->getHex(q, r - 1);
        case Direction::SW:
            return board->getHex(q, r + 1);
        case Direction::NW:
            return board->getHex(q - 1, r);
        case Direction::SE:
            return board->getHex(q + 1, r);
    }
    return nullptr;
}

std::vector<Hex*> Hex::findNeighbors() {
    if (!neighbors.empty()) return neighbors;
    for (int i = 0; i < 6; ++i) {
        Hex* neighbor_hex = neighbor(i);
        if (neighbor_hex != nullptr && (neighbor_hex->state == State::EMPTY ||
                                        neighbor_hex->state == state)) {
            neighbors.push_back(neighbor_hex);
        }
    }
    return neighbors;
}

std::vector<Hex*> Hex::findAllyNeighbors() {
    if (!ally_neighbors.empty()) return ally_neighbors;
    for (int i = 0; i < 6; ++i) {
        Hex* neighbor_hex = neighbor(i);
        if (neighbor_hex != nullptr && neighbor_hex->state == state) {
            ally_neighbors.push_back(neighbor_hex);
        }
    }
    return ally_neighbors;
}