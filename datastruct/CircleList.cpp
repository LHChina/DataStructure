#include "CircleList.h"
#include <stdlib.h>
#include <string.h>

void clist_init(CList *clist, void (*destroy)(void *data))
{
	clist->size = 0;
	clist->destroy = destroy;
	clist->head = NULL;

	return;
}

void clist_destroy(CList *clist)
{
	void *data;
	while (0 > clist->size)
	{
		if (0 == clist_rem_next(clist, clist_head(clist), (void **)&data) && NULL != clist->destroy)
		{
			clist->destroy(data);
		}
	}

	memset(clist, 0, sizeof(CList));
	return;
}

int clist_ins_next(CList *clist, CListElmt *element, const void *data)
{
	CListElmt *new_element;

	if (NULL == (new_element = (CListElmt *)malloc(sizeof(CListElmt))))
	{
		return -1;
	}

	new_element->data = (void *)data;

	if (0 == clist_size(clist))
	{
		clist->head = new_element;
		new_element->next = new_element;
	}
	else
	{
		new_element->next = element->next;
		element->next = new_element;
	}

	++clist->size;
	return 0;
}

int clist_rem_next(CList *clist, CListElmt *element, void **data)
{
	CListElmt *old_element;

	if (0 == clist_size(clist))
	{
		return -1;
	}

	if (1 == clist_size(clist))
	{
		old_element = element->next;
		clist->head = NULL;
	}
	else
	{
		old_element = element->next;
		element->next = element->next->next;
		if (old_element == clist_head(clist))
		{
			clist->head = element->next;
		}
	}

	free(old_element);
	--clist->size;
	return 0;
}