#include "ONPcalc.h"

#include <cstdio>

#include "ForwardList.h"
#include "Stack.h"
#include "Token.h"

/**
 * The function `calculate` processes a stack of tokens representing a Reverse
 * Polish Notation expression and performs arithmetic operations based on the
 * tokens.
 *
 * @param stack The `stack` parameter is a stack data structure that holds
 * tokens representing numbers and operators in the RPN expression.
 *
 * @return The `calculate` method does not return any value. It performs
 * calculations on the input stack and outputs the result to the console. The
 * final result of the calculations is printed to the console using `std::cout`
 * at the end of the method.
 */
void ONPcalc::calculate(Stack<Token, ForwardList>& stack) {
    while (!stack.isEmpty()) {
        Token token = stack.pop();
        if (token.type == Type::NUMBER) {
            int_stack.push(token.value);
        } else {
            int a, b, c;
            if (!int_stack.isEmpty()) {
                token.print();
                printf(" ");
                int_stack.printInt(" ");
            }
            switch (token.value) {
                case ADD:
                    a = int_stack.pop();
                    b = int_stack.pop();
                    int_stack.push(a + b);
                    break;
                case SUBTRACT:
                    a = int_stack.pop();
                    b = int_stack.pop();
                    int_stack.push(b - a);
                    break;
                case MULTIPLY:
                    a = int_stack.pop();
                    b = int_stack.pop();
                    int_stack.push(a * b);
                    break;
                case DIVIDE:
                    a = int_stack.pop();
                    b = int_stack.pop();
                    if (a == 0) {
                        printf("ERROR\n");
                        int_stack.clear();
                        stack.clear();
                        return;
                    }
                    int_stack.push(b / a);
                    break;
                case IF:
                    c = int_stack.pop();
                    b = int_stack.pop();
                    a = int_stack.pop();
                    int_stack.push(a > 0 ? b : c);
                    break;
                case NOT:
                    a = int_stack.pop();
                    int_stack.push(-a);
                    break;
                case MAX:
                    if (token.arg_count == 1) {
                        int_stack.push(int_stack.pop());
                        break;
                    }
                    while (token.arg_count-- > 1) {
                        a = int_stack.pop();
                        b = int_stack.pop();
                        int_stack.push(a > b ? a : b);
                    }
                    break;
                case MIN:
                    if (token.arg_count == 1) {
                        int_stack.push(int_stack.pop());
                        break;
                    }
                    while (token.arg_count-- > 1) {
                        a = int_stack.pop();
                        b = int_stack.pop();
                        int_stack.push(a < b ? a : b);
                    }
                    break;
            }
        }
    }
    printf("%d\n", int_stack.pop());
};