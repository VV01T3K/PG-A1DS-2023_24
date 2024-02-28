// Project/Stack/test.h
#ifndef LinkedListStack_H
#define LinkedListStack_H

typedef struct {
    int data;
    struct Node *next;
} Node;

typedef struct Stack {
    int size;
    struct node *top;
} Stack;

Stack *createStack();

void push(Stack *stack, int newData);

int pop(Stack *stack);

void deleteStack(Stack *stack);

void clearStack(Stack *stack);

#endif  // LinkedListStack_H