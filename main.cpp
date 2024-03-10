#include <iostream>
#include <stdexcept>
using namespace std;

class DynamicArray_2D {
    int **array;
    int max_row;
    int max_col;

   public:
    DynamicArray_2D(int row, int col) : max_row(row), max_col(col) {
        array = new int *[max_row];
        for (int i = 0; i < max_row; i++) {
            array[i] = new int[max_col];
            std::fill_n(array[i], max_col, 0);
        }
    }
    ~DynamicArray_2D() {
        for (int i = 0; i < max_row; ++i) delete[] array[i];
        delete[] array;
    };
    void print() const {
        for (int i = 0; i < max_row; i++) {
            for (int j = 0; j < max_col; j++) {
                cout << array[i][j] << " ";
            }
            cout << "\n";
        }
    }
    int &operator()(int row, int column) {
        if (row < 0) row += max_row;
        if (column < 0) column += max_col;
        if (row < 0 || row >= max_row)
            throw std::out_of_range("Row out of range");
        if (column < 0 || column >= max_col)
            throw std::out_of_range("Column out of range");

        return array[row][column];
    }
    int *operator[](int index) {
        if (index < 0 || index >= max_row)
            throw std::out_of_range("Index out of range");

        return array[index];
    }
};
int main() {
    int row, col, distance;

    cin >> row >> col;

    DynamicArray_2D array(row, col);

    for (int i = 0; i < row; i++) {
        for (int j = 0; j < col; j++) {
            cin >> array(i, j);
        }
    }
    cin >> distance;

    int i;

    for (int d = 0; d < distance; d++) {
        int tmp = array(0, 0);
        for (i = 0; i < col - 1; i++) {
            array(0, i) = array(0, i + 1);
        }
        for (i = 0; i < row - 1; i++) {
            array(i, -1) = array(i + 1, -1);
        }
        for (i = col - 1; i > 0; i--) {
            array(-1, i) = array(-1, i - 1);
        }
        for (i = row - 1; i > 0; i--) {
            array(i, 0) = array(i - 1, 0);
        }
        array(1, 0) = tmp;
    }

    array.print();

    return 0;
}