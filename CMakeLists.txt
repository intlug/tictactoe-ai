cmake_minimum_required(VERSION 3.16)
project(TicTacToe VERSION 1.0.0 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Find required packages
find_package(PkgConfig REQUIRED)
pkg_check_modules(GTK3 REQUIRED gtk+-3.0)

# Include directories
include_directories(${GTK3_INCLUDE_DIRS})
include_directories(include)

# Add compiler flags
add_definitions(${GTK3_CFLAGS_OTHER})

# Create executable
add_executable(${PROJECT_NAME}
    src/main.cpp
    src/TicTacToeGame.cpp
    src/GameBoard.cpp
    src/AIPlayer.cpp
)

# Link libraries
target_link_libraries(${PROJECT_NAME} ${GTK3_LIBRARIES})

# Set compile flags for debug builds
if(CMAKE_BUILD_TYPE STREQUAL "Debug")
    target_compile_options(${PROJECT_NAME} PRIVATE -g -O0 -Wall -Wextra)
endif()

# Install target
install(TARGETS ${PROJECT_NAME} DESTINATION bin)
