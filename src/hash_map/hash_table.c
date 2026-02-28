//============================================================================
// Copyright (C) 2026 Sunny Matato
//
// This program is free software. It comes without any warranty, to
// the extent permitted by applicable law. You can redistribute it
// and/or modify it under the terms of the Do What The Fuck You Want
// To Public License, Version 2, as published by Sam Hocevar.
// See http://www.wtfpl.net/ for more details.
//============================================================================
#include "hash_table.h"

//============================================================================
static unsigned long int hash_int(int key, size_t capacity) {
    if (key < 0) key = -key;
    return key % capacity;
}

//............................................................................
static unsigned long int hash_djb2(const char *s, size_t cap) {
    unsigned long int hash = 5381;
    int c;
    while ((c = *s++)) hash = ((hash << 5) + hash) + c;
    return hash % cap;
}

//............................................................................
static unsigned long HashTable_hashKey(HashNode_KeyType type,
                                       void *key,
                                       size_t cap)
{
    return (type == KEY_INT)
                ? hash_int((int)P2UINT(key), cap)
                : hash_djb2((char *)key, cap);

}

//============================================================================
static HashNode *HashTable_createNode(HashNode_KeyType type,
                                      void *key,
                                      void *value)
{
    HashNode *node = malloc(sizeof(HashNode));
    node->type = type;
    node->value = value;
    node->next = (HashNode *)0;
    if (type == KEY_INT) node->key = key;
    else                 node->key = strdup((char *)key);
    return node;
}

//............................................................................
static void HashTable_freeNode(HashNode *node) {
    if (node->type == KEY_STR) free(node->key); // (*strdup).
    free(node);
}

//............................................................................
static void HashTable_freeChain(HashNode *node) {
    while (node) {
        HashNode *tmp = node;
        node = node->next;
        HashTable_freeNode(tmp);
    }
}

//............................................................................
static bool HashTable_keyIsEqual(HashNode *n,
                                 HashNode_KeyType type,
                                 void *key)
{
    if (n->type != type) return false;
    if (type == KEY_INT) {
        return ((int)P2UINT(n->key)) == ((int)P2UINT(key));
    } else {
        return (strcmp((char *)(n->key), (char *)key) == 0);
    }
}

//============================================================================
static void HashTable_resize(HashTable *ht, size_t new_capacity) {
    HashNode **new_buckets = calloc(new_capacity,
                                    sizeof(HashNode *));
    for (size_t i = 0; i < ht->capacity; i++) {
        HashNode *node = ht->buckets[i];
        while (node) {
            HashNode *next = node->next;
            unsigned long new_idx = HashTable_hashKey(node->type,
                                                      node->key,
                                                      new_capacity);
            node->next = new_buckets[new_idx];
            new_buckets[new_idx] = node;
            node = next;
        }
    }
    free(ht->buckets);
    ht->buckets = new_buckets;
    ht->capacity = new_capacity;
}

//============================================================================
HashTable *HashTable_create(void) {
    HashTable *ht = malloc(sizeof(HashTable));
    ht->capacity = INITIAL_CAPACITY;
    ht->size = 0;
    ht->buckets = calloc(ht->capacity,
                         sizeof(HashNode *));
    return ht;
}

//............................................................................
void HashTable_free(HashTable *ht) {
    for (size_t i = 0; i < ht->capacity; i++) {
        HashTable_freeChain(ht->buckets[i]);
    }
    free(ht->buckets);
    free(ht);
}

//............................................................................
void HashTable_insert(HashTable *ht,
                      HashNode_KeyType type,
                      void *key,
                      void *value)
{
    unsigned long idx = HashTable_hashKey(type,
                                          key,
                                          ht->capacity);
    for (HashNode *n = ht->buckets[idx]; n; n = n->next) {
        if (HashTable_keyIsEqual(n, type, key)) {
            n->value = value;
            return;
        }
    }
    HashNode *node = HashTable_createNode(type, key, value);
    node->next = ht->buckets[idx];
    ht->buckets[idx] = node;
    ++ht->size;
    if (ht->capacity < ht->size * LOAD_FACTOR_LIMIT_INV) { // 0.5 thres.
        HashTable_resize(ht, ht->capacity * 2); // double it.
    }
}

//............................................................................
bool HashTable_remove(HashTable *ht, HashNode_KeyType type, void *key) {
    unsigned long idx = HashTable_hashKey(type,
                                          key,
                                          ht->capacity);
    HashNode *node = ht->buckets[idx], *prev = NULL;
    while (node) {
        if (HashTable_keyIsEqual(node, type, key)) {
            if (prev) prev->next = node->next;
            else      ht->buckets[idx] = node->next;
            HashTable_freeNode(node);
            --ht->size;
            return true;
        }
        prev = node;
        node = node->next;
    }
    return false;
}

//............................................................................
void *HashTable_find(HashTable *ht, HashNode_KeyType type, void *key) {
    unsigned long int idx = HashTable_hashKey(type,
                                              key,
                                              ht->capacity);
    HashNode *node = ht->buckets[idx];
    for (HashNode *n = ht->buckets[idx]; n; n = n->next) {
        if (HashTable_keyIsEqual(n, type, key)) {
            return &node->value;
        }
        node = node->next;
    }
    return NULL;
}
