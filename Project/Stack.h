#pragma once
#include <cstdio>
#include <iostream>

template <typename T, template <typename...> class Container>
class Stack {
   private:
    Container<T> container;

   public:
    template <typename U>
    void push(U&& data) {
        container.push_front(std::forward<U>(data));
    }
    T pop() { return container.pop_front(); }
    T& peek() { return container.front(); }

    void clear() { container.clear(); }

    void printInt() const { container.printInt(); }

    void printToken() const { container.printToken(); }

    bool isEmpty() const { return container.isEmpty(); }
    size_t getSize() const { return container.getSize(); }

    void swap(Stack& other) { container.swap(other.container); }
    void swap(Container<T>& other) { container.swap(other); }
    template <typename U>
    void swap(U& other) {
        Container<T> tmp;
        container.swap(tmp);
        other.swap(tmp);
        container.swap(tmp);
    }
};