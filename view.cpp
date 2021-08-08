#include "View.h"

qreal clickCorrectionWidth = 20;
qreal clickRangeWidth = 20;
qreal pointRadius = 50;

std::vector<QGraphicsLineItem*> lines;

View::View(QWidget* parent) : QGraphicsView(parent) {
  lines.reserve(4 * 7);

  pen = new QPen(Qt::green);
  pen->setWidth(10);
  brush = new QBrush(Qt::white);

  isBaseLineDrawn = false;
}

View::~View() {
  delete pen;
  delete brush;
}

void View::drawBaseLine(const QPointF& pos, const Qt::MouseButton& btn) {
  if (btn == Qt::LeftButton) {
    scene()->addLine(pos.x(), 0 + 10, pos.x(), static_cast<qreal>(4480 - 10),
                     *pen);
    pen->setColor(Qt::red);
    pen->setStyle(Qt::DotLine);
    scene()->addLine(0 + 10, pos.y(), static_cast<qreal>(3600 - 10), pos.y(),
                     *pen);
    pen->setColor(Qt::green);
    pen->setStyle(Qt::SolidLine);
    isBaseLineDrawn = true;
  }
}

void View::drawPointAndLine(QPointF pos, const Qt::MouseButton& btn) {
  pos.setX(pos.x() - clickCorrectionWidth);
  pos.setY(pos.y() - clickCorrectionWidth);
  if (btn == Qt::LeftButton) {
    if (clickRangedEllipseItemOrNull(pos) == false) {
      pen->setWidth(10);
      points.push_back({scene()->addEllipse(pos.x(), pos.y(), pointRadius,
                                            pointRadius, *pen, *brush),
                        pos});
    }
    if (points.size() % 4 == 0) {
      pen->setWidth(7);
      size_t idx = points.size() - 4;
      for (size_t i = 0; i < 4; ++i) {
        lines.push_back(scene()->addLine(
            points[idx + i].position.x() + clickCorrectionWidth,
            points[idx + i].position.y() + clickCorrectionWidth,
            points[idx + (i + 1) % 4].position.x() + clickCorrectionWidth,
            points[idx + (i + 1) % 4].position.y() + clickCorrectionWidth,
            *pen));
      }
    }
  } else {
    if (points.empty()) return;
    scene()->removeItem((QGraphicsItem*)points.back().item);
    points.pop_back();
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