#include "ViewLAT.h"

void ViewLAT::mousePressEvent(QMouseEvent* event) {
    QPointF pos = mapToScene(event->pos());
    Qt::MouseButton btn = event->button();

    if (isBaseLineDrawn == false)
        drawBaseLine(pos, btn);
    else
      drawSpinePoint(pos, btn);
}