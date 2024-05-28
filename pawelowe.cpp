void Graph::C4() {
    int v = vertexes;
    long long result = 0;
    for (int i = 0; i < v; i++) {
        if ((vertex[i]->neighbours < 2)) continue;
        bool* firstneigh = new bool[v]();
        getfirst(i, firstneigh);
        for (int j = i + 1; j < v; j++) {
            result += findLoops(i, j, firstneigh);
        }
        delete[] firstneigh;
    }

    printf("%lld\n", result / 2);
}

void Graph::getfirst(int index, bool* firstneigh) {
    Vertex* v1 = vertex[index];
    for (int i = 0; i < v1->neighbours; i++) {
        firstneigh[v1->neighbour[i]] = true;
    }
}
int Graph::findLoops(int first, int second, bool* firstnei) {
    Vertex* v2 = vertex[second];
    int mutual = getMutual(firstnei, first, v2);
    return ((mutual) * (mutual - 1) / 2);
}
int Graph::getMutual(bool* firstnei, int first, Vertex* v2) {
    int result = 0;
    for (int i = 0; i < v2->neighbours; i++) {
        int neigh = v2->neighbour[i];
        if (firstnei[neigh]) {
            result++;
        }
    }
    return result;
}