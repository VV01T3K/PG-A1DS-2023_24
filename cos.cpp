#include <iostream>

int main() {
    int n, m, distance;

    std::cin >> n >> m;
    int array[100][100];
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            std::cin >> array[i][j];
        }
    }
    std::cin >> distance;
    std::cout << "-------------\n";
    for (int d = 0; d < distance; d++) {
        int tmp = array[0][0];
        for (int i = 0; i < m - 1; i++) {
            array[0][i] = array[0][i + 1];
        }
        for (int i = 0; i < n - 1; i++) {
            array[i][m - 1] = array[i + 1][m - 1];
        }
        for (int i = m - 1; i > 0; i--) {
            array[n - 1][i] = array[n - 1][i - 1];
        }
        for (int i = n - 1; i > 0; i--) {
            array[i][0] = array[i - 1][0];
        }
        array[1][0] = tmp;
    }

    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            std::cout << array[i][j] << " ";
        }
        std::cout << "\n";
    }
    return 0;
}