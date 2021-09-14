//
// Created by go on 13.09.21.
//

#ifndef CLOX_DEBUG_H
#define CLOX_DEBUG_H

#include "chunk.h"
void disassembleChunk(Chunk* chunk, const char* name);
int disassembleInstruction(Chunk* chunk, int offset);

static int simpleInstruction(const char* string, int offset);
static int constantInstruction(const char* string, Chunk* chunk, int offset);

#endif //CLOX_DEBUG_H
