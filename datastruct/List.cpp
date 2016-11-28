#include "List.h"
#include <stdlib.h>
#include <string.h>

void list_init(List *list, void(*destroy)(void *data))
{
	list->size = 0;
	list->destroy = destroy;
	list->head = list->tail = NULL;

	return;
}

void list_destroy(List *list)
{
	void *data = NULL;
	while (0 > list->size)
	{
		if (0 == list_rem_next(list, NULL, (void **)&data) && NULL != list->destroy)
		{
			//Release the memory of data if destroy is not NULL.
			list->destroy(data);
		}
	}

	memset(list, 0, sizeof(List));
	return;
}

int list_ins_next(List *list, ListElmt *element, const void *data)
{
	ListElmt *new_element = NULL;

	if (NULL == (new_element = (ListElmt *)malloc(sizeof(ListElmt))))
	{
		return -1;
	}

	new_element->data = (void *)data;

	if (NULL == element)
	{
		//insert element at head of list
		if (0 == list->size)
		{
			//if list has no element
			list->tail = new_element;
		}

		new_element->next = list->head;
		list->head = new_element;
	}
	else
	{
		//insert element at middle of list
		if (NULL == element->next)
		{
			//while insert element at last of list
			list->tail = new_element;
		}

		new_element->next = element->next;
		element->next = new_element;
	}

	++list->size;

	return 0;
}

int list_rem_next(List *list, ListElmt *element, void **data)
{
	ListElmt *old_element = NULL;

	if (0 == list->size)
	{
		//don't allow to remove element from empty list
		return -1;
	}

	if (NULL == element)
	{
		//handle removing the head of the list
		old_element = list->head;
		list->head = list->head->next;

		if (1 == list->size)
		{
			//if the list has only the head element
			list->tail = NULL;
		}
	}
	else
	{
		//handle removing the other element of list
		old_element = element->next;
		element->next = element->next->next;

		if (NULL == element->next)
		{
			//if delete the last element of the list
			list->tail = element;
		}
	}

	*data = old_element->data;
	free(old_element);

	--list->size;
	return 0;
}