#pragma once
#include <iostream>
enum Operands : char {
    ADD = '+',
    SUBTRACT = '-',
    MULTIPLY = '*',
    DIVIDE = '/',
    IF = '?',
    NOT = '!',
    MAX = '>',
    MIN = '<',
    LEFT_BRACKET = '(',
    RIGHT_BRACKET = ')',
    COMMA = ',',
};
enum Type : char { NONE, NUMBER, OPERATOR, FUNCTION };
enum Associativity : char { LEFT, RIGHT };
class Token {
   public:
    int value;
    Type type;
    Associativity associativity;
    short arg_count;
    friend std::ostream& operator<<(std::ostream& out, const Token& token);
    Token(Type type, int value, short arg_count = -1)
        : type(type), value(value), arg_count(arg_count), associativity(LEFT){};
    Token()
        : type(Type::NUMBER), value(0), arg_count(-1), associativity(LEFT){};
    Token(const char* string);
    Token(int value)
        : type(Type::NUMBER),
          value(value),
          arg_count(-1),
          associativity(LEFT){};
    int getPrecedence() const;
};