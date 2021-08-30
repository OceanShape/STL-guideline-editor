#ifndef VIEW_H
#define VIEW_H

#include <QGraphicsEllipseItem>
#include <QGraphicsView>
#include <QMouseEvent>
#include <QPoint>

#include "Mode.h"

typedef struct {
  QGraphicsEllipseItem* item;
  QPointF position;
} point;

const int spineCount = 5;
const int pointCountInOneSpine = 4;

class View : public QGraphicsView {
  Q_OBJECT
 public:
  Mode currentMode = Mode::BASE_LINE;

  View::~View();
  explicit View(QWidget* parent = nullptr);
  bool clickRangedEllipseItemOrNull(const QPointF& pos);
  void drawBaseLine(const QPointF& pos, const Qt::MouseButton& btn);
  void drawPointAndLine(QPointF pos, const Qt::MouseButton& btn);

 signals:

 public slots:

 protected:
  point spine[pointCountInOneSpine * spineCount];
  std::vector<point> points;
  int currentPointCount;
  QPen* pen;
  QBrush* brush;
  bool isBaseLineDrawn;
};

#endif  // VIEW_H
