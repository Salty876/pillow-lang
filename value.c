#include <stdio.h>

#include "memory.h"
#include "value.h"

// Function to init array
void initValueArray(ValueArray* array) {
    array->values = NULL;
    array->capacity = 0;
    array->count = 0;
}

// Function to add to array
void writeValueArray(ValueArray* array, Value value) {
    if (array->capacity < array->count + 1) {
        int oldCap = array->capacity;
        array->capacity = GROW_CAPACITY(oldCap);

        array->values = GROW_ARRAY(Value, array->values, oldCap, array->capacity);
    }

    array->values[array->count] = value;
    array->count++;
}

// Function to free array
void freeValueArray(ValueArray* array) {
    FREE_ARRAY(Value, array->values, array->capacity);
    initValueArray(array);
}

void printValue(Value value) {
    printf("%g", AS_NUMBER(value));
}