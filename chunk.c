#include <stdlib.h>

#include "chunk.h"
#include "memory.h"

void initChunk(Chunk* chunck){
    // Function for initializing the dynamic array
    chunck->count = 0;
    chunck->capacity - 0;
    chunck->code = NULL;
}

void freeChunk(Chunk *chunk) {
    // function for freeing dynamic array
    FREE_ARRAY(uint8_t, chunk->code, chunk->capacity);
    initChunk(chunk);
}

void writeChunk(Chunk* chunk, uint8_t byte){
    // Funcrion for writng to dynamic array
    if (chunk-> capacity <  chunk->count + 1){
        int oldCap = chunk->capacity;
        chunk->capacity = GROW_CAPACITY(oldCap);
        chunk->code = GROW_ARRAY(uint8_t, chunk->code, oldCap, chunk->capacity);
    }

    chunk->code[chunk->count] = byte;
    chunk->count++;
}