#include "view.h"

std::vector<QGraphicsEllipseItem*> point;

View::View(QWidget* parent) : QGraphicsView(parent) {}

void View::mousePressEvent(QMouseEvent* event) {
  QPointF pos = mapToScene(event->pos());
  QPen* pen = new QPen(Qt::green);
  QBrush* brush = new QBrush(Qt::white);
  pen->setWidth(10);
  if (event->button() == Qt::LeftButton) {
    point.push_back(
        scene()->addEllipse(pos.x() - 10, pos.y() - 10, 50, 50, *pen, *brush));
  } else {
    if (!point.empty()) {
      scene()->removeItem((QGraphicsItem*)point.back());
      point.pop_back();
    }
  }
}