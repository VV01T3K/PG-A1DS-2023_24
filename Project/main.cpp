#include <cstdint>
#include <cstdio>

#include "array.hpp"
#include "graph.cpp"
#include "heapsort.hpp"

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
            graph.vertices[j].index = j + 1;  // dodatkowe
            // neighbors
            for (int ii = 0; ii < e; ii++) {
                int v;
                scanf("%d", &v);
                graph.addEdge(&graph.vertices[j], &graph.vertices[v - 1]);
            }
            degrees[j] = &graph.vertices[j];
        }

        heapsort(degrees.data(), n,
                 [](Vertex *a, Vertex *b) { return a->degree < b->degree; });
        for (auto vertex : degrees) {
            printf("%d ", vertex->degree);
        }
        printf("\n");  // 1

        int components = 0;
        for (auto &vertex : graph.vertices) {
            if (!vertex.visited) {
                graph.bfs(&vertex);
                components++;
            }
        }
        printf("%d\n", components);  // 2

        for (int ii = 0; ii < 7; ii++) printf("?\n");

        printf("%lld\n", graph.numOfcomplementEdges());  // 8
    }
    return 0;
}