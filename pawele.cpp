void Graph::SLF() {
    int v = vertexes;
    int max = 0;
    int* colors = new int[v];
    int* colorCount = new int[v];
    clearTab(colors, v);
    clearTab(colorCount, v);

    // ustaw 1 dla wierzcholka bez sasiadow
    for (int i = 0; i < v; i++) {
        if (!(vertex[i]->neighbours)) {
            colors[i] = 1;
        }
    }

    int currComponent = 0;

    while (currComponent != components) {
        int size = vertexesInNComponent[currComponent];
        // continue;
        int* currComponentArr = array2DOfComponents[currComponent];
        if (size != 1)
            while (true) {
                int index =
                    getNextIndex(colors, colorCount, currComponentArr, size);
                if (index < 0) break;
                bool newcolor = paintVertex(index, colors, max);

                if (!newcolor)
                    updateColorCount(colorCount, colors, index);
                else
                    ezUpdateColorCount(colorCount, colors, index);
            }
        currComponent++;
    }

    printColors(colors, v);
    delete[] colorCount;
    delete[] colors;
}

int Graph::getNextIndex(int* colors, int* colorCount, int* currComponentArr,
                        int size) {
    int pick = -1;
    int currentBestColors = 0;
    int currentBestDegree = 0;

    for (int x = size - 1; x >= 0; x--) {
        int i = currComponentArr[x];
        if (!colors[i]) {
            int currdeg = vertex[i]->neighbours;
            int differentColors = colorCount[i];
            if (differentColors == currentBestColors) {
                if (currdeg >= currentBestDegree) {
                    currentBestDegree = currdeg;
                    pick = i;
                }
            } else if (differentColors > currentBestColors) {
                currentBestColors = differentColors;
                currentBestDegree = currdeg;
                pick = i;
            }
        }
    }
    return pick;
}
int Graph::addNumOfColors(int curr, int lastIndex, int* colors) {
    Vertex* cv = (vertex[curr]);
    int lastColor = colors[lastIndex];
    for (int i = 0; i < cv->neighbours; i++) {
        int neigh = cv->neighbour[i];
        if (colors[neigh] == lastColor && neigh != lastIndex) {
            return 0;
        }
    }
    return 1;
}
void Graph::updateColorCount(int* colorCount, int* colors, int lastIndex) {
    Vertex* cv = vertex[lastIndex];
    // update tylko sasiadow, bo tylko im zmieni saturacje polozenie koloru na
    // lascie
    for (int i = 0; i < cv->neighbours; i++) {
        int neighIndex = cv->neighbour[i];
        if (!(colors[neighIndex])) {
            colorCount[neighIndex] +=
                addNumOfColors(neighIndex, lastIndex, colors);
        }
    }
}
void Graph::ezUpdateColorCount(int* colorCount, int* colors, int lastIndex) {
    Vertex* cv = vertex[lastIndex];
    // update tylko sasiadow, bo tylko im zmieni saturacje polozenie koloru na
    // lascie
    for (int i = 0; i < cv->neighbours; i++) {
        colorCount[cv->neighbour[i]]++;
    }
}