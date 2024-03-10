#include "Converter.h"

/**
 * The function `convertOneFormula` reads input tokens and converts them into
 * Reverse Polish Notation (RPN) using a stack and output queue.
 *
 * @return The function processes input tokens and
 * manipulates stacks and output lists based on certain conditions, but it does
 * not return any specific value or result.
 */
void Converter::convertOneFormula() {
    char str[MAX_STR_LENGTH];
    while (cin >> str) {
        if (str[0] == '.') break;
        Token token(str);
        if (token.type == NUMBER) {
            output.insertAtEnd(token);
        } else if (token.type == FUNCTION) {
            arg_counts.push(1);
            stack.push(token);
        } else if (token.type == OPERATOR) {
            while (!stack.isEmpty() && stack.peek().value != LEFT_BRACKET &&
                   (stack.peek().getPrecedence() > token.getPrecedence() ||
                    (stack.peek().getPrecedence() == token.getPrecedence() &&
                     token.associativity == LEFT))) {
                output.insertAtEnd(stack.pop());
            }
            stack.push(token);
        } else if (token.value == COMMA) {
            while (!stack.isEmpty() && stack.peek().value != LEFT_BRACKET) {
                output.insertAtEnd(stack.pop());
            }
            if (!arg_counts.isEmpty()) arg_counts.peek()++;
        } else if (token.value == LEFT_BRACKET) {
            stack.push(token);
        } else if (token.value == RIGHT_BRACKET) {
            while (!stack.isEmpty() && stack.peek().value != LEFT_BRACKET) {
                output.insertAtEnd(stack.pop());
            }
            if (stack.isEmpty()) {
                cerr << "Error: Unmatched parenthesis" << endl;
                return;
            }
            stack.pop();
            if (!stack.isEmpty() && stack.peek().type == FUNCTION) {
                output.insertAtEnd(stack.pop());
            }
        }
        if (!output.isEmpty() && !arg_counts.isEmpty() &&
            output.getTail()->data.type == FUNCTION &&
            output.getTail()->data.arg_count == -1) {
            output.getTail()->data.arg_count = arg_counts.pop();
        }
    }
    while (!stack.isEmpty()) {
        output.insertAtEnd(stack.pop());
    }
    output = stack.swapList(output);
}