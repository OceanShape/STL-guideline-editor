//#include <qgraphicsitem.h>
//
//
//#include "BaseLineStatus.h"
//
//class GlobalState {
// public:
//  static GlobalState& instance() {
//    static GlobalState* instance = new GlobalState();
//    return *instance;
//  }
//
//  BaseLineStatus baseLineStatus;
//  static QGraphicsLineItem* baseLine[baseLineCount];
//
//  point spinePoint[spineCount][pointCountForOneSpine];
//  QGraphicsLineItem* spineLine[spineCount][pointCountForOneSpine];
//  QPointF spineCenter[spineCount];
//  int currentSpine;
//  int currentSpinePoint;
//  std::stack<std::pair<int, int>> removedSpinePoint;
//  point spinousProcessPoint[spinousProcessPointCount];
//  int currentSpinousProcessPoint;
//  std::stack<int> removedSpinousProcessPoint;
//
//  QPen* pen;
//  QBrush* brush;
//
//  // LAT
//  point tailbonePoint[tailbonePointCount];
//  QGraphicsItem* tailboneLine[tailbonePointCount];
//  int currentTailbonePoint;
//  std::stack<int> removedTailbonePoint;
//
//  // AP
//  point pelvisPoint[pelvisPointCount];
//  QGraphicsItem* pelvisLine;
//  QPointF pelvisCenter;
//  int currentPelvisPoint;
//  std::stack<int> removedPelvisPoint;
//
// private:
//  GlobalState() {}
//};
//
//const int baseLineCount;
//const int spineCount;
//const int pointCountForOneSpine;
//const int spinousProcessPointCount;
//const qreal clickCorrectionWidth;
//const qreal clickRangeWidth;
//const qreal pointRadius;
//const qreal defaultBaseLineAPX;
//const qreal defaultBaseLineAPY;
//const qreal defaultBaseLineLATY;
//const qreal defaultBaseLineLATZ;
