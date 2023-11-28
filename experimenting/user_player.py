# user_player.py
def player_move(board):
    while True:
        try:
            move = input("Enter row and column (separated by space): ")
            row, col = map(int, move.split())
            if board[row][col] == ' ':
                return row, col
            else:
                print("Cell already taken. Try again.")
        except (ValueError, IndexError):
            print("Invalid input. Try again.")
