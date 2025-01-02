
#ifndef BOOT_DOT_DEV_STACK_UTILS_H
#define BOOT_DOT_DEV_STACK_UTILS_H
#include <stdlib.h>

typedef struct Stack
{
	size_t count;
	size_t capacity;
	void **data;
} stack_t;

stack_t *stack_new(size_t capacity);

size_t stack_push(stack_t *stack, void *item);

/**
 *
 * ```c
 * void *data = stack_pop(stack);
 * // Use the data...
 * free(data);  // Free the memory when it's no longer needed
 * ```
 */
void *stack_pop(stack_t *stack);

void stack_free(stack_t *stack);

void stack_remove_nulls(stack_t *stack);

void stack_print(stack_t *stack, const char *format_str);

void test_stack();

#endif // BOOT_DOT_DEV_STACK_UTILS_H