#include <stdio.h>
#include <stdlib.h>
#include <linkedlist/linkedlist.h>

static int add_end(linkedlist_t *list, void *element)
{
	node_t *node = malloc(sizeof(node_t));

	if (node == NULL)
		return (EXIT_FAILURE);
	node->value = element;
	node->next = NULL;
	node->prev = list->end;
	list->end->next = node;
	list->end = node;
	list->length += 1;
	return (EXIT_SUCCESS);
}

static int add_first(linkedlist_t *list, void *element)
{
	node_t *node = malloc(sizeof(node_t));

	if (node == NULL)
		return (EXIT_FAILURE);
	node->value = element;
	node->next = NULL;
	node->prev = NULL;
	list->begin = node;
	list->end = node;
	list->length += 1;
	return (EXIT_SUCCESS);
}

static int add_begin(linkedlist_t *list, void *element)
{
	node_t *node = malloc(sizeof(node_t));

	if (node == NULL)
		return (EXIT_FAILURE);
	node->value = element;
	node->prev = NULL;
	node->next = list->begin;
	list->begin->prev = node;
	list->begin = node;
	list->length += 1;
	return (EXIT_SUCCESS);
}

int linkedlist_append(linkedlist_t *list, void *element)
{
	if (list == NULL)
	{
		return (EXIT_FAILURE);
	}
	if (list->length == 0)
	{
		return (add_first(list, element));
	}
	return (add_end(list, element));
}

int linkedlist_prepend(linkedlist_t *list, void *element)
{
	if (list == NULL)
		return (EXIT_FAILURE);
	if (list->length == 0)
		return (add_first(list, element));
	return (add_begin(list, element));
}
