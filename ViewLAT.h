#ifndef VIEWLAT_H
#define VIEWLAT_H

#include "View.h"

const int tailbonePointCount = 3;

class ViewLAT : public View {
  Q_OBJECT
 public:
  explicit ViewLAT(QWidget* parent = nullptr);

  QPointF getTailbonePoint(int pointIdx) {
    return tailbonePoint[pointIdx].position;
  }

 signals:

 public slots:

 private:
  void mousePressEvent(QMouseEvent* event) override;

  point* clickRangedTailbonePointOrNull(const QPointF& pos, int& outCurrentPoint);
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
