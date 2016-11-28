#include "OHTbl.h"
#include <stdlib.h>
#include "List.h"
#include "string.h"

static char vacated;

int ohtbl_init(OHTbl *ohtbl, int positions, int(*h1)(const void *data), int(*h2)(const void *data), int(*match)(const void *key1, const void *key2), void(*destroy)(void *data))
{
	int i;
	if (NULL == (ohtbl->table = (void **)malloc(positions * sizeof(void *))))
	{
		return -1;
	}

	ohtbl->positions = positions;
	for (i = 0; i < ohtbl->positions; i++)
	{
		ohtbl->table[i] = NULL;
	}
	
	ohtbl->vacated = &vacated;

	ohtbl->h1 = h1;
	ohtbl->h2 = h2;
	ohtbl->match = match;
	ohtbl->destroy = destroy;

	ohtbl->size = 0;
	return 0;
}

void ohtbl_destroy(OHTbl *ohtbl)
{
	int i;
	if (NULL != ohtbl->destroy)
	{
		for (i = 0; i < ohtbl->positions; ++i)
		{
			if ((NULL != ohtbl->table[i]) || (ohtbl->vacated == ohtbl->table[i]))
			{
				ohtbl->destroy(ohtbl->table[i]);
			}
		}
	}

	free(ohtbl->table);

	memset(ohtbl, 0, sizeof(OHTbl));

	return;
}

int ohtbl_insert(OHTbl *ohtbl, const void *data)
{
	int i;
	int hashVal;
	void *temp;

	if (ohtbl_size(ohtbl) == ohtbl->positions)
	{
		return -1;
	}

	temp = (void *)data;
	if (0 == ohtbl_lookup(ohtbl, &temp))
	{
		return 1;
	}

	for (i = 0; i < ohtbl->positions; ++i)
	{
		hashVal = (ohtbl->h1(data) + i * ohtbl->h2(data)) % ohtbl->positions;

		if ((NULL == ohtbl->table[i]) || (ohtbl->vacated == ohtbl->table[i]))
		{
			ohtbl->table[i] = (void *)data;
			++ohtbl->size;
			return 0;
		}
	}
	
	return -1;
}

int ohtbl_remove(OHTbl *ohtbl, void **data)
{
	int i;
	int hashVal;
	
	for (i = 0; i < ohtbl->positions; ++i)
	{
		hashVal = (ohtbl->h1(data) + i * ohtbl->h2(data)) % ohtbl->positions;

		if (NULL == ohtbl->table[i])
		{
			return -1;
		}
		else if (ohtbl->vacated == ohtbl->table[i])
		{
			continue;
		}
		else if (1 == ohtbl->match(*data, ohtbl->table[i]))
		{
			*data = ohtbl->table[i];
			ohtbl->table[i] = ohtbl->vacated;
			--ohtbl->size;
			return 0;
		}
	}

	return -1;
}

int ohtbl_lookup(OHTbl *ohtbl, void **data)
{
	int i;
	int hashVal;

	for (i = 0; i < ohtbl->positions; ++i)
	{
		hashVal = (ohtbl->h1(data) + i * ohtbl->h2(data)) % ohtbl->positions;

		if (NULL == ohtbl->table[i])
		{
			return -1;
		}
		else if (ohtbl->vacated == ohtbl->table[i])
		{
			continue;
		}
		else if (1 == ohtbl->match(*data, ohtbl->table[i]))
		{
			*data = ohtbl->table[i];
			return 0;
		}
	}

	return -1;
}