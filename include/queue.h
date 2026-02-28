//============================================================================
// Copyright (C) 2026 Sunny Matato
//
// This program is free software. It comes without any warranty, to
// the extent permitted by applicable law. You can redistribute it
// and/or modify it under the terms of the Do What The Fuck You Want
// To Public License, Version 2, as published by Sam Hocevar.
// See http://www.wtfpl.net/ for more details.
//============================================================================
#ifndef QUEUE_H_
#define QUEUE_H_

//============================================================================
#include "queue_port.h"

//============================================================================
#ifndef QUEUE_CTRL_SIZE
    #define QUEUE_CTRL_SIZE 2
#endif // QUEUE_CTRL_SIZE

#if (QUEUE_CTRL_SIZE == 1)
    typedef uint8_t QueueCtr;
#elif (QUEUE_CTRL_SIZE == 2)
    typedef uint16_t QueueCtr;
#elif (QUEUE_CTRL_SIZE == 4)
    typedef uint32_t QueueCtr;
#elif (QUEUE_CTRL_SIZE == 8)
    typedef uint64_t QueueCtr;
#endif // QUEUE_CTRL_SIZE

//============================================================================
typedef struct CircularQueue {
    void **ring;
    QueueCtr head;
    QueueCtr tail;
    QueueCtr qLen;
    QueueCtr nUsed;
    QueueCtr nMin;
} CircularQueue;

//............................................................................
#define CircularQueue_empty(me_) ((me_)->nUsed == 0U)
#define CircularQueue_full(me_) ((me_)->nUsed >= (me_)->qLen)

//============================================================================
void CircularQueue_init(CircularQueue *me,
                        void *qSto, uint16_t qLen);
bool CircularQueue_put(CircularQueue *me, void *elemPut);
void *CircularQueue_get(CircularQueue *me);

#endif // QUEUE_H_
