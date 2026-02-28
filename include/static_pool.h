//============================================================================
// Copyright (C) 2026 Sunny Matato
//
// This program is free software. It comes without any warranty, to
// the extent permitted by applicable law. You can redistribute it
// and/or modify it under the terms of the Do What The Fuck You Want
// To Public License, Version 2, as published by Sam Hocevar.
// See http://www.wtfpl.net/ for more details.
//============================================================================
#ifndef STATIC_POOL_H_
#define STATIC_POOL_H_

//============================================================================
#include "static_pool_port.h"

//============================================================================
#ifndef STATIC_POOL_CTR_SIZE
    #define STATIC_POOL_CTR_SIZE 2
#endif // STATIC_POOL_CTR_SIZE

#if (STATIC_POOL_CTR_SIZE == 1)
    typedef uint8_t PoolCtr;
#elif (STATIC_POOL_CTR_SIZE == 2)
    typedef uint16_t PoolCtr;
#elif (STATIC_POOL_CTR_SIZE == 4)
    typedef uint32_t PoolCtr;
#elif (STATIC_POOL_CTR_SIZE == 8)
    typedef uint64_t PoolCtr;
#endif // STATIC_POOL_CTR_SIZE

//============================================================================
#define STATIC_POOL_ELEM_TYPE(type_)                                         \
    struct { void *sto_[((sizeof(type_) - 1U) / sizeof(void*)) + 1U]; }

//============================================================================
typedef struct StaticPool {
    void *free_head;
    void *start;
    void *end;
    PoolCtr blockSize;
    PoolCtr nTot;
    PoolCtr nFree;
    PoolCtr nMin;
} StaticPool;

//============================================================================
void StaticPool_init(StaticPool * const me,
                     void * const poolSto, PoolCtr poolSize,
                     PoolCtr blockSize);
void *StaticPool_get(StaticPool * const me);
void StaticPool_put(StaticPool * const me, void *block);

#endif // STATIC_POOL_H_
