// Host-only example port. Embedded clients supply their own header.
#ifndef TEST_TIME_EVT_PORT_H_
#define TEST_TIME_EVT_PORT_H_

#include <stddef.h>
#include <stdbool.h>

void TimeEvt_testRequire(bool condition, int line);
unsigned TimeEvt_testEnter(void);
void TimeEvt_testExit(unsigned previous);

#define TIME_EVT_REQUIRE(condition_) \
    TimeEvt_testRequire((condition_), __LINE__)
// A saved critical-state token also supports ports that restore IRQ state.
#define TIME_EVT_CRIT_STAT unsigned timeEvtCriticalState_;
#define TIME_EVT_CRIT_ENTRY() \
    (timeEvtCriticalState_ = TimeEvt_testEnter())
#define TIME_EVT_CRIT_EXIT() TimeEvt_testExit(timeEvtCriticalState_)

#endif // TEST_TIME_EVT_PORT_H_
