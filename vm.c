//
// Created by go on 14.09.21.
//

#include <stdio.h>
#include "vm.h"

VM vm;

void initVM() {

}

void freeVM() {

}

InterpretationResult interpretChunk(Chunk* c) {
    vm.chunk = c;
    vm.ip = vm.chunk->code;
    return run();
}

static InterpretationResult run() {
#define READ_BYTE() (*vm.ip++)
#define READ_CONSTANT() (vm.chunk->constants.values[READ_BYTE()])

    for (;;) {
        uint8_t instruction;
        switch (instruction = READ_BYTE()) {
            case OP_RETURN:
                return INTERPRET_OK;
            case OP_CONSTANT: {
                Value constant = READ_CONSTANT();
                printValue(constant);
                printf("\n");
            }
            default:
                return INTERPRET_COMPILE_ERROR;
        }
    }

#undef READ_CONSTANT
#undef READ_BYTE
}
