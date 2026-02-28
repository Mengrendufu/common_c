//============================================================================
// Copyright (C) 2026 Sunny Matato
//
// This program is free software. It comes without any warranty, to
// the extent permitted by applicable law. You can redistribute it
// and/or modify it under the terms of the Do What The Fuck You Want
// To Public License, Version 2, as published by Sam Hocevar.
// See http://www.wtfpl.net/ for more details.
//============================================================================
#ifndef HASH_TABLE_H_
#define HASH_TABLE_H_

//============================================================================
#include "hash_table_port.h"

//============================================================================
//! @brief Initial size and resize thres: 50%.
//! @cond INTERNAL

#define INITIAL_CAPACITY 8
#define LOAD_FACTOR_LIMIT_INV 2

//! @endcond

//! @enum Type of key of HashNode.
typedef enum {
    KEY_INT,
    KEY_STR
} HashNode_KeyType;

typedef struct HashNode {
    struct HashNode *next;
    HashNode_KeyType type;
    void *key;
    void *value;
} HashNode;

typedef struct HashTable {
    HashNode **buckets;
    size_t capacity;
    size_t size;
} HashTable;

HashTable *HashTable_create(void);
void HashTable_free(HashTable *ht);
void HashTable_insert(HashTable *ht,
                      HashNode_KeyType type,
                      void *key, void *value);
bool HashTable_remove(HashTable *ht, HashNode_KeyType type, void *key);
void *HashTable_find(HashTable *ht, HashNode_KeyType type, void *key);

#endif // HASH_TABLE_H_
