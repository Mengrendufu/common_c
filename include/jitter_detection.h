#ifndef jitter_detection_h_
#define jitter_detection_h_

/* class propotype ---------------------------------------------------------*/
typedef struct {
    volatile uint8_t jitter_continue_cnt;
} JitterCtrl;
/* class propotype ---------------------------------------------------------*/

/* model options -----------------------------------------------------------*/
/* directions --------------------------------------------------------------*/
enum JitterDirection {
    JITTER_DIRECTION_UP,
    JITTER_DIRECTION_DOWN,
    JITTER_DIRECTION_NONE  /* both */
};
/* directions --------------------------------------------------------------*/

/* continuous detection options --------------------------------------------*/
enum JitterRetreadOpt {
    JITTER_RETREAT_DISABLE,
    JITTER_RETREAT_ENABLE,
};
/* continuous detection options --------------------------------------------*/
/* model options -----------------------------------------------------------*/

/* handlers ----------------------------------------------------------------*/
/* clear -------------------------------------------------------------------*/
void JitterCtrl_init(JitterCtrl *me);
/* clear -------------------------------------------------------------------*/

/*****************************************************************************
    \brief detect continuous +-changes, and +-big_changes
    \note all not periodical, need to init the JitterCtrl manully
        after jitter happen
*****************************************************************************/

/* direction: + only -------------------------------------------------------*/
uint8_t Jitter_detection_up(
    JitterCtrl *me,
    uint16_t detect_base,
    uint16_t detect_target,
    uint8_t detect_thresh,
    uint8_t jitter_continue_thresh_times,
    uint8_t retreat,
    uint8_t big_jitter);
/* direction: + only -------------------------------------------------------*/

/* direction: - only -------------------------------------------------------*/
uint8_t Jitter_detection_down(
    JitterCtrl *me,
    uint16_t detect_base,
    uint16_t detect_target,
    uint8_t detect_thresh,
    uint8_t jitter_continue_thresh_times,
    uint8_t retreat,
    uint8_t big_jitter);
/* direction: - only -------------------------------------------------------*/

/* application handler -----------------------------------------------------*/
uint8_t jitter_detection(
    JitterCtrl *me,
    uint16_t detect_base,
    uint16_t detect_target,
    uint8_t jitter_direction,
    uint8_t detect_thresh,
    uint8_t jitter_continue_thresh_times,
    uint8_t retreat,
    uint8_t big_jitter);
/* application handler -----------------------------------------------------*/
/* handlers ----------------------------------------------------------------*/

/* test area ---------------------------------------------------------------*/
/* data window size --------------------------------------------------------*/
#define TEST_SIZE  10U
/* data window size --------------------------------------------------------*/

/* test handlers -----------------------------------------------------------*/
void jitter_test_handler(void);
/* test handlers -----------------------------------------------------------*/
/* test area ---------------------------------------------------------------*/

#endif  /* jitter_detection_h_ */
