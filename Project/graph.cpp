#include <cstdint>
#include <cstdio>
#include <queue>

#include "array.hpp"

enum class Color : uint8_t { WHITE, GRAY, BLACK };

class Vertex {
   public:
    Array<Vertex*> neighbors;
    Color color = Color::WHITE;
    int degree = 0;
    uint8_t visited = false;
    void addEdge(Vertex* v) { neighbors[degree++] = v; }
    void resizeNeighbors(int newSize) { neighbors.resize(newSize); }
};

class Graph {
   public:
    int V;
    Array<Vertex> vertices;
    explicit Graph(int V) : V(V), vertices(V) {}
    void addEdge(Vertex* u, Vertex* v) { u->addEdge(v); }

    void BFS(Vertex& start) {
        std::queue<Vertex*> q;
        q.push(&start);
        start.visited = true;
        while (!q.empty()) {
            Vertex* u = q.front();
            q.pop();
            for (int i = 0; i < u->degree; i++) {
                Vertex* v = u->neighbors[i];
                if (!v->visited) {
                    v->visited = true;
                    q.push(v);
                }
            }
        }
    }
};