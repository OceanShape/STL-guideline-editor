#include "ViewAP.h"

void ViewAP::mousePressEvent(QMouseEvent* event) {
  QPointF pos = mapToScene(event->pos());
  Qt::MouseButton btn = event->button();

  if (currentMode == Mode::BASE_LINE) {
    if (isBaseLineDrawn == false) drawBaseLine(pos, btn);
  } else if (currentMode == Mode::SPINE) {
    drawSpinePoint(pos, btn);
  }
}

void ViewAP::keyPressEvent(QKeyEvent* event) {
  if (event->key() == Qt::Key_1)
    currentMode = Mode::BASE_LINE;
  else if (event->key() == Qt::Key_2)
    currentMode = Mode::SPINE;
}