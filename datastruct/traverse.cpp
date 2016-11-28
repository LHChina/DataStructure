#include "List.h"
#include "BiTree.h"

int preorder(const BiTreeNode *node, List *list)
{
	if (!bitree_is_eob(node))
	{
		if (0 != list_ins_next(list, list_tail(list), bitree_data(node)))
		{
			return -1;
		}

		if (NULL != bitree_left(node))
		{
			if (0 != preorder(bitree_left(node), list))
				return -1;
		}

		if (NULL != bitree_right(node))
		{
			if (0 != preorder(bitree_right(node), list))
				return -1;
		}
	}

	return 0;
}

int inorder(const BiTreeNode *node, List *list)
{
	if (!bitree_is_eob(node))
	{
		if (NULL != bitree_left(node))
		{
			if (0 != inorder(bitree_left(node), list))
				return -1;
		}

		if (0 != list_ins_next(list, list_tail(list), bitree_data(node)))
		{
			return -1;
		}

		if (NULL != bitree_right(node))
		{
			if (0 != inorder(bitree_right(node), list))
				return -1;
		}
	}

	return 0;
}

int postorder(const BiTreeNode *node, List *list)
{
	if (!bitree_is_eob(node))
	{
		if (NULL != bitree_left(node))
		{
			if (0 != postorder(bitree_left(node), list))
				return -1;
		}

		if (NULL != bitree_right(node))
		{
			if (0 != postorder(bitree_right(node), list))
				return -1;
		}

		if (0 != list_ins_next(list, list_tail(list), bitree_data(node)))
		{
			return -1;
		}
	}

	return 0;
}