#include "ViewAP.h"

void ViewAP::removeAllPelvisLine() {
  if (gs.pelvisLine != nullptr) {
    scene()->removeItem(gs.pelvisLine);
    gs.pelvisLine = nullptr;
  }
}

void ViewAP::drawPelvisLine() {
  removeAllPelvisLine();

  bool isAllPointSet = true;
  for (int i = 0; i < pelvisPointCount; ++i) {
    if (isPointInvalid(gs.pelvisPoint[i])) {
      isAllPointSet = false;
    }
  }

  if (isAllPointSet) {
    point tmp;

    if (gs.pelvisPoint[0].position.x() > gs.pelvisPoint[1].position.x()) {
      tmp = gs.pelvisPoint[0];
      gs.pelvisPoint[0] = gs.pelvisPoint[1];
      gs.pelvisPoint[1] = tmp;
    }

    // ¼± ±ß±â
    gs.pen[scr]->setWidth(7);
    gs.pelvisLine = scene()->addLine(
      gs.pelvisPoint[0].position.x() + clickCorrectionWidth,
      gs.pelvisPoint[0].position.y() + clickCorrectionWidth,
      gs.pelvisPoint[1].position.x() + clickCorrectionWidth,
      gs.pelvisPoint[1].position.y() + clickCorrectionWidth, *gs.pen[scr]);
  }

  gs.pelvisCenter = {
      (gs.pelvisPoint[0].position.x() + gs.pelvisPoint[1].position.x()) / 2,
      (gs.pelvisPoint[0].position.y() + gs.pelvisPoint[1].position.y()) / 2};
}

void ViewAP::drawPelvisPoint(QPointF pos, const Qt::MouseButton& btn) {
  int removePointIndex;
  pos.setX(pos.x() - clickCorrectionWidth);
  pos.setY(pos.y() - clickCorrectionWidth);

  if (btn == Qt::LeftButton) {
    if (gs.currentPelvisPoint >= pelvisPointCount) return;
    if (clickRangedPelvisPointOrNull(pos, removePointIndex) != nullptr) return;

    gs.pen[scr]->setColor(Qt::blue);
    gs.pelvisPoint[gs.currentPelvisPoint] = {
        scene()->addEllipse(pos.x(), pos.y(), pointRadius, pointRadius,
                            *gs.pen[scr], *gs.brush[scr]),
        pos};

    if (gs.removedPelvisPoint.empty() == false) {
      int t = gs.removedPelvisPoint.top();
      gs.removedPelvisPoint.pop();
      gs.currentPelvisPoint = t;
    } else {
      ++gs.currentPelvisPoint;
    }
  } else {
    point* p = clickRangedPelvisPointOrNull(pos, removePointIndex);
    if (p == nullptr) return;
    gs.removedPelvisPoint.push(gs.currentPelvisPoint);
    gs.currentPelvisPoint = removePointIndex;

    scene()->removeItem((QGraphicsItem*)p->item);
    GlobalState::initPoint(p);
  }
  drawPelvisLine();
  resetPenSetting();
}

point* ViewAP::clickRangedPelvisPointOrNull(const QPointF& pos,
                                            int& outCurrentPoint) {
  for (int i = 0; i < pelvisPointCount; ++i) {
    qreal x = gs.pelvisPoint[i].position.x();
    qreal y = gs.pelvisPoint[i].position.y();
    if ((x - clickRangeWidth <= pos.x() && pos.x() <= x + clickRangeWidth) &&
        (y - clickRangeWidth <= pos.y() && pos.y() <= y + clickRangeWidth)) {
      outCurrentPoint = i;
      return &gs.pelvisPoint[i];
    }
  }
  return nullptr;
}
