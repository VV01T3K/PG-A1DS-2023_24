#pragma once
// !! danger !! this is a simplified version of the Stack container
template <typename T>
class Stack {
   private:
    T* array;
    int size = 0;
    int max_size;

   public:
    Stack(int size) : max_size(size) { array = new T[size]; }
    ~Stack() { delete[] array; }

    void push(T element) {
        if (size < max_size) array[size++] = element;
    }
    T pop() { return array[--size]; }
    T& top() { return array[size - 1]; }
    bool empty() { return size == 0; }
};