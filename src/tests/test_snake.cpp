#include <gtest/gtest.h>
#include <unistd.h>

#include "../brick_game/snake/controller/controller.h"

int main(int argc, char* argv[]) {
  testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}

TEST(state_test, test_start) {
  s21::SnakeGame model{};
  s21::Controller controller{&model};
  EXPECT_EQ(model.snake_state, s21::StartGame);
}

TEST(state_test, test_start_1) {
  s21::SnakeGame model{};
  s21::Controller controller{&model};
  EXPECT_EQ(model.snake_state, s21::StartGame);
  controller.userInput(Start, 0);
  controller.updateCurrentState();
  EXPECT_EQ(model.info.level, 0);
  EXPECT_EQ(model.info.high_score, 0);
  EXPECT_EQ(model.info.speed, 300);
}

TEST(state_test, test_pause) {
  s21::SnakeGame model{};
  s21::Controller controller{&model};
  EXPECT_EQ(model.snake_state, s21::StartGame);
  controller.userInput(Pause, 0);
  EXPECT_EQ(model.info.pause, false);
  controller.userInput(Pause, 0);
  EXPECT_EQ(model.info.pause, true);
}

TEST(state_test, test_Terminate) {
  s21::SnakeGame model{};
  s21::Controller controller{&model};
  EXPECT_EQ(model.snake_state, s21::StartGame);
  controller.userInput(Terminate, 0);
  EXPECT_EQ(model.snake_state, s21::End);
}

TEST(state_test, test_Action) {
  s21::SnakeGame model{};
  s21::Controller controller{&model};
  EXPECT_EQ(model.snake_state, s21::StartGame);
  controller.userInput(Action, 1);
  EXPECT_EQ(model.snake_state, s21::StartGame);
}

TEST(state_test, test_StartGame) {
  s21::SnakeGame model{};
  s21::Controller controller{&model};

  controller.model->info.pause = false;
  model.start = true;

  EXPECT_EQ(model.snake_state, s21::StartGame);
  controller.userInput(Start, false);
  controller.updateCurrentState();
  EXPECT_EQ(model.snake_state, s21::Shifting);
  controller.updateCurrentState();
}

TEST(state_test, test_End) {
  s21::SnakeGame model{};
  s21::Controller controller{&model};

  controller.model->info.pause = false;
  model.start = true;

  EXPECT_EQ(model.snake_state, s21::StartGame);
  controller.userInput(Terminate, false);
  controller.updateCurrentState();
  EXPECT_EQ(model.snake_state, s21::End);
  controller.updateCurrentState();
}

TEST(state_test, test_Left) {
  s21::SnakeGame model{};
  s21::Controller controller{&model};
  EXPECT_EQ(model.snake_state, s21::StartGame);
  EXPECT_EQ(model.next_direction, model.current_direction);
  controller.userInput(Left, 0);
  int test_direction;
  EXPECT_EQ(model.next_direction, test_direction = 3);
}

TEST(state_test, test_Right) {
  s21::SnakeGame model{};
  s21::Controller controller{&model};
  EXPECT_EQ(model.snake_state, s21::StartGame);
  EXPECT_EQ(model.next_direction, model.current_direction);
  controller.userInput(Right, 0);
  int test_direction;
  EXPECT_EQ(model.next_direction, test_direction = 2);
}

TEST(state_test, test_Down) {
  s21::SnakeGame model{};
  s21::Controller controller{&model};
  EXPECT_EQ(model.snake_state, s21::StartGame);
  EXPECT_EQ(model.next_direction, model.current_direction);
  controller.userInput(Down, 0);
  int test_direction;
  EXPECT_EQ(model.next_direction, test_direction = 1);
}

TEST(state_test, test_Up) {
  s21::SnakeGame model{};
  s21::Controller controller{&model};
  EXPECT_EQ(model.snake_state, s21::StartGame);
  EXPECT_EQ(model.next_direction, model.current_direction);
  controller.userInput(Up, 0);
  int test_direction;
  EXPECT_EQ(model.next_direction, test_direction = 1);
  controller.userInput(Left, 0);
  EXPECT_EQ(model.next_direction, test_direction = 3);
}

TEST(state_test, default_case_1) {
  s21::SnakeGame model{};
  s21::Controller controller{&model};

  UserAction_t invalidAction = static_cast<UserAction_t>(999);
  controller.userInput(invalidAction, false);

  EXPECT_EQ(model.snake_state, s21::StartGame);
  EXPECT_EQ(model.next_direction, model.current_direction);
}

TEST(model_test, random_apple) {
  s21::SnakeGame model{};
  model.randomApple();
  EXPECT_NE(model.apple.x, model.apple.y);

  s21::Point old_apple = model.apple;

  model.randomApple();
  old_apple = model.apple;
}

TEST(model_test, update_score) {
  s21::SnakeGame model{};
  model.updateScore();
  EXPECT_EQ(model.info.score, 0);
  EXPECT_EQ(model.info.level, 0);
  EXPECT_EQ(model.info.speed, 300);

  model.info.score = 10;
  model.updateScore();
  EXPECT_EQ(model.info.high_score, 10);
  EXPECT_EQ(model.info.score, 10);
  EXPECT_EQ(model.info.level, 2);
  EXPECT_EQ(model.info.speed, 280);
}

TEST(model_test, move_snake_down) {
  s21::SnakeGame model{};
  s21::Controller controller{&model};

  model.start = true;
  model.info.pause = false;

  model.current_direction = s21::DownRoute;
  model.next_direction = s21::DownRoute;

  model.apple = {5, 11};

  model.moveSnake();
  controller.updateCurrentState();
  EXPECT_EQ(model.snake.front().x, 5);
  EXPECT_EQ(model.snake.front().y, 11);
  EXPECT_EQ(model.info.score, 1);

  model.apple = {5, 12};
  model.moveSnake();
  controller.updateCurrentState();
  EXPECT_EQ(model.snake.front().x, 5);
  EXPECT_EQ(model.snake.front().y, 12);

  EXPECT_EQ(model.info.score, 2);
}

TEST(model_test, move_snake_up) {
  s21::SnakeGame model{};
  s21::Controller controller{&model};

  model.start = true;
  model.info.pause = false;

  model.current_direction = s21::UpRoute;
  model.next_direction = s21::UpRoute;

  model.apple = {5, 9};

  model.moveSnake();
  controller.updateCurrentState();
  EXPECT_EQ(model.snake.front().x, 5);
  EXPECT_EQ(model.snake.front().y, 9);
  EXPECT_EQ(model.info.score, 1);
}

TEST(model_test, move_snake_left) {
  s21::SnakeGame model{};
  s21::Controller controller{&model};

  model.start = true;
  model.info.pause = false;

  model.current_direction = s21::LeftRoute;
  model.next_direction = s21::LeftRoute;

  model.apple = {4, 10};

  model.moveSnake();
  controller.updateCurrentState();
  EXPECT_EQ(model.snake.front().x, 4);
  EXPECT_EQ(model.snake.front().y, 10);
  EXPECT_EQ(model.info.score, 1);
}

TEST(model_test, move_snake_right) {
  s21::SnakeGame model{};
  s21::Controller controller{&model};

  model.start = true;
  model.info.pause = false;

  model.current_direction = s21::RightRoute;
  model.next_direction = s21::RightRoute;

  model.apple = {6, 10};

  model.moveSnake();
  controller.updateCurrentState();
  EXPECT_EQ(model.snake.front().x, 6);
  EXPECT_EQ(model.snake.front().y, 10);
  EXPECT_EQ(model.info.score, 1);
}

TEST(model_test, move_snake_crash) {
  s21::SnakeGame model{};
  s21::Controller controller{&model};

  model.start = true;
  model.info.pause = false;

  model.current_direction = s21::DownRoute;
  model.next_direction = s21::DownRoute;

  for (int i = 0; i < 11; i++) {
    model.moveSnake();
  }

  controller.updateCurrentState();

  EXPECT_EQ(model.info.score, 0);
  EXPECT_EQ(model.info.speed, 300);
  EXPECT_EQ(model.snake_state, s21::StartGame);
}