//============================================================================
// Copyright (C) 2026 Sunny Matato
//
// This program is free software. It comes without any warranty, to
// the extent permitted by applicable law. You can redistribute it
// and/or modify it under the terms of the Do What The Fuck You Want
// To Public License, Version 2, as published by Sam Hocevar.
// See http://www.wtfpl.net/ for more details.
//============================================================================
#include "queue.h"

//============================================================================
void CircularQueue_init(CircularQueue *me,
                        void *qSto, uint16_t qLen)
{
    me->ring  = qSto;
    me->head  = 0U;
    me->tail  = 0U;
    me->qLen  = qLen;
    me->nUsed = 0U;
    me->nMin  = me->qLen;
}

//............................................................................
bool CircularQueue_put(CircularQueue *me, void *elemPut) {
    if (me->nUsed < me->qLen) { // Not full...
        me->ring[me->head] = elemPut;
        if (me->head == 0) me->head = me->qLen;
        --me->head;
        ++me->nUsed;
        if (me->nMin > me->qLen - me->nUsed) { // Update nMin.
            me->nMin = me->qLen - me->nUsed;
        }
        return true;
    } else { // Full...
        return false;
    }
}

//............................................................................
void *CircularQueue_get(CircularQueue *me) {
    void *elemGet;
    elemGet = me->ring[me->tail];
    if (me->tail == 0) me->tail = me->qLen;
    --me->tail;
    --me->nUsed;
    return elemGet;
}
