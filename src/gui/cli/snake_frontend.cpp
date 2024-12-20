#include "snake_frontend.h"

namespace s21 {

SnakeNcurses::SnakeNcurses(Controller *c) : controller{c} {};
SnakeNcurses::~SnakeNcurses() {};
void SnakeNcurses::startSnake() {
  WINDOW *field = newwin(22, 22, 0, 0);
  WINDOW *info = newwin(22, 18, 0, 22);
  int key = 0;
  while (controller->model->snake_state != End) {
    timeout(500);
    key = getch();
    UserAction_t user_input = keyAction(key);
    controller->userInput(keyAction(key), 0);
    GameInfo_t display = controller->updateCurrentState();
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
    case 'Q':
      action = Terminate;
      break;

    case 'p':
    case 'P':
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
  int **coordinat = game.field;
  for (int i{}; i < HEIGTH; ++i) {
    for (int j{}; j < WIDTH; ++j) {
      if (coordinat[i][j]) {
        mvwaddch(field, i + 1, j * 2 + 1, '#');
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