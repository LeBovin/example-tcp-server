/*
** EPITECH PROJECT, 2018
** linkedlist
** File description:
** stack
*/

#include <stdlib.h>
#include <linkedlist/linkedlist.h>

void *linkedlist_stack_peek(linkedlist_t *list)
{
	if (list->length == 0)
		return (NULL);
	return (list->end->value);
}

void *linkedlist_stack_pop(linkedlist_t *list)
{
	void *result;

	if (list->length == 0)
		return (NULL);
	result = list->end->value;
	linkedlist_remove_index(list, list->length - 1);
	return (result);
}
