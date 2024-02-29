#ifndef STACK_H
#define STACK_H

#define MAX_STACK_SIZE 100

typedef struct {
    int elements[MAX_STACK_SIZE];
    int top;
} Stack;

void clearStack(Stack *stack);
int isStackEmpty(Stack *stack);
int isStackFull(Stack *stack);
void push(Stack *stack, int newData);
int pop(Stack *stack);
int getTop(Stack *stack);
int get(Stack *stack, int index);

#endif  // STACK_H