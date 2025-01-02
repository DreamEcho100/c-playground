
#include <stddef.h>

#ifndef BOOT_DOT_DEV_TEXT_BUFFER_INDEX_H
#define BOOT_DOT_DEV_TEXT_BUFFER_INDEX_H

#define BOOT_DOT_DEV_TEXT_BUFFER_MAX_BUFFER 64

typedef struct
{
	size_t length;
	char buffer[64];
} TextBuffer;

int smart_append(TextBuffer *dest, const char *src);
void test_smart_append();
#endif // BOOT_DOT_DEV_TEXT_BUFFER_INDEX_H