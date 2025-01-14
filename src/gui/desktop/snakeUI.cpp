#include "snakeUI.h"
namespace s21 {
SnakeUI::SnakeUI(QWidget *parent)
    : QWidget{parent}, model{}, controller{&model} {
  setFixedSize(600, 720);
  setFocusPolicy(Qt::StrongFocus);
  setWindowTitle("Snake");

  timer = new QTimer;
  connect(timer, &QTimer::timeout, this, &SnakeUI::update_paint);
  timer->start(200 + controller.model->info.speed);
}

SnakeUI::~SnakeUI() { delete timer; }

void SnakeUI::paintEvent(QPaintEvent *e) {
  Q_UNUSED(e)
  QPainter p(this);
  controller.updateCurrentState();
  GameInfo_t inf = controller.model->info;
  drawGameArea(p, inf);
  drawGameField(p, inf);
}

void SnakeUI::drawGameField(QPainter &p, GameInfo_t inf) {
  int blockSize = 30;

  for (int i{}; i < 20; ++i) {
    for (int j{}; j < 10; ++j) {
      if (inf.field[i][j]) {
        p.setPen(Qt::white);
        p.setBrush(Qt::black);
        int x = j * blockSize;
        int y = i * blockSize;
        p.drawRect(x + blockSize, y + blockSize, blockSize, blockSize);
      }
    }
  }
}

void SnakeUI::drawGameArea(QPainter &p, GameInfo_t inf) {
  int left = 30;
  int top = 30;
  int width = 300;
  int height = 600;

  p.drawRect(left, top, width, height);
  QFont font = p.font();
  font.setPointSize(24);  // Размер текста
  p.setFont(font);

  drawMaxScore(p, inf);
  drawScore(p, inf);
  drawLevel(p, inf);
  if (controller.model->snake_state == StartGame) {
    drawInfoStart(p);
  }
  if (model.info.pause) {
    drawInfoPause(p);
  }
}

void SnakeUI::drawMaxScore(QPainter &p, GameInfo_t inf) {
  p.drawText(360, 30, "Max Score:");
  p.drawRect(360, 40, 120, 100);
  p.drawText(400, 80, QString("%1").arg(inf.high_score));
}

void SnakeUI::drawScore(QPainter &p, GameInfo_t inf) {
  p.drawText(360, 160, "Score:");
  p.drawRect(360, 180, 120, 100);
  p.drawText(400, 230, QString("%1").arg(inf.score));
}

void SnakeUI::drawLevel(QPainter &p, GameInfo_t inf) {
  p.drawText(360, 310, "Level:");
  p.drawRect(360, 320, 120, 100);
  p.drawText(400, 370, QString("%1").arg(inf.level));
}

void SnakeUI::drawInfoStart(QPainter &p) {
  p.drawText(400, 500, "Press SPACE");
  p.drawText(430, 530, "to start");
}

void SnakeUI::drawInfoPause(QPainter &p) { p.drawText(400, 540, "PAUSE"); }
void SnakeUI::keyPressEvent(QKeyEvent *e) {
  UserAction_t action = Start;

  switch (e->key()) {
    case Qt::Key_Up:
      action = Up;
      break;

    case Qt::Key_Down:
      action = Down;
      break;

    case Qt::Key_Left:
      action = Left;
      break;

    case Qt::Key_Right:
      action = Right;
      break;
    case Qt::Key_Space:
      action = Start;
      break;
    case Qt::Key_Q:
      action = Terminate;
      break;

    case Qt::Key_M:
      action = Action;
      break;

    case Qt::Key_P:
      action = Pause;
      break;

    default:
      break;
  }

  bool hold = (action == Action) ? true : false;
  controller.userInput(action, hold);
  update_paint();
  if (action == Terminate) {
    QWidget::close();
  }
}

void SnakeUI::update_paint() { repaint(); }
}  // namespace s21
