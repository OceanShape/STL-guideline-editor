#ifndef VIEWLAT_H
#define VIEWLAT_H

#include "View.h"

class ViewLAT : public View {
  Q_OBJECT
 public:
  ViewLAT::~ViewLAT();
  explicit ViewLAT(QWidget* parent = nullptr);

 signals:

 public slots:

 private:
  // void mousePressEvent(QMouseEvent* event) override;
};

#endif  // VIEWLAT_H
