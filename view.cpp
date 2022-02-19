#include "View.h"

void View::resetPenSetting() {
  gs.pen[scr]->setWidth(10);
  gs.pen[scr]->setColor(Qt::green);
  gs.pen[scr]->setStyle(Qt::SolidLine);
}

void View::mousePressEvent(QMouseEvent* event) {
  QPointF pos = mapToScene(event->pos());
  Qt::MouseButton btn = event->button();

  if (currentMode == Mode::BASE_LINE) {
    drawBaseLine(pos, btn);
  } else if (currentMode == Mode::SPINE) {
    drawSpinePoint(pos, btn);
  } else if (currentMode == Mode::SPINOUS_PROCESS) {
    drawSpinousProcessPoint(pos, btn);
  } else if (currentMode == Mode::PELVIS_OR_TAILBONE) {
    drawPelvisORTailbonePoint(pos, btn);
  }
  resetPenSetting();
  emit updateSignal();
}

void View::mouseMoveEvent(QMouseEvent* event) {
  moveBaseLine(mapToScene(event->pos()));
  emit updateSignal();
}

void View::mouseReleaseEvent(QMouseEvent* event) {
  releaseBaseLine(mapToScene(event->pos()));
  emit updateSignal();
}

void View::redrawBaseLine(const QPointF& pos,
                          const BaseLineType& baseLineType) {
  QLineF tmpLine = gs.baseLine[scr][baseLineType]->line();
  scene()->removeItem(gs.baseLine[scr][baseLineType]);

  if (baseLineType == BaseLineType::VERTICAL) {
    tmpLine.setP1({pos.x(), tmpLine.y1()});
    tmpLine.setP2({pos.x(), tmpLine.y2()});
    setCursor(Qt::SizeHorCursor);
  } else if (baseLineType == BaseLineType::HORIZONTAL) {
    tmpLine.setP1({tmpLine.x1(), pos.y()});
    tmpLine.setP2({tmpLine.x2(), pos.y()});
    gs.pen[scr]->setColor(Qt::red);
    gs.pen[scr]->setStyle(Qt::DotLine);
    setCursor(Qt::SizeVerCursor);
  }
  gs.baseLine[scr][baseLineType] = scene()->addLine(tmpLine, *gs.pen[scr]);
  resetPenSetting();
}

void View::drawDefaultBaseLine(const QPointF& pos) {
  gs.baseLine[scr][BaseLineType::VERTICAL] = scene()->addLine(
      pos.x(), 0 + 10, pos.x(), static_cast<qreal>(4480 - 10), *gs.pen[scr]);

  gs.pen[scr]->setColor(Qt::red);
  gs.pen[scr]->setStyle(Qt::DotLine);

  gs.baseLine[scr][BaseLineType::HORIZONTAL] = scene()->addLine(
      0 + 10, pos.y(), static_cast<qreal>(3600 - 10), pos.y(), *gs.pen[scr]);
  gs.baseLineStatus[scr] = BaseLineStatus::NOT_SELECTED;

  resetPenSetting();
}

void View::drawBaseLine(const QPointF& pos, const Qt::MouseButton& btn) {
  if (btn == Qt::LeftButton &&
      gs.baseLineStatus[scr] == BaseLineStatus::NOT_SELECTED) {
    BaseLineType clickedBaseLineType = clickRangedBaseLine(pos);
    if (clickedBaseLineType != BaseLineType::NONE) {
      redrawBaseLine(pos, clickedBaseLineType);
      gs.baseLineStatus[scr] = (clickedBaseLineType == BaseLineType::VERTICAL)
                                   ? BaseLineStatus::MOVE_VERTICAL
                                   : BaseLineStatus::MOVE_HORIZONTAL;
    }
  }
}

void View::moveBaseLine(const QPointF& pos) {
  if (gs.baseLineStatus[scr] == BaseLineStatus::MOVE_VERTICAL ||
      gs.baseLineStatus[scr] == BaseLineStatus::MOVE_HORIZONTAL) {
    BaseLineType baseLineType =
        (gs.baseLineStatus[scr] == BaseLineStatus::MOVE_VERTICAL)
            ? BaseLineType::VERTICAL
            : BaseLineType::HORIZONTAL;
    redrawBaseLine(pos, baseLineType);
  }
}

void View::releaseBaseLine(const QPointF& pos) {
  if (gs.baseLineStatus[scr] == BaseLineStatus::MOVE_VERTICAL ||
      gs.baseLineStatus[scr] == BaseLineStatus::MOVE_HORIZONTAL) {
    BaseLineType baseLineType =
        (gs.baseLineStatus[scr] == BaseLineStatus::MOVE_VERTICAL)
            ? BaseLineType::VERTICAL
            : BaseLineType::HORIZONTAL;
    redrawBaseLine(pos, baseLineType);
    setCursor(Qt::ArrowCursor);
    gs.baseLineStatus[scr] = BaseLineStatus::NOT_SELECTED;
  }
}

void View::removeAllSpineLine() {
  for (int i = 0; i < SPINE_COUNT; ++i)
    for (int j = 0; j < POINT_COUNT_FOR_ONE_SPINE; ++j)
      if (gs.spineLine[i][j] != nullptr) {
        scene()->removeItem(gs.spineLine[scr][i][j]);
        gs.spineLine[scr][i][j] = nullptr;
      }
}

bool View::isPointInvalid(const point& p) {
  return (p.position.x() <= static_cast<qreal>(-4480)) ||
         (p.position.y() <= static_cast<qreal>(-3600));
}

void View::drawSpineLine() {
  removeAllSpineLine();

  // Redraw all line
  for (int i = 0; i < SPINE_COUNT; ++i) {
    bool isAllPointSet = true;
    for (int j = 0; j < POINT_COUNT_FOR_ONE_SPINE; ++j) {
      if (isPointInvalid(gs.spinePoint[scr][i][j])) {
        isAllPointSet = false;
      }
    }

    if (isAllPointSet) {
      // Sort all point
      point tmp[POINT_COUNT_FOR_ONE_SPINE];

      for (int j = 0; j < POINT_COUNT_FOR_ONE_SPINE; ++j) {
        int rightPointCount = 0;
        int downPointCount = 0;
        for (int k = 0; k < POINT_COUNT_FOR_ONE_SPINE; ++k) {
          if (j == k) continue;
          if (gs.spinePoint[scr][i][j].position.x() <
              gs.spinePoint[scr][i][k].position.x())
            ++rightPointCount;
          if (gs.spinePoint[scr][i][j].position.y() <
              gs.spinePoint[scr][i][k].position.y())
            ++downPointCount;
        }
        if (rightPointCount >= 2) {
          if (downPointCount >= 2)
            tmp[0] = gs.spinePoint[scr][i][j];
          else
            tmp[3] = gs.spinePoint[scr][i][j];
        } else {
          if (downPointCount >= 2)
            tmp[1] = gs.spinePoint[scr][i][j];
          else
            tmp[2] = gs.spinePoint[scr][i][j];
        }
      }

      for (int j = 0; j < POINT_COUNT_FOR_ONE_SPINE; ++j)
        gs.spinePoint[scr][i][j] = tmp[j];

      // Draw line
      gs.pen[scr]->setWidth(7);
      for (int j = 0; j < POINT_COUNT_FOR_ONE_SPINE; ++j) {
        gs.spineLine[scr][i][j] = scene()->addLine(
            gs.spinePoint[scr][i][j].position.x() + CLICK_CORRECTION_WIDTH,
            gs.spinePoint[scr][i][j].position.y() + CLICK_CORRECTION_WIDTH,
            gs.spinePoint[scr][i][(j + 1) % 4].position.x() +
                CLICK_CORRECTION_WIDTH,
            gs.spinePoint[scr][i][(j + 1) % 4].position.y() +
                CLICK_CORRECTION_WIDTH,
            *gs.pen[scr]);
      }

      qreal x = 0, y = 0;
      for (int j = 0; j < POINT_COUNT_FOR_ONE_SPINE; ++j) {
        x += gs.spinePoint[scr][i][j].position.x();
        y += gs.spinePoint[scr][i][j].position.y();
      }
      gs.spineCenter[scr][i] = {x / 4, y / 4};
    }
  }
}

void View::drawSpinePoint(QPointF pos, const Qt::MouseButton& btn) {
  int removeSpineIndex, removePointIndex;
  pos.setX(pos.x() - CLICK_CORRECTION_WIDTH);
  pos.setY(pos.y() - CLICK_CORRECTION_WIDTH);
  if (btn == Qt::LeftButton) {
    if (gs.currentSpine[scr] >= SPINE_COUNT) return;
    if (clickRangedPointOrNull(pos, removeSpineIndex, removePointIndex) !=
        nullptr)
      return;

    gs.pen[scr]->setWidth(10);
    gs.spinePoint[scr][gs.currentSpine[scr]][gs.currentSpinePoint[scr]] = {
        scene()->addEllipse(pos.x(), pos.y(), POINT_RADIUS, POINT_RADIUS,
                            *gs.pen[scr], *gs.brush[scr]),
        pos};

    if (gs.removedSpinePoint[scr].empty() == false) {
      auto t = gs.removedSpinePoint[scr].top();
      gs.removedSpinePoint[scr].pop();
      gs.currentSpine[scr] = t.first;
      gs.currentSpinePoint[scr] = t.second;
    } else {
      ++gs.currentSpinePoint[scr];
      if (gs.currentSpinePoint[scr] == 4) {
        gs.currentSpinePoint[scr] = 0;
        ++gs.currentSpine[scr];
      }
    }
  } else {
    point* p = clickRangedPointOrNull(pos, removeSpineIndex, removePointIndex);
    if (p == nullptr) return;
    gs.removedSpinePoint[scr].push(
        {gs.currentSpine[scr], gs.currentSpinePoint[scr]});
    gs.currentSpine[scr] = removeSpineIndex;
    gs.currentSpinePoint[scr] = removePointIndex;

    scene()->removeItem((QGraphicsItem*)p->item);
    GlobalState::initPoint(p);
  }
  drawSpineLine();
  resetPenSetting();
}

point* View::clickRangedPointOrNull(const QPointF& pos, int& outCurrentSpine,
                                    int& outCurrentPoint) {
  for (int i = 0; i < SPINE_COUNT; ++i) {
    for (int j = 0; j < POINT_COUNT_FOR_ONE_SPINE; ++j) {
      qreal x = gs.spinePoint[scr][i][j].position.x();
      qreal y = gs.spinePoint[scr][i][j].position.y();
      if ((x - CLICK_RANGE_WIDTH <= pos.x() &&
           pos.x() <= x + CLICK_RANGE_WIDTH) &&
          (y - CLICK_RANGE_WIDTH <= pos.y() &&
           pos.y() <= y + CLICK_RANGE_WIDTH)) {
        outCurrentSpine = i;
        outCurrentPoint = j;
        return &gs.spinePoint[scr][i][j];
      }
    }
  }
  return nullptr;
}

BaseLineType View::clickRangedBaseLine(const QPointF& pos) {
  qreal x = gs.baseLine[scr][BaseLineType::VERTICAL]->line().x1();
  qreal y = gs.baseLine[scr][BaseLineType::HORIZONTAL]->line().y1();

  if (x - CLICK_RANGE_WIDTH <= pos.x() && pos.x() <= x + CLICK_RANGE_WIDTH) {
    return BaseLineType::VERTICAL;
  } else if (y - CLICK_RANGE_WIDTH <= pos.y() &&
             pos.y() <= y + CLICK_RANGE_WIDTH) {
    return BaseLineType::HORIZONTAL;
  }

  return BaseLineType::NONE;
}

void View::sortSpinousProcessPoint() {
  bool isAllPointSet = true;
  for (int i = 0; i < SPINOUS_PROCESS_POINT_COUNT; ++i) {
    if (isPointInvalid(gs.spinousProcessPoint[scr][i])) {
      isAllPointSet = false;
    }
  }

  if (isAllPointSet) {
    for (int i = 0; i < SPINOUS_PROCESS_POINT_COUNT; ++i) {
      for (int j = 0; j < SPINOUS_PROCESS_POINT_COUNT - (i + 1); ++j) {
        if (gs.spinousProcessPoint[scr][j].position.y() >
            gs.spinousProcessPoint[scr][j + 1].position.y()) {
          point tmp;
          tmp = gs.spinousProcessPoint[scr][j + 1];
          gs.spinousProcessPoint[scr][j + 1] = gs.spinousProcessPoint[scr][j];
          gs.spinousProcessPoint[scr][j] = tmp;
        }
      }
    }
  }
}

void View::drawSpinousProcessPoint(QPointF pos, const Qt::MouseButton& btn) {
  int removePointIndex;
  pos.setX(pos.x() - CLICK_CORRECTION_WIDTH);
  pos.setY(pos.y() - CLICK_CORRECTION_WIDTH);

  if (btn == Qt::LeftButton) {
    if (gs.currentSpinousProcessPoint[scr] >= SPINOUS_PROCESS_POINT_COUNT)
      return;
    if (clickRangedSpinousProcessPointOrNull(pos, removePointIndex) != nullptr)
      return;

    gs.pen[scr]->setColor(Qt::yellow);
    gs.spinousProcessPoint[scr][gs.currentSpinousProcessPoint[scr]] = {
        scene()->addEllipse(pos.x(), pos.y(), POINT_RADIUS, POINT_RADIUS,
                            *gs.pen[scr], *gs.brush[scr]),
        pos};

    if (gs.removedSpinousProcessPoint[scr].empty() == false) {
      int t = gs.removedSpinousProcessPoint[scr].top();
      gs.removedSpinousProcessPoint[scr].pop();
      gs.currentSpinousProcessPoint[scr] = t;
    } else {
      ++gs.currentSpinousProcessPoint[scr];
    }
  } else {
    point* p = clickRangedSpinousProcessPointOrNull(pos, removePointIndex);
    if (p == nullptr) return;
    gs.removedSpinousProcessPoint[scr].push(gs.currentSpinousProcessPoint[scr]);
    gs.currentSpinousProcessPoint[scr] = removePointIndex;

    scene()->removeItem((QGraphicsItem*)p->item);
    GlobalState::initPoint(p);
  }
  sortSpinousProcessPoint();
  resetPenSetting();
}

point* View::clickRangedSpinousProcessPointOrNull(const QPointF& pos,
                                                  int& outCurrentPoint) {
  for (int i = 0; i < SPINOUS_PROCESS_POINT_COUNT; ++i) {
    qreal x = gs.spinousProcessPoint[scr][i].position.x();
    qreal y = gs.spinousProcessPoint[scr][i].position.y();
    if ((x - CLICK_RANGE_WIDTH <= pos.x() &&
         pos.x() <= x + CLICK_RANGE_WIDTH) &&
        (y - CLICK_RANGE_WIDTH <= pos.y() &&
         pos.y() <= y + CLICK_RANGE_WIDTH)) {
      outCurrentPoint = i;
      return &gs.spinousProcessPoint[scr][i];
    }
  }
  return nullptr;
}
