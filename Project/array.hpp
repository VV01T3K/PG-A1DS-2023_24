#pragma once

template <typename T>
class Array {
   private:
    T* array = nullptr;
    bool isOwner = true;

   public:
    size_t capacity = 0;
    size_t top = 0;

    size_t size() const { return capacity; }

    Array() = default;
    explicit Array(size_t size) : capacity(size) { array = new T[size]; }
    Array(T* array, size_t size) : array(array), capacity(size) {
        isOwner = false;
    }
    Array(size_t size, const T& initVal) : capacity(size) {
        array = new T[size];
        for (size_t i = 0; i < size; ++i) array[i] = initVal;
    }
    ~Array() {
        if (isOwner) delete[] array;
    }
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
        top = 0;
    }

    void setinitVal(const T& initVal) {
        for (size_t i = 0; i < capacity; ++i) array[i] = initVal;
    }

    void push_back(const T& value) { array[top++] = value; }
};