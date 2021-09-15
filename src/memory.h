//
// Created by go on 13.09.21.
//

#ifndef CLOX_MEMORY_H
#define CLOX_MEMORY_H

#include "common.h"

#define GROW_CAPACITY(capacity) \
    ((capacity) < 8 ? 8 : (capacity) * 2)

#define GROW_ARRAY(type, code, oldCount, newCount) \
    (type*) reallocate(code, sizeof(type) * oldCount, sizeof(type) * newCount)

#define FREE_ARRAY(type, pointer, oldCount) \
    reallocate(pointer, sizeof(type) * oldCount, 0)

void* reallocate(void* pointer, size_t oldSize, size_t newSize);

#endif //CLOX_MEMORY_H
