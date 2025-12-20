#ifndef timer_h_
#define timer_h_

/* timer propotype ---------------------------------------------------------*/
typedef struct Timer {
    uint8_t hour;
    uint8_t min;
    uint8_t sec;
} Timer;
/* timer propotype ---------------------------------------------------------*/

/* constructor -------------------------------------------------------------*/
void Timer_set(
    Timer *me,
    uint8_t hour,
    uint8_t min,
    uint8_t sec);
/* constructor -------------------------------------------------------------*/

/* check -------------------------------------------------------------------*/
uint8_t Timer_is_clear(Timer *me);
/* check -------------------------------------------------------------------*/

/* clear -------------------------------------------------------------------*/
void Timer_turn_off(Timer *me);
/* clear -------------------------------------------------------------------*/

/* timer countdown by sec (utterly safe) -----------------------------------*/
void Timer_countdown(Timer *me);
/* timer countdown by sec (utterly safe) -----------------------------------*/

/* test area ---------------------------------------------------------------*/
#define TIMER_TEST_HOUR  0U
#define TIMER_TEST_MIN   0U
#define TIMER_TEST_SEC   15U
void Timer_test(void);
/* test area ---------------------------------------------------------------*/

#endif  /* timer_h_ */
