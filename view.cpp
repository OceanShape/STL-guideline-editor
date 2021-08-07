#include "view.h"

qreal clickCorrectionWidth = 20;
qreal clickRangeWidth = 50;
qreal pointRadius = 40;

View::View(QWidget* parent) : QGraphicsView(parent) {}

void View::mousePressEvent(QMouseEvent* event) {
  QPointF pos = mapToScene(event->pos());
  pos.setX(pos.x() - clickCorrectionWidth);
  pos.setY(pos.y() - clickCorrectionWidth);
  QPen* pen = new QPen(Qt::green);
  pen->setWidth(10);
  QBrush* brush = new QBrush(Qt::white);

  if (event->button() == Qt::LeftButton) {
    if (clickRangedEllipseItemOrNull(pos) == false) {
      points.push_back({scene()->addEllipse(pos.x(), pos.y(), pointRadius,
                                            pointRadius, *pen, *brush),
                        pos});
    }
    if (points.size() % 4 == 0) {
      pen->setWidth(7);
      int idx = points.size() - 4;
      for (int i = 0; i < 4; ++i) {
        scene()->addLine(
            points[idx + i].position.x() + clickCorrectionWidth,
            points[idx + i].position.y() + clickCorrectionWidth,
            points[idx + (i + 1) % 4].position.x() + clickCorrectionWidth,
            points[idx + (i + 1) % 4].position.y() + clickCorrectionWidth,
            *pen);
      }
    }
  } else {
    if (!points.empty()) {
      scene()->removeItem((QGraphicsItem*)points.back().item);
      points.pop_back();
    }
  }
}

bool View::clickRangedEllipseItemOrNull(const QPointF& pos) {
  for (const auto& p : points) {
    qreal x = p.position.x();
    qreal y = p.position.y();
    if ((x - clickRangeWidth <= pos.x() && pos.x() <= x + clickRangeWidth) &&
        (y - clickRangeWidth <= pos.y() && pos.y() <= y + clickRangeWidth)) {
      return true;
    }
  }
  return false;
}