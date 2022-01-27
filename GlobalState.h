#pragma once

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
//#define pelvisPointCount 2
//#define tailbonePointCount 3

#include <qgraphicsitem.h>
#include <stack>

#include "BaseLineStatus.h"

//typedef struct {
//  QGraphicsEllipseItem* item;
//  QPointF position;
//} point;

// typedef GlobalState GS;

class GlobalState {
 public:
  static GlobalState& instance() {
    static GlobalState* instance = new GlobalState();
    return *instance;
  }

  //BaseLineStatus baseLineStatus;
  //static QGraphicsLineItem* baseLine[baseLineCount];

  //point spinePoint[spineCount][pointCountForOneSpine];
  //QGraphicsLineItem* spineLine[spineCount][pointCountForOneSpine];
  //QPointF spineCenter[spineCount];
  //int currentSpine;
  //int currentSpinePoint;
  //std::stack<std::pair<int, int>> removedSpinePoint;
  //point spinousProcessPoint[spinousProcessPointCount];
  //int currentSpinousProcessPoint;
  //std::stack<int> removedSpinousProcessPoint;

  //QPen* pen;
  //QBrush* brush;

  // LAT
  // point tailbonePoint[tailbonePointCount];
  // QGraphicsItem* tailboneLine[tailbonePointCount];
  /*int currentTailbonePoint;
  std::stack<int> removedTailbonePoint;*/

  // AP
  // point pelvisPoint[pelvisPointCount];
  /*QGraphicsItem* pelvisLine;
  QPointF pelvisCenter;
  int currentPelvisPoint;
  std::stack<int> removedPelvisPoint;*/

 private:
  GlobalState() {}
};
