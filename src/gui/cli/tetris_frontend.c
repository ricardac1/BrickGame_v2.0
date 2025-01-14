#include "tetris_frontend.h"

void StartGame(TState state) {
  int timer = 0;
  while (state.state != EXIT) {
    UpdateCurrentState(&state);
    KeyPress(&state, 0);
    GameFPS(&state, &timer);
    refresh();
  }
}
void StartScreen() {
  clear();
  mvprintw(FIELD_HEIGHT / 2, FIELD_WIDTH - 6, "Press SPACE to Start");
  refresh();
}
void PauseScreen() {
  mvprintw(FIELD_HEIGHT - 12, FIELD_WIDTH - 2, "PAUSE");
  refresh();
}

void GameOverScreen() {
  clear();
  mvprintw(FIELD_HEIGHT - 10, FIELD_WIDTH, "GAME OVER");
  mvprintw(FIELD_HEIGHT - 9, FIELD_WIDTH, "Press Q to Exit");
  refresh();
}

void PrintField(TState *state) {
  clear();  // Очистка экрана

  attron(COLOR_PAIR(COLOR));
  // Отрисовка границ игрового поля
  // (y,x,width,height)
  DrawSquare(0, 1, FIELD_WIDTH * 2 - 2, FIELD_HEIGHT);
  DrawSquare(0, FIELD_WIDTH * 2 - 1, FIELD_WIDTH + 8, FIELD_HEIGHT);
  //  Отрисовка границ информационного поля
  //  (y,x,width,height)
  DrawSquare(1, FIELD_WIDTH * 2 + 1, FIELD_WIDTH + 4, 3);
  mvprintw(2, FIELD_WIDTH * 2 + 4, "Ricardac");
  mvprintw(5, FIELD_WIDTH * 2 + 2, "Next");
  PrintNextFigure(state);

  DrawSquare(7, FIELD_WIDTH * 2 + 1, 7, 4);
  DrawSquare(7, FIELD_WIDTH * 2 + 8, FIELD_WIDTH - 3, 4);
  mvprintw(8, FIELD_WIDTH * 2 + 2, "MAX");
  mvprintw(9, FIELD_WIDTH * 2 + 2, "Score");
  mvprintw(8, FIELD_WIDTH * 2 + 11, "%d", state->maxScore);

  DrawSquare(11, FIELD_WIDTH * 2 + 1, 7, 4);
  DrawSquare(11, FIELD_WIDTH * 2 + 8, FIELD_WIDTH - 3, 4);
  mvprintw(12, FIELD_WIDTH * 2 + 2, "Score");
  mvprintw(12, FIELD_WIDTH * 2 + 11, "%d", state->score);

  DrawSquare(15, FIELD_WIDTH * 2 + 1, 7, 4);
  DrawSquare(15, FIELD_WIDTH * 2 + 8, FIELD_WIDTH - 3, 4);
  mvprintw(16, FIELD_WIDTH * 2 + 2, "Level");
  mvprintw(16, FIELD_WIDTH * 2 + 11, "%d", state->level);

  PrintFigure(state);
  attroff(COLOR_PAIR(COLOR));

  refresh();  // Обновление экрана
}

void DrawSquare(int y, int x, int width, int height) {
  // Рисуем верхнюю и нижнюю границы
  for (int i = 0; i < width; i++) {
    mvaddch(y, x + i, ACS_HLINE);               // Верхняя граница
    mvaddch(y + height - 1, x + i, ACS_HLINE);  // Нижняя граница
  }
  // Рисуем боковые границы
  for (int i = 0; i < height; i++) {
    mvaddch(y + i, x, ACS_VLINE);              // Левая граница
    mvaddch(y + i, x + width - 1, ACS_VLINE);  // Правая граница
  }
  // Углы прямоугольника
  mvaddch(y, x, ACS_ULCORNER);  // Левый верхний угол
  mvaddch(y, x + width - 1, ACS_URCORNER);  // Правый верхний угол
  mvaddch(y + height - 1, x, ACS_LLCORNER);  // Левый нижний угол
  mvaddch(y + height - 1, x + width - 1, ACS_LRCORNER);  // Правый нижний угол

  refresh();  // Обновляем экран
}

void PrintFigure(TState *state) {
  // Отрисовка текущей фигуры
  for (int i = 0; i < FIGURE_SIZE; i++) {
    for (int j = 0; j < FIGURE_SIZE; j++) {
      if (state->currentFigure[i][j] == 1) {
        int x_pos = ((state->figureX + j) * 2);
        int y_pos = state->figureY + i;
        if (y_pos >= 1 && y_pos < FIELD_HEIGHT + 1 && x_pos >= 1 &&
            x_pos < FIELD_WIDTH * 2 + 1) {
          mvaddch(y_pos, x_pos, ACS_CKBOARD);
          mvaddch(y_pos, x_pos + 1, ACS_CKBOARD);
          // mvprintw(state->figureY + i, (state->figureX + j) * 2, "[]");
        }
      }
    }
  }
  PrintFixFigure(state);
  refresh();
}
void PrintFixFigure(TState *state) {
  for (int i = 1; i < FIELD_HEIGHT - 1; i++) {
    for (int j = 1; j < FIELD_WIDTH - 1; j++) {
      if (state->field[i][j] == 1) {
        mvaddch(i, j * 2, ACS_CKBOARD);
        mvaddch(i, j * 2 + 1, ACS_CKBOARD);
      }
    }
  }
}

void PrintNextFigure(TState *state) {
  int m = 4;   // Стартовая позиция по вертикали
  int n = 32;  // Стартовая позиция по горизонтали

  // Рисуем следующую фигуру
  for (int i = 0; i < FIGURE_SIZE; i++) {
    for (int j = 0; j < FIGURE_SIZE; j++) {
      if (state->nextFigure[i][j] == 1) {
        mvaddch(m, n, ACS_CKBOARD);
        mvaddch(m, n + 1, ACS_CKBOARD);
      }
      n += 2;
    }
    n = 32;
    m++;
  }
}

void KeyPress(TState *state, int kp) {
  GET_KEY();
  PrintField(state);
  if (state->state == START) {
    StartScreen();
    switch (kp) {
      case ' ':
        state->state = PLAYING;  // Начало игры при нажатии пробела
        break;
      case 'q':
      case 'Q':
        state->state = EXIT;
        break;
    }
  } else if (state->state == PLAYING) {
    switch (kp) {
      case 'p':
      case 'P':
        state->state = PAUSED;
        break;
      case 'q':
      case 'Q':
        state->state = EXIT;
        break;
      case KEY_LEFT:
        UserInput(Left, 0, state);
        break;
      case KEY_RIGHT:
        UserInput(Right, 0, state);
        break;
      case KEY_UP:
        UserInput(Up, 0, state);
        break;
      case KEY_DOWN:
        UserInput(Down, 0, state);
        break;
    }
  } else if (state->state == PAUSED) {
    PauseScreen();
    switch (kp) {
      case 'p':
      case 'P':
        state->state = PLAYING;
        break;
      case 'q':
      case 'Q':
        state->state = EXIT;
        break;
    }
  } else if (state->state == GAME_OVER) {
    GameOverScreen();
    switch (kp) {
      case 'q':
      case 'Q':
        state->state = EXIT;
        break;
    }
  }
}

void InitCurses() {
  initscr();
  cbreak();
  noecho();
  keypad(stdscr, TRUE);
  curs_set(0);
  timeout(80);
  mousemask(0, NULL);
  start_color();
  init_pair(1, COLOR_BLACK, COLOR_WHITE);
  init_pair(2, COLOR_WHITE, COLOR_BLACK);
  bkgd(COLOR_PAIR(COLOR));
}
