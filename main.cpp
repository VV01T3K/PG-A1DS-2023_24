#include <iostream>
using namespace std;

enum maze {
    WALL = 0,
    FLOOR = 1,
    START = 3,
    CHEESE = 5,
};

enum direction {
    SOUTH = 0,
    EAST = 1,
    WEST = 2,
    NORTH = 3,
};

class Stack {
   private:
    int* array;
    int size = 0;
    int max_size;

   public:
    Stack(int size) : max_size(size) { array = new int[size]; }
    ~Stack() { delete[] array; }
    void push(int element) {
        if (size < max_size) array[size++] = element;
    }
    int pop() { return array[--size]; }
};

int main() {
    int n, m;
    cin >> n >> m;
    Stack stack(n * m);
    int* maze = new int[n * m];
    for (int i = 0; i < n * m; i++) cin >> maze[i];

    // print maze
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) cout << maze[i * m + j] << " ";
        cout << endl;
    }

    delete[] maze;
    return 0;
}