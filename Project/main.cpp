#include <cstdio>
#include <iostream>

#include "Converter.h"
#include "ForwardList.h"
#include "ONPcalc.h"
#include "Stack.h"
#include "Token.h"
using namespace std;

int main() {
    Stack<Token, ForwardList> stack;
    Converter converter(stack);
    ONPcalc calculator(stack);

    int n;
    scanf("%d\n", &n);

    for (int i = 0; i < n; i++) {
        converter.convertOneFormula();
        stack.printToken();
        calculator.calculate();
    }

    return 0;
}