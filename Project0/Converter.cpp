#include "Converter.h"

// 16 wrong
void Converter::convertOneFormula() {
    char str[MAX_STR_LENGTH];
    while (cin >> str) {
        if (str[0] == '.') break;
        if (divideByZero) continue;
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
                calculate();
            }
            stack.push(token);
        } else if (token.value == COMMA) {
            while (!stack.isEmpty() && stack.peek().value != LEFT_BRACKET) {
                output.insertAtEnd(stack.pop());
                calculate();
            }
            if (!arg_counts.isEmpty()) arg_counts.peek()++;
        } else if (token.value == LEFT_BRACKET) {
            stack.push(token);
        } else if (token.value == RIGHT_BRACKET) {
            while (!stack.isEmpty() && stack.peek().value != LEFT_BRACKET) {
                output.insertAtEnd(stack.pop());
                calculate();
            }
            if (stack.isEmpty()) {
                cerr << "Error: Unmatched parenthesis" << endl;
                return;
            }
            stack.pop();
            if (!stack.isEmpty() && stack.peek().type == FUNCTION) {
                output.insertAtEnd(stack.pop());
                calculate();
            }
        }
        if (!output.isEmpty() && !arg_counts.isEmpty() &&
            output.getTail()->data.type == FUNCTION &&
            output.getTail()->data.arg_count == -1) {
            output.getTail()->data.arg_count = arg_counts.pop();
            calculate();
        }
    }
    while (!stack.isEmpty()) {
        output.insertAtEnd(stack.pop());
        calculate();
    }
    if (!divideByZero) cout << output << endl;
    output.clear();
    arg_counts.clear();
    stack.clear();
    divideByZero = false;
}

void Converter::calculate() {
    if (output.isEmpty()) return;
    if (output.getTail()->data.type == FUNCTION &&
        output.getTail()->data.arg_count == -1) {
        return;
    }
    if (divideByZero) return;
    Token token = output.removeAtEnd();
    int a, b, c;
    switch (token.value) {
        case ADD:
            a = output.removeAtEnd().value;
            b = output.removeAtEnd().value;
            output.insertAtEnd(a + b);
            break;
        case SUBTRACT:
            a = output.removeAtEnd().value;
            b = output.removeAtEnd().value;
            output.insertAtEnd(b - a);
            break;
        case MULTIPLY:
            a = output.removeAtEnd().value;
            b = output.removeAtEnd().value;
            output.insertAtEnd(a * b);
            break;
        case DIVIDE:
            a = output.removeAtEnd().value;
            b = output.removeAtEnd().value;
            if (a == 0) {
                divideByZero = true;
                std::cout << "ERROR" << std::endl;
                return;
            }
            output.insertAtEnd(b / a);
            break;
        case IF:
            c = output.removeAtEnd().value;
            b = output.removeAtEnd().value;
            a = output.removeAtEnd().value;
            output.insertAtEnd(a > 0 ? b : c);
            break;
        case NOT:
            a = output.removeAtEnd().value;
            output.insertAtEnd(-a);
            break;
        case MAX:
            if (token.arg_count == 0) break;
            if (token.arg_count == 1) {
                output.insertAtEnd(output.removeAtEnd().value);
                break;
            }
            while (token.arg_count-- > 1) {
                a = output.removeAtEnd().value;
                b = output.removeAtEnd().value;
                output.insertAtEnd(a > b ? a : b);
            }
            break;
        case MIN:
            if (token.arg_count == 0) break;
            if (token.arg_count == 1) {
                output.insertAtEnd(output.removeAtEnd().value);
                break;
            }
            while (token.arg_count-- > 1) {
                a = output.removeAtEnd().value;
                b = output.removeAtEnd().value;
                output.insertAtEnd(a < b ? a : b);
            }
            break;
        default:
            throw std::invalid_argument("Invalid operator");
    }
};