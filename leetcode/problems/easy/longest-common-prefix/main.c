/*
 * 14. Longest Common Prefix
 * Easy
 * Topics
 * Companies
 * Write a function to find the longest common prefix string amongst an array of
 * strings.
 *
 * If there is no common prefix, return an empty string "".
 *
 *
 *
 * Example 1:
 *
 * Input: strs = ["flower","flow","flight"]
 * Output: "fl"
 * Example 2:
 *
 * Input: strs = ["dog","racecar","car"]
 * Output: ""
 * Explanation: There is no common prefix among the input strings.
 *
 *
 * Constraints:
 *
 * 1 <= strs.length <= 200
 * 0 <= strs[i].length <= 200
 * strs[i] consists of only lowercase English letters if it is non-empty.
 *
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define NULL_TERMINATOR_CHAR ('\0')

// Helper function to allocate and return an empty string
char *allocateEmptyString() {
  char *emptyStr = malloc(1);
  if (emptyStr == NULL) {
    fprintf(stderr, "Memory allocation for empty string failed!\n");
    return NULL;
  }
  emptyStr[0] = NULL_TERMINATOR_CHAR;
  return emptyStr;
}

char *longestCommonPrefix(char **strs, int strsSize) {

  // int minLength = 0;
  // Handle edge case where strs is empty or first string is empty
  if (strsSize == 0 ||
      // ((minLength = strlen(strs[0])) == 0)
      strs[0][0] == NULL_TERMINATOR_CHAR) {
    return allocateEmptyString();
  }

  int minLength = minLength = strlen(strs[0]);
  // Find the minimum string length in the array
  // Start at 1 since we already considered strs[0]
  for (int i = 1; i < strsSize; i++) {
    int currentStrSize = strlen(strs[i]);
    if (currentStrSize == 0) {
      return allocateEmptyString();
    }
    if (currentStrSize < minLength) {
      minLength = currentStrSize;
    }
  }

  // Allocate memory for the common prefix
  // Ensures that memory is initialized to zero using `calloc`, making the
  // string null-terminated from the start
  char *commonPrefix = calloc(minLength + 1, 1);
  // malloc(minLength + 1);
  if (commonPrefix == NULL) {
    fprintf(stderr, "Memory allocation `commonPrefix` failed!\n");
    return NULL;
  }

  // Determine the longest common prefix
  // Loop for the `minLength` of a possible prefix could be
  for (int i = 0; i < minLength; i++) {
    char currentChar = strs[0][i];

    for (int j = 1; j < strsSize; j++) {
      if (
          // The following is commented because it's not needed since we fond
          // the min length earlier currentChar == NULL_TERMINATOR_CHAR ||
          currentChar != strs[j][i]) {
        commonPrefix[i] = NULL_TERMINATOR_CHAR;
        // Early return when mismatch found
        return commonPrefix;
      }
    }

    commonPrefix[i] = currentChar;
  }

  return commonPrefix;
}

int main() {
  char *strs1[] = {"flower", "flow", "flight"};
  char *result1 = longestCommonPrefix(strs1, 3);
  printf("Longest Common Prefix: %s\n", result1);
  free(result1);

  char *strs2[] = {"dog", "racecar", "car"};
  char *result2 = longestCommonPrefix(strs2, 3);
  printf("Longest Common Prefix: %s\n", result2);
  free(result2);

  char *strs3[] = {};
  char *result3 = longestCommonPrefix(strs3, 0);
  printf("Longest Common Prefix: %s\n", result3);
  free(result3);

  return 0;
}
