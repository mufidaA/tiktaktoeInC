#include "tictactoe.h"
#include <stdio.h>

char board[3][3] = {{' ', ' ', ' '}, {' ', ' ', ' '}, {' ', ' ', ' '}};
int currentPlayer = 1;
const int boardSize = 3;

void initializeBoard() {
    for (int i = 0; i < boardSize; ++i) {
        for (int j = 0; j < boardSize; ++j) {
            board[i][j] = ' ';
        }
    }
}
// Function to check if a player has won
int checkWin(char player) {
    // Check rows, columns, and diagonals
    for (int i = 0; i < boardSize; i++) {
        if ((board[i][0] == player && board[i][1] == player && board[i][2] == player) ||
            (board[0][i] == player && board[1][i] == player && board[2][i] == player)) {
            return 1; // Player has won
        }
    }

    // Check diagonals
    if ((board[0][0] == player && board[1][1] == player && board[2][2] == player) ||
        (board[0][2] == player && board[1][1] == player && board[2][0] == player)) {
        return 1; // Player has won
    }

    return 0; // No winner yet
}

// Function to check if the board is full
int isBoardFull() {
    for (int i = 0; i < boardSize; i++) {
        for (int j = 0; j < boardSize; j++) {
            if (board[i][j] == ' ') {
                return 0; // Board is not full
            }
        }
    }
    return 1; // Board is full
}

// Function to implement the AI using a simple minimax algorithm
int minimax(char currentPlayer, char player, char aiplayer) {
    // Base cases: check for terminal states (win, lose, draw)
    if (checkWin(player)) return -1; // AI loses
    if (checkWin(aiplayer)) return 1;  // AI wins
    if (isBoardFull()) return 0;   // It's a draw

    int bestScore;
    
    if (currentPlayer == aiplayer) {
        // Maximizing player (AI)
        bestScore = -1000;  // Initialize to a very small value

        // Check all empty positions on the board
        for (int i = 0; i < boardSize; i++) {
            for (int j = 0; j < boardSize; j++) {
                if (board[i][j] == ' ') {
                    // Try this move for the maximizing player
                    board[i][j] = aiplayer;
                    int score = minimax(player, player, aiplayer);  // Switch to the minimizing player

                    // Undo the move
                    board[i][j] = ' ';

                    // Update the best score
                    if (score > bestScore) {
                        bestScore = score;
                    }
                }
            }
        }
    } else {
       
        bestScore = 1000;  
        for (int i = 0; i < boardSize; i++) {
            for (int j = 0; j < boardSize; j++) {
                if (board[i][j] == ' ') {
                  
                    board[i][j] = player;
                    int score = minimax(aiplayer, player, aiplayer);  
                    // Undo the move
                    board[i][j] = ' ';

                    
                    if (score < bestScore) {
                        bestScore = score;
                    }
                }
            }
        }
    }

    return bestScore;
}

// Function to make a move for the AI
void makeAIMove(char player, char aiplayer, int* o_row, int* o_col) {
    int bestScore = -1000;  // Initialize to a very small value
    int bestMove[2] = {-1, -1};  // Initialize to an invalid move

    // Check all empty positions on the board
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            if (board[i][j] == ' ') {
                // Try this move for the maximizing player (AI)
                board[i][j] = aiplayer;
                int score = minimax(player, player, aiplayer);  // Switch to the minimizing player

                // Undo the move
                board[i][j] = ' ';

                // Update the best move if the current score is better
                if (score > bestScore) {
                    bestScore = score;
                    bestMove[0] = i;
                    bestMove[1] = j;
                }
            }
        }
    }

    // Make the best move for the AI
    board[bestMove[0]][bestMove[1]] = aiplayer;
    *o_row = bestMove[0];
    *o_col = bestMove[1];
}

