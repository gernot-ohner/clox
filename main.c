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

    constant = addConstant(&c, 3.4);
    writeChunk(&c, OP_CONSTANT, 123);
    writeChunk(&c, constant, 125);

    writeChunk(&c, OP_ADD, 126);

    constant = addConstant(&c, 5.6);
    writeChunk(&c, OP_CONSTANT, 123);
    writeChunk(&c, constant, 127);

    writeChunk(&c, OP_DIVIDE, 128);
    writeChunk(&c, OP_RETURN, 123);

//    disassembleChunk(&c, "test chunk");
    interpretChunk(&c);
    freeChunk(&c);
    return 0;
}
