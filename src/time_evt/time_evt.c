//============================================================================
// Copyright (C) 2026 Sunny Matato
//
// This program is free software. It comes without any warranty, to
// the extent permitted by applicable law. You can redistribute it
// and/or modify it under the terms of the Do What The Fuck You Want
// To Public License, Version 2, as published by Sam Hocevar.
// See http://www.wtfpl.net/ for more details.
//============================================================================
//============================================================================
#include "time_evt.h"
#include <stddef.h>

static TimeEvt *TimeEvt_head_;

void TimeEvt_ctor(TimeEvt *me, void const *event,
                  TimeEvt_PostOperations const *delivery) {
    TIME_EVT_REQUIRE(me != NULL);
    TIME_EVT_REQUIRE(event != NULL);
    TIME_EVT_REQUIRE(delivery != NULL && delivery->post != NULL);
    for (TimeEvt *node = TimeEvt_head_; node != NULL; node = node->next) {
        TIME_EVT_REQUIRE(node != me);
    }
    me->event = event;
    me->delivery = delivery;
    me->remaining = 0U;
    me->interval = 0U;
    me->next = TimeEvt_head_;
    TimeEvt_head_ = me;
}

void TimeEvt_arm(TimeEvt *me, uint32_t delay, uint32_t interval) {
    TIME_EVT_REQUIRE(me != NULL && me->delivery != NULL);
    TIME_EVT_REQUIRE(delay > 0U);
    TIME_EVT_CRIT_STAT
    TIME_EVT_CRIT_ENTRY();
    me->remaining = delay;
    me->interval = interval;
    TIME_EVT_CRIT_EXIT();
}

bool TimeEvt_disarm(TimeEvt *me) {
    TIME_EVT_REQUIRE(me != NULL && me->delivery != NULL);
    TIME_EVT_CRIT_STAT
    TIME_EVT_CRIT_ENTRY();
    bool const active = (me->remaining != 0U);
    me->remaining = 0U;
    me->interval = 0U;
    TIME_EVT_CRIT_EXIT();
    return active;
}

void TimeEvt_tick(void) {
    for (TimeEvt *node = TimeEvt_head_; node != NULL; node = node->next) {
        bool expired = false;
        TIME_EVT_CRIT_STAT
        TIME_EVT_CRIT_ENTRY();
        if (node->remaining != 0U && --node->remaining == 0U) {
            node->remaining = node->interval;
            expired = true;
        }
        TIME_EVT_CRIT_EXIT();
        if (expired) {
            node->delivery->post(node->delivery->context, node->event);
        }
    }
}
