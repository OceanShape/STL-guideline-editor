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
  Screen scr;
  Mode currentMode = Mode::BASE_LINE;

 public:
  View::~View();
  explicit View(QWidget* parent = nullptr);
  virtual void drawPelvisORTailbonePoint(const QPointF& pos,
                                         const Qt::MouseButton& btn){};
  QPointF getBasePoint() {
    return {baseLine[BaseLineType::VERTICAL]->line().p1().x(),
            baseLine[BaseLineType::HORIZONTAL]->line().p1().y()};
  }
  QPointF getSpinePoint(int spineIdx, int pointIdx) {
    return spinePoint[spineIdx][pointIdx].position;
  }
  QPointF getSpinousProcessPoint(int spineIdx) {
    return spinousProcessPoint[spineIdx].position;
  }
  void resetPenSetting();
  void initPoint(point* p);
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

 public slots:
 protected:
  BaseLineStatus baseLineStatus;
  QGraphicsLineItem* baseLine[baseLineCount];

  point spinePoint[spineCount][pointCountForOneSpine];
  QGraphicsLineItem* spineLine[spineCount][pointCountForOneSpine];
  QPointF spineCenter[spineCount];
  int currentSpine;
  int currentSpinePoint;
  std::stack<std::pair<int, int>> removedSpinePoint;
  point spinousProcessPoint[spinousProcessPointCount];
  int currentSpinousProcessPoint;
  std::stack<int> removedSpinousProcessPoint;

  QPen* pen;
  QBrush* brush;
};
#endif  // VIEW_H
