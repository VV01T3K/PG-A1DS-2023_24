#pragma once
#include <cstdio>

template <typename T, template <typename...> class Container>
class Stack {
   private:
    Container<T> container;

   public:
    void push(const T& value) { container.push_front(value); }
    T pop() { return container.pop_front(); }
    T& peek() { return container.front(); }

    void clear() { container.clear(); }

    void printInt(const char* seperator = " ") const {
        container.printInt(seperator);
    }

    void printToken(const char* seperator = " ") const {
        container.printToken(seperator);
    }

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