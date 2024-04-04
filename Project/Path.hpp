#pragma once

#include <forward_list>

#include "Hex.hpp"
class Path {
   public:
    std::forward_list<Hex*> hexes;
    int length = 0;

    Path() = default;
    Path(std::forward_list<Hex*> path, int length)
        : hexes(path), length(length) {}
    Path(const Path& other) = default;
    Path& operator=(const Path& other) = default;
    ~Path(){};
};