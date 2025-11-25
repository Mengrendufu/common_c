/* standard libs */
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <stdbool.h>

/* common modules */
#include "crc.h"
#include "queue.h"
#include "widths.h"
#include "endians.h"
#include "jitter_detection.h"
#include "timer.h"
#include "static_pool.h"
#include "quick_sort.h"
#include "merge_sort.h"
#include "heap_sort.h"
#include "insert_sort.h"
#include "hash_table.h"

/* main */
int main(int argc, char* argv[]) {
    /* opening titles */
    (void)argc;
    (void)argv;
    printf("Hello, world!\r\n");

    /* endian judge & convert */
    // endian_test();

    /* width test */
    system_lengths_test();

    /* jitter detection */
    // jitter_test_handler();

    /* crc test handler */
    // crc_test_handler();

    /* circular queue test */
    CircularQueue_test();

    /* timer test */
    // Timer_test();

    /* static pool test */
    // StaticPool_testHandler();

    /* quick sort test */
    QuickSort_testHandler();

    /* merge sort test */
    MergeSort_testHandler();

    /* heap sort test */
    // HeapSort_testHandler();

    /* insert sort test */
    // InsertSort_testHandler();

    /* hash map test */
    HashTable_testHandler();

    return 0;
}
