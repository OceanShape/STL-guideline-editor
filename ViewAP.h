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
