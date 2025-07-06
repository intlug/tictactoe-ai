// AI fix: Moved limits to the top to handle standard includes first.
#include <limits>
#include "../include/AIPlayer.h"

std::pair<int, int> AIPlayer::getBestMove(GameBoard& board) {
    int bestScore = std::numeric_limits<int>::min();
    std::pair<int, int> bestMove = {-1, -1};
    
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            if (board.isValidMove(i, j)) {
                board.makeMove(i, j, Player::COMPUTER);
                int score = minimax(board, 0, false, std::numeric_limits<int>::min(), std::numeric_limits<int>::max());
                board.forceMove(i, j, Player::NONE);
                // AI Fix - do not call "makeMove" with Player::NONE 
                
                if (score > bestScore) {
                    bestScore = score;
                    bestMove = {i, j};
                }
            }
        }
    }
    
    return bestMove;
}

int AIPlayer::minimax(GameBoard& board, int depth, bool isMaximizing, int alpha, int beta) {
    Player winner = board.checkWinner();
    
    // Terminal cases
    if (winner == Player::COMPUTER) return 10 - depth;
    if (winner == Player::HUMAN) return depth - 10;
    if (board.isFull()) return 0;
    
    if (isMaximizing) {
        int maxEval = std::numeric_limits<int>::min();
        for (int i = 0; i < 3; i++) {
            for (int j = 0; j < 3; j++) {
                if (board.isValidMove(i, j)) {
                    board.makeMove(i, j, Player::COMPUTER);
                    int eval = minimax(board, depth + 1, false, alpha, beta);
                    board.forceMove(i, j, Player::NONE); // Undo move
                    // AI Fix - do not call "makeMove" with Player - use forceMove instead
                    maxEval = std::max(maxEval, eval);
                    alpha = std::max(alpha, eval);
                    if (beta <= alpha) break; // Alpha-beta pruning
                }
            }
            if (beta <= alpha) break;
        }
        return maxEval;
    } else {
        int minEval = std::numeric_limits<int>::max();
        for (int i = 0; i < 3; i++) {
            for (int j = 0; j < 3; j++) {
                if (board.isValidMove(i, j)) {
                    board.makeMove(i, j, Player::HUMAN);
                    int eval = minimax(board, depth + 1, true, alpha, beta);
                    board.forceMove(i, j, Player::NONE); // Undo move
                    // AI Fix - do not call "makeMove" with Player - use forceMove instead
                    minEval = std::min(minEval, eval);
                    beta = std::min(beta, eval);
                    if (beta <= alpha) break; // Alpha-beta pruning
                }
            }
            if (beta <= alpha) break;
        }
        return minEval;
    }
}

int AIPlayer::evaluateBoard(const GameBoard& board) {
    Player winner = board.checkWinner();
    if (winner == Player::COMPUTER) return 1;
    if (winner == Player::HUMAN) return -1;
    return 0;
}
