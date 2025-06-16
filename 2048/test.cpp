#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include "doctest.h"
#include "2048.h"

TEST_CASE("1") {
    startNewGame();

    int nonZeroCount = 0;
    for (int i = 0; i < BOARD_SIZE; ++i)
        for (int j = 0; j < BOARD_SIZE; ++j)
            if (board[i][j] != 0)
                ++nonZeroCount;

    CHECK(nonZeroCount == 2);
    CHECK(score == 0);
}

TEST_CASE("2") {
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

TEST_CASE("3") {
    for (int i = 0; i < BOARD_SIZE; ++i)
        std::fill(board[i], board[i] + BOARD_SIZE, 0);

    board[1][2] = 2;
    board[1][3] = 2;
    score = 0;

    bool moved = moveRight();

    CHECK(moved == true);
    CHECK(board[1][3] == 4);
    CHECK(board[1][2] == 0);
    CHECK(score == 4);
}

TEST_CASE("4") {
    for (int i = 0; i < BOARD_SIZE; ++i)
        for (int j = 0; j < BOARD_SIZE; ++j)
            board[i][j] = 0;

    board[2][0] = 2;
    board[3][0] = 2;
    score = 0;

    bool moved = moveUp();

    CHECK(moved == true);
    CHECK(board[0][0] == 4);
    CHECK(board[1][0] == 0);
    CHECK(score == 4);
}

TEST_CASE("5") {
    for (int i = 0; i < BOARD_SIZE; ++i)
        for (int j = 0; j < BOARD_SIZE; ++j)
            board[i][j] = 0;

    board[0][1] = 2;
    board[1][1] = 2;
    score = 0;

    bool moved = moveDown();

    CHECK(moved == true);
    CHECK(board[3][1] == 4);
    CHECK(board[2][1] == 0);
    CHECK(score == 4);
}

TEST_CASE("6") {
    int val = 2;
    for (int i = 0; i < BOARD_SIZE; ++i)
        for (int j = 0; j < BOARD_SIZE; ++j)
            board[i][j] = val++;

    CHECK(canMove() == false);
}

TEST_CASE("7") {
    startNewGame();
    int before = 0;
    for (int i = 0; i < BOARD_SIZE; ++i)
        for (int j = 0; j < BOARD_SIZE; ++j)
            if (board[i][j] != 0)
                ++before;

    moveLeft();
    generateNumber();

    int after = 0;
    for (int i = 0; i < BOARD_SIZE; ++i)
        for (int j = 0; j < BOARD_SIZE; ++j)
            if (board[i][j] != 0)
                ++after;

    CHECK(after >= before);
}
