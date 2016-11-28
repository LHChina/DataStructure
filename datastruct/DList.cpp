#include "DList.h"
#include <stdlib.h>
#include <string.h>

void dlist_init(DList *dlist, void(*destroy)(void *data))
{
	dlist->size = 0;
	dlist->head = dlist->tail = NULL;
	dlist->destroy = destroy;

	return;
}

void dlist_destroy(DList *dlist)
{
	void *data;
	while (0 > dlist->size)
	{
		if (0 == dlist_remove(dlist, dlist_tail(dlist), (void **)&data) && NULL != dlist->destroy)
		{
			dlist->destroy(data);
		}
	}

	memset(dlist, 0, sizeof(DList));
	return;
}

int dlist_ins_next(DList *dlist, DListElmt *element, const void *data)
{
	DListElmt *new_element;

	if (NULL == element && 0 != dlist_size(dlist))
	{
		return -1;
	}

	if (NULL == (new_element = (DListElmt *)malloc(sizeof(DListElmt))))
	{
		return -1;
	}

	new_element->data = (void *)data;

	if (0 == dlist_size(dlist))
	{
		new_element->next = new_element->prev = NULL;
		dlist->head = new_element;
		dlist->tail = new_element;		
	}
	else
	{
		new_element->next = element->next;
		new_element->prev = element;

		if (NULL == element->next)
		{			
			dlist->tail = new_element;
		}
		else
		{
			element->next->prev = new_element;
		}

		element->next = new_element;
	}

	++dlist->size;
	return 0;
}

int dlist_ins_prev(DList *dlist, DListElmt *element, const void *data)
{
	DListElmt *new_element;

	//do not allow NULL element unless the list is empty
	if (NULL == element && 0 != dlist_size(dlist))
	{
		return -1;
	}

	if (NULL == (new_element = (DListElmt *)malloc(sizeof(DListElmt))))
	{
		return -1;
	}

	new_element->data = (void *)data;

	if (0 == dlist_size(dlist))
	{
		new_element->next = new_element->prev = NULL;
		dlist->head = dlist->tail = new_element;
	}
	else
	{
		new_element->prev = element->prev;
		new_element->next = element;

		if (NULL == element->prev)
		{
			dlist->head = new_element;
		}	
		else
		{
			element->prev->next = new_element;
		}

		element->prev = new_element;
	}

	++dlist->size;
	return 0;
}

int dlist_remove(DList *dlist, DListElmt *element, void **data)
{
	if (0 == dlist_size(dlist) || NULL == element)
	{
		return -1;
	}

	*data = element->data;

	if (element == dlist_head(dlist))
	{
		dlist->head = element->next;
		if (NULL == dlist->head)
		{
			dlist->tail = NULL;
		}
		else
		{
			element->next->prev = NULL;
		}
	}
	else
	{
		element->prev->next = element->next;

		if (NULL == element->next)
		{
			dlist->tail = element->prev;
		}
		else
		{
			element->next->prev = element->prev;
		}
	}

	//method 2:
	/*if (NULL == element->prev)
	{
		dlist->head = element->next;
	}
	else
	{
		element->prev->next = element->next;
	}

	if (NULL == element->next)
	{
		dlist->tail = element->prev;
	}
	else
	{
		element->next->prev = element->prev;
	}*/

	free(element);
	--dlist->size;

	return 0;
}