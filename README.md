# Tic-Tac-Toe Game

A modern C++ implementation of the classic Tic-Tac-Toe game with a GTK3 graphical interface and an intelligent AI opponent.

## Features

- 🎮 Interactive GTK3 graphical user interface
- 🤖 Intelligent AI opponent using minimax algorithm with alpha-beta pruning
- 🎯 Unbeatable AI that plays optimally
- 🔄 New game functionality
- 📱 Clean, modern interface with status updates
- 🏗️ CMake build system
- 🐛 VS Code debugging support

## Prerequisites

Before building the project, make sure you have the following dependencies installed:

### Ubuntu/Debian:
```bash
sudo apt update
sudo apt install build-essential cmake pkg-config libgtk-3-dev gdb
```

### Fedora/RHEL:
```bash
sudo dnf install gcc-c++ cmake pkgconfig gtk3-devel gdb
```

### Arch Linux:
```bash
sudo pacman -S base-devel cmake pkgconfig gtk3 gdb
```

## Building the Project

### Method 1: Using VS Code (Recommended)

1. Open the project folder in VS Code
2. Install the recommended extensions:
   - C/C++ Extension Pack
   - CMake Tools
3. Press `Ctrl+Shift+P` and run "CMake: Configure"
4. Press `Ctrl+Shift+P` and run "Tasks: Run Task" → "Compile Project"
5. Or simply press `Ctrl+Shift+B` to build

### Method 2: Command Line

```bash
# Configure the build
cmake -B build -DCMAKE_BUILD_TYPE=Debug

# Build the project
cmake --build build

# Run the game
./build/TicTacToe
```

## VS Code Development Features

### Building
- **Ctrl+Shift+B**: Build the project (default task)
- **Ctrl+Shift+P** → "Tasks: Run Task" → "Clean Build": Clean and rebuild

### Running
- **Ctrl+Shift+P** → "Tasks: Run Task" → "Run Game": Build and run the game

### Debugging
- **F5**: Start debugging session
- Set breakpoints by clicking on line numbers
- Use the Debug Console for GDB commands
- Variables and call stack are automatically displayed

### Available Tasks
- **Build Debug**: Configure CMake for debug build
- **Compile Project**: Build the executable (default)
- **Clean Build**: Remove build directory
- **Run Game**: Build and run the game

## How to Play

1. Launch the game
2. Click on any empty square to make your move (you play as 'X')
3. The computer will automatically make its move (plays as 'O')
4. Try to get three of your symbols in a row (horizontally, vertically, or diagonally)
5. Click "New Game" to start over

## AI Algorithm

The computer opponent uses the **minimax algorithm** with **alpha-beta pruning** to ensure optimal play. This means:

- The AI will never lose if it can avoid it
- The AI will always win if a winning opportunity exists
- The best you can achieve against the AI is a tie
- The AI evaluates all possible future moves to choose the best one

## Project Structure

```
├── CMakeLists.txt          # CMake build configuration
├── README.md               # This file
├── .vscode/                # VS Code configuration
│   ├── tasks.json          # Build tasks
│   ├── launch.json         # Debug configuration
│   ├── c_cpp_properties.json # IntelliSense configuration
│   └── settings.json       # Workspace settings
├── include/                # Header files
│   ├── GameBoard.h         # Game board logic
│   ├── AIPlayer.h          # AI implementation
│   └── TicTacToeGame.h     # Main game class with GTK interface
└── src/                    # Source files
    ├── main.cpp            # Application entry point
    ├── GameBoard.cpp       # Game board implementation
    ├── AIPlayer.cpp        # AI logic implementation
    └── TicTacToeGame.cpp   # GTK interface implementation
```

## Architecture

- **GameBoard**: Manages the game state and rules
- **AIPlayer**: Implements the minimax algorithm for computer moves
- **TicTacToeGame**: Handles the GTK3 user interface and game flow
- **main.cpp**: Application entry point and GTK initialization

## Troubleshooting

### Build Issues

1. **GTK3 not found**: Make sure you have installed `libgtk-3-dev` (Ubuntu) or equivalent
2. **CMake not found**: Install CMake using your package manager
3. **Compiler errors**: Ensure you have a C++17 compatible compiler

### Runtime Issues

1. **Display issues**: Make sure you're running in a graphical environment
2. **Permission errors**: Check that the executable has proper permissions

### VS Code Issues

1. **IntelliSense not working**: Install the C/C++ extension and reload VS Code
2. **Debugging not working**: Make sure `gdb` is installed
3. **Tasks not found**: Make sure you've opened the correct folder containing `.vscode/`

## Contributing

Feel free to fork this project and submit pull requests for improvements!

## License

This project is open source and available under the MIT License.
