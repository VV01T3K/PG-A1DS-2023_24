#include <cstdio>

#include "Array.hpp"
#include "Graph.cpp"
#include "HeapSort.hpp"

int main() {
    int k;

    scanf("%d", &k);

    for (int i = 0; i < k; i++) {
        int n;
        scanf("%d", &n);
        Graph graph(n);
        Array<int> degrees(n);
        for (int j = 0; j < n; j++) {
            int e;
            scanf("%d", &e);
            graph.vertices[j].resizeNeighbors(e);
            for (int k = 0; k < e; k++) {
                int v;
                scanf("%d", &v);
                graph.addEdge(&graph.vertices[j], &graph.vertices[v]);
            }
            degrees[j] = graph.vertices[j].degree;
        }

        heapsort(degrees.data(), n, [](int a, int b) { return a < b; });
        for (auto degree : degrees) {
            printf("%d ", degree);
        }
        printf("\n");
        for (int j = 0; j < 9; j++) {
            printf("?\n");
        }
    }
    return 0;
}