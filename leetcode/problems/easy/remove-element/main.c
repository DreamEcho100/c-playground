/**
 * 27. Remove Element
 * Easy
 * Topics
 * Companies
 * Hint
 * Given an integer array nums and an integer val, remove all occurrences of val in nums in-place. The order of the elements may be changed. Then return the number of elements in nums which are not equal to val.
 *
 * Consider the number of elements in nums which are not equal to val be k, to get accepted, you need to do the following things:
 *
 * Change the array nums such that the first k elements of nums contain the elements which are not equal to val. The remaining elements of nums are not important as well as the size of nums.
 * Return k.
 * Custom Judge:
 *
 * The judge will test your solution with the following code:
 *
 * int[] nums = [...]; // Input array
 * int val = ...; // Value to remove
 * int[] expectedNums = [...]; // The expected answer with correct length.
 *                             // It is sorted with no values equaling val.
 *
 * int k = removeElement(nums, val); // Calls your implementation
 *
 * assert k == expectedNums.length;
 * sort(nums, 0, k); // Sort the first k elements of nums
 * for (int i = 0; i < actualLength; i++) {
 *     assert nums[i] == expectedNums[i];
 * }
 * If all assertions pass, then your solution will be accepted.
 *
 *
 *
 * Example 1:
 *
 * Input: nums = [3,2,2,3], val = 3
 * Output: 2, nums = [2,2,_,_]
 * Explanation: Your function should return k = 2, with the first two elements of nums being 2.
 * It does not matter what you leave beyond the returned k (hence they are underscores).
 * Example 2:
 *
 * Input: nums = [0,1,2,2,3,0,4,2], val = 2
 * Output: 5, nums = [0,1,4,0,3,_,_,_]
 * Explanation: Your function should return k = 5, with the first five elements of nums containing 0, 0, 1, 3, and 4.
 * Note that the five elements can be returned in any order.
 * It does not matter what you leave beyond the returned k (hence they are underscores).
 *
 *
 * Constraints:
 *
 * 0 <= nums.length <= 100
 * 0 <= nums[i] <= 50
 * 0 <= val <= 100
 */

/**
 *
 */
#include <stddef.h>

int removeElement(int *nums, int numsSize, int val)
{

	if (numsSize == 0 || nums == NULL)
	{
		return 0;
	}

	int currentElemIndex = 0;
	for (int i = 0; i < numsSize; i++)
	{
		if (nums[i] == val)
		{
			continue;
		}

		nums[currentElemIndex] = nums[i];
		currentElemIndex++;
	}

	return currentElemIndex;
}

#include <stdio.h>

void printArray(int *nums, int size)
{
	printf("[");
	for (int i = 0; i < size; i++)
	{
		printf("%d", nums[i]);
		if (i < size - 1)
			printf(", ");
	}
	printf("]\n");
}

int main()
{
	int nums1[] = {3, 2, 2, 3};
	int size1 = sizeof(nums1) / sizeof(nums1[0]);
	int k1 = removeElement(nums1, size1, 3);
	printf("k = %d, nums = ", k1);
	printArray(nums1, k1);

	int nums2[] = {0, 1, 2, 2, 3, 0, 4, 2};
	int size2 = sizeof(nums2) / sizeof(nums2[0]);
	int k2 = removeElement(nums2, size2, 2);
	printf("k = %d, nums = ", k2);
	printArray(nums2, k2);

	int nums3[] = {3, 3, 3, 3};
	int size3 = sizeof(nums3) / sizeof(nums3[0]);
	int k3 = removeElement(nums3, size3, 3);
	printf("k = %d, nums = ", k3);
	printArray(nums3, k3);

	return 0;
}