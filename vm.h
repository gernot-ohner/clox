//
// Created by go on 14.09.21.
//

#ifndef CLOX_VM_H
#define CLOX_VM_H

#include "chunk.h"

typedef struct {
    Chunk* chunk;
    uint8_t* ip; // instruction pointer or program counter
} VM;

typedef enum {
    INTERPRET_OK,
    INTERPRET_COMPILE_ERROR,
    INTERPRET_RUNTIME_ERROR
} InterpretationResult;

void initVM();
void freeVM();
InterpretationResult interpretChunk(Chunk* c);
static InterpretationResult run();

#endif //CLOX_VM_H
