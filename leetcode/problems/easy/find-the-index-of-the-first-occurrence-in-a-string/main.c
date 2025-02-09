/**
 * 28. Find the Index of the First Occurrence in a String
 * Easy
 * Topics
 * Companies
 * Given two strings needle and haystack, return the index of the first occurrence of needle in haystack, or -1 if needle is not part of haystack.
 *
 *
 *
 * Example 1:
 *
 * Input: haystack = "sadbutsad", needle = "sad"
 * Output: 0
 * Explanation: "sad" occurs at index 0 and 6.
 * The first occurrence is at index 0, so we return 0.
 * Example 2:
 *
 * Input: haystack = "leetcode", needle = "leeto"
 * Output: -1
 * Explanation: "leeto" did not occur in "leetcode", so we return -1.
 *
 *
 * Constraints:
 *
 * 1 <= haystack.length, needle.length <= 104
 * haystack and needle consist of only lowercase English characters.
 */

/**
 *
 */

int strStr(char *haystack, const char *needle)
{
	if (!haystack || !needle)
		return -1;

	if (needle[0] == '\0')
		return 0;

	int i = 0;
	int j = 0;
	for (; haystack[i] != '\0'; i++)
	{
		j = 0;
		while (
				// the needle is not empty
				needle[j] != '\0'
				// the characters match
				&& haystack[i + j] == needle[j])
		{
			// Move to the next character to compare
			j++;
		}

		// If the needle is empty, we found it
		if (needle[j] == '\0')
		{
			return i;
		}
	}

	// If we didn't find it
	return -1;
}

#include <stdio.h>

void testStrStr(const char *haystack, const char *needle)
{
	int result = strStr(haystack, needle);
	printf("strStr(\"%s\", \"%s\") = %d\n", haystack, needle, result);
}

int main()
{
	testStrStr("sadbutsad", "sad");			// Expected: 0
	testStrStr("leetcode", "leeto");		// Expected: -1
	testStrStr("hello", "ll");					// Expected: 2
	testStrStr("hi", "hello");					// Expected: -1
	testStrStr("aaaaa", "bba");					// Expected: -1
	testStrStr("mississippi", "issip"); // Expected: 4
	testStrStr("a", "a");								// Expected: 0
	testStrStr("", "a");								// Expected: -1
	testStrStr("a", "");								// Expected: 0
	testStrStr("", "");									// Expected: 0
}
