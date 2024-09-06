/* dependencies ------------------------------------------------------------*/
#include "stdint.h"
#include "jitter_detection.h"
/* dependencies ------------------------------------------------------------*/

/* clear -------------------------------------------------------------------*/
void JitterCtrl_init(JitterCtrl *me) {
    me->jitter_continue_cnt = 0U;

    return;
}
/* clear -------------------------------------------------------------------*/

/* direction: + only -------------------------------------------------------*/
uint8_t Jitter_detection_up(
    JitterCtrl *me,
    uint16_t detect_base,
    uint16_t detect_target,
    uint8_t detect_thresh,
    uint8_t jitter_continue_thresh_times,
    uint8_t retreat,
    uint8_t big_jitter)
{
    /* up change */
    if (detect_target > detect_base) {
        /* big jitter detection enable */
        if (big_jitter != 0U) {
            if ((detect_target - detect_base) >= big_jitter) {
                /* big_jitter happend --------------------------------------*/
                return 1U;
                /* big_jitter happend --------------------------------------*/
            }
        }

        /* change big enough */
        if ((detect_target - detect_base) >= detect_thresh) {
            /* the me->jitter_continue_cnt */
            /* must be constructed as 0U before used. */
            ++me->jitter_continue_cnt;
            /* if continuous enough */
            if (me->jitter_continue_cnt == jitter_continue_thresh_times) {
                /* continuous change satisfied -----------------------------*/
                return 1U;
                /* continuous change satisfied -----------------------------*/
            }
        }
        /* change but not big enough */
        else {
            /* retreat option active */
            if (retreat) {
                /* ctrl count fall back */
                JitterCtrl_init(me);
            }
            /* retreat option not active */
            else {
                /* do nothing, count the cumulative jitter change */
            }
        }
    }
    /* no change */
    else if (detect_target == detect_base) {
        /* retreat option active */
        if (retreat) {
            /* ctrl count fall back */
            JitterCtrl_init(me);
        }
        /* retreat option not active */
        else {
            /* do nothing, count the cumulative jitter change */
        }
    }

    /* nothing happend -----------------------------------------------------*/
    return 0U;
    /* nothing happend -----------------------------------------------------*/
}
/* direction: + only -------------------------------------------------------*/

/* direction: - only -------------------------------------------------------*/
uint8_t Jitter_detection_down(
    JitterCtrl *me,
    uint16_t detect_base,
    uint16_t detect_target,
    uint8_t detect_thresh,
    uint8_t jitter_continue_thresh_times,
    uint8_t retreat,
    uint8_t big_jitter)
{
    /* down */
    if      (detect_target < detect_base) {
        // big jitter detection enable */
        if (big_jitter != 0U) {
            if ((detect_base - detect_target) >= big_jitter) {
                /* big_jitter happend --------------------------------------*/
                return 1U;
                /* big_jitter happend --------------------------------------*/
            }
        }

        if ((detect_base - detect_target) >= detect_thresh ) {
            /* the me->jitter_continue_cnt */
            /* must be constructed as 0U before used. */
            ++me->jitter_continue_cnt;
            /* if continuous enough */
            if (me->jitter_continue_cnt == jitter_continue_thresh_times) {
                /* continuous change satisfied -----------------------------*/
                return 1U;
                /* continuous change satisfied -----------------------------*/
            }
        }
        /* change but not big enough */
        else {
            /* retreat option active */
            if (retreat) {
                /* ctrl count fall back */
                JitterCtrl_init(me);
            }
            /* retreat option not active */
            else {
                /* do nothing, count the cumulative jitter change */
            }
        }
    }
    /* no change */
    else if (detect_target == detect_base) {
        /* retreat option active */
        if (retreat) {
            /* ctrl count fall back */
            JitterCtrl_init(me);
        }
        /* retreat option not active */
        else {
            /* do nothing, count the cumulative jitter change */
        }
    }

    /* nothing happend -----------------------------------------------------*/
    return 0U;
    /* nothing happend -----------------------------------------------------*/
}
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
    uint8_t big_jitter)
{
    uint8_t is_jitter;

    is_jitter = 0U;

    if      (jitter_direction == JITTER_DIRECTION_UP) {
        is_jitter = Jitter_detection_up(me,
            detect_base,
            detect_target,
            detect_thresh,
            jitter_continue_thresh_times,
            retreat,
            big_jitter);
    }
    else if (jitter_direction == JITTER_DIRECTION_DOWN) {
        is_jitter = Jitter_detection_down(me,
            detect_base,
            detect_target,
            detect_thresh,
            jitter_continue_thresh_times,
            retreat,
            big_jitter);
    }
    else if (jitter_direction == JITTER_DIRECTION_NONE) {
        is_jitter = Jitter_detection_up(me,
            detect_base,
            detect_target,
            detect_thresh,
            jitter_continue_thresh_times,
            retreat,
            big_jitter)
            |  /*! or */
            Jitter_detection_down(me,
                detect_base,
                detect_target,
                detect_thresh,
                jitter_continue_thresh_times,
                retreat,
                big_jitter);
    }
    else {
        /* error situation */
    }

    return is_jitter;
}
/* application handler -----------------------------------------------------*/

/* test area ---------------------------------------------------------------*/
/* test handlers -----------------------------------------------------------*/
void jitter_test_handler(void) {
    /* instance ------------------------------------------------------------*/
    JitterCtrl test_jitter;
    /* instance ------------------------------------------------------------*/

    /* init ----------------------------------------------------------------*/
    JitterCtrl_init(&test_jitter);
    /* init ----------------------------------------------------------------*/

    /* target input --------------------------------------------------------*/
    // uint8_t change_arr[TEST_SIZE] = {
    //     10, 10, 10, 10, 10,
    //     10, 10, 10, 10, 10
    // };
    // uint8_t change_arr[TEST_SIZE] = {
    //     10, 5, 5, 6, 8,
    //     10, 5, 5, 5, 8
    // };
    // uint8_t change_arr[TEST_SIZE] = {
    //     10, 6, 16, 15, 8,
    //     10, 10, 10, 8, 3
    // };
    uint8_t change_arr[TEST_SIZE] = {
        10, 10, 2, 10, 10,
        10, 10, 10, 10, 10
    };
    /* target input --------------------------------------------------------*/

    /* params setting ------------------------------------------------------*/
    uint8_t jitter_base = change_arr[0];
    uint8_t jitter_detection_times = 4U;
    uint8_t jitter_detection_thresh = 3U;
    uint8_t big_jitter = 7U;
    /* params setting ------------------------------------------------------*/

    /* reference -----------------------------------------------------------*/
    for (uint8_t i = 0U; i < TEST_SIZE; ++i) {
        if (jitter_detection(&test_jitter,
                jitter_base,
                change_arr[i],
                JITTER_DIRECTION_NONE,
                jitter_detection_thresh,
                jitter_detection_times,
                JITTER_RETREAT_DISABLE,
                big_jitter))
        {
            /* one time reference done -------------------------------------*/
            JitterCtrl_init(&test_jitter);
            printf("JitterHappen.\n");
            /* one time reference done -------------------------------------*/
        }
    }
    /* reference -----------------------------------------------------------*/

    return;
}
/* test handlers -----------------------------------------------------------*/
/* test area ---------------------------------------------------------------*/
