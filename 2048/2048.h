/**
 * @file 2048.h
 * @brief Заголовочный файл для консольной игры 2048.
 *
 * Содержит определения глобальных переменных и функций, 
 * отвечающих за основную логику игры: загрузка/сохранение состояния, 
 * отрисовка, управление игровым полем, генерация новых чисел, обработка ходов и проверка завершения игры.
 */

#ifndef GAME_2048_H
#define GAME_2048_H

#include <string>

/**
 * @brief Размер игрового поля (4x4).
 * @type int
 */
const int BOARD_SIZE = 4;

/**
 * @brief Игровое поле.
 * @type int[BOARD_SIZE][BOARD_SIZE]
 * Значения: степени двойки (2, 4, 8...) или 0 для пустых ячеек
 */
extern int board[BOARD_SIZE][BOARD_SIZE];

/**
 * @brief Текущий счёт игрока.
 * @type int
 */
extern int score;

/**
 * @brief Лучший сохранённый счёт.
 * @type int
 */
extern int bestScore;

/**
 * @brief Загружает сохранённое состояние игры из файла.
 * @return bool true, если удалось загрузить, иначе false.
 *
 * @code
 * if (!loadGame()) {
 *     startNewGame();
 * }
 * @endcode
 */
bool loadGame();

/**
 * @brief Сохраняет текущее состояние игры и лучший счёт в файл.
 * @return void
 *
 * @code
 * saveGame();
 * @endcode
 */
void saveGame();

/**
 * @brief Очищает экран консоли.
 * @return void
 *
 * Работает через system("cls") на Windows.
 *
 * @code
 * clearScreen();
 * @endcode
 */
void clearScreen();

/**
 * @brief Выводит игровое поле в консоль с текущим и лучшим счётом.
 * @return void
 *
 * @code
 * printBoard();
 * @endcode
 */
void printBoard();

/**
 * @brief Добавляет на случайную пустую ячейку число 2 (90%) или 4 (10%).
 * @return void
 *
 * Вызывается в начале игры и после каждого хода.
 *
 * @code
 * generateNumber();
 * @endcode
 */
void generateNumber();

/**
 * @brief Двигает и объединяет ячейки влево согласно правилам 2048.
 * @return bool true, если поле изменилось, иначе false.
 *
 * @code
 * board[0] = {2, 2, 0, 0};
 * moveLeft();
 * @endcode
 */
bool moveLeft();

/**
 * @brief Двигает и объединяет ячейки вправо согласно правилам 2048.
 * @return bool true, если поле изменилось, иначе false.
 *
 * @code
 * board[0] = {0, 0, 2, 2};
 * moveRight(); // board[0] -> {0, 0, 0, 4}, score += 4
 * @endcode
 */
bool moveRight();

/**
 * @brief Двигает и объединяет ячейки вверх согласно правилам 2048.
 * @return bool true, если поле изменилось, иначе false.
 *
 * @code
 * // Пример для первого столбца: {2, 2, 0, 0} -> {4, 0, 0, 0}, score += 4
 * moveUp();
 * @endcode
 */
bool moveUp();

/**
 * @brief Двигает и объединяет ячейки вниз согласно правилам 2048.
 * @return bool true, если поле изменилось, иначе false.
 *
 * @code
 * // Пример для первого столбца: {0, 0, 2, 2} -> {0, 0, 0, 4}, score += 4
 * moveDown();
 * @endcode
 */
bool moveDown();

/**
 * @brief Выполняет ход в заданном направлении.
 * @param dir Символ направления: 'w' (вверх), 'a' (влево), 's' (вниз), 'd' (вправо)
 * @type char
 * @return bool true, если поле изменилось после хода.
 *
 * @code
 * if (move('a')) {
 *     generateNumber();
 *     saveGame();
 * }
 * @endcode
 */
bool move(char dir);

/**
 * @brief Проверяет, возможно ли совершить хоть один ход.
 * @return bool true, если можно сделать ход, иначе false (игра окончена).
 *
 * Проверка:
 * - есть хотя бы одна пустая ячейка
 * - есть соседние одинаковые числа
 *
 * @code
 * if (!canMove()) {
 *     std::cout << "Game Over!";
 * }
 * @endcode
 */
bool canMove();

/**
 * @brief Инициализирует новое игровое поле: сбрасывает счёт и размещает два числа.
 * @return void
 *
 * @code
 * startNewGame();
 * @endcode
 */
void startNewGame();

#endif

