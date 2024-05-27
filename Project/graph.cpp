#include <algorithm>
#include <cstdint>
#include <cstdio>

#include "array.hpp"
#include "heap.hpp"
enum class Side : uint8_t { NONE, LEFT, RIGHT };
class Vertex {
   public:
    Array<Vertex*> neighbors;
    int index = 0;
    uint16_t color = 0;
    bool visited = 0;
    Side side = Side::NONE;

    void addEdge(Vertex* v) { neighbors[neighbors.top++] = v; }
    void resizeNeighbors(int newSize) { neighbors.resize(newSize); }

    int degree() const { return neighbors.capacity; }

    void print() const {
        for (auto& neighbor : neighbors) {
            printf("%d ", neighbor->index);
        }
        printf("\n");
    }
};

class Graph {
   public:
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
        s->visited = true;
        s->side = Side::LEFT;
        while (front < back) {
            Vertex* u = queue[front++];
            Side nextSide = (u->side == Side::LEFT) ? Side::RIGHT : Side::LEFT;
            for (auto v : u->neighbors) {
                if (v->side == Side::NONE)
                    v->side = nextSide;
                else if (v->side == u->side)
                    isBipartite = false;
                if (!v->visited) {
                    v->visited = true;
                    queue[back++] = v;
                }
            }
        }
    }

    void countCyclesOf4() {
        for (auto& vertex : vertices) {
            vertex.visited = false;
            for (int ii = 0; ii < vertex.degree(); ii++) {
                Vertex* u = vertex.neighbors[ii];
                if (!u->visited) continue;
                for (int jj = ii + 1; jj < vertex.degree(); jj++) {
                    Vertex* v = vertex.neighbors[jj];
                    if (!v->visited) continue;

                    for (int kk = 0; kk < u->degree(); kk++) {
                        Vertex* w = u->neighbors[kk];
                        if (!w->visited) continue;
                        for (int ll = 0; ll < v->degree(); ll++) {
                            Vertex* x = v->neighbors[ll];
                            if (!x->visited) continue;
                            if (w == x) cyclesOf4++;
                        }
                    }
                }
            }
        }
    }

    uint64_t numOfcomplementEdges() {
        return V * (V - 1) / 2 - doubled_number_of_edges / 2;
    }

    void colorize(Array<Vertex*>& vertices_ref) {
        for (auto vertex : vertices_ref) {
            Array<bool> usedColors(vertex->degree() + 2, false);
            for (int i = 0; i < vertex->degree(); i++) {
                if (vertex->neighbors[i]->color < vertex->degree() + 1)
                    usedColors[vertex->neighbors[i]->color] = true;
            }
            for (int color = 1; color <= vertex->degree() + 1; color++) {
                if (!usedColors[color]) {
                    vertex->color = color;
                    break;
                }
            }
        }
    }
};