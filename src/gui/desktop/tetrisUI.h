#ifndef TETRISUI_H
#define TETRISUI_H

#ifdef __cplusplus
extern "C" {
#endif
#include "../../brick_game/tetris/backend.h"
#ifdef __cplusplus
}
#endif

#include <QKeyEvent>
#include <QPainter>
#include <QTimer>
#include <QWidget>

class TetrisUI : public QWidget {
  Q_OBJECT
 public:
  explicit TetrisUI(QWidget *parent = nullptr);
  ~TetrisUI();

 protected:
  void paintEvent(QPaintEvent *e) override;
  void keyPressEvent(QKeyEvent *e) override;

 private:
  QTimer *timer;
  TState *state;

  void drawGameArea(QPainter &p);
  void drawStartScreen(QPainter &p);
  void drawGameField(QPainter &p);
  void drawPauseScreen(QPainter &p);
  void drawGameOverScreen(QPainter &p);
  void drawNextFigure(QPainter &p);
  void drawMaxScore(QPainter &p);
  void drawScore(QPainter &p);
  void drawLevel(QPainter &p);

 private slots:
  void update_paint(void);
};

#endif  // TETRISUI_H
