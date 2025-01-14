#include "model.h"
namespace s21 {

Point Point::randomPoint(std::vector<Point> &snake) {
  Point random;
  bool isValid;

  do {
    isValid = true;

    random.x = rand() % 10;
    random.y = rand() % 20;

    for (const auto &segment : snake) {
      if (segment.x == random.x && segment.y == random.y) {
        isValid = false;
        break;
      }
    }
  } while (!isValid);

  return random;
}

void SnakeGame::randomApple() {
  Point tmp = apple.randomPoint(snake);
  apple.x = tmp.x;
  apple.y = tmp.y;
}

// class SnakeGame
SnakeGame::SnakeGame() {
  info.score = info.level = 0;
  info.speed = 300;
  snake_state = StartGame;
  current_direction = DownRoute;
  next_direction = DownRoute;

  info.high_score = loadMaxScore();
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

int SnakeGame::loadMaxScore() {
  FILE *file = fopen("snake_score.txt", "r");
  if (file) {
    if (fscanf(file, "%d", &info.high_score) != 1) {
      info.high_score = 0;
    };
    fclose(file);
  } else {
    info.high_score = 0;
    saveScore();
    perror("Error opening file");
  }

  return info.high_score;
}

void SnakeGame::saveScore() {
  FILE *file = fopen("snake_score.txt", "w");
  if (file) {
    fprintf(file, "%d", info.high_score);
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
  if (!info.pause && start) {
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

    if (direction.x == apple.x && direction.y == apple.y) {
      if (info.score < 199) {
        info.score++;
        updateScore();
        snake_state = Spawn;
      } else {
        snake_state = GameOver;
      }
    } else if (checkCrash()) {
      clearField();
      snake.clear();
      snake_state = StartGame;
      start = false;
      info.score = info.level = 0;
      info.speed = 300;
    } else {
      snake_state = Shifting;
      snake.pop_back();
    }
    current_direction = next_direction;
  }
  updateFiguresAndField();
}

void SnakeGame::startGameInfo() {
  snake.clear();
  clearField();
  current_direction = DownRoute;
  next_direction = DownRoute;
  snakeVector();
  updateFiguresAndField();
}

bool SnakeGame::checkCrash() {
  Point tmp_direction = snake.front();
  bool res = false;
  if (checkBoard(tmp_direction.x, tmp_direction.y) ||
      checkCrashBodySnake(tmp_direction.x, tmp_direction.y, snake)) {
    res = true;
  }
  return res;
}

bool SnakeGame::checkBoard(int x, int y) {
  bool res = false;
  if (x < 0 || x >= WIDTH || y < 0 || y >= HEIGTH) {
    res = true;
  }
  return res;
}

bool SnakeGame::checkCrashBodySnake(int x, int y, std::vector<Point> &snake) {
  bool res = false;
  for (auto iter = snake.begin() + 1; iter != snake.end(); ++iter) {
    if (iter->x == x && iter->y == y) {
      res = true;
    }
  }
  return res;
}

void SnakeGame::updateScore() {
  if (info.high_score < info.score) {
    info.high_score = info.score;
  }
  if (info.level < 10) {
    info.level = info.score / 5;
  }
  info.speed = 300 - 10 * info.level;

  saveScore();
};

}  // namespace s21
