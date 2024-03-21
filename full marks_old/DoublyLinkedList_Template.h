#pragma once
#include <cstddef>
#include <iostream>
#include <stdexcept>

// !! copying and assignig is broken

template <typename T>
class Node {
   public:
    T data;
    Node<T> *next;
    Node<T> *prev;
    explicit Node(T data) : data(data), next(nullptr), prev(nullptr) {}
};

template <typename T>
class DoublyLinkedList {
    Node<T> *head;
    Node<T> *tail;
    size_t size;

   public:
    Node<T> *getHead() const { return head; }
    Node<T> *getTail() const { return tail; }
    DoublyLinkedList();
    ~DoublyLinkedList();
    void insertAtPos(size_t pos, T data);
    T removeAtPos(size_t pos);
    void insertAtBeginning(T data);
    T removeAtBeginning();
    void insertAtEnd(T data);
    T removeAtEnd();
    size_t getSize() const;
    bool isEmpty() const;
    T &getAtPos(size_t pos);
    T &getAtBeginning();
    T &getAtEnd();
    void clear();
    void print(const char *separator) const;
    template <typename T2>
    friend std::ostream &operator<<(std::ostream &out,
                                    const DoublyLinkedList<T2> &list);
};

template <typename T>
DoublyLinkedList<T>::DoublyLinkedList()
    : size(0), head(nullptr), tail(nullptr) {}

template <typename T>
DoublyLinkedList<T>::~DoublyLinkedList() {
    clear();
    head = nullptr;
    tail = nullptr;
};

template <typename T>
void DoublyLinkedList<T>::insertAtBeginning(T data) {
    Node<T> *newNode = new Node<T>(data);
    if (isEmpty()) {
        head = tail = newNode;
    } else {
        newNode->next = head;
        head->prev = newNode;
        head = newNode;
    }
    size++;
};

template <typename T>
void DoublyLinkedList<T>::insertAtEnd(T data) {
    Node<T> *newNode = new Node<T>(data);
    if (isEmpty()) {
        head = tail = newNode;
    } else {
        tail->next = newNode;
        newNode->prev = tail;
        tail = newNode;
    }
    size++;
};

template <typename T>
T DoublyLinkedList<T>::removeAtBeginning() {
    if (isEmpty()) throw std::out_of_range("List is empty");
    Node<T> *tmp = head;
    T data = tmp->data;
    head = head->next;
    delete tmp;
    size--;
    return data;
};

template <typename T>
T DoublyLinkedList<T>::removeAtEnd() {
    if (isEmpty()) throw std::out_of_range("List is empty");
    Node<T> *tmp = tail;
    T data = tmp->data;
    tail = tail->prev;
    delete tmp;
    size--;
    return data;
};

template <typename T>
void DoublyLinkedList<T>::insertAtPos(size_t pos, T data) {
    if (pos > getSize()) throw std::out_of_range("Index is out of range");
    Node<T> *newNode = new Node<T>(data);
    if (isEmpty()) {
        head = tail = newNode;
        size++;
    } else if (pos == 0) {
        insertAtBeginning(data);
    } else if (pos >= getSize()) {
        insertAtEnd(data);
    } else {
        Node<T> *tmp;
        if (pos < getSize() / 2) {
            tmp = head;
            for (size_t i = 0; i < pos; i++) tmp = tmp->next;
        } else {
            tmp = tail;
            for (size_t i = getSize() - 1; i > pos; i--) tmp = tmp->prev;
        }
        newNode->next = tmp;
        newNode->prev = tmp->prev;
        tmp->prev->next = newNode;
        tmp->prev = newNode;
        size++;
    }
};

template <typename T>
T DoublyLinkedList<T>::removeAtPos(size_t pos) {
    if (isEmpty()) throw std::out_of_range("List is empty");
    if (pos >= getSize()) throw std::out_of_range("Index is out of range");

    Node<T> *tmp;
    T data;
    if (pos == 0) {
        data = removeAtBeginning();
    } else if (pos == getSize() - 1) {
        data = removeAtEnd();
    } else {
        if (pos < getSize() / 2) {
            tmp = head;
            for (size_t i = 0; i < pos; i++) tmp = tmp->next;
        } else {
            tmp = tail;
            for (size_t i = getSize() - 1; i > pos; i--) tmp = tmp->prev;
        }
        data = tmp->data;
        tmp->prev->next = tmp->next;
        tmp->next->prev = tmp->prev;
        delete tmp;
        size--;
    }
    return data;
};

template <typename T>
void DoublyLinkedList<T>::print(const char *separator) const {
    if (isEmpty()) std::cerr << "List is empty (print)" << std::endl;
    Node<T> *tmp = getHead();
    while (tmp != nullptr) {
        std::cout << tmp->data;
        if (tmp->next != nullptr) {
            std::cout << separator;
        }
        tmp = tmp->next;
    }
    std::cout << std::endl;
};

template <typename T>
std::ostream &operator<<(std::ostream &out, const DoublyLinkedList<T> &list) {
    if (list.isEmpty()) std::cerr << "List is empty (<<)";
    Node<T> *tmp = list.getHead();
    while (tmp != nullptr) {
        out << tmp->data;
        if (tmp->next != nullptr) {
            out << " ";
        }
        tmp = tmp->next;
    }
    return out;
};

template <typename T>
size_t DoublyLinkedList<T>::getSize() const {
    return size;
};

template <typename T>
bool DoublyLinkedList<T>::isEmpty() const {
    return size == 0;
};

template <typename T>
T &DoublyLinkedList<T>::getAtPos(size_t pos) {
    if (isEmpty()) throw std::out_of_range("List is empty");
    if (pos >= getSize()) throw std::out_of_range("Index is out of range");
    Node<T> *tmp = head;
    for (size_t i = 0; i < pos; i++) tmp = tmp->next;
    return tmp->data;
};

template <typename T>
T &DoublyLinkedList<T>::getAtBeginning() {
    if (isEmpty()) throw std::out_of_range("List is empty");
    return head->data;
};

template <typename T>
T &DoublyLinkedList<T>::getAtEnd() {
    if (isEmpty()) throw std::out_of_range("List is empty");
    return tail->data;
};

template <typename T>
void DoublyLinkedList<T>::clear() {
    while (head != nullptr) {
        Node<T> *tmp = head;
        head = head->next;
        delete tmp;
    }
    head = nullptr;
    tail = nullptr;
    size = 0;
};