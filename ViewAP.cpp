#include "ViewAP.h"

void ViewAP::mousePressEvent(QMouseEvent* event) {
  QPointF pos = mapToScene(event->pos());
  Qt::MouseButton btn = event->button();

  if (isBaseLineDrawn == false)
    drawBaseLine(pos, btn);
  else
    drawPointAndLine(pos, btn);
}

void ViewAP::keyPressEvent(QKeyEvent* event) {
    if (event->key() == Qt::Key_1)
        currentMode = Mode::BASE_LINE;
    if (event->key() == Qt::Key_2)
        currentMode = Mode::SPINE;
}