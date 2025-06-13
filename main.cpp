/**
 * @file main.cpp
 * @brief Главный файл для запуска консольной игры 2048.
 *
 * Содержит точку входа в программу, предлагает пользователю выбор:
 * продолжить сохранённую игру или начать новую, и запускает игровой цикл.
 */

#include "2048.h"
#include <iostream>
#include <ctime>
#include <cctype>

/**
 * @brief Точка входа в игру 2048.
 *
 * Запускает главное меню, позволяет продолжить сохранённую игру или начать новую.
 * Основной игровой цикл обрабатывает пользовательский ввод (WASD для движения, Q для выхода),
 * отображает игровое поле, проверяет наличие возможных ходов, сохраняет состояние игры.
 *
 * @return 0 при успешном завершении.
 */
int main() {
    // Инициализация генератора случайных чисел
    srand(static_cast<unsigned>(time(0)));

    char choice;

    std::cout << "====== 2048 GAME ======\n";
    std::cout << "1. Continue saved game\n";
    std::cout << "2. Start new game\n";
    std::cout << "Choose (1 or 2): ";
    std::cin >> choice;

    bool loaded = false;

    // Загрузка сохранённой игры, если выбрана опция 1
    if (choice == '1') {
        loaded = loadGame();
        if (!loaded) {
            std::cout << "No saved game found. Starting new game...\n";
            startNewGame();
        }
    } else {
        startNewGame();
    }

    // Основной игровой цикл
    while (true) {
        printBoard();

        // Проверка на конец игры
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

        // Движение и генерация нового числа
        if (move(moveChar)) {
            generateNumber();
            saveGame();
        }
    }

    // Сохранение игры перед выходом
    saveGame();
    return 0;
}
