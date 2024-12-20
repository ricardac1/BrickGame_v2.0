#ifndef SNAKE_FRONTEND_H
#define SNAKE_FRONTEND_H

#include <ncurses.h>

#include "../../brick_game/snake/controller/controller.h"
// #include "../../brick_game/common/common.h"

namespace s21 {

class SnakeNcurses {
 private:
  Controller *controller;

 public:
  SnakeNcurses(Controller *controller);
  // SnakeNcurses(Controller *c) : controller{c} {};
  ~SnakeNcurses();

  void startSnake();
  void drawField(WINDOW *field, GameInfo_t game);
  void drawInfo(WINDOW *info, GameInfo_t game);
  UserAction_t keyAction(int key);
};

}  // namespace s21
#endif