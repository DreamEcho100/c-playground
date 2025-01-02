#include <stdio.h>
#include "./arrays_utils.h"

#define BOOT_DOT_DEV_TEST_ARR_CREATION_AND_ACCESS_SIZE 5

void test_arr_creation_and_access()
{
	printf("Hello, World!\n");

	// static const int arr_size = 5;
	// 10, 20, 30, 40, 50
	int arr[BOOT_DOT_DEV_TEST_ARR_CREATION_AND_ACCESS_SIZE] = {10, 20, 30, 40, 50};
	// {};
	// arr[0] = 10;
	// arr[1] = 20;
	// arr[2] = 30;
	// arr[3] = 40;
	// arr[4] = 50;

	printf("\n");

	printf("arr: %p\n", arr);
	printf("Testing the array, its address and its elements, using arr[]:\n");
	for (int i = 0; i < BOOT_DOT_DEV_TEST_ARR_CREATION_AND_ACCESS_SIZE; ++i)
	{
		printf("%p: %d\n", &arr[i], arr[i]);
	}

	printf("\n");

	// arr_ptr points to the first element of arr
	// arr decays to int* (pointer to the first element)
	int *arr_ptr = arr;
	printf("arr_ptr: %p\n", arr_ptr);

	for (int i = 0; i < BOOT_DOT_DEV_TEST_ARR_CREATION_AND_ACCESS_SIZE; ++i)
	{
		// `arr_ptr + i` is the address of the i-th element of arr
		// `*(arr_ptr + i)` is the value of the i-th element of arr
		printf("%p: %d\n", arr_ptr + i, *(arr_ptr + i));
	}
}

// int main()
// {
// 	test_arr_creation_and_access();
// 	printf("\n");

// 	return 0;
// }