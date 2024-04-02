#pragma once

#include <vector>

#include "Hex.hpp"

class Path {
   public:
    std::vector<Hex*> path;
    int length = 0;
    int cost = 0;

    Path() = default;
    Path(std::vector<Hex*> path, int length, int cost)
        : path(path), length(length), cost(cost) {}
    Path(const Path& other) = default;
    Path& operator=(const Path& other) = default;
    ~Path() = default;
};