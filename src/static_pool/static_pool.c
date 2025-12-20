/* dependencies ------------------------------------------------------------*/
#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>

#include "static_pool.h"
/* dependencies ------------------------------------------------------------*/

/* pool initialization -----------------------------------------------------*/
void StaticPool_init(
    StaticPool *me,
    void *poolSto,
    uint16_t poolSize,
    uint16_t blockSize)
{
    FreeBlock *fb;  /* linking */
    uint16_t nBlocks;  /* round up of blocksize */

    me->free_head = poolSto;

    /* round up of blocksize -----------------------------------------------*/
    me->blockSize = (uint16_t)sizeof(FreeBlock);  /* min block size */
    nBlocks = (uint16_t)1;
    while (me->blockSize < blockSize) {
        me->blockSize += (uint16_t)sizeof(FreeBlock);
        ++nBlocks;
    }
    /* round up of blocksize -----------------------------------------------*/

    /* creating block linking ----------------------------------------------*/
    /**
    * REQUIRE:
    *       poolSize >= me->blockSize,
    *       pool sto at least contains one block
    */
    poolSize -= me->blockSize;  /* first block */
    me->nTot = (uint16_t)1;
    fb = (FreeBlock *)me->free_head;
    while (poolSize >= me->blockSize) {
        fb->next = fb + nBlocks;
        fb = fb->next;
        poolSize -= me->blockSize;
        ++me->nTot;
    }
    fb->next = (FreeBlock *)0; /* NULL */
    /* creating block linking ----------------------------------------------*/

    /* attributes done -----------------------------------------------------*/
    me->start = poolSto;
    me->end = fb;
    me->nFree = me->nTot;
    me->nMin  = me->nTot;
    /* attributes done -----------------------------------------------------*/

    return;
}
/* pool initialization -----------------------------------------------------*/

/* block get ---------------------------------------------------------------*/
void *StaticPool_get(StaticPool * const me) {
    FreeBlock *fb;
    fb = (FreeBlock *)0;
    fb = (FreeBlock *)me->free_head;
    if (fb != (FreeBlock *)0) {
        me->free_head = fb->next;
        --me->nFree;
        if (me->nFree < me->nMin) {
            me->nMin = me->nFree;
        }
    }
    return fb;
}
/* block get ---------------------------------------------------------------*/

/* block gc ----------------------------------------------------------------*/
void StaticPool_put(
    StaticPool *me,
    void *block)
{
    ((FreeBlock *)block)->next = (FreeBlock *)me->free_head;
    me->free_head = block;
    ++me->nFree;
    return;
}
/* block gc ----------------------------------------------------------------*/

/* test handler ------------------------------------------------------------*/
#define POOL_STO_SIZE 4U
typedef struct PoolBlock_Test {
    uint8_t id;
    uint32_t age;
    uint32_t money;
} PoolBlock_Test;
void StaticPool_testHandler(void) {
    /* pool sto */
    STATIC_POOL_ELEM_TYPE(PoolBlock_Test) poolSto_test[POOL_STO_SIZE];
    StaticPool poolTest;  /* test instance */

    /* pool initialization -------------------------------------------------*/
    StaticPool_init(
        &poolTest,
        poolSto_test,
        sizeof(poolSto_test),
        sizeof(poolSto_test[0]));
    /* pool initialization -------------------------------------------------*/

    /* pool sto byte info --------------------------------------------------*/
    for (uint16_t i = 0U; i < sizeof(poolSto_test); ++i) {
        printf(
            "poolSto_test[%2u]: addr=0x%p\r\n",
            i, (uint8_t *)poolSto_test + i);
    }
    /* pool sto byte info --------------------------------------------------*/

    /* pool sto block info -------------------------------------------------*/
    for (uint16_t i = 0U; i < poolTest.nTot; ++i) {
        printf(
            "Block %u: addr=0x%p\r\n",
            i, (void *)((uint8_t *)poolTest.start + i * poolTest.blockSize));
    }
    /* pool sto block info -------------------------------------------------*/

    /* pool block get & put ------------------------------------------------*/
    PoolBlock_Test *pb;
    while (poolTest.nFree > 0U) {
        pb = (PoolBlock_Test *)StaticPool_get(&poolTest);
        if (pb != (PoolBlock_Test *)0) {
            printf("Get: addr=0x%p\r\n", pb);
            pb->id = (uint8_t)(poolTest.nTot - poolTest.nFree);
            pb->age = 20U + pb->id;
            pb->money = 1000U * pb->id;
            printf(
                "Get: id=%u, age=%u, money=%u\r\n",
                pb->id, pb->age, pb->money);
        }
    }
    /* pool block get & put ------------------------------------------------*/

    return;
}
/* test handler ------------------------------------------------------------*/
