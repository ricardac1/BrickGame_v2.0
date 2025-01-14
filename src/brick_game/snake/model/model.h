#ifndef SRC_BRICK_GAME_MODEL
#define SRC_BRICK_GAME_MODEL

#include <chrono>
#include <cstdlib>
#include <ctime>
#include <random>
#include <thread>

#include "../../common/common.h"
namespace s21 {

#define WIDTH 10
#define HEIGTH 20

typedef enum { StartGame, Spawn, Moving, Shifting, End, GameOver } GameState;
typedef enum { UpRoute, DownRoute, RightRoute, LeftRoute } Direction;

class Point {
 public:
  int x, y;
  Point() : x{}, y{} {};
  Point(int x, int y) : x{x}, y{y} {};
  Point(const Point& p) : x{p.x}, y{p.y} {};
  Point& operator=(const Point& other) {
    if (this != &other) {
      x = other.x;
      y = other.y;
    }
    return *this;
  }

  Point randomPoint(std::vector<Point>& snake);
};

class SnakeGame {
 public:
  SnakeGame();
  ~SnakeGame();

  GameState snake_state;
  std::vector<Point> snake;
  GameInfo_t info;
  Point apple;
  bool start;
  Direction current_direction;
  Direction next_direction;

  void randomApple();
  void connectApple();
  int loadMaxScore();
  void saveScore();
  void snakeVector();
  void connectSnake();
  void moveSnake();
  void clearField();
  GameInfo_t updateFiguresAndField();
  void startGameInfo();
  bool checkCrash();
  bool checkBoard(int x, int y);
  bool checkCrashBodySnake(int x, int y, std::vector<Point>& snake);
  void updateScore();
  void delaySnake(int milliseconds);
};
}  // namespace s21
#endif  //  SRC_BRICK_GAME_MODEL
