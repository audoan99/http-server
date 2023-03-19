/**
 * @file lru_cache.hpp
 * @author Au Doan Ngoc (doanngocau99@gmail.com)
 * @brief lru (least recently used) cache
 * @version 0.1
 * @date 2023-03-18
 *
 * @copyright Copyright (c) 2023
 *
 */

#ifndef __LRU_CACHE_HPP__
#define __LRU_CACHE_HPP__

#include "hash_table.hpp"

/* Individual hash table entry */
struct cache_entry
{
    char *path;   // Endpoint path--key to the cache
    char *content_type;
    int content_length;
    void *content;

    struct cache_entry *prev, *next; // Doubly-linked list
};

/* A cache */
struct cache
{
    struct hashtable *index;
    struct cache_entry *head, *tail; // Doubly-linked list
    int max_size; // Maxiumum number of entries
    int cur_size; // Current number of entries
};

class LRUCache : public HashTable
{
public:
    LRUCache() {}
    ~LRUCache() {}

    /**
     * @brief Allocate a cache entry
     *
     * @param path
     * @param content_type
     * @param content
     * @param content_length
     * @return struct cache_entry*
     */
    struct cache_entry *alloc_entry(char *path, char *content_type, void *content, int content_length);

    /**
     * @brief Deallocate a cache entry
     *
     * @param entry
     */
    void free_entry(struct cache_entry *entry);

    /**
     * @brief Create a new cache
     * max_size: maximum number of entries in the cache
     * hashsize: hashtable size (0 for default)
     *
     * @param max_size
     * @param hashsize
     * @return struct cache*
     */
    struct cache *cache_create(int max_size, int hashsize);

    /**
     * @brief Free a cache
     *
     * @param cache
     */
    void cache_free(struct cache *cache);

    /**
     * @brief Store an entry in the cache
     * This will also remove the least-recently-used items as necessary
     *
     * @param cache
     * @param path
     * @param content_type
     * @param content
     * @param content_length
     *
     * @note doesn't check for duplicate cache entries
     */
    void cache_put(struct cache *cache, char *path, char *content_type, void *content, int content_length);

    /**
     * @brief Retrieve an entry from the cache
     *
     * @param cache
     * @param path
     * @return struct cache_entry*
     */
    struct cache_entry *cache_get(struct cache *cache, char *path);

private:

};

#endif /* __LRU_CACHE_HPP__ */
