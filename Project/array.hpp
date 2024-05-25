#pragma once

template <typename T>
class Array {
   private:
    T* array;
    size_t capacity;

   public:
    Array() : array(nullptr), capacity(0) {}
    explicit Array(size_t size) : capacity(size) { array = new T[size]; }
    Array(size_t size, const T& initVal) : capacity(size) {
        array = new T[size];
        for (size_t i = 0; i < size; ++i) array[i] = initVal;
    }
    ~Array() { delete[] array; }
    T& operator[](size_t index) { return array[index]; }
    const T& operator[](size_t index) const { return array[index]; }
    T* data() { return array; }

    T* begin() { return array; }
    const T* begin() const { return array; }
    T* end() { return array + capacity; }
    const T* end() const { return array + capacity; }

    void resize(size_t newSize) {
        T* newArray = new T[newSize];
        delete[] array;
        array = newArray;
        capacity = newSize;
    }
};