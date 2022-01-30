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
  pelvisCenter = { -FLT_MAX, -FLT_MAX };
  pelvisLine = nullptr;

  // ViewLAT
  currentTailbonePoint = 0;
  for (int i = 0; i < tailbonePointCount; ++i) initPoint(&tailbonePoint[i]);
  for (int i = 0; i < tailbonePointCount; ++i) tailboneLine[i] = nullptr;
}
