#pragma once

#ifndef VIEW_H
#define VIEW_H

#include <QGraphicsEllipseItem>
#include <QGraphicsView>
#include <QMouseEvent>
#include <QPoint>
#include <QtMath>
#include <stack>

#include "BaseLineStatus.h"
#include "BaseLineType.h"
#include "GlobalState.h"
#include "Mode.h"

class View : public QGraphicsView {
  Q_OBJECT
 public:
  GlobalState& gs = GlobalState::getIncetance();
  Screen scr = SCR::AP;
  Mode currentMode = Mode::BASE_LINE;

 public:
  View::~View(){};
  explicit View(QWidget* parent = nullptr){};
  virtual void drawPelvisORTailbonePoint(const QPointF& pos,
                                         const Qt::MouseButton& btn){};
  QPointF getBasePoint() {
    return {gs.baseLine[scr][BaseLineType::VERTICAL]->line().p1().x(),
            gs.baseLine[scr][BaseLineType::HORIZONTAL]->line().p1().y()};
  }
  QPointF getSpinePoint(int spineIdx, int pointIdx) {
    return gs.spinePoint[scr][spineIdx][pointIdx].position;
  }
  QPointF getSpinousProcessPoint(int spineIdx) {
    return gs.spinousProcessPoint[scr][spineIdx].position;
  }
  void resetPenSetting();
  bool isPointInvalid(const point& p);
  point* clickRangedPointOrNull(const QPointF& pos, int& outCurrentSpine,
                                int& outCurrentPoint);
  BaseLineType clickRangedBaseLine(const QPointF& pos);
  void mousePressEvent(QMouseEvent* event) override;
  void mouseReleaseEvent(QMouseEvent* event) override;
  void mouseMoveEvent(QMouseEvent* event) override;
  void drawDefaultBaseLine(const QPointF& pos);
  void drawBaseLine(const QPointF& pos, const Qt::MouseButton& btn);
  void moveBaseLine(const QPointF& pos);
  void releaseBaseLine(const QPointF& pos);
  void redrawBaseLine(const QPointF& pos, const BaseLineType& baseLineType);
  void drawSpinePoint(QPointF pos, const Qt::MouseButton& btn);
  void drawSpineLine();
  void removeAllSpineLine();
  void sortSpinousProcessPoint();
  point* clickRangedSpinousProcessPointOrNull(const QPointF& pos,
                                              int& outCurrentPoint);
  void drawSpinousProcessPoint(QPointF pos, const Qt::MouseButton& btn);

 signals:
  void updateSignal();
};
#endif  // VIEW_H
