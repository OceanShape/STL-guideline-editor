#include "view.h"

std::vector<QGraphicsEllipseItem*> point;
const int clickCorrectionWidth = 20;
const int clickRangeRadius = 25;
const int pointRadius = 50;

View::View(QWidget* parent) : QGraphicsView(parent) {}

void View::mousePressEvent(QMouseEvent* event) {
  static int top = -1;
  QPointF pos = mapToScene(event->pos());
  pos.setX(pos.x() - clickCorrectionWidth);
  pos.setY(pos.y() - clickCorrectionWidth);
  QPen* pen = new QPen(Qt::green);
  QBrush* brush = new QBrush(Qt::white);
  pen->setWidth(10);
  if (event->button() == Qt::LeftButton) {
    point.push_back(scene()->addEllipse(pos.x(), pos.y(), pointRadius,
                                        pointRadius, *pen, *brush));
  } else {
    if (!point.empty()) {
      scene()->removeItem((QGraphicsItem*)point.back());
      point.pop_back();
    }
  }
}