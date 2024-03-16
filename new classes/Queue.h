#pragma once
#include <cstddef>
#include <iostream>
#include <stdexcept>
#include <utility>

template <typename T, template <typename...> class Container>
class Queue {
   private:
    Container<T> container;

   public:
    void put(const T& value) { container.push_back(value); }
    void get() {
        if (container.isEmpty()) throw std::out_of_range("Queue is empty");
        container.pop_front();
    }
    T& front() {
        if (container.isEmpty()) throw std::out_of_range("Queue is empty");
        return container.front();
    }
    T& back() {
        if (container.isEmpty()) throw std::out_of_range("Queue is empty");
        return container.back();
    }

    void print(const char* seperator = "<") const {
        container.print(seperator);
    }

    friend std::ostream& operator<<(std::ostream& out,
                                    const Queue<T, Container>& queue) {
        return out << queue.container;
    }

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