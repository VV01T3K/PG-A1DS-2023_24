#include "LinkedListStack.h"

#include <stdlib.h>

Stack *createStack() {
    Stack *stack = (Stack *)malloc(sizeof(Stack));
    stack->size = 0;
    stack->top = NULL;
    return stack;
}

void push(Stack *stack, int newData) {
    Node *node = (Node *)malloc(sizeof(Node));
    node->data = newData;
    node->next = stack->top;
    stack->top = node;
    stack->size++;
}

int pop(Stack *stack) {
    Node *node = stack->top;
    int data = node->data;
    stack->top = node->next;
    free(node);
    stack->size--;
    return data;
}

void clearStack(Stack *stack) {
    while (stack->size > 0) {
        pop(stack);
    }
    stack->top = NULL;
    stack->size = 0;
}

void deleteStack(Stack *stack) {
    clearStack(stack);
    free(stack);
}