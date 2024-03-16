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
 * final result of the calculations is printed to the console using `std::cout`
 * at the end of the method.
 */
void ONPcalc::calculate(Stack<Token, ForwardList>& stack) {
    while (!stack.isEmpty()) {
        Token token = stack.pop();
        if (token.type == Type::NUMBER) {
            calc_stack.push(token.value);
        } else {
            int a, b, c;
            if (!calc_stack.isEmpty()) {
                token.print();
                printf(" ");
                calc_stack.printInt(" ");
            }
            switch (token.value) {
                case ADD:
                    a = calc_stack.pop();
                    b = calc_stack.pop();
                    calc_stack.push(a + b);
                    break;
                case SUBTRACT:
                    a = calc_stack.pop();
                    b = calc_stack.pop();
                    calc_stack.push(b - a);
                    break;
                case MULTIPLY:
                    a = calc_stack.pop();
                    b = calc_stack.pop();
                    calc_stack.push(a * b);
                    break;
                case DIVIDE:
                    a = calc_stack.pop();
                    b = calc_stack.pop();
                    if (a == 0) {
                        std::cout << "ERROR" << std::endl;
                        calc_stack.clear();
                        stack.clear();
                        return;
                    }
                    calc_stack.push(b / a);
                    break;
                case IF:
                    c = calc_stack.pop();
                    b = calc_stack.pop();
                    a = calc_stack.pop();
                    calc_stack.push(a > 0 ? b : c);
                    break;
                case NOT:
                    a = calc_stack.pop();
                    calc_stack.push(-a);
                    break;
                case MAX:
                    if (token.arg_count == 0) break;
                    if (calc_stack.isEmpty()) {
                        throw std::invalid_argument("somthing no bueno");
                        break;
                    }
                    if (token.arg_count == 1) {
                        calc_stack.push(calc_stack.pop());
                        break;
                    }
                    while (token.arg_count-- > 1) {
                        a = calc_stack.pop();
                        b = calc_stack.pop();
                        calc_stack.push(a > b ? a : b);
                    }
                    break;
                case MIN:
                    if (token.arg_count == 0) break;
                    if (calc_stack.isEmpty()) {
                        throw std::invalid_argument("somthing no bueno");
                        break;
                    }
                    if (token.arg_count == 1) {
                        calc_stack.push(calc_stack.pop());
                        break;
                    }
                    while (token.arg_count-- > 1) {
                        a = calc_stack.pop();
                        b = calc_stack.pop();
                        calc_stack.push(a < b ? a : b);
                    }
                    break;
                default:
                    throw std::invalid_argument("Invalid operator");
            }
        }
    }
    std::cout << calc_stack.pop() << std::endl;
};