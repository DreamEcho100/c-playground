#include <stdio.h>
#include <string.h>
#include "./strings_utils.h"

#include <stddef.h> // For size_t
// Error codes for strncat_s
#define BOOT_DOT_DEV_STRNCAT_S_OK 0
#define BOOT_DOT_DEV_STRNCAT_S_ERR_INVALID_PARAM 22
#define BOOT_DOT_DEV_STRNCAT_S_ERR_TRUNCATION 24
#define BOOT_DOT_DEV_SIZE_MAX 4294967295
#define BOOT_DOT_DEV_NULL_TERMINATOR_CHAR ('\0')

void nih_strcat(char *str1, const char *str2)
{
	if (!str1 || !str2)
	{
		fprintf(stderr, "NULL pointer passed to nih_strcat\n");
		return;
	}

	int offset = 0;
	while (1)
	{
		if (str1[offset] == NULL_TERMINATOR_CHAR)
		{
			break;
		}

		offset++;
	}

	int src_index = 0;
	while (1)
	{
		if (str2[src_index] == NULL_TERMINATOR_CHAR)
		{
			str1[offset + src_index] = str2[src_index];
			break;
		}

		str1[offset + src_index] = str2[src_index];
		src_index++;
	}
}
void nih_strcat_2(char *str1, const char *str2)
{
	if (!str1 || !str2)
	{
		fprintf(stderr, "NULL pointer passed to nih_strcat\n");
		return;
	}

	while (*str1)
	{
		str1++;
	}

	while (*str2)
	{
		// Value assignment: It moves the value (character) from str2 to str1 without modifying the pointers themselves.
		// *str1 = *str2 copies the value from the address str2 points to into the memory location str1 points to.

		// str1 is a pointer to the current position in the destination string.
		*str1 =
				// str2 is a pointer to the current position in the source string.
				*str2;

		str1++;
		str2++;
	}

	*str1 = NULL_TERMINATOR_CHAR;
}
void nih_strcpy(char *dest, const char *src, size_t dest_size)
{
	// Ensure pointers are valid and size is not zero
	if (dest == NULL || src == NULL || dest_size <= 0)
	{
		return;
	}

	size_t remaining = dest_size - 1;

	// Copy characters until the source ends or we reach the size limit
	// dereference the pointer to access the value
	while (remaining > 0 && *src)
	{
		// Assign the value of the `dest` pointer _(it will be the first char initially)_
		*dest =
				// to the value of the `src` pointer _(it will be the first char initially)_
				*src;

		// increment the pointers to access the the char on the next iteration
		dest++;
		src++;
		remaining--;
	}

	*dest = NULL_TERMINATOR_CHAR;
}
size_t nih_strlen(const char *src)
{
	// Return 0 if the input pointer is NULL
	if (src == NULL)
	{
		return 0;
	}

	// Initialize the length to 0 with the type size_t (unsigned integer)
	// because"
	// - The length of a string cannot be negative
	// - It is always a whole number
	// - It can be very large.
	size_t length = 0;

	// Traverse the string until the null terminator is found (end of the string: '\0', which is false in a boolean context)
	while (*src)
	{
		src++;
		length++;
	}

	return length;
}
int nih_strcmp(const char *str1, const char *str2)
{
	// Check for NULL pointers (optional but good practice)
	// To make sure we don't access memory at NULL is undefined behavior (UB) which will likely crash the program :P
	if (str1 == NULL || str2 == NULL)
	{
		fprintf(stderr, "Error: NULL pointer passed to nih_strcmp\n");
		// Consider returning an error code in real applications
		return 0;
	}

	// Traverse both strings
	while (*str1 && *str2)
	{
		// If characters differ, return the difference in ASCII values
		if (*str1 != *str2)
		{
			return *str1 - *str2;
		}

		// Move to the next character in both strings
		str1++;
		str2++;
	}

	// Return difference between the final characters (or null terminators)
	return *str1 - *str2;
}
// Gave me a headache
void nih_strncpy(char *dest, size_t dest_size, const char *src, size_t size_limit)
{

	if (src == NULL || size_limit == 0)
	{
		return;
	}

	size_t i = 0;
	// Copy characters from src to dest up to size_limit
	while (
			// Check if we reached the size limit
			i < size_limit &&
			// Check if we reached the end of the src string
			i < dest_size - 1 &&
			// Check if we reached the end of the src string
			src[i] != NULL_TERMINATOR_CHAR)
	{
		dest[i] = src[i];
		++i;
	}

	// Null-terminate the destination string if there's space
	dest[i] = NULL_TERMINATOR_CHAR;

	// If we copied less than size_limit, null-terminate the dest string
	while (i < dest_size - 1)
	{
		dest[i] = NULL_TERMINATOR_CHAR; // Fill remaining space with null characters
		++i;
	}
}
void nih_strncat(char *dest, const char *src, size_t size_limit)
{
	if (dest == NULL || src == NULL || size_limit <= 0)
	{
		return;
	}

	char *dest_copy = dest;
	size_t dest_size = nih_strlen(dest_copy);

	printf("%zu\n", dest_size);

	while (*dest)
	{
		dest++;
	}

	size_t current_offset = 0;
	while (*src && current_offset < size_limit)
	{
		*dest = *src;
		current_offset++;
		dest++;
		src++;
	}
}
char *nih_strchr(const char *str, int desired_char)
{

	// 	Pointer Casting:
	// Cast str to (char *) when returning to ensure the return type matches the function's signature.

	// After the loop, we check if desired_char is '\0'
	// And handle it explicitly by returning a pointer to the end of the string.
	// This ensures proper behavior for cases like nih_strchr("Hello", '\0').
	if (desired_char == NULL_TERMINATOR_CHAR)
	{
		return (char *)str;
	}

	while (*str)
	{
		if (*str == desired_char)
		{
			return (char *)str;
		}

		str++;
	}

	// Explicit NULL Return :
	// If the loop finishes without finding the character (and desired_char is not '\0')
	// We explicitly return NULL. This is essential for cases where the character isn't in the string.
	return NULL; // Character not found
}
char *nih_strstr(const char *str, const char *substr)
{

	// After the loop, we check if desired_char is '\0'
	// And handle it explicitly by returning a pointer to the end of the string.
	// This ensures proper behavior for cases like nih_strchr("Hello", '\0').
	if (*substr == NULL_TERMINATOR_CHAR)
	{
		return (char *)str;
	}

	char *start_char = (char *)substr;
	char *char_check = (char *)start_char;

	while (*str)
	{

		printf("char_check: %c\n", *char_check);
		if (*char_check == NULL_TERMINATOR_CHAR)
		{
			printf("Match final\n");
			return start_char;
		}

		printf("str: %c\n", *str);
		printf("char_check: %c\n", *char_check);
		printf("*str == *char_check%s\n", *str == *char_check ? "true" : "false");
		if (*str == *char_check)
		{
			printf("is start_char: %s\n", *start_char == *str ? "true" : "false");
			return NULL;
			printf("Match\n");
			if (!start_char)
			{
				*start_char = *str;
				printf("start_char: %c\n", *start_char);
				*char_check = *start_char;
				printf("char_check: %c\n", *char_check);
			}
			else
			{
				printf("Increment\n");
				(void)(*char_check++);
			}

			if (!char_check)
			{
				return (char *)start_char;
			}
		}
		else
		{
			start_char = NULL;
		}

		str++;
	}

	// Explicit NULL Return :
	// If the loop finishes without finding the character (and desired_char is not '\0')
	// We explicitly return NULL. This is essential for cases where the character isn't in the string.
	printf("No match\n");
	return NULL; // Character not found
}

void test_strcat_comparison()
{
	// Custom Implementation
	char nih_first[50] = "Snek";
	char *nih_second = "lang!";
	nih_strcat(nih_first, nih_second);
	printf("Custom nih_strcat: %s\n", nih_first);

	// Standard Library Implementation
	char lib_first[50] = "Snek";
	char *lib_second = "lang!";
	strcat(lib_first, lib_second);
	printf("Standard strcat: %s\n", lib_first);
}
void test_strcpy_comparison()
{
	// Custom Implementation
	char src[] = "Hello";
	char dest[6];
	nih_strcpy(dest, src, sizeof(dest));
	printf("Custom nih_strcpy: %s\n", dest);

	// Standard Library Implementation
	char lib_dest[6];
	strcpy(lib_dest, src);
	printf("Standard strcpy: %s\n", lib_dest);
}
void test_strlen_comparison()
{
	// Custom Implementation
	char str[] = "Hello";
	size_t len = nih_strlen(str);
	printf("Custom nih_strlen: size of \"%s\" is (%zu)\n", str, len);

	// Standard Library Implementation
	size_t lib_len = strlen(str);
	printf("Standard strlen: size of \"%s\" is (%zu)\n", str, lib_len);
}
void test_strcmp_comparison()
{
	// Custom Implementation - Matching strings
	char str1_matches[] = "Hello";
	char str2_matches[] = "Hello";
	int result_matches = nih_strcmp(str1_matches, str2_matches);
	printf("Custom nih_strcmp (matches): %i\n", result_matches);

	// Standard Library Implementation - Matching strings
	int lib_result_matches = strcmp(str1_matches, str2_matches);
	printf("Standard strcmp (matches): %i\n", lib_result_matches);

	// Custom Implementation - First string greater
	char str1_greater[] = "World";
	char str2_greater[] = "Hello";
	int result_greater = nih_strcmp(str1_greater, str2_greater);
	printf("Custom nih_strcmp (greater): %i\n", result_greater);

	// Standard Library Implementation - First string greater
	int lib_result_greater = strcmp(str1_greater, str2_greater);
	printf("Standard strcmp (greater): %i\n", lib_result_greater);

	// Custom Implementation - Second string greater
	char str1_lesser[] = "Hello";
	char str2_lesser[] = "World";
	int result_lesser = nih_strcmp(str1_lesser, str2_lesser);
	printf("Custom nih_strcmp (lesser): %i\n", result_lesser);

	// Standard Library Implementation - Second string greater
	int lib_result_lesser = strcmp(str1_lesser, str2_lesser);
	printf("Standard strcmp (lesser): %i\n", lib_result_lesser);
}
void test_strncpy_comparison()
{
	size_t max_size_to_copy = 3;
	// Custom Implementation
	char src[] = "Hello";
	char dest[6];
	nih_strncpy(dest, sizeof(dest), src, max_size_to_copy);
	printf("Custom nih_strncpy: %s\n", dest);

	// Standard Library Implementation
	char lib_dest[6];
	strncpy(lib_dest, src, max_size_to_copy);
	printf("Standard strncpy: %s\n", lib_dest);

	// ??? - :_(, Why is the standard library implementation copying more than the custom implementation?
	// Output:
	// test_strncpy_comparison start
	// --------------------------------
	// Custom nih_strncpy: Hel
	// Standard strncpy: HelU
	// --------------------------------
	// test_strncpy_comparison end
}
void test_strncat_comparison()
{
	size_t max_size_to_copy = 3;
	// Custom Implementation
	char dest[12] = "Hello";
	char src[] = " World";
	nih_strncat(dest, src, max_size_to_copy);
	printf("Custom nih_strncat: %s\n", dest);

	// Standard Library Implementation
	char lib_dest[12] = "Hello";
	strncat(lib_dest, src, max_size_to_copy);
	printf("Standard strncat: %s\n", lib_dest);
}
void test_strchr_comparison()
{
	// Custom Implementation
	char str[] = "Hello";
	char *pos = nih_strchr(str, 'l');
	printf("Custom nih_strchr: %s\n", pos);

	// Standard Library Implementation
	char *lib_pos = strchr(str, 'l');
	printf("Standard strchr: %s\n", lib_pos);
}
void test_strstr_comparison()
{
	// Custom Implementation
	char str[] = "Hello World";
	// char *pos = nih_strstr(str, "el");
	// printf("Custom nih_strstr: %s\n", pos);
	printf("Custom nih_strstr: Not implemented\n");

	// Standard Library Implementation
	char *lib_pos = strstr(str, "World");
	printf("Standard strstr: %s\n", lib_pos);
}
void test_edge_cases()
{
	// Edge case: Empty strings
	char empty1[] = "";
	char empty2[] = "";
	size_t len_empty1 = nih_strlen(empty1);
	size_t len_empty2 = nih_strlen(empty2);
	printf("Edge case: Length of empty strings: %zu, %zu\n", len_empty1, len_empty2);

	// Edge case: NULL pointers
	printf("Edge case: NULL pointer for nih_strlen: %zu\n", nih_strlen(NULL));

	// Edge case: Concatenation with empty string
	char nih_empty[] = "";
	char nih_concat_result[50] = "Hello";
	nih_strcat(nih_concat_result, nih_empty);
	printf("Edge case: Concatenating with empty string (custom): %s\n", nih_concat_result);

	// Edge case: Concatenation with empty string (standard)
	char lib_concat_result[50] = "Hello";
	strcat(lib_concat_result, nih_empty);
	printf("Edge case: Concatenating with empty string (lib): %s\n", lib_concat_result);

	// Edge case: strcpy with small and large sizes
	char small_src[] = "A";
	char small_dest[2];
	nih_strcpy(small_dest, small_src, sizeof(small_dest));
	printf("Edge case: strcpy with small buffer (custom): %s\n", small_dest);

	// Edge case: strcpy with small and large sizes (standard)
	char lib_small_dest[2];
	strcpy(lib_small_dest, small_src);
	printf("Edge case: strcpy with small buffer (lib): %s\n", lib_small_dest);

	// Edge case: Comparing strings of different lengths (custom)
	char short_str[] = "Hi";
	char long_str[] = "Hello";
	printf("Edge case: Comparing strings of different lengths (custom): %i\n", nih_strcmp(short_str, long_str));

	// Edge case: Comparing strings of different lengths (lib)
	printf("Edge case: Comparing strings of different lengths (lib): %i\n", strcmp(short_str, long_str));

	// Edge case: strncpy with small and large sizes
	char nih_strncpy_src[] = "Hello";

	char nih_strncpy_dest[6];
	nih_strncpy(nih_strncpy_dest, sizeof(nih_strncpy_dest), nih_strncpy_src, 3);
	printf("Edge case: strncpy with small buffer (custom): %s\n", nih_strncpy_dest);

	// Edge case: strncpy with small and large sizes (standard)
	char lib_strncpy_dest[6];
	strncpy(lib_strncpy_dest, nih_strncpy_src, 6);
	printf("Edge case: strncpy with small buffer (lib): %s\n", lib_strncpy_dest);

	// Edge case: strncpy with large buffer
	char nih_strncpy_large_dest[6];
	nih_strncpy(nih_strncpy_large_dest, sizeof(nih_strncpy_large_dest), nih_strncpy_src, 10);
	printf("Edge case: strncpy with large buffer (custom): %s\n", nih_strncpy_large_dest);

	// Edge case: strncpy with large buffer (standard)
	char lib_strncpy_large_dest[6];
	nih_strncpy(lib_strncpy_large_dest, 6, nih_strncpy_src, 10);
	printf("Edge case: strncpy with large buffer (lib): %s\n", lib_strncpy_large_dest);

	// Edge case: strncat with small and large sizes
	char nih_strncat_dest[12] = "Hello";
	char nih_strncat_src[] = " World";
	nih_strncat(nih_strncat_dest, nih_strncat_src, 3);
	printf("Edge case: strncat with small buffer (custom): %s\n", nih_strncat_dest);

	// Edge case: strncat with small and large sizes (standard)
	char lib_strncat_dest[12] = "Hello";
	strncat(lib_strncat_dest, nih_strncat_src, 3);
	printf("Edge case: strncat with small buffer (lib): %s\n", lib_strncat_dest);

	// Edge case: nih_strchr with small and large sizes
	char nih_strchr_str[] = "Hello";
	char *nih_strchr_pos = nih_strchr(nih_strchr_str, 'l');
	printf("Edge case: nih_strchr with small buffer (custom): %s\n", nih_strchr_pos);

	// Edge case: nih_strchr with small and large sizes (standard)
	char *lib_strchr_pos = strchr(nih_strchr_str, 'l');
	printf("Edge case: nih_strchr with small buffer (lib): %s\n", lib_strchr_pos);

	// Edge case: nih_strchr with character not found
	char *nih_strchr_not_found = nih_strchr(nih_strchr_str, 'z');
	printf("Edge case: nih_strchr with character not found (custom): %s\n", nih_strchr_not_found);

	// Edge case: nih_strchr with character not found (standard)
	char *lib_strchr_not_found = strchr(nih_strchr_str, 'z');
	printf("Edge case: nih_strchr with character not found (lib): %s\n", lib_strchr_not_found);
}

void test_strings()
{
	// printf("\n");
	// printf("\n");

	// printf("test_strcat_comparison start\n");
	// printf("--------------------------------\n");
	// test_strcat_comparison();
	// printf("--------------------------------\n");
	// printf("test_strcat_comparison end\n");
	// printf("\n");
	// printf("\n");

	// printf("test_strcpy_comparison start\n");
	// printf("--------------------------------\n");
	// test_strcpy_comparison();
	// printf("--------------------------------\n");
	// printf("test_strcpy_comparison end\n");
	// printf("\n");
	// printf("\n");

	// printf("test_strlen_comparison start\n");
	// printf("--------------------------------\n");
	// test_strlen_comparison();
	// printf("--------------------------------\n");
	// printf("test_strlen_comparison end\n");
	// printf("\n");
	// printf("\n");

	// printf("test_strcmp_comparison start\n");
	// printf("--------------------------------\n");
	// test_strcmp_comparison();
	// printf("--------------------------------\n");
	// printf("test_strcmp_comparison end\n");
	// printf("\n");
	// printf("\n");

	// printf("test_strncpy_comparison start\n");
	// printf("--------------------------------\n");
	// test_strncpy_comparison();
	// printf("--------------------------------\n");
	// printf("test_strncpy_comparison end\n");
	// printf("\n");
	// printf("\n");

	// printf("test_strncat_comparison start\n");
	// printf("--------------------------------\n");
	// test_strncat_comparison();
	// printf("--------------------------------\n");
	// printf("test_strncat_comparison end\n");
	// printf("\n");
	// printf("\n");

	// printf("test_edge_cases start\n");
	// printf("--------------------------------\n");
	// test_edge_cases();
	// printf("--------------------------------\n");
	// printf("test_edge_cases end\n");
	// printf("\n");
	// printf("\n");

	// printf("test_strchr_comparison start\n");
	// printf("--------------------------------\n");
	// test_strchr_comparison();
	// printf("--------------------------------\n");
	// printf("test_strchr_comparison end\n");
	// printf("\n");
	// printf("\n");

	printf("test_strstr_comparison start\n");
	printf("--------------------------------\n");
	test_strstr_comparison();
	printf("--------------------------------\n");
	printf("test_strstr_comparison end\n");
	printf("\n");
	printf("\n");
}