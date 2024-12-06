#include "snake_frontend.h"

namespace s21 {

void SnakeNcurses::startSnake() {
  WINDOW *field = newwin(22, 22, 0, 0);
  WINDOW *info = newwin(12, 18, 0, 24);
  mvprintw(0, 0, "############################");
  int key = 0;
  while (key != 27) {
    key = getch();
    GameInfo_t display;
    drawField(field, display);
    drawInfo(info, display);
  }

  delwin(field);
  delwin(info);
}

void SnakeNcurses::drawField(WINDOW *field, GameInfo_t game) { werase(field); }

void SnakeNcurses::drawInfo(WINDOW *info, GameInfo_t game) {}
}  // namespace s21