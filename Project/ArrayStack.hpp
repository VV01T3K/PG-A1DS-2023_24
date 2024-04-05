#pragma once

#include <stdexcept>

template <typename T>
class ArrayStack {
   private:
    T* array;
    int size = 0;
    int max_size;

   public:
    ArrayStack(int size) : max_size(size) { array = new T[size]; }
    ~ArrayStack() { delete[] array; }

    void push(T element) {
        if (size < max_size) {
            array[size++] = element;
        }
    }
    T pop() {
        if (size > 0) return array[--size];
        throw std::out_of_range("Stack is empty");
    }
    T& top() {
        if (size > 0) return array[size - 1];
        throw std::out_of_range("Stack is empty");
    }
    bool empty() { return size == 0; }
};