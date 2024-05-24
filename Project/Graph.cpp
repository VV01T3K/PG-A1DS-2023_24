#include <cstdint>
#include <cstdio>
#include <forward_list>
#include <vector>

enum class Color : uint8_t { WHITE, GRAY, BLACK };

class Vertex {
   public:
    int id;
    Color color = Color::WHITE;
    std::forward_list<int> adjecent;
    int degree = 0;

    void addEdge(int v) {
        adjecent.push_front(v);
        degree++;
    }

    int getDegree() const { return degree; }

    void printVertex() {
        printf("%d: ", id);
        for (int v : adjecent) {
            printf("%d ", v);
        }
        printf("\n");
    }
};

class Graph {
   public:
    int V;
    std::vector<Vertex> vertices;
    explicit Graph(int V) : V(V) {
        vertices.resize(V);
        for (int i = 0; i < V; i++) {
            vertices[i].id = i;
        }
    }

    void printGraph() {
        for (Vertex v : vertices) v.printVertex();
    }
};