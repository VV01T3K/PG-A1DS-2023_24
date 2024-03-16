#pragma once
#include <iostream>

#include "Containers/ForwardList.h"
#include "Containers/Stack.h"
#include "Token.h"

/**
 * The `ONPcalc` class is defined with one private member variable:
 * - `tmp_stack`: a `Stack` of `int` objects used for temporary calculations
 */
class ONPcalc {
   private:
    Stack<int, ForwardList> calc_stack;

   public:
    /**
     * The function `calculate` processes a stack of tokens representing a
     * Reverse Polish Notation expression and performs arithmetic operations
     * based on the tokens.
     *
     * @param stack The `stack` parameter is a stack data structure that holds
     * tokens representing numbers and operators in the RPN expression.
     *
     * @return The `calculate` method does not return any value. It performs
     * calculations on the input stack and outputs the result to the console.
     * The final result of the calculations is printed to the console using
     * `std::cout` at the end of the method.
     */
    void calculate(Stack<Token, ForwardList>& stack);
};
