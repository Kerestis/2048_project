/**
 * @file 2048.cpp
 * @brief Реализация логики консольной игры 2048.
 *
 * Этот файл содержит функции, управляющие состоянием игры, выводом, 
 * движением чисел, генерацией новых блоков, а также сохранением/загрузкой состояния.
 */

#include "2048.h"

#include <iostream>
#include <vector>
#include <cstdlib>
#include <ctime>
#include <fstream>
#include <iomanip>
#include <algorithm>
#include <random>

/// @var board
/// Игровое поле размером 4x4, содержащее значения (0 — пустая клетка, остальное — степени двойки)
int board[BOARD_SIZE][BOARD_SIZE];

/// @var score
/// Текущий счёт игрока
int score = 0;

/// @var bestScore
/// Лучший достигнутый счёт (загружается/сохраняется отдельно)
int bestScore = 0;

/**
 * @brief Загружает состояние игры из файлов.
 * @return true если загрузка прошла успешно, иначе false.
 */
bool loadGame() {
    std::ifstream in("savegame.txt");
    if (!in.is_open()) return false;

    for (int i = 0; i < BOARD_SIZE; ++i)
        for (int j = 0; j < BOARD_SIZE; ++j)
            if (!(in >> board[i][j])) return false;

    if (!(in >> score)) return false;
    in.close();

    std::ifstream bestIn("bestscore.txt");
    if (bestIn.is_open()) {
        bestIn >> bestScore;
        bestIn.close();
    }

    return true;
}

/**
 * @brief Сохраняет текущее состояние игры и лучший счёт в файлы.
 */
void saveGame() {
    std::ofstream out("savegame.txt");
    for (int i = 0; i < BOARD_SIZE; ++i) {
        for (int j = 0; j < BOARD_SIZE; ++j)
            out << board[i][j] << ' ';
        out << '\n';
    }
    out << score;
    out.close();

    if (score > bestScore) {
        bestScore = score;
        std::ofstream bestOut("bestscore.txt");
        bestOut << bestScore;
        bestOut.close();
    }
}

/**
 * @brief Очищает экран консоли (только Windows).
 */
void clearScreen() {
    std::system("cls");
}

/**
 * @brief Печатает текущее игровое поле и счёт на экран.
 */
void printBoard() {
    clearScreen();
    std::cout << "Score: " << score << "  Best: " << bestScore << "\n\n";
    for (int i = 0; i < BOARD_SIZE; ++i) {
        for (int j = 0; j < BOARD_SIZE; ++j)
            std::cout << std::setw(5) << board[i][j];
        std::cout << "\n\n";
    }
}

/**
 * @brief Генерирует новое число (2 или 4) в случайной пустой ячейке.
 */
void generateNumber() {
    std::vector<std::pair<int, int>> empty;
    for (int i = 0; i < BOARD_SIZE; ++i)
        for (int j = 0; j < BOARD_SIZE; ++j)
            if (board[i][j] == 0)
                empty.emplace_back(i, j);

    if (!empty.empty()) {
        std::random_device rd;
        std::mt19937 gen(rd());
        std::uniform_int_distribution<size_t> dis(0, empty.size() - 1);
        auto [x, y] = empty[dis(gen)];
        board[x][y] = (rand() % 10 < 9) ? 2 : 4;
    }
}

/**
 * @brief Выполняет сдвиг и слияние ячеек влево.
 * @return true, если поле изменилось, иначе false.
 */
bool moveLeft() {
    bool moved = false;
    for (int i = 0; i < BOARD_SIZE; ++i) {
        int temp[BOARD_SIZE] = {};
        int idx = 0;
        for (int j = 0; j < BOARD_SIZE; ++j) {
            if (board[i][j] == 0) continue;
            if (temp[idx] == 0) {
                temp[idx] = board[i][j];
            } else if (temp[idx] == board[i][j]) {
                temp[idx++] *= 2;
                score += temp[idx - 1];
            } else {
                if (++idx < BOARD_SIZE)
                    temp[idx] = board[i][j];
            }
        }
        for (int j = 0; j < BOARD_SIZE; ++j) {
            if (board[i][j] != temp[j]) moved = true;
            board[i][j] = temp[j];
        }
    }
    return moved;
}

/**
 * @brief Поворачивает игровое поле по часовой стрелке.
 */
void rotateBoardClockwise() {
    int tmp[BOARD_SIZE][BOARD_SIZE];
    for (int i = 0; i < BOARD_SIZE; ++i)
        for (int j = 0; j < BOARD_SIZE; ++j)
            tmp[i][j] = board[BOARD_SIZE - j - 1][i];
    std::copy(&tmp[0][0], &tmp[0][0] + BOARD_SIZE * BOARD_SIZE, &board[0][0]);
}

/**
 * @brief Поворачивает игровое поле против часовой стрелки.
 */
void rotateBoardCounterClockwise() {
    int tmp[BOARD_SIZE][BOARD_SIZE];
    for (int i = 0; i < BOARD_SIZE; ++i)
        for (int j = 0; j < BOARD_SIZE; ++j)
            tmp[i][j] = board[j][BOARD_SIZE - i - 1];
    std::copy(&tmp[0][0], &tmp[0][0] + BOARD_SIZE * BOARD_SIZE, &board[0][0]);
}

/**
 * @brief Делает ход в заданном направлении.
 * @param dir Символ направления: 'w' (вверх), 'a' (влево), 's' (вниз), 'd' (вправо)
 * @return true, если поле изменилось после хода.
 */
bool move(char dir) {
    bool moved = false;
    switch (dir) {
        case 'a':
            moved = moveLeft();
            break;
        case 'd':
            rotateBoardClockwise();
            rotateBoardClockwise();
            moved = moveLeft();
            rotateBoardClockwise();
            rotateBoardClockwise();
            break;
        case 'w':
            rotateBoardCounterClockwise();
            moved = moveLeft();
            rotateBoardClockwise();
            break;
        case 's':
            rotateBoardClockwise();
            moved = moveLeft();
            rotateBoardCounterClockwise();
            break;
    }
    return moved;
}

/**
 * @brief Проверяет, можно ли совершить ход.
 * @return true, если есть хотя бы один доступный ход.
 */
bool canMove() {
    for (int i = 0; i < BOARD_SIZE; ++i)
        for (int j = 0; j < BOARD_SIZE; ++j) {
            if (board[i][j] == 0)
                return true;
            if (i + 1 < BOARD_SIZE && board[i][j] == board[i + 1][j])
                return true;
            if (j + 1 < BOARD_SIZE && board[i][j] == board[i][j + 1])
                return true;
        }
    return false;
}

/**
 * @brief Начинает новую игру: сбрасывает поле и счёт, генерирует 2 числа.
 */
void startNewGame() {
    score = 0;
    for (int i = 0; i < BOARD_SIZE; ++i)
        for (int j = 0; j < BOARD_SIZE; ++j)
            board[i][j] = 0;
    generateNumber();
    generateNumber();
}
