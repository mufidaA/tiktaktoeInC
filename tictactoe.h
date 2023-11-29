#ifndef TICTACTOE_H
#define TICTACTOE_H

void displayBoard();
void initializeBoard();
int checkWin(char player);
int  isBoardFull();
int minimax(char currentPlayer, char player, char aiplayer);
void makeAIMove(char player, char aiplayer, int* o_row, int* o_col);
extern char board[3][3];
extern int currentPlayer;
extern const int boardSize;

#endif 