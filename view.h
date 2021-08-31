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
const int pointCountForOneSpine = 4;
//const int totalSpinePointCount = spineCount * pointCountForOneSpine;

class View : public QGraphicsView {
  Q_OBJECT
 public:
  Mode currentMode = Mode::BASE_LINE;

  View::~View();
  explicit View(QWidget* parent = nullptr);
  void initSpineArray();
  bool isPointInvalid(const point& p);
  bool isClickRanged(const QPointF& pos);
  void drawBaseLine(const QPointF& pos, const Qt::MouseButton& btn);
  void drawSpinePoint(QPointF pos, const Qt::MouseButton& btn);
  void drawSpineLine();
  void removeAllLine();

 signals:

 public slots:

 protected:
  point spine[spineCount][pointCountForOneSpine];
  QGraphicsLineItem* spineLine[spineCount][pointCountForOneSpine];
  int currentSpine;
  int currentPointCount;
  std::vector<point> points;
  QPen* pen;
  QBrush* brush;
  bool isBaseLineDrawn;
};

#endif  // VIEW_H
