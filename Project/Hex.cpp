#include "Hex.hpp"

#include "HexBoard.hpp"

Hex::Hex(HexBoard& board) : board(board) {}
Hex::Hex(int q, int r, HexBoard& board) : board(board) {}

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

std::forward_list<Hex*>& Hex::findNeighbors() {
    if (found_neighbors) return neighbors;
    for (int i = 0; i < 6; ++i) {
        Hex* neighbor_hex = neighbor(i);
        if (neighbor_hex != nullptr) {
            neighbors.push_front(neighbor_hex);
        }
    }
    found_neighbors = true;
    return neighbors;
}

std::forward_list<Hex*>& Hex::findNeighborsEdge(Edge target_edge) {
    if (found_neighbors) return neighbors;
    Direction directions[6];
    switch (target_edge) {
        case Edge::RED_1:
            directions[0] = Direction::NW;
            directions[1] = Direction::N;
            directions[2] = Direction::SW;
            directions[3] = Direction::NE;
            directions[4] = Direction::S;
            directions[5] = Direction::SE;
            break;
        case Edge::RED_2:
            directions[0] = Direction::SE;
            directions[1] = Direction::S;
            directions[2] = Direction::NE;
            directions[3] = Direction::SW;
            directions[4] = Direction::N;
            directions[5] = Direction::NW;
            break;
        case Edge::BLUE_1:
            directions[0] = Direction::NE;
            directions[1] = Direction::N;
            directions[2] = Direction::SE;
            directions[3] = Direction::NW;
            directions[4] = Direction::S;
            directions[5] = Direction::SW;
            break;
        case Edge::BLUE_2:
            directions[0] = Direction::SW;
            directions[1] = Direction::S;
            directions[2] = Direction::NW;
            directions[3] = Direction::SE;
            directions[4] = Direction::N;
            directions[5] = Direction::NE;
            break;
    }
    for (int i = 0; i < 6; ++i) {
        Hex* hex = neighbor(directions[i]);
        if (hex != nullptr) {
            neighbors.push_front(hex);
        }
    }
    found_neighbors = true;
    return neighbors;
}