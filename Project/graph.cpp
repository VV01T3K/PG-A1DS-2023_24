#include <cstdint>
#include <cstdio>

#include "array.hpp"
#include "forwardlist.hpp"
#include "heap.hpp"
enum class Side : uint8_t { NONE, LEFT, RIGHT };
class Vertex {
   public:
    Array<Vertex*> neighbors;
    int index = 0;
    uint16_t color = 0;
    uint16_t visited = 0;
    Side side = Side::NONE;
    uint32_t distance = 0;
    uint32_t component = 0;

    void addEdge(Vertex* v) { neighbors[neighbors.top++] = v; }
    void resizeNeighbors(int newSize) { neighbors.resize(newSize); }

    int degree() const { return neighbors.capacity; }
};

class Graph {
   public:
    uint16_t currentVisit = 0;
    ForwardList<uint32_t> componentsList;
    Array<uint32_t> components;
    bool isBipartite = true;
    uint64_t cyclesOf4 = 0;
    uint64_t V;
    uint64_t doubled_number_of_edges = 0;
    Array<Vertex> vertices;
    explicit Graph(uint64_t V) : V(V), vertices(V) {}

    void bfs(Vertex* start) {
        uint32_t componentSize = 1;
        Array<Vertex*> queue(V);
        int front = 0, back = 0;
        queue[back++] = start;
        start->visited = true;
        start->side = Side::LEFT;
        start->component = componentsList.getSize();
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
                    componentSize++;
                    v->component = componentsList.getSize();
                }
            }
        }
        componentsList.push_back(componentSize);
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

    void eccentricity() {
        currentVisit += 5;
        for (auto& vertex : vertices) {
            currentVisit++;
            const int currentComponent = components[vertex.component];
            Array<Vertex*> queue(V);
            int front = 0, back = 0;
            queue[back++] = &vertex;
            vertex.visited = currentVisit;
            vertex.distance = 0;
            int added = 1;
            while (front < back) {
                Vertex* u = queue[front++];
                for (auto v : u->neighbors) {
                    if (v->visited != currentVisit) {
                        v->visited = currentVisit;
                        queue[back++] = v;
                        v->distance = u->distance + 1;
                        added++;
                    }
                }
                if (added >= currentComponent) break;
            }
            printf("%d ", queue[back - 1]->distance);
        }
        printf("\n");
    }

    void countCyclesOf4() {
        for (auto& vertex : vertices) {
            vertex.visited = false;
            for (int ii = 0; ii < vertex.degree(); ii++) {
                Vertex* u = vertex.neighbors[ii];
                if (!u->visited) continue;

                Array<bool> neighbormatrix(V + 1, false);
                for (auto v : u->neighbors) {
                    if (v->visited) neighbormatrix[v->index] = true;
                }

                for (int jj = ii + 1; jj < vertex.degree(); jj++) {
                    Vertex* v = vertex.neighbors[jj];
                    if (!v->visited) continue;

                    for (auto w : v->neighbors) {
                        if (neighbormatrix[w->index]) cyclesOf4++;
                    }
                }
            }
        }
    }
};