//============================================================================
// Copyright (C) 2026 Sunny Matato
//
// This program is free software. It comes without any warranty, to
// the extent permitted by applicable law. You can redistribute it
// and/or modify it under the terms of the Do What The Fuck You Want
// To Public License, Version 2, as published by Sam Hocevar.
// See http://www.wtfpl.net/ for more details.
//============================================================================
#include "static_pool.h"

//============================================================================
typedef struct FreeBlock {
    struct FreeBlock *next;
} FreeBlock;

//============================================================================
void StaticPool_init(StaticPool *me,
                     void *poolSto, PoolCtr poolSize,
                     PoolCtr blockSize)
{
    FreeBlock *fb;
    PoolCtr nBlocks;

    me->free_head = poolSto;

    me->blockSize = (PoolCtr)sizeof(FreeBlock);
    nBlocks = (PoolCtr)1;
    while (me->blockSize < blockSize) {
        me->blockSize += (PoolCtr)sizeof(FreeBlock);
        ++nBlocks;
    }

    poolSize -= me->blockSize;
    me->nTot = 1;
    fb = (FreeBlock *)me->free_head;
    while (poolSize >= me->blockSize) {
        fb->next = fb + nBlocks;
        fb = fb->next;
        poolSize -= me->blockSize;
        ++me->nTot;
    }
    fb->next = (FreeBlock *)0;

    me->start = poolSto;
    me->end = fb;
    me->nFree = me->nTot;
    me->nMin  = me->nTot;
}

//............................................................................
void *StaticPool_get(StaticPool * const me) {
    FreeBlock *fb;
    fb = (FreeBlock *)0;
    fb = (FreeBlock *)me->free_head;
    if (fb != (FreeBlock *)0) {
        me->free_head = fb->next;
        --me->nFree;
        if (me->nFree < me->nMin) {
            me->nMin = me->nFree;
        }
    }
    return fb;
}

//............................................................................
void StaticPool_put(StaticPool *me,
                    void *block)
{
    ((FreeBlock *)block)->next = (FreeBlock *)me->free_head;
    me->free_head = block;
    ++me->nFree;
}
