#ifndef BRO_CODE_TIC_TAC_TOE
#define BRO_CODE_TIC_TAC_TOE

#include <stdbool.h>

#define X_MOVE 'X'
#define O_MOVE 'O'

typedef struct TicTacToeManager
{
	char moves[3][3];
	int movements_available;
	int movements_total;
	int movements_row;
	int movements_column;

	char computer_move_type;
	char player_move_type;
} tic_tac_toe_manager_t;

void resetBoard(tic_tac_toe_manager_t *tic_tac_toe_manager);
void printBoard(tic_tac_toe_manager_t *tic_tac_toe_manager);
bool checkIsSpaceFree(char moves[3][3], int targetPos);
void playerMove(tic_tac_toe_manager_t *tic_tac_toe_manager);
void computerMove(tic_tac_toe_manager_t *tic_tac_toe_manager);
char checkWinner();
void printWinner();
void startGame();

#endif // BRO_CODE_TIC_TAC_TOE