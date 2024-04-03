#pragma once

#include <vector>

#include "Hex.hpp"
#define INT_MAX 2147483647
class Path {
   public:
    std::vector<Hex*> path;
    int length = INT_MAX;
    int cost = INT_MAX;

    Path() = default;
    Path(std::vector<Hex*> path, int length, int cost)
        : path(path), length(length), cost(cost) {}
    Path(const Path& other) = default;
    Path& operator=(const Path& other) = default;
    ~Path() = default;
};