#include "brick_game_cli.h"

int main() {
  TState state;
  state.state = START;
  InitCurses();

  while (1) {
    clear();
    mvprintw(1, 7, "BrickGame v2.0");
    mvprintw(2, 1, "Tetris - Enter 'T' or 't' for start");
    mvprintw(3, 1, "Snake  - Enter 'S' or 's' for start");
    mvprintw(4, 1, "Exit   - Enter 'Q'");
    int key_g = getch();
    if (key_g == 'T' || key_g == 't') {
      clear();
      StartGame(state);
    } else if (key_g == 'S' || key_g == 's') {
      clear();
      s21::SnakeGame model{};
      s21::Controller controller{&model};
      s21::SnakeNcurses view{&controller};
      // s21::SnakeNcurses view{};
      view.startSnake();
    } else if (key_g == 'Q' || key_g == 'q') {
      break;
    }
  }
  endwin();
  return 0;
}