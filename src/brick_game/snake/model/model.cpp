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
  info.score = info.level = 0;
  info.speed = 600;
  snake_state = StartGame;
  current_direction = DownRoute;
  next_direction = DownRoute;

  // randomApple();
  loadMaxScore();
  snakeVector();

  info.field = new int *[HEIGTH];
  for (int i{}; i < HEIGTH; ++i) {
    info.field[i] = new int[WIDTH]{};
  }

  connectSnake();
  connectApple();
}

SnakeGame::~SnakeGame() {
  for (int i{}; i < HEIGTH; ++i) {
    delete[] info.field[i];
  }
  delete[] info.field;
}

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

void SnakeGame::clearField() {
  for (int i{}; i < HEIGTH; ++i) {
    for (int j{}; j < WIDTH; ++j) {
      info.field[i][j] = 0;
    }
  }
}

void SnakeGame::snakeVector() {
  snake.clear();
  snake.push_back(Point{WIDTH / 2, HEIGTH / 2});
  snake.push_back(Point{WIDTH / 2, HEIGTH / 2 - 1});
  snake.push_back(Point{WIDTH / 2, HEIGTH / 2 - 2});
  snake.push_back(Point{WIDTH / 2, HEIGTH / 2 - 3});
}

void SnakeGame::connectApple() { info.field[apple.y][apple.x] = 1; }
void SnakeGame::connectSnake() {
  for (auto iter = snake.begin(); iter != snake.end(); ++iter) {
    int x = (*iter).x;
    int y = (*iter).y;
    info.field[y][x] = 1;
  }
}

GameInfo_t SnakeGame::updateFiguresAndField() {
  clearField();
  connectApple();
  connectSnake();
  return info;
}

void SnakeGame::moveSnake() {
  Point direction{snake.front()};
  switch (next_direction) {
    case UpRoute:
      direction.y -= 1;
      break;
    case DownRoute:
      direction.y += 1;
      break;
    case RightRoute:
      direction.x += 1;
      break;
    case LeftRoute:
      direction.x -= 1;
      break;
    default:
      break;
  }
  snake.insert(snake.begin(), direction);
  snake.pop_back();
  current_direction = next_direction;
  updateFiguresAndField();
}

void SnakeGame::startGameInfo() {
  snake.clear();
  clearField();
  current_direction = DownRoute;
  next_direction = DownRoute;
  randomApple();
  snakeVector();
  updateFiguresAndField();
}
}  // namespace s21
