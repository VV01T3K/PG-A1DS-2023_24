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
                graph.vertices[j].addEdge(&graph.vertices[v - 1]);
            }
            degrees[j] = &graph.vertices[j];
            graph.doubled_number_of_edges += e;
        }

        // printf("?\n");  // 1
        // printf("?\n");  // 2
        // printf("?\n");  // 3
        // printf("?\n");  // 4
        // printf("?\n");  // 5
        // printf("?\n");  // 6
        // printf("?\n");  // 7
        // printf("?\n");  // 8
        // printf("?\n");  // 9
        // printf("?\n");  // 10

        // continue;

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

        for (auto &vertex : graph.vertices) {
            if (!vertex.visited) graph.bfs(&vertex);
        }
        graph.components.resize((graph.componentsList.getSize()));

        for (int j = 0; j < graph.components.size(); j++) {
            graph.components[j] = graph.componentsList.pop_front();
        }

        printf("%d\n", graph.components.size());          // 2
        printf("%c\n", (graph.isBipartite ? 'T' : 'F'));  // 3

        graph.eccentricity();  // 4

        // printf("?\n");  // 1
        // printf("?\n");  // 2
        // printf("?\n");  // 3
        // printf("?\n");  // 4
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

        // printf("%lld\n", graph.cyclesOf4);  // 7

        printf("%lld\n", graph.numOfcomplementEdges());  // 8
    }
    return 0;
}