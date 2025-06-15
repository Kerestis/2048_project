#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include "doctest.h"
#include "2048.h"

TEST_CASE("New game initializes correctly") {
    startNewGame();

    int nonZeroCount = 0;
    for (int i = 0; i < BOARD_SIZE; ++i)
        for (int j = 0; j < BOARD_SIZE; ++j)
            if (board[i][j] != 0)
                ++nonZeroCount;

    CHECK(nonZeroCount == 2); // Должно быть 2 стартовых числа
    CHECK(score == 0);
}

TEST_CASE("Board rotation clockwise and counterclockwise") {
    startNewGame();

    // Заполним поле предсказуемыми значениями
    int value = 1;
    for (int i = 0; i < BOARD_SIZE; ++i)
        for (int j = 0; j < BOARD_SIZE; ++j)
            board[i][j] = value++;

    int original[BOARD_SIZE][BOARD_SIZE];
    std::copy(&board[0][0], &board[0][0] + BOARD_SIZE * BOARD_SIZE, &original[0][0]);

    rotateBoardClockwise();
    rotateBoardCounterClockwise();

    CHECK(std::equal(&board[0][0], &board[0][0] + BOARD_SIZE * BOARD_SIZE, &original[0][0]));  // Поле должно вернуться в исходное состояние
}

TEST_CASE("Moving left combines tiles correctly") {
    for (int i = 0; i < BOARD_SIZE; ++i)
        std::fill(board[i], board[i] + BOARD_SIZE, 0);

    board[0][0] = 2;
    board[0][1] = 2;

    score = 0;
    bool moved = moveLeft();

    CHECK(moved == true);
    CHECK(board[0][0] == 4);
    CHECK(board[0][1] == 0);
    CHECK(score == 4);
}

TEST_CASE("No move possible when board is full and no merges") {
    int val = 2;
    for (int i = 0; i < BOARD_SIZE; ++i)
        for (int j = 0; j < BOARD_SIZE; ++j)
            board[i][j] = val++;

    CHECK(canMove() == false);
}

TEST_CASE("Move adds new number to the board") {
    startNewGame();
    int before = 0;
    for (int i = 0; i < BOARD_SIZE; ++i)
        for (int j = 0; j < BOARD_SIZE; ++j)
            if (board[i][j] != 0)
                ++before;

    move('a');
    generateNumber();

    int after = 0;
    for (int i = 0; i < BOARD_SIZE; ++i)
        for (int j = 0; j < BOARD_SIZE; ++j)
            if (board[i][j] != 0)
                ++after;

    CHECK(after >= before); // Должно быть больше или равно (если ход не прошёл)
}
