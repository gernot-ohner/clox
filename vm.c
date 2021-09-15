//
// Created by go on 14.09.21.
//

#include <stdio.h>
#include "vm.h"
#include "debug.h"

VM vm;


void initVM() {
    resetStack();
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
#define BINARY_OP(op) \
    do { \
        double b = pop(); \
        double a = pop(); \
        push(a op b); \
    } while (false)


    for (;;) {
        uint8_t instruction;
        switch (instruction = *vm.ip++) {
#ifdef DEBUG_TRACE_EXECUTION
            printf("          ");
            for (Value* slot = vm.stack; slot < vm.stackTop; slot++) {
                printf("[");
                printf("%f", *slot);
                // print the current element
                printf("]");
            }
            printf("\n");

            disassembleInstruction(vm.chunk, (int) (vm.ip - vm.chunk->code));
#endif
            case OP_RETURN: {
                printValue(pop());
                printf("\n");
                return INTERPRET_OK;
            }
            case OP_NEGATE:
                push(-pop());
                break;
            case OP_CONSTANT: {
                Value constant = READ_CONSTANT();
                push(constant);
                printValue(constant);
                printf("\n");
                break;
            }
            case OP_ADD: BINARY_OP(+); break;
            case OP_SUBTRACT: BINARY_OP(-); break;
            case OP_MULTIPLY: BINARY_OP(*); break;
            case OP_DIVIDE: BINARY_OP(/); break;
            default:
                return INTERPRET_COMPILE_ERROR;
        }
    }

#undef BINARY_OP
#undef READ_CONSTANT
#undef READ_BYTE
}

void resetStack() {
    vm.stackTop = vm.stack;
}

void push(Value v) {
    *vm.stackTop = v;
    vm.stackTop++;
}

Value pop() {
    vm.stackTop--;
    return *vm.stackTop;
}
