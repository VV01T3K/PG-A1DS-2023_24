#include "DynamicSizeArrayStack.h"

#include <stdio.h>

Stack *createStack(int size) {
    Stack *stack = (Stack *)malloc(sizeof(Stack));
    stack->elements = (int *)malloc(size * sizeof(int));
    stack->top = -1;
    stack->max_size = size;
    return stack;
}

void clearStack(Stack *stack) { stack->top = -1; }

int isStackEmpty(Stack *stack) {
    if (stack->top == -1) return 1;
    return 0;
}

int isStackFull(Stack *stack) { return stack->top >= stack->max_size - 1; }

void push(Stack *stack, int newData) {
    if (isStackFull(stack)) {
        printf("Stack full\n");
        return;
    }
    stack->elements[++stack->top] = newData;
}

int pop(Stack *stack) {
    if (isStackEmpty(stack)) {
        printf("Stack empty.\n");
        return -1;
    }
    return stack->elements[stack->top--];
}

// This ** and NULL for easier debugging
void deleteStack(Stack **stack) {
    free((*stack)->elements);
    free(*stack);
    *stack = NULL;
}

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

// int main() {
//     Stack *stack = createStack(100);
//     // ...
//     deleteStack(&stack);
//     return 0;
// }