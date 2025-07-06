#pragma once
#include "GameBoard.h"
#include <utility>

class AIPlayer {
private:
    int minimax(GameBoard& board, int depth, bool isMaximizing, int alpha, int beta);
    int evaluateBoard(const GameBoard& board);
    
public:
    std::pair<int, int> getBestMove(GameBoard& board);
};
