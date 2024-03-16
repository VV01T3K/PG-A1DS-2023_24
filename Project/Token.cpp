#include "Token.h"

#include <iostream>

/**
 * The function `getPrecedence` returns the precedence level of an operator
 * token.
 *
 * @return The `getPrecedence` function returns an integer value representing
 * the precedence of the token. If the token type is an operator, it checks the
 * value of the operator and returns a precedence value based on the operator
 * type. If the token is not an operator, it returns 0.
 */
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
/**
 * The Token constructor parses a given string to determine the type and value
 * of the token.
 *
 * @param string The constructor checks the first character of the `string`
 * to determine the type of the token (whether it's a number or an
 * operator/function).
 */
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
/**
 * The function overloads the << operator to output a Token object based on its
 * type and value.
 *
 * @return The overloaded << operator function is returning a reference to the
 * std::ostream object 'out'.
 */
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

void Token::print() const {
    if (type == NUMBER) {
        printf("%d", value);
    } else {
        switch (value) {
            case IF:
                printf("IF");
                break;
            case NOT:
                printf("N");
                break;
            case MAX:
                printf("MAX%d", (int)arg_count);
                break;
            case MIN:
                printf("MIN%d", (int)arg_count);
                break;
            default:
                printf("%c", (char)value);
                break;
        }
    }
}