//============================================================================
// Copyright (C) 2026 Sunny Matato
//
// This program is free software. It comes without any warranty, to
// the extent permitted by applicable law. You can redistribute it
// and/or modify it under the terms of the Do What The Fuck You Want
// To Public License, Version 2, as published by Sam Hocevar.
// See http://www.wtfpl.net/ for more details.
//============================================================================
#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>
#include <string.h>
#include "common_c_test.h"
#include "crc_table_gen.h"
#include "crc8.h"
#include "crc8_maxim.h"
#include "crc16_ccitt_false.h"
#include "crc16_ccitt.h"
#include "crc16_maxim.h"
#include "crc32.h"
#include "crc32_mpeg2.h"
#include "sm_endian.h"
#include "hash_table.h"
#include "jitter_detection.h"
#include "queue.h"
#include "static_pool.h"
#include "heap_sort.h"
#include "linklist.h"
#include "timer.h"
#include "is_prime.h"

//============================================================================
#define NAME_SIZE 32
static const char commonTestNames[34][NAME_SIZE] = {
    "---TEST_START_MARKER---",   // [0] 首部测试标识 (23 chars)
    "Ada_Lovelace",              // 世界上第一位程序员
    "Alan_Turing",               // 计算机科学之父
    "John_von_Neumann",          // 冯·诺依曼架构奠基人
    "Claude_Shannon",            // 信息论之父 (Information Theory)
    "Grace_Hopper",              // 编译器之母 (COBOL)
    "Dennis_Ritchie",            // C 语言 & Unix 之父
    "Ken_Thompson",              // Unix & Go 语言设计者
    "Brian_Kernighan",           // K&R C 的作者之一
    "Donald_Knuth",              // 《计算机程序设计艺术》作者
    "Edsger_Dijkstra",           // 算法大师 (最短路径)
    "Leslie_Lamport",            // 分布式系统 & LaTeX 开发者
    "Barbara_Liskov",            // 里氏替换原则 (LSP) 提出者
    "Tim_Berners_Lee",           // 万维网 (WWW) 发明者
    "Vint_Cerf",                 // TCP/IP 协议联合设计者
    "James_Gosling",             // Java 语言之父
    "Guido_van_Rossum",          // Python 语言之父
    "Bjarne_Stroustrup",         // C++ 之父
    "Linus_Torvalds",            // Linux & Git 缔造者
    "Richard_Stallman",          // GNU & 自由软件运动领袖
    "Anders_Hejlsberg",          // C# / TypeScript 架构师
    "Bill_Joy",                  // VI 编辑器 & BSD 作者
    "John_McCarthy",             // Lisp 语言 & AI 之父
    "Niklaus_Wirth",             // Pascal 语言之父
    "Tony_Hoare",                // 快速排序 (Quicksort) 发明者
    "Margaret_Hamilton",         // 阿波罗计划软件工程先驱
    "Shafi_Goldwasser",          // 现代密码学图灵奖得主
    "Geoffrey_Hinton",           // 深度学习 (Deep Learning) 教父
    "Yann_LeCun",                // 卷积神经网络 (CNN) 先驱
    "Yoshua_Bengio",             // 现代 AI 神经网络专家
    "Andrew_Ng",                 // 吴恩达 (AI 落地与教育)
    "Satoshi_Nakamoto",          // 比特币/区块链创始人
    "Jeff_Dean",                 // Google 架构神级人物 (MapReduce)
    "---TEST_END_MARKERER---"    // [33] 尾部测试标识 (24 chars)
};

// crc =======================================================================
#define POLY_WIDTH 16
#define POLY_GEN   0x1021
#define IS_REFIN   false

#if (POLY_WIDTH == 8)
    typedef uint8_t CrcTblGen_Poly;
#elif (POLY_WIDTH == 16)
    typedef uint16_t CrcTblGen_Poly;
#elif (POLY_WIDTH == 32)
    typedef uint32_t CrcTblGen_Poly;
#endif // POLY_WIDTH

static void CRC_TableGen_test(void);
static void CRC_TableGen_test(void) {
    CrcTblGen_Poly poly = POLY_GEN;
    CRC_tableGen(POLY_WIDTH,
                 (uint8_t *)&poly,
                 IS_REFIN);
}

//============================================================================
#define CRC_STREAM_LEN 6
static uint8_t crcStream[CRC_STREAM_LEN] = {
    0x98, 0x53, 0x25, 0x00, 0x00, 0x00
};
static void CRC_test(void);
static void CRC_test(void) {
    //........................................................................
    printf("Original stream: ");
    for (uint16_t i = 0; i < CRC_STREAM_LEN; ++i) {
        if (!(i == CRC_STREAM_LEN - 1)) {
            printf("0x%02X, ", crcStream[i]);
        } else {
            printf("0x%02X", crcStream[i]);
        }
    }
    printf("\n");

    //........................................................................
    uint8_t crcRes_crc8 = crc8(crcStream, CRC_STREAM_LEN);
    uint8_t crcRes_crc8_maxim = crc8_maxim(crcStream, CRC_STREAM_LEN);
    uint16_t crcRes_crc16_ccitt_false = crc16_ccitt_false(crcStream,
                                                          CRC_STREAM_LEN);
    uint16_t crcRes_crc16_ccitt = crc16_ccitt(crcStream, CRC_STREAM_LEN);
    uint16_t crcRes_crc16_maxim = crc16_maxim(crcStream, CRC_STREAM_LEN);
    uint32_t crcRes_crc32 = crc32(crcStream, CRC_STREAM_LEN);
    uint32_t crcRes_crc32_mpeg2 = crc32_mpeg2(crcStream, CRC_STREAM_LEN);

    //........................................................................
    printf("crc8: 0x%02X\n", crcRes_crc8);
    printf("crc8_maxim: 0x%02X\n", crcRes_crc8_maxim);
    printf("crc16_ccitt_false: 0x%04X\n", crcRes_crc16_ccitt_false);
    printf("crc16_ccitt: 0x%04X\n", crcRes_crc16_ccitt);
    printf("crc16_maxim: 0x%04X\n", crcRes_crc16_maxim);
    printf("crc32: 0x%08X\n", crcRes_crc32);
    printf("crc32: 0x%08X\n", crcRes_crc32_mpeg2);
}

//============================================================================
static void EndianTest(void);
static void EndianTest(void) {
    if (isLittleEndian()) {
        printf("Arch is little endian.\n");
    } else {
        printf("Arch is big endian.\n");
    }

    uint16_t localVar_u16 = 0x1234;
    uint16_t cvtVar_u16   = SWAP_16(localVar_u16);
    printf("localVar_u16: 0x%04X ===> cvtVar_u16: 0x%04X\n",
           localVar_u16, cvtVar_u16);

    uint32_t localVar_u32 = 0x12345678;
    uint32_t cvtVar_u32   = SWAP_32(localVar_u32);
    printf("localVar_u32: 0x%08X ===> cvtVar_u32: 0x%08X\n",
           localVar_u32, cvtVar_u32);

    uint64_t localVar_u64 = 0x123456789ABCDEFF;
    uint64_t cvtVar_u64   = SWAP_64(localVar_u64);
    printf("localVar_u64: 0x%016lX ===> cvtVar_u64: 0x%016lX\n",
           (unsigned long)localVar_u64, (unsigned long)cvtVar_u64);
}

//============================================================================
static void HashTable_print(HashTable *ht);
static void HashTable_test(void);

static void HashTable_test(void) {
    HashTable *ht = HashTable_create();

    HashTable_insert(ht, KEY_INT,
                     VOID_CAST(98532500), VOID_CAST(2333));
    HashTable_print(ht);

    HashTable_insert(ht, KEY_STR,
                     VOID_CAST("SunnyMatato"), VOID_CAST(666));
    HashTable_print(ht);
}

static void HashTable_print(HashTable *ht) {
    printf("\n");
    for (uint16_t i = 0; i < ht->capacity; ++i) {
        if (ht->buckets[i]) {
            printf("BUCK[%03d]: ", i);
            HashNode *nd = ht->buckets[i];
            while (nd) {
                if (nd->type == KEY_INT) {
                    printf("%lld --> ", P2UINT(nd->key));
                } else if (nd->type == KEY_STR) {
                    printf("%s --> ", (char *)(nd->key));
                }
                nd = nd->next;
            }
            printf("NULL\n");
        } else {
            printf("BUCK[%03d]: NULL\n", i);
        }
    }
}

//============================================================================
#define JITTER_LEN 16
static JitterCtrType jitterStream[JITTER_LEN] = {
    9, 3, 5, 3, 2, 5, 0, 0, 3, 7, 5, 3, 4, 3, 5, 8
};
static JitterCtrl jitterInst;
static void JitterDetection_test(void);
static void JitterDetection_test(void) {
    // init... ---------------------------------------------------------------
    JitterCtrl_setCtr(&jitterInst, 3, 3);
    JitterCtrl_setBase(&jitterInst, jitterStream[0]);
    JitterCtrl_setMargin(&jitterInst, 3, 5);
    JitterCtrl_setOpts(&jitterInst, JITTER_DIRECTION_NONE, true);
    for (uint16_t i = 0; i < JITTER_LEN; ++i) {
        if (Jitter_monitor(&jitterInst, jitterStream[i])) {
            if (i < JITTER_LEN - 1) {
                printf("Base %02d Jit here: stream[%02d]: %02d --> ",
                       jitterInst.base, i, jitterStream[i]);
            } else {
                printf("Base %02d Jit here: stream[%02d]: %02d",
                       jitterInst.base, i, jitterStream[i]);
            }
            JitterCtrl_setBase(&jitterInst, jitterStream[i]);
        } else {
            if (i < JITTER_LEN - 1) {
                printf("%02d --> ", jitterStream[i]);
            } else {
                printf("%02d", jitterStream[i]);
            }
        }
    }
    printf("\n");
}

//============================================================================
typedef struct {
    char name[NAME_SIZE];
    uint16_t age;
    uint32_t save;
} DataBaseType;

#define STATIC_POOL_SIZE 16
#define QUEUE_SIZE 32

static void Pool_Queue_test(void);
static void Pool_Queue_test(void) {
    // StaticPool...
    StaticPool staticPool;
    STATIC_POOL_ELEM_TYPE(DataBaseType) staticPoolSto[STATIC_POOL_SIZE];
    StaticPool_init(&staticPool,
                    staticPoolSto, sizeof(staticPoolSto),
                    sizeof(staticPoolSto[0]));

    // Queue...
    CircularQueue queue;
    void *queueSto[QUEUE_SIZE];
    CircularQueue_init(&queue, queueSto, SM_ARR_SIZE(queueSto));

    //........................................................................
    printf("StaticPoolStart --> StaticPoolEnd:\n");
    void *poolStart = staticPool.start;
    while (poolStart != (void *)0) {
        printf("0x%p --> ", poolStart);
        poolStart = (*((void **)poolStart));
    }
    printf("NULL\n");

    //........................................................................
    printf("Queue with StaticPool:\n");
    uint8_t i = 0;
    while (!CircularQueue_full(&queue)) {
        DataBaseType *fb = (DataBaseType *)StaticPool_get(&staticPool);
        if (fb != (DataBaseType *)0) {
            fb->age = 18 + i;
            fb->save = 100000 * i;
            memcpy(fb->name, commonTestNames[i++], NAME_SIZE);
            CircularQueue_put(&queue, (void *)fb);
        } else {
            printf("StaticPool empty.\n");
            break;
        }
    }

    while (!CircularQueue_empty(&queue)) {
        DataBaseType *dataBlk = (DataBaseType *)CircularQueue_get(&queue);

        printf("name: %-24s -- age: %3d -- saving: %10d\n",
               dataBlk->name, dataBlk->age, dataBlk->save);

        StaticPool_put(&staticPool, (void *)dataBlk);
    }

    //========================================================================
    DataBaseType *anyBlock = (DataBaseType *)StaticPool_get(&staticPool);
    printf("\nspoolStart: 0x%p, poolEnd: 0x%p\n"
           "anyBlock: 0x%p\n",
           staticPool.start, staticPool.end,
           (void *)anyBlock);
}

//============================================================================
static void GenericHeapSort_test(void);
static void GenericHeapSort_test(void) {
    static HeapSortArrType testArr[HEAP_SORT_ARR_SIZE] = {
        9, 8, 5, 3, 2, 5, 0, 0, 0
    };

    printf("Before sorting: ");
    for (uint16_t i = 0; i < HEAP_SORT_ARR_SIZE; ++i) {
        printf("%d ", testArr[i]);
    }
    printf("\n");

#if (HEAP_SORT_USE_RECURSIVE == 1) // Recursive usage.
    printf("Recursive sorting...\n");
    HeapSort_heapSortRecursive((void *)testArr, HEAP_SORT_ARR_SIZE,
                               sizeof(HeapSortArrType),
                               (HeapSortCmp)&GenericHeapSort_cmp);
#else // Iterative usage.
    printf("Iterative sorting...\n");
    HeapSort_heapSortIterative((void *)testArr, HEAP_SORT_ARR_SIZE,
                               sizeof(HeapSortArrType),
                               (HeapSortCmp)&GenericHeapSort_cmp);
#endif // Recursive or iterative.

    printf("After  sorting: ");
    for (uint16_t i = 0; i < HEAP_SORT_ARR_SIZE; ++i) {
        printf("%d ", testArr[i]);
    }
    printf("\n");
}

//============================================================================
typedef struct {
    char name[NAME_SIZE];
    uint8_t age;
    uint16_t grade;
    ListNode link; // None-intrusive LinkList.
} Student;
#define STUDENT_NUM 8

static void Print_students(ListNode *sLt);
static void Print_students(ListNode *sLt) {
    printf("%-32s -- %5s -- %5s\n", "Name", "Age", "Grade");
    while (sLt) {
        Student *s = container_of(sLt, Student, link);
        printf("%-32s -- %5d -- %5d\n",
               s->name, s->age, s->grade);
        sLt = sLt->next;
    }
}

//............................................................................
static bool Student_gradeAssendingCmp(void *sLtLeft, void *sLtRight);
static bool Student_gradeAssendingCmp(void *sLtLeft, void *sLtRight) {
    Student *sLeft  = container_of(sLtLeft,  Student, link);
    Student *sRight = container_of(sLtRight, Student, link);
    if (sLeft->grade <= sRight->grade) return true;
    else                               return false;
}

//............................................................................
static bool Student_ageAssendingCmp(void *sLtLeft, void *sLtRight);
static bool Student_ageAssendingCmp(void *sLtLeft, void *sLtRight) {
    Student *sLeft  = container_of(sLtLeft,  Student, link);
    Student *sRight = container_of(sLtRight, Student, link);
    if (sLeft->age >= sRight->age) return true;
    else                           return false;
}

//............................................................................
static void LinkList_test(void);
static void LinkList_test(void) {
    // Initializing...
    Student students[STUDENT_NUM];
    memcpy(students[0].name, commonTestNames[0 + 1], NAME_SIZE);
    students[0].age = 32;
    students[0].grade = 96;
    memcpy(students[1].name, commonTestNames[1 + 1], NAME_SIZE);
    students[1].age = 32;
    students[1].grade = 96;
    memcpy(students[2].name, commonTestNames[2 + 1], NAME_SIZE);
    students[2].age = 28;
    students[2].grade = 90;
    memcpy(students[3].name, commonTestNames[3 + 1], NAME_SIZE);
    students[3].age = 19;
    students[3].grade = 86;
    memcpy(students[4].name, commonTestNames[4 + 1], NAME_SIZE);
    students[4].age = 26;
    students[4].grade = 92;
    memcpy(students[5].name, commonTestNames[5 + 1], NAME_SIZE);
    students[5].age = 24;
    students[5].grade = 88;
    memcpy(students[6].name, commonTestNames[6 + 1], NAME_SIZE);
    students[6].age = 33;
    students[6].grade = 91;
    memcpy(students[7].name, commonTestNames[7 + 1], NAME_SIZE);
    students[7].age = 36;
    students[7].grade = 99;
    // Linking...
    for (uint16_t i = 0; i < STUDENT_NUM; ++i) {
        if (i < STUDENT_NUM - 1) {
            students[i].link.next = &students[i+1].link;
        } else {
            students[i].link.next = (ListNode *)0;
        }
    }
    ListNode *sLt = &students[0].link; // Head of list.

    // Initial print.
    printf("\nInitial:\n"); Print_students(sLt);

    // MergeSort: grade.
    sLt = LinkList_mergeSort(sLt, (MergeSortCmp)&Student_gradeAssendingCmp);
    printf("\nAfter Grade sort:\n"); Print_students(sLt);

    // MergeSort: age.
    sLt = LinkList_mergeSort(sLt, (MergeSortCmp)&Student_ageAssendingCmp);
    printf("\nAfter age sort:\n"); Print_students(sLt);

    // LinkList reverse.
    sLt = LinkList_reverse(sLt);
    printf("\nAfter reverse:\n"); Print_students(sLt);
}

//============================================================================
static void Timer_timeoutCb_one(void);
static void Timer_timeoutCb_one(void) {
    printf("Timer timeout callback one triggered.\n");
}

static void Timer_timeoutCb_two(void);
static void Timer_timeoutCb_two(void) {
    printf("Timer timeout callback two triggered.\n");
}

static void Timer_test(void);
static void Timer_test(void) {
    Timer timerOne;
    Timer_ctor(&timerOne, Timer_timeoutCb_one);
    Timer_set(&timerOne, 0, 0, 10); // 10 seconds
    Timer timerTwo;
    Timer_ctor(&timerTwo, Timer_timeoutCb_two);
    Timer_set(&timerTwo, 0, 0, 20); // 20 seconds
    printf("Timers started. Simulating 30 seconds of ticks...\n");

    for (uint32_t tick = 0; tick < 30; ++tick) {
        printf("Tick %u: ", tick);
        Timer_countdown(&timerOne);
        Timer_countdown(&timerTwo);

        if (Timer_is_clear(&timerOne)) {
            printf("TimerOne cleared ");
        }
        if (Timer_is_clear(&timerTwo)) {
            printf("TimerTwo cleared ");
        }
        printf("\n");
    }

    printf("Timer test completed.\n");
}

// Math. =====================================================================
void Math_prime_test(void) {
    printf("\nPrime test:================================================\n");

    uint32_t count = 0;
    for (uint32_t n = 1; n <= 100; n++) {
        if (isPrime(n)) {
            printf("%2u ", n);
            ++count;
            if (count % 10 == 0) {
                printf("\n");
            }
        }
    }
    printf("\nTotal primes from 1 to 100: %u\n", count);
}

//============================================================================
void CommonC_test(void) {
    // crc. ==================================================================
    printf("\nCRCTableGen:===============================================\n");
    CRC_TableGen_test();

    // crc8. .................................................................
    printf("\nCRC test:==================================================\n");
    CRC_test();

    //========================================================================
    printf("\nendian test:===============================================\n");
    EndianTest();

    //========================================================================
    printf("\nHashTable test:============================================\n");
    HashTable_test();

    //========================================================================
    printf("\nJitter test:===============================================\n");
    JitterDetection_test();

    //========================================================================
    printf("\nPoolQueue test:============================================\n");
    Pool_Queue_test();

    //========================================================================
    printf("\nGeneric HeapSort test: ====================================\n");
    GenericHeapSort_test();

    //========================================================================
    printf("\nLinkList test: ============================================\n");
    LinkList_test();

    //========================================================================
    printf("\nTimer test: ===============================================\n");
    Timer_test();

    //========================================================================
    printf("\nMath Prime test: ==========================================\n");
    Math_prime_test();
}
