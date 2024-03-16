#pragma once
#include <cstdio>
#include <initializer_list>
#include <utility>

template <typename T>
class ForwardList {
   private:
    class Node {
       public:
        T data;
        Node* next;
        Node() : data(T()), next(nullptr){};
        Node(const T& data, Node* next) : data(data), next(next){};
        Node(T&& data, Node* next) : data(std::move(data)), next(next){};
        ~Node(){};
    };
    Node* head;
    Node* tail;
    std::size_t size;

    Node* getNodeAt(size_t index) const;

   public:
    ForwardList();
    explicit ForwardList(std::initializer_list<T> list);
    ForwardList(const ForwardList& orig);
    ForwardList(ForwardList&& orig);
    ForwardList& operator=(const ForwardList& right);
    ForwardList& operator=(ForwardList&& right);
    ~ForwardList();
    std::size_t getSize() const { return size; };
    bool isEmpty() const { return size == 0; };
    template <typename U>
    void push_front(U&& data);
    T pop_front();
    template <typename U>
    void push_back(U&& data);
    // pop_back isnt happening
    template <typename U>
    void insert(U&& data, std::size_t index);
    T& operator[](std::size_t index);
    const T& operator[](std::size_t index) const;
    void print(const char* seperator = ">") const;
    void printInt() const;
    void printToken() const;
    void clear();
    void swap(ForwardList& other);
    T& front() { return head->data; };
    T& back() { return tail->data; };
};

// typename to tell the compiler that SingleLinkedList<T>::Node is a type
template <typename T>
typename ForwardList<T>::Node* ForwardList<T>::getNodeAt(size_t index) const {
    Node* current = head;
    for (std::size_t i = 0; i < index; i++) current = current->next;
    return current;
}

template <typename T>
ForwardList<T>::ForwardList() : head(nullptr), tail(nullptr), size(0){};

template <typename T>
ForwardList<T>::ForwardList(std::initializer_list<T> list)
    : head(nullptr), tail(nullptr), size(0) {
    for (const auto& data : list) push_back(data);
};

template <typename T>
ForwardList<T>::ForwardList(const ForwardList& orig)
    : head(nullptr), tail(nullptr), size(0) {
    for (Node* current = orig.head; current != nullptr; current = current->next)
        push_back(current->data);
};

template <typename T>
ForwardList<T>::ForwardList(ForwardList&& orig)
    : head(orig.head), tail(orig.tail), size(orig.size) {
    orig.head = nullptr;
    orig.tail = nullptr;
    orig.size = 0;
};

template <typename T>
ForwardList<T>& ForwardList<T>::operator=(const ForwardList& right) {
    ForwardList temp(right);
    swap(temp);
    return *this;
};

template <typename T>
ForwardList<T>& ForwardList<T>::operator=(ForwardList&& right) {
    swap(right);
    return *this;
};

template <typename T>
ForwardList<T>::~ForwardList() {
    if (!isEmpty()) clear();
};

template <typename T>
template <typename U>
void ForwardList<T>::push_front(U&& data) {
    head = new Node(std::forward<U>(data), head);
    if (isEmpty()) tail = head;
    size++;
};

template <typename T>
template <typename U>
void ForwardList<T>::push_back(U&& data) {
    if (isEmpty()) {
        push_front(std::forward<U>(data));
        return;
    }
    tail->next = new Node(std::forward<U>(data), nullptr);
    tail = tail->next;
    size++;
};

template <typename T>
T ForwardList<T>::pop_front() {
    T data = std::move(head->data);
    Node* oldHead = head;
    head = head->next;
    delete oldHead;
    size--;
    return data;
};

template <typename T>
template <typename U>
void ForwardList<T>::insert(U&& data, size_t index) {
    if (index == 0) {
        push_front(std::forward<U>(data));
        return;
    }
    Node* prevNode = getNodeAt(index - 1);
    prevNode->next = new Node(std::forward<U>(data), prevNode->next);
    size++;
};

template <typename T>
T& ForwardList<T>::operator[](size_t index) {
    return getNodeAt(index)->data;
};

template <typename T>
const T& ForwardList<T>::operator[](size_t index) const {
    return getNodeAt(index)->data;
};

template <typename T>
void ForwardList<T>::printInt() const {
    Node* current = head;
    if (current != nullptr) {
        printf("%d", current->data);
        current = current->next;
    }
    while (current != nullptr) {
        printf(" %d", current->data);
        current = current->next;
    }
    printf("\n");
};

template <typename T>
void ForwardList<T>::printToken() const {
    Node* current = head;
    if (current != nullptr) {
        current->data.print();
        current = current->next;
    }
    while (current != nullptr) {
        current->data.print();
        current = current->next;
    }
    printf("\n");
};

template <typename T>
void ForwardList<T>::clear() {
    while (head != nullptr) {
        Node* current = head;
        head = head->next;
        delete current;
    }
    head = tail = nullptr;
    size = 0;
};

template <typename T>
void ForwardList<T>::swap(ForwardList& other) {
    std::swap(head, other.head);
    std::swap(tail, other.tail);
    std::swap(size, other.size);
};