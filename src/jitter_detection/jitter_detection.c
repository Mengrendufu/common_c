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
void JitterCtrl_init(JitterCtrl *me) {
    me->jitterCnt = 0U;
}

//............................................................................
bool Jitter_detection_up(JitterCtrl *me,
                         JitterCtrType base, JitterCtrType target,
                         JitterCtrType margin, JitterCtrType asynMargin,
                         JitterCtrType jitterThres,
                         bool fallEnable)
{
    if (target > base) {
        if (asynMargin != 0) {
            if ((target - base) >= asynMargin) {
                return true;
            }
        }

        if ((target - base) >= margin) {
            ++me->jitterCnt;
            if (me->jitterCnt == jitterThres) {
                return true;
            }
        } else {
            if (fallEnable) {
                JitterCtrl_init(me);
            }
        }
    } else if (target == base) {
        if (fallEnable) {
            JitterCtrl_init(me);
        }
    }
    return false;
}

//............................................................................
bool Jitter_detection_down(JitterCtrl *me,
                           JitterCtrType base, JitterCtrType target,
                           JitterCtrType margin, JitterCtrType asynMargin,
                           JitterCtrType jitterThres,
                           bool fallEnable)
{
    if (target < base) {
        if (asynMargin != 0) {
            if ((base - target) >= asynMargin) {
                return true;
            }
        }
        if ((base - target) >= margin ) {
            ++me->jitterCnt;
            if (me->jitterCnt == jitterThres) {
                return true;
            }
        } else {
            if (fallEnable) {
                JitterCtrl_init(me);
            }
        }
    } else if (target == base) {
        if (fallEnable) {
            JitterCtrl_init(me);
        }
    }
    return false;
}

//============================================================================
bool jitter_detection(JitterCtrl *me,
                      enum JitterDirection direction,
                      JitterCtrType base, JitterCtrType target,
                      JitterCtrType margin, JitterCtrType asynMargin,
                      JitterCtrType jitterThres,
                      bool fallEnable)
{
    bool result;
    result = false;
    if (direction == JITTER_DIRECTION_UP) {
        result = Jitter_detection_up(me,
                                     base, target,
                                     margin, asynMargin,
                                     jitterThres,
                                     fallEnable);
    } else if (direction == JITTER_DIRECTION_DOWN) {
        result = Jitter_detection_down(me,
                                       base, target,
                                       margin, asynMargin,
                                       jitterThres,
                                       fallEnable);
    } else if (direction == JITTER_DIRECTION_NONE) {
        result = Jitter_detection_up(me,
                                     base, target,
                                     margin, asynMargin,
                                     jitterThres,
                                     fallEnable)
                 | Jitter_detection_down(me,
                                         base, target,
                                         margin, asynMargin,
                                         jitterThres,
                                         fallEnable);
    }
    return result;
}
