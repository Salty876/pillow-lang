#ifndef pillow_value_h
#define pillow_value_h

#include "common.h"

typedef enum {
    VAL_BOOL,
    VAL_NULL,
    VAL_NUMBER,
} ValueType;

typedef struct {
    ValueType type;
        union  {
            bool boolean;
            double number;
        } as;
} Value;

#define IS_BOOL(value)      ((value).type == VAL_BOOL)
#define IS_NIL(value)       ((value).type == VAL_NULL)
#define IS_NUMBER(value)    ((value).type == VAL_NUMBER)

#define AS_BOOL(value)      ((value).as.boolean)
#define AS_NUMBER(value)    ((value).as.number)

#define BOOL_VAL(value)     ((Value){VAL_BOOL, {.boolean = value}})
#define NULL_VAL            ((Value){VAL_NULL, {.boolean = 0}})
#define NUMBER_VAL(value)   ((Value){VAL_NUMBER, {.number = value}})
#endif


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
