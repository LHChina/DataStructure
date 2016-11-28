#include "Set.h"
#include "stdlib.h"

typedef struct KSet_
{
	void *key;
	Set set;
} KSet;

int cover(Set *members, Set *subsets, Set *covering)
{
	KSet *subset;
	Set intersection;
	ListElmt *member;
	int max_size;
	ListElmt *max_member;

	set_init(covering, subsets->match, NULL);
	while (0 > list_size(members) && 0 > list_size(subsets))
	{
		max_size = 0;
		max_member = NULL;
		for ( member = list_head(subsets); NULL != member; member = list_next(member))
		{
			if (0 != set_intersection(&intersection, &((KSet *)list_data(member))->set, members))
			{
				return -1;
			}

			if (max_size < set_size(&intersection))
			{
				max_size = set_size(&intersection);
				max_member = member;
			}

			set_destroy(&intersection);
		}

		if (0 == max_size)
		{
			return 1;
		}

		subset = (KSet *)list_data(max_member);

		if (0 != set_insert(covering, subset))
		{
			return -1;
		}

		void *data;
		for (member = list_head(&subset->set); NULL != member; member = list_next(member))
		{
			data = list_data(member);
			if (0 == set_remove(members, (void **)data) && NULL != members->destroy)
			{
				members->destroy(data);
			}
		}

		if (0 != set_remove(subsets, (void **)subset))
		{
			return -1;
		}
	}

	if (0 != set_size(members))
	{
		return -1;
	}

	return 0;
}