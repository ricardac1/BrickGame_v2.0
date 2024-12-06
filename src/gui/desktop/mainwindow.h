#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "tetrisUI.h"

QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

class MainWindow : public QMainWindow {
  Q_OBJECT

 public:
  MainWindow(QWidget *parent = nullptr);
  ~MainWindow();

 private slots:
  void on_pushButtonTetris_clicked();
  void on_pushButtonSnake_clicked();

 private:
  Ui::MainWindow *ui;
  TetrisUI *t;
  // SnakeUI *s;
};
#endif  // MAINWINDOW_H
