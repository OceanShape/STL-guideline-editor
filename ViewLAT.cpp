#include "ViewLAT.h"

void ViewLAT::removeAllTailboneLine() {
  for (int i = 0; i < TAILBONE_POINT_COUNT; ++i)
    if (gs.tailboneLine[i] != nullptr) {
      scene()->removeItem(gs.tailboneLine[i]);
      gs.tailboneLine[i] = nullptr;
    }
}

void ViewLAT::drawTailboneLine() {
  removeAllTailboneLine();

  bool isAllPointSet = true;
  for (int i = 0; i < TAILBONE_POINT_COUNT; ++i) {
    if (isPointInvalid(gs.tailbonePoint[i])) {
      isAllPointSet = false;
    }
  }

  if (isAllPointSet) {
    for (int i = 0; i < TAILBONE_POINT_COUNT; ++i) {
      for (int j = 0; j < TAILBONE_POINT_COUNT - (i + 1); ++j) {
        if (gs.tailbonePoint[j].position.y() >
            gs.tailbonePoint[j + 1].position.y()) {
          point tmp;
          tmp = gs.tailbonePoint[j + 1];
          gs.tailbonePoint[j + 1] = gs.tailbonePoint[j];
          gs.tailbonePoint[j] = tmp;
        }
      }
    }

    // ¼± ±ß±â
    gs.pen[scr]->setWidth(7);
    for (int i = 0; i < TAILBONE_POINT_COUNT; ++i) {
      gs.tailboneLine[i] = scene()->addLine(
          gs.tailbonePoint[i].position.x() + CLICK_CORRECTION_WIDTH,
          gs.tailbonePoint[i].position.y() + CLICK_CORRECTION_WIDTH,
          gs.tailbonePoint[(i + 1) % 3].position.x() + CLICK_CORRECTION_WIDTH,
          gs.tailbonePoint[(i + 1) % 3].position.y() + CLICK_CORRECTION_WIDTH,
          *gs.pen[scr]);
    }
  }
}

void ViewLAT::drawTailbonePoint(QPointF pos, const Qt::MouseButton& btn) {
  int removePointIndex;
  pos.setX(pos.x() - CLICK_CORRECTION_WIDTH);
  pos.setY(pos.y() - CLICK_CORRECTION_WIDTH);

  if (btn == Qt::LeftButton) {
    if (gs.currentTailbonePoint >= TAILBONE_POINT_COUNT) return;
    if (clickRangedTailbonePointOrNull(pos, removePointIndex) != nullptr)
      return;

    gs.pen[scr]->setColor(Qt::blue);
    gs.tailbonePoint[gs.currentTailbonePoint] = {
        scene()->addEllipse(pos.x(), pos.y(), POINT_RADIUS, POINT_RADIUS,
                            *gs.pen[scr], *gs.brush[scr]),
        pos};

    if (gs.removedTailbonePoint.empty() == false) {
      int t = gs.removedTailbonePoint.top();
      gs.removedTailbonePoint.pop();
      gs.currentTailbonePoint = t;
    } else {
      ++gs.currentTailbonePoint;
    }
  } else {
    point* p = clickRangedTailbonePointOrNull(pos, removePointIndex);
    if (p == nullptr) return;
    gs.removedTailbonePoint.push(gs.currentTailbonePoint);
    gs.currentTailbonePoint = removePointIndex;

    scene()->removeItem((QGraphicsItem*)p->item);
    GlobalState::initPoint(p);
  }
  drawTailboneLine();
  resetPenSetting();
}

point* ViewLAT::clickRangedTailbonePointOrNull(const QPointF& pos,
                                               int& outCurrentPoint) {
  for (int i = 0; i < TAILBONE_POINT_COUNT; ++i) {
    qreal x = gs.tailbonePoint[i].position.x();
    qreal y = gs.tailbonePoint[i].position.y();
    if ((x - CLICK_RANGE_WIDTH <= pos.x() && pos.x() <= x + CLICK_RANGE_WIDTH) &&
        (y - CLICK_RANGE_WIDTH <= pos.y() && pos.y() <= y + CLICK_RANGE_WIDTH)) {
      outCurrentPoint = i;
      return &gs.tailbonePoint[i];
    }
  }
  return nullptr;
}
