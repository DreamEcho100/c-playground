/*
20. Valid Parentheses
Easy
Topics
Companies
Hint
Given a string s containing just the characters '(', ')', '{', '}', '[' and ']', determine if the input string is valid.

An input string is valid if:

Open brackets must be closed by the same type of brackets.
Open brackets must be closed in the correct order.
Every close bracket has a corresponding open bracket of the same type.


Example 1:

Input: s = "()"

Output: true

Example 2:

Input: s = "()[]{}"

Output: true

Example 3:

Input: s = "(]"

Output: false

Example 4:

Input: s = "([])"

Output: true



Constraints:

1 <= s.length <= 104
s consists of parentheses only '()[]{}'.
*/

#include <stdbool.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

// ASCII decimal values for the brackets
#define CLOSED_CURLY_BRACKET_ASCII_DECIMAL (125)

bool isValid(char *s)
{
	// Handle edge case where s is empty or NULL
	if (s == NULL || s[0] == '\0')
	{
		return true;
	}

	// Map of closed brackets to their corresponding open brackets
	char bracketsClosedToOpenChars[CLOSED_CURLY_BRACKET_ASCII_DECIMAL + 1] = {0};

	// Initialize the map
	bracketsClosedToOpenChars[')'] = '(';
	bracketsClosedToOpenChars['}'] = '{';
	bracketsClosedToOpenChars[']'] = '[';

	// Initialize the stack
	// The stack will only contain open brackets
	int sLen = strlen(s);
	char *openBracketsStack = malloc(sLen);
	if (openBracketsStack == NULL)
	{
		fprintf(stderr, "Memory allocation for `stack` failed!\n");
		return NULL;
	}
	// The stack size will be the index of the next element to be pushed
	int stackSize = 0;

	for (int i = 0; i < sLen; i++)
	{
		char currentChar = s[i];
		switch (currentChar)
		{
		case '(':
		case '[':
		case '{':
			// Push the open bracket onto the stack
			// And increment the stack size using the post-increment operator
			openBracketsStack[stackSize++] = currentChar;
			break;

		case ')':
		case ']':
		case '}':
			// Get the corresponding open bracket for the current character from the map
			char correspondingOpenBracket = bracketsClosedToOpenChars[currentChar];

			// If the stack is empty or the top of the stack doesn't match, return false
			if (stackSize == 0 || openBracketsStack[stackSize - 1] != correspondingOpenBracket)
			{
				// Don't forget to free the stack before returning
				free(openBracketsStack);
				return false; // Stack is empty or top of stack doesn't match
			}

			// Pop the open bracket from the stack
			stackSize--;
		}
	}

	// Don't forget to free the stack before returning
	free(openBracketsStack);

	// If the stack is empty, all brackets are matched
	return stackSize == 0;
}

void runTest(char *testString, bool expected)
{
	bool result = isValid(testString);
	printf("Test: \"%s\" | Expected: %s | Result: %s\n",
				 testString,
				 expected ? "true" : "false",
				 result ? "true" : "false");
}

int main()
{
	// Test cases
	runTest("()", true);							// Simple valid case
	runTest("()[]{}", true);					// Multiple types of brackets
	runTest("(]", false);							// Mismatched brackets
	runTest("([])", true);						// Nested valid brackets
	runTest("([)]", false);						// Incorrect order
	runTest("{[]}", true);						// Nested valid brackets
	runTest("", true);								// Empty string
	runTest("(", false);							// Single opening bracket
	runTest(")", false);							// Single closing bracket
	runTest("{[()()]}", true);				// Complex valid case
	runTest("{[()()]}]", false);			// Extra closing bracket
	runTest("((((((()))))))", true);	// Long nested valid brackets
	runTest("(((((((())))))", false); // Long nested with missing closing

	return 0;
}
