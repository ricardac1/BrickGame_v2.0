#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent),
      ui(new Ui::MainWindow),
      t(new TetrisUI) {
    ui->setupUi(this);
    setWindowTitle("BrickGame");
}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::on_pushButtonTetris_clicked()
{
    hide();
    t->show();
}


void MainWindow::on_pushButtonSnake_clicked()
{
    hide();
    //s->show();
}

