#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/*
 * 9. Palindrome Number
 * Easy
 * Topics
 * Companies
 * Hint
 * Given an integer x, return true if x is a
 * palindrome
 * , and false otherwise.
 *
 *
 *
 * Example 1:
 *
 * Input: x = 121
 * Output: true
 * Explanation: 121 reads as 121 from left to right and from right to left.
 * Example 2:
 *
 * Input: x = -121
 * Output: false
 * Explanation: From left to right, it reads -121. From right to left, it becomes 121-. Therefore it is not a palindrome.
 * Example 3:
 *
 * Input: x = 10
 * Output: false
 * Explanation: Reads 01 from right to left. Therefore it is not a palindrome.
 *
 *
 * Constraints:
 *
 * -231 <= x <= 231 - 1
 *
 *
 * Follow up: Could you solve it without converting the integer to a string?
 */
bool isPalindrome(int x)
{
	if (x < 0 || x != 0 && x % 10 == 0)
		return false;

	int length = snprintf(NULL, 0, "%d", x);

	int strSize = length + 1;
	char *str = malloc(strSize);
	snprintf(str, strSize, "%d", x);

	int beforeMid = length / 2;
	for (int i = 0; i < beforeMid; i++)
	{
		if (str[i] != str[length - 1 - i])
		{
			free(str);
			return false;
		}
	}

	free(str);

	return true;
}

int main()
{
	int x = 11;
	/**
	 * In C, snprintf() function is a standard library function that is used
	 * to print the specified string till a specified length in the specified format.
	 * It is defined in the `<stdio.h>` header file.
	 */

	bool isXPalindrome = isPalindrome(x);
	printf("isXPalindrome: %d\n", isXPalindrome ? 1 : 0);

	return 0;
}