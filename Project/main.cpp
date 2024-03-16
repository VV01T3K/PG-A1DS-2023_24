#include <iostream>

#include "Converter.h"
#include "ONPcalc.h"
#include "Stack.h"
using namespace std;

int main() {
    Stack<Token, ForwardList> stack;

    int n;
    scanf("%d", &n);
    Converter converter(stack);

    for (int i = 0; i < n; i++) {
        converter.convertOneFormula();
        stack.print("  ");
        ONPcalc calc;
        calc.calculate(stack);
    }

    return 0;
}