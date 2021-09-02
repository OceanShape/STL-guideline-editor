#include "ViewLAT.h"

void ViewLAT::mousePressEvent(QMouseEvent* event) {
    QPointF pos = mapToScene(event->pos());
    Qt::MouseButton btn = event->button();

    if (isBaseLineDrawn == false)
        drawBaseLine(pos, btn);
    else
      drawSpinePoint(pos, btn);
}

void ViewLAT::keyPressEvent(QKeyEvent* event) {
  if (event->key() == Qt::Key_1)
    currentMode = Mode::BASE_LINE;
  else if (event->key() == Qt::Key_2)
    currentMode = Mode::SPINE;
}