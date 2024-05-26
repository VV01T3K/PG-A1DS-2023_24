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
        int largest = i;
        int left = Left(i);
        int right = Right(i);

        if (left < size && compare(data[left], data[largest])) largest = left;
        if (right < size && compare(data[right], data[largest]))
            largest = right;

        if (largest != i) {
            my::swap(data[i], data[largest]);
            heapify(largest);
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

    void remove(int i) {
        data[i] = data[--size];
        heapify(i);
    }

    void bulkUpdate(Array<int>& indices) {
        for (int i : indices) {
            update(i);
        }
    }

    void update(int i) {
        while (i != 0 && compare(data[Parent(i)], data[i])) {
            my::swap(data[i], data[Parent(i)]);
            i = Parent(i);
        }
        heapify(i);
    }
};

template <typename T, typename Func>
void heapsort(T array[], int size, Func compare = Func()) {
    Heap<T, Func> heap(array, size, compare);
    heap.sort();
}