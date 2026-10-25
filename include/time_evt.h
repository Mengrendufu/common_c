//============================================================================
// Copyright (C) 2026 Sunny Matato
//
// This program is free software. It comes without any warranty, to
// the extent permitted by applicable law. You can redistribute it
// and/or modify it under the terms of the Do What The Fuck You Want
// To Public License, Version 2, as published by Sam Hocevar.
// See http://www.wtfpl.net/ for more details.
//============================================================================
#ifndef TIME_EVT_H_
#define TIME_EVT_H_

#include <stdbool.h>
#include <stdint.h>
#include "time_evt_port.h"

// Required delivery capability. The service borrows the event and never
// interprets or modifies it. post must return promptly and must not call
// TimeEvt_tick recursively. It runs outside the timing critical section.
typedef struct {
    void *context;
    void (*post)(void *context, void const *event);
} TimeEvt_PostOperations;

typedef struct TimeEvt TimeEvt;
struct TimeEvt {
    TimeEvt *next;
    void const *event;
    TimeEvt_PostOperations const *delivery;
    uint32_t remaining;
    uint32_t interval;
};

// Register once during serialized setup, before concurrent use begins.
// Node, event, operations and context must outlive all timer use and any
// queued delivery. No copying, runtime registration, removal or rebinding.
// Members are service-owned; consumers use only ctor/arm/disarm.
void TimeEvt_ctor(TimeEvt *me, void const *event,
                  TimeEvt_PostOperations const *delivery);

// Units are calls to tick; the owner supplies its frequency. delay must be
// positive; interval=0 is one-shot. Re-arm replaces the outstanding count.
// First decrement occurs at the next tick: uncertainty is one tick period.
void TimeEvt_arm(TimeEvt *me, uint32_t delay, uint32_t interval);

// Returns whether a countdown was active. Stops future expirations but
// cannot recall one already committed by tick, even before post is called.
// Re-arm also does not retract prior expirations or queued deliveries.
bool TimeEvt_disarm(TimeEvt *me);

// Single, non-reentrant driver. Registration is frozen during operation.
// arm/disarm may run concurrently only as supported by the supplied port.
// Disarmed nodes remain linked; no allocation or time source is required.
void TimeEvt_tick(void);

#endif // TIME_EVT_H_
