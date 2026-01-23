#ifndef pillow_value_h
#define pillow_value_h

#include "common.h"

// Lowk start simple and only do doubles for floats
typedef double Value;

// dynamic array structure for the datatype, array should be dynamic
typedef struct {
    int capacity;
    int count;
    Value* values;
} ValueArray;

// Chunk functions but for array
void initValueArray(ValueArray* array);
void writeValueArray(ValueArray* array, Value value);
void freeValueArray(ValueArray* array);
void printValue(Value value);

#endif