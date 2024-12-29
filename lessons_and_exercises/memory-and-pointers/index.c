#include <stdio.h>

/** Basic Pointer Operations */
void exercise_basic_pointer_operations()
{
	// Declares an integer variable.
	int secret_num = 69420;

	// Declares a pointer to the variable.
	int *secret_num_ptr = &secret_num;

	// Prints the address and value using the pointer.
	printf("The secret num pointer address is: (%p)\n", secret_num_ptr);
	printf("The secret num pointer value is: (%i)\n", *secret_num_ptr);
}

/** Allocating and Freeing Memory */
void exercise_allocating_and_freeing_memory()
{

	size_t arr_size = 10;
	// Allocates memory for an array of 10 integers using malloc.
	int *arr = (int *)malloc(arr_size * sizeof(int));

	if (arr == NULL)
	{
		fprintf(stderr, "Memory allocation failed!\n");
		exit(1);
	}

	// Fills the array with the squares of the index (0, 1, 4, 9, ...).
	for (size_t i = 0; i < arr_size; ++i)
	{
		arr[i] = pow(i, i);
	}

	// Prints the values.

	// Fills the array with the squares of the index (0, 1, 4, 9, ...).
	for (size_t i = 0; i < arr_size; ++i)
	{
		printf("arr[%zu]: %d\n", i, arr[i]);
	}

	// Frees the memory.
	free(arr);
}

/** Accepts a pointer-to-pointer to an integer. */
void allocate_int(int **ptr_to_ptr, int value)
{

	// Allocates memory for an integer on the heap.
	int *heap_memory = (int *)malloc(sizeof(int));
	if (heap_memory == NULL)
	{
		fprintf(stderr, "Memory allocation failed!\n");
		exit(1);
	}

	// Sets the integer to a value passed in as a parameter.
	*heap_memory = value;

	// Update the pointer that pointer_to_pointer is pointing to.
	*ptr_to_ptr = heap_memory;
}

void allocate_double(double **ptr_to_ptr, double value)
{
	double *heap_memory = (double *)malloc(sizeof(double));
	if (heap_memory == NULL)
	{
		fprintf(stderr, "Memory allocation failed!\n");
		exit(1);
	}

	*heap_memory = value;

	*ptr_to_ptr = heap_memory;
}

/** Pointer-to-Pointer */
void exercise_pointer_to_pointer()
{
	// Declaring an integer pointer.
	int *int_num_ptr = NULL;
	// Passing its address to allocate_int.
	allocate_int(&int_num_ptr, 420);
	// Printing the value.
	printf("Value allocated on the heap: %i\n", *int_num_ptr);
	free(int_num_ptr);

	double *double_num_ptr = NULL;
	allocate_double(&double_num_ptr, 6942069420694206);
	printf("Value allocated on the heap: %lf\n", *double_num_ptr);
	free(double_num_ptr);
}

/*
The secret num pointer address is: (0x7fffffffda3c)
The secret num pointer value is: (69420)
arr[0]: 1
arr[1]: 1
arr[2]: 4
arr[3]: 27
arr[4]: 256
arr[5]: 3125
arr[6]: 46656
arr[7]: 823543
arr[8]: 16777216
arr[9]: 387420489
Value allocated on the heap: 420
Value allocated on the heap: 6942069420694206.000000
*/