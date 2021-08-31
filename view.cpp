#include "View.h"

qreal clickCorrectionWidth = 20;
qreal clickRangeWidth = 20;
qreal pointRadius = 50;

std::vector<QGraphicsLineItem*> lines;

View::View(QWidget* parent) : QGraphicsView(parent) {
  currentSpine = 0;
  currentPointCount = 0;

  initSpineArray();
  for (int i = 0; i < spineCount; ++i)
    for (int j = 0; j < pointCountForOneSpine; ++j) spineLine[i][j] = nullptr;

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

void View::initSpineArray() {
  for (size_t i = 0; i < spineCount; ++i)
    for (size_t j = 0; j < pointCountForOneSpine; ++j)
      spine[i][j].position = {-FLT_MAX, -FLT_MAX};
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

bool View::isPointInvalid(const point& p) {
  return (p.position.x() <= static_cast<qreal>(-4480)) ||
         (p.position.y() <= static_cast<qreal>(-3600));
}

void View::removeAllLine() {
  for (int i = 0; i < spineCount; ++i)
    for (int j = 0; j < pointCountForOneSpine; ++j)
      if (spineLine[i][j] != nullptr) {
        scene()->removeItem(spineLine[i][j]);
        spineLine[i][j] = nullptr;
      }
}

void View::drawSpineLine() {
  // 선 모두 지우기
  removeAllLine();

  // 모든 선 다시 그리기
  for (int i = 0; i < spineCount; ++i) {
    bool isAllPointSet = true;
    for (int j = 0; j < pointCountForOneSpine; ++j) {
      if (isPointInvalid(spine[i][j])) isAllPointSet = false;
    }

    if (isAllPointSet) {
      // 점 정렬
      point tmp[pointCountForOneSpine];

      for (int j = 0; j < pointCountForOneSpine; ++j) {
        int rightPointCount = 0;
        int downPointCount = 0;
        for (int k = 0; k < pointCountForOneSpine; ++k) {
          if (j == k) continue;
          if (spine[i][j].position.x() < spine[i][k].position.x())
            ++rightPointCount;
          if (spine[i][j].position.y() < spine[i][k].position.y())
            ++downPointCount;
        }
        if (rightPointCount >= 2) {
          if (downPointCount >= 2)
            tmp[0] = spine[i][j];
          else
            tmp[3] = spine[i][j];
        } else {
          if (downPointCount >= 2)
            tmp[1] = spine[i][j];
          else
            tmp[2] = spine[i][j];
        }
      }

      for (int j = 0; j < pointCountForOneSpine; ++j) spine[i][j] = tmp[j];

      // 선 긋기
      pen->setWidth(7);
      for (int j = 0; j < pointCountForOneSpine; ++j) {
        spineLine[i][j] = scene()->addLine(
            spine[i][j].position.x() + clickCorrectionWidth,
            spine[i][j].position.y() + clickCorrectionWidth,
            spine[i][(j + 1) % 4].position.x() + clickCorrectionWidth,
            spine[i][(j + 1) % 4].position.y() + clickCorrectionWidth, *pen);
      }
    }
  }
}

void View::drawSpinePoint(QPointF pos, const Qt::MouseButton& btn) {
  pos.setX(pos.x() - clickCorrectionWidth);
  pos.setY(pos.y() - clickCorrectionWidth);
  if (btn == Qt::LeftButton) {
    if (currentSpine >= spineCount) return;
    if (isClickRanged(pos)) return;
    pen->setWidth(10);
    spine[currentSpine][currentPointCount++] = {
        scene()->addEllipse(pos.x(), pos.y(), pointRadius, pointRadius, *pen,
                            *brush),
        pos};
    if (currentPointCount == 4) {
      currentPointCount = 0;
      ++currentSpine;
    }
  } else {
    if (points.empty()) return;
    scene()->removeItem((QGraphicsItem*)points.back().item);
    points.pop_back();
  }
  drawSpineLine();
}

bool View::isClickRanged(const QPointF& pos) {
  for (const auto& p : points) {
    qreal x = p.position.x();
    qreal y = p.position.y();
    if ((x - clickRangeWidth <= pos.x() && pos.x() <= x + clickRangeWidth) &&
        (y - clickRangeWidth <= pos.y() && pos.y() <= y + clickRangeWidth))
      return true;
  }
  return false;
}