/**
 * @file lru_cache.cpp
 * @author Au Doan Ngoc (doanngocau99@gmail.com)
 * @brief lru (least recently used) cache
 * @version 0.1
 * @date 2023-03-18
 *
 * @copyright Copyright (c) 2023
 *
 */

#include <string.h>
#include "lru_cache.hpp"

/**
 * Insert a cache entry at the head of the linked list
 */
void dllist_insert_head(struct cache *cache, struct cache_entry *ce)
{
    // Insert at the head of the list
    if (cache->head == NULL)
    {
        cache->head = cache->tail = ce;
        ce->prev = ce->next = NULL;
    }
    else
    {
        cache->head->prev = ce;
        ce->next = cache->head;
        ce->prev = NULL;
        cache->head = ce;
    }
}

/**
 * Move a cache entry to the head of the list
 */
void dllist_move_to_head(struct cache *cache, struct cache_entry *ce)
{
    if (ce != cache->head)
    {
        if (ce == cache->tail)
        {
            cache->tail = ce->prev;
            cache->tail->next = NULL;

        }
        else
        {
            ce->prev->next = ce->next;
            ce->next->prev = ce->prev;
        }

        ce->next = cache->head;
        cache->head->prev = ce;
        ce->prev = NULL;
        cache->head = ce;
    }
}

/**
 * Removes the tail from the list and returns it
 *
 * NOTE: does not deallocate the tail
 */
struct cache_entry *dllist_remove_tail(struct cache *cache)
{
    struct cache_entry *oldtail = cache->tail;

    cache->tail = oldtail->prev;
    cache->tail->next = NULL;

    cache->cur_size--;

    return oldtail;
}


struct cache_entry *LRUCache::alloc_entry(char *path, char *content_type, void *content, int content_length)
{
    struct cache_entry *new_entry = (struct cache_entry *)malloc(sizeof(*new_entry));

    new_entry->path = strdup(path);
    new_entry->content_type = strdup(content_type);
    new_entry->content_length = content_length;

    new_entry->content = malloc(content_length);
    memcpy(new_entry->content, content, content_length);
    new_entry->prev = NULL;
    new_entry->next = NULL;

    return new_entry;
}

void LRUCache::free_entry(struct cache_entry *entry)
{
    free(entry->path);
    free(entry->content_type);
    free(entry->content);
    free(entry);
}

struct cache *LRUCache::cache_create(int max_size, int hashsize)
{
    struct cache *new_cache = (struct cache *)malloc(sizeof(*new_cache));

    new_cache->index = hashtable_create(hashsize, NULL);
    new_cache->head = NULL;
    new_cache->tail = NULL;
    new_cache->max_size = max_size;
    new_cache->cur_size = hashsize;

    return new_cache;
}

void LRUCache::cache_free(struct cache *cache)
{
    struct cache_entry *cur_entry = cache->head;

    hashtable_destroy(cache->index);

    while (cur_entry != NULL)
    {
        struct cache_entry *next_entry = cur_entry->next;

        free_entry(cur_entry);

        cur_entry = next_entry;
    }

    free(cache);
}

void LRUCache::cache_put(struct cache *cache, char *path, char *content_type, void *content, int content_length)
{
    struct cache_entry *new_entry = alloc_entry(path, content_type, content, content_length);

    dllist_insert_head(cache, new_entry);

    hashtable_put(cache->index, path, new_entry);

    cache->cur_size++;

    if (cache->cur_size > cache->max_size)
    {
        struct cache_entry *old_entry = dllist_remove_tail(cache);
        hashtable_delete(cache->index, old_entry->path);
        free_entry(old_entry);
    }
}

struct cache_entry *LRUCache::cache_get(struct cache *cache, char *path)
{
    struct cache_entry *query = (struct cache_entry *)hashtable_get(cache->index, path);

    if (query == NULL)
    {
        return NULL;
    }
    else
    {
        dllist_move_to_head(cache, query);
        return query;
    }
}
