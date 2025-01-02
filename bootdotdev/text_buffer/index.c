#include <stdio.h>
#include <string.h>

#include "./index.h"

int smart_append(TextBuffer *dest, const char *src)
{
	// If the destination or source strings are NULL
	if (dest == NULL || src == NULL)
	{
		// Return an error code
		return 1;
	}

	size_t src_len = strlen(src);
	size_t remaining_space = BOOT_DOT_DEV_TEXT_BUFFER_MAX_BUFFER - dest->length - 1; // Account for the null terminator

	// If the source string is larger than the remaining space in the buffer
	if (src_len > remaining_space)
	{
		// Append as much of the source as possible
		strncat(dest->buffer, src, remaining_space);

		// Ensure the buffer is null-terminated
		dest->buffer[BOOT_DOT_DEV_TEXT_BUFFER_MAX_BUFFER - 1] = '\0';

		// Update the length to the max size
		dest->length = BOOT_DOT_DEV_TEXT_BUFFER_MAX_BUFFER - 1;

		return 1; // Return an error code (not enough space for full append)
	}

	// Otherwise, append the full source string
	strcat(dest->buffer, src);

	// Update the length
	dest->length += src_len;

	return 0; // Return a success code
}

void test_smart_append()
{
	TextBuffer buffer = {0, ""};
	smart_append(&buffer, "Hello");
	smart_append(&buffer, " World");
	printf("Buffer: %s\n", buffer.buffer);
	printf("Length: %zu\n", buffer.length);
}