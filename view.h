#ifndef VIEW_H
#define VIEW_H

#include <QGraphicsEllipseItem>
#include <QGraphicsView>
#include <QMouseEvent>
#include <QPoint>
#include <stack>

#include "Mode.h"

typedef struct {
  QGraphicsEllipseItem* item;
  QPointF position;
} point;

const int spineCount = 5;
const int pointCountForOneSpine = 4;
// const int totalSpinePointCount = spineCount * pointCountForOneSpine;

class View : public QGraphicsView {
  Q_OBJECT
 public:
  Mode currentMode = Mode::BASE_LINE;
  std::stack<std::pair<int, int>> removedPoint;

  View::~View();
  explicit View(QWidget* parent = nullptr);
  void initSpinePoint(point* p);
  void initSpineArray();
  bool isPointInvalid(const point& p);
  point* clickRangedPointOrNull(const QPointF& pos, int& outCurrentSpine,
                                int& outCurrentPoint);
  void drawBaseLine(const QPointF& pos, const Qt::MouseButton& btn);
  void drawSpinePoint(QPointF pos, const Qt::MouseButton& btn);
  void drawSpineLine();
  void removeAllLine();
  void update();

 signals:

 public slots:

 protected:
  point spinePoint[spineCount][pointCountForOneSpine];
  QGraphicsLineItem* spineLine[spineCount][pointCountForOneSpine];
  QPointF spineCenter[spineCount];
  int currentSpine;
  int currentPointCount;
  QPen* pen;
  QBrush* brush;
  bool isBaseLineDrawn;
};

#endif  // VIEW_H
