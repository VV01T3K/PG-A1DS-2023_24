#include <cstdio>

enum MAZE {
    WALL = 0,
    FLOOR = 1,
    START = 3,
    CHEESE = 5,
};

class Cell {
   public:
    int y, x;
    MAZE type;
    bool visited = false;
    Cell(int y, int x, int type) : y(y), x(x), type((MAZE)type) {}
    Cell(int y, int x) : y(y), x(x) {}
    Cell() {}
};

class Stack {
   public:
    Cell *array;
    int size = 0;
    int max_size;
    Stack(int size) : max_size(size) { array = new Cell[size]; }
    ~Stack() { delete[] array; }
    void push(Cell data) { array[size++] = data; }
    Cell pop() { return array[--size]; }
    bool empty() { return size == 0; }
};

enum Direction {
    SOUTH = 0,
    EAST = 1,
    WEST = 2,
    NORTH = 3,
};

void dfs(Cell **maze, int **path, int n, int m, Cell start) {
    Stack stack(m * n);
    start.visited = true;
    stack.push(start);

    while (!stack.empty()) {
        Cell curr = stack.pop();
        maze[curr.y][curr.x].visited = true;
        path[curr.y][curr.x] = 1;
        if (maze[curr.y][curr.x].type == CHEESE) break;
        for (int i = 3; i >= 0; i--) {
            int y = curr.y, x = curr.x;
            switch (i) {
                case NORTH:
                    y--;
                    break;
                case WEST:
                    x--;
                    break;
                case EAST:
                    x++;
                    break;
                case SOUTH:
                    y++;
                    break;
            }
            if (maze[y][x].type == WALL || maze[y][x].visited) continue;
            stack.push({y, x});
        }
    }
}

int main() {
    int n, m;
    scanf("%d %d", &m, &n);

    Cell start;
    Cell **maze = new Cell *[n];
    int **path = new int *[n];
    for (int i = 0; i < n; i++) {
        maze[i] = new Cell[m];
        path[i] = new int[m]{0};
        for (int j = 0; j < m; j++) {
            int tmp;
            scanf("%d", &tmp);
            maze[i][j] = Cell(i, j, tmp);
            if (tmp == START) start = {i, j};
        }
    }

    dfs(maze, path, n, m, start);

    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) printf("%d ", path[i][j]);
        printf("\n");
    }

    return 0;
}