#pragma once
#include <gtk/gtk.h>
#include "GameBoard.h"
#include "AIPlayer.h"

class TicTacToeGame {
private:
    GtkWidget *window;
    GtkWidget *grid;
    GtkWidget *buttons[3][3];
    GtkWidget *statusLabel;
    GtkWidget *newGameButton;
    
    GameBoard gameBoard;
    AIPlayer aiPlayer;
    bool gameOver;
    Player currentPlayer;
    
    static void onButtonClicked(GtkWidget *widget, gpointer data);
    static void onNewGameClicked(GtkWidget *widget, gpointer data);
    static gboolean onWindowDelete(GtkWidget *widget, GdkEvent *event, gpointer data);
    
    void updateButtonText(int row, int col);
    void updateStatusLabel();
    void checkGameEnd();
    void makeComputerMove();
    void resetGame();
    void setButtonsEnabled(bool enabled);
    
public:
    TicTacToeGame();
    ~TicTacToeGame();
    
    void run();
    void handleButtonClick(int row, int col);
    void handleNewGame();
};
