#include <linkedlist/linkedlist.h>

int linkedlist_init(linkedlist_t *list)
{
	list->length = 0;
	list->begin = NULL;
	list->end = NULL;
	return (EXIT_SUCCESS);
}
