#ifndef DLIST_H_INCLUDE
#define DLIST_H_INCLUDE

typedef struct DoubleListElmt_
{
	void *data;
	struct DoubleListElmt_ *prev;
	struct DoubleListElmt_ *next;
} DListElmt;

typedef struct DoubleList_
{
	int size;
	int (*match)(const void *key1, const void *key2);
	void (*destroy)(void *data);
	struct DoubleListElmt_ *head;
	struct DoubleListElmt_ *tail;
} DList;

void dlist_init(DList *dlist, void(*destroy)(void *data));
void dlist_destroy(DList *dlist);
int dlist_ins_next(DList *dlist, DListElmt *element, const void *data);
int dlist_ins_prev(DList *dlist, DListElmt *element, const void *data);
int dlist_remove(DList *dlist, DListElmt *element, void **data);

#define dlist_size(dlist) ((dlist)->size)
#define dlist_head(dlist) ((dlist)->head)
#define dlist_tail(dlist) ((dlist)->tail)
#define dlist_is_head(element) (NULL == (element)->prev ? 1 : 0)
#define dlist_is_tail(element) (NULL == (element)->next ? 1 : 0)
#define dlist_data(element) ((element)->data)
#define dlist_prev(element) ((element)->prev)
#define dlist_next(element) ((element)->next)

#endif

