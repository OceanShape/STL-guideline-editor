#include "ViewLAT.h"

ViewLAT::ViewLAT(QWidget* parent) : View(parent) {
  currentTailbonePoint = 0;
  currentTailbonePoint = 0;

  for (int i = 0; i < tailbonePointCount; ++i) initPoint(&tailbonePoint[i]);
  for (int i = 0; i < tailbonePointCount; ++i) tailboneLine[i] = nullptr;
}

void ViewLAT::removeAllTailboneLine() {
  for (int i = 0; i < tailbonePointCount; ++i)
    if (tailboneLine[i] != nullptr) {
      scene()->removeItem(tailboneLine[i]);
      tailboneLine[i] = nullptr;
    }
}

void ViewLAT::drawTailboneLine() {
  removeAllTailboneLine();

  bool isAllPointSet = true;
  for (int i = 0; i < tailbonePointCount; ++i) {
    if (isPointInvalid(tailbonePoint[i])) {
      isAllPointSet = false;
    }
  }

  if (isAllPointSet) {
    for (int i = 0; i < tailbonePointCount; ++i) {
      for (int j = 0; j < tailbonePointCount - (i + 1); ++j) {
        if (tailbonePoint[j].position.y() >
          tailbonePoint[j + 1].position.y()) {
          point tmp;
          tmp = tailbonePoint[j + 1];
          tailbonePoint[j + 1] = tailbonePoint[j];
          tailbonePoint[j] = tmp;
        }
      }
    }

    // ¼± ±ß±â
    pen->setWidth(7);
    for (int i = 0; i < tailbonePointCount; ++i) {
      tailboneLine[i] = scene()->addLine(
        tailbonePoint[i].position.x() + clickCorrectionWidth,
        tailbonePoint[i].position.y() + clickCorrectionWidth,
        tailbonePoint[(i + 1) % 3].position.x() + clickCorrectionWidth,
        tailbonePoint[(i + 1) % 3].position.y() + clickCorrectionWidth,
        *pen);
    }
  }
}

void ViewLAT::drawTailbonePoint(QPointF pos, const Qt::MouseButton& btn) {
  int removePointIndex;
  pos.setX(pos.x() - clickCorrectionWidth);
  pos.setY(pos.y() - clickCorrectionWidth);

  if (btn == Qt::LeftButton) {
    if (currentTailbonePoint >= tailbonePointCount) return;
    if (clickRangedTailbonePointOrNull(pos, removePointIndex) != nullptr)
      return;

    pen->setColor(Qt::blue);
    tailbonePoint[currentTailbonePoint] = {
    scene()->addEllipse(pos.x(), pos.y(), pointRadius, pointRadius, *pen,
                        *brush),
    pos };

    if (removedTailbonePoint.empty() == false) {
      int t = removedTailbonePoint.top();
      removedTailbonePoint.pop();
      currentTailbonePoint = t;
    }
    else {
      ++currentTailbonePoint;
    }
  }
  else {
    point* p = clickRangedTailbonePointOrNull(pos, removePointIndex);
    if (p == nullptr) return;
    removedTailbonePoint.push(currentTailbonePoint);
    currentTailbonePoint = removePointIndex;

    scene()->removeItem((QGraphicsItem*)p->item);
    initPoint(p);
  }
  drawTailboneLine();
  resetPenSetting();
}

point* ViewLAT::clickRangedTailbonePointOrNull(const QPointF& pos,
                                               int& outCurrentPoint) {
  for (int i = 0; i < tailbonePointCount; ++i) {
    qreal x = tailbonePoint[i].position.x();
    qreal y = tailbonePoint[i].position.y();
    if ((x - clickRangeWidth <= pos.x() && pos.x() <= x + clickRangeWidth) &&
      (y - clickRangeWidth <= pos.y() && pos.y() <= y + clickRangeWidth)) {
      outCurrentPoint = i;
      return &tailbonePoint[i];
    }
  }
  return nullptr;
}