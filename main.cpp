#include <forward_list>
#include <iostream>
#include <stack>
#include <utility>
#include <vector>
using namespace std;

enum MAZE {
    WALL = 0,
    FLOOR = 1,
    START = 3,
    CHEESE = 5,
};

class Point {
   public:
    int x, y;
    MAZE type;
    bool visited = false;
    Point(int x, int y, int type) : x(x), y(y), type((MAZE)type) {}
    Point() {}
};

int main() {
    system("clear");
    int n, m;
    cin >> n >> m;
    vector<vector<Point>> maze(n, vector<Point>(m));
    pair<int, int> start;
    for (int i = 0; i < n; i++)
        for (int j = 0; j < m; j++) {
            int tmp;
            cin >> tmp;
            maze[i][j] = Point(i, j, tmp);
            if (tmp == START) start = {i, j};
        }

    std::forward_list<pair<int, int>> path;
    stack<pair<int, int>> stack;
    maze[start.first][start.second].visited = true;
    stack.push(start);

    while (!stack.empty()) {
        pair<int, int> current = stack.top();
        path.push_front(current);
        stack.pop();
        if (maze[current.first][current.second].type == CHEESE) break;
        for (int i = 0; i < 4; i++) {
            int x = current.first, y = current.second;
            switch (i) {
                case 0:
                    x--;
                    break;
                case 1:
                    y--;
                    break;
                case 2:
                    y++;
                    break;
                case 3:
                    x++;
                    break;
            }
            if (x < 0 || x >= n || y < 0 || y >= m) continue;
            if (maze[x][y].type == WALL || maze[x][y].visited) continue;
            maze[x][y].visited = true;
            stack.push({x, y});
        }
    }

    // n x m array filed with 0
    vector<vector<int>> path_map(n, vector<int>(m, 0));
    for (auto p : path) {
        path_map[p.first][p.second] = 1;
    }

    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) cout << path_map[i][j] << " ";
        cout << endl;
    }
}