/*
** EPITECH PROJECT, 2018
** Epitech scolarship project (4 years remaining)
** File description:
**      Made on 2018/04 by lebovin
*/

#ifndef PSU_MYFTP_2017_LINKEDLIST_H
#define PSU_MYFTP_2017_LINKEDLIST_H

#include <stdlib.h>
# define linkedlist_stack_push(x, y) linkedlist_append(x, y)
# define linkedlist_queue_push(x, y) linkedlist_prepend(x, y)
# define linkedlist_at(x, y) ((linkedlist_getnode(x, y))->value);

struct node_s
{
	void *value;
	struct node_s *next;
	struct node_s *prev;
};
typedef struct node_s node_t;

struct linkedlist_s
{
	size_t length;
	node_t *begin;
	node_t *end;
};
typedef struct linkedlist_s linkedlist_t;

int linkedlist_init(linkedlist_t *list);
int linkedlist_destroy(linkedlist_t *list);
int linkedlist_append(linkedlist_t *list, void *element);
int linkedlist_prepend(linkedlist_t *list, void *element);
int linkedlist_insert(linkedlist_t *list, void *elem, size_t index);
int linkedlist_contains(const linkedlist_t *list, void *data, size_t size);
int linkedlist_remove(linkedlist_t *list, void *data, size_t n);
int linkedlist_remove_end(linkedlist_t *list);
int linkedlist_remove_begin(linkedlist_t *list);
int linkedlist_remove_index(linkedlist_t *list, size_t index);
void *linkedlist_stack_pop(linkedlist_t *list);
void **linkedlist_to_array(const linkedlist_t *list);
node_t *linkedlist_getnode(const linkedlist_t *list, size_t index);

#endif //PSU_MYFTP_2017_LINKEDLIST_H
