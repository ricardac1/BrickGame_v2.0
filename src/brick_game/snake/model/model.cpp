#include "model.h"
namespace s21 {

Point Point::randomPoint() {
  Point random;
  random.x = rand() % 10;  // Например, от 0 до 19
  random.y = rand() % 20;

  return random;
}

void SnakeGame::randomApple() {
  Point tmp = apple.randomPoint();
  apple.x = tmp.x;
  apple.y = tmp.y;
}

// class SnakeGame
SnakeGame::SnakeGame() {
  randomApple();
  loadMaxScore();
  info.score = info.level = 0;
  info.speed = 600;

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

void SnakeGame::connectAppleAndField(void) { info.field[apple.y][apple.x] = 1; }

void SnakeGame::loadMaxScore() {
  FILE *file = fopen("snake_score.txt", "r");
  if (file) {
    fscanf(file, "%d", &info.high_score);
    fclose(file);
  } else {
    saveScore();
    perror("Error opening file");
  }
}

void SnakeGame::saveScore() {
  FILE *file = fopen("snake_score.txt", "w");
  if (file) {
    fprintf(file, "%d", &info.high_score);
    fclose(file);
  } else {
    perror("Error opening file");
  }
}

};  // namespace s21
