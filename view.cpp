#include "view.h"

const qreal clickCorrectionWidth = 20;
const qreal clickRangeWidth = 50;
const qreal pointRadius = 50;
std::vector<QPair<QGraphicsEllipseItem*, QPointF>> point;

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
      point.push_back({scene()->addEllipse(pos.x(), pos.y(), pointRadius,
                                           pointRadius, *pen, *brush),
                       pos});
    }
  }
  // else {
  // if (!point.empty()) {
  //  scene()->removeItem((QGraphicsItem*)point.back());
  //  point.pop_back();
  //}
  //}
}

bool View::clickRangedEllipseItemOrNull(const QPointF& pos) {
  for (const auto& p : point) {
    qreal x = p.second.x();
    qreal y = p.second.y();
    if ((x - clickRangeWidth <= pos.x() && pos.x() <= x + clickRangeWidth) &&
        (y - clickRangeWidth <= pos.y() && pos.y() <= y + clickRangeWidth)) {
      return true;
    }
  }
  return false;
}