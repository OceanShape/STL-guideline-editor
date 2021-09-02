#ifndef VIEWLAT_H
#define VIEWLAT_H

#include "View.h"

class ViewLAT : public View {
  Q_OBJECT
 public:
  explicit ViewLAT(QWidget* parent = nullptr) : View(parent){};

 signals:

 public slots:

 private:
  void mousePressEvent(QMouseEvent* event) override;
  void keyPressEvent(QKeyEvent* event) override;
};

#endif  // VIEWLAT_H
