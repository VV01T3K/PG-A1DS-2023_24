#include <stdio.h>
#include <stdlib.h>

#define MAX_STACK_SIZE 100

typedef struct {
    int elements[MAX_STACK_SIZE];
    int top;
} Stack;

void clearStack(Stack *stack) { stack->top = -1; }

int isStackEmpty(Stack *stack) {
    if (stack->top == -1) return 1;
    return 0;
}

int isStackFull(Stack *stack) { return stack->top >= MAX_STACK_SIZE - 1; }

void push(Stack *stack, int newData) {
    if (isStackFull(stack)) {
        printf("Stack is full\n");
        return;
    }
    stack->elements[++stack->top] = newData;
}

int pop(Stack *stack) {
    if (isStackEmpty(stack)) {
        printf("Stack is empty. Cannot pop.\n");
        return -1;
    }
    return stack->elements[stack->top--];
}

// for dynamic stack???
// void deleteStack(Stack *stack) { free(stack); }

int getTop(Stack *stack) {
    if (isStackEmpty(stack)) return -1;
    return stack->elements[stack->top];
}

int get(Stack *stack, int index) {
    if (index < 0 || index > stack->top) {
        printf("Index out of range\n");
        return -1;
    }
    return stack->elements[index];
}