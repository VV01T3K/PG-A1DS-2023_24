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
            for (int l = 0; l < e; l++) {
                int v;
                scanf("%d", &v);
                graph.vertices[j].addEdge(v);
            }
            for (int v : graph.vertices[j].adjecent) {
                degrees[j] += graph.vertices[v].degree;
            }
        }

        heapsort(degrees.data(), n, [](int a, int b) { return a < b; });
        for (int j = 0; j < n; j++) {
            printf("%d ", degrees[j]);
        }
        for (int j = 0; j < 9; j++) {
            printf("? ");
        }
        // graph.printGraph();
    }
    return 0;
}