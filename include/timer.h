//============================================================================
// Copyright (C) 2026 Sunny Matato
//
// This program is free software. It comes without any warranty, to
// the extent permitted by applicable law. You can redistribute it
// and/or modify it under the terms of the Do What The Fuck You Want
// To Public License, Version 2, as published by Sam Hocevar.
// See http://www.wtfpl.net/ for more details.
//============================================================================
#ifndef TIMER_H_
#define TIMER_H_

//============================================================================
#include "timer_port.h"

//============================================================================
typedef void (*timeoutCallback)(void);

//============================================================================
typedef struct Timer {
    uint8_t hour;
    uint8_t min;
    uint8_t sec;
    timeoutCallback tmCb;
} Timer;

//============================================================================
void Timer_ctor(Timer *me, timeoutCallback cb);
void Timer_set(Timer *me,
               uint8_t hour, uint8_t min, uint8_t sec);
bool Timer_is_clear(Timer *me);
void Timer_turn_off(Timer *me);
void Timer_countdown(Timer *me);

#endif // TIMER_H_
