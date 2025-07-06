// AI Fix: Change include sequence to avoid invalid redefine of the std namespace
// This also clears the error of gtk not found. Note the CMakeLists.txt file has been updated to include the necessary GTK libraries.

#include <iostream>
#include <exception>
#include <gtk/gtk.h>
#include "../include/TicTacToeGame.h"

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
