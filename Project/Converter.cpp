#include "Converter.h"

#include <cstdio>

#include "List.h"
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
        Token token(str);
        if (token.type == NUMBER) {
            output.put(std::move(token));
        } else if (token.type == FUNCTION) {
            arg_counts.push(ONE);
            stack.push(std::move(token));
        } else if (token.type == OPERATOR) {
            while (!stack.isEmpty() && stack.peek().value != LEFT_BRACKET &&
                   (stack.peek().getPrecedence() > token.getPrecedence() ||
                    (stack.peek().getPrecedence() == token.getPrecedence() &&
                     token.associativity == LEFT))) {
                output.put(stack.pop());
            }
            stack.push(std::move(token));
        } else if (token.value == COMMA) {
            while (!stack.isEmpty() && stack.peek().value != LEFT_BRACKET) {
                output.put(stack.pop());
            }
            if (!arg_counts.isEmpty()) arg_counts.peek()++;
        } else if (token.value == LEFT_BRACKET) {
            stack.push(std::move(token));
        } else if (token.value == RIGHT_BRACKET) {
            while (!stack.isEmpty() && stack.peek().value != LEFT_BRACKET) {
                output.put(stack.pop());
            }
            stack.pop();
            if (!stack.isEmpty() && stack.peek().type == FUNCTION) {
                output.put(stack.pop());
            }
        }
        if (!output.isEmpty() && !arg_counts.isEmpty() &&
            output.back().type == FUNCTION && output.back().arg_count == -1) {
            output.back().arg_count = arg_counts.pop();
        }
    }
    getc(stdin);
    while (!stack.isEmpty()) {
        output.put(stack.pop());
    }
    stack.swap(output);
}

void Converter::calculate(Token& token) {
    Token token = stack.pop();
    if (token.type == Type::NUMBER) {
        int_stack.push(token.value);
    } else {
        int a, b, c;
        if (!int_stack.isEmpty()) {
            token.print();
            int_stack.printInt();
        }
        switch (token.value) {
            case ADD:
                int_stack.push(int_stack.pop() + int_stack.pop());
                break;
            case SUBTRACT:
                a = int_stack.pop();
                b = int_stack.pop();
                int_stack.push(b - a);
                break;
            case MULTIPLY:
                int_stack.push(int_stack.pop() * int_stack.pop());
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