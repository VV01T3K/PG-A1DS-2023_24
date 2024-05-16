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
    Cell *parent = nullptr;
    MAZE type;
    bool visited = false;
    Cell(int y, int x, MAZE type) : y(y), x(x), type(type) {}
    Cell() {}
};

class Queue {
   public:
    Cell *arr;
    int capacity, front, rear, count;
    Queue(int size)
        : capacity(size), front(0), rear(-1), count(0), arr(new Cell[size]) {}
    ~Queue() { delete[] arr; }
    void put(Cell item) {
        rear = (rear + 1) % capacity;
        arr[rear] = item;
        count++;
    }
    Cell get() {
        Cell x = arr[front];
        front = (front + 1) % capacity;
        count--;
        return x;
    }
    bool empty() { return count == 0; }
};

enum Direction {
    SOUTH = 0,
    EAST = 1,
    WEST = 2,
    NORTH = 3,
};

void bfs(Cell **maze, int **path, int n, int m, Cell start, Cell &end) {
    Queue queue(m * n);
    start.visited = true;
    queue.put(start);
    while (!queue.empty()) {
        Cell curr = queue.get();
        maze[curr.y][curr.x].visited = true;
        if (maze[curr.y][curr.x].type == CHEESE) {
            end = curr;
            break;
        }
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
            maze[y][x].parent = &maze[curr.y][curr.x];
            queue.put(maze[y][x]);
        }
    }
}

int main() {
    int n, m;
    scanf("%d %d", &m, &n);

    Cell start;
    Cell end;
    Cell **maze = new Cell *[n];
    int **path = new int *[n];
    for (int i = 0; i < n; i++) {
        maze[i] = new Cell[m];
        path[i] = new int[m]{0};
        for (int j = 0; j < m; j++) {
            int tmp;
            scanf("%d", &tmp);
            maze[i][j] = Cell(i, j, (MAZE)tmp);
            if (tmp == START) start = maze[i][j];
        }
    }

    bfs(maze, path, n, m, start, end);

    Cell *curr = &end;
    while (curr->parent != nullptr) {
        path[curr->y][curr->x] = 1;
        curr = curr->parent;
    }
    path[start.y][start.x] = 1;

    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) printf("%d ", path[i][j]);
        printf("\n");
    }

    for (int i = 0; i < n; i++) {
        delete[] maze[i];
        delete[] path[i];
    }
    delete[] maze;
    delete[] path;

    return 0;
}