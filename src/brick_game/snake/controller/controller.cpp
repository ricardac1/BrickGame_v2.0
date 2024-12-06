#include "controller.h"
namespace s21 {

Controller::Controller(SnakeGame *model) : model{model} {}
Controller::~Controller() {}

GameInfo_t Controller::updateCurrentState() {
  auto pause = model->info.pause;
  return model->info;
}

}  // namespace s21