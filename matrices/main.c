#include <stdio.h>
#include <stdlib.h>

int main()
{
	int print_matrix_2d_1_r = 3;
	int print_matrix_2d_1_c = 3;
	int print_matrix_2d_1[3][3] = {
			{1, 2, 3},
			{4, 5, 6},
			{7, 8, 9},
	};

	printf("Test `print_matrix`\n");
	for (int r = 0; r < print_matrix_2d_1_r; r++)
	{
		for (int c = 0; c < print_matrix_2d_1_c; c++)
		{
			printf("%d", print_matrix_2d_1[r][c]);

			if (c != print_matrix_2d_1_c - 1)
			{
				printf(" ");
			}
		}
		// if (r != print_matrix_2d_1_r - 1)
		// {
		// 	printf("\n");
		// }
		printf("\n");
	}
	printf("\n");

	int sum_matrix_2d_1[3][3] = {
			{1, 1, 1},
			{1, 1, 1},
			{1, 1, 1},
	};
	int sum_matrix_2d_2[3][3] = {
			{2, 2, 2},
			{2, 2, 2},
			{2, 2, 2},
	};

	int sum_matrix_2d_3_r = 3;
	int sum_matrix_2d_3_c = 3;
	int sum_matrix_2d_3[3][3] = {{0}};

	printf("Test `sum_matrix`\n");
	for (int r = 0; r < sum_matrix_2d_3_r; r++)
	{
		for (int c = 0; c < sum_matrix_2d_3_c; c++)
		{
			sum_matrix_2d_3[r][c] = sum_matrix_2d_1[r][c] + sum_matrix_2d_2[r][c];
			printf("%d", sum_matrix_2d_3[r][c]);

			if (c != sum_matrix_2d_3_c - 1)
			{
				printf(" ");
			}
		}
		// if (r != sum_matrix_2d_3_r - 1)
		// {
		// 	printf("\n");
		// }
		printf("\n");
	}
	printf("\n");

	return 0;
}