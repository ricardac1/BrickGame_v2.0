#include "controller.h"
namespace s21 {

Controller::Controller(SnakeGame *model) : model{model} {}
Controller::~Controller() {}

void Controller::userInput(UserAction_t action, bool hold) {
  auto state = model->snake_state;
  auto pause = model->info.pause;

  switch (action) {
    case Start:
      model->start = true;
      break;
    case Pause:
      model->info.pause = !pause;
      break;
    case Terminate:
      model->snake_state = End;
      break;
    case Up:
      model->moveSnake(action);
      break;
    case Down:
      model->moveSnake(action);
      break;
    case Right:
      model->moveSnake(action);
      break;
    case Left:
      model->moveSnake(action);
      break;
    default:
      break;
  }
}
GameInfo_t Controller::updateCurrentState() {
  auto pause = model->info.pause;
  return model->info;
}

}  // namespace s21