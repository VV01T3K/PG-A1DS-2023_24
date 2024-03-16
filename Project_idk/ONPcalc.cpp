#include "ONPcalc.h"

#include <iostream>

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
 * final result of the calculations is printed to the console using `printf`
 * at the end of the method.
 */
void ONPcalc::calculate(Stack<Token>& stack) {
    while (!stack.isEmpty()) {
        Token token = stack.pop();
        if (token.type == Type::NUMBER) {
            tmp_stack.push(token.value);
        } else {
            int a, b, c;
            if (!tmp_stack.isEmpty()) {
                token.print();
                printf(" ");
                tmp_stack.printINT(" ");
            }
            switch (token.value) {
                case ADD:
                    a = tmp_stack.pop();
                    b = tmp_stack.pop();
                    tmp_stack.push(a + b);
                    break;
                case SUBTRACT:
                    a = tmp_stack.pop();
                    b = tmp_stack.pop();
                    tmp_stack.push(b - a);
                    break;
                case MULTIPLY:
                    a = tmp_stack.pop();
                    b = tmp_stack.pop();
                    tmp_stack.push(a * b);
                    break;
                case DIVIDE:
                    a = tmp_stack.pop();
                    b = tmp_stack.pop();
                    if (a == 0) {
                        printf("ERROR\n");
                        tmp_stack.clear();
                        stack.clear();
                        return;
                    }
                    tmp_stack.push(b / a);
                    break;
                case IF:
                    c = tmp_stack.pop();
                    b = tmp_stack.pop();
                    a = tmp_stack.pop();
                    tmp_stack.push(a > 0 ? b : c);
                    break;
                case NOT:
                    a = tmp_stack.pop();
                    tmp_stack.push(-a);
                    break;
                case MAX:
                    if (token.arg_count == 1) {
                        tmp_stack.push(tmp_stack.pop());
                        break;
                    }
                    while (token.arg_count-- > 1) {
                        a = tmp_stack.pop();
                        b = tmp_stack.pop();
                        tmp_stack.push(a > b ? a : b);
                    }
                    break;
                case MIN:
                    if (token.arg_count == 1) {
                        tmp_stack.push(tmp_stack.pop());
                        break;
                    }
                    while (token.arg_count-- > 1) {
                        a = tmp_stack.pop();
                        b = tmp_stack.pop();
                        tmp_stack.push(a < b ? a : b);
                    }
                    break;
                default:
                    throw std::invalid_argument("Invalid operator");
            }
        }
    }
    printf("%d\n", tmp_stack.pop());
};