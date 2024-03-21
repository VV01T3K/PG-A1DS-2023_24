#include "Converter.h"

#include <cstdio>

#include "ForwardList.h"
#include "Stack.h"
#include "Token.h"

#define MAX_TOKEN_LENGTH 15

void Converter::readToken(char* str) {
    int i = 0;
    char c = '\0';
    while (c != ' ' && c != '\n') {
        str[i++] = c = (char)getc(stdin);
    }
    str[i - 1] = '\0';
}

/**
 * The function `convertOneFormula` reads input tokens and converts them into
 * Reverse Polish Notation (RPN) using a stack and output queue.
 *
 * @return The function processes input tokens and
 * manipulates stacks and output lists based on certain conditions, but it does
 * not return any specific value or result.
 */
void Converter::convertOneFormula() {
    char str[MAX_TOKEN_LENGTH];
    const short ONE = 1;
    while (true) {
        readToken(str);
        if (str[0] == '.') break;
        if (divideByZero) continue;
        Token token(str);
        if (token.type == NUMBER) {
            output.push(token);
        } else if (token.type == FUNCTION) {
            arg_counts.push(ONE);
            stack.push(token);
        } else if (token.type == OPERATOR) {
            while (!stack.isEmpty() && stack.peek().value != LEFT_BRACKET &&
                   (stack.peek().getPrecedence() > token.getPrecedence() ||
                    (stack.peek().getPrecedence() == token.getPrecedence() &&
                     token.associativity == LEFT))) {
                output.push(stack.pop());
                calculate();
            }
            stack.push(token);
        } else if (token.value == COMMA) {
            while (!stack.isEmpty() && stack.peek().value != LEFT_BRACKET) {
                output.push(stack.pop());
                calculate();
            }
            if (!arg_counts.isEmpty()) arg_counts.peek()++;
        } else if (token.value == LEFT_BRACKET) {
            stack.push(token);
        } else if (token.value == RIGHT_BRACKET) {
            while (!stack.isEmpty() && stack.peek().value != LEFT_BRACKET) {
                output.push(stack.pop());
                calculate();
            }
            stack.pop();
            if (!stack.isEmpty() && stack.peek().type == FUNCTION) {
                output.push(stack.pop());
                calculate();
            }
        }
        if (!output.isEmpty() && !arg_counts.isEmpty() &&
            output.peek().type == FUNCTION && output.peek().arg_count == -1) {
            output.peek().arg_count = arg_counts.pop();
            calculate();
        }
    }
    getc(stdin);
    while (!stack.isEmpty()) {
        output.push(stack.pop());
        calculate();
    }
    if (!divideByZero) printf("%d\n", output.pop().value);
    output.clear();
    arg_counts.clear();
    stack.clear();
    divideByZero = false;
}

void Converter::calculate() {
    if (output.isEmpty()) return;
    if (output.peek().type == FUNCTION && output.peek().arg_count == -1) {
        return;
    }
    if (divideByZero) return;
    Token token = output.pop();
    if (token.type == Type::NUMBER) {
        output.push(token.value);
    } else {
        int a, b, c;
        switch (token.value) {
            case ADD:
                a = output.pop().value;
                b = output.pop().value;
                output.push(a + b);
                break;
            case SUBTRACT:
                a = output.pop().value;
                b = output.pop().value;
                output.push(b - a);
                break;
            case MULTIPLY:
                output.push(output.pop().value * output.pop().value);
                break;
            case DIVIDE:
                a = output.pop().value;
                if (a == 0) {
                    printf("ERROR\n");
                    divideByZero = true;
                    return;
                }
                b = output.pop().value;
                output.push(b / a);
                break;
            case IF:
                c = output.pop().value;
                b = output.pop().value;
                a = output.pop().value;
                output.push(a > 0 ? b : c);
                break;
            case NOT:
                a = output.pop().value;
                output.push(-a);
                break;
            case MAX:
                if (token.arg_count == 1) {
                    output.push(output.pop().value);
                    break;
                }
                while (token.arg_count-- > 1) {
                    a = output.pop().value;
                    b = output.pop().value;
                    output.push(a > b ? a : b);
                }
                break;
            case MIN:
                if (token.arg_count == 1) {
                    output.push(output.pop().value);
                    break;
                }
                while (token.arg_count-- > 1) {
                    a = output.pop().value;
                    b = output.pop().value;
                    output.push(a < b ? a : b);
                }
                break;
        }
    }
}