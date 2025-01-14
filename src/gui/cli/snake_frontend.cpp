#include "snake_frontend.h"

namespace s21 {

SnakeNcurses::SnakeNcurses(Controller *c) : controller{c} {};
SnakeNcurses::~SnakeNcurses() {};
void SnakeNcurses::startSnake() {
  WINDOW *field = newwin(22, 22, 0, 0);
  WINDOW *info = newwin(22, 18, 0, 22);

  while (controller->model->snake_state != End) {
    timeout(controller->model->info.speed);
    int key = getch();

    keyAction(key);
    controller->userInput(keyAction(key), 1);
    GameInfo_t display = controller->updateCurrentState();

    if (controller->model->snake_state == GameOver) {
      clear();
      mvprintw(1, 1, "Game Over");
      mvprintw(1, 2, "Max score: %d", display.high_score);
      mvprintw(1, 3, "Press Q to Exit to Menu");
      if (key == 'q' || key == 'Q') {
        break;
      }
    }
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
    case ' ':
      action = Start;
      break;
    case 'q':
    case 'Q':
      action = Terminate;
      break;

    case 'm':
    case 'M':
      action = Action;
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
        mvwaddch(field, i + 1, j * 2 + 1, ACS_CKBOARD);
        mvwaddch(field, i + 1, j * 2 + 2, ACS_CKBOARD);
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
    mvwprintw(info, 15, 6, "PAUSE");
  }
  if (controller->model->snake_state == StartGame) {
    mvwprintw(info, 14, 3, "Press SPACE");
    mvwprintw(info, 15, 4, "to start");
  }
  wrefresh(info);
}
}  // namespace s21