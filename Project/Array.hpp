#pragma once
#include <iostream>

template <typename T>
class Array {
   private:
    T* array;
    size_t size;

   public:
    Array(size_t size, const T& initVal = T()) : size(size) {
        array = new T[size]{initVal};
        std::fill_n(array, size, initVal);
    }

    T& operator[](size_t index) { return array[index]; }
    const T& operator[](size_t index) const { return array[index]; }
    size_t size() const { return size; }
    T* data() { return array; }
    ~Array() { delete[] array; }

    T* begin() { return array; }
    const T* begin() const { return array; }
    T* end() { return array + size; }
    const T* end() const { return array + size; }
};