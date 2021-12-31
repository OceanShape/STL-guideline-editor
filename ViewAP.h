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

  qreal getD2(int spineIdx) {
    qreal x1, y1, x2, y2, m, b, x3, y3;
    x1 = (spinePoint[spineIdx][0].position.x() +
          spinePoint[spineIdx][1].position.x()) /
         2;
    x2 = (spinePoint[spineIdx][2].position.x() +
          spinePoint[spineIdx][3].position.x()) /
         2;
    y1 = (spinePoint[spineIdx][0].position.y() +
          spinePoint[spineIdx][1].position.y()) /
         2;
    y2 = (spinePoint[spineIdx][2].position.y() +
          spinePoint[spineIdx][3].position.y()) /
         2;
    x3 = spinousProcessPoint[spineIdx].position.x();
    y3 = spinousProcessPoint[spineIdx].position.y();
    m = (y2 - y1) / (x1 - x2);
    b = -m * x1 + y1;
    qreal res = abs(m * x3 - y3 + b) / sqrt(m * m + 1);
    if (x3 > (x1 + x2) / 2) {
      res *= -1;
    }
    return res;
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
