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
    Array<uint16_t> neighborsUniqueColors;
    int index = 0;
    uint16_t color = 0;
    uint16_t visited = 0;
    uint32_t distance = 0;
    uint32_t component = 0;
    Side side = Side::NONE;

    void addEdge(Vertex* v, int vertIndex) {
        neighbors[neighbors.top++] = v;
        neighborsIndex[neighborsIndex.top++] = vertIndex;
    }
    void resizeNeighbors(int newSize) {
        neighbors.resize(newSize);
        neighborsIndex.resize(newSize);
        neighborsUniqueColors.resize(newSize);
    }

    int degree() const { return neighbors.capacity; }

    int saturation() const { return neighborsUniqueColors.top; }
};

class Graph {
   public:
    uint16_t currentVisit = 0;
    ForwardList<uint32_t> componentsList;
    Array<uint32_t> components;
    bool isBipartite = true;
    uint64_t V;
    uint64_t doubledNumberOfEdges = 0;
    Array<Vertex> vertices;
    explicit Graph(uint64_t V) : V(V), vertices(V) {}

    /**
     * The function performs a breadth-first search (BFS) traversal on a graph
     * starting from a specified vertex, assigning sides to vertices and
     * checking for bipartiteness.
     *
     * @param start The `start` parameter in the `bfs` function represents the
     * starting vertex from which the breadth-first search algorithm will begin
     * traversing the graph. It is the initial vertex from which the algorithm
     * will explore its neighbors and components.
     */
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

    /**
     * The function calculates the number of complement edges in a graph.
     *
     * @return The function `numOfcomplementEdges()` returns the number of
     * complement edges in a graph.
     */
    uint64_t numOfcomplementEdges() {
        return V * (V - 1) / 2 - doubledNumberOfEdges / 2;
    }

    /**
     * The function `eccentricity` calculates the eccentricity of each vertex in
     * a graph.
     */
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

    /**
     * The function countCyclesOf4 checks if the graph is bipartite and then
     * calls the appropriate function to count cycles of length 4.
     */
    void countCyclesOf4() {
        if (isBipartite)
            bipartiteCountCyclesOf4();
        else
            countCyclesOf4();
    }

    /**
     * The function `nonBipartiteCountCyclesOf4` calculates the number of cycles
     * of length 4 in a non-bipartite graph.
     */
    void nonBipartiteCountCyclesOf4() {
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

    /**
     * The function `bipartiteCountCyclesOf4` calculates the number of cycles of
     * length 4 in a bipartite graph.
     */
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

    /**
     * The function colorize takes an array of Vertex pointers and calls
     * colorizeVertex on each vertex in the array.
     *
     * @param vertices_ref The `vertices_ref` parameter is an array of pointers
     * to `Vertex` objects. The `colorize` function takes this array as input
     * and iterates through each `Vertex` object in the array, calling the
     * `colorizeVertex` function on each `Vertex` object.
     */
    void colorize(Array<Vertex*>& vertices_ref) {
        for (auto vertex : vertices_ref) colorizeVertex(vertex);
    }

    /**
     * The function colorizeSLF assigns colors to vertices in a graph while
     * ensuring neighboring vertices have unique colors.
     *
     * @param vertices_ref The `vertices_ref` parameter is a reference to an
     * array of pointers to `Vertex` objects. The function `colorizeSLF` takes
     * this array as input and performs colorization on the vertices based on
     * certain conditions. Each `Vertex` object represents a node in a graph,
     * and the function
     */
    void colorizeSLF(Array<Vertex*>& vertices_ref) {
        uint16_t maxColor = 0;
        for (int i = 0; i < vertices_ref.size(); i++) {
            Vertex* vertex = pickBestVertex(vertices_ref);
            if (!vertex) break;
            bool newMaxColor = false;
            colorizeVertex(vertex);
            if (vertex->color > maxColor) {
                maxColor = vertex->color;
                newMaxColor = true;
            }
            if (newMaxColor)
                for (auto neighbor : vertex->neighbors) {
                    if (neighbor->color) continue;
                    neighbor->neighborsUniqueColors.push_back(maxColor);
                }
            else {
                uint16_t color = vertex->color;
                for (auto neighbor : vertex->neighbors) {
                    if (neighbor->color) continue;
                    if (!neighbor->neighborsUniqueColors.contains(color))
                        neighbor->neighborsUniqueColors.push_back(color);
                }
            }
        }
    }

    /**
     * The function `pickBestVertex` selects the best vertex from an array based
     * on saturation and degree criteria.
     *
     * @param vertices_ref The function `pickBestVertex` takes an array of
     * pointers to `Vertex` objects as input. The array is passed by reference,
     * meaning any changes made to the array inside the function will affect the
     * original array in the calling code.
     *
     * @return The function `pickBestVertex` returns a pointer to the best
     * vertex among the input array of vertices based on certain criteria such
     * as saturation and degree.
     */
    Vertex* pickBestVertex(Array<Vertex*>& vertices_ref) {
        Vertex* bestVertex = nullptr;
        int currentBestSaturation = 0;
        int currentBestDegree = 0;

        for (int x = vertices_ref.size() - 1; x >= 0; x--) {
            Vertex* vertex = vertices_ref[x];
            if (!vertex->color) {
                int currentDegree = vertex->degree();
                int saturation = vertex->saturation();
                if (saturation == currentBestSaturation) {
                    if (currentDegree >= currentBestDegree) {
                        currentBestDegree = currentDegree;
                        bestVertex = vertex;
                    }
                } else if (saturation > currentBestSaturation) {
                    currentBestSaturation = saturation;
                    currentBestDegree = currentDegree;
                    bestVertex = vertex;
                }
            }
        }
        return bestVertex;
    }

    /**
     * The function colorizeVertex assigns a color to a vertex based on the
     * colors of its neighboring vertices.
     *
     * @param vertex The `colorizeVertex` function takes a pointer to a `Vertex`
     * object as a parameter. The function assigns a color to the vertex based
     * on the colors of its neighboring vertices. The vertex is assigned the
     * smallest available color that is not used by its neighbors.
     */
    void colorizeVertex(Vertex* vertex) {
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