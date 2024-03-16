#include <cstdio>

#include "Converter.h"
#include "ONPcalc.h"
#include "Stack.h"
using namespace std;

int main() {
    Stack<Token, ForwardList> stack;
    Converter converter(stack);
    ONPcalc calculator(stack);

    int n;
    scanf("%d", &n);

    for (int i = 0; i < n; i++) {
        converter.convertOneFormula();
        stack.printToken();
        calculator.calculate();
    }

    return 0;
}