#include "model.h"

namespace s21 {

Point Point::randomPoint() {
  Point random;
  random.x = rand() % 20;  // Например, от 0 до 19
  random.y = rand() % 10;

  return random;
}

void SnakeGame::randomApple() {
  Point tmp = apple.randomPoint();
  apple.x = tmp.x;
  apple.y = tmp.y;
}

void SnakeGame::connectAppleAndField(void) { info.field[apple.y][apple.x] = 1; }
// class SnakeGame
SnakeGame::SnakeGame() {
  randomApple();

  info.field = new int *[HEIGTH];
  for (int i{}; i < HEIGTH; ++i) {
    info.field[i] = new int[WIDTH]{};
  }
  connectAppleAndField();
}

SnakeGame::~SnakeGame() {
  for (int i{}; i < HEIGTH; ++i) {
    delete[] info.field[i];
  }
  delete[] info.field;
}
}  // namespace s21
