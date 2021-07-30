#include "view.h"

view::view(QWidget *parent) : QGraphicsView(parent)
{

}

void view::mousePressEvent(QMouseEvent *event) {
    QPointF scenePosition = mapToScene(event->pos());
    QPen* pen = new QPen(Qt::green);
    pen->setWidth(3);
    scene()->addLine(scenePosition.x(), scenePosition.y(), scenePosition.x() + 100, scenePosition.y() + 100, *pen);
}
