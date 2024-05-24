#include <cstdio>

#include "Graph.cpp"

int main() {
    int k;

    scanf("%d", &k);

    for (int i = 0; i < 1; i++) {
        int n;
        scanf("%d", &n);
        // for (int j = 0; j < 10; j++) {
        //     printf("?\n");
        // }
        Graph graph(n);
        for (int j = 0; j < n; j++) {
            int e;
            scanf("%d", &e);
            for (int l = 0; l < e; l++) {
                int v;
                scanf("%d", &v);
                graph.vertices[j].addEdge(v);
            }
        }
        graph.printGraph();
    }

    return 0;
}