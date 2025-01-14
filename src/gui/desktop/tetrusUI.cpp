#include "tetrisUI.h"

TetrisUI::TetrisUI(QWidget *parent) : QWidget{parent}, state(new TState) {
  setFixedSize(600, 720);
  setFocusPolicy(Qt::StrongFocus);
  setWindowTitle("Tetris");

  timer = new QTimer;
  state->state = START;
  connect(timer, &QTimer::timeout, this, &TetrisUI::update_paint);
  timer->start(100);
}

TetrisUI::~TetrisUI() {
  delete timer;
  delete state;
}

void TetrisUI::paintEvent(QPaintEvent *e) {
  Q_UNUSED(e)
  QPainter p(this);

  switch (state->state) {
    case START:
      drawStartScreen(p);
      break;
    case PLAYING:
      drawGameArea(p);
      drawGameField(p);
      drawNextFigure(p);
      break;
    case PAUSED:
      drawPauseScreen(p);
      break;
    case GAME_OVER:
      drawGameOverScreen(p);
      break;
    default:
      break;
  }
}

void TetrisUI::keyPressEvent(QKeyEvent *e) {
  if (state->state == START) {
    switch (e->key()) {
      case Qt::Key_Space:
        state->state = PLAYING;  // Начало игры при нажатии пробела
        break;
      case Qt::Key_Q:
        state->state = EXIT;
        break;
        close();  // Закрыть окно игры
    }
  } else if (state->state == PLAYING) {
    switch (e->key()) {
      case Qt::Key_P:
        state->state = PAUSED;
        break;
      case Qt::Key_Q:
        state->state = EXIT;
        close();  // Закрыть окно игры
        break;
      case Qt::Key_Left:
        UserInput(Left, 0, state);
        break;
      case Qt::Key_Right:
        UserInput(Right, 0, state);
        break;
      case Qt::Key_Up:
        UserInput(Up, 0, state);
        break;
      case Qt::Key_Down:
        UserInput(Down, 0, state);
        break;
    }
  } else if (state->state == PAUSED) {
    if (e->key() == Qt::Key_P) {
      state->state = PLAYING;  // Возврат к игре
    } else if (e->key() == Qt::Key_Q) {
      state->state = EXIT;
      close();  // Закрыть окно игры
    }
  } else if (state->state == GAME_OVER) {
    // GameOverScreen();
    if (e->key() == Qt::Key_Q) {
      state->state = EXIT;
      close();  // Закрыть окно игры
    }
  }
}

void TetrisUI::update_paint(void) {
  repaint();
  // Обновление состояния игры
  static int time = 0;  // Временная переменная для FPS
  if (state->state != EXIT) {
    UpdateCurrentState(state);
    GameFPS(state, &time);
  } else {
    // Если состояние EXIT, закрываем виджет
    close();
  }
}

void TetrisUI::drawStartScreen(QPainter &p) {
  QFont font = p.font();
  font.setPointSize(16);
  p.setFont(font);
  p.drawText(220, 300, "Welcome to Tetris!");
  p.drawText(220, 340, "Press SPACE to Start");
  p.drawText(220, 380, "Press Q to Quit");
}

void TetrisUI::drawGameField(QPainter &p) {
  int blockSize = 30;
  p.setBrush(Qt::black);

  for (int i = 0; i < FIGURE_SIZE; ++i) {
    for (int j = 0; j < FIGURE_SIZE; ++j) {
      if (state->currentFigure[i][j] == 1) {
        int x_pos = (state->figureX + j) * blockSize;
        int y_pos = (state->figureY + i) * blockSize;

        if (y_pos >= 0 && y_pos < FIELD_HEIGHT * blockSize && x_pos >= 0 &&
            x_pos < FIELD_WIDTH * blockSize) {
          p.drawRect(x_pos, y_pos, blockSize, blockSize);
        }
      }
    }
  }
  for (int i = 1; i < FIELD_HEIGHT - 1; ++i) {
    for (int j = 1; j < FIELD_WIDTH - 1; ++j) {
      if (state->field[i][j] == 1) {
        int x = j * blockSize;
        int y = i * blockSize;
        p.drawRect(x, y, blockSize, blockSize);
      }
    }
  }
}

void TetrisUI::drawPauseScreen(QPainter &p) {
  QFont font = p.font();
  font.setPointSize(16);
  p.setFont(font);

  p.drawText(220, 300, "Game Paused");
  p.drawText(220, 340, "Press P to Resume");
  p.drawText(220, 380, "Press Q to Quit");
}

void TetrisUI::drawGameOverScreen(QPainter &p) {
  QFont font = p.font();
  font.setPointSize(16);
  p.setFont(font);

  p.drawText(220, 300, "Game Over!");
  p.drawText(220, 340, "Press Q to Quit");
}

void TetrisUI::drawGameArea(QPainter &p) {
  // p.setBrush(Qt::white);

  int left = 30;
  int top = 30;
  int width = 300;
  int height = 600;

  QFont font = p.font();
  font.setPointSize(24);  // Размер текста
  p.setFont(font);

  p.drawRect(left, top, width, height);

  // Рисуем поле для отображения следующей фигуры
  p.drawText(360, top + 20, "Next Figure:");
  p.drawRect(360, top + 30, 120, 120);

  drawMaxScore(p);
  drawScore(p);
  drawLevel(p);
}

void TetrisUI::drawNextFigure(QPainter &p) {
  const int blockSize = 30;
  const int startX = 360;
  const int startY = 60;
  p.setBrush(Qt::black);

  // Рисуем следующую фигуру
  for (int i = 0; i < FIGURE_SIZE; i++) {
    for (int j = 0; j < FIGURE_SIZE; j++) {
      if (state->nextFigure[i][j] == 1) {
        int x_pos = startX + j * blockSize;
        int y_pos = startY + i * blockSize;
        p.drawRect(x_pos, y_pos, blockSize, blockSize);
      }
    }
  }
}

void TetrisUI::drawMaxScore(QPainter &p) {
  p.drawText(360, 210, "Max Score:");
  p.drawRect(360, 220, 120, 100);
  p.drawText(390, 270, QString("%1").arg(state->maxScore));
}

void TetrisUI::drawScore(QPainter &p) {
  p.drawText(360, 350, "Score:");
  p.drawRect(360, 360, 120, 100);
  p.drawText(390, 410, QString("%1").arg(state->maxScore));
}

void TetrisUI::drawLevel(QPainter &p) {
  p.drawText(360, 510, "Level:");
  p.drawRect(360, 520, 120, 100);
  p.drawText(400, 570, QString("%1").arg(state->level));
}
