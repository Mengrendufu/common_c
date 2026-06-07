//============================================================================
// Copyright (C) 2026 Sunny Matato
//
// This program is free software. It comes without any warranty, to
// the extent permitted by applicable law. You can redistribute it
// and/or modify it under the terms of the Do What The Fuck You Want
// To Public License, Version 2, as published by Sam Hocevar.
// See http://www.wtfpl.net/ for more details.
//============================================================================
#include "jitter_detection.h"

//============================================================================
void JitterCtrl_setCtr(JitterCtrl *me,
                       JitterCtrType ctr, JitterCtrType interval)
{
    me->ctr = ctr;
    me->ctrLoad = me->ctr;
    me->interval = interval;
}
//............................................................................
void JitterCtrl_reload(JitterCtrl *me) {
    me->ctr = me->ctrLoad;
}
//............................................................................
void JitterCtrl_setBase(JitterCtrl *me, JitterCtrType base) {
    me->base = base;
}
//............................................................................
void JitterCtrl_setMargin(JitterCtrl *me,
                          JitterCtrType margin, JitterCtrType asyncMargin)
{
    me->margin = margin;
    me->asyncMargin = asyncMargin;
}
//............................................................................
void JitterCtrl_setOpts(JitterCtrl *me,
                        enum JitterDirection direct,
                        bool isRetreatable)
{
    me->direct = direct;
    me->enableRetreat = isRetreatable;
}

//============================================================================
static bool Jitter_isAsyncUp(JitterCtrl *me, JitterCtrType target) {
    if (me->base >= target) {
        return false;
    } else {
        if (me->asyncMargin == 0) {
            return false;
        } else {
            return (target - me->base >= me->asyncMargin);
        }
    }
}
//............................................................................
static bool Jitter_isUp(JitterCtrl *me, JitterCtrType target) {
    if (me->base >= target) {
        return false;
    } else {
        if (me->margin == 0) {
            return false;
        } else {
            return (target - me->base >= me->margin);
        }
    }
}
//............................................................................
static bool Jitter_isAsyncDown(JitterCtrl *me, JitterCtrType target) {
    if (me->base <= target) {
        return false;
    } else {
        if (me->asyncMargin == 0) {
            return false;
        } else {
            return (me->base - target >= me->asyncMargin);
        }
    }
}
//............................................................................
static bool Jitter_isDown(JitterCtrl *me, JitterCtrType target) {
    if (me->base <= target) {
        return false;
    } else {
        if (me->margin == 0) {
            return false;
        } else {
            return (me->base - target >= me->margin);
        }
    }
}
//............................................................................
bool Jitter_monitor(JitterCtrl *me, JitterCtrType target) {
    bool asyncCon, norCon;

    switch (me->direct) {
        case JITTER_DIRECTION_UP: {
            asyncCon = Jitter_isAsyncUp(me, target);
            norCon = Jitter_isUp(me, target);
            break;
        }
        case JITTER_DIRECTION_DOWN: {
            asyncCon = Jitter_isAsyncDown(me, target);
            norCon = Jitter_isDown(me, target);
            break;
        }
        case JITTER_DIRECTION_NONE: {
            asyncCon = Jitter_isAsyncUp(me, target) ||
                    Jitter_isAsyncDown(me, target);
            norCon = Jitter_isUp(me, target) || Jitter_isDown(me, target);
            break;
        }
        default: {
            asyncCon = false;
            norCon = false;
            break;
        }
    }

    if (asyncCon) {
        if (me->interval > 0) {
            me->ctr = me->interval;
        }
        return true;
    } else if (norCon) {
        if (me->ctr > 0) {
            --me->ctr;
            if (me->ctr == 0) {
                if (me->interval > 0) {
                    me->ctr = me->interval;
                }
                return true;
            }
        }
    } else {
        if (me->enableRetreat) {
            me->ctr = me->ctrLoad;
        }
    }

    return false;
}
