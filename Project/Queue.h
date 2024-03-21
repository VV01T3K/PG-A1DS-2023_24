#pragma once
#include <cstdio>

template <typename T, template <typename...> class Container>
class Queue {
   private:
    Container<T> container;

   public:
    template <typename U>
    void put(U&& data) {
        container.push_back(std::forward<U>(data));
    }
    T get() { return container.pop_front(); }

    void clear() { container.clear(); }

    T& front() { return container.front(); }
    T& back() { return container.back(); }

    bool isEmpty() const { return container.isEmpty(); }
    size_t getSize() const { return container.getSize(); }

    void swap(Queue& other) { container.swap(other.container); }
    void swap(Container<T>& other) { container.swap(other); }
    template <typename U>
    void swap(U& other) {
        Container<T> tmp;
        container.swap(tmp);
        other.swap(tmp);
        container.swap(tmp);
    }
};