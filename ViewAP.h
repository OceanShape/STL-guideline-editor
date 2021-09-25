#ifndef VIEWAP_H
#define VIEWAP_H

#include "View.h"

const int pelvisPointCount = 2;

class ViewAP : public View {
  Q_OBJECT
 public:
   explicit ViewAP(QWidget* parent = nullptr);

 signals:

 public slots:

 private:
  void mousePressEvent(QMouseEvent* event) override;
  void keyPressEvent(QKeyEvent* event) override;
  point* clickRangedPointOrNull(const QPointF& pos, int& outCurrentPoint);
  void drawPelvisPoint(QPointF pos, const Qt::MouseButton& btn);
  void drawPelvisLine();
  void removeAllSpineLine();

public:
  point pelvisPoint[pelvisPointCount];
  QGraphicsItem* pelvisLine;
  QPointF pelvisCenter;
  int currentPelvisPoint;
  std::stack<int> removedPelvisPoint;
};

#endif  // VIEWAP_H
