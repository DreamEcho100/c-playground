#include <stdio.h>

#include "./bubble-sort/index.h"

int main()
{
	printf("Hello World!");

	// Bubble Sort
	int arr[] = {64, 34, 25, 12, 22, 11, 90};
	int n = sizeof(arr) / sizeof(arr[0]);

	printf("Unsorted array: \n");

	for (int i = 0; i < n; i++)
	{
		printf("%d ", arr[i]);
	}

	bubble_sort_int(arr, n);
	printf("Sorted array: \n");

	for (int i = 0; i < n; i++)
	{
		printf("%d ", arr[i]);
	}

	return 0;
}