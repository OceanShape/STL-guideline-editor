#include "View.h"

qreal clickCorrectionWidth = 20;
qreal clickRangeWidth = 50;
qreal pointRadius = 50;

View::View(QWidget* parent) : QGraphicsView(parent) {
  currentSpine = 0;
  currentPointCount = 0;

  initSpineArray();
  for (int i = 0; i < spineCount; ++i) spineCenter[i] = {-FLT_MAX, -FLT_MAX};

  for (int i = 0; i < spineCount; ++i)
    for (int j = 0; j < pointCountForOneSpine; ++j) spineLine[i][j] = nullptr;

  pen = new QPen(Qt::green);
  pen->setWidth(10);
  brush = new QBrush(Qt::white);

  isBaseLineDrawn = false;
}

View::~View() {
  delete pen;
  delete brush;
}

void View::initSpinePoint(point* p) {
  p->position = {-FLT_MAX, -FLT_MAX};
  p->item = nullptr;
}
void View::initSpineArray() {
  for (size_t i = 0; i < spineCount; ++i)
    for (size_t j = 0; j < pointCountForOneSpine; ++j)
      initSpinePoint(&spinePoint[i][j]);
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

void View::removeAllLine() {
  for (int i = 0; i < spineCount; ++i)
    for (int j = 0; j < pointCountForOneSpine; ++j)
      if (spineLine[i][j] != nullptr) {
        scene()->removeItem(spineLine[i][j]);
        spineLine[i][j] = nullptr;
      }
}

bool View::isPointInvalid(const point& p) {
  return (p.position.x() <= static_cast<qreal>(-4480)) ||
         (p.position.y() <= static_cast<qreal>(-3600));
}

void View::drawSpineLine() {
  // 선 모두 지우기
  removeAllLine();

  // 모든 선 다시 그리기
  for (int i = 0; i < spineCount; ++i) {
    bool isAllPointSet = true;
    for (int j = 0; j < pointCountForOneSpine; ++j) {
      if (isPointInvalid(spinePoint[i][j])) {
        isAllPointSet = false;
      }
    }

    if (isAllPointSet) {
      // 점 정렬
      point tmp[pointCountForOneSpine];

      for (int j = 0; j < pointCountForOneSpine; ++j) {
        int rightPointCount = 0;
        int downPointCount = 0;
        for (int k = 0; k < pointCountForOneSpine; ++k) {
          if (j == k) continue;
          if (spinePoint[i][j].position.x() < spinePoint[i][k].position.x())
            ++rightPointCount;
          if (spinePoint[i][j].position.y() < spinePoint[i][k].position.y())
            ++downPointCount;
        }
        if (rightPointCount >= 2) {
          if (downPointCount >= 2)
            tmp[0] = spinePoint[i][j];
          else
            tmp[3] = spinePoint[i][j];
        } else {
          if (downPointCount >= 2)
            tmp[1] = spinePoint[i][j];
          else
            tmp[2] = spinePoint[i][j];
        }
      }

      for (int j = 0; j < pointCountForOneSpine; ++j) spinePoint[i][j] = tmp[j];

      // 선 긋기
      pen->setWidth(7);
      for (int j = 0; j < pointCountForOneSpine; ++j) {
        spineLine[i][j] = scene()->addLine(
            spinePoint[i][j].position.x() + clickCorrectionWidth,
            spinePoint[i][j].position.y() + clickCorrectionWidth,
            spinePoint[i][(j + 1) % 4].position.x() + clickCorrectionWidth,
            spinePoint[i][(j + 1) % 4].position.y() + clickCorrectionWidth,
            *pen);
      }

      qreal x = 0, y = 0;
      for (int j = 0; j < pointCountForOneSpine; ++j) {
        x += spinePoint[i][j].position.x();
        y += spinePoint[i][j].position.y();
      }
      spineCenter[i] = {x / 4, y / 4};
    }
  }
}

void View::update() { drawSpineLine(); }

void View::drawSpinePoint(QPointF pos, const Qt::MouseButton& btn) {
  int removeSpineIndex, removePointIndex;
  pos.setX(pos.x() - clickCorrectionWidth);
  pos.setY(pos.y() - clickCorrectionWidth);
  if (btn == Qt::LeftButton) {
    if (currentSpine >= spineCount) return;
    if (clickRangedPointOrNull(pos, removeSpineIndex, removePointIndex) !=
        nullptr)
      return;

    pen->setWidth(10);
    spinePoint[currentSpine][currentPointCount] = {
        scene()->addEllipse(pos.x(), pos.y(), pointRadius, pointRadius, *pen,
                            *brush),
        pos};

    if (removedPoint.empty() == false) {
      auto t = removedPoint.top();
      removedPoint.pop();
      currentSpine = t.first;
      currentPointCount = t.second;
    } else {
      ++currentPointCount;
      if (currentPointCount == 4) {
        currentPointCount = 0;
        ++currentSpine;
      }
    }
  } else {
    point* p = clickRangedPointOrNull(pos, removeSpineIndex, removePointIndex);
    if (p == nullptr) return;
    removedPoint.push({currentSpine, currentPointCount});
    currentSpine = removeSpineIndex;
    currentPointCount = removePointIndex;

    scene()->removeItem((QGraphicsItem*)p->item);
    initSpinePoint(p);
  }
  update();
}

point* View::clickRangedPointOrNull(const QPointF& pos, int& outCurrentSpine,
                                    int& outCurrentPoint) {
  for (int i = 0; i < spineCount; ++i) {
    for (int j = 0; j < pointCountForOneSpine; ++j) {
      qreal x = spinePoint[i][j].position.x();
      qreal y = spinePoint[i][j].position.y();
      if ((x - clickRangeWidth <= pos.x() && pos.x() <= x + clickRangeWidth) &&
          (y - clickRangeWidth <= pos.y() && pos.y() <= y + clickRangeWidth)) {
        outCurrentSpine = i;
        outCurrentPoint = j;
        return &spinePoint[i][j];
      }
    }
  }
  return nullptr;
}