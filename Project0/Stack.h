#pragma once
#include <cstddef>
#include <iostream>
#include <stdexcept>

#include "DoublyLinkedList_Template.h"
template <typename T>
class Stack {
    DoublyLinkedList<T> list;
    Node<T> *top;

   public:
    DoublyLinkedList<T> swapList(DoublyLinkedList<T> &newlist) {
        DoublyLinkedList<T> tmpList;
        tmpList = list;
        list = newlist;
        return tmpList;
    }
    Stack();
    ~Stack();
    void push(T data);
    void print(const char *separator) const;
    T pop();
    T &peek() {
        if (isEmpty()) throw std::out_of_range("Stack is empty");
        return top->data;
    };
    size_t getSize() const { return list.getSize(); };
    bool isEmpty() const { return list.isEmpty(); };
    void clear() { list.clear(); };
    template <typename T2>
    friend std::ostream &operator<<(std::ostream &out, const Stack<T2> &stack);
};

template <typename T>
void Stack<T>::print(const char *separator) const {
    list.print(separator);
};

template <typename T>
Stack<T>::Stack() : top(nullptr) {}

template <typename T>
Stack<T>::~Stack() {
    list.clear();
    top = nullptr;
};

template <typename T>
std::ostream &operator<<(std::ostream &out, const Stack<T> &stack) {
    out << stack.list;
    return out;
};

template <typename T>
void Stack<T>::push(T data) {
    list.insertAtBeginning(data);
    top = list.getHead();
};

template <typename T>
T Stack<T>::pop() {
    if (isEmpty())
        throw std::out_of_range("Stack is empty - cannot pop element!");
    T data = list.removeAtBeginning();
    top = list.getHead();
    return data;
};