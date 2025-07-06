#include "../include/GameBoard.h"
#include <iostream>

GameBoard::GameBoard() {
    reset();
}

void GameBoard::reset() {
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            board[i][j] = Player::NONE;
        }
    }
}

bool GameBoard::makeMove(int row, int col, Player player) {
    if (isValidMove(row, col)) {
        board[row][col] = player;
        return true;
    }
    return false;
}

Player GameBoard::getCell(int row, int col) const {
    if (row >= 0 && row < 3 && col >= 0 && col < 3) {
        return board[row][col];
    }
    return Player::NONE;
}

bool GameBoard::isFull() const {
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            if (board[i][j] == Player::NONE) {
                return false;
            }
        }
    }
    return true;
}

Player GameBoard::checkWinner() const {
    // Check rows
    for (int i = 0; i < 3; i++) {
        if (board[i][0] != Player::NONE && 
            board[i][0] == board[i][1] && 
            board[i][1] == board[i][2]) {
            return board[i][0];
        }
    }
    
    // Check columns
    for (int j = 0; j < 3; j++) {
        if (board[0][j] != Player::NONE && 
            board[0][j] == board[1][j] && 
            board[1][j] == board[2][j]) {
            return board[0][j];
        }
    }
    
    // Check diagonals
    if (board[0][0] != Player::NONE && 
        board[0][0] == board[1][1] && 
        board[1][1] == board[2][2]) {
        return board[0][0];
    }
    
    if (board[0][2] != Player::NONE && 
        board[0][2] == board[1][1] && 
        board[1][1] == board[2][0]) {
        return board[0][2];
    }
    
    return Player::NONE;
}

bool GameBoard::isValidMove(int row, int col) const {
    return row >= 0 && row < 3 && col >= 0 && col < 3 && board[row][col] == Player::NONE;
}

void GameBoard::printBoard() const {
    std::cout << "Current board state:\n";
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            char symbol = ' ';
            if (board[i][j] == Player::HUMAN) symbol = 'X';
            else if (board[i][j] == Player::COMPUTER) symbol = 'O';
            std::cout << symbol;
            if (j < 2) std::cout << "|";
        }
        std::cout << "\n";
        if (i < 2) std::cout << "-----\n";
    }
    std::cout << "\n";
}
