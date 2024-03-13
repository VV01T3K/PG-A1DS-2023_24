#include "Token.h"

#include <iostream>

int Token::getPrecedence() const {
    if (type == OPERATOR) {
        switch (value) {
            case ADD:
            case SUBTRACT:
                return 1;
            case MULTIPLY:
            case DIVIDE:
                return 2;
            case IF:
            case NOT:
            case MAX:
            case MIN:
                return 3;
            default:
                return 4;
        }
    }
    return 0;
}

// Translaiting to token
Token::Token(const char* string) {
    if (isdigit(string[0])) {
        type = Type::NUMBER;
        value = atoi(string);
    } else {
        type = Type::OPERATOR;
        associativity = Associativity::LEFT;
        switch (string[0]) {
            case 'I':
                type = Type::FUNCTION;
                arg_count = -1;
                value = IF;
                break;
            case 'N':
                associativity = Associativity::RIGHT;
                value = NOT;
                break;
            case 'M':
                type = Type::FUNCTION;
                arg_count = -1;
                if (string[1] == 'A')
                    value = MAX;
                else
                    value = MIN;
                break;
            case ',':
            case '(':
            case ')':
                type = Type::NONE;
                value = string[0];
                break;
            default:
                value = string[0];
                break;
        }
    }
};

// Przeciążenie operatora << dla klasy Token
std::ostream& operator<<(std::ostream& out, const Token& token) {
    if (token.type == NUMBER) {
        out << token.value;
    } else {
        switch (token.value) {
            case IF:
                out << "IF";
                break;
            case NOT:
                out << 'N';
                break;
            case MAX:
                out << "MAX" << (int)token.arg_count;
                break;
            case MIN:
                out << "MIN" << (int)token.arg_count;
                break;
            default:
                out << (char)token.value;
                break;
        }
    }
    return out;
}