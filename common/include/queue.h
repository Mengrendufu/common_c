#ifndef queue_h_
#define queue_h_

/*****************************************************************************
    Here, we always store the data in the void *sto which might cause some
wasted.

    If we want to store bytes in the the *ring, then the size of
sizeof(void *) - sizeof(unsigned char) is wasted.
*****************************************************************************/

/* type cast hepler --------------------------------------------------------*/
#define CIRQUEUE_CAST(type_, unit_) ((type_)(unit_))
/* type cast hepler --------------------------------------------------------*/

/* class -------------------------------------------------------------------*/
typedef struct CircularQueue {
    void *ring;  /*! ==> void *queue_sto[QUEUE_SIZE] */
    uint16_t head;
    uint16_t tail;
    uint16_t qLen;
    uint16_t nUsed;
} CircularQueue;
/* class -------------------------------------------------------------------*/

/* look up macros ----------------------------------------------------------*/
#define CircularQueue_empty(me_) \
    (((me_)->nUsed == 0U) ? (1U) : (0U))
#define CircularQueue_full(me_) \
    (((me_)->nUsed >= (me_)->qLen) ? (1U) : (0U))
/* look up macros ----------------------------------------------------------*/

/* constructor -------------------------------------------------------------*/
void CircularQueue_init(
    CircularQueue *me,
    void *qSto,
    uint16_t qLen);
/* constructor -------------------------------------------------------------*/

/* circular put ------------------------------------------------------------*/
void CircularQueue_put(
    CircularQueue *me,
    void *elemPut);
/* circular put ------------------------------------------------------------*/

/* none-empty getter -------------------------------------------------------*/
void CircularQueue_get(
    CircularQueue *me,
    void *elemGet);
/* none-empty getter -------------------------------------------------------*/

/* test area ---------------------------------------------------------------*/
#define CIRQUEUE_TEST_DATA_SIZE   23U
#define CIRQUEUE_TEST_QUEUE_SIZE  20U
typedef uint32_t CirQueueTest_Type;
void CircularQueue_test(void);
/* test area ---------------------------------------------------------------*/

#endif  /* queue_h_ */
