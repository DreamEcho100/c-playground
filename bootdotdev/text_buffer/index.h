
#include <stddef.h>

#ifndef TEXT_BUFFER_INDEX_H
#define TEXT_BUFFER_INDEX_H

#define TEXT_BUFFER_MAX_BUFFER 64

typedef struct
{
	size_t length;
	char buffer[64];
} TextBuffer;

int smart_append(TextBuffer *dest, const char *src);
void test_smart_append();
#endif // TEXT_BUFFER_INDEX_H