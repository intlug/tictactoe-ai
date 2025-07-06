#include <gtk/gtk.h>
#include "../include/TicTacToeGame.h"
#include <iostream>

int main(int argc, char *argv[]) {
    // Initialize GTK
    gtk_init(&argc, &argv);
    
    std::cout << "Starting Tic-Tac-Toe Game..." << std::endl;
    
   
    try {
        // Create and run the game
        TicTacToeGame game;
        game.run();
    } catch (const std::exception& e) {
        std::cerr << "Error: " << e.what() << std::endl;
        return 1;
    }
    
    std::cout << "Game ended. Goodbye!" << std::endl;
    return 0;
}
