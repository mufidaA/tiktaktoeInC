#ifndef TICTACTOE_H
#define TICTACTOE_H

void displayBoard();
int checkWin(char player);
int  isBoardFull();
int minimax(char player);
void makeAIMove();
extern char board[3][3];
extern int current_player;

#endif 