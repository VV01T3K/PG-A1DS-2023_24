#pragma once

#include <cstring>
#include <iostream>

#include "DoublyLinkedList_Template.h"
#include "Stack.h"
#include "Token.h"

using namespace std;

#define MAX_STR_LENGTH 100

class Converter {
    Stack<Token>& stack;
    DoublyLinkedList<Token> output;
    Stack<short> arg_counts;
    bool divideByZero = false;

   public:
    Converter(Stack<Token>& stack) : stack(stack){};
    ~Converter(){};
    void convertOneFormula();
    void calculate();
};