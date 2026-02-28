//============================================================================
// Copyright (C) 2026 Sunny Matato
//
// This program is free software. It comes without any warranty, to
// the extent permitted by applicable law. You can redistribute it
// and/or modify it under the terms of the Do What The Fuck You Want
// To Public License, Version 2, as published by Sam Hocevar.
// See http://www.wtfpl.net/ for more details.
//============================================================================
#include "timer.h"

//============================================================================
void Timer_ctor(Timer *me, timeoutCallback cb) {
    me->tmCb = cb;
}

//............................................................................
void Timer_set(Timer *me,
               uint8_t hour, uint8_t min, uint8_t sec)
{
    me->hour = hour;
    me->min  = min;
    me->sec  = sec;
}

//............................................................................
bool Timer_is_clear(Timer *me) {
    if (
        (me->hour == 0U) && (me->min == 0U) && (me->sec == 0U)
    ) {
        return true;
    } else {
        return false;
    }
}

//............................................................................
void Timer_turn_off(Timer *me) {
    me->hour = 0U;
    me->min  = 0U;
    me->sec  = 0U;
}

//............................................................................
void Timer_countdown(Timer *me) {
    if (me->hour == 0U) {
        if (me->min == 0U) {
            if (me->sec == 0U) { // Timer off...
            } else { // hour==0, min==0, sec!=0
                --me->sec;
                if (me->sec == 0U) {
                    (*me->tmCb)(); // Calling timeout callback.
                }
            }
        } else {
            if (me->sec == 0U) { // hour==0, min!=0, sec==0
                --me->min;
                me->sec = 59U;
            } else { // hour==0, min!=0, sec!=0
                --me->sec;
            }
        }
    } else {
        if (me->min == 0U) {
            if (me->sec == 0U) { // hour!=0, min==0, sec==0
                --me->hour;
                me->min = 59U;
                me->sec = 59U;
            } else { // hour!=0, min==0, sec!=0
                --me->sec;
            }
        } else {
            if (me->sec == 0U) { // hour!=0, min!=0, sec==0
                --me->min;
                me->sec = 59U;
            } else { // hour!=0, min!=0, sec!=0
                --me->sec;
            }
        }
    }
}
