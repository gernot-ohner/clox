//
// Created by go on 14.09.21.
//

#ifndef CLOX_VM_H
#define CLOX_VM_H

#define STACK_MAX 256

#include "chunk.h"

typedef struct {
    Chunk* chunk;
    uint8_t* ip; // instruction pointer or program counter
    Value stack[STACK_MAX];
    Value* stackTop;
} VM;

typedef enum {
    INTERPRET_OK,
    INTERPRET_COMPILE_ERROR,
    INTERPRET_RUNTIME_ERROR
} InterpretationResult;

VM* getVm();
void initVM();
void freeVM();
void resetStack();
InterpretationResult interpretChunk(Chunk* c);
static InterpretationResult run();

void push(Value v);
Value pop();

#endif //CLOX_VM_H
