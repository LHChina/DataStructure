#ifndef BITREE_H_INCLUDE
#define BITREE_H_INCLUDE

#include "stdlib.h"

typedef struct BiTreeNode_
{
	void *data;
	struct BiTreeNode_ *left;
	struct BiTreeNode_ *right;
} BiTreeNode;

typedef struct BiTree_
{
	int size;

	int(*compare)(const void *key1, const void *key2);
	void(*destroy)(void *data);

	BiTreeNode *root;
} BiTree;

void bitree_init(BiTree *bitree, void(*destroy)(void *data));
void bitree_destroy(BiTree *bitree);
int bitree_ins_left(BiTree *bitree, BiTreeNode *node, const void *data);
int bitree_ins_right(BiTree *bitree, BiTreeNode *node, const void *data);
void bitree_rem_left(BiTree *bitree, BiTreeNode *node);
void bitree_rem_right(BiTree *bitree, BiTreeNode *node);
int bitree_merge(BiTree *merge, BiTree *left, BiTree *right, const void *data);

#define bitree_size(bitree) ((bitree)->size)
#define bitree_root(bitree) ((bitree)->root)
#define bitree_data(node) ((node)->data)
#define bitree_left(node) ((node)->left)
#define bitree_right(node) ((node)->right)
#define bitree_is_eob(node) (NULL == (node))
#define bitree_is_leaf(node) (NULL == (node)->left && NULL == (node)->right)

#endif
