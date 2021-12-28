#ifndef VIEWLAT_H
#define VIEWLAT_H

#include "View.h"

const int tailbonePointCount = 3;

class ViewLAT : public View {
  Q_OBJECT
 public:
  explicit ViewLAT(QWidget* parent = nullptr);

  void drawPelvisORTailbonePoint(const QPointF& pos,
                                 const Qt::MouseButton& btn) {
    drawTailbonePoint(pos, btn);
  }

  QPointF getTailbonePoint(int pointIdx) {
    return tailbonePoint[pointIdx].position;
  }

  qreal getTailboneAlpha() {
    return -atan2(
               tailbonePoint[0].position.y() - tailbonePoint[1].position.y(),
               tailbonePoint[0].position.x() - tailbonePoint[1].position.x()) *
           180 / M_PI;
  }

  qreal getTailboneBeta() {
    return atan2(
               tailbonePoint[1].position.y() - tailbonePoint[2].position.y(),
               tailbonePoint[2].position.x() - tailbonePoint[1].position.x()) *
           180 / M_PI;
  }

 signals:

 public slots:

 private:
  point* clickRangedTailbonePointOrNull(const QPointF& pos,
                                        int& outCurrentPoint);
  void drawTailbonePoint(QPointF pos, const Qt::MouseButton& btn);
  void drawTailboneLine();
  void removeAllTailboneLine();

 public:
  point tailbonePoint[tailbonePointCount];
  QGraphicsItem* tailboneLine[tailbonePointCount];
  int currentTailbonePoint;
  std::stack<int> removedTailbonePoint;
};

#endif  // VIEWLAT_H
