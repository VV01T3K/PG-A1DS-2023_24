#include <cstdint>
#include <cstdio>

#include "array.hpp"
#include "forwardlist.hpp"
#include "heap.hpp"
enum class Side : uint8_t { NONE, LEFT, RIGHT };
class Vertex {
   public:
    Array<Vertex*> neighbors;
    Array<int> neighborsIndex;
    int index = 0;
    uint16_t color = 0;
    uint16_t visited = 0;
    uint32_t distance = 0;
    uint32_t component = 0;
    uint32_t saturation = 0;
    Side side = Side::NONE;

    void addEdge(Vertex* v, int vertIndex) {
        neighbors[neighbors.top++] = v;
        neighborsIndex[neighborsIndex.top++] = vertIndex;
    }
    void resizeNeighbors(int newSize) {
        neighbors.resize(newSize);
        neighborsIndex.resize(newSize);
    }

    int degree() const { return neighbors.capacity; }
};

class Graph {
   public:
    uint16_t currentVisit = 0;
    Array<Vertex*> componentBlocks;
    ForwardList<uint32_t> componentsList;
    Array<uint32_t> components;
    bool isBipartite = true;
    uint64_t V;
    uint64_t doubled_number_of_edges = 0;
    Array<Vertex> vertices;
    explicit Graph(uint64_t V) : V(V), vertices(V) {
        componentBlocks.resize(V);
    }

    void bfs(Vertex* start) {
        uint32_t componentSize = 1;
        Array<Vertex*> queue(V);
        int front = 0, back = 0;
        queue[back++] = start;
        start->visited = true;
        start->side = Side::LEFT;
        componentBlocks.push_back(start);
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
                    componentBlocks.push_back(v);
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
            Array<Vertex*> queue(currentComponent);
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
        int64_t cyclesOf4 = 0;
        for (int ii = 0; ii < V; ii++) {
            const Vertex* x = &vertices[ii];
            if (x->degree() < 2 || components[x->component] < 4) continue;
            Array<bool> neighbormatrix(V, false);
            for (int y : x->neighborsIndex) neighbormatrix[y] = true;
            for (int jj = ii + 1; jj < V; jj++) {
                const Vertex* y = &vertices[jj];
                int commonNeighbors = 0;
                for (int z : y->neighborsIndex)
                    if (neighbormatrix[z]) commonNeighbors++;
                cyclesOf4 += (commonNeighbors * (commonNeighbors - 1) / 2);
            }
        }
        printf("%lld\n", cyclesOf4 / 2);
    }

    void bipartiteCountCyclesOf4() {
        int64_t cyclesOf4 = 0;
        for (int ii = 0; ii < V; ii++) {
            const Vertex* x = &vertices[ii];
            if (x->degree() < 2 || components[x->component] < 4) continue;
            Array<bool> neighbormatrix(V, false);
            const Side Xside = x->side;
            for (int y : x->neighborsIndex) neighbormatrix[y] = true;
            for (int jj = ii + 1; jj < V; jj++) {
                const Vertex* y = &vertices[jj];
                if (Xside != y->side) continue;
                int commonNeighbors = 0;
                for (int z : y->neighborsIndex)
                    if (neighbormatrix[z]) commonNeighbors++;
                cyclesOf4 += (commonNeighbors * (commonNeighbors - 1) / 2);
            }
        }
        printf("%lld\n", cyclesOf4 / 2);
    }

    Array<Vertex*> getComponent(uint32_t blockIndex) {
        uint32_t start = 0;
        for (uint32_t i = 0; i < blockIndex; i++) start += components[i];
        return Array<Vertex*>(componentBlocks.data() + start,
                              components[blockIndex]);
    }

    void colorizeSLF(Array<Vertex*>& vertices_ref) {
        for (int i = 0; i < V; i++) {
            Vertex* vertex = pick_best_vertex(vertices_ref);
            colorize_vertex(vertex);
        }
    }

    Vertex* pick_best_vertex(Array<Vertex*>& vertices_ref) {
        heapsort(vertices_ref.data(), vertices_ref.size(),
                 [](Vertex* a, Vertex* b) {
                     if (a->saturation != b->saturation)
                         return a->saturation < b->saturation;
                     else if (a->degree() != b->degree())
                         return a->degree() < b->degree();
                     else
                         return a->index > b->index;
                 });

        for (auto vertex : vertices_ref) {
            if (vertex->color) continue;
            return vertex;
        }
        return nullptr;
    }

    void colorize_vertex(Vertex* vertex) {
        if (vertex->neighbors.size() == 0) {
            vertex->color = 1;
            return;
        }
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
};