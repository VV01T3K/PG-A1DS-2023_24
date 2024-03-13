#include <iostream>

#include "Converter.h"
#include "ONPcalc.h"
#include "Stack.h"
using namespace std;

int main() {
    Stack<Token> stack;

    int n;
    cin >> n;
    Converter converter(stack);

    for (int i = 0; i < n; i++) {
        converter.convertOneFormula();
        stack.specialprint("  ");

        ONPcalc calc;
        calc.calculate(stack);
        printf("\n");
    }

    return 0;
}