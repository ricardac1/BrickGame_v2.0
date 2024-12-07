#ifndef SRC_BRICK_GAME_MODEL
#define SRC_BRICK_GAME_MODEL

#include <algorithm>
#include <cstdlib>  // Для rand() и srand()
#include <ctime>    // Для time()
#include <random>

#include "../../common/common.h"
namespace s21 {

#define WIDTH 10
#define HEIGTH 20

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

  // Point randomPoint(std::vector<Point>& snake);
  Point randomPoint();
};

class SnakeGame {
 public:
  SnakeGame();
  ~SnakeGame();
  GameInfo_t info;
  Point apple;

  void randomApple(void);
  void connectAppleAndField(void);
  void loadMaxScore();
  void saveScore();
};
}  // namespace s21
#endif  //  SRC_BRICK_GAME_MODEL
