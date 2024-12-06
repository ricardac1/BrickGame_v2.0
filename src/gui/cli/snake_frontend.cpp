#include "snake_frontend.h"

namespace s21 {

void SnakeNcurses::startSnake() {
  WINDOW *field = newwin(22, 22, 0, 0);
  WINDOW *info = newwin(22, 18, 0, 22);
  int key = 0;
  while (key != 27) {
    key = getch();
    GameInfo_t display;
    UserAction_t user_input = keyAction(key);
    drawField(field, display);
    drawInfo(info, display);
  }

  delwin(field);
  delwin(info);
}

UserAction_t SnakeNcurses::keyAction(int key) {
  UserAction_t action;
  switch (key) {
    case KEY_UP:
      action = Up;
      break;

    case KEY_DOWN:
      action = Down;
      break;

    case KEY_LEFT:
      action = Left;
      break;

    case KEY_RIGHT:
      action = Right;
      break;
    case '\n':
      action = Start;
      break;
    case 'q':
      action = Terminate;
      break;

    case 'p':
      action = Pause;
      break;

    default:
      break;
  }

  return action;
};
void SnakeNcurses::drawField(WINDOW *field, GameInfo_t game) {
  werase(field);
  box(field, 0, 0);
  int testField[20][10] = {
      {0, 0, 0, 0, 0, 0, 0, 0, 0, 0}, {0, 0, 1, 1, 1, 0, 0, 0, 0, 0},
      {0, 0, 0, 0, 1, 0, 0, 0, 0, 0}, {0, 0, 0, 0, 1, 0, 0, 0, 0, 0},
      {0, 0, 0, 0, 1, 1, 1, 1, 0, 0}, {0, 0, 0, 0, 0, 0, 0, 1, 0, 0},
      {0, 0, 0, 0, 0, 0, 0, 1, 0, 0}, {0, 0, 0, 0, 0, 0, 0, 1, 1, 1},
      {0, 0, 0, 0, 0, 0, 0, 0, 0, 0}, {0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
      {0, 0, 0, 0, 0, 0, 0, 0, 0, 0}, {0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
      {0, 0, 0, 0, 0, 0, 0, 0, 0, 0}, {0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
      {0, 0, 0, 0, 0, 0, 0, 0, 0, 0}, {0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
      {0, 0, 0, 0, 0, 0, 0, 0, 0, 0}, {0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
      {0, 0, 0, 0, 0, 0, 0, 0, 0, 0}, {0, 0, 0, 0, 0, 0, 0, 0, 0, 0}};

  game.field = new int *[20];
  for (int i = 0; i < 20; i++) {
    game.field[i] = new int[10];
    for (int j = 0; j < 10; j++) {
      game.field[i][j] = testField[i][j];
    }
  }
  int **coordinat = game.field;
  for (int i{}; i < 20; ++i) {
    for (int j{}; j < 10; ++j) {
      if (coordinat[i][j]) {
        mvwaddch(field, i + 1, j + 1, '#');
      }
    }
  }
  wrefresh(field);
}

void SnakeNcurses::drawInfo(WINDOW *info, GameInfo_t game) {
  werase(info);
  box(info, 0, 0);
  mvwprintw(info, 1, 1, "SCORE %d", game.score);
  mvwprintw(info, 3, 1, "MAX SCORE %d", game.high_score);
  mvwprintw(info, 5, 1, "LEVEL %d", game.level);
  mvwprintw(info, 7, 1, "SPEED %d", game.speed);
  if (game.pause) {
    mvwprintw(info, 9, 1, "PAUSE");
  }
  UserAction_t draw_info;
  if (draw_info == Start) {
    mvwprintw(info, 14, 3, "Press ENTER");
    mvwprintw(info, 15, 4, "to start");
  }
  wrefresh(info);
}
}  // namespace s21