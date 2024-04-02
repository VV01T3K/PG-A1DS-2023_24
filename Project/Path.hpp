#pragma once

#include <vector>

#include "Hex.hpp"
#define MAX_INT 2000000
class Path {
   public:
    std::vector<Hex*> path;
    int length = MAX_INT;
    int cost = MAX_INT;

    Path() = default;
    Path(std::vector<Hex*> path, int length, int cost)
        : path(path), length(length), cost(cost) {}
    Path(const Path& other) = default;
    Path& operator=(const Path& other) = default;
    ~Path() = default;
};