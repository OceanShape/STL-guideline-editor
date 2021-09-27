#include "View.h"

View::View(QWidget* parent) : QGraphicsView(parent) {
  // baseline 초기화
  isBaseLineDrawn = false;
  baseLineStatus = BaseLineStatus::NOT_DRAWN;
  for (int i = 0; i < baseLineCount; ++i) baseLine[i] = nullptr;

  // spine 초기화
  currentSpine = 0;
  currentSpinePoint = 0;

  for (int i = 0; i < spineCount; ++i) {
    for (int j = 0; j < pointCountForOneSpine; ++j) {
      initPoint(&spinePoint[i][j]);
    }

    spineCenter[i] = {-FLT_MAX, -FLT_MAX};

    for (int j = 0; j < pointCountForOneSpine; ++j) spineLine[i][j] = nullptr;
  }

  // pen,brush 설정 초기화
  pen = new QPen(Qt::green);
  pen->setWidth(10);
  brush = new QBrush(Qt::white);
}

View::~View() {
  delete pen;
  delete brush;
}

void View::resetPenSetting() {
  pen->setWidth(10);
  pen->setColor(Qt::green);
  pen->setStyle(Qt::SolidLine);
}

void View::initPoint(point* p) {
  p->position = {-FLT_MAX, -FLT_MAX};
  p->item = nullptr;
}

void View::mouseMoveEvent(QMouseEvent* event) {
  moveBaseLine(mapToScene(event->pos()));
}

void View::mouseReleaseEvent(QMouseEvent* event) {
  releaseBaseLine(mapToScene(event->pos()));
}

void View::keyPressEvent(QKeyEvent* event) {
  if (event->key() == Qt::Key_1)
    currentMode = Mode::BASE_LINE;
  else if (event->key() == Qt::Key_2)
    currentMode = Mode::SPINE;
  else if (event->key() == Qt::Key_3)
    currentMode = Mode::AP_PELVIS;
  else if (event->key() == Qt::Key_4)
    currentMode = Mode::AP_SPINOUS_PROCESS;
  else if (event->key() == Qt::Key_5)
    currentMode = Mode::LAT_TAILBONE;
}

void View::redrawBaseLine(const QPointF& pos,
                          const BaseLineType& baseLineType) {
  QLineF tmpLine = baseLine[baseLineType]->line();
  scene()->removeItem(baseLine[baseLineType]);

  if (baseLineType == BaseLineType::VERTICAL) {
    tmpLine.setP1({pos.x(), tmpLine.y1()});
    tmpLine.setP2({pos.x(), tmpLine.y2()});
  } else if (baseLineType == BaseLineType::HORIZONTAL) {
    tmpLine.setP1({tmpLine.x1(), pos.y()});
    tmpLine.setP2({tmpLine.x2(), pos.y()});
    pen->setColor(Qt::red);
    pen->setStyle(Qt::DotLine);
  }
  baseLine[baseLineType] = scene()->addLine(tmpLine, *pen);
  resetPenSetting();
}

void View::drawBaseLine(const QPointF& pos, const Qt::MouseButton& btn) {
  if (btn == Qt::LeftButton) {
    if (baseLineStatus == BaseLineStatus::NOT_DRAWN) {
      baseLine[BaseLineType::VERTICAL] = scene()->addLine(
          pos.x(), 0 + 10, pos.x(), static_cast<qreal>(4480 - 10), *pen);

      pen->setColor(Qt::red);
      pen->setStyle(Qt::DotLine);

      baseLine[BaseLineType::HORIZONTAL] = scene()->addLine(
          0 + 10, pos.y(), static_cast<qreal>(3600 - 10), pos.y(), *pen);
      baseLineStatus = BaseLineStatus::NOT_SELECTED;
    } else if (baseLineStatus == BaseLineStatus::NOT_SELECTED) {
      BaseLineType clickedBaseLineType = clickRangedBaseLine(pos);
      if (clickedBaseLineType != BaseLineType::NONE) {
        redrawBaseLine(pos, clickedBaseLineType);
        baseLineStatus = (clickedBaseLineType == BaseLineType::VERTICAL)
                             ? BaseLineStatus::MOVE_VERTICAL
                             : BaseLineStatus::MOVE_HORIZONTAL;
      }
    }
  }
}

void View::moveBaseLine(const QPointF& pos) {
  if (baseLineStatus == BaseLineStatus::MOVE_VERTICAL ||
      baseLineStatus == BaseLineStatus::MOVE_HORIZONTAL) {
    BaseLineType baseLineType =
        (baseLineStatus == BaseLineStatus::MOVE_VERTICAL)
            ? BaseLineType::VERTICAL
            : BaseLineType::HORIZONTAL;
    redrawBaseLine(pos, baseLineType);
  }
}

void View::releaseBaseLine(const QPointF& pos) {
  if (baseLineStatus == BaseLineStatus::MOVE_VERTICAL ||
      baseLineStatus == BaseLineStatus::MOVE_HORIZONTAL) {
    BaseLineType baseLineType =
        (baseLineStatus == BaseLineStatus::MOVE_VERTICAL)
            ? BaseLineType::VERTICAL
            : BaseLineType::HORIZONTAL;
    redrawBaseLine(pos, baseLineType);
    baseLineStatus = BaseLineStatus::NOT_SELECTED;
  }
}

void View::removeAllSpineLine() {
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
  removeAllSpineLine();

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
    spinePoint[currentSpine][currentSpinePoint] = {
        scene()->addEllipse(pos.x(), pos.y(), pointRadius, pointRadius, *pen,
                            *brush),
        pos};

    if (removedSpinePoint.empty() == false) {
      auto t = removedSpinePoint.top();
      removedSpinePoint.pop();
      currentSpine = t.first;
      currentSpinePoint = t.second;
    } else {
      ++currentSpinePoint;
      if (currentSpinePoint == 4) {
        currentSpinePoint = 0;
        ++currentSpine;
      }
    }
  } else {
    point* p = clickRangedPointOrNull(pos, removeSpineIndex, removePointIndex);
    if (p == nullptr) return;
    removedSpinePoint.push({currentSpine, currentSpinePoint});
    currentSpine = removeSpineIndex;
    currentSpinePoint = removePointIndex;

    scene()->removeItem((QGraphicsItem*)p->item);
    initPoint(p);
  }
  drawSpineLine();
  resetPenSetting();
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

BaseLineType View::clickRangedBaseLine(const QPointF& pos) {
  qreal x = baseLine[BaseLineType::VERTICAL]->line().x1();
  qreal y = baseLine[BaseLineType::HORIZONTAL]->line().y1();

  if (x - clickRangeWidth <= pos.x() && pos.x() <= x + clickRangeWidth) {
    return BaseLineType::VERTICAL;
  } else if (y - clickRangeWidth <= pos.y() && pos.y() <= y + clickRangeWidth) {
    return BaseLineType::HORIZONTAL;
  }

  return BaseLineType::NONE;
}