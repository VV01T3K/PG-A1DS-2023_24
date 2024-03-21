#pragma once
#include <cstddef>
#include <initializer_list>
#include <iostream>
#include <utility>

template <typename T>
class List {
   private:
    class Node {
       public:
        T data;
        Node* next;
        Node* prev;
        Node() : data(T()), next(nullptr), prev(nullptr){};
        Node(const T& data, Node* next, Node* prev)
            : data(data), next(next), prev(prev){};
        Node(T&& data, Node* next, Node* prev)
            : data(std::move(data)), next(next), prev(prev){};
        ~Node(){};
    };
    Node* head;
    Node* tail;
    std::size_t size;

    Node* getNodeAt(size_t index) const;

   public:
    List();
    explicit List(std::initializer_list<T> list);
    List(const List& orig);
    List(List&& orig);
    List& operator=(const List& right);
    List& operator=(List&& right);
    ~List();
    std::size_t getSize() const { return size; };
    bool isEmpty() const { return size == 0; };
    template <typename U>
    void push_front(U&& data);
    T pop_front();
    template <typename U>
    void push_back(U&& data);
    T pop_back();
    template <typename U>
    void insert(U&& data, std::size_t index);
    T& operator[](size_t index);
    const T& operator[](size_t index) const;
    void print(const char* seperator = "><") const;
    template <typename U>
    friend std::ostream& operator<<(std::ostream& out, const List<U>& list);
    void clear();
    void swap(List& other);
    T& front() {
        if (isEmpty())
            throw std::out_of_range("List is empty and can't peek()");
        return head->data;
    };
    T& back() {
        if (isEmpty())
            throw std::out_of_range("List is empty and can't peekTail()");
        return tail->data;
    };
};

// typename to tell the compiler that SingleLinkedList<T>::Node is a type
template <typename T>
typename List<T>::Node* List<T>::getNodeAt(size_t index) const {
    if (index >= size) throw std::out_of_range("Index is out of range");
    Node* current;
    if (index < size / 2) {
        current = head;
        for (size_t i = 0; i < index; i++) current = current->next;
    } else {
        current = tail;
        for (size_t i = size - 1; i > index; i--) current = current->prev;
    }
    return current;
}

template <typename T>
List<T>::List() : head(nullptr), tail(nullptr), size(0){};

template <typename T>
List<T>::List(std::initializer_list<T> list)
    : head(nullptr), tail(nullptr), size(0) {
    for (const auto& data : list) push_back(data);
};

template <typename T>
List<T>::List(const List& orig) : head(nullptr), tail(nullptr), size(0) {
    for (Node* current = orig.head; current != nullptr; current = current->next)
        push_back(current->data);
};

template <typename T>
List<T>::List(List&& orig) : head(orig.head), tail(orig.tail), size(orig.size) {
    orig.head = nullptr;
    orig.tail = nullptr;
    orig.size = 0;
};

template <typename T>
List<T>& List<T>::operator=(const List& right) {
    List temp(right);
    swap(temp);
    return *this;
};

template <typename T>
List<T>& List<T>::operator=(List&& right) {
    swap(right);
    return *this;
};

template <typename T>
List<T>::~List() {
    if (!isEmpty()) clear();
};

template <typename T>
template <typename U>
void List<T>::push_front(U&& data) {
    head = new Node(std::forward<U>(data), head, nullptr);
    if (isEmpty())
        tail = head;
    else
        head->next->prev = head;
    size++;
};

template <typename T>
template <typename U>
void List<T>::push_back(U&& data) {
    if (isEmpty()) {
        push_front(std::forward<U>(data));
        return;
    }
    tail = new Node(std::forward<U>(data), nullptr, tail);
    tail->prev->next = tail;
    size++;
};

template <typename T>
T List<T>::pop_front() {
    if (isEmpty()) throw std::out_of_range("List is empty and can't pop()");
    T data = std::move(head->data);
    Node* oldHead = head;
    head = head->next;
    head->prev = nullptr;
    delete oldHead;
    size--;
    return data;
};

template <typename T>
T List<T>::pop_back() {
    if (isEmpty()) throw std::out_of_range("List is empty and can't popTail()");
    if (size == 1) return pop_front();
    T data = std::move(tail->data);
    Node* oldTail = tail;
    tail = tail->prev;
    tail->next = nullptr;
    delete oldTail;
    size--;
    return data;
};

template <typename T>
template <typename U>
void List<T>::insert(U&& data, size_t index) {
    if (index > size)
        throw std::out_of_range("Index is out of range and can't insert()");
    if (index == 0) {
        push_front(std::forward<U>(data));
        return;
    }
    Node* prevNode = getNodeAt(index - 1);
    prevNode->next = new Node(std::forward<U>(data), prevNode->next, prevNode);
    prevNode->next->next->prev = prevNode->next;
    size++;
};

template <typename T>
T& List<T>::operator[](size_t index) {
    return getNodeAt(index)->data;
};

template <typename T>
const T& List<T>::operator[](size_t index) const {
    return getNodeAt(index)->data;
};

template <typename T>
void List<T>::print(const char* seperator) const {
    if (isEmpty()) {
        std::cout << "EmptyList" << std::endl;
        return;
    }
    Node* current = head;
    while (current != nullptr) {
        std::cout << current->data;
        if (current->next != nullptr) std::cout << seperator;
        current = current->next;
    }
    std::cout << std::endl;
};

template <typename T>
std::ostream& operator<<(std::ostream& out, const List<T>& list) {
    if (list.isEmpty()) {
        out << "EmptyList";
    } else {
        typename List<T>::Node* current = list.head;
        while (current != nullptr) {
            out << current->data << " ";
            current = current->next;
        }
    }
    return out;
};

template <typename T>
void List<T>::clear() {
    while (head != nullptr) {
        Node* current = head;
        head = head->next;
        delete current;
    }
    head = tail = nullptr;
    size = 0;
};

template <typename T>
void List<T>::swap(List& other) {
    std::swap(head, other.head);
    std::swap(tail, other.tail);
    std::swap(size, other.size);
};