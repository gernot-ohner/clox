#include <stdio.h>
#include "common.h"
#include "chunk.h"
#include "debug.h"
#include "vm.h"

int main() {

    initVM();

    Chunk c;
    initChunk(&c);

    int constant = addConstant(&c, 1.2);
    writeChunk(&c, OP_CONSTANT, 123);
    writeChunk(&c, constant, 123);

    writeChunk(&c, OP_RETURN, 123);

//    disassembleChunk(&c, "test chunk");
    interpretChunk(&c);
    freeChunk(&c);
    return 0;
}
