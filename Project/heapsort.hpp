#pragma once

#include "other.hpp"

template <typename T, typename Func>
class Heap {
   public:
    T* data;
    int size;
    Func compare;

    static int Left(int i) { return 2 * i + 1; }
    static int Right(int i) { return 2 * i + 2; }

    Heap(T* array, int size, Func compare = Func())
        : data(array), size(size), compare(compare) {}

    void heapify(int i) {
        int left = Left(i);
        int right = Right(i);
        int min = i;
        bool leftInBounds = left < size;
        bool rightInBounds = right < size;
        if (leftInBounds && compare(data[left], data[i])) min = left;
        if (rightInBounds && compare(data[right], data[min])) min = right;
        if (min != i) {
            swap(data[i], data[min]);
            heapify(min);
        }
    }

    void buildHeap() {
        for (int i = size - 1; i >= 0; i--) heapify(i);
    }
};

template <typename T, typename Func>
void heapsort(T array[], int size, Func compare = Func()) {
    Heap<T, Func> heap(array, size, compare);
    heap.buildHeap();
    for (int i = size - 1; i > 0; i--) {
        swap(array[0], array[i]);
        heap.size--;
        heap.heapify(0);
    }
}