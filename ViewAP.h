#pragma once

#ifndef VIEWAP_H
#define VIEWAP_H

#include "View.h"

const int pelvisPointCount = 2;

class ViewAP : public View {
  Q_OBJECT
 public:
  explicit ViewAP(QWidget* parent = nullptr);

  void drawPelvisORTailbonePoint(const QPointF& pos,
                                 const Qt::MouseButton& btn) {
    drawPelvisPoint(pos, btn);
  }

  QPointF getPelvisPoint(int pointIdx) {
    return pelvisPoint[pointIdx].position;
  }

  qreal getPelvisAlpha() {
    return -atan2(pelvisPoint[1].position.y() - pelvisPoint[0].position.y(),
                  pelvisPoint[1].position.x() - pelvisPoint[0].position.x()) *
           180 / M_PI;
  }

  qreal getSpineRotateZ(int spineIdx) {
    qreal x1, y1, x2, y2;
    x1 = spineCenter[spineIdx].x();
    y1 = spineCenter[spineIdx].y();
    x2 = (spinePoint[spineIdx][1].position.x() +
          spinePoint[spineIdx][2].position.x()) /
         2;
    y2 = (spinePoint[spineIdx][1].position.y() +
          spinePoint[spineIdx][2].position.y()) /
         2;

    double dY = y2 - y1;
    double dX = x2 - x1;
    return -atan2(dY, dX) * 180 / M_PI;
  }

 signals:

 public slots:

 private:
  point* clickRangedPelvisPointOrNull(const QPointF& pos, int& outCurrentPoint);
  void drawPelvisPoint(QPointF pos, const Qt::MouseButton& btn);
  void drawPelvisLine();
  void removeAllPelvisLine();

 public:
  point pelvisPoint[pelvisPointCount];
  QGraphicsItem* pelvisLine;
  QPointF pelvisCenter;
  int currentPelvisPoint;
  std::stack<int> removedPelvisPoint;
};

#endif  // VIEWAP_H
