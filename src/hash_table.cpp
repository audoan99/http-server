/**
 * @file hash_table.cpp
 * @author Au Doan Ngoc (doanngocau99@gmail.com)
 * @brief build a hash table
 * @version 0.1
 * @date 2023-03-18
 *
 * @copyright Copyright (c) 2023
 *
 */

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "hash_table.hpp"

/**
 * Change the entry count, maintain load metrics
 */
void add_entry_count(struct hashtable *ht, int d)
{
    ht->num_entries += d;
    ht->load = (float)ht->num_entries / ht->size;
}

/**
 * Default modulo hashing function
 */
int default_hashf(void *data, int data_size, int bucket_count)
{
    const int R = 31; // Small prime
    int h = 0;
    unsigned char *p = (unsigned char *)data;

    for (int i = 0; i < data_size; i++)
    {
        h = (R * h + p[i]) % bucket_count;
    }

    return h;
}

/**
 * Free an htent
 */
void htent_free(void *htent, void *arg)
{
	(void)arg;

	free(htent);
}


/**
 * Comparison function for hashtable entries
 */
int htcmp(void *a, void *b)
{
    struct htent *entA = (struct htent *)a, *entB = (struct htent *)b;

    int size_diff = entB->key_size - entA->key_size;

    if (size_diff) {
        return size_diff;
    }

    return memcmp(entA->key, entB->key, entA->key_size);
}


/**
 * Foreach callback function
 */
void foreach_callback(void *vent, void *vpayload)
{
	struct htent *ent = (struct htent *)vent;
	struct foreach_callback_payload *payload = (struct foreach_callback_payload *)vpayload;

	payload->f(ent->data, payload->arg);
}

struct hashtable *HashTable::hashtable_create(int size, int (*hashf)(void *, int, int))
{
    if (size < 1)
    {
        size = DEFAULT_SIZE;
    }

    if (hashf == NULL)
    {
        hashf = default_hashf;
    }

    struct hashtable *ht = (struct hashtable *)malloc(sizeof *ht);

    if (ht == NULL) return NULL;

    ht->size = size;
    ht->num_entries = 0;
    ht->load = 0;
    ht->bucket = (struct llist **)malloc(size * sizeof(struct llist *));
    ht->hashf = hashf;

    for (int i = 0; i < size; i++)
    {
        ht->bucket[i] = llist_create();
    }

    return ht;
}

void HashTable::hashtable_destroy(struct hashtable *ht)
{
    for (int i = 0; i < ht->size; i++)
    {
        struct llist *llist = ht->bucket[i];

		llist_foreach(llist, htent_free, NULL);
        llist_destroy(llist);
    }

    free(ht);
}

void *HashTable::hashtable_put(struct hashtable *ht, char *key, void *data)
{
    return hashtable_put_bin(ht, key, strlen(key), data);
}

void *HashTable::hashtable_put_bin(struct hashtable *ht, void *key, int key_size, void *data)
{
    int index = ht->hashf(key, key_size, ht->size);

    struct llist *llist = ht->bucket[index];

    struct htent *ent = (struct htent *)malloc(sizeof *ent);
    ent->key = malloc(key_size);
    memcpy(ent->key, key, key_size);
    ent->key_size = key_size;
    ent->hashed_key = index;
    ent->data = data;

    if (llist_append(llist, ent) == NULL)
    {
        free(ent->key);
        free(ent);
        return NULL;
    }

    add_entry_count(ht, +1);

    return data;
}

void *HashTable::hashtable_get(struct hashtable *ht, char *key)
{
    return hashtable_get_bin(ht, key, strlen(key));
}

void *HashTable::hashtable_get_bin(struct hashtable *ht, void *key, int key_size)
{
    int index = ht->hashf(key, key_size, ht->size);

    struct llist *llist = ht->bucket[index];

    struct htent cmpent;
    cmpent.key = key;
    cmpent.key_size = key_size;

    struct htent *n = (struct htent *)llist_find(llist, &cmpent, htcmp);

    if (n == NULL) { return NULL; }

    return n->data;
}

void *HashTable::hashtable_delete(struct hashtable *ht, char *key)
{
    return hashtable_delete_bin(ht, key, strlen(key));
}

void *HashTable::hashtable_delete_bin(struct hashtable *ht, void *key, int key_size)
{
    int index = ht->hashf(key, key_size, ht->size);

    struct llist *llist = ht->bucket[index];

    struct htent cmpent;
    cmpent.key = key;
    cmpent.key_size = key_size;

    struct htent *ent = (struct htent *)llist_delete(llist, &cmpent, htcmp);

	if (ent == NULL)
    {
		return NULL;
	}

	void *data = ent->data;

	free(ent);

    add_entry_count(ht, -1);

	return data;
}

void HashTable::hashtable_foreach(struct hashtable *ht, void (*f)(void *, void *), void *arg)
{
	struct foreach_callback_payload payload;

	payload.f = f;
	payload.arg = arg;

	for (int i = 0; i < ht->size; i++)
    {
		struct llist *llist = ht->bucket[i];

		llist_foreach(llist, foreach_callback, &payload);
	}
}
