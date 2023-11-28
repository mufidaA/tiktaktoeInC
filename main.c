#include "tictactoe.h"
#include <stdio.h>


int main() {
    int currentPlayer = 1; // 1 for the player, 2 for the AI
    int row, col;

    do {
        // Display the current state of the board
        displayBoard();

        // Get the move from the current player
        if (currentPlayer == 1) {
            printf("Player's turn (Enter row and column): ");
            scanf("%d %d", &row, &col);
            // Adjust to 0-based index
            row--;
            col--;
            // Check if the move is valid
            if (row < 0 || row >= 3 || col < 0 || col >= 3 || board[row][col] != ' ') {
                printf("Invalid move. Try again.\n");
                continue;
            }
            // Make the player's move
            board[row][col] = 'X';
        } else {
            // AI's turn
            printf("AI's turn:\n");
            makeAIMove();
        }

        if (checkWin(currentPlayer == 1 ? 'X' : 'O')) {
            displayBoard();
            printf("Player %d wins!\n", currentPlayer);
            break;
        } else if (isBoardFull()) {
            displayBoard();
            printf("It's a draw!\n");
            break;
        }

        // Switch to the other player
        currentPlayer = 3 - currentPlayer;

    } while (1);
    return 0;
}