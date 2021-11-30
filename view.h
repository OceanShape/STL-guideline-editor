#ifndef VIEW_H
#define VIEW_H

#include <QGraphicsEllipseItem>
#include <QGraphicsView>
#include <QMouseEvent>
#include <QPoint>
#include <stack>

#include "BaseLineStatus.h"
#include "BaseLineType.h"
#include "Mode.h"

typedef struct {
  QGraphicsEllipseItem* item;
  QPointF position;
} point;

const int baseLineCount = 2;
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

 public:
  View::~View();
  explicit View(QWidget* parent = nullptr);
  QPointF getBasePoint();
  QPointF getSpinePoint(int spineIdx, int pointIdx) {
    return spinePoint[spineIdx][pointIdx].position;
  }
  void resetPenSetting();
  void initPoint(point* p);
  bool isPointInvalid(const point& p);
  point* clickRangedPointOrNull(const QPointF& pos, int& outCurrentSpine,
                                int& outCurrentPoint);
  BaseLineType clickRangedBaseLine(const QPointF& pos);
  void mouseReleaseEvent(QMouseEvent* event) override;
  void mouseMoveEvent(QMouseEvent* event) override;
  void keyPressEvent(QKeyEvent* event) override;
  void drawBaseLine(const QPointF& pos, const Qt::MouseButton& btn);
  void moveBaseLine(const QPointF& pos);
  void releaseBaseLine(const QPointF& pos);
  void redrawBaseLine(const QPointF& pos, const BaseLineType& baseLineType);
  void drawSpinePoint(QPointF pos, const Qt::MouseButton& btn);
  void drawSpineLine();
  void removeAllSpineLine();

 signals:

 public slots:
 protected:
  bool isBaseLineDrawn;
  BaseLineStatus baseLineStatus;
  QGraphicsLineItem* baseLine[baseLineCount];

  point spinePoint[spineCount][pointCountForOneSpine];
  QGraphicsLineItem* spineLine[spineCount][pointCountForOneSpine];
  QPointF spineCenter[spineCount];
  int currentSpine;
  int currentSpinePoint;
  std::stack<std::pair<int, int>> removedSpinePoint;

  QPen* pen;
  QBrush* brush;
};
#endif  // VIEW_H
