#include "ViewAP.h"

void ViewAP::mousePressEvent(QMouseEvent* event) {
  QPointF pos = mapToScene(event->pos());
  Qt::MouseButton btn = event->button();

  if (isBaseLineDrawn == false)
    drawBaseLine(pos, btn);
  else
    drawPointAndLine(pos, btn);
}