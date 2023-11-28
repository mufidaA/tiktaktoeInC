#include "tictactoe.h"
#include <stdio.h>

char board[3][3] = {{' ', ' ', ' '}, {' ', ' ', ' '}, {' ', ' ', ' '}};

// Function to display the Tic-Tac-Toe board
void displayBoard() {
    printf(" %c | %c | %c \n", board[0][0], board[0][1], board[0][2]);
    printf("-----------\n");
    printf(" %c | %c | %c \n", board[1][0], board[1][1], board[1][2]);
    printf("-----------\n");
    printf(" %c | %c | %c \n", board[2][0], board[2][1], board[2][2]);
}

// Function to check if a player has won
int checkWin(char player) {
    // Check rows, columns, and diagonals
    for (int i = 0; i < 3; i++) {
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
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            if (board[i][j] == ' ') {
                return 0; // Board is not full
            }
        }
    }
    return 1; // Board is full
}

// Function to implement the AI using a simple minimax algorithm
int minimax(char player) {
    // Base cases: check for terminal states (win, lose, draw)
    if (checkWin('X')) return -1; // AI loses
    if (checkWin('O')) return 1;  // AI wins
    if (isBoardFull()) return 0;   // It's a draw

    int bestScore;
    
    if (player == 'O') {
        // Maximizing player (AI)
        bestScore = -1000;  // Initialize to a very small value

        // Check all empty positions on the board
        for (int i = 0; i < 3; i++) {
            for (int j = 0; j < 3; j++) {
                if (board[i][j] == ' ') {
                    // Try this move for the maximizing player
                    board[i][j] = 'O';
                    int score = minimax('X');  // Switch to the minimizing player

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
        // Minimizing player (opponent)
        bestScore = 1000;  
        for (int i = 0; i < 3; i++) {
            for (int j = 0; j < 3; j++) {
                if (board[i][j] == ' ') {
                  
                    board[i][j] = 'X';
                    int score = minimax('O');  
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
void makeAIMove() {
    int bestScore = -1000;  // Initialize to a very small value
    int bestMove[2] = {-1, -1};  // Initialize to an invalid move

    // Check all empty positions on the board
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            if (board[i][j] == ' ') {
                // Try this move for the maximizing player (AI)
                board[i][j] = 'O';
                int score = minimax('X');  // Switch to the minimizing player

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
    board[bestMove[0]][bestMove[1]] = 'O';
}

