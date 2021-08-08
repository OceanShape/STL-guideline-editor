#ifndef VIEWAP_H
#define VIEWAP_H

#include "View.h"

class ViewAP : public View {
  Q_OBJECT
 public:
  ViewAP::~ViewAP();
  explicit ViewAP(QWidget* parent = nullptr);

 signals:

 public slots:

 private:
  // void mousePressEvent(QMouseEvent* event) override;
};

#endif  // VIEWAP_H
