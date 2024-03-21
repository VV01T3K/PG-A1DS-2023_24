#include <cstdio>
#include <iostream>

#include "Converter.h"
#include "ForwardList.h"
#include "Stack.h"
#include "Token.h"
using namespace std;

int main() {
    std::ios::sync_with_stdio(false);
    Stack<Token, ForwardList> stack;
    Converter converter(stack);

    int n;
    scanf("%d\n", &n);

    for (int i = 0; i < n; i++) {
        converter.convertOneFormula();
    }

    return 0;
}