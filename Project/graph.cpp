#include <cstdint>
#include <cstdio>

#include "array.hpp"

enum class Color : uint8_t { WHITE, GRAY, BLACK };

class Vertex {
   public:
    Array<Vertex*> neighbors;
    Color color = Color::WHITE;
    int index = 0;
    int degree = 0;
    uint8_t visited = 0;

    void addEdge(Vertex* v) { neighbors[degree++] = v; }
    void resizeNeighbors(int newSize) { neighbors.resize(newSize); }

    void print() {
        for (auto& neighbor : neighbors) {
            printf("%d ", neighbor->index);
        }
        printf("\n");
    }
};

class Graph {
   public:
    int V;
    Array<Vertex> vertices;
    explicit Graph(int V) : V(V), vertices(V) {}
    void addEdge(Vertex* u, Vertex* v) { u->addEdge(v); }

    void print() {
        for (auto& vertex : vertices) {
            vertex.print();
        }
    }

    void bfs(Vertex* s) {
        Array<Vertex*> queue(V);
        int front = 0, back = 0;
        queue[back++] = s;
        s->visited = true;
        while (front < back) {
            Vertex* u = queue[front++];
            for (auto& v : u->neighbors) {
                if (!v->visited) {
                    v->visited = true;
                    queue[back++] = v;
                }
            }
        }
    }
};