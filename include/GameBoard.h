#pragma once
#include <array>

enum class Player {
    NONE,
    HUMAN,
    COMPUTER
};

class GameBoard {
private:
    std::array<std::array<Player, 3>, 3> board;
    
public:
    GameBoard();
    void reset();
    bool makeMove(int row, int col, Player player);
    Player getCell(int row, int col) const;
    bool isFull() const;
    Player checkWinner() const;
    bool isValidMove(int row, int col) const;
    void printBoard() const; // For debugging
};
