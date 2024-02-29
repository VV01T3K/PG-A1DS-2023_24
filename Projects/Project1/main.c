#include <stdio.h>

#include "ONPcalc.h"

int main() {
    char* input = "3 4 + 100 *";  // (3 + 4) * 100 = 700

    printf("Result: %d\n", calculate(input));

    return 0;
}