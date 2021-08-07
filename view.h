#ifndef VIEW_H
#define VIEW_H

#include <QGraphicsEllipseItem>
#include <QGraphicsView>
#include <QMouseEvent>
#include <QPoint>

typedef struct {
  QGraphicsEllipseItem* item;
  QPointF position;
} point;

class View : public QGraphicsView {
  Q_OBJECT
 public:
  explicit View(QWidget* parent = nullptr);
  bool clickRangedEllipseItemOrNull(const QPointF& pos);

 signals:

 public slots:

 protected:
  std::vector<point> points;

  void mousePressEvent(QMouseEvent* event) override;
};

#endif  // VIEW_H
