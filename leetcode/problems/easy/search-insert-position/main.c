/**
35. Search Insert Position
Easy
Topics
Companies
Given a sorted array of distinct integers and a target value, return the index if the target is found. If not, return the index where it would be if it were inserted in order.

You must write an algorithm with O(log n) runtime complexity.



Example 1:

Input: nums = [1,3,5,6], target = 5
Output: 2
Example 2:

Input: nums = [1,3,5,6], target = 2
Output: 1
Example 3:

Input: nums = [1,3,5,6], target = 7
Output: 4


Constraints:

1 <= nums.length <= 104
-104 <= nums[i] <= 104
nums contains distinct values sorted in ascending order.
-104 <= target <= 104
*/
#include <stdio.h>

int searchInsert(int *nums, int numsSize, int target)
{
	if (!nums)
	{
		return -1;
	}

	int low = 0;
	int high = numsSize - 1;
	int mid;

	while (low <= high)
	{
		mid = low + ((high - low) / 2);
		if (target == nums[mid])
		{
			return mid;
		}
		else if (target > nums[mid])
		{
			low = mid + 1;
		}
		else
		{
			high = mid - 1;
		}
	}

	return low;
}

int main()
{
	int nums[] = {1, 3, 5, 6};
	int numsSize = sizeof(nums) / sizeof(nums[0]);
	int target = 7;
	int result = searchInsert(nums, numsSize, target);
	printf("result = %d\n", result);
	return 0;
}
