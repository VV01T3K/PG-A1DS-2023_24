#include "ONPcalc.h"

#include <ctype.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "../Stack/LinkedListStack.h"

enum Operator {
    ADD = '+',
    SUBTRACT = '-',
    MULTIPLY = '*',
    DIVIDE = '/',
};

int resloveIntCalculation(char operator, int a, int b) {
    switch (operator) {
        case ADD:
            return a + b;
        case SUBTRACT:
            return a - b;
        case MULTIPLY:
            return a * b;
        case DIVIDE:
            return a / b;
        default:
            return 0;
    }
}

int calculate(char* input) {
    Stack* stack = createStack();
    const char operators[] = "+-*/";

    int i = 0;

    while (input[i] != '\0') {
        char c = input[i];

        if (c == ' ') {
            i++;
            continue;
        }

        if (isdigit(c)) {
            push(stack, c - '0');
        } else if (strchr(operators, c)) {
            int a = pop(stack);
            int b = pop(stack);

            int result = resloveIntCalculation(c, a, b);

            push(stack, result);
        }
        i++;
    }

    return pop(stack);
}