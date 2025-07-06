#include "../include/TicTacToeGame.h"
#include <iostream>

TicTacToeGame::TicTacToeGame() : gameOver(false), currentPlayer(Player::HUMAN) {
    // Initialize GTK
    window = gtk_window_new(GTK_WINDOW_TOPLEVEL);
    gtk_window_set_title(GTK_WINDOW(window), "Tic-Tac-Toe Game");
    gtk_window_set_default_size(GTK_WINDOW(window), 400, 500);
    gtk_window_set_resizable(GTK_WINDOW(window), FALSE);
    gtk_window_set_position(GTK_WINDOW(window), GTK_WIN_POS_CENTER);
    
    // Create main container
    GtkWidget *vbox = gtk_box_new(GTK_ORIENTATION_VERTICAL, 10);
    gtk_container_add(GTK_CONTAINER(window), vbox);
    gtk_container_set_border_width(GTK_CONTAINER(vbox), 20);
    
    // Create status label
    statusLabel = gtk_label_new("Your turn! Click a square to make your move.");
    gtk_box_pack_start(GTK_BOX(vbox), statusLabel, FALSE, FALSE, 0);
    
    // Create game grid
    grid = gtk_grid_new();
    gtk_grid_set_row_homogeneous(GTK_GRID(grid), TRUE);
    gtk_grid_set_column_homogeneous(GTK_GRID(grid), TRUE);
    gtk_grid_set_row_spacing(GTK_GRID(grid), 5);
    gtk_grid_set_column_spacing(GTK_GRID(grid), 5);
    gtk_box_pack_start(GTK_BOX(vbox), grid, TRUE, TRUE, 0);
    
    // Create buttons for the game board
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            buttons[i][j] = gtk_button_new_with_label(" ");
            gtk_widget_set_size_request(buttons[i][j], 100, 100);
            
            // Set button data to identify position
            int* position = new int[2];
            position[0] = i;
            position[1] = j;
            g_object_set_data_full(G_OBJECT(buttons[i][j]), "position", position, g_free);
            
            // Connect button signal
            g_signal_connect(buttons[i][j], "clicked", G_CALLBACK(onButtonClicked), this);
            
            gtk_grid_attach(GTK_GRID(grid), buttons[i][j], j, i, 1, 1);
        }
    }
    
    // Create new game button
    newGameButton = gtk_button_new_with_label("New Game");
    gtk_box_pack_start(GTK_BOX(vbox), newGameButton, FALSE, FALSE, 0);
    g_signal_connect(newGameButton, "clicked", G_CALLBACK(onNewGameClicked), this);
    
    // Connect window delete event
    g_signal_connect(window, "delete-event", G_CALLBACK(onWindowDelete), this);
}

TicTacToeGame::~TicTacToeGame() {
    // GTK cleanup is handled automatically
}

void TicTacToeGame::run() {
    gtk_widget_show_all(window);
    gtk_main();
}

void TicTacToeGame::onButtonClicked(GtkWidget *widget, gpointer data) {
    TicTacToeGame* game = static_cast<TicTacToeGame*>(data);
    int* position = static_cast<int*>(g_object_get_data(G_OBJECT(widget), "position"));
    game->handleButtonClick(position[0], position[1]);
}

void TicTacToeGame::onNewGameClicked(GtkWidget *widget, gpointer data) {
    TicTacToeGame* game = static_cast<TicTacToeGame*>(data);
    game->handleNewGame();
}

gboolean TicTacToeGame::onWindowDelete(GtkWidget *widget, GdkEvent *event, gpointer data) {
    gtk_main_quit();
    return FALSE;
}

void TicTacToeGame::handleButtonClick(int row, int col) {
    if (gameOver || currentPlayer != Player::HUMAN) {
        return;
    }
    
    if (gameBoard.makeMove(row, col, Player::HUMAN)) {
        updateButtonText(row, col);
        checkGameEnd();
        
        if (!gameOver) {
            currentPlayer = Player::COMPUTER;
            updateStatusLabel();
            
            // Make computer move after a short delay for better UX
            g_timeout_add(500, [](gpointer data) -> gboolean {
                TicTacToeGame* game = static_cast<TicTacToeGame*>(data);
                game->makeComputerMove();
                return FALSE; // Don't repeat
            }, this);
        }
    }
}

void TicTacToeGame::handleNewGame() {
    resetGame();
}

void TicTacToeGame::updateButtonText(int row, int col) {
    Player player = gameBoard.getCell(row, col);
    const char* text = " ";
    
    if (player == Player::HUMAN) {
        text = "X";
    } else if (player == Player::COMPUTER) {
        text = "O";
    }
    
    gtk_button_set_label(GTK_BUTTON(buttons[row][col]), text);
}

void TicTacToeGame::updateStatusLabel() {
    if (gameOver) {
        Player winner = gameBoard.checkWinner();
        if (winner == Player::HUMAN) {
            gtk_label_set_text(GTK_LABEL(statusLabel), "🎉 You win! Congratulations!");
        } else if (winner == Player::COMPUTER) {
            gtk_label_set_text(GTK_LABEL(statusLabel), "💻 Computer wins! Better luck next time!");
        } else {
            gtk_label_set_text(GTK_LABEL(statusLabel), "🤝 It's a tie! Good game!");
        }
    } else if (currentPlayer == Player::HUMAN) {
        gtk_label_set_text(GTK_LABEL(statusLabel), "Your turn! Click a square to make your move.");
    } else {
        gtk_label_set_text(GTK_LABEL(statusLabel), "Computer is thinking...");
    }
}

void TicTacToeGame::checkGameEnd() {
    Player winner = gameBoard.checkWinner();
    if (winner != Player::NONE || gameBoard.isFull()) {
        gameOver = true;
        setButtonsEnabled(false);
    }
    updateStatusLabel();
}

void TicTacToeGame::makeComputerMove() {
    if (gameOver) return;
    
    auto move = aiPlayer.getBestMove(gameBoard);
    if (move.first != -1 && move.second != -1) {
        gameBoard.makeMove(move.first, move.second, Player::COMPUTER);
        updateButtonText(move.first, move.second);
        currentPlayer = Player::HUMAN;
        checkGameEnd();
    }
}

void TicTacToeGame::resetGame() {
    gameBoard.reset();
    gameOver = false;
    currentPlayer = Player::HUMAN;
    
    // Reset button labels
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            gtk_button_set_label(GTK_BUTTON(buttons[i][j]), " ");
        }
    }
    
    setButtonsEnabled(true);
    updateStatusLabel();
}

void TicTacToeGame::setButtonsEnabled(bool enabled) {
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            gtk_widget_set_sensitive(buttons[i][j], enabled);
        }
    }
}
