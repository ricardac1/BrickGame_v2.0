#include "controller.h"
namespace s21 {

Controller::Controller(SnakeGame *model) : model{model} {}
Controller::~Controller() {}

void Controller::userInput(UserAction_t action, bool hold) {
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
      if (model->current_direction != DownRoute) {
        model->next_direction = UpRoute;
      }
      break;
    case Down:
      if (model->current_direction != UpRoute) {
        model->next_direction = DownRoute;
      }
      break;
    case Right:
      if (model->current_direction != LeftRoute) {
        model->next_direction = RightRoute;
      }

      break;
    case Left:
      if (model->current_direction != RightRoute) {
        model->next_direction = LeftRoute;
      }
      break;
    case Action:
      if (hold) {
        model->moveSnake();
      }
      break;
    default:
      break;
  }
}

GameInfo_t Controller::updateCurrentState() {
  if (!model->info.pause && model->start) {
    switch (model->snake_state) {
      case StartGame:
        model->startGameInfo();
        model->snake_state = Shifting;
        break;
      case Spawn:
        model->randomApple();
        model->snake_state = Shifting;
        break;
      case Shifting:
        model->moveSnake();
        break;
      case End:
        model->clearField();
        model->snake.clear();
        break;
      default:
        break;
    }
  }
  model->updateFiguresAndField();
  return model->info;
}

}  // namespace s21