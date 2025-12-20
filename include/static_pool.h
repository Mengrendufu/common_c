#ifndef static_pool_h_
#define static_pool_h_

/* size of static pool unit ------------------------------------------------*/
#define STATIC_POOL_ELEM_TYPE(type_) \
        struct { void *sto_[((sizeof(type_) - 1U) / sizeof(void*)) + 1U]; }
/* size of static pool unit ------------------------------------------------*/

/* free block single link list ---------------------------------------------*/
typedef struct FreeBlock {
    struct FreeBlock *next;
} FreeBlock;
/* free block single link list ---------------------------------------------*/

/* static pool -------------------------------------------------------------*/
typedef struct StaticPool {
    void *free_head;  /*! get & put */
    void *start;
    void *end;
    uint16_t blockSize;
    uint16_t nTot;
    uint16_t nFree;
    uint16_t nMin;  /*! system monitor */
} StaticPool;
/* static pool -------------------------------------------------------------*/

/* operations --------------------------------------------------------------*/
/* initialization ----------------------------------------------------------*/
void StaticPool_init(
    StaticPool * const me,
    void * const poolSto,
    uint16_t poolSize,
    uint16_t blockSize);
/* initialization ----------------------------------------------------------*/

/* get ---------------------------------------------------------------------*/
void *StaticPool_get(StaticPool * const me);
/* get ---------------------------------------------------------------------*/

/* put ---------------------------------------------------------------------*/
void StaticPool_put(
    StaticPool * const me,
    void *block);
/* put ---------------------------------------------------------------------*/
/* operations --------------------------------------------------------------*/

/* test handler ------------------------------------------------------------*/
void StaticPool_testHandler(void);
/* test handler ------------------------------------------------------------*/

#endif /* static_pool_h_ */
