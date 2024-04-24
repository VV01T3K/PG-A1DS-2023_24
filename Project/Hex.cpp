#include "Hex.hpp"

#include "HexBoard.hpp"

Hex::Hex(HexBoard& board) : board(board) {}

Hex* Hex::neighbor(int direct) const {
    Direction direction = static_cast<Direction>(direct);
    return neighbor(direction);
}

Hex* Hex::neighbor(Direction direction) const {
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

// ForwardList<Hex*>& Hex::findNeighbors() {
//     if (found_neighbors) return neighbors;
//     for (int i = 0; i < 6; ++i) {
//         Hex* neighbor_hex = neighbor(i);
//         if (neighbor_hex != nullptr) {
//             neighbors.push_front(neighbor_hex);
//         }
//     }
//     found_neighbors = true;
//     return neighbors;
// }

/**
 * The function `findNeighborsEdge` in C++ finds and returns the neighbors of a
 * Hex towards a specified Edge.
 *
 * @return A reference to a ForwardList of pointers to Hex objects is being
 * returned.
 */
ForwardList<Hex*>& Hex::findNeighborsEdge(Edge target_edge) {
    if (found_neighbors) return neighbors;
    for (int i = 0; i < 6; ++i) {
        Hex* hex = neighbor(best_directions[static_cast<int>(target_edge)][i]);
        if (hex != nullptr) {
            neighbors.push_front(hex);
        }
    }
    found_neighbors = true;
    return neighbors;
}

void Hex::reset() {
    state = State::UNDEFINED;
    neighbors.clear();
    visited = -1;
    edge = Edge::NONE;
    alt_edge = Edge::NONE;
    found_neighbors = false;
    q = -1;
    r = -1;
}

// for recursive dfs
const Direction Hex::best_directions[4][6] = {
    {
        Direction::SE,
        Direction::S,
        Direction::NE,
        Direction::SW,
        Direction::N,
        Direction::NW,
    },
    {
        Direction::NW,
        Direction::N,
        Direction::SW,
        Direction::NE,
        Direction::S,
        Direction::SE,
    },
    {
        Direction::SW,
        Direction::S,
        Direction::NW,
        Direction::SE,
        Direction::N,
        Direction::NE,
    },
    {
        Direction::NE,
        Direction::N,
        Direction::SE,
        Direction::NW,
        Direction::S,
        Direction::SW,
    },

};
// // for iterative dfs
// const Direction Hex::best_directions[4][6] = {
//     {
//         Direction::NW,
//         Direction::N,
//         Direction::SW,
//         Direction::NE,
//         Direction::S,
//         Direction::SE,
//     },
//     {
//         Direction::SE,
//         Direction::S,
//         Direction::NE,
//         Direction::SW,
//         Direction::N,
//         Direction::NW,
//     },
//     {
//         Direction::NE,
//         Direction::N,
//         Direction::SE,
//         Direction::NW,
//         Direction::S,
//         Direction::SW,
//     },
//     {
//         Direction::SW,
//         Direction::S,
//         Direction::NW,
//         Direction::SE,
//         Direction::N,
//         Direction::NE,
//     },
// };