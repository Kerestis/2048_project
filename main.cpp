/**
 * @file main.cpp
 * @brief Главный файл запуска консольной игры 2048.
 *
 * Содержит только функцию main() и логику запуска игрового цикла.
 */

#include "2048.h"
#include <iostream>
#include <ctime>
#include <cctype>

int main() {
    srand(static_cast<unsigned>(time(0)));

    char choice;

    std::cout << "====== 2048 GAME ======\n";
    std::cout << "1. Continue saved game\n";
    std::cout << "2. Start new game\n";
    std::cout << "Choose (1 or 2): ";
    std::cin >> choice;

    bool loaded = false;

    if (choice == '1') {
        loaded = loadGame();
        if (!loaded) {
            std::cout << "No saved game found. Starting new game...\n";
            startNewGame();
        }
    } else {
        startNewGame();
    }

    while (true) {
        printBoard();

        if (!canMove()) {
            std::cout << "Game Over! No more possible moves.\n";
            break;
        }

        std::cout << "Move (WASD, Q to quit): ";
        char moveChar;
        std::cin >> moveChar;
        moveChar = static_cast<char>(std::tolower(moveChar));

        if (moveChar == 'q') break;

        if (moveChar != 'w' && moveChar != 'a' && moveChar != 's' && moveChar != 'd') {
            std::cout << "Invalid input! Use WASD keys to move.\n";
            continue;
        }

        if (move(moveChar)) {
            generateNumber();
            saveGame();
        }
    }

    saveGame();
    return 0;
}
