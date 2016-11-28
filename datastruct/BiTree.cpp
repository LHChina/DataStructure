#include "BiTree.h"
#include "stdlib.h"
#include "string.h"

void bitree_init(BiTree *bitree, void(*destroy)(void *data))
{
	bitree->size = 0;
	bitree->destroy = destroy;
	bitree->root = NULL;

	return;
}

void bitree_destroy(BiTree *bitree)
{
	bitree_rem_left(bitree, NULL);

	memset(bitree, 0, sizeof(BiTree));
	return;
}

int bitree_ins_left(BiTree *bitree, BiTreeNode *node, const void *data)
{
	BiTreeNode *newNode, **position;

	if (NULL == node)
	{
		if (0 < bitree_size(bitree))
		{
			return -1;
		}

		position = &bitree->root;
	}
	else
	{
		if (NULL != node->left)
		{
			return -1;
		}

		position = &node->left;
	}

	if (NULL == (newNode = (BiTreeNode *)malloc(sizeof(BiTreeNode))))
	{
		return -1;
	}

	newNode->data = (void *)data;
	newNode->left = NULL;
	newNode->right = NULL;
	*position = newNode;

	++bitree->size;

	return 0;
}

int bitree_ins_right(BiTree *bitree, BiTreeNode *node, const void *data)
{
	BiTreeNode *newNode, **position;

	if (NULL == node)
	{
		if (0 < bitree_size(bitree))
		{
			return -1;
		}

		position = &bitree->root;
	}
	else
	{
		if (NULL != node->right)
		{
			return -1;
		}

		position = &node->right;
	}

	if (NULL == (newNode = (BiTreeNode *)malloc(sizeof(BiTreeNode))))
	{
		return -1;
	}

	newNode->data = (void *)data;
	newNode->left = NULL;
	newNode->right = NULL;
	*position = newNode;

	++bitree->size;

	return 0;
}

void bitree_rem_left(BiTree *bitree, BiTreeNode *node)
{
	BiTreeNode **position = NULL;

	if (0 == bitree_size(bitree))
	{
		return;
	}

	if (NULL == node)
	{
		position = &bitree->root;
	}
	else
	{
		position = &node->left;
	}

	if (NULL != position)
	{
		bitree_rem_left(bitree, *position);
		bitree_rem_right(bitree, *position);

		if (NULL != bitree->destroy)
		{
			bitree->destroy((*position)->data);
		}
		
		free(*position);
		*position = NULL;
		--bitree->size;
	}

	return;
}
void bitree_rem_right(BiTree *bitree, BiTreeNode *node)
{
	BiTreeNode **position = NULL;

	if (0 == bitree_size(bitree))
	{
		return;
	}

	if (NULL == node)
	{
		position = &bitree->root;
	}
	else
	{
		position = &node->right;
	}

	if (NULL != position)
	{
		bitree_rem_left(bitree, *position);
		bitree_rem_right(bitree, *position);

		if (NULL != bitree->destroy)
		{
			bitree->destroy((*position)->data);
		}

		free(*position);
		*position = NULL;
		--bitree->size;
	}

	return;
}

int bitree_merge(BiTree *merge, BiTree *left, BiTree *right, const void *data)
{
	bitree_init(merge, left->destroy);

	//if (NULL == (merge->root = (BiTreeNode*)malloc(sizeof(BiTreeNode))))
	//{
	//	bitree_destroy(merge);
	//	return -1;
	//}

	//bitree_data(merge->root) = (void *)data;

	if (0 != bitree_ins_left(merge, NULL, data))
	{
		bitree_destroy(merge);
		return -1;
	}

	bitree_left(merge->root) = bitree_root(left);
	bitree_right(merge->root) = bitree_root(right);

	merge->size = bitree_size(left) + bitree_size(right) + merge->size;

	left->root = NULL;
	left->size = 0;
	left->root = NULL;
	left->size = 0;

	return 0;
}