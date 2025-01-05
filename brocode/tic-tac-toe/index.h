#ifndef BRO_CODE_TIC_TAC_TOE
#define BRO_CODE_TIC_TAC_TOE

#include <stdbool.h>

#define X_MOVE 'X'
#define O_MOVE 'O'

typedef enum USER
{
	USER_UNDECIDED,
	USER_COMPUTER,
	USER_PLAYER,
} user_e;
// #define USER_PLAYER "USER_PLAYER"
// #define USER_COMPUTER "USER_COMPUTER"
// #define USER_UNDECIDED "USER_UNDECIDED"

typedef struct TicTacToeManager
{
	int grid_dir_size;
	char moves[3][3];
	int movements_available;
	int movements_total;
	int row_size;
	int column_size;

	char computer_move_type;
	char player_move_type;

	int active_user;
	int winner;
} tic_tac_toe_manager_t;

void resetBoard(tic_tac_toe_manager_t *tic_tac_toe_manager);
void printBoard(tic_tac_toe_manager_t *tic_tac_toe_manager);
bool checkIsSpaceFree(char moves[3][3], int targetPos);
void playerMove(tic_tac_toe_manager_t *tic_tac_toe_manager);
void computerMove(tic_tac_toe_manager_t *tic_tac_toe_manager);
bool checkActiveUserMoves(tic_tac_toe_manager_t *tic_tac_toe_manager);
void printWinner(tic_tac_toe_manager_t *tic_tac_toe_manager);
void switch_active_user(tic_tac_toe_manager_t *tic_tac_toe_manager);
void startGame();

#endif // BRO_CODE_TIC_TAC_TOE