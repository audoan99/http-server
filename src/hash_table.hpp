/**
 * @file hash_table.hpp
 * @author Au Doan Ngoc (doanngocau99@gmail.com)
 * @brief build a hash table
 * @version 0.1
 * @date 2023-03-18
 *
 * @copyright Copyright (c) 2023
 *
 */

#ifndef __HASH_TABLE_HPP__
#define __HASH_TABLE_HPP__

#include "llist.hpp"

#define DEFAULT_SIZE                128
#define DEFAULT_GROW_FACTOR         2

/* Hash table entry */
struct htent {
    void *key;
    int key_size;
    int hashed_key;
    void *data;
};

/* Used to cleanup the linked lists */
struct foreach_callback_payload {
	void *arg;
	void (*f)(void *, void *);
};

struct hashtable {
    int size; // Read-only
    int num_entries; // Read-only
    float load; // Read-only
    struct llist **bucket;
    int (*hashf)(void *data, int data_size, int bucket_count);
};

class HashTable : public Llist
{
public:
    HashTable() {}
    ~HashTable() {}

    /**
     * @brief Create a new hashtable
     *
     * @param size
     * @param hashf
     * @return struct hashtable*
     */
    struct hashtable *hashtable_create(int size, int (*hashf)(void *, int, int));

    /**
     * @brief Destroy a hashtable
     *
     * @param ht
     *
     * @note does *not* free the data pointer
     */
    void hashtable_destroy(struct hashtable *ht);

    /**
     * @brief Put to hash table with a string key
     *
     * @param ht
     * @param key
     * @param data
     * @return void*
     */
    void *hashtable_put(struct hashtable *ht, char *key, void *data);

    /**
     * @brief Put to hash table with a binary key
     *
     * @param ht
     * @param key
     * @param key_size
     * @param data
     * @return void*
     */
    void *hashtable_put_bin(struct hashtable *ht, void *key, int key_size, void *data);

    /**
     * @brief Get from the hash table with a string key
     *
     * @param ht
     * @param key
     * @return void*
     */
    void *hashtable_get(struct hashtable *ht, char *key);

    /**
     * @brief Get from the hash table with a binary data key
     *
     * @param ht
     * @param key
     * @param key_size
     * @return void*
     */
    void *hashtable_get_bin(struct hashtable *ht, void *key, int key_size);

    /**
     * @brief Delete from the hashtable by string key
     *
     * @param ht
     * @param key
     * @return void*
     */
    void *hashtable_delete(struct hashtable *ht, char *key);

    /**
     * @brief Delete from the hashtable by binary key
     *
     * @param ht
     * @param key
     * @param key_size
     * @return void*
     *
     * @note does *not* free the data--just free's the hash table entry
     */
    void *hashtable_delete_bin(struct hashtable *ht, void *key, int key_size);

    /**
     * @brief For-each element in the hashtable
     *
     * @param ht
     * @param f
     * @param arg
     *
     * @note elements are returned in effectively random order
     */
    void hashtable_foreach(struct hashtable *ht, void (*f)(void *, void *), void *arg);
private:

};

#endif /* __HASH_TABLE_HPP__ */
