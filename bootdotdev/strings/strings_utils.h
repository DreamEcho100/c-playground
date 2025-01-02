#ifndef BOOT_DOT_DEV_STRINGS_UTILS_H
#define BOOT_DOT_DEV_STRINGS_UTILS_H

/**
 *
 * nih_strcat: Concatenates (appends) one string to another.
 *
 * ```c
 * 	char dest[12] = "Hello";
 * 	char src[] = " World";
 * 	nih_strcat(dest, src);
 * 	// dest now contains "Hello World"
 * ```
 */
void nih_strcat(char *str1, const char *str2);
void nih_strcat_2(char *str1, const char *str2);

/**
 *
 * nih_strcpy: Copies a string to another.
 *
 * **Example:**
 * ```c
 * 	char src[] = "Hello";
 * 	char dest[6];
 * 	nih_strcpy(dest, src);
 * 	// dest now contains "Hello"
 * ```
 *
 * **Notes:**
 * - The destination string must be large enough to hold the source string.
 */
void nih_strcpy(char *dest, const char *src, size_t n);

/**
 * nih_strlen: Returns the length of a string (excluding the null terminator).
 *
 * **Example:**
 * ```c
 * 	char str[] = "Hello";
 * 	size_t len = nih_strlen(str);
 * 	// len is 5
 * ```
 *
 * **Notes:** The string must be null-terminated.
 */
size_t nih_strlen(const char *str);

/**
 * nih_strcmp: Compares two strings lexicographically.
 *
 * **Examples:**
 *
 * ```c
 * 	char str1[] = "Hello";
 * 	char str2[] = "World";
 * 	int result = nih_strcmp(str1, str2);
 * 	// result is negative since "Hello" < "World"
 * ```
 *
 * ```c
 * 	char str1[] = "Hello";
 * 	char str2[] = "Hello";
 * 	int result = nih_strcmp(str1, str2);
 * 	// result is 0 since "Hello" == "Hello"
 * ```
 *
 * ```c
 * 	char str1[] = "World";
 * 	char str2[] = "Warld";
 * 	int result = nih_strcmp(str1, str2);
 * 	// result is negative since "World" < "Warld"
 * ```
 *
 * **Notes:**
 * - The strings must be null-terminated.
 * - The return value is negative if the first string is less than the second, positive if the first string is greater than the second, and 0 if the strings are equal.
 * - The comparison is case-sensitive.
 * - The comparison is based on the ASCII values of the characters.
 * - The comparison stops when a null terminator is reached in either string.
 * - The comparison is done character by character.
 * - The comparison is done lexicographically _(which means it is done in dictionary order)_.
 * - The comparison is done from left to right.
 * - The comparison is done in a single traversal.
 */
int nih_strcmp(const char *str1, const char *str2);

/**
 * nih_strncpy: Copies a specified number of characters from one string to another.
 *
 * **Example:**
 * ```c
 * 	char src[] = "Hello";
 * 	char dest[6];
 * 	nih_strncpy(dest, src, 3);
 * 	// dest now contains "Hel"
 * 	dest[3] = '\0';
 * 	// ensure null termination
 * ```
 *
 * **Notes:**
 * - The destination string must be large enough to hold the source string.
 * - The number of characters to copy must be specified.
 * - The source string must be null-terminated.
 * - The destination string will be null-terminated.
 * - The null terminator is included in the count of characters to copy.
 * - If the source string is shorter than the specified number of characters, the destination string will be padded with null characters.
 */
void nih_strncpy(char *dest, size_t dest_size, const char *src, size_t size_limit);

/**
 * nih_strncat: Concatenates a specified number of characters from one string to another.
 *
 * **Example:**
 * ```c
 * 	char dest[12] = "Hello";
 * 	char src[] = " World";
 * 	nih_strncat(dest, src, 3);
 * 	// dest now contains "Hello Wo"
 * ```
 *
 * **Notes:**
 * - The destination string must be large enough to hold the source string.
 * - The number of characters to concatenate must be specified.
 * - The source string must be null-terminated.
 * - The destination string will be null-terminated.
 * - The null terminator is included in the count of characters to concatenate.
 */
void nih_strncat(char *dest, const char *src, size_t size_limit);

/**
 * nih_strchr: Finds the first occurrence of a character in a string.
 *
 * **Example:**
 * ```c
 * 	char str[] = "Hello";
 * 	char *pos = nih_strchr(str, 'l');
 * 	// pos points to the first 'l' in "Hello"
 * ```
 *
 * **Notes:**
 * - Returns a pointer to the first occurrence of the character in the string.
 * - Returns NULL if the character is not found.
 * - The string must be null-terminated.
 * - The character to find must be specified.
 * - The search is case-sensitive.
 * - The search stops when the character is found or the null terminator is reached.
 * - The search is done from left to right.
 * - The search is done in a single traversal.
 * - The search is done character by character.
 * - If the character to find is the null terminator ('\0'), a pointer to the end of the string is returned.
 * - If the input string is a const string, the function casts away the const qualifier when returning the pointer.
 * - Care should be taken to avoid modifying the string through the returned pointer if the input string is const.
 */
char *nih_strchr(const char *str, int desired_char);

/**
 * nih_strstr: Finds the first occurrence of a substring in a string.
 *
 * **Example:**
 * ```c
 * 	char str[] = "Hello World";
 * 	char *pos = nih_strstr(str, "World");
 * 	// pos points to "World" in "Hello World"
 * ```
 *
 * **Notes:**
 * - Returns a pointer to the first occurrence of the substring in the string.
 * - Returns NULL if the substring is not found.
 * - The string and substring must be null-terminated.
 * - The search is case-sensitive.
 * - The search stops when the substring is found or the null terminator is reached.
 * - The search is done from left to right.
 * - The search is done in a single traversal.
 * - The search is done character by character.
 * - If the substring is empty, the input string is returned.
 * - If the input string is a const string, the function casts away the const qualifier when returning the pointer.
 * - Care should be taken to avoid modifying the string through the returned pointer if the input string is const.
 */
char *nih_strstr(const char *str, const char *substr);

void test_strcat_comparison();
void test_strcpy_comparison();
void test_strlen_comparison();
void test_strcmp_comparison();
void test_strcmp_comparison();
void test_strncpy_comparison();
void test_strncat_comparison();
void test_strchr_comparison();
void test_strstr_comparison();
void test_edge_cases();

void test_strings();

/*

nih_strstr: Finds the first occurrence of a substring in a string.
char str[] = "Hello World";
char *pos = strstr(str, "World");
// pos points to "World" in "Hello World"





*/

#endif // BOOT_DOT_DEV_STRING_UTILS_H