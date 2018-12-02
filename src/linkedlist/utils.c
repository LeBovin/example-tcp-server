#include <stdlib.h>
#include <memory.h>
#include <linkedlist/linkedlist.h>

static node_t *getnode_from_begin(const linkedlist_t *list, size_t index)
{
	size_t iterator;
	node_t *result;

	iterator = 0;
	result = list->begin;
	while (iterator < index)
	{
		result = result->next;
		iterator += 1;
	}
	return (result);
}

static node_t *getnode_from_end(const linkedlist_t *list, size_t index)
{
	size_t iterator;
	node_t *result;

	iterator = list->length - 1;
	result = list->end;
	while (iterator != index)
	{
		result = result->prev;
		iterator -= 1;
	}
	return (result);
}

node_t *linkedlist_getnode(const linkedlist_t *list, size_t index)
{
	size_t diff;
	size_t half;

	if (index >= list->length)
		return (NULL);
	diff = (list->length - index);
	half = (list->length / 2);
	if (diff > half)
		return (getnode_from_end(list, index));
	return (getnode_from_begin(list, index));
}

int linkedlist_contains(const linkedlist_t *list, void *data, size_t size)
{
	for (node_t *node = list->begin; node != NULL; node = node->next)
		if (memcmp(node, data, size) == 0)
			return (1);
	return (0);
}

void **linkedlist_to_array(const linkedlist_t *list)
{
	node_t *node;
	size_t index = 0;
	void **result = malloc(sizeof(void *) * (list->length + 1));

	if (result == NULL)
		return (NULL);
	node = list->begin;
	while (index < list->length)
	{
		result[index] = node->value;
		index += 1;
		node = node->next;
	}
	result[index] = 0;
	return (result);
}
