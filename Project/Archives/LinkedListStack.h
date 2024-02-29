// Project/Stack/test.h
#ifndef LinkedListStack_H
#define LinkedListStack_H

typedef struct Node {
    int data;
    struct Node *next;
} Node;

typedef struct Stack {
    int size;
    Node *top;
} Stack;

Stack *createStack();

void push(Stack *stack, int newData);

int pop(Stack *stack);

void deleteStack(Stack *stack);

void clearStack(Stack *stack);

int isStackEmpty(Stack *stack);

int getTop(Stack *stack);

int get(Stack *stack, int index);

#endif  // LinkedListStack_H