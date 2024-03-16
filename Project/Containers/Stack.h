#pragma once
#include <cstddef>
#include <iostream>
#include <stdexcept>
#include <utility>

template <typename T, template <typename...> class Container>
class Stack {
   private:
    Container<T> container;

   public:
    void push(const T& value) { container.push_front(value); }
    T pop() {
        if (container.isEmpty()) throw std::out_of_range("Stack is empty");
        return container.pop_front();
    }
    T& peek() {
        if (container.isEmpty()) throw std::out_of_range("Stack is empty");
        return container.front();
    }

    void clear() { container.clear(); }

    void print(const char* seperator = ">") const {
        container.print(seperator);
    }

    friend std::ostream& operator<<(std::ostream& out,
                                    const Stack<T, Container>& stack) {
        return out << stack.container;
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