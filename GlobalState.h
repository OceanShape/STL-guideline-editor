#pragma once

#ifndef GLOBALSTATE_H
#define GLOBALSTATE_H

#define screenCount 2
#define baseLineCount 2
#define spineCount 5
#define pointCountForOneSpine 4
#define spinousProcessPointCount 5
#define clickCorrectionWidth 20
#define clickRangeWidth 50
#define pointRadius 50
#define defaultBaseLineAPX 1920
#define defaultBaseLineAPY 2800
#define defaultBaseLineLATY 2876
#define defaultBaseLineLATZ 1513
#define pelvisPointCount 2
#define tailbonePointCount 3

#include <qbrush.h>
#include <qgraphicsitem.h>
#include <qpen.h>

#include <qpoint>
#include <stack>

#include "BaseLineStatus.h"

typedef struct {
  QGraphicsEllipseItem* item;
  QPointF position;
} point;

typedef enum Screen { AP, LAT } SCR;

class GlobalState {
 public:
  GlobalState* instance;

  BaseLineStatus baseLineStatus[screenCount];
  QGraphicsLineItem* baseLine[screenCount][baseLineCount];

  point spinePoint[screenCount][spineCount][pointCountForOneSpine];
  QGraphicsLineItem* spineLine[screenCount][spineCount][pointCountForOneSpine];
  QPointF spineCenter[screenCount][spineCount];
  int currentSpine[screenCount];
  int currentSpinePoint[screenCount];
  std::stack<std::pair<int, int>> removedSpinePoint[screenCount];
  point spinousProcessPoint[screenCount][spinousProcessPointCount];
  int currentSpinousProcessPoint[screenCount];
  std::stack<int> removedSpinousProcessPoint[screenCount];

  // ViewAP data
  point pelvisPoint[pelvisPointCount];
  QGraphicsItem* pelvisLine;
  QPointF pelvisCenter;
  int currentPelvisPoint;
  std::stack<int> removedPelvisPoint;

  // ViewLAT data
  point tailbonePoint[tailbonePointCount];
  QGraphicsItem* tailboneLine[tailbonePointCount];
  int currentTailbonePoint;
  std::stack<int> removedTailbonePoint;

  QPen* pen[screenCount];
  QBrush* brush[screenCount];

 public:
  static GlobalState& getIncetance() {
    static GlobalState gs;
    return gs;
  }
  void initPoint(point* p) {
    p->position = {-FLT_MAX, -FLT_MAX};
    p->item = nullptr;
  }

 private:
  void initState();
  GlobalState() { initState(); }
  GlobalState(const GlobalState& ref) { initState(); }
  GlobalState& operator=(const GlobalState& ref) {}
  ~GlobalState() {
    for (int scr = 0; scr < screenCount; ++scr) {
      delete pen[scr];
      delete brush[scr];
    }
  }
};
#endif
