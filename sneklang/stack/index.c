#include <stdio.h>
#include <stdlib.h>

#include "./index.h"

stack_t *stack_new(size_t capacity)
{
	stack_t *stack = (stack_t *)malloc(sizeof(stack_t));
	if (stack == NULL)
	{
		fprintf(stderr, "Error: Couldn't allocate stack.\n");
		exit(EXIT_FAILURE);
	}

	stack->count = 0;
	stack->capacity = capacity;
	stack->data = malloc(capacity * sizeof(void *));

	if (stack->data == NULL)
	{
		free(stack);
		fprintf(stderr, "Error: Couldn't allocate stack data.\n");
		exit(EXIT_FAILURE);
	}

	return stack;
}

size_t stack_push(stack_t *stack, void *item)
{
	if (stack == NULL)
	{
		fprintf(stderr, "Error: stack is NULL.\n");
		exit(EXIT_FAILURE);
	}
	if (stack->data == NULL)
	{
		fprintf(stderr, "Error: stack->data is NULL.\n");
		exit(EXIT_FAILURE);
	}
	if (stack->count >= stack->capacity)
	{
		fprintf(stderr, "Error: stack is full.\n");
		exit(EXIT_FAILURE);
	}

	if (stack->count == stack->capacity)
	{
		size_t new_capacity = stack->capacity * 2;
		// How does `realloc` works?
		void **realloc_data = realloc(stack->data, new_capacity * sizeof(void *));
		if (realloc_data == NULL)
		{
			free(stack);
			fprintf(stderr, "Error: realloc_data is NULL.\n");
			exit(EXIT_FAILURE);
		}
		// Is the assignment here needed?
		stack->data = realloc_data;
		stack->capacity = new_capacity;
	}

	stack->data[stack->count++] = item;
	return stack->count;
}

void *stack_pop(stack_t *stack)
{
	if (stack->count == 0)
	{
		return NULL;
	}

	return stack->data[--stack->count];
}

void stack_free(stack_t *stack)
{
	if (stack == NULL || stack->data == NULL)
	{
		return;
	}

	free(stack->data); // Free the dynamically allocated data array
	free(stack);			 // Free the stack structure itself
}

void stack_remove_nulls(stack_t *stack)
{
	size_t new_count = 0;

	// Iterate through the stack and compact non-NULL pointers.
	for (size_t i = 0; i < stack->count; ++i)
	{
		if (stack->data[i] != NULL)
		{
			stack->data[new_count++] = stack->data[i];
		}
	}

	// Update the count to reflect the new number of elements.
	stack->count = new_count;

	// Optionally, you might want to zero out the remaining slots.
	for (size_t i = new_count; i < stack->capacity; ++i)
	{
		stack->data[i] = NULL;
	}
}

void stack_print(stack_t *stack, const char *format_str)
{
	if (stack == NULL)
	{
		printf("Stack is NULL.\n");
		return;
	}

	if (!format_str)
	{
		printf("Invalid format string.\n");
		return;
	}

	printf("Stack (count = %zu, capacity = %zu):\n", stack->count, stack->capacity);

	for (size_t i = 0; i < stack->count; ++i)
	{
		printf(" [%zu]: ", i);
		printf(format_str, stack->data[i]); // Print the element using the provided format
		printf("\n");
	}
}

void test_stack()
{
	// Create a stack
	stack_t *stack = stack_new(8);

	// Push some elements
	stack_push(stack, "Hello"); // strdup
	stack_push(stack, NULL);		// strdup
	stack_push(stack, "World"); // strdup
	stack_push(stack, NULL);		// strdup
	stack_push(stack, NULL);		// strdup
	stack_push(stack, NULL);		// strdup
	stack_push(stack, "!");			// strdup

	// Print the stack
	stack_print(stack, "%s");

	// Reset the stack
	printf("\nRemoving NULLs stack...\n");
	stack_remove_nulls(stack);

	// Print the stack again
	stack_print(stack, "%s");

	// Free the stack
	stack_free(stack);
}

/*
char *my_strdup(const char *str) {
		if (str == NULL) return NULL;  // Handle NULL input

		size_t len = strlen(str) + 1;  // Length of string + 1 for null terminator
		char *copy = malloc(len);      // Allocate memory

		if (copy) {
				memcpy(copy, str, len);    // Copy the string (including null terminator)
		}

		return copy;
}
*/

/*
Stack Print Flexibility
The stack_print function works great but assumes all elements are strings. If the stack is storing integers, structs, or other types, this won't work.

Suggestion: Instead of expecting the format_str, pass a function pointer for printing individual elements. This allows flexibility for any type of data.

Improved Code:

c
Copy code
void stack_print(stack_t *stack, void (*print_func)(void *))
{
		if (stack == NULL)
		{
				printf("Stack is NULL.\n");
				return;
		}

		printf("Stack (count = %zu, capacity = %zu):\n", stack->count, stack->capacity);

		for (size_t i = 0; i < stack->count; ++i)
		{
				printf(" [%zu]: ", i);
				print_func(stack->data[i]); // Use the custom print function
				printf("\n");
		}
}
You can then pass a specific printing function for your data type, e.g.:

c
Copy code
void print_string(void *data) {
		printf("%s", (char *)data);
}

void print_int(void *data) {
		printf("%d", *(int *)data);
}
*/