#include <cstdint>
#include <cstdio>

#include "array.hpp"
#include "heapsort.hpp"
enum class Side : uint8_t { NONE, LEFT, RIGHT };
class Vertex {
   public:
    Array<Vertex*> neighbors;
    int index = 0;
    int degree = 0;
    uint16_t color = 0;
    uint8_t visited = 0;
    Side side = Side::NONE;

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
    uint8_t current_visit = 1;
    bool isBipartite = true;
    uint64_t cyclesOf4 = 0;
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
        s->visited = current_visit;
        s->side = Side::LEFT;
        while (front < back) {
            Vertex* u = queue[front++];
            Side nextSide = (u->side == Side::LEFT) ? Side::RIGHT : Side::LEFT;
            for (auto v : u->neighbors) {
                if (v->side == Side::NONE)
                    v->side = nextSide;
                else if (v->side == u->side)
                    isBipartite = false;
                if (v->visited != current_visit) {
                    v->visited = current_visit;
                    queue[back++] = v;
                }
            }
        }
    }

    void recursivedfs(Vertex* start, Vertex* current, int depth = 1) {
        if (depth == 4) {
            for (auto neighbor : current->neighbors) {
                if (neighbor == start) {
                    cyclesOf4++;
                    break;
                }
            }
            current->visited = 0;
            return;
        }
        current->visited = current_visit;
        for (auto neighbor : current->neighbors) {
            if (!neighbor->visited && neighbor != start) {
                recursivedfs(start, neighbor, depth + 1);
            }
        }
        current->visited = 0;
    }

    uint64_t numOfcomplementEdges() {
        return V * (V - 1) / 2 - doubled_number_of_edges / 2;
    }

    void colorize(Array<Vertex*>& vertices_ref) {
        for (auto vertex : vertices_ref) {
            Array<bool> usedColors(vertex->degree + 2, false);
            for (int i = 0; i < vertex->degree; i++) {
                if (vertex->neighbors[i]->color < vertex->degree + 1)
                    usedColors[vertex->neighbors[i]->color] = true;
            }
            for (int color = 1; color <= vertex->degree + 1; color++) {
                if (!usedColors[color]) {
                    vertex->color = color;
                    break;
                }
            }
        }
    }
};