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

//============================================================================
typedef struct {
    volatile JitterCtrType ctr;
    JitterCtrType ctrLoad;
    JitterCtrType interval;
    JitterCtrType base;

    // should be >= 0 ...
    JitterCtrType margin;
    JitterCtrType asyncMargin;

    enum JitterDirection direct;
    bool enableRetreat;
} JitterCtrl;

//============================================================================
void JitterCtrl_setCtr(JitterCtrl *me,
                       JitterCtrType ctr, JitterCtrType interval);
//............................................................................
void JitterCtrl_reload(JitterCtrl *me);
//............................................................................
void JitterCtrl_setBase(JitterCtrl *me, JitterCtrType base);
//............................................................................
void JitterCtrl_setMargin(JitterCtrl *me,
                          JitterCtrType margin, JitterCtrType asyncMargin);
//............................................................................
void JitterCtrl_setOpts(JitterCtrl *me,
                        enum JitterDirection direct,
                        bool isRetreatable);

//============================================================================
bool Jitter_monitor(JitterCtrl *me, JitterCtrType target);

#endif // JITTER_DETECTION_H_
