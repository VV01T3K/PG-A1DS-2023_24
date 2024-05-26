#include <cstdint>
#include <cstdio>

#include "array.hpp"
#include "graph.cpp"
#include "heap.hpp"

int main() {
    int k;

    scanf("%d", &k);

    // graph
    for (int i = 0; i < k; i++) {
        uint64_t n;
        scanf("%lld", &n);
        Graph graph(n);
        Array<Vertex *> degrees(n);
        // vertex
        for (int j = 0; j < n; j++) {
            int e;
            scanf("%d", &e);
            graph.vertices[j].resizeNeighbors(e);
            graph.vertices[j].index = j + 1;
            // neighbors
            for (int ii = 0; ii < e; ii++) {
                int v;
                scanf("%d", &v);
                graph.addEdge(&graph.vertices[j], &graph.vertices[v - 1]);
            }
            heapsort(graph.vertices[j].neighbors.data(), e,
                     [](Vertex *a, Vertex *b) { return a->index < b->index; });
            degrees[j] = &graph.vertices[j];
        }
        graph.colorize(degrees);
        heapsort(degrees.data(), n, [](Vertex *a, Vertex *b) {
            if (a->degree() != b->degree())
                return a->degree() < b->degree();
            else
                return a->index > b->index;
        });
        for (auto vertex : degrees) {
            printf("%d ", vertex->degree());
        }
        printf("\n");  // 1

        int components = 0;
        for (auto &vertex : graph.vertices) {
            if (!vertex.visited) {
                graph.bfs(&vertex);
                components++;
            }
        }
        printf("%d\n", components);                       // 2
        printf("%c\n", (graph.isBipartite ? 'T' : 'F'));  // 3

        // printf("?\n");  // 1
        // printf("?\n");  // 2
        // printf("?\n");  // 3
        printf("?\n");  // 4
        printf("?\n");  // 5

        // printf("?\n");  // 6a
        for (auto &vertex : graph.vertices) {
            printf("%d ", vertex.color);
            vertex.color = 0;
        }
        printf("\n");  // 6a

        // printf("?\n");  // 6b
        graph.colorize(degrees);
        for (auto &vertex : graph.vertices) {
            printf("%d ", vertex.color);
            vertex.color = 0;
        }
        printf("\n");  // 6b

        printf("?\n");  // 6c

        printf("?\n");  // 7
        // printf("?\n");  // 8

        // graph.countCyclesOf4();

        // printf("%lld\n", graph.cyclesOf4 / 2);  // 7

        printf("%lld\n", graph.numOfcomplementEdges());  // 8
    }
    return 0;
}