#include "Token.h"

#include <cctype>
#include <cstdio>
#include <cstdlib>
#include <utility>

// Copy constructor
Token::Token(const Token& orig)
    : value(orig.value),
      type(orig.type),
      associativity(orig.associativity),
      arg_count(orig.arg_count) {}

// Move constructor
Token::Token(Token&& orig)
    : value(std::move(orig.value)),
      type(std::move(orig.type)),
      associativity(std::move(orig.associativity)),
      arg_count(std::move(orig.arg_count)) {}

/**
 * The function `getPrecedence` returns the precedence level of an operator
 * token.
 *
 * @return The `getPrecedence` function returns an integer value
 * representing the precedence of the token. If the token type is an
 * operator, it checks the value of the operator and returns a precedence
 * value based on the operator type. If the token is not an operator, it
 * returns 0.
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
                arg_count = 0;
                value = IF;
                break;
            case 'N':
                associativity = Associativity::RIGHT;
                value = NOT;
                break;
            case 'M':
                type = Type::FUNCTION;
                arg_count = 0;
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

void Token::print() const {
    if (type == NUMBER) {
        printf("%d ", value);
    } else {
        switch (value) {
            case IF:
                printf("IF ");
                break;
            case NOT:
                printf("N ");
                break;
            case MAX:
                printf("MAX%d ", arg_count);
                break;
            case MIN:
                printf("MIN%d ", arg_count);
                break;
            default:
                printf("%c ", (char)value);
                break;
        }
    }
}