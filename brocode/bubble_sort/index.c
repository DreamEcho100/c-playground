#include <stdbool.h>
#include <stdio.h>

#include "./index.h"
#include "../print_array/index.h"

void bubble_sort_int(int arr[], int size)
{
	// This is a flag to check if the array is already sorted
	bool isSorted = true;

	// Loop through the array
	for (int i = 0; i < size - 1; i++)
	{
		isSorted = true;
		// Loop through the array from 0 to (size - i - 1)
		// We minus i because the largest element is already at the end of the array from the previous iteration
		for (int j = 0; j < size - i - 1; j++)
		{
			// If the current element is greater than the next element, then the array is not sorted
			if (arr[j] > arr[j + 1])
			{

				isSorted = false;
				// Swap the elements
				int temp = arr[j];
				arr[j] = arr[j + 1];
				arr[j + 1] = temp;
			}
		}

		// If the array is already sorted, then break the loop
		if (isSorted)
		{
			break;
		}
	}
}

void bubble_sort_int_test()
{

	// Bubble Sort
	int arr[] = {64, 34, 25, 12, 22, 11, 90};
	int arr_size = sizeof(arr) / sizeof(arr[0]);

	printf("Unsorted array: \n");
	print_arr_int(arr, arr_size, "%d\n");
	printf("\n");

	bubble_sort_int(arr, arr_size);

	printf("Sorted array: \n");
	print_arr_int(arr, arr_size, "%d\n");
	printf("\n");
}