#include <cstdio>
#include <iostream>

#include "Converter.h"
#include "List.h"
#include "Stack.h"
#include "Token.h"
using namespace std;

int main() {
    Stack<Token, List> stack;
    Converter converter(stack);

    int n;
    scanf("%d\n", &n);

    for (int i = 0; i < n; i++) {
        converter.convertOneFormula();
    }

    return 0;
}