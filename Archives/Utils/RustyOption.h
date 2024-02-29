// option.h

#ifndef OPTION_H
#define OPTION_H

#include <stdbool.h>

// ----------------- Option_INT -----------------
typedef struct {
    bool has_value;
    int value;
} Option_INT;

Option_INT Some_INT(int value);
Option_INT None_INT();
int unwrap_INT(Option_INT option);
Option_INT map_INT(Option_INT option, int (*func)(int));

// ----------------- Option_FLOAT -----------------
typedef struct {
    bool has_value;
    float value;
} Option_FLOAT;

Option_FLOAT Some_FLOAT(float value);
Option_FLOAT None_FLOAT();
float unwrap_FLOAT(Option_FLOAT option);
Option_FLOAT map_FLOAT(Option_FLOAT option, float (*func)(float));

// ----------------- Option_STRING -----------------
typedef struct {
    bool has_value;
    char* value;
} Option_STRING;

Option_STRING Some_STRING(char* value);
Option_STRING None_STRING();
char* unwrap_STRING(Option_STRING option);
Option_STRING map_STRING(Option_STRING option, char* (*func)(char*));
void free_STRING(Option_STRING* option);

#endif  // OPTION_H