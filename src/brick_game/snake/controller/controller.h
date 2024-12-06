#ifndef CONTROLLER_H_
#define CONTROLLER_H_

#include "../model/model.h"

typedef enum UserAction_t {
  Start,
  Pause,
  Terminate,
  Left,
  Right,
  Up,
  Down,
  Action
} UserAction_t;

typedef struct {
  int **field;
  int **next;
  int score;
  int high_score;
  int level;
  int speed;
  int pause;
} GameInfo_t;

namespace s21 {

class Controller {
 public:
  SnakeGame *model;

  Controller(SnakeGame *model);
  ~Controller();

  // void userInput(UserAction_t action, bool hold);
  // GameInfo_t updateCurrentState();
};

}  // namespace s21

#endif  // CONTROLLER_H_