#ifndef pillow_value_h
#define pillow_value_h

#include "common.h"

typedef struct Object Object;


typedef enum {
    VAL_BOOL,
    VAL_NULL,
    VAL_NUMBER,
    VAL_OBJECT
} ValueType;

typedef struct {
    ValueType type;
    union {
        bool boolean;
        double number;
        Object* object;
    } as;
} Value;

#define IS_BOOL(value)      ((value).type == VAL_BOOL)
#define IS_NULL(value)      ((value).type == VAL_NULL)
#define IS_NUMBER(value)    ((value).type == VAL_NUMBER)
#define IS_OBJECT(value)    ((value).type == VAL_OBJECT)

#define AS_BOOL(value)      ((value).as.boolean)
#define AS_NUMBER(value)    ((value).as.number)
#define AS_OBJECT(value)    ((value).as.object)
#define BOOL_VAL(value)     ((Value){.type = VAL_BOOL, .as = {.boolean = (value)}})
#define NULL_VAL            ((Value){.type = VAL_NULL, .as = {.boolean = false}})
#define NUMBER_VAL(value)   ((Value){.type = VAL_NUMBER, .as = {.number = (value)}})

// dynamic array structure for the datatype, array should be dynamic
typedef struct {
    int capacity;
    int count;
    Value* values;
} ValueArray;

// Chunk functions but for array
void initValueArray(ValueArray* array);
void writeValueArray(ValueArray* array, Value value);
bool valuesEqual(Value a, Value b);
void freeValueArray(ValueArray* array);
void printValue(Value value);

#endif
