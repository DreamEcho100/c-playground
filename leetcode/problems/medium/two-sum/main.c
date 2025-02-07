#include <stdlib.h>
#include <math.h>

#define HASH_MAP_MAX 10000

typedef struct HasMap
{
	int key;
	int value;
} hash_map_t;

int hashKey(int k)
{
	return abs(k) % HASH_MAP_MAX;
}

/**
 * Given an array of integers nums and an integer target, return indices of the two numbers such that they add up to target.
 *
 * You may assume that each input would have exactly one solution, and you may not use the same element twice.
 *
 * You can return the answer in any order.
 *
 *
 *
 * Example 1:
 *
 * Input: nums = [2,7,11,15], target = 9
 * Output: [0,1]
 * Explanation: Because nums[0] + nums[1] == 9, we return [0, 1].
 *
 * Example 2:
 *
 * Input: nums = [3,2,4], target = 6
 * Output: [1,2]
 *
 * Example 3:
 *
 * Input: nums = [3,3], target = 6
 * Output: [0,1]
 *
 *
 *
 * Constraints:
 *
 *     2 <= nums.length <= 104
 *     -109 <= nums[i] <= 109
 *     -109 <= target <= 109
 *     Only one valid answer exists.
 *
 * Follow-up: Can you come up with an algorithm that is less than O(n2) time complexity?
 */
/**
 * Note: The returned array must be malloced, assume caller calls free().
 */
int *twoSum(int *nums, int numsSize, int target, int *returnSize)
{
	// Create hash map
	hash_map_t *numberToIndexMap = (hash_map_t *)malloc(sizeof(hash_map_t) * HASH_MAP_MAX);

	// Init it with -10000, that's only a dump implementation and could be improved
	for (unsigned int i = 0; i < HASH_MAP_MAX; i++)
	{
		numberToIndexMap[i].key = -10000;
		numberToIndexMap[i].value = -10000;
	}

	for (unsigned int i = 0; i < numsSize; i++)
	{
		// calc the compliment to search for
		int compliment = target - nums[i];
		// Get it's `hashedIndex` key to search with on our hash_map
		int hashedComplimentValue = hashKey(compliment);

		// If the complement is found _(been stored on some prev iteration)_
		if (numberToIndexMap[hashedComplimentValue].key == compliment)
		{
			// return the indexes for the current and it's complement in an int array
			int *arr = (int *)malloc(sizeof(int) * 2);
			// Store the complement index first since it's what's been stored first
			arr[0] = numberToIndexMap[hashedComplimentValue].value;
			// Then the current
			arr[1] = i;

			*returnSize = 2; // Update returnSize
			free(numberToIndexMap);
			return arr;
		}

		int currHashedValue = hashKey(nums[i]);
		// Key stores the number
		numberToIndexMap[currHashedValue].key = nums[i];
		// value stores it's index on the array
		numberToIndexMap[currHashedValue].value = i;
	}

	// If no solution found, return NULL
	free(numberToIndexMap);
	return NULL;
}