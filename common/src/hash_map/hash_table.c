/* dependencies ------------------------------------------------------------*/
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "void_ops.h"
#include "hash_table.h"
/* dependencies ------------------------------------------------------------*/

/* hash algorithm ----------------------------------------------------------*/
static unsigned long int hash_int(int key, size_t capacity) {
    if (key < 0) {
        key = -key;
    }
    return key % capacity;  /* mod */
}
static unsigned long int hash_djb2(const char *s, size_t cap) {
    unsigned long int hash = 5381;
    int c;
    while ((c = *s++)) {
        hash = ((hash << 5) + hash) + c;
    }
    return hash % cap;
}
/* hash algorithm ----------------------------------------------------------*/

/* hash key ----------------------------------------------------------------*/
static unsigned long HashTable_hashKey(
    HashNode_KeyType type,
    void *key,
    size_t cap)
{
    return (type == KEY_INT)
            ? hash_int((int)ALIGN_PTR_LEN(key), cap)
            : hash_djb2((char *)key, cap);
}
/* hash key ----------------------------------------------------------------*/

/* =============================
 * hash node create & free
 * ============================= */
static HashNode *HashTable_createNode(
    HashNode_KeyType type, void *key, void *value)
{
    HashNode *node = malloc(sizeof(HashNode));
    node->type = type;
    node->value = value;
    node->next = NULL;
    if (type == KEY_INT) {
        node->key = key;
    } else {
        node->key = strdup((char *)key); /* string copy */
    }
    return node;
}
static void HashTable_freeNode(HashNode *node) {
    if (node->type == KEY_STR) {
        free(node->key);
    }
    free(node);
    return;
}

/* =============================
 * key compare
 * ============================= */
static int HashTable_keyIsEqual(
    HashNode *n,
    HashNode_KeyType type,
    void *key)
{
    if (n->type != type) {
        return 0;
    }
    if (type == KEY_INT) {
        return ((int)ALIGN_PTR_LEN(n->key)) == ((int)ALIGN_PTR_LEN(key));
    }
    else {
        return strcmp((char *)(n->key), (char *)key) == 0;
    }
}
static void HashTable_freeChain(HashNode *node) {
    while (node) {
        HashNode *tmp = node;
        node = node->next;
        HashTable_freeNode(tmp);
    }
    return;
}

/* =============================
 * resize when inserting
 * ============================= */
static void HashTable_resize(HashTable *ht, size_t new_capacity) {
    HashNode **new_buckets = calloc(new_capacity, sizeof(HashNode *));
    for (size_t i = 0; i < ht->capacity; i++) {
        HashNode *node = ht->buckets[i];
        while (node) {
            HashNode *next = node->next;
            /* re-hash */
            unsigned long new_idx = HashTable_hashKey(
                                        node->type,
                                        node->key,
                                        new_capacity);
            node->next = new_buckets[new_idx];
            new_buckets[new_idx] = node;
            node = next;
        }
    }
    free(ht->buckets);  /* free old buckets */
    ht->buckets = new_buckets;
    ht->capacity = new_capacity;
    return;
}

/* =============================
 * create hash table
 * ============================= */
HashTable *HashTable_create(void) {
    HashTable *ht = malloc(sizeof(HashTable));
    ht->capacity = INITIAL_CAPACITY;
    ht->size = 0;
    ht->buckets = calloc(ht->capacity, sizeof(HashNode *));
    return ht;
}
/* =============================
 * destroy hash table
 * ============================= */
void HashTable_free(HashTable *ht) {
    /* free nodes */
    for (size_t i = 0; i < ht->capacity; i++) {
        HashTable_freeChain(ht->buckets[i]);
    }
    /* free buckets */
    free(ht->buckets);
    /* free table head */
    free(ht);
    return;
}

/* =============================
 * insert, update value if key overrites
 * ============================= */
void HashTable_insert(
    HashTable *ht,
    HashNode_KeyType type,
    void *key,
    void *value)
{
    unsigned long idx = HashTable_hashKey(type, key, ht->capacity);
    /* value update */
    for (HashNode *n = ht->buckets[idx]; n; n = n->next) {
        if (HashTable_keyIsEqual(n, type, key)) {
            n->value = value;
            return;
        }
    }
    /* insert new node */
    HashNode *node = HashTable_createNode(type, key, value);
    node->next = ht->buckets[idx];
    ht->buckets[idx] = node;
    ht->size++;
    /* resize */
    if (ht->capacity / (float)ht->size < LOAD_FACTOR_LIMIT_INV) {
        HashTable_resize(ht, ht->capacity * 2);
    }
    return;
}

/* =============================
 * node delete
 * ============================= */
int HashTable_remove(HashTable *ht, HashNode_KeyType type, void *key) {
    unsigned long idx = HashTable_hashKey(type, key, ht->capacity);
    HashNode *node = ht->buckets[idx], *prev = NULL;
    while (node) {
        if (HashTable_keyIsEqual(node, type, key)) {
            if (prev) {
                prev->next = node->next;
            }
            else {
                ht->buckets[idx] = node->next;
            }
            HashTable_freeNode(node);
            --ht->size;
            return 1;
        }
        prev = node;
        node = node->next;
    }
    return 0;
}

/* =============================
 * find
 * ============================= */
void *HashTable_find(HashTable *ht, HashNode_KeyType type, void *key) {
    unsigned long int idx = HashTable_hashKey(type, key, ht->capacity);
    HashNode *node = ht->buckets[idx];
    for (HashNode *n = ht->buckets[idx]; n; n = n->next) {
        if (HashTable_keyIsEqual(n, type, key))
            return &node->value;
        node = node->next;
    }
    return NULL;
}

/* =============================
 * hash table print
 * ============================= */
void HashTable_print(HashTable *ht) {
    if (ht) {
        printf("HashTable(capacity=%zu, size=%zu):\n", ht->capacity, ht->size);
        for (size_t i = 0; i < ht->capacity; i++) {
            printf("[%2zu] -> ", i);
            for (HashNode *n = ht->buckets[i]; n; n = n->next) {
                if (n->type == KEY_INT)
                    printf(
                        "(int %d : %d) -> ",
                        (int)ALIGN_PTR_LEN(n->key), (int)ALIGN_PTR_LEN(n->value));
                else
                    printf(
                        "(str \"%s\" : %d) -> ",
                        (char *)n->key, (int)ALIGN_PTR_LEN(n->value));
            }
            printf("NULL\n");
        }
    }
    else {
        printf("HashTable doesn't exist!\r\n");
    }
    return;
}
/* test handler ------------------------------------------------------------*/
void HashTable_testHandler(void) {
    printf("Hash table test -------------------------------------------\r\n");

    HashTable *ht = HashTable_create();

    int testArr[] = {9, 8, 5, 3, 2, 18, 7, -6, 4, 0};
    uint8_t testArrSize = sizeof(testArr)/sizeof(testArr[0]);
    /* insert */
    for (uint8_t i = 0; i < testArrSize; ++i) {
        HashTable_insert(
            ht,
            KEY_INT,
            (void *)ALIGN_PTR_LEN(testArr[i]),
            (void *)ALIGN_PTR_LEN(i));
    }

    HashTable_insert(ht, KEY_STR, "HelloWorld", (void *)(233));
    HashTable_insert(ht, KEY_STR, "HuSicheng", (void *)(666));
    HashTable_insert(ht, KEY_STR, "c", (void *)(88));

    /* print check */
    // HashTable_print(ht);

    /* find */
    int *v;
    for (int i = -100; i < 100; ++i) {
        v = HashTable_find(ht, KEY_INT, (void *)ALIGN_PTR_LEN(i));
        if (v) {
            printf(
                "find: %2d in testArr[%2d]!\r\n",
                i, *v);

            if (*v == testArr[3]) {
                HashTable_remove(ht, KEY_INT, (void *)ALIGN_PTR_LEN(*v));
            }
        }
    }

    v = HashTable_find(ht, KEY_STR, "HuSicheng");
    if (v) {
        printf("find: %s: %d\r\n", "HuSicheng", *v);
    }

    HashTable_free(ht);
    ht = NULL;

    /* print check */
    // HashTable_print(ht);

    return;
}
/* test handler ------------------------------------------------------------*/
