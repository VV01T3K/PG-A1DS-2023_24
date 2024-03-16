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

/**
 * The `Token` class is defined with five member variables:
 * - `value`: an integer representing the value of a token
 * - `type`: an enum `Type` representing the type of a token
 * - `associativity`: an enum `Associativity` representing the associativity of
 * an operator token
 * - `arg_count`: a short integer representing the number of arguments that the
 * token takes
 */
class Token {
   public:
    int value;
    Type type;
    Associativity associativity;
    short arg_count;
    /**
     * The function overloads the << operator to output a Token object based on
     * its type and value.
     *
     * @return The overloaded << operator function is returning a reference to
     * the std::ostream object 'out'.
     */
    friend std::ostream& operator<<(std::ostream& out, const Token& token);

    /**
     * Constructs a Token with the specified type, value, and argument count.
     *
     * @param type The type of the token.
     * @param value The value of the token.
     * @param arg_count The number of arguments that the token takes. Defaults
     * to -1.
     */
    Token(Type type, int value, short arg_count = -1)
        : type(type), value(value), arg_count(arg_count), associativity(LEFT){};

    /**
     * Default constructor. Constructs a Token of type NUMBER, with a value of 0
     * and argument count of -1.
     */
    Token()
        : type(Type::NUMBER), value(0), arg_count(-1), associativity(LEFT){};

    /**
     * The Token constructor parses a given string to determine the type and
     * value of the token.
     *
     * @param string The constructor checks the first character of the `string`
     * to determine the type of the token (whether it's a number or an
     * operator/function).
     */
    Token(const char* string);

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
    int getPrecedence() const;
    void print() const;
};