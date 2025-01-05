#include <stdio.h>
#include <ctype.h>
#include <stdbool.h>
#include <time.h>
#include <stdlib.h>

#include "./index.h"

void resetBoard(tic_tac_toe_manager_t *tic_tac_toe_manager)
{
	for (int i = 0; i < tic_tac_toe_manager->row_size; ++i)
	{
		for (int j = 0; j < tic_tac_toe_manager->column_size; ++j)
		{
			tic_tac_toe_manager->moves[i][j] =
					// ((i * tic_tac_toe_manager->row_size) + j + 49);
					('1' + (i * tic_tac_toe_manager->column_size) + j); // Assign '1' to '9'
		}
	}
};

void printBoard(tic_tac_toe_manager_t *tic_tac_toe_manager)
{

	int row_char_size =
			// char + padded space around char = 3
			(3 * tic_tac_toe_manager->row_size) +
			// separators between each block/cell
			(tic_tac_toe_manager->row_size - 1);
	// char *hr = (char *)malloc(sizeof(char) * row_char_size + 2);
	char hr[row_char_size + 2];

	int i = 0;
	for (; i < row_char_size; ++i)
	{
		hr[i] = (i + 1) % 4 == 0 ? '|' : '-';
	}
	hr[i] = '\n';
	hr[++i] = '\0';

	int block_size = 4;
	int block_char_idx = (block_size - 1) / 2;

	// char *block = (char *)malloc(sizeof(char *) * row_char_size + 2);
	char block[row_char_size + 2];
	for (int i = 0; i < tic_tac_toe_manager->row_size; ++i)
	{

		int j;
		int k;
		int idx;
		for (j = 0; j < tic_tac_toe_manager->column_size; j++)
		{
			for (k = 0; k < block_size; k++)
			{
				idx = (j * block_size) + (k);
				block[idx] = ' ';
				if (k == block_size - 1)
				{
					block[idx] =
							(j == tic_tac_toe_manager->column_size - 1) ? '\n' : '|';
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
		if (i != tic_tac_toe_manager->row_size - 1)
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

		int row = selected_pos / tic_tac_toe_manager->row_size;
		int column = selected_pos % tic_tac_toe_manager->column_size;
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
			int row = pos / tic_tac_toe_manager->row_size;
			int column = pos % tic_tac_toe_manager->column_size;
			tic_tac_toe_manager->moves[row][column] = tic_tac_toe_manager->computer_move_type;
			printf("Computer (%c) moved to position (%d)\n", tic_tac_toe_manager->moves[row][column], (row * tic_tac_toe_manager->row_size) + column + 1);
			break;
		}
	}

	tic_tac_toe_manager->movements_available--;
}

// Note: in progress
bool checkActiveUserMoves(tic_tac_toe_manager_t *tic_tac_toe_manager)
{
	if (tic_tac_toe_manager->movements_available > (tic_tac_toe_manager->grid_dir_size * 1.75))
	{
		return NULL;
	}

	char move_type = tic_tac_toe_manager->active_user == USER_PLAYER ? tic_tac_toe_manager->player_move_type : tic_tac_toe_manager->computer_move_type;

	int acc = 0;

	// Check horizontal moves
	for (int r = 0; r < tic_tac_toe_manager->row_size; ++r)
	{

		acc = 0;
		for (int c = 0; c < tic_tac_toe_manager->column_size; c++)
		{
			if (tic_tac_toe_manager->moves[r][c] != move_type)
			{
				break;
			}

			acc++;
		}

		if (acc == tic_tac_toe_manager->grid_dir_size)
		{
			return true;
		}
	}

	acc = 0;
	// Check vertical moves
	for (int c = 0; c < tic_tac_toe_manager->row_size; ++c)
	{

		for (int r = 0; r < tic_tac_toe_manager->column_size; r++)
		{
			if (tic_tac_toe_manager->moves[r][c] != move_type)
			{
				break;
			}

			acc++;
		}

		if (acc == tic_tac_toe_manager->grid_dir_size)
		{
			return true;
		}
	}

	// Check diagonal moves
	acc = 0;

	if (acc == tic_tac_toe_manager->grid_dir_size)
	{
		return true;
	}

	return false;
}

// Note: in progress
void printWinner(tic_tac_toe_manager_t *tic_tac_toe_manager)
{
	printf("\n\n-- printWinner\n");
	printf("-- [tic_tac_toe_manager->winner]: (%d)", tic_tac_toe_manager->winner);

	if (tic_tac_toe_manager->winner == USER_COMPUTER)
	{
		printf("The computer is the winner!!!\n");
		return;
	}

	if (tic_tac_toe_manager->winner == USER_PLAYER)
	{
		printf("The player is the winner!!!\n");
		return;
	}

	if (tic_tac_toe_manager->movements_available == 0)
	{
		printf("Tie!!!\n");
		return;
	}

	printf("???\n");
}

void switch_active_user(tic_tac_toe_manager_t *tic_tac_toe_manager)
{
	int new_active_user = tic_tac_toe_manager->active_user == USER_PLAYER ? USER_COMPUTER : USER_PLAYER;

	tic_tac_toe_manager->active_user = new_active_user;
	printf("Now the [%d] turn\n", new_active_user);
}

void startGame()
{

	srand(time(0));

	int grid_dir_size = 3;
	tic_tac_toe_manager_t tic_tac_toe_manager = {
			.moves = {},
			.grid_dir_size = grid_dir_size,
			.movements_available = grid_dir_size * grid_dir_size,
			.movements_total = grid_dir_size * grid_dir_size,
			.row_size = grid_dir_size,
			.column_size = grid_dir_size,

			// .computer_move_type = NULL,
			// .player_move_type = NULL,
			.winner = USER_UNDECIDED};

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
			if (tic_tac_toe_manager.player_move_type == X_MOVE)
			{
				tic_tac_toe_manager.computer_move_type = O_MOVE;
				tic_tac_toe_manager.active_user = USER_PLAYER;
			}
			else
			{
				tic_tac_toe_manager.computer_move_type = X_MOVE;
				// tic_tac_toe_manager.active_user = USER_PLAYER;
				tic_tac_toe_manager.active_user = USER_COMPUTER;
			}
			break;
		}

		printf("You have entered a non valid character!\n");
	}

	printf("You chose '%c'. The computer will be '%c'.\n", tic_tac_toe_manager.player_move_type, tic_tac_toe_manager.computer_move_type);

	printBoard(&tic_tac_toe_manager);

	while (tic_tac_toe_manager.winner == USER_UNDECIDED)
	{
		if (tic_tac_toe_manager.active_user == USER_PLAYER)
		{
			playerMove(&tic_tac_toe_manager);
		}
		else
		{
			computerMove(&tic_tac_toe_manager);
		}

		printBoard(&tic_tac_toe_manager);

		if (checkActiveUserMoves(&tic_tac_toe_manager))
		{
			tic_tac_toe_manager.winner = tic_tac_toe_manager.active_user;
			break;
		}

		switch_active_user(&tic_tac_toe_manager);
	}

	printWinner(&tic_tac_toe_manager);
	printBoard(&tic_tac_toe_manager);
};
