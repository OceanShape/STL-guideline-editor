#ifndef VIEWAP_H
#define VIEWAP_H

#include "View.h"

const int pelvisPointCount = 2;
const int spinousProcessPointCount = 5;

class ViewAP : public View {
  Q_OBJECT
 public:
   explicit ViewAP(QWidget* parent = nullptr);

 signals:

 public slots:

 private:
  void mousePressEvent(QMouseEvent* event) override;
  point* clickRangedPelvisPointOrNull(const QPointF& pos, int& outCurrentPoint);
  void drawPelvisPoint(QPointF pos, const Qt::MouseButton& btn);
  void drawPelvisLine();
  void removeAllPelvisLine();

  void sortSpinousProcessPoint();
  point* clickRangedSpinousProcessPointOrNull(const QPointF& pos, int& outCurrentPoint);
  void drawSpinousProcessPoint(QPointF pos, const Qt::MouseButton& btn);

public:
  point pelvisPoint[pelvisPointCount];
  QGraphicsItem* pelvisLine;
  QPointF pelvisCenter;
  int currentPelvisPoint;
  std::stack<int> removedPelvisPoint;

  point spinousProcessPoint[spinousProcessPointCount];
  int currentSpinousProcessPoint;
  std::stack<int> removedSpinousProcessPoint;
};

#endif  // VIEWAP_H
