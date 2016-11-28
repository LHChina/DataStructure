#ifndef CHTBL_H_INCLUDE
#define CHTBL_H_INCLUDE

#include "List.h"

typedef struct CHTBL_
{
	int buckets;

	int(*h)(const void *data);
	int(*match)(const void *key1, const void *key2);
	void(*destroy)(void *data);

	int size;
	List *table;
} CHTbl;

int chtbl_init(CHTbl *chtbl, int buckets, int(*h)(void *data), int(*match)(const void *key1, const void *key2), void(*destroy)(void *data));
void chtbl_destroy(CHTbl *chtbl);
int chtbl_insert(CHTbl *chtbl, const void *data);
int chtbl_remove(CHTbl *chtbl, void **data);
int chtbl_lookup(CHTbl *chtbl, void **data);

#define chtbl_size(chtbl) ((chtbl)->size)

#endif
