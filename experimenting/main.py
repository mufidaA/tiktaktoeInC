import random
from board import print_board, is_winner, is_board_full, get_empty_cells
from ai_player import ai_move
from user_player import player_move

def main():
    board = [[' ' for _ in range(3)] for _ in range(3)]
    players = ['X', 'O']
    human_player = random.choice(players)
    ai_player = 'X' if human_player == 'O' else 'O'

    while True:
        print_board(board)

        if human_player == 'X':
            row, col = player_move(board)
        else:
            print("AI is making a move...")
            row, col = ai_move(board, ai_player, human_player)

        board[row][col] = human_player

        if is_winner(board, human_player):
            print_board(board)
            print(f"{human_player} wins!")
            break
        elif is_board_full(board):
            print_board(board)
            print("It's a tie!")
            break

        print_board(board)

        if ai_player == 'X':
            row, col = player_move(board)
        else:
            print("AI is making a move...")
            row, col = ai_move(board, ai_player, human_player)

        board[row][col] = ai_player

        if is_winner(board, ai_player):
            print_board(board)
            print(f"{ai_player} wins!")
            break
        elif is_board_full(board):
            print_board(board)
            print("It's a tie!")
            break

if __name__ == "__main__":
    main()
