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

int isStackEmpty(Stack *stack) {
    if (stack->size == 0) return 1;
    return 0;
}

int pop(Stack *stack) {
    Node *node = stack->top;
    if (isStackEmpty(stack)) return -1;
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

int getTop(Stack *stack) {
    if (isStackEmpty(stack)) return -1;
    return stack->top->data;
}

int get(Stack *stack, int index) {
    if (index < 0 || index >= stack->size) return -1;
    Node *node = stack->top;
    for (int i = 0; i < index; i++) {
        node = node->next;
    }
    return node->data;
}