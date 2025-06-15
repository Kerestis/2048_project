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

/// Размер игрового поля (4x4)
const int BOARD_SIZE = 4;

/// Глобальный массив игрового поля
/// Значения: степени двойки (2, 4, 8...) или 0 для пустых ячеек
extern int board[BOARD_SIZE][BOARD_SIZE];

/// Текущий счёт игрока
extern int score;

/// Лучший сохранённый счёт
extern int bestScore;

/// @brief Загружает сохранённое состояние игры из файла.
/// @return true, если удалось загрузить, иначе false.
///
/// @code
/// if (!loadGame()) {
///     startNewGame();
/// }
/// @endcode
bool loadGame();

/// @brief Сохраняет текущее состояние игры и лучший счёт в файл.
///
/// @code
/// saveGame();
/// @endcode
void saveGame();

/// @brief Очищает экран консоли.
///
/// Работает через system("cls") на Windows.
/// @code
/// clearScreen();
/// @endcode
void clearScreen();

/// @brief Выводит игровое поле в консоль с текущим и лучшим счётом.
///
/// @code
/// printBoard();
/// @endcode
void printBoard();

/// @brief Добавляет на случайную пустую ячейку число 2 (90%) или 4 (10%).
///
/// Вызывается в начале игры и после каждого хода.
/// @code
/// generateNumber();
/// @endcode
void generateNumber();

/// @brief Двигает и объединяет ячейки влево согласно правилам 2048.
/// @return true, если поле изменилось, иначе false.
///
/// @code
/// board[0] = {2, 2, 0, 0};
/// moveLeft();
/// @endcode
bool moveLeft();

/// @brief Поворачивает игровое поле по часовой стрелке на 90°.
///
/// Используется для реализации движения вверх и вправо через moveLeft().
///
/// @code
/// rotateBoardClockwise();
/// @endcode
void rotateBoardClockwise();

/// @brief Поворачивает игровое поле против часовой стрелки на 90°.
///
/// Используется для реализации движения вверх и вниз через moveLeft().
///
/// @code
/// rotateBoardCounterClockwise();
/// @endcode
void rotateBoardCounterClockwise();

/// @brief Выполняет ход в заданном направлении ('w', 'a', 's', 'd').
/// @param dir — символ направления: W (вверх), A (влево), S (вниз), D (вправо)
/// @return true, если поле изменилось после хода.
///
/// @code
/// if (move('a')) {
///     generateNumber();
///     saveGame();
/// }
/// @endcode
bool move(char dir);

/// @brief Проверяет, возможно ли совершить хоть один ход.
/// @return true, если можно сделать ход, иначе false (игра окончена).
///
/// Проверка:
/// - есть хотя бы одна пустая ячейка
/// - есть соседние одинаковые числа
///
/// @code
/// if (!canMove()) {
///     std::cout << "Game Over!";
/// }
/// @endcode
bool canMove();

/// @brief Инициализирует новое игровое поле: сбрасывает счёт и размещает два числа.
///
/// @code
/// startNewGame();
/// @endcode
void startNewGame();

#endif // GAME_2048_H
