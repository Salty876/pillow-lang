#ifndef pillow_object_h
#define pillow_object_h

#include "chunk.h"
#include "value.h"


typedef struct ObjString ObjString;

typedef enum {
    OBJ_STRING
} ObjType;

struct Object {
    ObjType type;
};

struct ObjString {
    Object object;
    int length;
    char* chars;
};

static inline bool isObjType(Value value, ObjType type) {
    return IS_OBJECT(value) && AS_OBJ(value)->type == type;
}


#define OBJ_TYPE(value)        (AS_OBJ(value)->type)
#define IS_STRING(value)       isObjType(value, OBJ_STRING)
#define AS_STRING(value)       ((ObjString*)AS_OBJ(value))
#define AS_CSTRING(value)      (((ObjString*)AS_OBJ(value))->chars)


ObjString* copyString(const char* chars, int length);
void printObject(Value value);

#endif