import random
from board import *

def ai_move(board, ai_symbol, player_symbol):
    best_score = float('-inf')
    best_move = None
    alpha = float('-inf')
    beta = float('inf')

    for row, col in get_empty_cells(board):
        board[row][col] = ai_symbol
        score = minimax(board, 0, False, ai_symbol, player_symbol, alpha, beta)
        board[row][col] = ' '

        if score > best_score:
            best_score = score
            best_move = (row, col)

        alpha = max(alpha, best_score)

    return best_move

def minimax(board, depth, maximizing_player, ai_symbol, player_symbol, alpha, beta):
    if is_winner(board, ai_symbol):
        return 1
    elif is_winner(board, player_symbol):
        return -1
    elif is_board_full(board):
        return 0

    if maximizing_player:
        max_eval = float('-inf')
        for row, col in get_empty_cells(board):
            board[row][col] = ai_symbol
            eval = minimax(board, depth + 1, False, ai_symbol, player_symbol, alpha, beta)
            board[row][col] = ' '
            max_eval = max(max_eval, eval)
            alpha = max(alpha, eval)
            if beta <= alpha:
                break
        return max_eval
    else:
        min_eval = float('inf')
        for row, col in get_empty_cells(board):
            board[row][col] = player_symbol
            eval = minimax(board, depth + 1, True, ai_symbol, player_symbol, alpha, beta)
            board[row][col] = ' '
            min_eval = min(min_eval, eval)
            beta = min(beta, eval)
            if beta <= alpha:
                break
        return min_eval
