#pragma once
template <typename T>
class Array {
   private:
    T* array;
    size_t arraySize = 0;

   public:
    Array() : array(nullptr) {}
    Array(size_t size) : arraySize(size) { array = new T[size]; }
    Array(size_t size, const T& initVal) : arraySize(size) {
        array = new T[size];
        for (size_t i = 0; i < size; ++i) array[i] = initVal;
    }
    ~Array() { delete[] array; }
    T& operator[](size_t index) { return array[index]; }
    const T& operator[](size_t index) const { return array[index]; }
    size_t size() const { return arraySize; }
    T* data() { return array; }

    T* begin() { return array; }
    const T* begin() const { return array; }
    T* end() { return array + arraySize; }
    const T* end() const { return array + arraySize; }
};