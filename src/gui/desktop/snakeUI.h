#ifndef SNAKEUI_H
#define SNAKEUI_H

#include <QKeyEvent>
#include <QPainter>
#include <QTimer>
#include <QWidget>

#include "../../brick_game/snake/controller/controller.h"
namespace s21 {

class SnakeUI : public QWidget {
  Q_OBJECT
 public:
  explicit SnakeUI(QWidget *parent = nullptr);
  ~SnakeUI();

 protected:
  void paintEvent(QPaintEvent *e) override;
  void keyPressEvent(QKeyEvent *e) override;

 private:
  SnakeGame model;
  Controller controller;
  QTimer *timer;
  void drawGameField(QPainter &p, GameInfo_t inf);
  void drawGameArea(QPainter &p, GameInfo_t inf);
  void drawGameOverScreen(QPainter &p, GameInfo_t inf);
  void drawMaxScore(QPainter &p, GameInfo_t inf);
  void drawScore(QPainter &p, GameInfo_t inf);
  void drawLevel(QPainter &p, GameInfo_t inf);
  void drawInfoStart(QPainter &p);
  void drawInfoPause(QPainter &p);

 private slots:
  void update_paint(void);
};

}  // namespace s21
#endif
