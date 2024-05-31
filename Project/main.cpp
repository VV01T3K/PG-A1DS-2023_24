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
        Array<Vertex *> sortedByDegreeDesc(n);
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
                graph.vertices[j].addEdge(&graph.vertices[v - 1], v - 1);
            }
            sortedByDegreeDesc[j] = &graph.vertices[j];
            graph.doubled_number_of_edges += e;
        }

        // graph.colorize(sortedByDegreeDesc);
        heapsort(sortedByDegreeDesc.data(), n, [](Vertex *a, Vertex *b) {
            if (a->degree() != b->degree())
                return a->degree() < b->degree();
            else
                return a->index > b->index;
        });
        // for (auto vertex : sortedByDegreeDesc) {
        //     printf("%d ", vertex->degree());
        // }
        // printf("\n");  // 1

        for (auto &vertex : graph.vertices) {
            if (!vertex.visited) graph.bfs(&vertex);
        }
        graph.components.resize((graph.componentsList.getSize()));

        for (int j = 0; j < graph.components.size(); j++) {
            graph.components[j] = graph.componentsList.pop_front();
        }

        graph.colorizeSLF(sortedByDegreeDesc);
        for (auto &vertex : graph.vertices) {
            printf("%d ", vertex.color);
        }
        printf("\n");

        // for (auto vertex : graph.componentBlocks) {
        //     printf("%d ", vertex->index);
        // }
        // printf("\n");

        // for (int j = 0; j < graph.components.size(); j++) {
        //     printf("%d ", graph.components[j]);
        // }
        // printf("\n");

        // for (int blockIndex = 0; blockIndex < graph.components.size();
        //      blockIndex++) {
        //     Array<Vertex *> block = graph.getComponent(blockIndex);
        //     heapsort(block.data(), block.size(), [](Vertex *a, Vertex *b) {
        //         if (a->degree() != b->degree())
        //             return a->degree() < b->degree();
        //         else
        //             return a->index > b->index;
        //     });

        //     for (auto vertex : block) {
        //         printf("%d ", vertex->index);
        //     }
        //     printf("\n");
        // }
    }
    return 0;
}
