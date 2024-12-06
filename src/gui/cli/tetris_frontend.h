#ifndef FRONTEND_H
#define FRONTEND_H

#include <ncurses.h>

#ifdef TEST_MODE
#define GET_KEY()
#else
#define GET_KEY() kp = getch()
#endif

#include "../../brick_game/tetris/backend.h"

#define COLOR 2  // Цветовая палитра терминала (1 - белый, 2 - черный)

/**
 * Инициализирует библиотеку ncurses и настраивает основные параметры окна.
 */
void InitCurses();

/**
 * Отображает стартовый экран игры с информацией о начале игры.
 */
void StartScreen();

/**
 * Отображает экран паузы при приостановке игры.
 */
void PauseScreen();

/**
 * Отображает экран окончания игры с финальными результатами.
 */
void GameOverScreen();

/**
 * Рисует квадрат на экране с указанными координатами и размерами.
 * @param x Координата X левого верхнего угла квадрата.
 * @param y Координата Y левого верхнего угла квадрата.
 * @param width Ширина квадрата.
 * @param height Высота квадрата.
 */
void DrawSquare(int x, int y, int width, int height);

/**
 * Обрабатывает нажатия клавиш для управления игрой.
 * @param state Указатель на текущее состояние игры.
 * @param kp Код нажатой клавиши.
 */
void KeyPress(TState *state, int kp);

/**
 * Отображает текущую фигуру на поле.
 * @param state Указатель на текущее состояние игры.
 */
void PrintFigure(TState *state);

void StartGame(TState state);

void InitCurses();

#endif
