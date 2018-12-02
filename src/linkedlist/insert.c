#include <stdlib.h>
#include <linkedlist/linkedlist.h>

static int insert_index(linkedlist_t *list, void *element, size_t index)
{
	node_t *node;
	node_t *tmp;

	node = malloc(sizeof(node_t));
	if (node == NULL)
		return (EXIT_FAILURE);
	tmp = linkedlist_getnode(list, index);
	node->value = element;
	node->prev = tmp->prev;
	node->prev->next = node;
	node->next = tmp;
	tmp->prev = node;
	list->length += 1;
	return (EXIT_SUCCESS);
}

int linkedlist_insert(linkedlist_t *list, void *element, size_t index)
{
	if (list == NULL || index > list->length)
	{
		return (EXIT_FAILURE);
	}
	if (index == 0)
	{
		return (linkedlist_prepend(list, element));
	}
	if (index == list->length)
	{
		return (linkedlist_append(list, element));
	}
	return (insert_index(list, element, index));
}
