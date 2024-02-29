#include <stdio.h>

#include "ONPcalc.h"

int main() {
    char* input = "3 4 + 5 *";  // (3 + 4) * 5 = 35

    printf("Result: %d\n", calculate(input));

    return 0;
}