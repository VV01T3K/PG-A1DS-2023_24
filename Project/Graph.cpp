#include <cstdint>
#include <cstdio>

#include "Array.hpp"

enum class Color : uint8_t { WHITE, GRAY, BLACK };

class Vertex {
   public:
    Array<Vertex*> neighbors;
    Color color = Color::WHITE;
    int degree = 0;
    void addEdge(Vertex* v) { neighbors[degree++] = v; }
    void resizeNeighbors(int newSize) { neighbors.resize(newSize); }
};

class Graph {
   public:
    int V;
    Array<Vertex> vertices;
    explicit Graph(int V) : V(V), vertices(V) {}
    void addEdge(Vertex* u, Vertex* v) { u->addEdge(v); }
};