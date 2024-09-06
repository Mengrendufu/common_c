/* dependencies ------------------------------------------------------------*/
#include "stdint.h"
#include "stdio.h"
#include "queue.h"
/* dependencies ------------------------------------------------------------*/

/* constructor -------------------------------------------------------------*/
void CircularQueue_init(
    CircularQueue *me,
    void *qSto,
    uint16_t qLen)
{
    me->ring   = qSto;
    me->head   = 0U;
    me->tail   = 0U;
    me->qLen   = qLen;
    me->nUsed  = 0U;

    return;
}
/* constructor -------------------------------------------------------------*/

/* circular put ------------------------------------------------------------*/
void CircularQueue_put(
    CircularQueue *me,
    void *elemPut)
{
    /* Element input (type erasure) ----------------------------------------*/
    *(CIRQUEUE_CAST(void **, me->ring) + me->head)
        = *CIRQUEUE_CAST(void **, elemPut);
    /* Element input (type erasure) ----------------------------------------*/

    /* count adjust --------------------------------------------------------*/
    if (me->head == 0U) {
        me->head = me->qLen;
    }
    --me->head;
    /* count adjust --------------------------------------------------------*/

    if (me->nUsed < me->qLen) {
        /* not full --------------------------------------------------------*/
        ++me->nUsed;
        /* not full --------------------------------------------------------*/
    }
    else {
        /* overflow, wrap around -------------------------------------------*/
        if (me->tail == 0U) {
            me->tail = me->qLen;
        }
        --me->tail;
        /* overflow, wrap around -------------------------------------------*/
    }

    return;
}
/* circular put ------------------------------------------------------------*/

/* none-empty getter -------------------------------------------------------*/
void CircularQueue_get(
    CircularQueue *me,
    void *elemGet)
{
    /* Element input (type erasure) ----------------------------------------*/
    *CIRQUEUE_CAST(void **, elemGet)
        = *(CIRQUEUE_CAST(void **, me->ring) + me->tail);
    /* Element input (type erasure) ----------------------------------------*/

    /* wrap around ---------------------------------------------------------*/
    if (me->tail == 0U) {
        me->tail = me->qLen;
    }
    /* wrap around ---------------------------------------------------------*/
    --me->tail;
    --me->nUsed;

    return;
}
/* none-empty getter -------------------------------------------------------*/

/* test area ---------------------------------------------------------------*/
void CircularQueue_test(void) {
    /* circular queue ------------------------------------------------------*/
    CircularQueue queue_test;
    void *queue_sto_test[CIRQUEUE_TEST_QUEUE_SIZE];
    CircularQueue_init(
        &queue_test,
        (void *)queue_sto_test,
        CIRQUEUE_TEST_QUEUE_SIZE);
    /* circular queue ------------------------------------------------------*/

    /* test data -----------------------------------------------------------*/
    CirQueueTest_Type test_data[CIRQUEUE_TEST_DATA_SIZE];
    for (uint8_t i = 0U; i < CIRQUEUE_TEST_DATA_SIZE; ++i) {
        test_data[i] = i;
    }
    /* test data -----------------------------------------------------------*/

    /* en queue ------------------------------------------------------------*/
    for (uint8_t i = 0U; i < CIRQUEUE_TEST_DATA_SIZE; ++i) {
        CircularQueue_put(
            &queue_test,
            (void *)&test_data[i]);
    }
    /* en queue ------------------------------------------------------------*/

    /* de queue & print out ------------------------------------------------*/
    CirQueueTest_Type tmp;
    while (!CircularQueue_empty(&queue_test)) {
        CircularQueue_get(
            &queue_test,
            &tmp);
        printf("%d ", tmp);
    }
    printf("\r\n");
    /* de queue & print out ------------------------------------------------*/

    return;
}
/* test area ---------------------------------------------------------------*/
