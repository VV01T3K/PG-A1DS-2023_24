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

    int tmp;
    for (int d = 0; d < distance; d++) {
        for (int i = 0; i < n - 1; i++) {
            tmp = array[0][i];
            array[0][i] = array[0][i + 1];
            array[0][i + 1] = tmp;
        }

        for (int j = 0; j < m - 1; j++) {
            tmp = array[j][m - 1];
            array[j][m - 1] = array[j + 1][m - 1];
            array[j + 1][m - 1] = tmp;
        }

        for (int i = m - 1; i >= 1; i--) {
            tmp = array[n - 1][i];
            array[n - 1][i] = array[n - 1][i - 1];
            array[n - 1][i - 1] = tmp;
        }
        for (int j = n - 1; j >= 1; j--) {
            tmp = array[j][0];
            array[j][0] = array[j - 1][0];
            array[j - 1][0] = tmp;
        }
    }
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            std::cout << array[i][j] << " ";
        }
        std::cout << "\n";
    }

    return 0;
}