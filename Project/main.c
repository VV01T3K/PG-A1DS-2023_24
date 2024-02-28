#include <stdio.h>
#include <stdlib.h>

#include "Stack/LinkedListStack.h"

int main() {
    Stack *myStack = createStack();
    push(myStack, 1);
    push(myStack, 2);
    push(myStack, 3);
    printf("%d\n", pop(myStack));
    printf("%d\n", pop(myStack));
    printf("%d\n", pop(myStack));
    deleteStack(myStack);
    return 0;
}