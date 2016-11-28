#include "Chtbl.h"

#include "stdlib.h"
#include "string.h"

int chtbl_init(CHTbl *chtbl, int buckets, int(*h)(const void *data), int(*match)(const void *key1, const void *key2), void(*destroy)(void *data))
{
	int i;
	if (NULL == (chtbl->table = (List *)malloc(buckets * sizeof(List))))
	{
		return -1;
	}

	chtbl->buckets = buckets;
	
	for (i=0; i<buckets; ++i)
	{
		list_init(&chtbl->table[i], destroy);
	} //end of for

	chtbl->h = h;
	chtbl->match = match;
	chtbl->destroy = destroy;

	chtbl->size = 0;
	return 0;
}

void chtbl_destroy(CHTbl *chtbl)
{
	int i;
	for (i=0; i<chtbl->buckets; ++i)
	{
		list_destroy(&chtbl->table[i]);
	} //end of for

	free(chtbl->table);
	memset(chtbl, 0, sizeof(CHTbl));
	return;
}

int chtbl_insert(CHTbl *chtbl, const void *data)
{
	void *temp;
	int bucket;
	int retval;
	
	temp = (void *)data;
	if (0 == chtbl_lookup(chtbl, &temp))
	{
		return 1;
	}

	bucket = chtbl->h(data) % chtbl->buckets;

	if (0 == (retval = list_ins_next(&chtbl->table[bucket], NULL, data)))
	{
		++chtbl->size;
	}

	return retval;
}

int chtbl_remove(CHTbl *chtbl, void **data)
{
	int bucket;
	int retval;

	ListElmt *prev;
	ListElmt *element;

	bucket = chtbl->h(*data) % chtbl->buckets;

	prev = NULL;

	for (element = list_head(&chtbl->table[bucket]); NULL != element; element = list_next(element))
	{
		if (chtbl->match(list_data(element), *data))
		{
			if (0 == list_rem_next(&chtbl->table[bucket], prev, data))
			{
				--chtbl->size;
				return 0;
			}
			else
			{
				return -1;
			}
		}
		prev = element;
	} //end of for

	return -1;
}

int chtbl_lookup(CHTbl *chtbl, void **data)
{
	int bucket;
	
	ListElmt *element;

	bucket = chtbl->h(data) % chtbl->buckets;
	for (element = list_head(&chtbl->table[bucket]); NULL != element; element = list_next(element))
	{
		if (0 == chtbl->match(list_data(element), data))
		{
			*data = list_data(element);
			return 0;
		}
	} //end of for

	return -1;
}


