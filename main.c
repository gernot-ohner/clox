#include <stdio.h>
#include "common.h"
#include "chunk.h"
#include "debug.h"

int main() {
    Chunk c;
    initChunk(&c);
    writeChunk(&c, OP_RETURN);
    disassembleChunk(&c, "test chunk");
    freeChunk(&c);
    return 0;
}
