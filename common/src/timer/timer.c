/* dependencies ------------------------------------------------------------*/
#include "stdio.h"
#include "stdint.h"
#include "timer.h"
/* dependencies ------------------------------------------------------------*/

/* constructor -------------------------------------------------------------*/
void Timer_set(
    Timer *me,
    uint8_t hour,
    uint8_t min,
    uint8_t sec)
{
    me->hour = hour;
    me->min  = min;
    me->sec  = sec;

    return;
}
/* constructor -------------------------------------------------------------*/

/* check -------------------------------------------------------------------*/
uint8_t Timer_is_clear(Timer *me) {
    if ((me->hour == 0U) &&
            (me->min == 0U) &&
            (me->sec == 0U))
    {
        return 1U;
    }
    else {
        return 0U;
    }
}
/* check -------------------------------------------------------------------*/

/* clear -------------------------------------------------------------------*/
void Timer_turn_off(Timer *me) {
    me->hour = 0U;
    me->min  = 0U;
    me->sec  = 0U;

    return;
}
/* clear -------------------------------------------------------------------*/

/* timer countdown by sec --------------------------------------------------*/
void Timer_countdown(Timer *me) {
    // count down the timer
    if (me->hour == 0U) {
        if (me->min == 0U) {
            // hour==0, min==0, sec==0
            if (me->sec == 0U) {
                /*! timer is set to off ------------------------------------*/
                /*! timer is set to off ------------------------------------*/
            }
            // hour==0, min==0, sec!=0
            else {
                --me->sec;
                if (me->sec == 0U) {
                    /*! timer running out ----------------------------------*/
                    /*! timer running out ----------------------------------*/
                }
            }
        }
        else {
            // hour==0, min!=0, sec==0
            if (me->sec == 0U) {
                --me->min;
                // 1 minute has 60 secs
                me->sec = 59U;
            }
            // hour==0, min!=0, sec!=0
            else {
                --me->sec;
            }
        }
    }
    else {
        if (me->min == 0U) {
            // hour!=0, min==0, sec==0
            if (me->sec == 0U) {
                --me->hour;
                // one hour has 60 minutes
                me->min = 59U;
                me->sec = 59U;
            }
            // hour!=0, min==0, sec!=0
            else {
                --me->sec;
            }
        }
        else {
            // hour!=0, min!=0, sec==0
            if (me->sec == 0U) {
                --me->min;
                // 1 minute has 60 secs
                me->sec = 59U;
            }
            // hour!=0, min!=0, sec!=0
            else {
                --me->sec;
            }
        }
    }

    return;
}
/* timer countdown by sec --------------------------------------------------*/

/* test area ---------------------------------------------------------------*/
void Timer_test(void) {
    /* instance ------------------------------------------------------------*/
    Timer timer_test;
    /* instance ------------------------------------------------------------*/

    /* construct -----------------------------------------------------------*/
    Timer_set(
        &timer_test,
        TIMER_TEST_HOUR,
        TIMER_TEST_MIN,
        TIMER_TEST_SEC);
    /* construct -----------------------------------------------------------*/

    /* counting ------------------------------------------------------------*/
    /*! start */
    printf("%02d:%02d:%02d\r\n",
            timer_test.hour, timer_test.min, timer_test.sec);
    while (!Timer_is_clear(&timer_test)) {
        Timer_countdown(&timer_test);
        printf("%02d:%02d:%02d\r\n",
                timer_test.hour, timer_test.min, timer_test.sec);
    }
    /* counting ------------------------------------------------------------*/

    return;
}
/* test area ---------------------------------------------------------------*/
