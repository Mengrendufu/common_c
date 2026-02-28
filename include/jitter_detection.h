//============================================================================
// Copyright (C) 2026 Sunny Matato
//
// This program is free software. It comes without any warranty, to
// the extent permitted by applicable law. You can redistribute it
// and/or modify it under the terms of the Do What The Fuck You Want
// To Public License, Version 2, as published by Sam Hocevar.
// See http://www.wtfpl.net/ for more details.
//============================================================================
#ifndef JITTER_DETECTION_H_
#define JITTER_DETECTION_H_

//============================================================================
#include "jitter_detection_port.h"

//! @brief
//! @cond INTERNAL

#ifndef JITTER_CTR_SIZE
    #define JITTER_CTR_SIZE 2
#endif // JITTER_CTR_SIZE

#if (JITTER_CTR_SIZE == 1)
    typedef int8_t JitterCtrType;
#elif (JITTER_CTR_SIZE == 2)
    typedef int16_t JitterCtrType;
#elif (JITTER_CTR_SIZE == 4)
    typedef int32_t JitterCtrType;
#elif (JITTER_CTR_SIZE == 8)
    typedef int64_t JitterCtrType;
#endif // JITTER_CTR_SIZE

//! @endcond

//============================================================================
enum JitterDirection {
    JITTER_DIRECTION_UP,
    JITTER_DIRECTION_DOWN,
    JITTER_DIRECTION_NONE // Both.
};

//............................................................................
enum JitterRetreadOpt {
    JITTER_RETREAT_DISABLE,
    JITTER_RETREAT_ENABLE,
};

//............................................................................
typedef struct {
    volatile JitterCtrType jitterCnt;
} JitterCtrl;

//============================================================================
void JitterCtrl_init(JitterCtrl *me);

//............................................................................
bool Jitter_detection_up(JitterCtrl *me,
                         JitterCtrType base, JitterCtrType target,
                         JitterCtrType margin, JitterCtrType asynMargin,
                         JitterCtrType jitterThres,
                         bool fallEnable);

//............................................................................
bool Jitter_detection_down(JitterCtrl *me,
                           JitterCtrType base, JitterCtrType target,
                           JitterCtrType margin, JitterCtrType asynMargin,
                           JitterCtrType jitterThres,
                           bool fallEnable);

//............................................................................
bool jitter_detection(JitterCtrl *me,
                      enum JitterDirection direction,
                      JitterCtrType base, JitterCtrType target,
                      JitterCtrType margin, JitterCtrType asynMargin,
                      JitterCtrType jitterThres,
                      bool fallEnable);

#endif // JITTER_DETECTION_H_
