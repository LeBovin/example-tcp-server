/*
** EPITECH PROJECT, 2018
** linkedlist
** File description:
** remove
*/

#include <memory.h>
#include <linkedlist/linkedlist.h>

static int linkedlist_reset(linkedlist_t *list)
{
	free(list->begin);
	list->begin = NULL;
	list->end = NULL;
	list->length = 0;
	return (EXIT_SUCCESS);
}

int linkedlist_remove_begin(linkedlist_t *list)
{
	node_t *node = list->begin;

	if (list->length > 1)
	{
		node->next->prev = NULL;
		list->begin = node->next;
	}
	else
		list->begin = NULL;
	list->length -= 1;
	free(node);
	return (EXIT_SUCCESS);
}

int linkedlist_remove_end(linkedlist_t *list)
{
	node_t *node = list->end;

	node->prev->next = NULL;
	list->end = node->prev;
	list->length -= 1;
	free(node);
	return (EXIT_SUCCESS);
}

int linkedlist_remove_index(linkedlist_t *list, size_t index)
{
	node_t *node;

	if (list->length == 0 || index > list->length - 1)
		return (EXIT_FAILURE);
	if (list->length == 1 && index == 0)
		return (linkedlist_reset(list));
	if (index == list->length - 1)
		return (linkedlist_remove_end(list));
	if (index == 0)
		return (linkedlist_remove_begin(list));
	node = linkedlist_getnode(list, index);
	if (node == NULL)
		return (EXIT_FAILURE);
	node->prev->next = node->next;
	node->next->prev = node->prev;
	list->length -= 1;
	free(node);
	return (EXIT_SUCCESS);
}

int linkedlist_remove(linkedlist_t *list, void *data, size_t n)
{
	size_t index = 0;

	for (node_t *node = list->begin; node != NULL; node = node->next)
	{
		if (memcmp(node->value, data, n) == 0)
		{
			linkedlist_remove_index(list, index);
			return (EXIT_SUCCESS);
		}
		index++;
	}
	return (EXIT_FAILURE);
}
