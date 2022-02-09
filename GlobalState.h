#pragma once

#ifndef GLOBALSTATE_H
#define GLOBALSTATE_H

#define SCREEN_COUNT 2
#define BASELINE_COUNT 2
#define SPINE_COUNT 5
#define POINT_COUNT_FOR_ONE_SPINE 4
#define SPINOUS_PROCESS_POINT_COUNT 5
#define CLICK_CORRECTION_WIDTH 20
#define CLICK_RANGE_WIDTH 50
#define POINT_RADIUS 50
#define DEFAULT_BASELINE_AP_X 1920
#define DEFAULT_BASELINE_AP_Y 2800
#define DEFAULT_BASELINE_LAT_Y 2876
#define DEFAULT_BASELINE_LAT_Z 1513
#define IMAGE_HEIGHT 4480
#define PELVIS_POINT_COUNT 2
#define TAILBONE_POINT_COUNT 3

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

  BaseLineStatus baseLineStatus[SCREEN_COUNT];
  QGraphicsLineItem* baseLine[SCREEN_COUNT][BASELINE_COUNT];

  point spinePoint[SCREEN_COUNT][SPINE_COUNT][POINT_COUNT_FOR_ONE_SPINE];
  QGraphicsLineItem* spineLine[SCREEN_COUNT][SPINE_COUNT][POINT_COUNT_FOR_ONE_SPINE];
  QPointF spineCenter[SCREEN_COUNT][SPINE_COUNT];
  int currentSpine[SCREEN_COUNT];
  int currentSpinePoint[SCREEN_COUNT];
  std::stack<std::pair<int, int>> removedSpinePoint[SCREEN_COUNT];
  point spinousProcessPoint[SCREEN_COUNT][SPINOUS_PROCESS_POINT_COUNT];
  int currentSpinousProcessPoint[SCREEN_COUNT];
  std::stack<int> removedSpinousProcessPoint[SCREEN_COUNT];

  // ViewAP data
  point pelvisPoint[PELVIS_POINT_COUNT];
  QGraphicsItem* pelvisLine;
  QPointF pelvisCenter;
  int currentPelvisPoint;
  std::stack<int> removedPelvisPoint;

  // ViewLAT data
  point tailbonePoint[TAILBONE_POINT_COUNT];
  QGraphicsItem* tailboneLine[TAILBONE_POINT_COUNT];
  int currentTailbonePoint;
  std::stack<int> removedTailbonePoint;

  QPen* pen[SCREEN_COUNT];
  QBrush* brush[SCREEN_COUNT];

public:
  static GlobalState& getIncetance() {
    static GlobalState gs;
    return gs;
  }
  static void initPoint(point* p) {
    p->position = { -FLT_MAX, -FLT_MAX };
    p->item = nullptr;
  }
  static bool isDataValid(const point& p) {
    return isDataValid(p.item) && isDataValid(p.position);
  };
  static bool isDataValid(const QPointF& f) {
    return f.x() != -FLT_MAX && f.y() != -FLT_MAX;
  };
  static bool isDataValid(const QGraphicsItem* i) { return i != nullptr; };
  bool isAllDataSet();

 private:
  void initState();
  GlobalState() { initState(); }
  GlobalState(const GlobalState& ref) { initState(); }
  GlobalState& operator=(const GlobalState& ref) {}
  ~GlobalState() {
    for (int scr = 0; scr < SCREEN_COUNT; ++scr) {
      delete pen[scr];
      delete brush[scr];
    }
  }
};
#endif
