/**
 * @file llist.hpp
 * @author Au Doan Ngoc (doanngocau99@gmail.com)
 * @brief Doubly linkedlist
 * @version 0.1
 * @date 2023-03-18
 *
 * @copyright Copyright (c) 2023
 *
 */

#include <stdlib.h>

struct llist_node
{
	void *data;
	struct llist_node *next;
};

struct llist
{
	struct llist_node *head;
	int count;
};

class Llist
{
public:
    Llist() {}
    ~Llist() {}

    /**
     * @brief Allocate a new linked list
     *
     * @return struct llist*
     */
    struct llist *llist_create(void);

    /**
     * @brief Destroy a linked list
     * If destfn is not NULL, it is called with the node data before the
     * node is deallocated.
     *
     * @param llist
     *
     * @note does *not* deallocate the data in each node!
     */
    void llist_destroy(struct llist *llist);

    /**
     * @brief Insert at the head of a linked list
     * 
     * @param llist 
     * @param data 
     * @return void* 
     */
    void *llist_insert(struct llist *llist, void *data);

    /**
     * @brief Append to the end of a list
     * 
     * @param llist 
     * @param data 
     * @return void* 
     */
    void *llist_append(struct llist *llist, void *data);

    /**
     * @brief Return the first element in a list
     * 
     * @param llist 
     * @return void* 
     */
    void *llist_head(struct llist *llist);

    /**
     * @brief Return the last element in a list
     * 
     * @param llist 
     * @return void* 
     */
    void *llist_tail(struct llist *llist);

    /**
     * @brief Find an element in the list
     * cmpfn should return 0 if the comparison to this node's data is equal
     * 
     * @param llist 
     * @param data 
     * @param cmpfn 
     * @return void* 
     */
    void *llist_find(struct llist *llist, void *data, int (*cmpfn)(void *, void *));

    /**
     * @brief Delete an element in the list
     * cmpfn should return 0 if the comparison to this node's data is equal
     * 
     * @param llist 
     * @param data 
     * @param cmpfn 
     * @return void* 
     * 
     * @note does *not* free the data--it merely returns a pointer to it
     */
    void *llist_delete(struct llist *llist, void *data, int (*cmpfn)(void *, void *));
    
    /**
     * @brief Return the number of elements in the list
     * 
     * @param llist 
     * @return int 
     */
    int llist_count(struct llist *llist);

    /**
     * @brief For each item in the list run a function
     * 
     * @param llist 
     * @param f 
     * @param arg 
     */
    void llist_foreach(struct llist *llist, void (*f)(void *, void *), void *arg);

    /**
     * @brief Allocates and returns a new NULL-terminated array of pointers to data
     * elements in the list
     * 
     * @param llist 
     * 
     * @note This is a read-only array! Consider it an array view onto the linked list
     */
    void **llist_array_get(struct llist *llist);

    /**
     * @brief Free an array allocated with llist_array_get()
     * 
     * @param a 
     * 
     * @note this does not modify the linked list or its data in any way
     */
    void llist_array_free(void **a);
private:

};
