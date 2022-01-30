#include "ViewAP.h"

ViewAP::ViewAP(QWidget* parent) : View(parent) {
  currentPelvisPoint = 0;
  for (int i = 0; i < pelvisPointCount; ++i) gs.initPoint(&pelvisPoint[i]);
  pelvisCenter = {-FLT_MAX, -FLT_MAX};
  pelvisLine = nullptr;
}

void ViewAP::removeAllPelvisLine() {
  if (pelvisLine != nullptr) {
    scene()->removeItem(pelvisLine);
    pelvisLine = nullptr;
  }
}

void ViewAP::drawPelvisLine() {
  removeAllPelvisLine();

  bool isAllPointSet = true;
  for (int i = 0; i < pelvisPointCount; ++i) {
    if (isPointInvalid(pelvisPoint[i])) {
      isAllPointSet = false;
    }
  }

  if (isAllPointSet) {
    point tmp;

    if (pelvisPoint[0].position.x() > pelvisPoint[1].position.x()) {
      tmp = pelvisPoint[0];
      pelvisPoint[0] = pelvisPoint[1];
      pelvisPoint[1] = tmp;
    }

    // ¼± ±ß±â
    gs.pen[scr]->setWidth(7);
    pelvisLine = scene()->addLine(
        pelvisPoint[0].position.x() + clickCorrectionWidth,
        pelvisPoint[0].position.y() + clickCorrectionWidth,
        pelvisPoint[1].position.x() + clickCorrectionWidth,
        pelvisPoint[1].position.y() + clickCorrectionWidth, *gs.pen[scr]);
  }

  pelvisCenter = {
      (pelvisPoint[0].position.x() + pelvisPoint[1].position.x()) / 2,
      (pelvisPoint[0].position.y() + pelvisPoint[1].position.y()) / 2};
}

void ViewAP::drawPelvisPoint(QPointF pos, const Qt::MouseButton& btn) {
  int removePointIndex;
  pos.setX(pos.x() - clickCorrectionWidth);
  pos.setY(pos.y() - clickCorrectionWidth);

  if (btn == Qt::LeftButton) {
    if (currentPelvisPoint >= pelvisPointCount) return;
    if (clickRangedPelvisPointOrNull(pos, removePointIndex) != nullptr) return;

    gs.pen[scr]->setColor(Qt::blue);
    pelvisPoint[currentPelvisPoint] = {
        scene()->addEllipse(pos.x(), pos.y(), pointRadius, pointRadius,
                            *gs.pen[scr], *gs.brush[scr]),
        pos};

    if (removedPelvisPoint.empty() == false) {
      int t = removedPelvisPoint.top();
      removedPelvisPoint.pop();
      currentPelvisPoint = t;
    } else {
      ++currentPelvisPoint;
    }
  } else {
    point* p = clickRangedPelvisPointOrNull(pos, removePointIndex);
    if (p == nullptr) return;
    removedPelvisPoint.push(currentPelvisPoint);
    currentPelvisPoint = removePointIndex;

    scene()->removeItem((QGraphicsItem*)p->item);
    gs.initPoint(p);
  }
  drawPelvisLine();
  resetPenSetting();
}

point* ViewAP::clickRangedPelvisPointOrNull(const QPointF& pos,
                                            int& outCurrentPoint) {
  for (int i = 0; i < pelvisPointCount; ++i) {
    qreal x = pelvisPoint[i].position.x();
    qreal y = pelvisPoint[i].position.y();
    if ((x - clickRangeWidth <= pos.x() && pos.x() <= x + clickRangeWidth) &&
        (y - clickRangeWidth <= pos.y() && pos.y() <= y + clickRangeWidth)) {
      outCurrentPoint = i;
      return &pelvisPoint[i];
    }
  }
  return nullptr;
}
