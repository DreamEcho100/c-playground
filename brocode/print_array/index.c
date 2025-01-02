#include "./index.h"
#include <stdio.h>
#include <stdlib.h>

void print_arr_int(int *arr, size_t size, char *format_str)
{
	for (size_t i = 0; i < size; i++)
	{
		printf(format_str, arr[i]);
	}
}