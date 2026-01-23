#ifndef pillow_chunk_h
#define pillow_chunk_h

#include "common.h"
#include "value.h"

typedef enum {
    OP_RETURN,
    OP_CONSTANT,
} OpCode;

typedef struct {
    int count;
    int capacity;
    uint8_t* code;
    int* lines; // Keeps the line numbers in a array seperate from the bytecode
    ValueArray constants; //Growable array
} Chunk;

void initChunk(Chunk* chunk);
void freeChunk(Chunk* chunk);
void writeChunk(Chunk* chunk, uint8_t byte, int line);
int addConstant(Chunk* chunk, Value val);


#endif