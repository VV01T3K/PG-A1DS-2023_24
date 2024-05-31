#pragma once

#include "array.hpp"
#include "other.hpp"

template <typename T, typename Func>
class Heap {
   public:
    T* data;
    int size;
    Func compare;

    static int Left(int i) { return 2 * i + 1; }
    static int Right(int i) { return 2 * i + 2; }
    static int Parent(int i) { return (i - 1) / 2; }

    Heap(T* array, int size, Func compare = Func())
        : data(array), size(size), compare(compare) {}

    void heapify(int i) {
        int best = i;
        int left = Left(i);
        int right = Right(i);

        if (left < size && compare(data[left], data[best])) best = left;
        if (right < size && compare(data[right], data[best])) best = right;

        if (best != i) {
            my::swap(data[i], data[best]);
            heapify(best);
        }
    }

    void buildHeap() {
        for (int i = size / 2 - 1; i >= 0; i--) heapify(i);
    }

    void sort() {
        buildHeap();
        for (int i = size - 1; i > 0; i--) {
            my::swap(data[0], data[i]);
            size--;
            heapify(0);
        }
    }
};

template <typename T, typename Func>
void heapsort(T array[], int size, Func compare = Func()) {
    Heap<T, Func> heap(array, size, compare);
    heap.sort();
}