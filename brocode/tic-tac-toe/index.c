#include <stdio.h>
#include <ctype.h>
#include <stdbool.h>
#include <time.h>
#include <string.h>
#include <stdlib.h>

#include "./index.h"

void resetBoard(tic_tac_toe_manager_t *tic_tac_toe_manager)
{
	for (int i = 0; i < tic_tac_toe_manager->movements_row; ++i)
	{
		for (int j = 0; j < tic_tac_toe_manager->movements_column; ++j)
		{
			tic_tac_toe_manager->moves[i][j] =
					// ((i * tic_tac_toe_manager->movements_row) + j + 49);
					('1' + (i * tic_tac_toe_manager->movements_column) + j); // Assign '1' to '9'
		}
	}
};

void printBoard(tic_tac_toe_manager_t *tic_tac_toe_manager)
{

	int row_char_size = (3 * tic_tac_toe_manager->movements_row) + (tic_tac_toe_manager->movements_row - 1);
	// char *hr = (char *)malloc(sizeof(char) * row_char_size + 2);
	char hr[row_char_size + 2];

	int i = 0;
	for (; i < row_char_size; i++)
	{
		hr[i] = (i + 1) % 4 == 0 ? '|' : '-';
	}
	hr[i] = '\n';
	hr[++i] = '\0';

	int block_size = 4;
	int block_char_idx = (block_size - 1) / 2;

	// char *block = (char *)malloc(sizeof(char *) * row_char_size + 2);
	char block[row_char_size + 2];
	for (int i = 0; i < tic_tac_toe_manager->movements_row; ++i)
	{

		int j;
		int k;
		int idx;
		for (j = 0; j < tic_tac_toe_manager->movements_column; j++)
		{
			for (k = 0; k < block_size; k++)
			{
				idx = (j * block_size) + (k);
				block[idx] = ' ';
				if (k == block_size - 1)
				{
					block[idx] =
							(j == tic_tac_toe_manager->movements_column - 1) ? '\n' : '|';
				}
				else if (k == block_char_idx)
				{
					block[idx] = tic_tac_toe_manager->moves[i][j];
				}
				else
				{
					block[idx] = ' ';
				}
			}
		}
		block[++idx] = '\0';

		printf("%s", block);
		// // printf(" %c | %c | %c \n", tic_tac_toe_manager->moves[i][0], tic_tac_toe_manager->moves[i][1], tic_tac_toe_manager->moves[i][2]);
		if (i != tic_tac_toe_manager->movements_row - 1)
		{
			printf("%s", hr);
		}
	}

	// free(block);
	// free(hr);
};

bool checkIsSpaceFree(char moves[3][3], int targetPos)
{
	int row = targetPos / 3;
	int col = targetPos % 3;
	return moves[row][col] != X_MOVE && moves[row][col] != O_MOVE;
}

void playerMove(tic_tac_toe_manager_t *tic_tac_toe_manager)
{
	int selected_pos;
	while (true)
	{
		printf("Please select from the available free position\n");
		scanf(" %d", &selected_pos);
		while (getchar() != '\n')
			;

		if (selected_pos < 0 || selected_pos > tic_tac_toe_manager->movements_total)
		{
			printf("Invalid position, please try again\n");
			continue;
		}

		selected_pos--;
		if (!checkIsSpaceFree(tic_tac_toe_manager->moves, selected_pos))
		{
			printf("Occupied position, please try again\n");
			continue;
		}

		int row = selected_pos / tic_tac_toe_manager->movements_row;
		int column = selected_pos % tic_tac_toe_manager->movements_column;
		tic_tac_toe_manager->moves[row][column] = tic_tac_toe_manager->player_move_type;
		break;
	}

	tic_tac_toe_manager->movements_available--;
};

void computerMove(tic_tac_toe_manager_t *tic_tac_toe_manager)
{

	while (true)
	{
		int pos = rand() % tic_tac_toe_manager->movements_total;

		if (checkIsSpaceFree(tic_tac_toe_manager->moves, pos))
		{
			int row = pos / tic_tac_toe_manager->movements_row;
			int column = pos % tic_tac_toe_manager->movements_column;
			tic_tac_toe_manager->moves[row][column] = tic_tac_toe_manager->computer_move_type;
			printf("Computer (%c) moved to position (%d)\n", tic_tac_toe_manager->moves[row][column], (row * tic_tac_toe_manager->movements_row) + column + 1);
			break;
		}
	}

	tic_tac_toe_manager->movements_available--;
}

// Note: in progress
char checkWinner();

// Note: in progress
void printWinner();

void startGame()
{

	srand(time(0));
	tic_tac_toe_manager_t tic_tac_toe_manager = {
			.moves = {},
			.movements_available = 9,
			.movements_total = 9,
			.movements_row = 3,
			.movements_column = 3,

			.computer_move_type = ' ',
			.player_move_type = ' ',
	};

	resetBoard(&tic_tac_toe_manager);

	while (true)
	{

		printf("Select your role (\"X\" or \"O\"): \n");
		scanf(" %c", &tic_tac_toe_manager.player_move_type);
		while (getchar() != '\n')
			;
		tic_tac_toe_manager.player_move_type = toupper(tic_tac_toe_manager.player_move_type);

		if (tic_tac_toe_manager.player_move_type == X_MOVE || tic_tac_toe_manager.player_move_type == O_MOVE)
		{
			tic_tac_toe_manager.computer_move_type = (char)(tic_tac_toe_manager.player_move_type == O_MOVE ? X_MOVE : O_MOVE);
			break;
		}

		printf("You have entered a non valid character!\n");
	}

	printf("You chose '%c'. The computer will be '%c'.\n", tic_tac_toe_manager.player_move_type, tic_tac_toe_manager.computer_move_type);

	printBoard(&tic_tac_toe_manager);

	computerMove(&tic_tac_toe_manager);
	printBoard(&tic_tac_toe_manager);
	// printBoard(&tic_tac_toe_manager);
	playerMove(&tic_tac_toe_manager);
	printBoard(&tic_tac_toe_manager);
};
