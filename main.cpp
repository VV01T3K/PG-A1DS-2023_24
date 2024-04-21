#include <cstdio>

enum MAZE {
    WALL = 0,
    FLOOR = 1,
    START = 3,
    CHEESE = 5,
};
class Point {
   public:
    int y, x;
    MAZE type;
    bool visited = false;
    Point(int y, int x, int type) : y(y), x(x), type((MAZE)type) {}
    Point(int y, int x) : y(y), x(x) {}
    Point() {}
};

class Stack {
   public:
    Point* array;
    int size = 0;
    int max_size;
    Stack(int size) : max_size(size) { array = new Point[size]; }
    ~Stack() { delete[] array; }
    void push(Point element) {
        if (size < max_size) array[size++] = element;
    }
    Point pop() { return array[--size]; }
    bool empty() { return size == 0; }
};

enum DIRECTION {
    SOUTH = 0,
    EAST = 1,
    WEST = 2,
    NORTH = 3,
};

void dfs(Point** maze, int** path, int n, int m, Point start) {
    Stack stack(n * m);
    start.visited = true;
    stack.push(start);

    while (!stack.empty()) {
        Point current = stack.pop();
        path[current.y][current.x] = 1;
        if (maze[current.y][current.x].type == CHEESE) break;
        for (int i = 3; i >= 0; i--) {
            int y = current.y, x = current.x;
            switch (i) {
                case NORTH:
                    y--;
                    break;
                case WEST:
                    x--;
                    break;
                case SOUTH:
                    y++;
                    break;
                case EAST:
                    x++;
                    break;
            }
            if (y < 0 || y >= n || x < 0 || x >= m) continue;
            if (maze[y][x].type == WALL || maze[y][x].visited) continue;
            maze[y][x].visited = true;
            stack.push({y, x});
        }
    }
}

int main() {
    int n, m;
    scanf("%d %d", &n, &m);
    Point start;

    Point** maze = new Point*[n];
    int** path = new int*[n];
    for (int i = 0; i < n; i++) {
        maze[i] = new Point[m];
        path[i] = new int[m]{0};
        for (int j = 0; j < m; j++) {
            int tmp;
            scanf("%d", &tmp);
            maze[i][j] = Point(i, j, tmp);
            if (tmp == START) start = {i, j};
        }
    }

    dfs(maze, path, n, m, start);

    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) printf("%d ", path[i][j]);
        printf("\n");
    }
}