#include <cstdint>
#include <cstdio>
#include <vector>

#include "array.hpp"
#include "heapsort.hpp"

class Vertex {
   public:
    Array<Vertex*> neighbors;
    int color = 0;
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
    uint64_t V;
    uint64_t doubled_number_of_edges = 0;
    Array<Vertex> vertices;
    explicit Graph(uint64_t V) : V(V), vertices(V) {}
    void addEdge(Vertex* u, Vertex* v) {
        u->addEdge(v);
        doubled_number_of_edges++;
    }

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
    uint64_t numOfcomplementEdges() {
        return V * (V - 1) / 2 - doubled_number_of_edges / 2;
    }

    void colorize() {
        for (auto& vertex : vertices) {
            Array<bool> usedColors(vertex.degree + 2, false);
            for (int i = 0; i < vertex.degree; i++) {
                if (vertex.neighbors[i]->color < vertex.degree + 1)
                    usedColors[vertex.neighbors[i]->color] = true;
            }
            for (int color = 1; color <= vertex.degree + 1; color++) {
                if (!usedColors[color]) {
                    vertex.color = color;
                    break;
                }
            }
        }
    }
};