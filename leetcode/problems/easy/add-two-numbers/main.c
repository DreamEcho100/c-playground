#include <stdlib.h>

#include "./main.h"

/*
 * 2. Add Two Numbers
 * Medium
 * Topics
 * Companies
 * You are given two non-empty linked lists representing two non-negative integers. The digits are stored in reverse order, and each of their nodes contains a single digit. Add the two numbers and return the sum as a linked list.
 *
 * You may assume the two numbers do not contain any leading zero, except the number 0 itself.
 *
 *
 *
 * Example 1:
 *
 *
 * Input: l1 = [2,4,3], l2 = [5,6,4]
 * Output: [7,0,8]
 * Explanation: 342 + 465 = 807.
 * Example 2:
 *
 * Input: l1 = [0], l2 = [0]
 * Output: [0]
 * Example 3:
 *
 * Input: l1 = [9,9,9,9,9,9,9], l2 = [9,9,9,9]
 * Output: [8,9,9,9,0,0,0,1]
 *
 *
 * Constraints:
 *
 * The number of nodes in each linked list is in the range [1, 100].
 * 0 <= Node.val <= 9
 * It is guaranteed that the list represents a number that does not have leading zeros.
 */

/**
 * Definition for singly-linked list.
 * struct ListNode {
 *     int val;
 *     struct ListNode *next;
 * };
 */

list_node_t *addTwoNumbers(list_node_t *l1, list_node_t *l2)
{
	list_node_t *beforeHead = malloc(sizeof(list_node_t));
	if (beforeHead == NULL)
	{
		return NULL;
	}
	list_node_t *currentNode = beforeHead;

	int carry = 0;
	while (l1 != NULL || l2 != NULL || carry != 0)
	{
		int sum = carry;

		if (l1 != NULL)
		{
			sum += l1->val;
			l1 = l1->next;
		}
		if (l2 != NULL)
		{
			sum += l2->val;
			l2 = l2->next;
		}

		list_node_t *newNode = malloc(sizeof(list_node_t));
		if (newNode == NULL)
		{
			// Free all previously allocated nodes
			while (beforeHead != NULL)
			{
				list_node_t *temp = beforeHead;
				beforeHead = beforeHead->next;
				free(temp);
			}
			return NULL;
		}

		newNode->val = sum % 10;
		newNode->next = NULL;

		currentNode->next = newNode;
		currentNode = currentNode->next;
		carry = sum / 10;
	}

	list_node_t *result = beforeHead->next;
	free(beforeHead);

	return result;
}
