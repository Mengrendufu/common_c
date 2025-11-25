#ifndef hash_table_h_
#define hash_table_h_

/* hash table --------------------------------------------------------------*/
/* initial setting ---------------------------------------------------------*/
#define INITIAL_CAPACITY 8
#define LOAD_FACTOR_LIMIT_INV 2U
/* initial setting ---------------------------------------------------------*/

/* =================================
 * key type of hash node
 * ================================= */
typedef enum {
    KEY_INT,
    KEY_STR
} HashNode_KeyType;

/* =============================
 * Hash node
 * ============================= */
typedef struct HashNode {
    HashNode_KeyType type;
    void *key;                  /* mixed key */
    void *value;                /* value */
    struct HashNode *next;      /* node link */
} HashNode;

/* =============================
 * Hash table
 * ============================= */
typedef struct HashTable {
    HashNode **buckets;         /* buckets, head of the nodes */
    size_t capacity;
    size_t size;
} HashTable;

/* Hash table methods */
HashTable *HashTable_create(void);
void HashTable_free(HashTable *ht);
void HashTable_insert(
    HashTable *ht, HashNode_KeyType type, void *key, void *value);
int HashTable_remove(HashTable *ht, HashNode_KeyType type, void *key);
void *HashTable_find(HashTable *ht, HashNode_KeyType type, void *key);
/* hash table --------------------------------------------------------------*/

/* test handler ------------------------------------------------------------*/
void HashTable_print(HashTable *ht);
void HashTable_testHandler(void);
/* test handler ------------------------------------------------------------*/

#endif  /* hash_table_h_ */
