#include "RustyOption.h"

#include <stdbool.h>
#include <stdio.h>

// ----------------- Option_INT -----------------

Option_INT Some_INT(int value) {
    Option_INT option;
    option.has_value = true;
    option.value = value;
    return option;
}

Option_INT None_INT() {
    Option_INT option;
    option.has_value = false;
    return option;
}

int unwrap_INT(Option_INT option) {
    if (option.has_value) return option.value;
    printf("Option does not have a value\n");
    exit(1);
}

Option_INT map_INT(Option_INT option, int (*func)(int)) {
    if (option.has_value) return Some_INT(func(option.value));
    return None_INT();
}

// int main() {
//     Option_INT opt;
//     opt = Some_INT(5);
//     if (opt.has_value) {
//         printf("Value: %d\n", opt.value);
//     } else {
//         printf("No value\n");
//     }
//     return 0;
// }

// ----------------- Option_FLOAT -----------------

Option_FLOAT Some_FLOAT(float value) {
    Option_FLOAT option;
    option.has_value = true;
    option.value = value;
    return option;
}

Option_FLOAT None_FLOAT() {
    Option_FLOAT option;
    option.has_value = false;
    return option;
}

float unwrap_FLOAT(Option_FLOAT option) {
    if (option.has_value) return option.value;
    printf("Option does not have a value\n");
    exit(1);
}

Option_FLOAT map_FLOAT(Option_FLOAT option, float (*func)(float)) {
    if (option.has_value) return Some_FLOAT(func(option.value));
    return None_FLOAT();
}

// ----------------- Option_STRING -----------------

Option_STRING Some_STRING(char* value) {
    Option_STRING option;
    option.has_value = true;
    option.value = malloc(strlen(value) + 1);
    strcpy(option.value, value);
    return option;
}

Option_STRING None_STRING() {
    Option_STRING option;
    option.has_value = false;
    return option;
}

char* unwrap_STRING(Option_STRING option) {
    if (option.has_value) return option.value;
    printf("Option does not have a value\n");
    exit(1);
}

Option_STRING map_STRING(Option_STRING option, char* (*func)(char*)) {
    if (option.has_value) return Some_STRING(func(option.value));
    return None_STRING();
}

void free_STRING(Option_STRING* option) {
    if (option->has_value) {
        free(option->value);
        option->value = NULL;
        option->has_value = false;
    }
}

// Option_STRING option = Some_STRING("Hello, world!");
// .....
// free_STRING(&option);