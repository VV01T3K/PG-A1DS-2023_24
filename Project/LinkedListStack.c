#include "LinkedListStack.h"

#include <stdlib.h>

Stack *createStack() {
    Stack *stack = (Stack *)malloc(sizeof(Stack));
    stack->size = 0;
    stack->top = NULL;
    return stack;
}

void push(Stack *stack, int newData) {
    Node *new_node = (Node *)malloc(sizeof(Node));
    new_node->data = newData;
    new_node->next = stack->top;
    stack->top = new_node;
    stack->size++;
}

int isStackEmpty(Stack *stack) {
    if (stack->size == 0) return 1;
    return 0;
}

int pop(Stack *stack) {
    if (isStackEmpty(stack)) return -1;
    Node *top_node = stack->top;
    const int data_tmp = top_node->data;
    stack->top = top_node->next;
    free(top_node);
    stack->size--;
    return data_tmp;
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
    const Node *top_node = stack->top;
    for (int i = 0; i < index; i++) {
        top_node = top_node->next;
    }
    return top_node->data;
}