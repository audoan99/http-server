/**
 * @file llist.cpp
 * @author Au Doan Ngoc (doanngocau99@gmail.com)
 * @brief Doubly linkedlist
 * @version 0.1
 * @date 2023-03-18
 *
 * @copyright Copyright (c) 2023
 *
 */

#include "llist.hpp"

struct llist *Llist::llist_create(void)
{
	return (struct llist*)calloc(1, sizeof(struct llist));
}

void Llist::llist_destroy(struct llist *llist)
{
	struct llist_node *n = llist->head, *next;

	while (n != nullptr)
    {
		next = n->next;
		free(n);

		n = next;
	}

	free(llist);
}

void *Llist::llist_insert(struct llist *llist, void *data)
{
	struct llist_node *n = (struct llist_node*)calloc(1, sizeof *n);

	if (n == NULL)
	{
		return NULL;
	}

	n->data = data;
	n->next = llist->head;
	llist->head = n;

	llist->count++;

	return data;
}

void *Llist::llist_append(struct llist *llist, void *data)
{
	struct llist_node *tail = llist->head;

	/* If list is empty, just insert */
	if (tail == NULL)
	{
		return llist_insert(llist, data);
	}

	struct llist_node *n = (struct llist_node*)calloc(1, sizeof *n);

	if (n == NULL)
	{
		return NULL;
	}

	while (tail->next != NULL)
	{
		tail = tail->next;
	}

	n->data = data;
	tail->next = n;

	llist->count++;

	return data;
}

void *Llist::llist_head(struct llist *llist)
{
	if (llist->head == NULL)
	{
		return NULL;
	}

	return llist->head->data;
}

void *Llist::llist_tail(struct llist *llist)
{
	struct llist_node *n = llist->head;

	if (n == NULL)
	{
		return NULL;
	}

	while (n->next != NULL)
	{
		n = n->next;
	}

	return n->data;
}

void *Llist::llist_find(struct llist *llist, void *data, int (*cmpfn)(void *, void *))
{
	struct llist_node *n = llist->head;

	if (n == NULL)
	{
		return NULL;
	}

	while (n != NULL)
	{
		if (cmpfn(data, n->data) == 0)
		{
			break;
		}

		n = n->next;
	}

	if (n == NULL)
	{
		return NULL;
	}

	return n->data;
}

void *Llist::llist_delete(struct llist *llist, void *data, int (*cmpfn)(void *, void *))
{
	struct llist_node *n = llist->head, *prev = NULL;

	while (n != NULL)
	{
		if (cmpfn(data, n->data) == 0)
		{
			void *data = n->data;

			if (prev == NULL)
			{
				/* Free the head */
				llist->head = n->next;
				free(n);

			}
			else
			{
				/* Free the non-head */
				prev->next = n->next;
				free(n);
			}

			llist->count--;

			return data;
		}

		prev = n;
		n = n->next;
	}

	return NULL;
}

int Llist::llist_count(struct llist *llist)
{
	return llist->count;
}

void Llist::llist_foreach(struct llist *llist, void (*f)(void *, void *), void *arg)
{
	struct llist_node *p = llist->head, *next;

	while (p != NULL)
	{
		next = p->next;
		f(p->data, arg);
		p = next;
	}
}
void **Llist::llist_array_get(struct llist *llist)
{
	if (llist->head == NULL)
	{
		return NULL;
	}

	void **a = (void **)malloc(sizeof *a * llist->count + 1);

	struct llist_node *n;
	int i;

	for (i = 0, n = llist->head; n != NULL; i++, n = n->next)
	{
		a[i] = n->data;
	}

	a[i] = NULL;

	return a;
}

void Llist::llist_array_free(void **a)
{
	free(a);
}
