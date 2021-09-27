#include "ViewAP.h"

ViewAP::ViewAP(QWidget* parent) : View(parent) {
  currentPelvisPoint = 0;
  currentSpinousProcessPoint = 0;

  for (int i = 0; i < pelvisPointCount; ++i) initPoint(&pelvisPoint[i]);
  for (int i = 0; i < spinousProcessPointCount; ++i)
    initPoint(&spinousProcessPoint[i]);

  pelvisCenter = {-FLT_MAX, -FLT_MAX};

  pelvisLine = nullptr;
}

void ViewAP::mousePressEvent(QMouseEvent* event) {
  QPointF pos = mapToScene(event->pos());
  Qt::MouseButton btn = event->button();

  if (currentMode == Mode::BASE_LINE) {
    drawBaseLine(pos, btn);
  } else if (currentMode == Mode::SPINE) {
    drawSpinePoint(pos, btn);
  } else if (currentMode == Mode::AP_PELVIS) {
    drawPelvisPoint(pos, btn);
  } else if (currentMode == Mode::AP_SPINOUS_PROCESS) {
    drawSpinousProcessPoint(pos, btn);
  }
  resetPenSetting();
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
    pen->setWidth(7);
    pelvisLine = scene()->addLine(
        pelvisPoint[0].position.x() + clickCorrectionWidth,
        pelvisPoint[0].position.y() + clickCorrectionWidth,
        pelvisPoint[1].position.x() + clickCorrectionWidth,
        pelvisPoint[1].position.y() + clickCorrectionWidth, *pen);
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

    pen->setColor(Qt::blue);
    pelvisPoint[currentPelvisPoint] = {
        scene()->addEllipse(pos.x(), pos.y(), pointRadius, pointRadius, *pen,
                            *brush),
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
    initPoint(p);
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

void ViewAP::sortSpinousProcessPoint() {

  bool isAllPointSet = true;
  for (int i = 0; i < spinousProcessPointCount; ++i) {
    if (isPointInvalid(spinousProcessPoint[i])) {
      isAllPointSet = false;
    }
  }

  if (isAllPointSet) {
    for (int i = 0; i < spinousProcessPointCount; ++i) {
      for (int j = 0; j < spinousProcessPointCount - (i + 1); ++j) {
        if (spinousProcessPoint[j].position.y() >
          spinousProcessPoint[j + 1].position.y()) {
          point tmp;
          tmp = spinousProcessPoint[j+1];
          spinousProcessPoint[j+1] = spinousProcessPoint[j];
          spinousProcessPoint[j] = tmp;
        }
      }
    }
  }
}

void ViewAP::drawSpinousProcessPoint(QPointF pos, const Qt::MouseButton& btn) {
  int removePointIndex;
  pos.setX(pos.x() - clickCorrectionWidth);
  pos.setY(pos.y() - clickCorrectionWidth);

  if (btn == Qt::LeftButton) {
    if (currentSpinousProcessPoint >= spinousProcessPointCount) return;
    if (clickRangedSpinousProcessPointOrNull(pos, removePointIndex) != nullptr)
      return;

    pen->setColor(Qt::yellow);
    spinousProcessPoint[currentSpinousProcessPoint] = {
    scene()->addEllipse(pos.x(), pos.y(), pointRadius, pointRadius, *pen,
                        *brush),
    pos };

    if (removedSpinousProcessPoint.empty() == false) {
      int t = removedSpinousProcessPoint.top();
      removedSpinousProcessPoint.pop();
      currentSpinousProcessPoint = t;
    } else {
      ++currentSpinousProcessPoint;
    }
  } else {
    point* p = clickRangedSpinousProcessPointOrNull(pos, removePointIndex);
    if (p == nullptr) return;
    removedSpinousProcessPoint.push(currentSpinousProcessPoint);
    currentSpinousProcessPoint = removePointIndex;

    scene()->removeItem((QGraphicsItem*)p->item);
    initPoint(p);
  }
  sortSpinousProcessPoint();
  resetPenSetting();
}

point* ViewAP::clickRangedSpinousProcessPointOrNull(const QPointF& pos,
                                                    int& outCurrentPoint) {
  for (int i = 0; i < spinousProcessPointCount; ++i) {
    qreal x = spinousProcessPoint[i].position.x();
    qreal y = spinousProcessPoint[i].position.y();
    if ((x - clickRangeWidth <= pos.x() && pos.x() <= x + clickRangeWidth) &&
        (y - clickRangeWidth <= pos.y() && pos.y() <= y + clickRangeWidth)) {
      outCurrentPoint = i;
      return &spinousProcessPoint[i];
    }
  }
  return nullptr;
}