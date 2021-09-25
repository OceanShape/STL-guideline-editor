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
static qreal clickCorrectionWidth = 20;
static qreal clickRangeWidth = 50;
static qreal pointRadius = 50;
// const int totalSpinePointCount = spineCount * pointCountForOneSpine;

class View : public QGraphicsView {
  Q_OBJECT
 public:
  Mode currentMode = Mode::BASE_LINE;

  View::~View();
  explicit View(QWidget* parent = nullptr);
  void resetPenSetting();
  void initPoint(point* p);
  bool isPointInvalid(const point& p);
  point* clickRangedPointOrNull(const QPointF& pos, int& outCurrentSpine,
                                int& outCurrentPoint);
  void drawBaseLine(const QPointF& pos, const Qt::MouseButton& btn);
  void drawSpinePoint(QPointF pos, const Qt::MouseButton& btn);
  void drawSpineLine();
  void removeAllSpineLine();

 signals:

 public slots:

 protected:
  point spinePoint[spineCount][pointCountForOneSpine];
  QGraphicsLineItem* spineLine[spineCount][pointCountForOneSpine];
  QPointF spineCenter[spineCount];
  int currentSpine;
  int currentSpinePoint;
  std::stack<std::pair<int, int>> removedSpinePoint;

  QPen* pen;
  QBrush* brush;
  bool isBaseLineDrawn;
};

#endif  // VIEW_H
