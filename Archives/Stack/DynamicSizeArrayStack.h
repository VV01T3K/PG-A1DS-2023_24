#ifndef STACK_H
#define STACK_H

typedef struct {
    int *elements;
    int top;
    int max_size;
} Stack;

Stack *createStack(int size);
void clearStack(Stack *stack);
int isStackEmpty(Stack *stack);
int isStackFull(Stack *stack);
void push(Stack *stack, int newData);
int pop(Stack *stack);
void deleteStack(Stack **stack);
int getTop(Stack *stack);
int get(Stack *stack, int index);

#endif  // STACK_H