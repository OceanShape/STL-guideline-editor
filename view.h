#ifndef VIEW_H
#define VIEW_H

#include <QGraphicsEllipseItem>
#include <QGraphicsView>
#include <QMouseEvent>
#include <QPoint>
#include <QtMath>
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
const int spinousProcessPointCount = 5;
static qreal clickCorrectionWidth = 20;
static qreal clickRangeWidth = 50;
static qreal pointRadius = 50;
static qreal defaultBaseLineAPX = 1920;
static qreal defaultBaseLineAPY = 2800;
static qreal defaultBaseLineLATY = 2876;
static qreal defaultBaseLineLATZ = 1513;

class View : public QGraphicsView {
  Q_OBJECT
public:
  Mode currentMode = Mode::BASE_LINE;

 public:
  View::~View();
  explicit View(QWidget* parent = nullptr);
  virtual void drawPelvisORTailbonePoint(const QPointF& pos, const Qt::MouseButton& btn) {};
  QPointF getBasePoint() {
    return { baseLine[BaseLineType::VERTICAL]->line().p1().x(),
            baseLine[BaseLineType::HORIZONTAL]->line().p1().y() };
  }
  QPointF getSpinePoint(int spineIdx, int pointIdx) {
    return spinePoint[spineIdx][pointIdx].position;
  }
  QPointF getSpinousProcessPoint(int spineIdx) {
    return spinousProcessPoint[spineIdx].position;
  }
  void resetPenSetting();
  void initPoint(point* p);
  bool isPointInvalid(const point& p);
  point* clickRangedPointOrNull(const QPointF& pos, int& outCurrentSpine,
                                int& outCurrentPoint);
  BaseLineType clickRangedBaseLine(const QPointF& pos);
  void mousePressEvent(QMouseEvent* event) override;
  void mouseReleaseEvent(QMouseEvent* event) override;
  void mouseMoveEvent(QMouseEvent* event) override;
  void keyPressEvent(QKeyEvent* event) override;
  void drawDefaultBaseLine(const QPointF& pos);
  void drawBaseLine(const QPointF& pos, const Qt::MouseButton& btn);
  void moveBaseLine(const QPointF& pos);
  void releaseBaseLine(const QPointF& pos);
  void redrawBaseLine(const QPointF& pos, const BaseLineType& baseLineType);
  void drawSpinePoint(QPointF pos, const Qt::MouseButton& btn);
  void drawSpineLine();
  void removeAllSpineLine();
  void sortSpinousProcessPoint();
  point* clickRangedSpinousProcessPointOrNull(const QPointF& pos, int& outCurrentPoint);
  void drawSpinousProcessPoint(QPointF pos, const Qt::MouseButton& btn);

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
  point spinousProcessPoint[spinousProcessPointCount];
  int currentSpinousProcessPoint;
  std::stack<int> removedSpinousProcessPoint;

  QPen* pen;
  QBrush* brush;
};
#endif  // VIEW_H
