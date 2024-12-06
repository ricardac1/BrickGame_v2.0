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

  void DrawGameArea(QPainter &p);
  void DrawStartScreen(QPainter &p);
  void DrawGameField(QPainter &p);
  void DrawPauseScreen(QPainter &p);
  void DrawGameOverScreen(QPainter &p);
  void DrawNextFigure(QPainter &p);
  void DrawMaxScore(QPainter &p);
  void DrawScore(QPainter &p);
  void DrawLevel(QPainter &p);

 private slots:
  void update_paint(void);
};

#endif  // TETRISUI_H
