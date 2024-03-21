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
            output.push_back(std::move(token));
        } else if (token.type == FUNCTION) {
            arg_counts.push(ONE);
            stack.push(std::move(token));
        } else if (token.type == OPERATOR) {
            while (!stack.isEmpty() && stack.peek().value != LEFT_BRACKET &&
                   (stack.peek().getPrecedence() > token.getPrecedence() ||
                    (stack.peek().getPrecedence() == token.getPrecedence() &&
                     token.associativity == LEFT))) {
                output.push_back(stack.pop());
            }
            stack.push(std::move(token));
        } else if (token.value == COMMA) {
            while (!stack.isEmpty() && stack.peek().value != LEFT_BRACKET) {
                output.push_back(stack.pop());
            }
            if (!arg_counts.isEmpty()) arg_counts.peek()++;
        } else if (token.value == LEFT_BRACKET) {
            stack.push(std::move(token));
        } else if (token.value == RIGHT_BRACKET) {
            while (!stack.isEmpty() && stack.peek().value != LEFT_BRACKET) {
                output.push_back(stack.pop());
            }
            stack.pop();
            if (!stack.isEmpty() && stack.peek().type == FUNCTION) {
                output.push_back(stack.pop());
            }
        }
        if (!output.isEmpty() && !arg_counts.isEmpty() &&
            output.back().type == FUNCTION && output.back().arg_count == -1) {
            output.back().arg_count = arg_counts.pop();
        }
    }
    getc(stdin);
    while (!stack.isEmpty()) {
        output.push_back(stack.pop());
    }
}

void Converter::calculate() {
    Token token = output.pop_back();
    if (token.type == Type::NUMBER) {
        output.push_back(token.value);
    } else {
        int a, b, c;
        switch (token.value) {
            case ADD:
                output.push_back(output.pop_back().value +
                                 output.pop_back().value);
                break;
            case SUBTRACT:
                a = output.pop_back().value;
                b = output.pop_back().value;
                output.push_back(b - a);
                break;
            case MULTIPLY:
                output.push_back(output.pop_back().value *
                                 output.pop_back().value);
                break;
            case DIVIDE:
                a = output.pop_back().value;
                b = output.pop_back().value;
                if (a == 0) {
                    printf("ERROR\n");
                    output.clear();
                    stack.clear();
                    arg_counts.clear();
                    return;
                }
                output.push_back(b / a);
                break;
            case IF:
                c = output.pop_back().value;
                b = output.pop_back().value;
                a = output.pop_back().value;
                output.push_back(a > 0 ? b : c);
                break;
            case NOT:
                a = output.pop_back().value;
                output.push_back(-a);
                break;
            case MAX:
                if (token.arg_count == 1) {
                    output.push_back(output.pop_back().value);
                    break;
                }
                while (token.arg_count-- > 1) {
                    a = output.pop_back().value;
                    b = output.pop_back().value;
                    output.push_back(a > b ? a : b);
                }
                break;
            case MIN:
                if (token.arg_count == 1) {
                    output.push_back(output.pop_back().value);
                    break;
                }
                while (token.arg_count-- > 1) {
                    a = output.pop_back().value;
                    b = output.pop_back().value;
                    output.push_back(a < b ? a : b);
                }
                break;
        }
    }
}