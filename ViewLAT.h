#pragma once

#ifndef VIEWLAT_H
#define VIEWLAT_H

#include "View.h"

class ViewLAT : public View {
  Q_OBJECT
 public:
  explicit ViewLAT(QWidget* parent = nullptr){};

  void drawPelvisORTailbonePoint(const QPointF& pos,
                                 const Qt::MouseButton& btn) {
    drawTailbonePoint(pos, btn);
  }

  QPointF getTailbonePoint(int pointIdx) {
    return gs.tailbonePoint[pointIdx].position;
  }

  qreal getTailboneAlpha() {
    return -atan2(gs.tailbonePoint[0].position.y() -
                      gs.tailbonePoint[1].position.y(),
                  gs.tailbonePoint[0].position.x() -
                      gs.tailbonePoint[1].position.x()) *
           180 / M_PI;
  }

  qreal getTailboneBeta() {
    return atan2(gs.tailbonePoint[1].position.y() -
                     gs.tailbonePoint[2].position.y(),
                 gs.tailbonePoint[2].position.x() -
                     gs.tailbonePoint[1].position.x()) *
           180 / M_PI;
  }

  qreal getD1(int spineIdx) {
    qreal x1, y1, x2, y2, m, b, x3, y3;
    x1 = (gs.spinePoint[scr][spineIdx][0].position.x() +
          gs.spinePoint[scr][spineIdx][1].position.x()) /
         2;
    x2 = (gs.spinePoint[scr][spineIdx][2].position.x() +
          gs.spinePoint[scr][spineIdx][3].position.x()) /
         2;
    y1 = (gs.spinePoint[scr][spineIdx][0].position.y() +
          gs.spinePoint[scr][spineIdx][1].position.y()) /
         2;
    y2 = (gs.spinePoint[scr][spineIdx][2].position.y() +
          gs.spinePoint[scr][spineIdx][3].position.y()) /
         2;
    x3 = gs.spinousProcessPoint[scr][spineIdx].position.x();
    y3 = gs.spinousProcessPoint[scr][spineIdx].position.y();
    m = abs((y2 - y1) / (x1 - x2));
    b = -m * x1 + y1;
    return abs(m * x3 - y3 + b) / sqrt(m * m + 1);
  }

 signals:

 public slots:

 private:
  point* clickRangedTailbonePointOrNull(const QPointF& pos,
                                        int& outCurrentPoint);
  void drawTailbonePoint(QPointF pos, const Qt::MouseButton& btn);
  void drawTailboneLine();
  void removeAllTailboneLine();
};

#endif  // VIEWLAT_H
