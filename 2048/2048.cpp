/**
 * @file 2048.cpp
 * @brief Реализация функций для консольной игры 2048.
 *
 * Содержит определение функций, объявленных в 2048.h.
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

int board[BOARD_SIZE][BOARD_SIZE];
int score = 0;
int bestScore = 0;

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

void clearScreen() {
    std::system("cls");
}

void printBoard() {
    clearScreen();
    std::cout << "Score: " << score << "  Best: " << bestScore << "\n\n";
    for (int i = 0; i < BOARD_SIZE; ++i) {
        for (int j = 0; j < BOARD_SIZE; ++j)
            std::cout << std::setw(5) << board[i][j];
        std::cout << "\n\n";
    }
}

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

bool moveRight() {
    bool moved = false;
    for (int i = 0; i < BOARD_SIZE; ++i) {
        int temp[BOARD_SIZE] = {};
        int idx = BOARD_SIZE - 1;
        for (int j = BOARD_SIZE - 1; j >= 0; --j) {
            if (board[i][j] == 0) continue;
            if (temp[idx] == 0) {
                temp[idx] = board[i][j];
            } else if (temp[idx] == board[i][j]) {
                temp[idx--] *= 2;
                score += temp[idx + 1];
            } else {
                if (--idx >= 0)
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

bool moveUp() {
    bool moved = false;
    for (int j = 0; j < BOARD_SIZE; ++j) {
        int temp[BOARD_SIZE] = {};
        int idx = 0;
        for (int i = 0; i < BOARD_SIZE; ++i) {
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
        for (int i = 0; i < BOARD_SIZE; ++i) {
            if (board[i][j] != temp[i]) moved = true;
            board[i][j] = temp[i];
        }
    }
    return moved;
}

bool moveDown() {
    bool moved = false;
    for (int j = 0; j < BOARD_SIZE; ++j) {
        int temp[BOARD_SIZE] = {};
        int idx = BOARD_SIZE - 1;
        for (int i = BOARD_SIZE - 1; i >= 0; --i) {
            if (board[i][j] == 0) continue;
            if (temp[idx] == 0) {
                temp[idx] = board[i][j];
            } else if (temp[idx] == board[i][j]) {
                temp[idx--] *= 2;
                score += temp[idx + 1];
            } else {
                if (--idx >= 0)
                    temp[idx] = board[i][j];
            }
        }
        for (int i = 0; i < BOARD_SIZE; ++i) {
            if (board[i][j] != temp[i]) moved = true;
            board[i][j] = temp[i];
        }
    }
    return moved;
}

bool move(char dir) {
    switch (dir) {
        case 'a': return moveLeft();
        case 'd': return moveRight();
        case 'w': return moveUp();
        case 's': return moveDown();
    }
    return false;
}

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

void startNewGame() {
    score = 0;
    for (int i = 0; i < BOARD_SIZE; ++i)
        for (int j = 0; j < BOARD_SIZE; ++j)
            board[i][j] = 0;
    generateNumber();
    generateNumber();
}
