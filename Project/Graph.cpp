#include <iostream>
#include <list>
#include <vector>

enum class Color { WHITE, GRAY, BLACK };

class Vertex {
   public:
    int id;
    int degree = 0;
    Color color = Color::WHITE;
    std::list<int> adjecenty;

    void addEdge(int v) {
        adjecenty.push_back(v);
        degree++;
    }

    void printVertex() {
        std::cout << id << ": ";
        for (int v : adjecenty) {
            std::cout << v << " ";
        }
        std::cout << std::endl;
    }
};

class Graph {
   public:
    int V;
    std::vector<Vertex> vertices;
    Graph(int V) {
        this->V = V;
        vertices.resize(V);
        for (int i = 0; i < V; i++) {
            vertices[i].id = i;
        }
    }

    void printGraph() {
        for (Vertex v : vertices) v.printVertex();
    }
};