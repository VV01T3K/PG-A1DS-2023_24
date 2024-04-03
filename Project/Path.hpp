#pragma once

#include <forward_list>

#include "Hex.hpp"
#define MAX_INT 10000
class Path {
   public:
    std::forward_list<Hex*> hexes;
    int length = MAX_INT;
    int cost = MAX_INT;

    Path() = default;
    Path(std::forward_list<Hex*> path, int length, int cost)
        : hexes(path), length(length), cost(cost) {}
    Path(const Path& other) = default;
    Path& operator=(const Path& other) = default;
    ~Path(){};
};