#pragma once

#include <cstdio>

#include "ForwardList.h"
#include "ONPcalc.h"
#include "Queue.h"
#include "Stack.h"
#include "Token.h"

/**
 * The `Converter` class is defined with three private member variables:
 * - `stack`: a reference to a `Stack` of `Token` objects
 * - `output`: a `DoublyLinkedList` of `Token` objects
 * - `arg_counts`: a `Stack` of `unsigned char` integers
 */
class Converter {
    Stack<Token, ForwardList>& stack;
    Queue<Token, ForwardList> output;
    Stack<unsigned char, ForwardList> arg_counts;

    static void readToken(char* str);

   public:
    /**
     * The `Converter` constructor initializes the `stack` member with the
     * provided `Stack` of `Token` objects.
     *
     * @param stack A reference to a `Stack` of `Token` objects.
     */
    explicit Converter(Stack<Token, ForwardList>& stack) : stack(stack){};

    // The `Converter` destructor.
    ~Converter(){};

    /**
     * The function `convertOneFormula` reads input tokens and converts them
     * into Reverse Polish Notation (RPN) using a stack and output queue.
     *
     * @return The function processes input tokens and
     * manipulates stacks and output lists based on certain conditions, but it
     * does not return any specific value or result.
     */
    void convertOneFormula();
};