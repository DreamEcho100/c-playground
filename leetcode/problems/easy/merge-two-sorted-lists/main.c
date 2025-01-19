/*
 * 21. Merge Two Sorted Lists
 * Easy
 * Topics
 * Companies
 * You are given the heads of two sorted linked lists list1 and list2.
 *
 * Merge the two lists into one sorted list. The list should be made by splicing together the nodes of the first two lists.
 *
 * Return the head of the merged linked list.
 *
 *
 *
 * Example 1:
 *
 *
 * Input: list1 = [1,2,4], list2 = [1,3,4]
 * Output: [1,1,2,3,4,4]
 * Example 2:
 *
 * Input: list1 = [], list2 = []
 * Output: []
 * Example 3:
 *
 * Input: list1 = [], list2 = [0]
 * Output: [0]
 *
 *
 * Constraints:
 *
 * The number of nodes in both lists is in the range [0, 50].
 * -100 <= Node.val <= 100
 * Both list1 and list2 are sorted in non-decreasing order.
 */

/**
 * Definition for singly-linked list.
 * struct ListNode {
 *     int val;
 *     struct ListNode *next;
 * };
 */

#include <stdbool.h>
#include <stdlib.h>

typedef struct ListNode list_node_t;

struct ListNode
{
	int val;
	struct ListNode *next;
};

list_node_t *mergeTwoLists(list_node_t *list1, list_node_t *list2)
{

	// 	In C, local variables (on the stack) are indeed destroyed when the function exits. This applies to variables like the dummy node in the improved solution.
	// However, if you are simply linking existing heap-allocated nodes (list1 and list2) together, there's no need to allocate new memory.

	// Dummy node to simplify the logic
	// The `dummy` node is just a placeholder for managing pointers while merging.
	list_node_t dummy;
	list_node_t *tail = &dummy;
	dummy.next = NULL;

	while (list1 != NULL && list2 != NULL)
	{
		if (list1->val < list2->val)
		{
			tail->next = list1;
			list1 = list1->next;
		}
		else
		{
			tail->next = list2;
			list2 = list2->next;
		}

		tail = tail->next;
	}

	tail->next = (list1 != NULL) ? list1 : list2;

	// The actual returned list is composed of nodes from list1 and list2
	// Which remain valid after the function ends because they are allocated on the heap (outside this function).
	return dummy.next;
}
