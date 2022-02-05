#include "GlobalState.h"

void GlobalState::initState() {
  for (int scr = 0; scr < screenCount; ++scr) {
    baseLineStatus[scr] = BaseLineStatus::NOT_SELECTED;
    currentSpinousProcessPoint[scr] = 0;

    for (int i = 0; i < baseLineCount; ++i) baseLine[scr][i] = nullptr;

    currentSpine[scr] = 0;
    currentSpinePoint[scr] = 0;

    for (int i = 0; i < spineCount; ++i) {
      for (int j = 0; j < pointCountForOneSpine; ++j) {
        spinePoint[scr][i][j].position = {-FLT_MAX, -FLT_MAX};
        spinePoint[scr][i][j].item = nullptr;
      }

      spineCenter[scr][i] = {-FLT_MAX, -FLT_MAX};

      for (int j = 0; j < pointCountForOneSpine; ++j)
        spineLine[scr][i][j] = nullptr;
    }

    for (int i = 0; i < spinousProcessPointCount; ++i)
      initPoint(&spinousProcessPoint[scr][i]);

    pen[scr] = new QPen(Qt::green);
    pen[scr]->setWidth(10);
    brush[scr] = new QBrush(Qt::white);
  }

  // ViewAP
  currentPelvisPoint = 0;
  for (int i = 0; i < pelvisPointCount; ++i) initPoint(&pelvisPoint[i]);
  pelvisCenter = {-FLT_MAX, -FLT_MAX};
  pelvisLine = nullptr;

  // ViewLAT
  currentTailbonePoint = 0;
  for (int i = 0; i < tailbonePointCount; ++i) initPoint(&tailbonePoint[i]);
  for (int i = 0; i < tailbonePointCount; ++i) tailboneLine[i] = nullptr;
}

bool GlobalState::isAllDataSet() {
  for (int scr = 0; scr < screenCount; ++scr) {
    for (int i = 0; i < baseLineCount; ++i) {
      if (baseLine[scr][i] == nullptr) return false;
    }

    for (int i = 0; i < spineCount; ++i) {
      for (int j = 0; j < pointCountForOneSpine; ++j)
        if (!isDataValid(spinePoint[scr][i][j])) return false;

      if (spineCenter[scr][i].x() == -FLT_MAX ||
          spineCenter[scr][i].y() == -FLT_MAX)
        return false;

      for (int j = 0; j < pointCountForOneSpine; ++j)
        if (spineLine[scr][i][j] == nullptr) return false;
    }

    for (int i = 0; i < spinousProcessPointCount; ++i) {
      if (!isDataValid(spinousProcessPoint[scr][i])) return false;
    }
  }

  // ViewAP
  for (int i = 0; i < pelvisPointCount; ++i)
    if (!isDataValid(pelvisPoint[i])) return false;
  if (pelvisCenter.x() == -FLT_MAX || pelvisCenter.y() == -FLT_MAX)
    return false;
  if (pelvisLine == nullptr) return false;

  // ViewLAT
  for (int i = 0; i < tailbonePointCount; ++i)
    if (!isDataValid(tailbonePoint[i])) return false;
  for (int i = 0; i < tailbonePointCount; ++i)
    if (tailboneLine[i] == nullptr) return false;

  return true;
}
