#include "GlobalState.h"

void GlobalState::initState() {
  for (int scr = 0; scr < SCREEN_COUNT; ++scr) {
    baseLineStatus[scr] = BaseLineStatus::NOT_SELECTED;
    currentSpinousProcessPoint[scr] = 0;

    for (int i = 0; i < BASELINE_COUNT; ++i) baseLine[scr][i] = nullptr;

    currentSpine[scr] = 0;
    currentSpinePoint[scr] = 0;

    for (int i = 0; i < SPINE_COUNT; ++i) {
      for (int j = 0; j < POINT_COUNT_FOR_ONE_SPINE; ++j) {
        spinePoint[scr][i][j].position = {-FLT_MAX, -FLT_MAX};
        spinePoint[scr][i][j].item = nullptr;
      }

      spineCenter[scr][i] = {-FLT_MAX, -FLT_MAX};

      for (int j = 0; j < POINT_COUNT_FOR_ONE_SPINE; ++j)
        spineLine[scr][i][j] = nullptr;
    }

    for (int i = 0; i < SPINOUS_PROCESS_POINT_COUNT; ++i)
      initPoint(&spinousProcessPoint[scr][i]);

    pen[scr] = new QPen(Qt::green);
    pen[scr]->setWidth(10);
    brush[scr] = new QBrush(Qt::white);
  }

  // ViewAP
  currentPelvisPoint = 0;
  for (int i = 0; i < PELVIS_POINT_COUNT; ++i) initPoint(&pelvisPoint[i]);
  pelvisCenter = {-FLT_MAX, -FLT_MAX};
  pelvisLine = nullptr;

  // ViewLAT
  currentTailbonePoint = 0;
  for (int i = 0; i < TAILBONE_POINT_COUNT; ++i) initPoint(&tailbonePoint[i]);
  for (int i = 0; i < TAILBONE_POINT_COUNT; ++i) tailboneLine[i] = nullptr;
}

bool GlobalState::isAllDataSet() {
  for (int scr = 0; scr < SCREEN_COUNT; ++scr) {
    for (int i = 0; i < BASELINE_COUNT; ++i) {
      if (baseLine[scr][i] == nullptr) return false;
    }

    for (int i = 0; i < SPINE_COUNT; ++i) {
      for (int j = 0; j < POINT_COUNT_FOR_ONE_SPINE; ++j)
        if (!isDataValid(spinePoint[scr][i][j])) return false;

      if (spineCenter[scr][i].x() == -FLT_MAX ||
          spineCenter[scr][i].y() == -FLT_MAX)
        return false;

      for (int j = 0; j < POINT_COUNT_FOR_ONE_SPINE; ++j)
        if (spineLine[scr][i][j] == nullptr) return false;
    }

    for (int i = 0; i < SPINOUS_PROCESS_POINT_COUNT; ++i) {
      if (!isDataValid(spinousProcessPoint[scr][i])) return false;
    }
  }

  // ViewAP
  for (int i = 0; i < PELVIS_POINT_COUNT; ++i)
    if (!isDataValid(pelvisPoint[i])) return false;
  if (pelvisCenter.x() == -FLT_MAX || pelvisCenter.y() == -FLT_MAX)
    return false;
  if (pelvisLine == nullptr) return false;

  // ViewLAT
  for (int i = 0; i < TAILBONE_POINT_COUNT; ++i)
    if (!isDataValid(tailbonePoint[i])) return false;
  for (int i = 0; i < TAILBONE_POINT_COUNT; ++i)
    if (tailboneLine[i] == nullptr) return false;

  return true;
}
